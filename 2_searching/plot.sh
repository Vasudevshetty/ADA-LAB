#!/bin/bash

if [ $# -lt 3 ]; then
    echo "Usage: $0 <source_file.c> [mode] [searchtype]"
    echo "mode: 'test' or 'plot'"
    echo "searchtype: 'linear' or 'binary'"
    exit 1
fi

SOURCE_FILE=$1
MODE=$2
SEARCHTYPE=$3

BASENAME=$(basename "$SOURCE_FILE" .c)
DATA_FILE="data/${SEARCHTYPE}_results.dat"
PNG_FILE="img/${SEARCHTYPE}_results.png"

echo "Compiling the C program ($SOURCE_FILE)"
gcc -o "$BASENAME" "$SOURCE_FILE"

if [ $? -ne 0 ]; then
    echo "Compilin failed. Exiting"
    exit 1
fi
echo "Running the compiled program $MODE mode"

if [ "$MODE" = "test" ]; then
    ./"$BASENAME" test "$SEARCHTYPE"
    echo "Test completed successfully."
elif [ "$MODE" = "plot" ]; then
    ./"$BASENAME" plot "$SEARCHTYPE"

    echo "Plotting the data..."
    # Create PNG output using gnuplot
    gnuplot -e "set terminal pngcairo size 800,600; \
                set output '$PNG_FILE'; \
                set title 'Performance Analysis'; \
                set xlabel 'Input size(n)'; \
                set ylabel 'Number of comparisons'; \
                set key outside right top; \
                plot '$DATA_FILE' using 1:2 with linespoints title 'Best Case' lc rgb 'blue', \
                '$DATA_FILE' using 1:3 with linespoints title 'Average Case' lc rgb 'green', \
                '$DATA_FILE' using 1:4 with linespoints title 'Worst Case' lc rgb 'red'"

    echo "PNG output created at $PNG_FILE"

    gnuplot -persist -e "set title 'Performace Analysis'; \
                        set xlabel 'Input size(n)'; \
                        set ylabel 'Number of comparsions'; \
                        set key outside right top; \
                        plot '$DATA_FILE' using 1:2 with linespoints title 'Best Case' lc rgb 'blue', \
                        '$DATA_FILE' using 1:3 with linespoints title 'Average Case' lc rgb 'green', \
                        '$DATA_FILE' using 1:4 with linespoints title 'Worst Case' lc rgb 'red'"

    echo "Plotting completed."
fi
