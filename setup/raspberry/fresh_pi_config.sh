#configs.

## get inside the scripts dir and execute on-boot script.
#
sudo echo ""
sudo echo "#performing custom config on boot.."
sudo cp -f ./on_boot.sh /etc/init.d/
sudo cp -f ./raspi_params.sh /etc/init.d/
sudo chmod ugo+rwx  /etc/init.d/on_boot.sh
sudo chmod ugo+rwx  /etc/init.d/raspi_params.sh



# manual installs.
#
echo "set correct display resolution: 720x480 16:9 60hz seems to work."
echo "enable sftp,ssh,vnc & static-ip"
echo "enable video-camera-codecs-option, 256mb-memory-split-option, expanded-file-system in raspi-config,"
echo "launching raspiconfig in 10s..."
sleep 10
sudo raspi-config 
