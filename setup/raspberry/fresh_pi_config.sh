#configs.

## get inside the scripts dir and execute on-boot script.
#
sudo echo "" >> ~/.bashrc
sudo echo "performing custom config on boot...">>~/.bashrc

sudo "cd `pwd`" >> ~/.bashrc
sudo echo "sh on_boot.sh > ~/ob_boot_log.txt" >> ~/.bashrc
sudo "cd -" >> ~/.bashrc

# manual installs.
#
echo "set correct display resolution: 720x680 16:9 60hz seems to work."
echo "enable sftp,ssh,vnc"
echo "launching raspiconfig in 10s..."
sleep 10
raspiconfig 
