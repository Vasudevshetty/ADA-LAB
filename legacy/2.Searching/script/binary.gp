set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output './images/binary_search.png' 

set title "Number of Comparisons for Binary Search"
set xlabel "Array Size"
set ylabel "Number of Comparisons"

plot './data/binary_search.dat' using 1:2 title 'best case' with linespoints, \
     './data/binary_search.dat' using 1:3 title 'average case' with linespoints, \
     './data/binary_search.dat' using 1:4 title 'worst case' with linespoints

set output