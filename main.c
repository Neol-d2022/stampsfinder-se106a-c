#include <stdio.h>

#include "stamp.h"
#include "mm.h"

int main(void)
{
    unsigned int *stamps;
    unsigned int target, n, i, t, j;
    Vector_t v, w;

    scanf("%u", &t);

    for (j = 0; j < t; j += 1)
    {
        scanf("%u", &target);
        scanf("%u", &n);

        VInit(&v);
        VInit(&w);
        stamps = Mmalloc(sizeof(*stamps) * n);
        for (i = 0; i < n; i += 1)
        {
            scanf("%u", stamps + i);
            VAdd(&v, stamps + i);
        }

        SFind(&v, &w, target);

        VDeInit(&v);
        Vforeach(&w, NULL, SDestroyV);
        VDeInit(&w);
        Mfree(stamps);
    }
    return 0;
}
