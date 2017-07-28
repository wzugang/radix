/*
 * include/radix/assembler.h
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

#ifndef RADIX_ASSEMBLER_H
#define RADIX_ASSEMBLER_H

#ifdef __ASSEMBLY__

#define ASM_NL ;

#define BEGIN_FUNC(name)                \
	.global name ASM_NL             \
	.type name, @function ASM_NL    \
	name:

#define END_FUNC(name)                  \
	.size name, . - name

#endif /* __ASSEMBLY__ */

#endif /* RADIX_ASSEMBLER_H */
