#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 1
# calculate primes
# use: python primes.py 100
#     shows all primes below 100

import sys
import math 

def main(size):
	size = int(size)
	if(size < 2):
		print "not a valid input"
		return

	results = []
	count = 0
	# array from 1 to size
	primes = range(1,size)
	primes[0] = 0
	
	for k in range(2,int(math.sqrt(size))+1):
		if(primes[k-1] != 0):
			for m in range(k**2, size, k):
				primes[m-1] = 0
	
	for j  in range(len(primes)):
		if(primes[j] != 0):
			results.append(primes[j])
			count += 1

	print "The number of primes less than ",size, ": ", count
	print "The primes are: "
	print results

if __name__ == '__main__':
	main(sys.argv[1])