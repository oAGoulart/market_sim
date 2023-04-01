/* Augusto Goulart (1901560080) 29/03/2023 09:19:00 */
#include "../include/supermarket.h"

struct supermarket_s {
  size_t cashier_count_;
  size_t preferential_count_;
  size_t customer_count_;
  list_t* cashier_list_;
};

void supermarket_create(supermarket_t** self, size_t cashier_count, size_t preferential_count)
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (cashier_count == 0) __throw(__exception_invalid_argument); 
  *self = (supermarket_t*)malloc(sizeof(supermarket_t));
  (*self)->cashier_count_ = cashier_count;
  (*self)->preferential_count_ = preferential_count;
  (*self)->customer_count_ = 0;
  list_create(&(*self)->cashier_list_);
  size_t i = 0;
  for (; i < cashier_count; i++) {
    boolean_t preferential = (i < preferential_count) ? TRUE : FALSE;
    cashier_t* cashier;
    cashier_create(&cashier, i, preferential);
    list_emplace_back((*self)->cashier_list_, cashier);
  }
}

void supermarket_destroy(supermarket_t** self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (*self == NULL) __throw(__exception_null_pointer);
  size_t i = 0;
  for (; i < (*self)->cashier_count_; i++) {
    cashier_t* cashier = (cashier_t*)list_remove((*self)->cashier_list_, 0);
    cashier_destroy(&cashier);
  }
  list_destroy(&(*self)->cashier_list_);
  free(*self);
  *self = NULL;
}

void supermarket_update(supermarket_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  customer_t* customer = NULL;
  if (__rand(0, 99) < 80) {
    customer_type_t type = customer_type_regular;
    if (__rand(0, 99) < 5) type = customer_type_cut;
    if (__rand(0, 99) < 15) type = customer_type_preferential;
    customer_create(&customer, self->customer_count_, type);
    self->customer_count_++;
  }
  cashier_t* free_cashier = NULL;
  size_t i = 0;
  for (; i < self->cashier_count_; i++) {
    cashier_t* cashier = (cashier_t*)list_at(self->cashier_list_, i);
    cashier_update(cashier);
    if (free_cashier == NULL) free_cashier = cashier;
    else if (cashier_size(cashier) < cashier_size(free_cashier))
      free_cashier = cashier;
  }
  if (customer != NULL && free_cashier != NULL)
    cashier_add_customer(free_cashier, customer);
}

size_t supermarket_customer_count(supermarket_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  return self->customer_count_;
}

size_t supermarket_cashier_count(supermarket_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  return self->cashier_count_;
}
