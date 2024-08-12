#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: <plot|test>"
    exit 1
fi

echo "Compiling the c program"
gcc -o topo_sort topo_sort.c

if [ $? -ne 0 ]; then
    ecoh "Compiling failed. Exiting"
    exit 1
fi

echo "Running the compiled program ..."

if [ $1 = "test" ]; then
    ./topo_sort test
    echo "Tested the topo_sort successfully"
elif [ $1 = "plot" ]; then
    ./topo_sort plot
    echo "Plotting the data..."

    gnuplot -e "set terminal pngcairo size 800,600; \
                set output 'topo_sort_results.png'; \
                set title 'Perfomrance analysis'; \
                set xlabel 'Input size(n)'; \
                set ylabel 'No of comparison'; \
                set key outside right top; \
                plot 'topo_sort_results.dat' using 1:2 with linespoints title 'Best Case' lc rgb 'blue', \
                'topo_sort_results.dat' using 1:3 with linespoints title 'Worst Case' lc rgb 'red';"
    echo "PNG output generted at topo_sort_results.png"

    gnuplot -persist -e "set title 'Performance analysis'; \
                         set xlabel 'Input size(n)'; \
                         set ylabel 'No of comparisions'; \
                         set key outside right top; \
                         plot 'topo_sort_results.dat' using 1:2 with linespoints title 'Best Case' lc rgb 'blue', \
                         'topo_sort_results.dat' using 1:3 with linespoints title 'Worst Case' lc rgb 'red';"
    echo "Plotting completed."
else
    echo "Invalid mode: $1. Please use 'test' or 'plot'"
    exit 1
fi
