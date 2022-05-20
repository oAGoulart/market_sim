/*
  18:01:00 01/05/2022, Augusto Goulart 1901560080
*/
#include "../include/cashier.h"

struct cashier_s {
  size_t _id; /* unique cashier identifier */
  queue_t* _queue;
  cashier_t* _next;
  cashier_t* _previous;
};

void cashier_ctor(cashier_t** self, const size_t id)
{
  if (self != NULL) {
    queue_t* queue = NULL;
    queue_ctor(&queue);
    *self = (cashier_t*)malloc(sizeof(cashier_t));
    if (*self != NULL) {
      (*self)->_id = id;
      (*self)->_queue = queue;
      (*self)->_next = NULL;
      (*self)->_previous = NULL;
      return;
    }
    queue_dtor(&queue);
  }
  __throw("Could not construct object of type cashier_t");
}

void cashier_dtor(cashier_t** self)
{
  if (self != NULL) {
    if ((*self) != NULL) {
      queue_dtor(&(*self)->_queue);
      free(*self);
      return;
    }
  }
  __throw("Object 'self' is not a valid cashier_t");
}

size_t cashier_get_id(cashier_t* self)
{
  return self->_id;
}

queue_t* cashier_get_queue(cashier_t* self)
{
  return self->_queue;
}

cashier_t* cashier_get_next(cashier_t* self)
{
  return self->_next;
}

cashier_t* cashier_get_previous(cashier_t* self)
{
  return self->_previous;
}

void cashier_set_next(cashier_t* self, cashier_t* next)
{
  self->_next = next;
}

void cashier_set_previous(cashier_t* self, cashier_t* previous)
{
  self->_previous = previous;
}
