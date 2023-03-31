/* Augusto Goulart (1901560080) 29/03/2023 09:19:00 */
#include "../include/queue.h"

void queue_create(queue_t** self)
{
  list_create(self);
}

void queue_destroy(queue_t** self)
{
  list_destroy(self);
}

void queue_enqueue(queue_t* self, void* data)
{
  list_emplace_back(self, data);
}

void* queue_dequeue(queue_t* self)
{
  return list_remove_front(self);
}

void* queue_peek(queue_t* self)
{
  return list_at(self, 0);
}

void queue_clear(queue_t* self)
{
  list_clear(self);
}

size_t queue_size(queue_t* self)
{
  return list_size(self);
}

boolean_t queue_empty(queue_t* self)
{
  return list_empty(self);
}
