#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 5
CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement
PROGS=pipeline


all: $(PROGS)

pipeline: pipeline.o clean
	@$(CC) $(CFLAGS) -o pipeline pipeline.o

pipeline.o: pipeline.c clean
	@$(CC) $(CFLAGS) -c pipeline.c

test:
	@echo Running tests .... 
	@echo  --- Running bash --- 
	@echo
	@./pipeline.bash -f output2bash < words.txt > output1bash

	@echo --- Running pipeline ---
	@echo
	@./pipeline -f output2pipe < words.txt > output1pipe

	@echo --- Running Python pipeline extra credit ---
	@echo
	@python pipeline.py output2py < words.txt > output1py

	@echo --- Diff on bash and C  output 1 files ---
	@echo
	@diff output1bash output1pipe

	@echo --- Diff on bash and C  output 2  files ---
	@echo
	@diff output2bash output2pipe

	@echo --- Diff on bash and Python output 1 files ---
	@diff output1bash output1py
	@echo 

	@echo --- Diff on bash and Python output 2 files ---
	@echo
	@diff output2bash output2py

tests: test

clean:
	@echo --- Removing output exe and object files
	@rm -f output2bash output1bash output1pipe output2pipe $(PROGS) *.o *~ *#

