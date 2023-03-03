#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef enum {
    FIFO_RES_SUCCESS,
    FIFO_RES_EMPTY,
    FIFO_RES_FULL
} FIFO_Result;

#define ARRAY_LENGTH(A) (sizeof(A) / sizeof((A)[0]))

#define DECLARE_FIFO(NAME, ITEM_TYPE, NUM_ITEMS)                       \
    typedef struct {                                                   \
        size_t read_idx;                                               \
        size_t write_idx;                                              \
        size_t n_elem;                                                 \
        ITEM_TYPE items[NUM_ITEMS];                                    \
    } NAME;                                                            \
    void NAME##_init(NAME *p_fifo);                                    \
    FIFO_Result NAME##_put(NAME *p_fifo, const ITEM_TYPE *p_new_item); \
    FIFO_Result NAME##_get(NAME *p_fifo, ITEM_TYPE *p_item_out);       \
    bool NAME##_is_empty(NAME *p_fifo);

#define DEFINE_FIFO(NAME, ITEM_TYPE)                                    \
    void NAME##_init(NAME *p_fifo) {                                    \
        p_fifo->read_idx = 0;                                           \
        p_fifo->write_idx = 0;                                          \
        p_fifo->n_elem = 0;                                             \
    }                                                                   \
                                                                        \
    FIFO_Result NAME##_put(NAME *p_fifo, const ITEM_TYPE *p_new_item) { \
        size_t const capacity = ARRAY_LENGTH(p_fifo->items);            \
        if (p_fifo->n_elem == capacity) {                               \
            return FIFO_RES_FULL;                                       \
        }                                                               \
                                                                        \
        p_fifo->items[p_fifo->write_idx] = *p_new_item;                 \
                                                                        \
        if (++p_fifo->write_idx == capacity) {                          \
            p_fifo->write_idx = 0;                                      \
        }                                                               \
        ++p_fifo->n_elem;                                               \
        return FIFO_RES_SUCCESS;                                        \
    }                                                                   \
                                                                        \
    FIFO_Result NAME##_get(NAME *p_fifo, ITEM_TYPE *p_item_out) {       \
        size_t const capacity = ARRAY_LENGTH(p_fifo->items);            \
                                                                        \
        if (p_fifo->n_elem == 0) {                                      \
            return FIFO_RES_EMPTY;                                      \
        }                                                               \
                                                                        \
        *p_item_out = p_fifo->items[p_fifo->read_idx];                  \
                                                                        \
        if (++p_fifo->read_idx == capacity) {                           \
            p_fifo->read_idx = 0;                                       \
        }                                                               \
        --p_fifo->n_elem;                                               \
        return FIFO_RES_SUCCESS;                                        \
    }                                                                   \
                                                                        \
    bool NAME##_is_empty(NAME *p_fifo) {                                \
        return p_fifo->n_elem == 0;                                     \
    }

#endif