/*
 * arch/i386/include/radix/asm/ipi.h
 * Copyright (C) 2017 Alexei Frolov
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

#ifndef ARCH_I386_RADIX_IPI_H
#define ARCH_I386_RADIX_IPI_H

#define IPI_VEC_TLB_SHOOTDOWN   0xF0
#define IPI_VEC_TIMER_ACTION    0xF1

#endif /* ARCH_I386_RADIX_IPI_H */
