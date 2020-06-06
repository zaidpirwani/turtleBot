# turtleBot
ROS TurtleBot DIY Omni Wheel base

Kinect and Omni Wheel Based Raspberry Pi ROS Rover

GOAL: To implement TeleOperation, Mapping and Navigation

Download Ubuntu 16.04 from https://ubuntu-mate.community/t/old-releases-of-ubuntu-mate-torrent-downloads-md5-checksums/19426, under :pie: Old Raspberry Pi releases
Install on 16GB SD Card via Win32DiskImager

Created an empty file SSH in the SD Card to enable SSH Access

Created a file wpa_supplicant.conf in the SD Card, as per https://www.raspberrypi.org/documentation/configuration/wireless/headless.md with the following info

ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=PK

network={
 ssid="<Name of your wireless LAN>"
 psk="<Password for your wireless LAN>"
}

WIFI CONNECTION DID NOT WORK
after several tries, realized, this method is for RASAPBIAN - and might not work on Ubuntu Mate

Need to use a Linux system to write wpa_supplicant to the correct location, or need to use an HDMI Display/Keyboard/Mouse to set it up manually using the GUI

Ended up powering the Pi from battery/Regulator, and connecting to the Internet Router via Wired Cable to get Connectivity to setup WiFi and SSH etc

got the IP Address from the Router Admin DHCP Page - 192.168.18.35

conecting via PuTTY, got error connection refused

still doesnt work - SSH is disabled on Ubuntu Mate - now need to connect monitor/keyboard and mouse

have no keyboard, only wired mouse, will need to somehow enable on-screen keyboard and work that way with HDMI connected

Seems too slow, asked for Language (English), Region (Karachi), user info (name: turtle, username: turtle, pc name: bot, password: 1)

seems to be downloading and installing updates

clicked on the BLUE ACCESSIBILITY ICON, enabled On-Screen Keyboard and also added password for WiFi

Now need to enable SSH, waiting for update/background process to complete
-- background process was stuck, clicked on close, rebooted
-- resolution was stuck at 640x480 - very difficult to open terminal and also use on-screen keyboard
-- rebooted again, resolution auto fixed

Open Terminal
Open On-Screen Keyboard Accessibility Menu

sudo raspi-config
SSH, Enabled from interfacing Options
Restart

Now connected via PuTTY, finally, after getting IP from the router

open raspi-config
sudo raspi-config
	set boot to CLI from Boot Options
	Expand File System - from Advanced Options
	Memory Split, set to 16MB to GPU
	Ran the Update option
sudo reboot

sudo apt update
sudo apt upgrade
(might take a long time for first time, approx download size is 400MB+)

