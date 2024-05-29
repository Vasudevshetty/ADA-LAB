set terminal pngcairo size 800, 600 enhanced font 'Verdana,10'
set output './images/selection_sort.png'

set title 'selection sort Algorithm anaylsis'
set xlabel 'Size of the array'
set ylabel 'Comparisons took for sorting'
set grid

set key outside

plot './data/selection_sort.dat' using 1:2 title 'Best Case' with linespoints, \
     './data/selection_sort.dat' using 1:3 title 'Average Case' with linespoints, \
     './data/selection_sort.dat' using 1:4 title 'Worst Case' with linespoints

set output