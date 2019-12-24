#!/bin/sh


echo "echo $0 ++"

sudo apt update
sudo apt upgrade

#installs

echo "installing transmission...."
sudo apt-get install transmission

echo "installing vnc client..."
sudo apt-get install realvnc-vnc-server realvnc-vnc-viewer

echo "installing vlc..."
sudo apt-get install vlc

echo "installing and configuring git.."
sudo apt-get install git
cd ~
mkdir source
sudo git clone https://github.com/SJA2019/base.git ./source/
cd -

sudo apt-get install vim


echo "waiting for 10s."

sleep 10

echo "echo $0 --"
