#/bin/sh

#referance: https://raspberrypi.stackexchange.com/questions/5427/can-a-raspberry-pi-be-used-to-create-a-backup-of-itself

echo "$0 ++"

RASP_BACKUP_PATH=$1 
RASP_BACKUP_STATUS_FILE="backup.sucess"
RASP_RESTORE_PATH=$2

if [ $# -lt 2 ]
then
echo "error: invalid arguments."
exit 1
fi

if [ ! -d $RASP_BACKUP_PATH ]
then
echo "error: $RASP_BACKUP_PATH is not available."
fi

if [ ! -d $RASP_RESTORE_PATH ]
then
echo "error: $RASP_RESTORE_PATH is not available."
fi


if [ ! -f $RASP_BACKUP_PATH$/RASP_BACKUP_STATUS_FILE ]
then
echo "error: $RASP_BACKUP_STATUS_FILE is not available." 
exit 1
fi

RESULT1 = rsync -av --delete-during  $RASP_BACKUP_PATH/ $RASP_RESTORE_PATH/

if [ $RESULT1 -ne 0 ]
then
echo "error: rsync failed trying to restore."
exit 1
fi

RESULT1 = rm $RASP_BACKUP_PATH/$RASP_BACKUP_STATUS_FILE

if [ $RESULT1 -ne 0 ]
then
echo "error: cleanup failed to delete the status file in restored location : please check."
exit 1
fi


echo "$0 --"
