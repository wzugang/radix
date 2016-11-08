/*
 * arch/i386/mm/pagetable.c
 * Copyright (C) 2016 Alexei Frolov
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

#include <untitled/mm.h>
#include <untitled/page.h>

/*
 * The final entry page directory is mapped to the page directory itself.
 * The virtual address 0xFFC00000 is therefore the starting address of the
 * page directory, interpreted as a page table.
 * Virtual address 0xFFFFF000 is the page containing the actual page directory.
 */
#define PGDIR_BASE	0xFFC00000
#define PGDIR_VADDR	0xFFFFF000

/*
 * The page directory of a legacy 2-level x86 paging setup.
 */
pde_t * const pgdir = (pde_t *)PGDIR_VADDR;

addr_t __virt_to_phys(addr_t addr)
{
	size_t pdi, pti;
	pte_t *pgtbl;

	pdi = PGDIR_INDEX(addr);
	pti = PGTBL_INDEX(addr);

	if (PDE(pgdir[pdi]) & PAGE_PRESENT) {
		pgtbl = (pte_t *)(PGDIR_BASE + pdi * PAGE_SIZE);
		if (PTE(pgtbl[pti]) & PAGE_PRESENT)
			return (PTE(pgtbl[pti]) & PAGE_MASK) + (addr & 0xFFF);
	}

	return 0;
}
