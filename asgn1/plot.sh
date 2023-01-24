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
awk '(NR>1){
    diff = $2 - 3.1415926535;
    print diff;
}' number_test.txt > piError.dat

gnuplot <<END
    set terminal pdf size 3, 3
    set output "circle.pdf"
    set title "Dropped Coconuts"
    set xlabel "x"
    set ylabel "y"
    set object 1 circle at graph 0,0 size graph 1 fs empty border rgb "black" arc [0:90] front
    plot    "outCircle.dat" lt rgb "red" with dots title "", \
            "inCircle.dat" lt rgb "blue" with dots title ""
END
