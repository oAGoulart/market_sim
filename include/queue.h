/*
  19:27:00 30/04/2022, Augusto Goulart 1901560080
*/
#ifndef QUEUE_H
#define QUEUE_H 1

#include <stdlib.h>
#include "base.h"
#include "customer.h"

typedef struct queue_s queue_t;

void queue_ctor(queue_t** self);
void queue_dtor(queue_t** self);

void queue_enqueue(queue_t* self,
  const size_t serial_number,
  const size_t service_time,
  const size_t cashier
);
void queue_dequeue(queue_t* self);
customer_t* queue_peek(queue_t* self);
void queue_iterate(queue_t* self, void (*iterator)(customer_t* customer, const size_t at));
boolean_t queue_empty(queue_t* self);
size_t queue_size(queue_t* self);

#endif /* QUEUE_H */
