/*-
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $DragonFly: src/usr.bin/make/str.h,v 1.10 2005/07/29 22:48:41 okumoto Exp $
 */

#ifndef str_h_44db59e6
#define	str_h_44db59e6

#include "util.h"

struct Buffer;

/**
 * An array of c-strings.  The pointers stored in argv, point to
 * strings stored in buffer.
 */
typedef struct ArgArray {
	int	size;		/* size of argv array */
	int	argc;		/* strings referenced in argv */
	char	**argv;		/* array of string pointers */
	size_t	len;		/* size of buffer */
	char	*buffer;	/* data buffer */
} ArgArray;

void ArgArray_Init(ArgArray *);
void ArgArray_Done(ArgArray *);

char *str_concat(const char *, char, const char *);
void brk_string(ArgArray *, const char [], bool);
char *MAKEFLAGS_quote(const char *);
void MAKEFLAGS_break(ArgArray *, const char []);
int Str_Match(const char *, const char *);
const char *Str_SYSVMatch(const char *, const char *, int *);
void Str_SYSVSubst(struct Buffer *, const char *, const char *, int);

#endif /* str_h_44db59e6 */
