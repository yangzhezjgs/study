#ifndef RING_H__
#define RING_H__

struct ring_t *ring_t;

extern ring_t ring_new(void);
extern ring_t ring_ring(void *x, ...);
extern void ring_free(ring_t *ring);
extern int ring_length(ring_t ring);
extern void *ring_get(ring_t ring, int i);
extern void *ring_put(ring_t ring, int i, void *x);
extern void *ring_add(ring_t ring, int pos, void *x);
extern void *ring_addlo(ring_t ring, void *X);
extern void *ring_addhi(ring_t ring, void *x);
extern void *ring_remove(ring_t ring, int i);
extern void *ring_remlo(ring_t ring);
extern void *ring_remhi(ring_t ring);
extern void ring_totate(ring_t ring, int n);

#endif
