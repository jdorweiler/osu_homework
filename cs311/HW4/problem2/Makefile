#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 4
CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall
PROGS=sig_demo


all: $(PROGS)


sig_demo: sig_demo.o
	$(CC) $(CFLAGS) -o sig_demo sig_demo.o

sig_demo.o: sig_demo.c
	$(CC) $(CFLAGS) -c sig_demo.c

clean:
	rm -f $(PROGS) *.o *~ *#

