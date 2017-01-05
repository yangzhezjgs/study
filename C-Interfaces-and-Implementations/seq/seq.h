#ifndef SEQ_H__
#define SEQ_H__

typedef struct seq_t *seq_t;

extern seq_t seq_new(int hint);
extern seq_t seq_seq(void *x, ...);
extern void seq_free(seq_t *seq);
extern int seq_length(seq_t seq);
extern void *seq_get(seq_t seq, int i);
extern void *seq_put(seq_t seq, int i, void *x);
extern void *seq_addlo(seq_t seq, void *x);
extern void *seq_addhi(seq_t seq, void *x);
extern void *seq_remlo(seq_t seq);
extern void *seq_remhi(seq_t seq);

#endif
