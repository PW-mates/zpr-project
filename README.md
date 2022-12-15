# ZPR-Project
[![Coverage Status](https://coveralls.io/repos/github/box/boxcli/badge.svg?branch=main)](https://coveralls.io/github/box/boxcli?branch=main)

Tool for synchronizing the contents of directories through a server accessible via ssh.

Project outcome is to create an application that perform continuous data synchronization of a specified folder between a local PC and a remote Server and implement the following requirements:

* Server access via ssh
* Main functionality should correspond to the Unison functionality

# Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.
## Prerequisites
The main application will be written by C++20 (ISO/IEC 14882) with the following libraries:
| Tool | Version |
| -------- | -------- |
| CMake | 3.24.4+ |
| inotify-tools | 3.22.6.0+ |
| boost | 1.80.0+ |
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
### MacOS
To install all the required libraries on MacOS, run the following command:
```
sh ./configure/macos.sh
```
## Usage
### Connect to localhost
ssh-keygen -t rsa -f test_key
cat test_key.pub >> ~/.ssh/authorized_keys
./zpr_sync --pl /. --n user@localhost --pr /Downloads/ --k pathToKey

