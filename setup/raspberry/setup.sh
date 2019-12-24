#!/bin/sh


cd configuration
sudo sh ./configure_params.sh
cd -

cd software_install
sudo sh ./install_programs.sh
cd -

cd on_boot
sudo sh ./install_boot_script.sh
cd -
