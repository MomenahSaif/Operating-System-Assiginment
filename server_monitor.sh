#!/bin/bash

#setting the limit for Disk,CPU,Memory 
Disk=30
CPU=30
Memory=10

#setting the size od log file
Log_File="$HOME/server_monitor.log"
Log_Size=10MB

# This function send alerts and save in the log file
send_alert() 
{
  local msg="$1"
  echo "Alert:- $msg"
}

# This fucntion is for checking disk usage
Disk_usage()
 {
  local disk_usage=$(df -h / | awk 'NR==2{sub(/%/, "", $5); print $5}')
  if (( $(echo "$disk_usage >= $Disk" | awk '{print ($1 >= $2)}') )); then
    send_alert "Usage of Disk is exceeded ${Disk}% - Current Usage: $disk_usage%"
  fi
}

# This fucntion is for checking CPU usage
CPU_usage()
 {
  local cpu_usage=$(top -bn1 | grep "Cpu(s)" | awk '{sub(/%us,/, ""); print $2}')
  if (( $(echo "$cpu_usage >= $CPU" | awk '{print ($1 >= $2)}') )); then
    send_alert "Usage of CPU is exceeded ${CPU}% - Current Usage: $cpu_usage%"
  fi
}

# This fucntion is for checking memory usage
Memory_usage() 
{
  local free_memory=$(free | awk '/Mem/{print int(($4/$2) * 100)}')
  if (( $(echo "$free_memory <= $Memory" | awk '{print ($1 <= $2)}') )); then
    send_alert "Available memory falls below a limit: $free_memory%"
  fi
}

# Function for log rotation
Log_rotation() 
{
  if [ -f "$Log_File" ] && (( $(du -k "$Log_File" | cut -f1) >= $(echo "$Log_Size * 1024" | awk '{print int($1)}') )); then
    mv "$Log_File" "$Log_File.old"
    touch "$Log_File"
  fi
}


# creating the log file
touch "$Log_File"

# script time 
echo "Server monitoring script started at $(date)" >> "$Log_File"

#Functions
Disk_usage
CPU_usage
Memory_usage
Log_rotation

# This maintain the log script end time
echo "Server monitoring and management script ended at $(date)" >> "$Log_File"




