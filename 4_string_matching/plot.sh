#!/bin/bash

echo "Compiling the c program"
gcc -o stringMatching stringMatching.c

if [ $? -ne 0 ]; then
    echo "Compiling failed. Exiting"
    exit 1
fi

echo "Running the compileed program ..."
./stringMatching $1

if [ ! -f stringMatching_results.dat ]; then
    echo "Data file not found. Exiting"
    exit 1
fi
if [ $1 = "plot" ]; then
    echo "Data file generated succesfully"

    echo "Plotting the data..."
    # Create PNG output using gnuplot
    gnuplot -e "set terminal pngcairo size 800,600; \
                set output 'stringMatching_results.png'; \
                set title 'Performance Analysis'; \
                set xlabel 'Input size(n)'; \
                set ylabel 'Number of comparisons'; \
                set key outside right top; \
                plot 'stringMatching_results.dat' using 1:2 with linespoints title 'Best Case' lc rgb 'blue', \
                'stringMatching_results.dat' using 1:3 with linespoints title 'Average Case' lc rgb 'green', \
                'stringMatching_results.dat' using 1:4 with linespoints title 'Worst Case' lc rgb 'red'"

    echo "PNG output created at stringMatching_results.png"

    echo "Plotting the data..."
    gnuplot -persist -e "set title 'stringMatching sort Performance analysis'; \
                    set xlabel 'Input size(n)'; \
                    set ylabel 'Number of Comparisons'; \
                    set key outside right top; \
                    set logscale x 2; \
                    plot 'stringMatching_results.dat' using 1:2 with linespoints title 'Best Case' lc rgb 'blue', \
                    'stringMatching_results.dat' using 1:3 with linespoints title 'Average Case' lc rgb 'green', \
                    'stringMatching_results.dat' using 1:4 with linespoints title 'Worst Case' lc rgb 'red'"

    echo "Plotting completed"
fi
