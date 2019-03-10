#configs.

. ./onBootScript_install.sh

. ./raspi_params.sh


sudo chmod ugo+rwx $CONFIG_VAR_RASPI_PATH_250
sudo chmod ugo+rwx $CONFIG_VAR_RASPI_PATH_150
sudo chmod ugo+rwx $CONFIG_VAR_RASPI_PATH_100

## setup nfs server
#
if [ ! -f /etc/exports ]
then
	touch /etc/exports
fi
echo "$CONFIG_VAR_RASPI_PATH_250 *(rw,sync)" >> /etc/exports
echo "$CONFIG_VAR_RASPI_PATH_150 *(rw,sync)" >> /etc/exports
echo "$CONFIG_VAR_RASPI_PATH_100 *(rw,sync)" >> /etc/exports
sudo exportfs
sudo update-rc.d rpcbind enable
sudo service rpcbind restart
sudo exportfs


## setup smb server.
#

#if [ ! -f /etc/init.d/smb.conf ]
#then
#	touch /etc/init.d/smb.conf
#fi
#echo "[250gb]" > /etc/init.d/smb.conf
#echo "comment = Pi shared folder" >> /etc/init.d/smb.conf
#echo "path = $CONFIG_VAR_RASPI_PATH_250/Media" >> /etc/init.d/smb.conf
#echo "browseable = yes" >> /etc/init.d/smb.conf
#echo "writeable = Yes" >> /etc/init.d/smb.conf
#echo "only guest = no" >> /etc/init.d/smb.conf
#echo "create mask = 0777" >> /etc/init.d/smb.conf
#echo "directory mask = 0777" >> /etc/init.d/smb.conf
#echo "public = yes" >> /etc/init.d/smb.conf
#echo "guest ok = yes" >> /etc/init.d/smb.conf
#echo "force user = pi" >> /etc/init.d/smb.conf
#echo "valid users = pi">> /etc/init.d/smb.conf

#echo -e "raspberry\nraspberry" | sudo smbpasswd -s -a pi
sudo /etc/init.d/samba restart


# manual installs.
#
echo "set correct display resolution: 720x480 16:9 60hz seems to work."
echo "enable sftp,ssh,vnc & static-ip"
echo "enable video-camera-codecs-option, 256mb-memory-split-option, expanded-file-system in raspi-config,"
echo "launching raspiconfig in 10s..."
sleep 10
sudo raspi-config 
