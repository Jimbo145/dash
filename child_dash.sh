#!/bin/bash

export XDG_RUNTIME_DIR=/run/user/1000
export HOME=/home/pi

exec startx /home/pi/dash/bin/dash -- vt7 
