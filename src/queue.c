/*
  22:16:00 30/04/2022, Augusto Goulart 1901560080
*/
#include "../include/queue.h"

struct queue_s {
  customer_t* _front;
  customer_t* _back;
  size_t _size;
};

void queue_ctor(queue_t** self)
{
  if (self != NULL) {
    *self = (queue_t*)malloc(sizeof(queue_t));
    if (*self != NULL) {
      (*self)->_back = NULL;
      (*self)->_front = NULL;
      (*self)->_size = 0;
      return;
    }
  }
  __throw("Could not construct object of type queue_t");
}

void queue_dtor(queue_t** self)
{
  if (self != NULL) {
    if ((*self) != NULL) {
      customer_t* current = (*self)->_front;
      while (current != NULL) {
        customer_t* next = customer_get_next(current);
        customer_dtor(&current);
        current = next;
      }
      free(*self);
      return;
    }
  }
  __throw("Object 'self' is not a valid queue_t");
}

void queue_insert(queue_t* self, customer_t* customer)
{
  if (self->_front == NULL)
    self->_front = customer;
  else
    customer_set_next(self->_back, customer);

  self->_back = customer;
  self->_size++;
}

void queue_enqueue(queue_t* self,
  const size_t serial_number,
  const size_t service_time,
  const size_t cashier
)
{
  customer_t* customer = NULL;
  customer_ctor(&customer, serial_number, service_time, cashier);
  queue_insert(self, customer);
}

customer_t* queue_remove(queue_t* self)
{
  if (self->_front != NULL) {
    customer_t* tmp = self->_front;
    if (self->_back == tmp)
      self->_back = NULL;

    self->_front = customer_get_next(tmp);
    self->_size--;
    return tmp;
  }
  return NULL;
}

void queue_dequeue(queue_t* self)
{
  customer_t* customer = queue_remove(self);
  customer_dtor(&customer);
}

customer_t* queue_peek(queue_t* self)
{
  return self->_front;
}

void queue_iterate(queue_t* self, void (*iterator)(customer_t* customer, const size_t at))
{
  if (self->_size > 0) {
    size_t counter = 0;
    customer_t* aux = self->_front;
    do
    {
      customer_t* next = customer_get_next(aux);
      iterator(aux, counter);
      aux = next;
      counter++;
    } while (aux != NULL);
  }
}

boolean_t queue_empty(queue_t* self)
{
  return (self->_size == 0);
}

size_t queue_size(queue_t* self)
{
  return self->_size;
}
