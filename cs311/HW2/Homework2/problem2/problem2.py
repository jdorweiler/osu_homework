#Author: Jason Dorweiler
#Email: dorweilj@onid.oregonstate.edu
#Class: cs311-400
#Assignment: Homework 2
# create directories
# use: python problem2.py --term spring2014 --c cs311-400
import subprocess
import shlex
import os
import sys
import getopt

def main(argv):
	optlist, args = getopt.getopt(argv, 't:c:',['class=', 'term='])
	term = ''
	class_name = ''


	# get the term and class names
	for e in optlist:
		if(e[0] == '-t' or e[0] == '--term'):
			term = e[1]
		if(e[0] == '-c' or e[0] == '--class'):
			class_name = e[1]

	workingDir = term+'/'+class_name+'/' 

	# make the class and term dirs
	processCommand(shlex.split('mkdir ' + term))
	processCommand(shlex.split('mkdir '+workingDir))

	# array to hold directory names
	dirs = ['assignments', 'examples', 'exams', 'lecture_notes', 'submissions']

	# make the directories
	for d in dirs:
		processCommand(shlex.split('mkdir ' + workingDir+ d))

	# make symbolic links
	link1 = "/usr/local/classes/eecs/"+term+'/'+class_name+'/src/README'
	link2 = "/usr/local/classes/eecs/"+term+'/'+class_name+'/src'
	
	processCommand(shlex.split("ln -s "+link1+" README"))
	processCommand(shlex.split("ln -s "+link2+" src_class"))	

def checkSTDOUT(arg):
	if(arg):
		print "Warning ", arg.rstrip()

def processCommand(cmd):
	try:
		p = subprocess.Popen(cmd, stderr=subprocess.STDOUT, stdout=subprocess.PIPE)
		checkSTDOUT(p.stdout.read())
	except OSError as e:
		pass

if __name__ == '__main__':
	main(sys.argv[1:])