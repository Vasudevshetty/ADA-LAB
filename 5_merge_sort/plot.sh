#!/bin/bash

echo "Compiling the c program"
gcc -o merge_sort mergeSort.c 

if [ $? -ne 0 ]; then
    echo "Compiling failed. Exiting"
    exit 1
fi

echo "Running the compileed program ..."
./merge_sort $1

if [ $1 = "test" ]; then  
    echo "Tested the algorithm succesfully"
    exit 0
fi

if [ $1 = "plot" ] && [ ! -f merge_results.dat ]; then
    echo "Data file not found. Exiting"
    exit 1
fi

echo "Data file generated succesfully"

echo "Plotting the data..."
gnuplot -persist -e "set title 'Merge sort Performance analysis'; \
                    set xlabel 'Input size(n)'; \
                    set ylabel 'Number of Comparisons'; \
                    set key outside right top; \
                    set logscale x 2; \
                    plot 'merge_results.dat' using 1:2 with linespoints title 'Best Case' lc rgb 'blue', \
                    'merge_results.dat' using 1:3 with linespoints title 'Average Case' lc rgb 'green', \
                    'merge_results.dat' using 1:4 with linespoints title 'Worst Case' lc rgb 'red'"

echo "Plotting completed"

