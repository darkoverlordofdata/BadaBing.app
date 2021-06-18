# badabing.app

## Daily Wallpaper from https://bing.wallpaper.pics/ for helloSystem

    Images are copyright to their respective owners. 
    Bing is a trademark of Microsoft. 
    This application is not affiliated with Bing or its services in any way.

### a re-idmagineering of:

https://github.com/darkoverlordofdata/badabing

Rather than a traditional ui, this will focus on a system tray icon.
Screen lock will be a prefrence: none | metalock | catlock

### dependancies

    pyqt5
    libappindicator
    ImageMagick

### features

    Enable automation by using gui to set preferences.
    General Preferences:

        Launch on start:
            creates /Applications/Autostart/BadaBing.app

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


