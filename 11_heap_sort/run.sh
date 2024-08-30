#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: <plot|test>"
    exit 1
fi

echo "Compiling the program"
gcc -o heap_sort heap_sort.c

if [ $? -ne 0 ]; then
    echo "Compiling failed. Exiting"
    exit 1
fi

echo "Running the compiled program..."

if [ $1 == "test" ]; then
    ./heap_sort test
    echo "Tested the topo_sort successfully"
elif [ $1 == "plot" ]; then
    ./heap_sort plot

    echo "Plotting the data..."

    gnuplot -e "set terminal pngcairo size 800,600; \
                set output 'heap_sort_results.png'; \
                set title 'Performance analysis'; \
                set xlabel 'Input size(n)'; \
                set ylabel 'No of comparisons'; \
                set key outside right top; \
                plot 'heap_sort_results.dat' using 1:2 with linespoints title 'Best case' lc rgb 'blue', \
                    'heap_sort_results.dat' using 1:3 with linespoints title 'Averag case' lc rgb 'red', \
                    'heap_sort_results.dat' using 1:4 with linespoints title 'Worst case' lc rgb 'green';"

    echo "PNG output generated at heap_sort_results.png"

    gnuplot -persist -e "set title 'Performance analysis'; \
                        set xlabel 'Input size(n)'; \
                        set ylabel 'No of comparisons'; \
                        set key outside right top; \
                        plot 'heap_sort_results.dat' using 1:2 with linespoints title 'Best case' lc rgb 'blue', \
                            'heap_sort_results.dat' using 1:3 with linespoints title 'Averag case' lc rgb 'red', \
                            'heap_sort_results.dat' using 1:4 with linespoints title 'Worst case' lc rgb 'green';"
fi

echo "Graph Plotted"
rm *exe
