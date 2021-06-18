#!/usr/bin/env bash
# 
#	Bake graphical assets
#
#  $1 - home dir
#  $2 - chached background jpg 
#  $3 - screen width
#  $4 - screen height
#
#	Copy & resize the wallpaper to fit on the device
#
mkdir -p $1/.local/share/catlock/themes

# scale images to the used resolution

res=$(xwininfo -root | grep 'geometry' | awk '{print $2;}')
wxh=$(echo $res | cut -f1 -d+)
width=$(echo $wxh | cut -f1 -dx)
height=$(echo $wxh | cut -f2 -dx)



convert $2 -resize $widthx$height\! $1/.local/share/catlock/themes/wallpaper.locked.jpg
#
#
if [ -f $1/.local/share/catlock/themes/avatar.png ]; then

	let center=($width/2)-96
	let top=$height/6

	convert $2 -resize $widthx$height\! -fill black -colorize 40% $1/.local/share/catlock/themes/wallpaper.tmp.jpg
	convert $1/.local/share/catlock/themes/wallpaper.tmp.jpg  $1/.local/share/catlock/themes/avatar.png -geometry +$center+$top -composite $1/.local/share/catlock/themes/wallpaper.authorize.jpg
	rm -f $1/.local/share/catlock/themes/wallpaper.tmp.jpg

elif [ -f $1/.iface ]; then

	let center=($width/2)-96
	let top=$height/6

	convert $2 -resize $widthx$height\! -fill black -colorize 40% $1/.local/share/catlock/themes/wallpaper.tmp.jpg
	convert $1/.local/share/catlock/themes/wallpaper.tmp.jpg  $1/.iface -geometry +$center+$top -composite $1/.local/share/catlock/themes/wallpaper.authorize.jpg
	rm -f $1/.local/share/catlock/themes/wallpaper.tmp.jpg

else

    convert $2 -resize $widthx$height -fill black -colorize 40% $1/.local/share/catlock/themes/wallpaper.authorize.jpg

fi       

launch Filer --set-wallpaper $2