set terminal png
set output 'output.png'
set title 'Gcd analysis'
set xrange [10:100]
set yrange [10:100]
set xlabel 'gcd of inputs'
set ylabel 'count'
set style data linespoints
plot 'best_gcd.txt' title 'best time', 'worst_gcd.txt' title 'worst time'
set output