PROJECT=picoserver
DATE=$(shell date +"%m-%d-%Y-%H-%M-%S")
PROJECT_DATED=${PROJECT}.${DATE}
PROJECT_TAR=${PROJECT_DATED}.tar
INSTALL_DIR=/home/nsa/bin
OPTIONS= -g -Wall
LDFLAGS=
SRC_DIR=src
OBJS_DIR=objs
DEPS_DIR=deps
CC = gcc
CPP = cpp

SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o)
dep = $(OBJS:.o=.d)


all: bin/server
	mv $(SRC_DIR)/*.o $(OBJS_DIR)
	mv $(SRC_DIR)/*.d $(DEPS_DIR)

bin/server: $(OBJS)
	$(CC) $(OPTIONS) -o $@ $^ $(LDFLAGS)

-include $(dep)

%.d: %.c
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

install: bin/server
	install bin/server $(INSTALL_DIR)

.PHONY: clean
clean:
	@rm -rf *.o
	@rm -rf objs/*.o
	@rm -rf *.d
	@rm -rf deps/*.d
	@rm -rf bin/*

.PHONY: cleandep
cleandep:
	rm -f $(dep)

.PHONY: tar
tar:
	tar --exclude='tar' --exclude='bin' --exclude='.git' -cf tar/${PROJECT_TAR} .
	gzip tar/${PROJECT_TAR}
	gpg -c tar/${PROJECT_TAR}.gz

cleantar:
	rm tar/*
