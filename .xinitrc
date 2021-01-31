#!/bin/sh

setxkbmap dk

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap

if [ -f $sysresources ]; then
    xrdb -merge $sysresources
fi

if [ -f $sysmodmap ]; then
    xmodmap $sysmodmap
fi

if [ -f "$userresources" ]; then
    xrdb -merge "$userresources"
fi

if [ -f "$usermodmap" ]; then
    xmodmap "$usermodmap"
fi

[ -f ~/.Xdefaults ] && xrdb -merge ~/.Xdefaults

if [ -d /etc/X11/xinit/xinitrc.d ] ; then
 for f in /etc/X11/xinit/xinitrc.d/?*.sh ; do
  [ -x "$f" ] && . "$f"
 done
 unset f
fi

if [ "$(command -v xset)" >/dev/null 2>&1 ];
then
    xset s off -dpms 	#Disable DPMS and prevent screen from blanking
    #xset s off 	#Disable screen saver blanking
    #xset -dpms 	#Turn off DPMS
    #xset s 3600 3600 	#Change blank time to 1 hour
    #xset dpms force off 	#Turn off screen immediately
    #xset dpms force standby 	#Standby screen
    #xset dpms force suspend 	#Suspend screen 
fi

#xcalib -d :0 /usr/local/share/color/PL2488H.icm
export GTK_CSD="0"
export LD_PRELOAD="/usr/lib/libgtk3-nocsd.so.0"

xsetroot -cursor_name left_ptr
xsetroot -solid "#000000"

while true; do
    volume=`pactl list sinks | grep '^[[:space:]]Volume:' | grep -Po '\d+%' | head -n 1`
    date=`date '+%a %d/%m %H:%M'`
    ip=`ip a show eno1 | grep inet | awk '{ print $2}' | head -n 1 | cut -d'/' -f1`
    xsetroot -name "vol: ${volume}  /  ${ip}  /  ${date}";
    sleep 1;
done &


exec dwm
