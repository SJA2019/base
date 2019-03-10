#!/bin/sh
### BEGIN INIT INFO
# Provides:          on_boot.sh
# Required-Start:    $local_fs $network $named $time $syslog
# Required-Stop:     $local_fs $network $named $time $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Description:       on_boot_script
### END INIT INFO

#changeToTargetDir
{
	set -x
	. ./raspi_params.sh
	echo "echo $0 ++"



	sleep 5
	#update script dir.
	sudo echo "cd ~/source"
	sudo echo "git pull"
	sudo echo "cd -"


	sudo ifconfig eth0 192.168.2.100 netmask 255.255.255.0


	sleep 1m
	perform backup.
	echo "starting backup script."
	cd backup
	if [ -d $CONFIG_VAR_RASPI_BACKUP_PATH ] 
	then
	sudo bash backup.sh $CONFIG_VAR_RASPI_BACKUP_PATH/$CONFIG_VAR_RASPI_BACKUP_DIR_NAME
	fi
	cd -
	echo "done backup script."


	sleep 2m
	#start music.
	echo raspberry | sudo -S -u pi /usr/bin/cvlc $CONFIG_VAR_RASPI_MUSIC_DIR
	#kodi
	echo "echo $0 --"
#changeToOrigDir
#exit 0
} > /root/on_boot_output.txt 2> /root/on_boot_output_errors.txt
exit 0
