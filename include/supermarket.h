/*
  18:28:00 01/05/2022, Augusto Goulart 1901560080
*/
#ifndef SUPERMARKET_H
#define SUPERMARKET_H 1

#include <stdlib.h>
#include <limits.h>
#include "base.h"
#include "cashier.h"

typedef struct supermarket_s supermarket_t;

void supermarket_ctor(supermarket_t** self);
void supermarket_dtor(supermarket_t** self);

cashier_t* supermarket_at(supermarket_t* self, const size_t at);
boolean_t supermarket_emplace(supermarket_t* self, const size_t id, const size_t at);
void supermarket_erase(supermarket_t* self, const size_t at);
void supermarket_iterate(supermarket_t* self, void (*iterator)(cashier_t* cashier, const size_t at));
boolean_t supermarket_empty(supermarket_t* self);
void supermarket_update_time_counter(supermarket_t* self);
void supermarket_update_customer_counter(supermarket_t* self);
size_t supermarket_size(supermarket_t* self);
size_t supermarket_time_counter(supermarket_t* self);
size_t supermarket_customer_counter(supermarket_t* self);
cashier_t* supermarket_get_available_cashier(supermarket_t* self);

#endif /* SUPERMARKET_H */
