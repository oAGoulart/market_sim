/*
  18:29:00 01/05/2022, Augusto Goulart 1901560080
*/
#include "../include/supermarket.h"

struct supermarket_s {
  cashier_t* _head;
  cashier_t* _tail;
  size_t _size;
  size_t _time_counter; /* time since market opened */
  size_t _customer_counter; /* total amount of customers processed */
};

void supermarket_ctor(supermarket_t** self)
{
  if (self != NULL) {
    *self = (supermarket_t*)malloc(sizeof(supermarket_t));
    if (*self != NULL) {
      (*self)->_head = NULL;
      (*self)->_tail = NULL;
      (*self)->_size = 0;
      (*self)->_time_counter = 0;
      (*self)->_customer_counter = 0;
      return;
    }
  }
  __throw("Could not construct object of type supermarket_t");
}

void supermarket_dtor(supermarket_t** self)
{
  if (self != NULL) {
    if ((*self) != NULL) {
      cashier_t* current = (*self)->_head;
      while (current != NULL) {
        cashier_t* next = cashier_get_next(current);
        cashier_dtor(&current);
        current = next;
      }
      free(*self);
      return;
    }
  }
  __throw("Object 'self' is not a valid supermarket_t");
}

/* returns cashier at specific index if it exists, NULL otherwise */
cashier_t* supermarket_at(supermarket_t* self, const size_t at)
{
  if (at >= self->_size)
    return NULL;

  size_t counter = 0;
  cashier_t* aux = self->_head;
  while (aux != NULL) {
    if (counter == at)
      break;

    aux = cashier_get_next(aux);
    counter++;
  }
  return aux;
}

boolean_t supermarket_insert(supermarket_t* self, cashier_t* cashier, const size_t at)
{
  boolean_t success = FALSE;
  if (at > self->_size)
    return success;

  if (at == 0) {
    if (self->_head != NULL) {
      cashier_set_next(cashier, self->_head);
      cashier_set_previous(self->_head, cashier);
    }
    self->_head = cashier;
    success = TRUE;
  }
  if (at == self->_size) {
    if (self->_tail != NULL) {
      cashier_set_previous(cashier, self->_tail);
      cashier_set_next(self->_tail, cashier);
    }
    self->_tail = cashier;
    success = TRUE;
  }
  else {
    cashier_t* aux = supermarket_at(self, at);
    if (aux != NULL) {
      /* nodes above head always have previous */
      cashier_t* tmp = cashier_get_previous(aux);
      cashier_set_next(tmp, cashier);
      cashier_set_previous(cashier, tmp);
      cashier_set_previous(aux, cashier);
      cashier_set_next(cashier, aux);
      success = TRUE;
    }
  }
  if (success)
    self->_size++;
  return success;
}

/* creates cashier at index */
boolean_t supermarket_emplace(supermarket_t* self, const size_t id, const size_t at)
{
  cashier_t* cashier = NULL;
  cashier_ctor(&cashier, id);

  if (supermarket_insert(self, cashier, at))
    return TRUE;

  cashier_dtor(&cashier);
  return FALSE;
}

cashier_t* supermarket_remove_front(supermarket_t* self)
{
  cashier_t* aux = self->_head;
  if (aux != NULL) {
    cashier_t* tmp = cashier_get_next(self->_head);
    if (tmp != NULL)
      cashier_set_previous(tmp, NULL);

    self->_size--;
    self->_head = tmp;
    if (self->_head == self->_tail)
      self->_tail = NULL;
  }
  return aux;
}

cashier_t* supermarket_remove_back(supermarket_t* self)
{
  cashier_t* aux = self->_tail;
  if (aux != NULL) {
    cashier_t* tmp = cashier_get_previous(self->_tail);
    if (tmp != NULL)
      cashier_set_next(tmp, NULL);

    self->_size--;
    self->_tail = tmp;
    if (self->_head == self->_tail)
      self->_tail = NULL;
  }
  return aux;
}

cashier_t* supermarket_remove(supermarket_t* self, const size_t at)
{
  if (at >= self->_size)
    return NULL;
  if (at == 0)
    return supermarket_remove_front(self);
  else if (at == (self->_size - 1))
    return supermarket_remove_back(self);

  cashier_t* aux = supermarket_at(self, at);
  if (aux != NULL) {
    /* nodes between head and tail always have next and previous */
    cashier_t* previous = cashier_get_previous(aux);
    cashier_t* next = cashier_get_next(aux);
    cashier_set_next(previous, next);
    cashier_set_previous(next, previous);
    self->_size--;
  }
  return aux;
}

/* destroys cashier at index */
void supermarket_erase(supermarket_t* self, const size_t at)
{
  cashier_t* cashier = supermarket_remove(self, at);
  cashier_dtor(&cashier);
}

void supermarket_iterate(supermarket_t* self, void (*iterator)(cashier_t* cashier, const size_t at))
{
  if (self->_size > 0) {
    size_t counter = 0;
    cashier_t* aux = self->_head;
    do
    {
      cashier_t* next = cashier_get_next(aux);
      iterator(aux, counter);
      aux = next;
      counter++;
    } while (aux != NULL);
  }
}

void supermarket_update_time_counter(supermarket_t* self)
{
  self->_time_counter++;
}

void supermarket_update_customer_counter(supermarket_t* self)
{
  self->_customer_counter++;
}

boolean_t supermarket_empty(supermarket_t* self)
{
  return (self->_size == 0);
}

size_t supermarket_size(supermarket_t* self)
{
  return self->_size;
}

size_t supermarket_time_counter(supermarket_t* self)
{
  return self->_time_counter;
}

size_t supermarket_customer_counter(supermarket_t* self)
{
  return self->_customer_counter;
}

cashier_t* supermarket_get_available_cashier(supermarket_t* self)
{
  size_t size = ULONG_MAX;
  cashier_t* c = NULL;
  cashier_t* aux = self->_head;
  while (aux != NULL) {
    queue_t* tmp = cashier_get_queue(aux);
    if (queue_size(tmp) < size) {
      size = queue_size(tmp);
      c = aux;
    }
    aux = cashier_get_next(aux);
  }
  return c;
}
