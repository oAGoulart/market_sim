/*
  17:49:00 01/05/2022, Augusto Goulart 1901560080
*/
#ifndef CASHIER_H
#define CASHIER_H 1

#include <stdlib.h>
#include "base.h"
#include "queue.h"

typedef struct cashier_s cashier_t;

void cashier_ctor(cashier_t** self, const size_t id);
void cashier_dtor(cashier_t** self);

size_t cashier_get_id(cashier_t* self);
queue_t* cashier_get_queue(cashier_t* self);
cashier_t* cashier_get_next(cashier_t* self);
cashier_t* cashier_get_previous(cashier_t* self);
void cashier_set_next(cashier_t* self, cashier_t* next);
void cashier_set_previous(cashier_t* self, cashier_t* previous);

#endif /* CASHIER_H */
