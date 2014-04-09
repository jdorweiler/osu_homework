import subprocess
import shlex
import os
import sys
import getopt

def main(argv):
	command = 'who'

	optlist, args = getopt.getopt(argv, 'b,d,l,p,r,T,t,u')

	if(optlist):
		command = command + " " + optlist[0][0]

	ls = subprocess.Popen(shlex.split(command), stdout=subprocess.PIPE)
	ls_out = ls.stdout.readlines()

	for line in ls_out:
		print line,

if __name__ == '__main__':
	main(sys.argv[1:])
