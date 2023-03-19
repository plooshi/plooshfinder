INCLDIRS = -I./include
SRC = $(wildcard src/*)
OBJDIR = obj
OBJS = $(patsubst src/%,$(OBJDIR)/%,$(SRC:.c=.o))

LDFLAGS ?= -fuse-ld=lld
CFLAGS ?= -O2
CC := clang
AR ?= ar
RANLIB ?= ranlib

all: dirs $(OBJS) libplooshfinder.a

dirs:
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf libplooshfinder.a obj

libplooshfinder.a: $(OBJS)
	$(AR) rcs libplooshfinder.a $(OBJS)
	$(RANLIB) libplooshfinder.a


$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLDIRS) -c -o $@ $<