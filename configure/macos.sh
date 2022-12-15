#!/bin/bash

brew install libssh
brew install boost
brew install googletest
brew install doxygen
brew install lcov

wget https://boostorg.jfrog.io/artifactory/main/release/1.66.0/source/boost_1_66_0.tar.bz2
tar --bzip2 -xf boost_1_66_0.tar.bz2
cd boost_1_66_0
sudo ./bootstrap.sh
sudo ./b2 install
sudo ./bjam toolset=clang cxxflags="-std=c++0x -stdlib=libc++" variant=release link=static threading=multi runtime-link=shared --build-dir=Build --layout=system --without-mpi --without-python install --prefix=/usr/local 
