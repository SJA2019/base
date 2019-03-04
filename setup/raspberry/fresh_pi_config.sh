#configs.

## get inside the scripts dir and execute on-boot script.
#
sudo echo "" >> ~/.bashrc
sudo echo "performing custom config on boot...">>~/.bashrc

sudo echo "cd `pwd`" >> ~/.bashrc
sudo echo "sh on_boot.sh > ~/ob_boot_log.txt" >> ~/.bashrc
sudo echo "cd -" >> ~/.bashrc

# manual installs.
#
echo "set correct display resolution: 720x680 16:9 60hz seems to work."
echo "enable sftp,ssh,vnc & static-ip"
echo "enable video-camera-codecs-option, 256mb-memory-split-option, expanded-file-system in raspi-config,"
echo "launching raspiconfig in 10s..."
sleep 10
raspi-config 
