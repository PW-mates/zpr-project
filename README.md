# ZPR-Project
![Build status](https://github.com/PW-mates/zpr-project/actions/workflows/c-cpp.yml/badge.svg?branch=main)
[![Coverage Status](https://coveralls.io/repos/github/PW-mates/zpr-project/badge.svg?branch=main)](https://coveralls.io/github/PW-mates/zpr-project?branch=main)

Tool for synchronizing the contents of directories through a server accessible via ssh.

Project outcome is to create an application that perform one-time data synchronization of a specified folder between a local PC and a remote Server and implement the following requirements:

* Server access via ssh
* Main functionality should correspond to the Unison functionality

# Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.
## Prerequisites
The main application will be written by C++17 (ISO/IEC 14882) with the following libraries:
| Tool | Version |
| -------- | -------- |
| CMake | 3.24.4+ |
| boost | 1.56 |
| filesystem | built-in library since C++17 |
| libssh | 0.10.3+ |
| openssl | 3.0 |
| doxygen | 1.9.4+ |

## Installing
### Linux
To install all the required libraries on Linux, run the following command:
```
sh ./configure/linux.sh
```
### MacOS (temporarily unavailable)
To install all the required libraries on MacOS, run the following command:
```
sh ./configure/macos.sh
```
### Windows (temporarily unavailable)
To install all the required libraries on Windows, run the following command:
```
```

## Usage
*it is assumed that you are in **source_dir** and follow each step in sequence*
### 1. Create SSH key pairs (for localhost purposes)
```
mkdir keys
cd keys
ssh-keygen -t rsa -f test_key
cat test_key.pub >> ~/.ssh/authorized_keys
cd ..
```
### 2. Build
```
mkdir build
cd build
cmake ..
make
```
### 3. Connection to the localhost
```
./Debug/zpr_sync --pl /. --n user@localhost --pr /Downloads/ --k ../keys/test_key
```
the output of execution should be the same as ```cd ~ && ls```
### Allowed arguments
```
./Debug/zpr_sync --h
```
### Run tests
```
./Debug/runUnitTests
```
### Build documentation
```
doxygen doxyfile
```
**index.html** - /source_dir/build/html/index.html

