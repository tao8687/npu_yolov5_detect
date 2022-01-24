/*
 * Copyright (c) HighPoint Technologies, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/sys/dev/hptrr/vim_list.h,v 1.2.2.1.4.1 2010/06/14 02:09:06 kensmith Exp $
 */
/*
 * $Id: vim_list.h,v 1.6 2006/10/31 06:25:28 gmm Exp $
 * Copyright (C) 2004-2005 HighPoint Technologies, Inc. All rights reserved.
 */
#ifndef _VIM_LIST_H_
#define _VIM_LIST_H_

#ifndef _LINUX_LIST_H

#ifndef VIM_INLINE
#define VIM_INLINE __inline
#endif

typedef unsigned long VIM_UPTR;

struct vim_list_head {
	struct vim_list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define INIT_LIST_HEAD(ptr) do { (ptr)->next = (ptr); (ptr)->prev = (ptr); } while (0)

static VIM_INLINE void __vim_list_add(struct vim_list_head * _new, struct vim_list_head * prev, struct vim_list_head * next)
{
	next->prev = _new;
	_new->next = next;
	_new->prev = prev;
	prev->next = _new;
}

static VIM_INLINE void vim_list_add(struct vim_list_head *_new, struct vim_list_head *head)
{
	__vim_list_add(_new, head, head->next);
}

static VIM_INLINE void vim_list_add_tail(struct vim_list_head *_new, struct vim_list_head *head)
{
	__vim_list_add(_new, head->prev, head);
}

static VIM_INLINE void __vim_list_del(struct vim_list_head * prev, struct vim_list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

static VIM_INLINE void vim_list_del(struct vim_list_head *entry)
{
	__vim_list_del(entry->prev, entry->next);
}

static VIM_INLINE void vim_list_del_init(struct vim_list_head *entry)
{
	__vim_list_del(entry->prev, entry->next);
	INIT_LIST_HEAD(entry); 
}

static inline void vim_list_move(struct vim_list_head *list, struct vim_list_head *head)
{
        __vim_list_del(list->prev, list->next);
        vim_list_add(list, head);
}

static inline void vim_list_move_tail(struct vim_list_head *list,
				  struct vim_list_head *head)
{
        __vim_list_del(list->prev, list->next);
        vim_list_add_tail(list, head);
}

static VIM_INLINE int vim_list_empty(struct vim_list_head *head)
{
	return head->next == head;
}

static VIM_INLINE void __vim_list_splice(struct vim_list_head *list,
				 struct vim_list_head *head)
{
	struct vim_list_head *first = list->next;
	struct vim_list_head *last = list->prev;
	struct vim_list_head *at = head->next;

	first->prev = head;
	head->next = first;

	last->next = at;
	at->prev = last;
}

static VIM_INLINE void vim_list_splice(struct vim_list_head *list, struct vim_list_head *head)
{
	if (!vim_list_empty(list))
		__vim_list_splice(list, head);
}

static VIM_INLINE void vim_list_splice_init(struct vim_list_head *list, struct vim_list_head *head)
{
	if (!vim_list_empty(list)) {
		__vim_list_splice(list, head);
		INIT_LIST_HEAD(list);
	}
}

/*#define vim_list_entry(ptr, type, member) \
 ((type *)((char *)(ptr)-(VIM_UPTR)(&((type *)0)->member))) */
#define vim_list_entry(ptr, type, member) \
	((type *)((unsigned long)(ptr)-((unsigned long)(&((type *)1)->member) - 1)))

#define vim_list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define vim_list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

#define get_first_item(attached, type, member) \
	((type *)((char *)((attached)->next)-(VIM_UPTR)(&((type *)0)->member)))

#endif

#endif
