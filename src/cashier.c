/* Augusto Goulart (1901560080) 29/03/2023 09:19:00 */
#include "../include/cashier.h"

struct cashier_s {
  size_t id_;
  boolean_t is_preferential_;
  cashier_status_t status_;
  queue_t* customers_;
};

void cashier_create(cashier_t** self, size_t id, boolean_t preferential)
{
  if (self == NULL) __throw(__exception_null_pointer);
  *self = (cashier_t*) malloc(sizeof(cashier_t));
  (*self)->id_ = id;
  (*self)->is_preferential_ = preferential;
  (*self)->status_ = cashier_status_open;
  queue_create(&(*self)->customers_);
}

void cashier_destroy(cashier_t** self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (*self == NULL) __throw(__exception_null_pointer);
  queue_destroy(&(*self)->customers_);
  free(*self);
  *self = NULL;
}

void cashier_add_customer(cashier_t* self, customer_t* customer)
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (customer == NULL) __throw(__exception_null_pointer);
  queue_enqueue(self->customers_, customer);
}

customer_t* cashier_remove_customer(cashier_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  return (customer_t*)queue_dequeue(self->customers_);
}

customer_t* cashier_peek_customer(cashier_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (queue_empty(self->customers_)) return NULL;
  return (customer_t*)queue_peek(self->customers_);
}

void draw_customer(cashier_t* cashier, customer_t* customer, size_t at)
{
  if (cashier == NULL) __throw(__exception_null_pointer);
  if (customer == NULL) __throw(__exception_null_pointer);
  const size_t bx = 12 + (4 * at);
  const size_t by = 18 + (22 * cashier_id(cashier));

  /* if true -> magenta; else -> yellow; */
  size_t color = 35;
  if (customer_type(customer) == customer_type_preferential) color = 33;
  else if (customer_type(customer) == customer_type_cut) color = 36;
  __csave();
  __cmove(bx + 1, by); printf(__cs("%lu;%lu", "DD"), color, color + 10);
  __cmove(bx, by + 3); printf(__cs("%lu", "n: %lu"), color, customer_id(customer));
  __cmove(bx + 1, by + 3); printf(__cs("%lu", "t: %lu"), color, customer_served_time(customer));
  __cmove(bx + 2, by + 3); printf(__cs("%lu", "w: %lu"), color, customer_waiting_time(customer));
  __crestore();
}

void cashier_sort_customers_(cashier_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  list_t* customers;
  list_create(&customers);
  while (!queue_empty(self->customers_)) {
    customer_t* customer = (customer_t*)queue_dequeue(self->customers_);

    customer_update(customer, FALSE);
    if (customer_status(customer) == customer_status_left) 
      customer_destroy(&customer);

    if (customer != NULL) {
      customer_type_t type = customer_type(customer);
      if (self->is_preferential_ && type == customer_type_preferential)
        list_emplace_front(customers, customer);
      else if (type == customer_type_preferential && (__rand(0, 99) < 50))
        list_emplace_front(customers, customer);
      else if (type == customer_type_cut)
        list_emplace(customers, customer, list_size(customers) / 2);
      else
        list_emplace_back(customers, customer);
    } 
  }
  size_t n = 0;
  while (!list_empty(customers)) {
    customer_t* customer = (customer_t*)list_remove_front(customers);
    draw_customer(self, customer, n);
    queue_enqueue(self->customers_, customer);
    n++;
  }
  list_destroy(&customers);
}

void draw_cashier(cashier_t* cashier, size_t at)
{
  if (cashier == NULL) __throw(__exception_null_pointer);
  const size_t bx = 10;
  const size_t by = 8 + (22 * at);

  __csave();
  __cmove(bx, by); printf("id: " __c(34, "%lu"), cashier_id(cashier));
  __cmove(bx + 2, by); printf(__c(37;47, "DDDDDDDD"));
  __cmove(bx + 3, by); printf(__c(37;47, "DDDDDDDD"));
  __cmove(bx + 4, by + 4); printf(__c(37;47, "DDDD"));
  __cmove(bx + 5, by + 4); printf(__c(37;47, "DDDD"));
  __cmove(bx + 6, by + 4); printf(__c(37;47, "DDDD"));
  __cmove(bx + 7, by + 4); printf(__c(37;47, "DDDD"));
  __crestore();
}

void cashier_update(cashier_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  cashier_sort_customers_(self);
  draw_cashier(self, cashier_id(self));
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
  if (self == NULL) __throw(__exception_null_pointer);
  return queue_size(self->customers_);
}

boolean_t cashier_empty(cashier_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  return queue_empty(self->customers_);
}

size_t cashier_id(cashier_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  return self->id_;
}
