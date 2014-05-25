#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 6

CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall 
PROGS=primeMProc primePThread


all: $(PROGS)

primePThread: primePThread.o clean
	@$(CC) $(CFLAGS) -o primePThread primePThread.o -lrt -lm -pthread


primePThread.o: primePThread.c clean
	@echo --- Building primePThread ---
	@$(CC) $(CFLAGS) -c primePThread.c

primeMProc: primeMProc.o clean
	@$(CC) $(CFLAGS) -o primeMProc primeMProc.o -lrt -lm 


primeMProc.o: primeMProc.c clean
	@echo --- Building primeMProc ---
	@$(CC) $(CFLAGS) -c primeMProc.c

maxProc:
	@echo --- 1 process, UINT_MAX primes ---
	./primeMProc -c 1 -m 4294967295 -q -t > proc.txt

maxThread:
	@echo --- 1 thread, UINT_MAX primes ---
	./primePThread -c 1 -m 4294967295 -q -t > thread.txt

maxProc10:
	@echo --- 10 process, UINT_MAX primes ---
	./primeMProc -c 10 -m 4294967295 -q -t > proc.txt

maxThread10:
	@echo --- 10 threads, UINT_MAX primes ---
	./primePThread -c 10 -m 4294967295 -q -t > thread.txt

time1:
	@echo --- Running time tests ---
	@echo --- 1 process, 500M primes ---
	time ./primeMProc -c 1 -m 500000000 -q
	@echo --- 1 process, 1B primes ---
	time ./primeMProc -c 1 -m 1000000000 -q
	@echo --- 1 process, 1.5B primes ---
	time ./primeMProc -c 1 -m 1500000000 -q
	@echo --- 1 process, 2B primes ---
	time ./primeMProc -c 1 -m 2000000000 -q
	@echo --- 1 process, 3B primes ---
	time ./primeMProc -c 1 -m 3000000000 -q
	@echo --- 1 process, UINT_MAX primes ---
	time ./primeMProc -c 1 -m 4294967295 -q

time2:
	@echo --- Running time tests ---
	@echo --- 2 process, 500M primes ---
	time ./primeMProc -c 2 -m 500000000 -q
	@echo --- 2 process, 1B primes ---
	time ./primeMProc -c 2 -m 1000000000 -q
	@echo --- 2 process, 1.5B primes ---
	time ./primeMProc -c 2 -m 1500000000 -q
	@echo --- 2 process, 2B primes ---
	time ./primeMProc -c 2 -m 2000000000 -q
	@echo --- 2 process, 3B primes ---
	time ./primeMProc -c 2 -m 3000000000 -q
	@echo --- 2 process, UINT_MAX primes ---
	time ./primeMProc -c 2 -m 4294967295 -q

time5: 
	@echo --- Running time tests ---
	@echo --- 5 process, 500M primes ---
	time ./primeMProc -c 5 -m 500000000 -q
	@echo --- 5 process, 1B primes ---
	time ./primeMProc -c 5 -m 1000000000 -q
	@echo --- 5 process, 1.5B primes ---
	time ./primeMProc -c 5 -m 1500000000 -q
	@echo --- 5 process, 2B primes ---
	time ./primeMProc -c 5 -m 2000000000 -q
	@echo --- 5 process, 3B primes ---
	time ./primeMProc -c 5 -m 3000000000 -q
	@echo --- 5 process, UINT_MAX primes ---
	time ./primeMProc -c 5 -m 4294967295 -q

time10:
	@echo --- Running time tests ---
	@echo --- 10 process, 500M primes ---
	time ./primeMProc -c 10 -m 500000000 -q
	@echo --- 10 process, 1B primes ---
	time ./primeMProc -c 10 -m 1000000000 -q
	@echo --- 10 process, 1.5B primes ---
	time ./primeMProc -c 10 -m 1500000000 -q
	@echo --- 10 process, 2B primes ---
	time ./primeMProc -c 10 -m 2000000000 -q
	@echo --- 10 process, 3B primes ---
	time ./primeMProc -c 10 -m 3000000000 -q
	@echo --- 10 process, UINT_MAX primes ---
	time ./primeMProc -c 10 -m 4294967295 -q

