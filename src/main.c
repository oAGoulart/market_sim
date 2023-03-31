/* Augusto Goulart (1901560080) 29/03/2023 17:22:00 */
#include <ctype.h>
#include <string.h>
#include "../include/base.h"
#include "../include/supermarket.h"

void draw_info(supermarket_t* sm)
{
  __csave();
  __cmove(4lu, 5lu); printf("total number of stations:");
  __cmove(4lu, 57lu); printf(__c(33, "%lu"), supermarket_cashier_count(sm));
  __cmove(5lu, 5lu); printf("Total number of customers serviced since opening:");
  __cmove(5lu, 57lu); printf(__c(33, "%lu"), supermarket_customer_count(sm));
  __crestore();
}

void draw_help()
{
  __csave();
  __cmove(2lu, 1lu);
  /* 30;47 -> black foreground and white background */
  printf("Type " __c(30;47, " Q ") " to quit or " __c(30;47, " ENTER ") " to resume");
  __crestore();
}

int main()
{
  supermarket_t* sm;
  supermarket_create(&sm, 5, 1);
  srand(time(NULL));

  char k = '.';
  do
  {
    __tflush();
    __cmove(1lu, 1lu);

    draw_info(sm);
    supermarket_update(sm);
    draw_help();

    k = (char)toupper(getchar());
    if (k == 'Q') break;
  } while (TRUE);
  __tflush();

  supermarket_destroy(&sm);
  return 0;
}
