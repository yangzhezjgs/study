#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct list {
    double val;
    struct list *next;
} list_t;

void
bucket_sort(double buf[], int n)
{
    int i, j;
    list_t *lists[n], *node, *list, *prev;

    memset(lists, 0, sizeof(lists));
    for (i = 0; i < n; i++) {
        node = malloc(sizeof(list_t));
        node->val = buf[i];
        j = (unsigned int) (buf[i] * n);

        list = lists[j];
        if (list == NULL) {
            lists[j] = node;
            node->next = NULL;
        } else {
            for (prev = NULL; list != NULL; prev = list, list = list->next)
                if (list->val >= node->val)
                    if (prev == NULL) {
                        node->next = list;
                        lists[j] = node;
                    } else {
                        node->next = list;
                        prev->next = node;
                    }
        }
    }

    for (i = j = 0; i < n; i++)
        for (list = lists[i]; list != NULL; list = node) {
            buf[j++] = list->val;
            node = list->next;
            free(list);
        }
}

int
main(void)
{
    double buf[] = { 0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68 };
    int i;

    bucket_sort(buf, 10);
    for (i = 0; i < 10; i++)
        printf("%.2f ", buf[i]);
    printf("\n");

    return 0;
}
