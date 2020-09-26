#!/bin/bash
curl http://aqicn.org/?city=Shanghai&widgetscript&size=large&id=52b39d71decf07.20261781 -o Raw
cand=$(cat Raw | sed 's/ /\n/g' | sed -n 's~>\([0-9]*\)<\\\/td~Temp: \1~p')
cand1=$(cat $cand | sed -n 's~\(Temp: [0-9]*\)><\\\/tr><\\\/table~\1~p')
echo $cand1

