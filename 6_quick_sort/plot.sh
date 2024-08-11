#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 <source_file.c>  [mode]"
    echo "mode: 'test' or 'plot'"
    exit 1
fi

SOURCE_FILE=$1
MODE=$2

BASENAME=$(basename "$SOURCE_FILE" .c)
DATA_FILE="${BASENAME}_results.dat"

echo "Compliing the C program ($SOURCE_FILE)"
gcc -o "$BASENAME" "$SOURCE_FILE"

if [ $? -ne 0 ]; then
    echo "Compiling failed. Exiting"
    exit 1
fi
echo "Running the compiled program to generate data file..."

if [ "$MODE" = "test" ]; then
    ./"$BASENAME" test
    echo "Test completed successfully."
elif [ "$MODE" = "plot" ]; then
    ./"$BASENAME" plot "$DATA_FILE"
    echo "Plotting the data..."
    gnuplot -persist -e "set title 'Performance Analysis'; \
                        set xlabel 'Input size(n)'; \
                        set ylabel 'Number of comparisons'; \
                        set key outside right top; \
                        set logscale x 2; \
                        plot '$DATA_FILE' using 1:2 with linespoints title 'Best Case' lc rgb 'blue', \
                        '$DATA_FILE' using 1:3 with linespoints title 'Average Case' lc rgb 'green', \
                        '$DATA_FILE' using 1:4 with linespoints title 'Worst Case' lc rgb 'red'"
                    
    echo "Plotting completed.."
fi