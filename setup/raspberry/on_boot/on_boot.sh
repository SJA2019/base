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

	set -x
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

	echo "echo $0 -- date=`date`, user=`whoami`"
	zenity "[`date`] Greetings `whoami`. Have a nice session!!"

#changeToOrigDir
#exit 0
} > /tmp/on_boot_output.txt 2> /tmp/on_boot_output_errors.txt
exit 0
