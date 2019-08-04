#!/bin/bash

# check if we are root
if [ "$EUID" -eq 0 ] ; then
  echo "Please do not run as root ... installing to user space"
  exit 1
fi

if [[ $# -ne 1 ]]; then
  echo "Please supply an OpenCV version number"
  echo "ex: ./build-opencv.sh 3.4.0"
  exit 1
fi

OPENCV_VERSION=$1
CURRDIR=$(pwd)
OPENCV_INSTALL_DIR="/home/kevin/.local"

if [ ! -f opencv-$OPENCV_VERSION.tar.gz ]; then
  wget -O opencv-$OPENCV_VERSION.tar.gz https://github.com/opencv/opencv/archive/$OPENCV_VERSION.tar.gz
  # wget -O opencv_contrib-$OPENCV_VERSION.tar.gz https://github.com/opencv/opencv_contrib/archive/$OPENCV_VERSION.tar.gz
else
  echo ""
  echo "<<< Using previously downloaded file >>>"
  echo ""
fi

tar -xzf opencv-$OPENCV_VERSION.tar.gz
mkdir opencv-$OPENCV_VERSION/build
cd opencv-$OPENCV_VERSION/build

cmake -DCMAKE_BUILD_TYPE=RELEASE \
-DCMAKE_INSTALL_PREFIX=$OPENCV_INSTALL_DIR \
-DOPENCV_ENABLE_NONFREE=ON \
-DBUILD_WITH_DEBUG_INFO=OFF \
-DBUILD_DOCS=OFF \
-DBUILD_EXAMPLES=OFF \
-DBUILD_TESTS=OFF \
-DBUILD_opencv_ts=OFF \
-DWITH_EIGEN=OFF \
-DWITH_TBB=ON \
-DWITH_V4L=ON \
-DWITH_LIBV4L=ON \
-DWITH_FFMPEG=ON \
-DWITH_QT=OFF \
-DWITH_GTK=ON \
-DCPACK_BINARY_DEB=ON \
-DWITH_CUDA=OFF \
-DBUILD_opencv_python2=OFF \
-DBUILD_opencv_python3=OFF \
-DWITH_PROTOBUF=OFF \
..

make -j4
# make install
make package
