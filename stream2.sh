ffmpeg -i $1 -vf scale=$3:$4 -y -r $2 -vcodec rawvideo -pix_fmt gray -f rawvideo pipe:1 | \
bin/petscii_convert -f $2 -w $3 -h $4 -p gray -t -s 4000 -z -n 5 -m 1 > $5
