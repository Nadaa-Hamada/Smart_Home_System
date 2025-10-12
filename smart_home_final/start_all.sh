#!/bin/bash
# start_all.sh - start mosquitto, mjpg-streamer (if installed), python script and node-red
set -e
echo "Starting mosquitto (if installed)..."
if command -v mosquitto >/dev/null 2>&1; then
  sudo systemctl start mosquitto || true
fi
echo "Starting mjpg-streamer (if installed)..."
if command -v mjpg_streamer >/dev/null 2>&1; then
  sudo systemctl start mjpg-streamer || true
fi
echo "Starting smart_home_pi.py..."
nohup python3 smart_home_pi.py >/var/log/smart_home_py.log 2>&1 &
sleep 1
echo "Starting node-red..."
if command -v node-red >/dev/null 2>&1; then
  nohup node-red >/var/log/node-red.log 2>&1 &
fi
echo "All started."
