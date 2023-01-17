#!/bin/bash
file_array=()
IFS=" "
./monte_carlo -n 10 > number_test.txt
#read -ra file_array <<< "a b c d e f"
#echo ${file_array[0]}
#while read line; do echo $line; done < number_test.txt
#while read line; do read -ra file_array <<< $line; x="${file_array[0]}"; x+=" "; x+="${file_array[1]}"; echo $x; done < number_test.txt
while read line; do read -ra file_array <<< $line; if [[ ${file_array[4]} = 1 ]]; then line="${file_array[2]}"; line+=" "; line+="${file_array[3]}"; echo $line >> in_circle.txt; else line="${file_array[2]}"; line+=" "; line+="${file_array[3]}"; echo $line >> out_circle.txt; fi done < number_test.txt

