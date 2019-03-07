#configs.

## get inside the scripts dir and execute on-boot script.
#
sudo echo ""
sudo echo "#performing custom config on boot.."
sudo cp -f ./on_boot.sh /etc/init.d/
sudo cp -f ./raspi_params.sh /etc/init.d/
sudo chmod ugo+rwx  /etc/init.d/on_boot.sh
sudo chmod ugo+rwx  /etc/init.d/raspi_params.sh


. ./raspi_params.sh

## setup smb server.
#
sudo chmod ugo+rwx $CONFIG_VAR_RASPI_PATH_250

if [ ! -f /etc/init.d/smb.conf]
then
	touch /etc/init.d/smb.confsmb.conf
fi
echo "[share]" >> /etc/init.d/smb.conf
echo "Comment = Pi shared folder" >> /etc/init.d/smb.conf
echo "Path = $CONFIG_VAR_RASPI_PATH_250" >> /etc/init.d/smb.conf
echo "Browseable = yes" >> /etc/init.d/smb.conf
echo "Writeable = Yes" >> /etc/init.d/smb.conf
echo "only guest = no" >> /etc/init.d/smb.conf
echo "create mask = 0777" >> /etc/init.d/smb.conf
echo "directory mask = 0777" >> /etc/init.d/smb.conf
echo "Public = yes" >> /etc/init.d/smb.conf
echo "Guest ok = yes" >> /etc/init.d/smb.conf

#sudo smbpasswd -a pi
sudo /etc/init.d/samba restart


# manual installs.
#
echo "set correct display resolution: 720x480 16:9 60hz seems to work."
echo "enable sftp,ssh,vnc & static-ip"
echo "enable video-camera-codecs-option, 256mb-memory-split-option, expanded-file-system in raspi-config,"
echo "launching raspiconfig in 10s..."
sleep 10
sudo raspi-config 
