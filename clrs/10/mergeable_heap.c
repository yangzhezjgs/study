#include <stdlib.h>

typedef struct node_t {
    int key;
    struct node_t *next;
} node_t;

typedef struct list_t {
    node_t *head;
} list_t;

void
insert_sorted(list_t *list, int key)
{
    node_t *new;
    node_t *node;

    new->key = key;
    node = list->head;

    if (!node || node->key > key) {
        list->head = new;
        new->next = node;
        return;
    }

    while (node->next && node->next < key)
        node = node->next;

    new->next = node->next;
    node->next = new;
}

/* 有序链表实现可合并堆
 * 已排序链表已经满足堆的条件
 */
typedef struct heap_t {
    list_t *heap;
} heap_t;

heap_t
*make_heap(void)
{
    heap_t *heap = malloc(sizeof(heap_t));
    heap->heap->head = NULL;
    return heap;
}

void
insert(heap_t *heap, int key)
{
    insert_sorted(heap->heap, key);
}

int
minimum(heap_t *heap)
{
    return head->heap->head->key;
}

int
extract_min(heap_t *heap)
{
    node_t *head;
    int result;

    head = heap->heap->head;
    result = head->key;
    heap->heap->head = head->next;
    free(head);

    return result;
}

/* union类似归并排序的merge */
