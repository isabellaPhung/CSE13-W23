#!/bin/bash

./monte_carlo -n 10000 > number_test.txt
awk '{
    if ($5==1) { 
        print $3 " " $4
    }
}' number_test.txt > inCircle.dat

awk '{
    if ($5==0) {
        print $3 " " $4
    }
}' number_test.txt > outCircle.dat

for (( i=1; i < 5; i++ )); do
    ./monte_carlo -n 10000 -r ${i} > number_test${i}.txt
    awk '(NR>1){
        diff = $2 - 3.1415926535;
        print diff;
    }' number_test${i}.txt > "piError${i}.dat";
done

gnuplot <<END
    set terminal pdf size 3, 3
    set output "circle.pdf"
    set title "Dropped Coconuts"
    set xlabel "x"
    set ylabel "y"
    set object 1 circle at graph 0,0 size graph 1 fs empty border rgb "black" arc [0:90] front
    plot    "outCircle.dat" lt rgb "red" with dots title "", \
            "inCircle.dat" lt rgb "blue" with dots title ""
    unset object 1

    set terminal pdf size 5, 3
    set output "error.pdf"
    set title "Pi Error over multiple iterations"
    set xlabel "iterations"
    set logscale x
    set grid
    set ylabel "Difference from Accepted Value"
plot        "piError1.dat" lt rgb "red" with lines title "", \
            "piError2.dat" lt rgb "blue" with lines title "", \
            "piError3.dat" lt rgb "green" with lines title "", \
            "piError4.dat" lt rgb "violet" with lines title "",
END

rm outCircle.dat inCircle.dat piError1.dat piError2.dat piError3.dat piError4.dat number_test.txt number_test1.txt number_test2.txt number_test3.txt number_test4.txt