timeT1:
	@echo --- Running time tests ---
	@echo --- 1 process, 500M primes ---
	time ./primePThread -c 1 -m 500000000 -q
	@echo --- 1 process, 1B primes ---
	time ./primePThread -c 1 -m 1000000000 -q
	@echo --- 1 process, 1.5B primes ---
	time ./primePThread -c 1 -m 1500000000 -q
	@echo --- 1 process, 2B primes ---
	time ./primePThread -c 1 -m 2000000000 -q
	@echo --- 1 process, 3B primes ---
	time ./primePThread -c 1 -m 3000000000 -q
	@echo --- 1 process, UINT_MAX primes ---
	time ./primePThread -c 1 -m 4294967295 -q

timeT2:
	@echo --- Running time tests ---
	@echo --- 2 process, 500M primes ---
	time ./primePThread -c 2 -m 500000000 -q
	@echo --- 2 process, 1B primes ---
	time ./primePThread -c 2 -m 1000000000 -q
	@echo --- 2 process, 1.5B primes ---
	time ./primePThread -c 2 -m 1500000000 -q
	@echo --- 2 process, 2B primes ---
	time ./primePThread -c 2 -m 2000000000 -q
	@echo --- 2 process, 3B primes ---
	time ./primePThread -c 2 -m 3000000000 -q
	@echo --- 2 process, UINT_MAX primes ---
	time ./primePThread -c 2 -m 4294967295 -q

timeT5:
	@echo --- Running time tests ---
	@echo --- 5 process, 500M primes ---
	time ./primePThread -c 5 -m 500000000 -q
	@echo --- 5 process, 1B primes ---
	time ./primePThread -c 5 -m 1000000000 -q
	@echo --- 5 process, 1.5B primes ---
	time ./primePThread -c 5 -m 1500000000 -q
	@echo --- 5 process, 2B primes ---
	time ./primePThread -c 5 -m 2000000000 -q
	@echo --- 5 process, 3B primes ---
	time ./primePThread -c 5 -m 3000000000 -q
	@echo --- 5 process, UINT_MAX primes ---
	time ./primePThread -c 5 -m 4294967295 -q

timeT10:
	@echo --- Running time tests ---
	@echo --- 10 process, 500M primes ---
	time ./primePThread -c 10 -m 500000000 -q
	@echo --- 10 process, 1B primes ---
	time ./primePThread -c 10 -m 1000000000 -q
	@echo --- 10 process, 1.5B primes ---
	time ./primePThread -c 10 -m 1500000000 -q
	@echo --- 10 process, 2B primes ---
	time ./primePThread -c 10 -m 2000000000 -q
	@echo --- 10 process, 3B primes ---
	time ./primePThread -c 10 -m 3000000000 -q
	@echo --- 10 process, UINT_MAX primes ---
	time ./primePThread -c 10 -m 4294967295 -q

test: time1 time2 time5 time10

testT: timeT1 timeT2 timeT5 timeT10

validate: 
	@echo --- Validating against known primes ---
	@echo --- Testing PThreads ---
	./primePThread -c 1 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primePThread -c 2 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primePThread -c 5 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primePThread -c 10 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primePThread -c 15 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primePThread -c 20 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primePThread -c 25 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primePThread -c 30 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	@echo --- Testing MProc ---
	./primeMProc -c 1 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primeMProc -c 2 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primeMProc -c 5 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primeMProc -c 10 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primeMProc -c 15 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primeMProc -c 20 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primeMProc -c 25 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	./primeMProc -c 30 -m 18409205 -q -t > out.txt
	diff out.txt primeStandard.txt
	@echo --- Running both programs 1 thread proc up to UMAX_INT and comparing output ---
	make maxProc
	make maxThread
	diff proc.txt thread.txt
	@echo --- Running both programs 10 thread proc  up to UMAX_INT and comparing output ---
	make maxProc10
	make maxThread10
	diff proc.txt thread.txt
	 
clean:
	@echo --- Removing output exe and object files
	@rm -f $(PROGS) thread.txt proc.txt *out* *.o *~ *# 

