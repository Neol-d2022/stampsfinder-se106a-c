#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "stamp.h"
#include "mm.h"

static int _SInit(const Vector_t *stamps, Vector_t *startIA, unsigned int targetValue)
{
    size_t *p, j;
    unsigned int m, n, i;

    j = stamps->count - 1;
    m = *(unsigned int *)(stamps->storage[j]);
    n = (unsigned int)ceil((double)targetValue / (double)m);

    for (i = 0; i < n; i += 1)
    {
        p = Mmalloc(sizeof(*p));
        *p = j;
        VAdd(startIA, p);
    }

    return 0;
}

static unsigned int _SSum(const Vector_t *stamps, Vector_t *ia);
static int _SStepDown(const Vector_t *stamps, Vector_t *ia, unsigned int targetValue)
{
    unsigned int n, d, m, i, r;
    size_t *p, *q, j;

    if (stamps->count == 0)
        return 1;

    if (ia->count == 0)
        return 1;

    p = (size_t *)(ia->storage[0]);
    VRemoveI(ia, 0);

    n = _SSum(stamps, ia);
    if (n < targetValue)
    {
        if (*p > 0)
        {
            j = (*p) - 1;
            m = *(unsigned int *)(stamps->storage[j]);
            d = targetValue - n;
            r = (unsigned int)ceil((double)d / (double)m);
            for (i = 0; i < r; i += 1)
            {
                q = Mmalloc(sizeof(*q));
                *q = j;
                VAdd(ia, q);
            }
        }
    }

    Mfree(p);
    return 0;
}

typedef struct
{
    Vector_t *destination;
} _SFind_copyInit_internal_object_t;

static void _SFind_copyInit(void *data, void *param)
{
    _SFind_copyInit_internal_object_t *io = (_SFind_copyInit_internal_object_t *)param;
    unsigned int *u = (unsigned int *)data, *v;

    v = Mmalloc(sizeof(*v));
    *v = *u;
    VAdd(io->destination, v);
}

static int _ScmpV(const void *a, const void *b)
{
    unsigned int *c = *(unsigned int **)a;
    unsigned int *d = *(unsigned int **)b;

    if (*c > *d)
        return 1;
    else if (*c < *d)
        return -1;
    else
        return 0;
}

static int _ScmpIA(const void *a, const void *b)
{
    size_t *c = *(size_t **)a;
    size_t *d = *(size_t **)b;

    if (*c > *d)
        return 1;
    else if (*c < *d)
        return -1;
    else
        return 0;
}

void SDestroyV(void *data, void *_)
{
    Mfree(data);
    data = _;
}

static void _SDebug(const Vector_t *stamps, Vector_t *ia, unsigned int targetValue)
{
    size_t i;

    fprintf(stderr, "[");
    if (stamps->count > 0)
    {
        fprintf(stderr, "%u", *(unsigned int *)(stamps->storage[0]));
        for (i = 1; i < stamps->count; i += 1)
            fprintf(stderr, ", %u", *(unsigned int *)(stamps->storage[i]));
    }
    fprintf(stderr, "]\n[");
    if (ia->count > 0)
    {
        fprintf(stderr, "%u", *(unsigned int *)(stamps->storage[*(size_t *)(ia->storage[0])]));
        for (i = 1; i < ia->count; i += 1)
            fprintf(stderr, ", %u", *(unsigned int *)(stamps->storage[*(size_t *)(ia->storage[i])]));
    }
    fprintf(stderr, "]\n%u to %u\n", _SSum(stamps, ia), targetValue);
}

int SFind(const Vector_t *stamps, Vector_t *out, unsigned int targetValue)
{
    _SFind_copyInit_internal_object_t io;
    Vector_t _stamps;
    Vector_t *ia = out;

    memset(&io, 0, sizeof(io));
    VInit(&_stamps);
    io.destination = &_stamps;
    Vforeach((Vector_t *)stamps, &io, _SFind_copyInit);
    qsort(_stamps.storage, _stamps.count, sizeof(*(_stamps.storage)), _ScmpV);

    _SInit(&_stamps, ia, targetValue);
    fprintf(stderr, "\n");
    _SDebug(&_stamps, ia, targetValue);

    while (_SSum(&_stamps, ia) != targetValue)
    {
        if (_SStepDown(&_stamps, ia, targetValue))
            break;
        qsort(ia->storage, ia->count, sizeof(*(ia->storage)), _ScmpIA);
        fprintf(stderr, "\n");
        _SDebug(&_stamps, ia, targetValue);
    }

    Vforeach(&_stamps, NULL, SDestroyV);
    VDeInit(&_stamps);

    return 0;
}

// --------

typedef struct
{
    const Vector_t *stamps;
    unsigned int sum;
} _SSum_internal_object_t;

static void _SSum_V_handler(void *data, void *param)
{
    _SSum_internal_object_t *io = (_SSum_internal_object_t *)param;
    size_t *i = (size_t *)data;
    unsigned int v = *((unsigned int *)(io->stamps->storage)[*i]);

    io->sum += v;
}

static unsigned int _SSum(const Vector_t *stamps, Vector_t *ia)
{
    _SSum_internal_object_t io;

    memset(&io, 0, sizeof(io));
    io.stamps = stamps;
    Vforeach(ia, &io, _SSum_V_handler);

    return io.sum;
}
