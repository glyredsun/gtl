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
#define container_of(list_ptr, type, member)		(type*)((const char*)list_ptr - offset_of(type, member))
#endif // !container_of

#ifndef list_head_of
#define list_head_of(container_ptr, type, member)	(list_head*)((const char*)container_ptr + offset_of(type, member))
#endif // !list_of

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

static inline void __list_add(struct list_head *n, struct list_head *prev, struct list_head *next)
{
	n->next = next;
	n->prev = prev;
	prev->next = n;
	next->prev = n;
}

static inline void list_add(struct list_head *n, struct list_head *head)
{
	__list_add(n, head, head->next);
}

static inline void list_add_tail(struct list_head *n, struct list_head *head)
{
	__list_add(n, head->prev, head);
}

static inline void __list_del(struct list_head *prev, struct list_head *next)
{
	prev->next = next;
	next->prev = prev;
}

static inline void list_del(struct list_head *head)
{
	__list_del(head->prev, head->next);
}

static inline void list_del_init(struct list_head *head)
{
	__list_del(head->prev, head->next);
	list_init(head);
}

static inline void list_replace(struct list_head *o, struct  list_head *n)
{
	n->next = o->next;
	n->prev = o->prev;
	o->prev->next = n;
	o->next->prev = n;
}

static inline void list_replace_init(struct list_head *o, struct list_head *n)
{
	list_replace(o, n);
	list_init(o);
}

static inline void list_move(struct list_head *list, struct list_head *head)
{
	list_del(list);
	list_add(list, head);
}

static inline void list_move_tail(struct list_head *list, struct list_head *head)
{
	list_del(list);
	list_add_tail(list, head);
}

#define list_empty(head)	((head)->next == (head))

#define list_is_singular(head)	(!list_empty(head) && (head)->prev == (head)->next)

#define list_is_last(entry, head)	((entry)->next == (head))

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