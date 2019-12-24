#!/bin/sh

#configs.
echo "echo $0 ++"

# copy config.txt to /boot/
#
cp ./config.txt /boot/config.txt

# enable ssh
#
touch /boot/ssh

# start vnc server
#
sudo systemctl enable vncserver-x11-serviced.service

echo "echo $0 --"
