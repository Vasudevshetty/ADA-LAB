#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: <plot|test> <memoized|normal>"
    exit 1
fi

MODE=$1
TYPE=$2

echo "Compiling the program ..."
gcc -o knapsack knapsack.c

echo "Running the program in $MODE"

if [ "$MODE" = "test" ]; then
    ./knapsack test "$TYPE"
    echo "Tested successfully"
elif [ "$MODE" = "plot" ]; then
    ./knapsack plot "$TYPE"

    echo "Data generated."
    echo "Plottting the data..."

    gnuplot -persist -e "set title 'Performance analysis'; \
                         set xlabel 'Input size(n)'; \
                         set ylabel 'No of comparisons'; \
                         set key outside right top; \
                         plot 'knapsack_results.dat' with linespoints lc rgb 'blue';"

    echo "Plotted data."
fi
rm *.exe
