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
PNG_FILE="img/${BASENAME}_results.png"

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

    PLOT_COMMAND=""
    if [ "$BASENAME" = "floyds" ]; then
        PLOT_COMMAND="plot '$DATA_FILE' using 1:2 with linespoints title 'Floyds general' lc rgb 'blue';"
    else
        PLOT_COMMAND="plot '$DATA_FILE' using 1:2 with linespoints title 'Best Case' lc rgb 'blue', \
        '$DATA_FILE' using 1:3 with linespoints title 'Worst Case' lc rgb 'red';"
    fi

    gnuplot -e "set terminal pngcairo size 800, 600; \
                        set output '$PNG_FILE'; \
                        set title 'Performace analysis'; \
                        set xlabel 'Input size(n)'; \
                        set ylabel 'No of comparisons'; \
                        set key outside right top; \
                        $PLOT_COMMAND"

    gnuplot -persist -e "set title 'Performace analysis'; \
                        set xlabel 'Input size(n)'; \
                        set ylabel 'No of comparisons'; \
                        set key outside right top; \
                        $PLOT_COMMAND"

    echo "plotting completed."

    rm *.exe
else
    echo "Invalid mode: $MODE. Please use 'test' or 'plot'"
    exit 1
fi
