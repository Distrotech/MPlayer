/*
 * copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVUTIL_X86_CPU_H
#define AVUTIL_X86_CPU_H

#include <stdint.h>
#include "config.h"

#if ARCH_X86_64 || defined(__ILP32__)
#    define OPSIZE "q"
#    define REG_a "rax"
#    define REG_b "rbx"
#    define REG_c "rcx"
#    define REG_d "rdx"
#    define REG_D "rdi"
#    define REG_S "rsi"
#if defined(__ILP32__)
typedef int32_t x86_ptr;
#else
typedef int64_t x86_ptr;
#endif
#    define PTR_SIZE LP_SIZE
typedef int64_t x86_reg;
#    define REG_SP "rsp"
#    define REG_BP "rbp"
#    define REGBP   RBP_LP
#    define REGa    RAX_LP
#    define REGb    RBX_LP
#    define REGc    RCX_LP
#    define REGd    RDX_LP
#    define REGSP   RSP_LP

#elif ARCH_X86_32

#    define OPSIZE "l"
#    define REG_a "eax"
#    define REG_b "ebx"
#    define REG_c "ecx"
#    define REG_d "edx"
#    define REG_D "edi"
#    define REG_S "esi"
#    define PTR_SIZE "4"
typedef int32_t x86_reg;
typedef int32_t x86_ptr;

#    define REG_SP "esp"
#    define REG_BP "ebp"
#    define REGBP   ebp
#    define REGa    eax
#    define REGb    ebx
#    define REGc    ecx
#    define REGd    edx
#    define REGSP   esp
#else
typedef int x86_reg;
#endif

#define HAVE_7REGS (ARCH_X86_64 || (HAVE_EBX_AVAILABLE && HAVE_EBP_AVAILABLE))
#define HAVE_6REGS (ARCH_X86_64 || (HAVE_EBX_AVAILABLE || HAVE_EBP_AVAILABLE))

#if ARCH_X86_64 && defined(PIC)
#    define BROKEN_RELOCATIONS 1
#endif

/*
 * If gcc is not set to support sse (-msse) it will not accept xmm registers
 * in the clobber list for inline asm. XMM_CLOBBERS takes a list of xmm
 * registers to be marked as clobbered and evaluates to nothing if they are
 * not supported, or to the list itself if they are supported. Since a clobber
 * list may not be empty, XMM_CLOBBERS_ONLY should be used if the xmm
 * registers are the only in the clobber list.
 * For example a list with "eax" and "xmm0" as clobbers should become:
 * : XMM_CLOBBERS("xmm0",) "eax"
 * and a list with only "xmm0" should become:
 * XMM_CLOBBERS_ONLY("xmm0")
 */
#if HAVE_XMM_CLOBBERS
#    define XMM_CLOBBERS(...)        __VA_ARGS__
#    define XMM_CLOBBERS_ONLY(...) : __VA_ARGS__
#else
#    define XMM_CLOBBERS(...)
#    define XMM_CLOBBERS_ONLY(...)
#endif

#endif /* AVUTIL_X86_CPU_H */
