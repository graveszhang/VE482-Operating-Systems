#! /bin/sh
wget https://shanghaicity.openservice.kankanews.com/public/aqi/index -O aqi.txt > /dev/null 2>&1
wget https://m.weathercn.com/en/cn/shanghai/106577/weather-forecast/106577 -O temp.txt > /dev/null 2>&1
temp_line=$(sed -n "/&deg/p" temp.txt)
temp=$(echo $temp_line | awk '{split($0,a,"="); print a[3]}' | awk '{split($0,a," "); print a[2]}' | awk '{split($0,a,"&"); print a[1]}')
aqi_line=$(sed -n "/AQI-text/p" aqi.txt)
aqi=$(echo $aqi_line  | awk '{split($0,a,"="); print a[4]}'| awk '{split($0,a,"<"); print a[1]}' | awk '{split($0,a,">"); print a[2]}')
echo "AQ: ${aqi} Temp: ${temp} ºC"
rm -rf aqi.txt temp.txt
