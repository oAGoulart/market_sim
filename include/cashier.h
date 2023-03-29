/* Augusto Goulart (1901560080) 29/03/2023 09:19:00 */
#ifndef CASHIER_H
#define CASHIER_H 1

#include <stdlib.h>
#include "base.h"
#include "queue.h"
#include "customer.h"

typedef struct cashier_s cashier_t;

typedef enum cashier_status_e {
  cashier_status_open,
  cashier_status_closed,
  cashier_status_issue
} cashier_status_t;

void cashier_create(cashier_t** self, size_t id, boolean_t preferential);
void cashier_destroy(cashier_t** self);
void cashier_add_customer(cashier_t* self, customer_t* customer);
customer_t* cashier_remove_customer(cashier_t* self);
customer_t* cashier_peek_customer(cashier_t* self);
void cashier_iterate(cashier_t* self, void (*callback)(customer_t*));
void cashier_update(cashier_t* self);
size_t cashier_size(cashier_t* self);
boolean_t cashier_empty(cashier_t* self);
size_t cashier_id(cashier_t* self);

#endif /* CASHIER_H */
