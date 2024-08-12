#!/bin/bash

if [ $# -lt 3 ]; then
    echo "Usage: $0 <source_file.c> [mode] [traversal]"
    echo "mode: 'test' or 'plot'"
    echo "traversal: 'dfs' or 'bfs'"
    exit 1
fi

SOURCE_FILE=$1
MODE=$2
TRAVERSAL=$3

BASENAME=$(basename "$SOURCE_FILE" .c)
DATA_FILE="data/${TRAVERSAL}_result.dat"
PNG_FILE="img/${TRAVERSAL}_result.png"

echo "Compliing the C program ($SOURCE_FILE)"
gcc -o "$BASENAME" "$SOURCE_FILE"

if [ $? -ne 0 ]; then
    echo "Compilation filaed. Exiting"
    exit 1
fi

mkdir -p data img
echo "Running the compiled program $MODE mode"

if [ "$MODE" = "test" ]; then
    ./"$BASENAME" test "$TRAVERSAL"
    if [ $? -eq 0 ]; then
        echo "Test completed successfully."
    else
        echo "Test failed"
        exit 1
    fi
elif [ "$MODE" = "plot" ]; then
    ./"$BASENAME" plot "$TRAVERSAL"

    echo "Plotting the data..."

    gnuplot -e "set terminal pngcairo size 800,600; \
                set output '$PNG_FILE'; \
                set title 'Performace analysis'; \
                set xlabel 'Input size(n)'; \
                set ylabel 'No of comparisions'; \
                set key outside right top; \
                plot '$DATA_FILE' using 1:2 with linespoints title 'Best Case' lc rgb 'blue', \
                '$DATA_FILE' using 1:3 with linespoints title 'Worst Case' lc rgb 'red'; "

    echo "PNG output created at $PNG_FILE"

    gnuplot -persist -e "set title 'Performace analysis'; \
                        set xlabel 'Input size(n)'; \
                        set ylabel 'No of comparisions'; \
                        set key outside right top; \
                        plot '$DATA_FILE' using 1:2 with linespoints title 'Best Case' lc rgb 'blue', \
                        '$DATA_FILE' using 1:3 with linespoints title 'Worst Case' lc rgb 'red'; "

    echo "plotting completed."
else
    echo "Invalid mode: $MODE. Please use 'test' or 'plot'"
    exit 1
fi
