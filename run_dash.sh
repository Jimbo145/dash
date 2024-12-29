#!/bin/bash

export XDG_RUNTIME_DIR=/run/user/1000
export HOME=/home/pi

# Define the log file path
LOG_FILE="/home/pi/dash/logs/dash_output.log"

# Ensure the logs directory exists
mkdir -p /home/pi/dash/logs

while true; do
    exec startx /home/pi/dash/bin/dash -- vt7 > "$LOG_FILE" 2>&1
    sleep 1
done
