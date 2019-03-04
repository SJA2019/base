#!/bin/sh

source raspi_params.sh
echo "echo $0 ++"

sleep 30
#perform backup.
echo "starting backup script."
pushd backup
if [ ! -d $CONFIG_VAR_RASPI_BACKUP_PATH ] 
then
./backup.sh $CONFIG_VAR_RASPI_BACKUP_PATH/$CONFIG_VAR_RASPI_BACKUP_DIR_NAME
fi
popd
echo "done backup script."


sleep 2m
vlc $CONFIG_VAR_RASPI_MUSIC_DIR

echo "echo $0 --"
