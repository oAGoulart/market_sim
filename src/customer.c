/* Augusto Goulart (1901560080) 29/03/2023 09:19:00 */
#include "../include/customer.h"

struct customer_s {
  size_t id_;
  customer_type_t type_;
  customer_status_t status_;
  size_t waiting_time_;
  size_t served_time_;
};

void customer_create(customer_t** self, size_t id, customer_type_t type)
{
  if (self == NULL) __throw("customer_create: customer is NULL");
  *self = (customer_t*) malloc(sizeof(customer_t));
  (*self)->id_ = id;
  (*self)->type_ = type;
  (*self)->status_ = customer_status_waiting;
  (*self)->waiting_time_ = 0;
  (*self)->served_time_ = __rand(1, 10);
}

void customer_destroy(customer_t** self)
{
  if (self == NULL) __throw("customer_destroy: customer is NULL");
  if (*self == NULL) __throw("customer_destroy: *customer is NULL");
  free(*self);
  *self = NULL;
}

void customer_update(customer_t* self, boolean_t served)
{
  if (self == NULL) __throw("customer_update: customer is NULL");
  if (self->status_ == customer_status_waiting) {
    self->waiting_time_++;
    if (self->type_ == customer_type_cut && (__rand(0, 99) < 5))
      self->status_ = customer_status_left;
    if (self->waiting_time_ >= 6 && (__rand(0, 99) < 5))
      self->status_ = customer_status_left;
    else if (served) self->status_ = customer_status_served;
  }
  if (self->status_ == customer_status_served && served) {
    self->served_time_--;
    if (self->served_time_ == 0) self->status_ = customer_status_left;
  }
}

customer_status_t customer_status(customer_t* self)
{
  if (self == NULL) __throw("customer_status: customer is NULL");
  return self->status_;
}

customer_type_t customer_type(customer_t* self)
{
  if (self == NULL) __throw("customer_type: customer is NULL");
  return self->type_;
}

size_t customer_id(customer_t* self)
{
  if (self == NULL) __throw("customer_id: customer is NULL");
  return self->id_;
}
