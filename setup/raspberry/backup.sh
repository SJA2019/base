#!/bin/sh

if [ $# -lt 1 ]
then
exit 1
fi

#"referance: https://www.raspberrypi.org/documentation/linux/filesystem/backup.md"
#"backup: sudo dd bs=4M if=/dev/sdb | gzip > raspbian.img.gz"
#"restore: gunzip --stdout raspbian.img.gz | sudo dd bs=4M of=/dev/sdb"

echo "running the script:****\n"
cat $1
echo "****\n"

echo "BackingUp:****"
sudo dd bs=4M if=/dev/sdb | gzip > $1/raspbian.img.gz
echo "DoneBackingUp:****"




