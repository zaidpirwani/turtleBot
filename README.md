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

done update / installation - asked for configuration file replace, selected N - no, kept old one

sudo shutdown -h now
shutdown, removed HDMI / mouse and battery
back to running pi from 5V Wall Adapter

now will connect to SSH over WiFi - need WiFi IP - checking router - found IP, but it seems pi not connected to WiFi
now connected to Pi via LAN directly with Laptop

Used a long process to connect to Pi, found IP of pi using NetScan - See LINK
https://medium.com/@jrcharney/connect-your-raspberry-pi-to-your-computer-via-ethernet-4564e1e68922

Now, need to setup WiFi on Pi AGAIN and confirm

Connecting to WiFi form Terminal has always been a mysterious/confusing task - and always it works in a different way
tried this link: https://askubuntu.com/questions/461825/how-to-connect-to-wifi-from-the-command-line
the below command finally worked, 
nmcli d connect wlan0

rebooting and checking
rebooted, wifi did not automatically connect, connects with the above command ....

Added the following to /etc/network/interfaces
auto wlan0
iface wlan0 inet dhcp
wpa-conf /etc/wpa_supplicant/wpa_supplicant.conf

Added the following to /ect/wpa_supplicant/wpa_supplicant.conf
country=PK

network={
    ssid="MyWifiNetwork"
    psk="myP4ssw0rd"
}
rebooted - now cant even login via the LAN :( SSH connection refuses - still not connecting to WiFi automatically

removed the internet connection sharing in WiFi adapter in windows, setup a bridge between WiFi and ethernet
got IP of pi from netscan

now reverting previous tasks and trying again
removed added lines from interfaces and wpa_supplicant files
reboot

connected again via SSH - WiFi/Ethernet Bridge, IP from NetScan
ifconfig still shows WiFi not connected
typing in the command connects to WiFi
sudo nmcli d connect wlan0

THINKING OF A HACK / JUGAAR
sudo crontab -e
use nano editor
added line
@reboot sleep 30; nmcli d connect wlan0
save and exit
this should run the command 30 seconds after reboot

possibly the problem can be fixed with GUI network settings, but currently no monitor

reboot and test - shutdown - disconnect ethernet - remove bridge in windows

turn on Pi, see netscan for IP - WORKS.... :)

installing ROS Kinetic - following: http://wiki.ros.org/kinetic/Installation/Ubuntu
Installing the DESKTOP FULL VERSION - below commands are copies to keep track of what commands were run, copy from the WEB PAGE - preferred
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
sudo apt-get update
sudo apt-get install ros-kinetic-desktop-full
echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
sudo apt install python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential
sudo apt install python-rosdep
sudo rosdep init
rosdep update

install step might take time, 400+ MB to download and install

ROS KINETIC INSTALLED

Creating ROS WorkSpace
http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment
	mkdir -p ~/turtle_ws/src
	cd turtle_ws
	catkin_make
	
added environment setup lines in .bashrc file
cd ~
nano .bashrc
	source source ~/turtle_ws/devel/setup.bash
	export ROS_HOSTNAME=192.168.18.36
	export ROS_MASTER_URI=http://192.168.18.36:11311/

installed screen, sudo apt install screen

installing RosSerial - all packages
	sudo apt install ros-kinetic-rosserial-*

Installing Arduino-cli - https://arduino.github.io/arduino-cli/installation/
	cd ~
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
	arduino-cli config init
	arduino-cli core update-index
	arduino-cli core install arduino:avr
	arduino-cli board list			(to see where is Arduino board connected and which one and if it is detected)

	Arduino is connected via
	Port         Type              Board Name                FQBN             Core
	/dev/ttyACM0 Serial Port (USB) Arduino Mega or Mega 2560 arduino:avr:mega arduino:avr


Create a new Catkin Package
	cd ~
	cd src
	catkin_create_pkg motorControl rospy roscpp std_msgs
	cd motorControl

Creating an Arduino Sketch in Catkin Package to Test Motors
	cd ~/turtle_ws/src/motorControl
	arduino-cli sketch new motorTest
	nano motorTest/motorTest.ino	
	CODE - see file in GIT - motorTest.ino
	arduino-cli compile --fqbn arduino:avr:mega motorTest
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:mega motorTest
	GOT ERROR ABOUT PERMISSION DENIED
	sudo adduser $USER dialout
	end SSH Session and start a new one, go to the package directory
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:mega motorTest
	
	Tested each motor individually to confirm pins and directions

	had some problems with connectivity again, installed screen
	sudo apt install screen
	
	run screen initially when starting a new SSH session and use screen -r to resume to a prevous screen session


Created another Arduino Sketch to test Basic Movement of the Robot
	cd ~/turtle_ws/src/motorControl
	arduino-cli sketch new firstMoves
	nano firstMoves/firstMoves.ino
	arduino-cli compile --fqbn arduino:avr:mega firstMoves
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:mega firstMoves

See Arduino Code in the git repo
The code is not ideal, but works - see Youtube Video: https://www.youtube.com/watch?v=o_DxhvRwbOo

Install Teleop_Twist_Keyboard for Keyboard Control
	sudo apt install ros-kinetic-teleop-twist-keyboard

Test TeleopTwistKeyboard, in different SSH Terminals, type the following
SSH 1 - roscore
SSH 2 - rosrun teleop_twist_keyboard teleop_twist_keyboard.py
	press the keys to send teleop Twist Commands on the cmd_vel topic
SSH 3 - for viewing the data
rostopic list			gives the list of current topics
rostopic info /cmd_vel	gives info about the topic cmd_vel
rostopic echo /cmd_vel	echos the data on cmd_vel topic

Create Arduino Sketch Folder and build rosserial Arduino libraries
mkdir Arduino
cd Arduino/
mkdir libraries
cd libraries
rosrun rosserial_arduino make_libraries.py .

Created another Arduino Sketch to perform simple TELEOP
	cd ~/turtle_ws/src/motorControl
	arduino-cli sketch new teleTurtle
	nano teleTurtle/teleTurtle.ino
	arduino-cli compile --fqbn arduino:avr:mega teleTurtle
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:mega teleTurtle
	
	See code in the repository, teleTurtle

for some reason, sketch not comiling, seems to be library location / sketchbook location issue

now installing in another way
arduino-cli lib update-index
arduino-cli lib search rosserial
arduino-cli lib install "Rosserial Arduino Library"

The issue was NOT the library, it said 2 libraries, using this one when upload

apparently, copying the whole code related to ROS, at the start of the arduino sketch made it work....

to run the teleop, need 3 different terminals
SSH 1: roscore
SSH 2: rosrun teleop_twist_keyboard teleop_twist_keyboard.py
SSH 3: rosrun rosserial_python serial_node.py /dev/ttyACM0
