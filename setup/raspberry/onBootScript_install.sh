#!/bin/sh
## get inside the scripts dir and execute on-boot script.
#
CURR_DIR=`pwd`
sudo echo ""
sudo echo "#performing custom config on boot.."
sudo cp -f ./on_boot.sh /etc/init.d/
sudo update-rc.d on_boot.sh defaults
sudo sed -i "s|#changeToTargetDir|cd $CURR_DIR|g" /etc/init.d/on_boot.sh
sudo sed -i "s/#changeToOrigDir/cd -/g" /etc/init.d/on_boot.sh
sudo chmod ugo+rwx -R ./

#sudo cp -f ./raspi_params.sh /etc/init.d/
#sudo cp -rf ./backup /etc/init.d/ 
#sudo chmod ugo+rwx  /etc/init.d/on_boot.sh
#sudo chmod ugo+rwx  /etc/init.d/raspi_params.sh
#sudo chmod ugo+rwx -R  /etc/init.d/backup
