#!/usr/bin/env bash
#
#  $1 - chached background jpg 
#  $2 - title information
#
#	Copy & resize the wallpaper to fit on the device
#
mkdir -p ~/.local/share/catlock/themes

res=$(xwininfo -root | grep 'geometry' | awk '{print $2;}')
wxh=$(echo $res | cut -f1 -d+)
width=$(echo $wxh | cut -f1 -dx)
height=$(echo $wxh | cut -f2 -dx)

cp -f $2 ~/.local/share/catlock/themes/wallpaper.info

convert $1 -resize ${width}x$height\! ~/.local/share/catlock/themes/wallpaper.locked.jpg
#
#
if [ -f ~/.local/share/catlock/themes/avatar.png ]; then

	let center=($width/2)-96
	let top=$height/6

	convert $1 -resize ${width}x$height\! -fill black -colorize 40% ~/.local/share/catlock/themes/wallpaper.tmp.jpg
	convert ~/.local/share/catlock/themes/wallpaper.tmp.jpg  ~/.local/share/catlock/themes/avatar.png -geometry +$center+$top -composite ~/.local/share/catlock/themes/wallpaper.authorize.jpg
	rm -f ~/.local/share/catlock/themes/wallpaper.tmp.jpg

elif [ -f ~/.iface ]; then

	let center=($width/2)-96
	let top=$height/6

	convert $1 -resize ${width}x$height\! -fill black -colorize 40% ~/.local/share/catlock/themes/wallpaper.tmp.jpg
	convert ~/.local/share/catlock/themes/wallpaper.tmp.jpg  ~/.iface -geometry +$center+$top -composite ~/.local/share/catlock/themes/wallpaper.authorize.jpg
	rm -f ~/.local/share/catlock/themes/wallpaper.tmp.jpg

else

    convert $1 -resize ${width}x$height -fill black -colorize 40% ~/.local/share/catlock/themes/wallpaper.authorize.jpg

fi       

launch Filer --set-wallpaper $1