ffmpeg -i $1 -vf scale=$3:$4 -y -r $2 -vcodec rawvideo -pix_fmt gray -f rawvideo pipe:1 2>/dev/null | \
bin/petscii_convert -f $2 -w $3 -h $4 -p gray -t -s 3000 -z -n 4 -m 3 -e 10 2>/dev/null | \
bin/petpix 3
#| ./petscii_convert -f $2 -w $3 -h $4 -p gray -t -s 80 -o > doom.pet
