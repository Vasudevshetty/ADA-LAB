set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'gcd_counts.png'

set title "GCD Algorithm Comparison"
set xlabel "Test Case Index"
set ylabel "Number of Operations"
set grid

set key outside
set style data linespoints

plot "./data/gcd_counts.dat" using 0:4 title "Euclid" with linespoints, \
     "./data/gcd_counts.dat" using 0:5 title "Consecutive" with linespoints, \
     "./data/gcd_counts.dat" using 0:6 title "Modified Euclid" with linespoints
