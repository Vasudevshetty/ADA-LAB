#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 [mode] [sort-type]"
    echo "mode: 'test' or 'plot'"
    echo "gcdtype: 'euclid' or 'modified' or 'consective'"
    exit 1
fi

MODE=$1
TYPE=$2

echo "Compliing the C program"
gcc -o gcd_algo driver.c

if [ $? -ne 0 ]; then
    echo "Compiling failed. Exiting"
    exit 1
fi

echo "Running compiled program $MODE mode"

if [ "$MODE" = "test" ]; then
    ./gcd_algo test "$TYPE"
    echo "Test completed successfully"
elif [ "$MODE" = "plot" ]; then
    ./gcd_algo plot "$TYPE"
    DATA_FILE="data/${TYPE}_results.dat"
    PNG_FILE="img/${TYPE}_results.png"

    mkdir -p img data

    # Create PNG output using gnuplot
    echo "Plotting the data..."
    gnuplot -e "set terminal pngcairo size 800,600; \
                set output '$PNG_FILE'; \
                set title 'Performance Analysis'; \
                set xlabel 'Input size(n)'; \
                set ylabel 'Number of comparisons'; \
                set key outside right top; \
                plot '$DATA_FILE' using 1:2 with linespoints title 'Best Case' lc rgb 'blue', \
                '$DATA_FILE' using 1:3 with linespoints title 'Worst Case' lc rgb 'red'"

    echo "PNG output created at $PNG_FILE"

    gnuplot -persist -e "set title 'Performace Analysis'; \
                        set xlabel 'Input size(n)'; \
                        set ylabel 'Number of comparsions'; \
                        set key outside right top; \
                        plot '$DATA_FILE' using 1:2 with linespoints title 'Best Case' lc rgb 'blue', \
                        '$DATA_FILE' using 1:3 with linespoints title 'Worst Case' lc rgb 'red'"

    echo "Plotting completed."
fi
