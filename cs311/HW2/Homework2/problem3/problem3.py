#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 2
# get contents from url
# use: python problem3.py google.com testfile.html

import urllib2
import sys

def main(argv):
	url = argv[0]
	
	if(len(argv) == 2):
		newFile = argv[1]
	else:
		print "No file name was entered"
		sys.exit(2)

	response = urllib2.urlopen('http://'+url)
	html = response.read()
	
	myFile = open(newFile, 'w')
	myFile.write(html)
	myFile.close()

if __name__ == '__main__':
	main(sys.argv[1:])