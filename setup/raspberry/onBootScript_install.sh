#!/bin/sh
## get inside the scripts dir and execute on-boot script.
#
sudo echo ""
sudo echo "#performing custom config on boot.."
sudo cp -f ./on_boot.sh /etc/init.d/
sudo cp -f ./raspi_params.sh /etc/init.d/
sudo chmod ugo+rwx  /etc/init.d/on_boot.sh
sudo chmod ugo+rwx  /etc/init.d/raspi_params.sh

