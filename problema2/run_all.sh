#!/bin/bash
for i in 20 22 24 25 26 27 28; do
    res=$(./camaras-fb $i)
    voraz_cam=$(echo "$res" | grep "Seran necesarias" | awk '{print $3}')
    voraz_time=$(echo "$res" | grep "Tiempo Voraz" | awk '{print $3}')
    fb_cam=$(echo "$res" | grep "La solucion con valor" | awk '{print $5}')
    fb_time=$(echo "$res" | grep "$i tiempo:" | awk '{print $3}')
    echo "| **$i** | $voraz_cam | $fb_cam | $voraz_time | $fb_time |"
done
