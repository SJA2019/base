#!/bin/sh
### BEGIN INIT INFO
# Provides:          on_boot.sh
# Required-Start:    $local_fs $network $named $time $syslog
# Required-Stop:     $local_fs $network $named $time $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Description:       on_boot_script
### END INIT INFO

{

#changeToTargetDir

	#verbose mode : https://stackoverflow.com/questions/36273665/what-does-set-x-do
	set -x

	rm /tmp/on_boot_output*txt
	echo "echo $0 ++"

	sleep 5

	#set the ip address.
	#
	sudo ifconfig eth0 192.168.2.100 netmask 255.255.255.0

	#update script dir.
	#
	sudo echo "cd ~/source"
	sudo echo "git pull"
	sudo echo "cd -"

	zenity "[`date`] Greetings `whoami`. Have a nice session!!"
	echo "echo $0 -- date=`date`, user=`whoami`"

#changeToOrigDir
#exit 0
} > /tmp/on_boot_output.txt 2> /tmp/on_boot_output_errors.txt
echo "||| LastUpdated: `date +'%y%m%d%H%M'`" >> /tmp/on_boot_output.txt
echo "||| LastUpdated: `date +'%y%m%d%H%M'`" >> /tmp/on_boot_output_errors.txt
exit 0
