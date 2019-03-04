#!/bin/sh

#referance: https://raspberrypi.stackexchange.com/questions/5427/can-a-raspberry-pi-be-used-to-create-a-backup-of-itself

echo "$0 ++"

RASP_BACKUP_PATH=$1 
BACKUP_DIR_1=backup1
BACKUP_DIR_2=backup2
RASP_BACKUP_STATUS_FILE="backup.sucess"


if [ $# -lt 1 ]
then
echo "error: invalid arguments."
exit 1
fi

if [ ! -d $RASP_BACKUP_PATH ]
then
echo "error: $RASP_BACKUP_PATH is not a directory."
fi

#backup1
#
if [ ! -f $RASP_BACKUP_PATH/$BACKUP_DIR_1/$RASP_BACKUP_STATUS_FILE ]
then
echo "alert: $RASP_BACKUP_PATH/$BACKUP_DIR_1/$RASP_BACKUP_STATUS_FILE is not present: looks like a first time backup."
fi

rm $RASP_BACKUP_PATH/$BACKUP_DIR_1/$RASP_BACKUP_STATUS_FILE
if [ $? -ne 0 ]
then
echo "alert: unable to remove $RASP_BACKUP_PATH/$BACKUP_DIR_1/$RASP_BACKUP_STATUS_FILE"
fi

rsync -aHv --delete --exclude-from=./rsyncExclude.txt / $RASP_BACKUP_PATH/$BACKUP_DIR_1/
if [ $? -ne 0 ]
then
echo "error: rsync failed to backup to $BACKUP_DIR_1."
exit 1
fi

touch $RASP_BACKUP_PATH/$BACKUP_DIR_1/$RASP_BACKUP_STATUS_FILE
if [ $? -ne 0 ]
then
echo "alert: unable to create $RASP_BACKUP_PATH/$BACKUP_DIR_1/$RASP_BACKUP_STATUS_FILE"
fi



#backup2
#
if [ ! -f $RASP_BACKUP_PATH/$BACKUP_DIR_2/$RASP_BACKUP_STATUS_FILE ]
then
echo "alert: $RASP_BACKUP_PATH/$BACKUP_DIR_2/$RASP_BACKUP_STATUS_FILE is not present: looks like a first time backup."
fi 

rm $RASP_BACKUP_PATH/$BACKUP_DIR_2/$RASP_BACKUP_STATUS_FILE
if [ $? -ne 0 ]
then
echo "alert: unable to remove $RASP_BACKUP_PATH/$BACKUP_DIR_2/$RASP_BACKUP_STATUS_FILE"
fi

rsync -aHv --delete --exclude-from=./rsyncExclude.txt / $RASP_BACKUP_PATH/$BACKUP_DIR_2/
if [ $? -ne 0 ]
then
echo "error: rsync failed to backup to $BACKUP_DIR_2."
exit 1
fi

touch $RASP_BACKUP_PATH/$BACKUP_DIR_2/$RASP_BACKUP_STATUS_FILE
if [ $? -ne 0 ]
then
echo "alert: unable to create $RASP_BACKUP_PATH/$BACKUP_DIR_2/$RASP_BACKUP_STATUS_FILE"
fi

echo "$0 --"
