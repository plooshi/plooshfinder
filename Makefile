INCLDIRS = -I./include
SRC = $(wildcard src/*.c) $(wildcard src/formats/*.c) $(wildcard src/asm/*.c)
OBJDIR = obj
OBJS = $(patsubst src/%,$(OBJDIR)/%,$(SRC:.c=.o))

CFLAGS ?= -O2
CC := clang
AR ?= ar
RANLIB ?= ranlib

all: dirs $(OBJS) libplooshfinder.a

dirs:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/formats
	@mkdir -p $(OBJDIR)/asm

clean:
	@rm -rf libplooshfinder.a obj

libplooshfinder.a: $(OBJS)
	$(AR) rcs libplooshfinder.a $(OBJS)
	$(RANLIB) libplooshfinder.a


$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLDIRS) -c -o $@ $<