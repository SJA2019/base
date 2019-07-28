#!/bin/sh


sudo sh ./configure_params.sh
sudo sh ./install_programs.sh
cd on_boot
sudo sh ./install_boot_script.sh
cd -
