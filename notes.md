

### run:
/home/darko/Documents/GitHub/BadaBing.app/binglock --pin 420420

### not working:
launch Filer --set-wallpaper /home/darko/Pictures/badabing.jpeg

setting wallpaper via command line causes the desktop icons to move from right alignment to left alignment. I have to manualy re-selct the wallpaper image in Desktop Preferences to move them back to the right, or log out and back in.

### install
```
cd Documents/GitHub
git clone https://github.com/darkoverlordofdata/BadaBing.app.git
cp -rf ~/Documents/GitHub/BadaBing.app  /Applications/Autostart
```

### remove 
rm -rf /Applications/Autostart/BadaBing.app



/Applications/Autostart/BadaBing.app/binglock --pin 420420

### features

Launch on start:
    create link as /Applications/Autostart/BadaBing.app

Rather than a traditional ui, this will focus on a system tray icon.
Screen lock will be a prefrence: none | metalock | catlock


    Enable automation by using gui to set preferences.
    General Preferences:

        Run daily cron job:??
            creates daily job in crontab at 12.01 am

        Use system tray notifier:
            notify when the screen changes

        Generate screen lock assets:
            Integrate with catlock (https://github.com/darkoverlordofdata/kitty-cat-lock.git), my screen lock application.

### other features wanted

    check ~/.face or ~/Pictues/avatar.png for screen lock assets
    screen lock drop down list: none; catlock; metalock

### considerations

    the badabing functionality can easily be replaced with python.
    can imageMagick dependency also be replaced?

    The screen lock can be:
    none (off)
    metalock - sudo pkg install metalock
    catlock - currently using kitty-kat-lock. Can this be replaced using go?


### icon

    The icon is from [icons8](https://icons8.com/icon/pack/user%20interface/small)

    [terms](https://community.icons8.com/t/can-i-use-icons8-for-free/30)


Rather than a traditional ui, this will focus on a system tray icon.
Screen lock will be a prefrence: none | metalock | catlock


    Enable automation by using gui to set preferences.
    General Preferences:

        Run daily cron job:??
            creates daily job in crontab at 12.01 am

        Use system tray notifier:
            notify when the screen changes

        Generate screen lock assets:
            Integrate with catlock (https://github.com/darkoverlordofdata/kitty-cat-lock.git), my screen lock application.

### other features wanted

    check ~/.face or ~/Pictues/avatar.png for screen lock assets
    screen lock drop down list: none; catlock; metalock

### considerations

    the badabing functionality can easily be replaced with python.
    can imageMagick dependency also be replaced?

    The screen lock can be:
    none (off)
    metalock - sudo pkg install metalock
    catlock - currently using kitty-kat-lock. Can this be replaced using go?

