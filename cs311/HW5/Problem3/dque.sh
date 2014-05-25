#!/bin/bash -x
# remove message queues
IDS=`ipcs -q | grep $LOGNAME| awk '{print $2}'`
for i in $IDS ; do ipcrm -q $i; done