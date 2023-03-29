/* Augusto Goulart (1901560080) 29/03/2023 09:19:00 */
#include "../include/cashier.h"

struct cashier_s {
  size_t id_;
  boolean_t is_preferential;
  cashier_status_t status_;
  queue_t* customers_;
};

void cashier_create(cashier_t** self, size_t id, boolean_t preferential)
{
  if (self == NULL) __throw("cashier_create: self is NULL");
  *self = (cashier_t*) malloc(sizeof(cashier_t));
  (*self)->id_ = id;
  (*self)->is_preferential = preferential;
  (*self)->status_ = cashier_status_open;
  queue_create(&(*self)->customers_);
}

void cashier_destroy(cashier_t** self)
{
  if (self == NULL) __throw("cashier_destroy: self is NULL");
  if (*self == NULL) __throw("cashier_destroy: *self is NULL");
  queue_destroy(&(*self)->customers_);
  free(*self);
  *self = NULL;
}

void cashier_add_customer(cashier_t* self, customer_t* customer)
{
  if (self == NULL) __throw("cashier_add_customer: self is NULL");
  if (customer == NULL) __throw("cashier_add_customer: customer is NULL");
  queue_enqueue(self->customers_, customer);
}

customer_t* cashier_remove_customer(cashier_t* self)
{
  if (self == NULL) __throw("cashier_remove_customer: self is NULL");
  return (customer_t*)queue_dequeue(self->customers_);
}

customer_t* cashier_peek_customer(cashier_t* self)
{
  if (self == NULL) __throw("cashier_peek_customer: self is NULL");
  return (customer_t*)queue_peek(self->customers_);
}

void cashier_iterate(cashier_t* self, void (*callback)(customer_t*))
{
  if (self == NULL) __throw("cashier_iterate: self is NULL");
  if (callback == NULL) __throw("cashier_iterate: callback is NULL");
  queue_iterate(self->customers_, (void (*)(void*))callback);
}

void cashier_sort_customers_(cashier_t* self)
{
  if (self == NULL) __throw("cashier_update_customers_: self is NULL");
  list_t* customers;
  list_create(&customers);
  while (!queue_empty(self->customers_)) {
    customer_t* customer = (customer_t*)queue_dequeue(self->customers_);

    customer_update(customer, FALSE);
    if (customer_status(customer) == customer_status_left) 
      customer_destroy(&customer);

    if (customer != NULL) {
      customer_type_t type = customer_type(customer);
      if (self->is_preferential && type == customer_type_preferential)
        list_emplace_front(customers, customer);
      else if (type == customer_type_preferential && (__rand(0, 99) < 50))
        list_emplace_front(customers, customer);
      else if (type == customer_type_cut)
        list_insert(customers, customer, list_size(customers) / 2);
      else
        list_emplace_back(customers, customer);
    } 
  }
  while (!list_empty(customers)) {
    customer_t* customer = (customer_t*)list_remove_front(customers);
    queue_enqueue(self->customers_, customer);
  }
  list_destroy(&customers);
}

void cashier_update(cashier_t* self)
{
  if (self == NULL) __throw("cashier_update: self is NULL");
  cashier_sort_customers_(self);
  if (self->status_ == cashier_status_open) {
    customer_t* customer = cashier_peek_customer(self);
    if (customer != NULL)
      customer_update(customer, TRUE);

    if (__rand(0, 99) < 10)
      self->status_ = cashier_status_issue;
    else if (__rand(0, 99) < 2)
      self->status_ = cashier_status_closed;
  }
  else if (self->status_ == cashier_status_closed) {
    if (!queue_empty(self->customers_))
      queue_clear(self->customers_);
    if (__rand(0, 99) < 50) self->status_ = cashier_status_open;
  }
  else if (self->status_ == cashier_status_issue && (__rand(0, 99) < 70))
    self->status_ = cashier_status_open;
}

size_t cashier_size(cashier_t* self)
{
  if (self == NULL) __throw("cashier_size: self is NULL");
  return queue_size(self->customers_);
}

boolean_t cashier_empty(cashier_t* self)
{
  if (self == NULL) __throw("cashier_empty: self is NULL");
  return queue_empty(self->customers_);
}

size_t cashier_id(cashier_t* self)
{
  if (self == NULL) __throw("cashier_id: self is NULL");
  return self->id_;
}
