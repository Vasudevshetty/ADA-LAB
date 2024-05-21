set terminal pngcairo size 1000,800 enhanced font 'Verdana,10'
set output 'binary_search_time.png'

set title "Binary Search Timing Analysis"
set xlabel "Array Size"
set ylabel "Time (nano-seconds)"
set grid

set xrange [0:10000]
set yrange [0:10e-4]

set key outside
set style data linespoints

plot "./files/binarySearch/binary_search_time.dat" using 1:2 title "Best Case" with linespoints, \
     "./files/binarySearch/binary_search_time.dat" using 1:3 title "Average Case" with linespoints, \
     "./files/binarySearch/binary_search_time.dat" using 1:4 title "Worst Case" with linespoints

set output