# badabing.app

## Daily Wallpaper from https://bing.wallpaper.pics/ for helloSystem

    Images are copyright to their respective owners. 
    Bing is a trademark of Microsoft. 
    This application is not affiliated with Bing or its services in any way.

### Launch on start:
    create link as /Applications/Autostart/BadaBing.app


### icon

    The icon is from [icons8](https://icons8.com/icon/pack/user%20interface/small)

    [terms](https://community.icons8.com/t/can-i-use-icons8-for-free/30)




![Screenshot](https://raw.githubusercontent.com/darkoverlordofdata/BadaBing.app/main/assets/locked.png "Screen Locked")

![Screenshot](https://raw.githubusercontent.com/darkoverlordofdata/BadaBing.app/main/assets/authorize.png "Enter PIN")

### dependancies

    pyqt5
    libappindicator

### build catlock

run as BadaBing.app/catlock/catlock
```
cd catlock
./configure
cd build
make
```
 ./catlock/catlock --pin 420420 --theme wallpaper 

/home/darko/GitHub/BadaBing.app/catlock.py --pin 420420 --tz -3 --font 'Noto Sans'