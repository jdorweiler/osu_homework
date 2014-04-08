#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 2
# calculate the nth prime
# use: python problem4.py 2000

import sys
import math 

def main(n):
	n = int(n)

	if(n < 1):
		print "invalid input"
		return

	keepGoing = True
	count = 0
	prime = 0
	num = 2

	while(keepGoing):
		if(isPrime(num)):
			count += 1
		if(count == n):
			keepGoing = False
		num += 1
	
	print "Prime number #",n, "is: ", num-1

def isPrime(n):
	if(n == 2):
		return True
	if(n == 3):
		return True

	for i in range(2, n):
		if(n%i == 0):
			return False
	return True

if __name__ == '__main__':
	main(sys.argv[1])