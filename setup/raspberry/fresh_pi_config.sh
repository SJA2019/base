#configs.

. ./onBootScript_install.sh

. ./raspi_params.sh

## setup smb server.
#
sudo chmod ugo+rwx $CONFIG_VAR_RASPI_PATH_250

if [ ! -f /etc/init.d/smb.conf ]
then
	touch /etc/init.d/smb.conf
fi
echo "[pi]" > /etc/init.d/smb.conf
echo "Comment = Pi shared folder" >> /etc/init.d/smb.conf
echo "Path = $CONFIG_VAR_RASPI_PATH_250/Media" >> /etc/init.d/smb.conf
echo "Browseable = yes" >> /etc/init.d/smb.conf
echo "Writeable = Yes" >> /etc/init.d/smb.conf
echo "only guest = no" >> /etc/init.d/smb.conf
echo "create mask = 0777" >> /etc/init.d/smb.conf
echo "directory mask = 0777" >> /etc/init.d/smb.conf
echo "Public = yes" >> /etc/init.d/smb.conf
echo "Guest ok = yes" >> /etc/init.d/smb.conf
echo "force user = pi" >> /etc/init.d/smb.conf

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
