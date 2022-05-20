/*
  21:30:00 30/04/2022, Augusto Goulart 1901560080
*/
#include "../include/customer.h"

struct customer_s {
  size_t _serial_number; /* unique customer identifier */
  size_t _service_time; /* time this customer will take once at the cashier */
  size_t _waiting_time; /* time this customer has been waiting in the queue */
  size_t _cashier; /* cashier id this customer is at */
  customer_state_t _state; /* current state of this customer */
  customer_t* _next;
};

void customer_ctor(customer_t** self,
  const size_t serial_number,
  const size_t service_time,
  const size_t cashier
)
{
  if (self != NULL) {
    *self = (customer_t*)malloc(sizeof(customer_t));
    if (*self != NULL) {
      (*self)->_serial_number = serial_number;
      (*self)->_service_time = service_time;
      (*self)->_waiting_time = 0;
      (*self)->_cashier = cashier;
      (*self)->_state = CUSTOMER_NONE;
      (*self)->_next = NULL;
      return;
    }
  }
  __throw("Could not construct object of type customer_t");
}

void customer_dtor(customer_t** self)
{
	if (self != NULL) {
		if (*self != NULL) {
			free(*self);
			*self = NULL;
      return;
		}
	}
  __throw("Object 'self' is not a valid customer_t");
}

void customer_update(customer_t* self, const customer_state_t state)
{
  self->_state = state;
  switch (self->_state)
  {
  case CUSTOMER_WAITING:
    {
      self->_waiting_time++;
      break;
    }
  case CUSTOMER_SERVICE:
    {
      if (self->_service_time <= 1) {
        self->_state = CUSTOMER_FINISHED;
        self->_service_time = 0;
        break;
      }
      self->_service_time--;
      break;
    }
  default:
    {
      break;
    }
  }
}

size_t customer_get_serial_number(customer_t* self)
{
  return self->_serial_number;
}

size_t customer_get_service_time(customer_t* self)
{
  return self->_service_time;
}

size_t customer_get_waiting_time(customer_t* self)
{
  return self->_waiting_time;
}

size_t customer_get_cashier_id(customer_t* self)
{
  return self->_cashier;
}

customer_state_t customer_get_state(customer_t* self)
{
  return self->_state;
}

customer_t* customer_get_next(customer_t* self)
{
  return self->_next;
}

void customer_set_next(customer_t* self, customer_t* next)
{
  self->_next = next;
}
