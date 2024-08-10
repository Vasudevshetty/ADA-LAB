set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output './string_matching.png' 

set title "Number of Comparisons for String Matching"
set xlabel "Text Size"
set ylabel "Number of Comparisons"

plot './string_data.dat' using 1:2 title 'best case' with linespoints, \
     './string_data.dat' using 1:3 title 'average case' with linespoints, \
     './string_data.dat' using 1:4 title 'worst case' with linespoints

set output