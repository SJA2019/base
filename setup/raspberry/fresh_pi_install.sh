#!/bin/sh


sudo apt update
sudo apt upgrade

#installs

echo "installing transmission...."
sudo apt-get install transmission

echo "installing vnc..."
sudo apt-get install realvnc-vnc-server realvnc-vnc-viewer

echo "installing vlc..."
sudo apt-get install vlc

echo "installing and configuring git.."
sudo apt-get install git
cd ~
mkdir source
sudo git clone https://github.com/SJA2019/base.git ./source/
cd -

#kodi
echo "please install latest kodi from site."
sudo apt-get install kodi

sudo apt-get install vim

#sudo apt-get install samba samba-common-bin

sudo apt-get install nfs-common nfs-server -y

echo "waiting for 10s."
sleep 10
