#!/bin/bash
(
while true; do
    TIME=$(date +'%H:%M')
    STATUS=""
    PID_FILE="/tmp/ffmpeg_record.pid"   
    if [ -f "$PID_FILE" ]; then
        PID=$(cat "$PID_FILE")
        if ps -p "$PID" > /dev/null; then
            STATUS="REC"
        else
            rm "$PID_FILE"
        fi
    fi
    
    xsetroot -name "$STATUS   $TIME"
    sleep 1
done
) &

export QT_QPA_PLATFORMTHEME=qt5ct


/lib/xdg-desktop-portal-gtk &
/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &

~/.script/setup-script.sh

exec sxhkd &
dwm


