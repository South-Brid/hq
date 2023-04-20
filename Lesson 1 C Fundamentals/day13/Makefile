#!/bin/bash 
EXC=a.out
OBJS=
OBJS+=
OBJS+=
CC=
$(EXC):$(OBJS)
	$(CC) -o $@ $^
.c:.o
	$(CC) -c $<
clean:
	rm *.c $(EXC)
rebulid:$(EXC) clean

