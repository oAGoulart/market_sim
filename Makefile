# Augusto Goulart (1901560080) 29/03/2023 09:19:00
CC = gcc
CFLAGS = -g
MD = mkdir
RM = rm

OUT_DIR = bin/
SRC_DIR = src/

PROJECT = market_sim
SOURCES =  supermarket.c list.c cashier.c queue.c customer.c main.c
SOURCES_ABS = $(addprefix $(SRC_DIR),$(SOURCES))
DEBUG_FLAGS = $(CFLAGS)
RELEASE_FLAGS = $(CFLAGS) -DNDEBUG -O3

.PHONY: all clean debug release

all: debug release

clean:
	$(RM) -f -d -r $(OUT_DIR)

release: debug
	$(MD) -p $(OUT_DIR)release/
	$(CC) $(RELEASE_FLAGS) $(SOURCES_ABS) -o $(OUT_DIR)release/$(PROJECT)

debug:
	$(CC) $(DEBUG_FLAGS) $(SOURCES_ABS) -o $(OUT_DIR)$(PROJECT)
