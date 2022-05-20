/*
  20:08:00 02/05/2022, Augusto Goulart 1901560080
*/
#include <ctype.h>
#include <time.h>
#include "../include/supermarket.h"

void draw_customer(customer_t* customer, const size_t at)
{
  /* base x and y */
  const size_t bx = 12 + (4 * at);
  const size_t by = 18 + (22 * customer_get_cashier_id(customer));

  /* if true -> magenta; else -> yellow; */
  size_t color = (at == 0) ? 35 : 33;
  __csave();
  __cmove(bx + 1, by); printf(__cs("%lu;%lu", "DD"), color, color + 10);
  __cmove(bx, by + 3); printf(__cs("%lu", "n: %lu"), color, customer_get_serial_number(customer));
  __cmove(bx + 1, by + 3); printf(__cs("%lu", "t: %lu"), color, customer_get_service_time(customer));
  __cmove(bx + 2, by + 3); printf(__cs("%lu", "w: %lu"), color, customer_get_waiting_time(customer));
  __crestore();

  if (at == 0)
    customer_update(customer, CUSTOMER_SERVICE);
  else
    customer_update(customer, CUSTOMER_WAITING);
}

void draw_cashier(cashier_t* cashier, const size_t at)
{
  /* base x and y */
  const size_t bx = 10;
  const size_t by = 8 + (22 * at);

  __csave();
  __cmove(bx, by); printf("id: " __c(34, "%lu"), cashier_get_id(cashier));
  __cmove(bx + 2, by); printf(__c(37;47, "DDDDDDDD"));
  __cmove(bx + 3, by); printf(__c(37;47, "DDDDDDDD"));
  __cmove(bx + 4, by + 4); printf(__c(37;47, "DDDD"));
  __cmove(bx + 5, by + 4); printf(__c(37;47, "DDDD"));
  __cmove(bx + 6, by + 4); printf(__c(37;47, "DDDD"));
  __cmove(bx + 7, by + 4); printf(__c(37;47, "DDDD"));
  __crestore();

  /* dequeue first customer if service time is zero */
  queue_t* queue = cashier_get_queue(cashier);
  customer_t* customer = queue_peek(queue);
  if (customer != NULL) {
    if (customer_get_state(customer) == CUSTOMER_FINISHED)
      queue_dequeue(queue);
  }

  /* draw this cashier's customers */
  queue_iterate(queue, &draw_customer);
}

void draw_info(supermarket_t* sm)
{
  __csave();
  __cmove(4lu, 5lu); printf("Number of cashiers available:");
  __cmove(4lu, 57lu); printf(__c(33, "%lu"), supermarket_size(sm));
  __cmove(5lu, 5lu); printf("Total number of customers serviced since opening:");
  __cmove(5lu, 57lu); printf(__c(33, "%lu"), supermarket_customer_counter(sm));
  __cmove(6lu, 5lu); printf("Amount of minutes since opening:");
  __cmove(6lu, 57lu); printf(__c(33, "%lu"), supermarket_time_counter(sm));
  __crestore();
}

void draw_exitmsg()
{
  __csave();
  __cmove(2lu, 1lu);
  /* 30;47 -> black foreground and white background */
  printf("Type " __c(30;47, " Q ") " to quit or " __c(30;47, " ENTER ") " to resume");
  __crestore();
}

int main()
{
  supermarket_t* sm = NULL;
  supermarket_ctor(&sm);
  srand(time(NULL));

  size_t i = 0;
  for (; i < 5; i++)
    supermarket_emplace(sm, i, i);

  char flag = '.';
  do
  {
    if (__rand(1, 100) <= 60) {
      /* c -> cashier with least amount of customers */
      cashier_t* c = supermarket_get_available_cashier(sm);
      if (c != NULL) {
        queue_t* q = cashier_get_queue(c);
        queue_enqueue(q, supermarket_customer_counter(sm), __rand(1, 15), cashier_get_id(c));
        supermarket_update_customer_counter(sm);
      }
    }
    /* flush terminal and move cursor to home */
    __tflush();
    __cmove(1lu, 1lu);

    /* main flow: draw and update simulation */
    draw_info(sm);
    supermarket_iterate(sm, &draw_cashier);
    draw_exitmsg();

    /* wait user input and verify if it is time to quit */
    flag = (char)toupper(getchar());
    if (flag == 'Q')
      break;

    /* simulation continues: increase time by one minute */
    supermarket_update_time_counter(sm);
  } while (TRUE);
  __tflush();

  supermarket_dtor(&sm);
  return 0;
}
