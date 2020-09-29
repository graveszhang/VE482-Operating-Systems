#!/bin/bash
curl "http://aqicn.org/?city=Shanghai&widgetscript&size=large&id=52b39d71decf07.20261781" -o raw.txt
temp=$(sed -n "s/.*>\([0-9]\)/\1/p" raw.txt)
temp2=$(echo $temp | awk '{split($0,a,"<"); print a[1]}')

aqi=$(sed -n "s/.*10px;'>\([0-9]*\)<.*tr_p/\1/p" raw.txt)
aqi2=$(echo $aqi | awk '{split($0,a,"m"); print a[1]}')

echo "AQ: $aqi2 Temp: $temp2 ºC"
rm raw.txt
