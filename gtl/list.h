#ifdef _MSC_VER
#pragma once
#endif

#ifndef _LIST_H_
#define	_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef offset_of
#define offset_of(type, member)	(size_t)(&(((type*)0)->member))
#endif // !offset_of

#ifndef container_of
#define container_of(ptr, type, member)		(type*)((const char*)ptr - offset_of(type, member))
#endif // !container_of

#define	list_entry(ptr, type, member)	container_of(ptr, type, member)

struct list_head {
	struct list_head *prev, *next;
};

#define	LIST_HEAD_INIT(name)	{&(name), &(name)}

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name);

static inline void list_init(struct list_head *list)
{
	list->next = list->prev = list;
}

static inline void list_add(struct list_head *n, struct list_head *head)
{
	head->next->prev = n;
	n ->next = head->next;
	head->next = n;
	n->prev = head;
}

static inline void list_add_tail(struct list_head *n, struct list_head *head)
{
	head->prev->next = n;
	n->prev = head->prev;
	head->prev = n;
	n->next = head;
}

static inline void list_del(struct list_head *h)
{
	h->prev->next = h->next;
	h->next->prev = h->prev;
	h->next = h->prev = h;
}

#define list_empty(head)	((head)->next == (head))

#define list_is_singular(head)	(!list_empty(head) && (head)->prev == (head)->next)

#define list_foreach(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_foreach_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

#define list_foreach_prev(pos, head) \
	for (pos = (head)->prev; pos != (head); pos = pos->prev)

#define list_foreach_prev_safe(pos, n, head) \
	for (pos = (head)->prev, n = pos->prev; pos != (head); pos = n, n = pos->prev)

#ifdef __cplusplus
};
#endif

#endif