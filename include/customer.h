/* Augusto Goulart (1901560080) 29/03/2023 09:19:00 */
#ifndef CUSTOMER_H
#define CUSTOMER_H 1

#include <stdlib.h>
#include "base.h"

typedef struct customer_s customer_t;

typedef enum customer_type_e {
  customer_type_regular,
  customer_type_preferential,
  customer_type_cut
} customer_type_t;

typedef enum customer_status_e {
  customer_status_waiting,
  customer_status_served,
  customer_status_left
} customer_status_t;

void customer_create(customer_t** self, size_t id, customer_type_t type);
void customer_destroy(customer_t** self);
void customer_update(customer_t* self, boolean_t served);
customer_status_t customer_status(customer_t* self);
customer_type_t customer_type(customer_t* self);
size_t customer_id(customer_t* self);


#endif /* CUSTOMER_H */
