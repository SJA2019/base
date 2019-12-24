#!/bin/sh
## get inside the scripts dir and execute on-boot script.
#

echo "echo $0 ++"

CURR_DIR=`pwd`
sudo echo ""
sudo echo "#performing custom config on boot.."
sudo cp -f ./on_boot.sh /etc/init.d/
sudo update-rc.d on_boot.sh defaults
sudo sed -i "s|#changeToTargetDir|cd $CURR_DIR|g" /etc/init.d/on_boot.sh
sudo sed -i "s/#changeToOrigDir/cd -/g" /etc/init.d/on_boot.sh
sudo chmod ugo+rwx -R ./

echo "echo $0 --"
