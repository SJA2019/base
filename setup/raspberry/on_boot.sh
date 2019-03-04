#!/bin/sh

. ./raspi_params.sh
echo "echo $0 ++"


sleep 5
#update script dir.
sudo echo "cd ~/source"
sudo echo "git pull"
sudo echo "cd -"

sleep 1m
#perform backup.
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
vlc $CONFIG_VAR_RASPI_MUSIC_DIR

echo "echo $0 --"
