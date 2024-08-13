#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 <source_file.c> [mode]"
    echo "mode: 'test' or 'plot'"
    exit 1
fi

SOURCE_FILE=$1
MODE=$2

BASENAME=$(basename "$SOURCE_FILE" .c)
DATA_FILE="data/${BASENAME}_results.dat"

mkdir -p data img

echo "Compiling the c program ($SOURCE_FILE)"
gcc -o "$BASENAME" "$SOURCE_FILE"

if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting"
    exit 1
fi

if [ "$MODE" = "test" ]; then
    ./"$BASENAME" test
    if [ $? -eq 0 ]; then
        echo "Test completed successfully."
    else
        echo "Test failed"
        exit 1
    fi
elif [ "$MODE" = "plot" ]; then
    ./"$BASENAME" plot

    echo "Plotting the data..."

    gnuplot -persist -e "set title 'Performace analysis'; \
                        set xlabel 'Input size(n)'; \
                        set ylabel 'No of comparisons'; \
                        set key outside right top; \
                        plot '$DATA_FILE' with linespoints title 'Floyds general' lc rgb 'blue';"

    echo "plotting completed."
else
    echo "Invalid mode: $MODE. Please use 'test' or 'plot'"
    exit 1
fi
