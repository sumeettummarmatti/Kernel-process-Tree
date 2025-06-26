#!/bin/bash

echo "🔧 [1] Building..."
make || exit 1

echo "🚀 [2] Running user program..."
./user &
USER_PID=$!
echo "👨‍👦 Parent PID: $USER_PID"

# Give child processes time to spawn
sleep 1

echo "📦 [3] Inserting kernel module..."
sudo insmod kernul.ko target_pid=$USER_PID

sleep 1

echo "📄 [4] Output from /proc/mem_tree:"
cat /proc/mem_tree

echo "🧹 [5] Unloading kernel module..."
sudo rmmod kernul

echo "🧽 [6] Cleaning up..."
make clean

echo "✅ Done."
