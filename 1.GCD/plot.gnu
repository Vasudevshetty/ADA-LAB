set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'gcd_counts.png'

set title "GCD Algorithm Comparison (Min/Max Analysis)"
set xlabel "Test Case Index"
set ylabel "Number of Operations"
set grid

set xrange [0:220]
set yrange [-10:220]

set key outside
set style data linespoints

plot "./data/gcd_counts.dat" using 1:2 title "Euclid Min" with linespoints, \
     "./data/gcd_counts.dat" using 1:3 title "Euclid Max" with linespoints, \
     "./data/gcd_counts.dat" using 1:4 title "Consecutive Min" with linespoints, \
     "./data/gcd_counts.dat" using 1:5 title "Consecutive Max" with linespoints, \
     "./data/gcd_counts.dat" using 1:6 title "Modified Min" with linespoints, \
     "./data/gcd_counts.dat" using 1:7 title "Modified Max" with linespoints

set output