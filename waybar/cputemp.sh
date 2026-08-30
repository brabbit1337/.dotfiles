#!/usr/bin/env bash

# CPU Temp monitor

#paste <(cat /sys/class/thermal/thermal_zone*/type) <(cat /sys/class/thermal/thermal_zone*/temp) | column -s $'\t' -t | sed 's/\(.\)..$/.\1°C/' | awk '{print $2}' | tail -n +2 | cut -c 1-2



#!/bin/bash

if grep -qi "AMD" /proc/cpuinfo; then
    # AMD processzor esetén k10temp-ből olvassuk ki a hőmérsékletet
    sensors | awk '/Tctl/ {gsub("\\+|°C", "", $2); print $2}'
else
    # Intel processzor esetén a sysfs fájlokat olvassuk
    paste <(cat /sys/class/thermal/thermal_zone*/type) <(cat /sys/class/thermal/thermal_zone*/temp) | \
        column -s $'\t' -t | sed 's/\(.\)..$/.\1°C/' | awk '{print $2}' | tail -n +2 | cut -c 1-2
fi
