set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output './images/sort_data.png' 

set title "Number of Comparisons for Sorting techniques(Insertion, Bubble, Selection)"
set xlabel "Array Size"
set ylabel "Number of Comparisons"

plot './data/sort_data.dat' using 1:2 title 'bubble sort' with linespoints, \
     './data/sort_data.dat' using 1:3 title 'insertion sort' with linespoints, \
     './data/sort_data.dat' using 1:4 title 'selection sort' with linespoints

set output