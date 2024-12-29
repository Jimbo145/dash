#!/bin/bash

nmcli con add type wifi ifname wlan0 con-name SAABnet autoconnect yes ssid SAABnet
nmcli con modify SAABnet 802-11-wireless.mode ap 802-11-wireless.band a ipv4.method shared
nmcli con modify SAABnet wifi-sec.key-mgmt wpa-psk
nmcli con modify SAABnet wifi-sec.psk "1234567890"
nmcli con up SAABnet


systemctl disable lightdm
systemctl enable dash

sudo chmod g+rw /dev/tty0
sudo chmod g+rw /dev/tty7
sudo chmod 777 /home/pi/dash/firstrun.sh