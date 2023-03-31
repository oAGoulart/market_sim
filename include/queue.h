/* Augusto Goulart (1901560080) 29/03/2023 09:19:00 */
#ifndef QUEUE_H
#define QUEUE_H 1

#include <stdlib.h>
#include "base.h"
#include "list.h"

typedef struct list_s queue_t;

void queue_create(queue_t** self);
void queue_destroy(queue_t** self);
void queue_enqueue(queue_t* self, void* data);
void* queue_dequeue(queue_t* self);
void* queue_peek(queue_t* self);
void queue_clear(queue_t* self);
size_t queue_size(queue_t* self);
boolean_t queue_empty(queue_t* self);

#endif /* QUEUE_H */
