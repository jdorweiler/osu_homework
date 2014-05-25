#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 5

CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement
PROGS=uniquify 


all: $(PROGS)

uniquify: uniquify.o clean
	@$(CC) $(CFLAGS) -o uniquify uniquify.o


uniquify.o: uniquify.c clean
	@echo --- Building uniquify ---
	@$(CC) $(CFLAGS) -c uniquify.c

time:
	@echo --- Generating standard file from uniquify.bash ---
	@ ./uniquify.bash < websters.txt > std.txt
	@echo --- running time test, 1 process, websters.txt ---
	@time ./uniquify -n 1 < websters.txt > out.txt
	@echo --- Testing Diff against standard file ---
	 

	@echo --- running time test, 2 process, websters.txt ---
	@time ./uniquify -n 2 < websters.txt > out.txt
	@echo --- Testing Diff against standard file ---
	 

	@echo --- running time test, 3 process, websters.txt ---
	@time ./uniquify -n 3 < websters.txt > out.txt
	@echo --- Testing Diff against standard file ---
	 

	@echo --- running time test, 4 process, websters.txt ---
	@time ./uniquify -n 4 < websters.txt > out.txt
	@echo --- Testing Diff against standard file ---
	 

	@echo --- running time test, 5 process, websters.txt ---
	@time ./uniquify -n 5 < websters.txt > out.txt
	@echo --- Testing Diff against standard file ---
	 

	@echo --- running time test, 10 process, websters.txt ---
	@time ./uniquify -n 10 < websters.txt > out.txt
	@echo --- Testing Diff against standard file ---
	 

	@echo --- running time test, 15 process, websters.txt ---
	@time ./uniquify -n 15 < websters.txt > out.txt
	@echo --- Testing Diff against standard file ---
	 

	@echo --- running time test, 20 process, websters.txt ---
	@time ./uniquify -n 20 < websters.txt > out.txt
	@echo --- Testing Diff against standard file ---

test:
	@echo Running tests .... 
	@echo --- Generating standard file from uniquify.bash ---
	@ ./uniquify.bash < websters.txt > std.txt
	@echo --- running time test, 5 process, websters.txt ---
	@time ./uniquify -n 5 < websters.txt > out.txt
	@echo --- Testing Diff against standard file ---
	diff out.txt std.txt

	
clean:
	@echo --- Removing output exe and object files
	@rm -f out.txt $(PROGS) *.o *~ *#

