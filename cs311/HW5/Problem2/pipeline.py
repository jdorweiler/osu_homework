#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 5

import os, sys
import subprocess
import pipes

def main(argv):

	process1 = subprocess.Popen(["rev"], stdout=subprocess.PIPE)
	process2 = subprocess.Popen(["sort"], stdin=process1.stdout, stdout=subprocess.PIPE)
	process3 = subprocess.Popen(["uniq", "-c"], stdin=process2.stdout, stdout=subprocess.PIPE)
	process4 = subprocess.Popen(["tee", argv[1]], stdin=process3.stdout, stdout=subprocess.PIPE)
	process5 = subprocess.Popen(["wc"], stdin=process3.stdout)
	stdout, stderr = process5.communicate()

if __name__ == '__main__':
	main(sys.argv)