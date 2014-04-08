#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 2
# largest product of an array
# use: python problem6.py
import sys
import numpy as np

def main():
	bigNum = []
	myFile = open('num.txt', 'r')
	for num in list(myFile.read()):
		bigNum.append(int(num))
	myFile.close()

	largestProd = 0
	window = 5

	for e in range(len(bigNum)-window+1):
		largestProd = np.maximum(largestProd, getProduct(bigNum, e, e+window))

	print "The largest product is: ", largestProd

def getProduct(array, low, high):
	total = 1
	for i in range(low, high):
		total *= array[i]
	return total

if __name__ == '__main__':
	main()