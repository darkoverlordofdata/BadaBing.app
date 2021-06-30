

# Wallpaper & ScreenLock
This is stalled due to the nature of Qt and my inexperience with it. Yo supress the global menu, I need to use Xlib - the original catlock (kitty-cat-lock) is written in c. Do I rework the c version or can I use X11 from python, which I also lack experience in?

### run:
/home/darko/Documents/GitHub/BadaBing.app/catlock --pin 420420 --tz -3

/Applications/Autostart/BadaBing.app/catlock --pin 420420 --tz -3

### install
```
cd Documents/GitHub 
git clone https://github.com/darkoverlordofdata/BadaBing.app.git
cp -rf ~/Documents/GitHub/BadaBing.app  /Applications/Autostart
```

### remove 
rm -rf /Applications/Autostart/BadaBing.app

/Applications/Autostart/BadaBing.app/catlock.py --pin 420420

### screen locks
if you need security use metalock -
```
#pkg install metalock
```
Catlock is desiged for low security situations - 
* keeping Balthazar* off my keyboard
* use the same pin as my other devices
* share my desktop without giving out my password

* my cat Balthazar has crashed metalock.  

### todo 
* optionally use metalock
* authorize using password if no --pin is specified
