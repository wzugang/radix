/*
 * kernel/kthread.c
 * Copyright (C) 2016-2017 Alexei Frolov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <untitled/kernel.h>
#include <untitled/kthread.h>
#include <untitled/mm.h>
#include <untitled/slab.h>
#include <untitled/task.h>

struct task *kthread_create(void (*func)(void *), void *arg,
                            int page_order, char *name, ...)
{
	struct task *thread;
	struct page *p;
	addr_t stack_top;
	void *err;
	va_list ap;

	if (unlikely(!name))
		return ERR_PTR(EINVAL);

	thread = kthread_task();
	if (IS_ERR(thread))
		return thread;

	p = alloc_pages(PA_STANDARD, page_order);
	if (IS_ERR(p)) {
		err = p;
		goto out_thread;
	}

	stack_top = (addr_t)p->mem + POW2(page_order) * PAGE_SIZE - 0x10;
	kthread_reg_setup(&thread->regs, stack_top, (addr_t)func, (addr_t)arg);
	thread->stack_base = p->mem;

	thread->cmdline = kmalloc(2 * sizeof (*thread->cmdline));
	thread->cmdline[0] = kmalloc(KTHREAD_NAME_LEN);
	va_start(ap, name);
	vsnprintf(thread->cmdline[0], KTHREAD_NAME_LEN, name, ap);
	va_end(ap);
	thread->cmdline[1] = NULL;

	return thread;

out_thread:
	task_free(thread);
	return err;
}

void kthread_start(struct task *thread)
{
	thread->state = TASK_READY;
	sched_add(thread);
}

/*
 * kthread_exit: clean up resources and destroy the current thread.
 * This function is called from within a thread to request termination.
 * All created threads set this function as their base return address.
 */
void kthread_exit(void)
{
	struct task *thread;
	char *s;

	thread = current_task;
	free_pages(thread->stack_base);

	for (s = *thread->cmdline; *s; ++s)
		kfree(s);
	kfree(thread->cmdline);

	task_free(current_task);
	current_task = NULL;
	schedule(1);
}