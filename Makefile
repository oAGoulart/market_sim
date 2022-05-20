# 15:47:00 05/05/2022, Augusto Goulart 1901560080

CC = gcc
CFLAGS = -g
MD = mkdir
RM = rm

OUT_DIR = bin/
SRC_DIR = src/

PROJECT = market_sim
SOURCES = main.c supermarket.c cashier.c queue.c customer.c
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
	$(MD) -p $(OUT_DIR)
	$(CC) $(DEBUG_FLAGS) $(SOURCES_ABS) -o $(OUT_DIR)$(PROJECT)
