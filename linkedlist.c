#include <stdlib.h>

#include "linkedlist.h"
#include "mm.h"

void LinkedInit(Linked_t *l)
{
    l->head = NULL;
    l->count = 0;
}

void LinkedDeInit(Linked_t *l)
{
    LinkedNode_t *d, *n;

    d = l->head;
    while (d)
    {
        n = d->next;
        Mfree(d);
        d = n;
    }

    LinkedInit(l);
}

void LinkedQuickInsert(Linked_t *l, LinkedNode_t ***ppp, void *v)
{
    LinkedNode_t *n, **c;

    c = *ppp;
    n = (LinkedNode_t *)Mmalloc(sizeof(*n));
    n->v = v;
    n->next = *c;
    *c = n;
    c = &(n->next);
    *ppp = c;
    l->count += 1;
}

void LinkedIterate(Linked_t *l, void *param, void (*pf)(void *data, void *param))
{
    LinkedNode_t *d;

    d = l->head;
    while (d)
    {
        pf(d->v, param);
        d = d->next;
    }
}
