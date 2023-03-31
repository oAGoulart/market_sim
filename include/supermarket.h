/* Augusto Goulart (1901560080) 29/03/2023 09:19:00 */
#ifndef SUPERMARKET_H
#define SUPERMARKET_H 1

#include <stdlib.h>
#include <limits.h>
#include "base.h"
#include "list.h"
#include "cashier.h"

typedef struct supermarket_s supermarket_t;

void supermarket_create(supermarket_t** self, size_t cashier_count, size_t preferential_count);
void supermarket_destroy(supermarket_t** self);
void supermarket_update(supermarket_t* self);
size_t supermarket_customer_count(supermarket_t* self);
size_t supermarket_cashier_count(supermarket_t* self);

#endif /* SUPERMARKET_H */
