/* 严重错误, 前驱和后继指针无法存储 */
/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Harry Bovik",
    /* First member's email address */
    "bovik@cs.cmu.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define WSIZE       4
#define DSIZE       8
#define MINSIZE     16
#define CHUNKSIZE   (1<<12)

#define MAX(x, y)   ((x) > (y) ? (x) : (y))

#define PACK(size, alloc) ((size) | (alloc))

#define GET(p)      (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

#define GET_PTR(p)  ((unsigned int *)(long)(GET(p)))
#define PUT_PTR(p, ptr) (*(unsigned int *)(p) = (long)(ptr))

#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

#define HDRP(bp)    ((char *)(bp) - WSIZE)
#define FTRP(bp)    ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define PRED_BLKP(bp)    (bp)
#define SUCC_BLKP(bp)    ((char *)(bp) + DSIZE)

#define NEXT_BLKP(bp)   ((char *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLKP(bp)   ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

static char *heap_blkp;
static void *extend_heap(size_t wrods);
static void *coalesce(void *bp);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    char *bp;
    if ((bp = mem_sbrk(4*WSIZE)) == (void *)-1)
        return -1;
    PUT(bp, 0);
    PUT(bp + (1*WSIZE), PACK(DSIZE, 1));
    PUT(bp + (2*WSIZE), PACK(DSIZE, 1));
    PUT(bp + (3*WSIZE), PACK(0, 1));

    if ((bp = extend_heap(CHUNKSIZE/WSIZE)) == NULL)
        return -1;
    heap_blkp = bp;
    return 0;
}

static void *extend_heap(size_t words)
{
    char *bp;
    size_t size;

    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
    if ((long)(bp = mem_sbrk(size)) == -1)
        return NULL;

    PUT(HDRP(bp), PACK(size, 0));
    PUT_PTR(PRED_BLKP(bp), NULL);
    PUT(FTRP(bp), PACK(size, 0));
    PUT_PTR(SUCC_BLKP(bp), NULL);
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

    return coalesce(bp);
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    size_t asize;
    size_t extendsize;
    char *bp;

    if (size == 0)
        return NULL;

    if (size <= DSIZE) {
        asize = MINSIZE;
    } else {
        asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);
    }

    if ((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
        return NULL;
    place(bp, asize);
    return bp;      
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    size_t size = GET_SIZE(HDRP(ptr));
    char *bp = heap_blkp;

    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    heap_blkp = coalesce(ptr);
    PUT_PTR(PRED_BLKP(heap_blkp), NULL);
    PUT_PTR(SUCC_BLKP(heap_blkp), bp);
    if (heap_blkp + GET_SIZE(HDRP(heap_blkp)) > bp && heap_blkp < bp)
        return;
    PUT_PTR(PRED_BLKP(bp), heap_blkp);
}

static void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) {
        return bp;
    } else if (prev_alloc && !next_alloc) {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
        PUT_PTR(SUCC_BLKP(GET_PTR(PRED_BLKP(NEXT_BLKP(bp)))), GET_PTR(SUCC_BLKP(NEXT_BLKP(bp))));
        PUT_PTR(PRED_BLKP(GET_PTR(SUCC_BLKP(NEXT_BLKP(bp)))), GET_PTR(PRED_BLKP(NEXT_BLKP(bp))));
    } else if (!prev_alloc && next_alloc) {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT_PTR(SUCC_BLKP(GET_PTR(PRED_BLKP(PREV_BLKP(bp)))), GET_PTR(SUCC_BLKP(PREV_BLKP(bp))));
        PUT_PTR(PRED_BLKP(GET_PTR(SUCC_BLKP(PREV_BLKP(bp)))), GET_PTR(PRED_BLKP(PREV_BLKP(bp))));
        bp = PREV_BLKP(bp);
    } else {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        PUT_PTR(SUCC_BLKP(GET_PTR(PRED_BLKP(NEXT_BLKP(bp)))), GET_PTR(SUCC_BLKP(NEXT_BLKP(bp))));
        PUT_PTR(PRED_BLKP(GET_PTR(SUCC_BLKP(NEXT_BLKP(bp)))), GET_PTR(PRED_BLKP(NEXT_BLKP(bp))));
        PUT_PTR(SUCC_BLKP(GET_PTR(PRED_BLKP(PREV_BLKP(bp)))), GET_PTR(SUCC_BLKP(PREV_BLKP(bp))));
        PUT_PTR(PRED_BLKP(GET_PTR(SUCC_BLKP(PREV_BLKP(bp)))), GET_PTR(PRED_BLKP(PREV_BLKP(bp))));
        bp = PREV_BLKP(bp);
    }
    return bp;
}

static void *find_fit(size_t asize)
{
    void *bp = heap_blkp;

    do {
        if (asize <= GET_SIZE(HDRP(bp)))
            return bp;
        bp = GET_PTR(SUCC_BLKP(bp));
    } while (bp != NULL);
    return NULL;
}

static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));
    char *ptr;

    if ((csize - asize) >= MINSIZE) {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        ptr = NEXT_BLKP(bp);
        PUT(HDRP(ptr), PACK(csize-asize, 0));
        PUT(FTRP(ptr), PACK(csize-asize, 0));
        PUT_PTR(PRED_BLKP(ptr), GET_PTR(PRED_BLKP(PREV_BLKP(ptr))));
        PUT_PTR(SUCC_BLKP(ptr), GET_PTR(SUCC_BLKP(PREV_BLKP(ptr))));
        if (bp != heap_blkp) {
            PUT_PTR(SUCC_BLKP(GET_PTR(PRED_BLKP(ptr))), ptr);
            PUT_PTR(PRED_BLKP(GET_PTR(SUCC_BLKP(ptr))), ptr);
        } else {
            heap_blkp = ptr;
        }
    } else {
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
        if (bp != heap_blkp) {
            PUT_PTR(SUCC_BLKP(GET_PTR(PRED_BLKP(bp))), GET_PTR(SUCC_BLKP(bp)));
            PUT_PTR(PRED_BLKP(GET_PTR(SUCC_BLKP(bp))), GET_PTR(PRED_BLKP(bp)));
        } else {
            heap_blkp = (char *)GET_PTR(SUCC_BLKP(bp));
        }
    }
}




/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;
    
    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}














