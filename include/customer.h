/*
  19:40:00 30/04/2022, Augusto Goulart 1901560080
*/
#ifndef CUSTOMER_H
#define CUSTOMER_H 1

#include <stdlib.h>
#include "base.h"

typedef enum customer_state_e {
  CUSTOMER_WAITING,
  CUSTOMER_SERVICE,
  CUSTOMER_FINISHED,
  CUSTOMER_NONE
} customer_state_t;

typedef struct customer_s customer_t;

void customer_ctor(customer_t** self,
  const size_t serial_number,
  const size_t service_time,
  const size_t cashier
);
void customer_dtor(customer_t** self);

void customer_update(customer_t* self, const customer_state_t state);
size_t customer_get_serial_number(customer_t* self);
size_t customer_get_service_time(customer_t* self);
size_t customer_get_waiting_time(customer_t* self);
size_t customer_get_cashier_id(customer_t* self);
customer_state_t customer_get_state(customer_t* self);
customer_t* customer_get_next(customer_t* self);
void customer_set_next(customer_t* self, customer_t* next);

#endif /* CUSTOMER_H */
