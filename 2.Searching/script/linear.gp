set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output './images/linear_search.png' 

set title "Number of Comparisons for Linear Search"
set xlabel "Array Size"
set ylabel "Number of Comparisons"



plot './data/linear_search.dat' using 1:2 title 'best case' with linespoints, \
     './data/linear_search.dat' using 1:3 title 'average case' with linespoints, \
     './data/linear_search.dat' using 1:4 title 'worst case' with linespoints


set output