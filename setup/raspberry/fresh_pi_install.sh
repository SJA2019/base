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
pushd ~
mkdir source
sudo git clone https://github.com/SJA2019/base.git ./source/
popd

#kodi
echo "please install latest kodi from site."
echo "perform steps: https://www.makeuseof.com/tag/install-kodi-raspbian-media-center"

echo "waiting for 10s."
sleep 10