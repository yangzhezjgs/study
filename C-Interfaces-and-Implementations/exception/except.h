#ifndef EXCEPT_H__
#define EXCEPT_H__
#include <setjmp.h>

typedef struct except_t {
    const char *reason;
} except_t;

typedef struct except_frame {
    struct except_frame *prev;
    jmp_buf env;
    const char *file;
    int line;
    const except_t *exception;
} except_frame;

typedef enum except_status {
    EXCEPT_ENTERED = 0,
    EXCEPT_RAISED,
    EXCEPT_HANDLED,
    EXCEPT_FINALIZED
} except_status;

extern except_frame *except_stack;
extern const except_t assert_failed;

extern void except_raise(const except_t *e, const char *file, int line);

#define TRY do { \
    volatile except_status except_flag; \
    excpet_frame except_frame; \
    except_frame.prev = except_stack; \
    except_stack = &except_frame; \
    except_flag = setjump(&except_frame.env); \
    if (except_flag == EXCEPT_ENTERED) {

#define EXCEPT(e) \
        if (except_flag == EXCEPT_ENTERED) \
            except_stack = except_stack->prev; \
    } else if (except_frame.exception == &(e)) { \
            except_flag = EXCEPT_HANDLED;

#define ELSE \
        if (except_flag == EXCEPT_ENTERED) \
            except_stack = except_stack->prev; \
    } else { \
        except_flag = EXCEPT_HANDLED;

#define FINALLY \
        if (except_flag == EXCEPT_ENTERED) \
            except_stack = except_stack->prev; \
    } { \
        if (except_flag == EXCEPT_ENTERED) \
            except_flag = EXCEPT_FINALIZED;

#define END_TRY \
        if (except_flag == EXCEPT_ENTERED) \
            except_stack = except_stack->prev; \
    } \
    if (except_flag == EXCEPT_RAIESED) \
        RERAISE; \
} while (0)

#define RERAISE \
    except_raise(except_frame.exception, except_frame.file, except_frame.line)

#define RAISE(e) except_raise(&(e), __FILE__, __LINE__)

#define RETURN switch(except_stack = except_stack->prev, 0) default: return

#endif


