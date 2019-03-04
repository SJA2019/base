#configs.

## get inside the scripts dir and execute on-boot script.
#
sudo echo ""
sudo echo "#performing custom config on boot.."
#sudo echo "cd `pwd`" >> ~/.bashrc
#sudo echo "rm ~/Desktop/ob_boot_log.txt >> ~/Desktop/ob_boot_log.txt" >> ~/.bashrc
#sudo echo "sh on_boot.sh >> ~/Desktop/ob_boot_log.txt" >> ~/.bashrc
#sudo echo "cd -" >> ~/.bashrc
chmod ugo+x  



# manual installs.
#
echo "set correct display resolution: 720x480 16:9 60hz seems to work."
echo "enable sftp,ssh,vnc & static-ip"
echo "enable video-camera-codecs-option, 256mb-memory-split-option, expanded-file-system in raspi-config,"
echo "launching raspiconfig in 10s..."
sleep 10
sudo raspi-config 
