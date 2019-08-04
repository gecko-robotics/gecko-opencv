#!/bin/bash

apt-get -y upgrade
apt-get autoremove -y

apt-get -y install cmake git pkg-config
apt-get -y install libeigen3-dev
apt-get -y install libtbb2 libtbb-dev
apt-get -y install ffmpeg
# apt-get -y install libjpeg8-dev libtiff-dev libjasper-dev libpng-dev libpng-tools
apt-get -y install libv4l-dev v4l-utils x264
apt-get -y install libavresample-dev
apt-get -y install liblapack-dev
apt-get -y install libavcodec-dev libavformat-dev libswscale-dev
# apt-get -y --force-yes install libxvidcore-dev libx264-dev
# apt-get -y install libatlas-base-dev gfortran
# apt -y install libprotobuf-dev protobuf-compiler
# apt-get -y install python2.7-dev
# apt-get -y install python3-dev
# apt-get -y install libgtk2.0-dev
apt-get autoremove -y
