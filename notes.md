

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