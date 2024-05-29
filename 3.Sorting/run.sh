#!/bin/bash

javac -d ./bin/ *.java

if [ $? -eq 0 ]; then
    echo "Java files Compilation successfull"
else
    echo "Error: Java files Compilation failed."
    exit
fi

TYPE=$1
java -cp ./bin/ Plotter $TYPE

if [ $? -eq 0 ]; then
    echo "Execution of Plotter"
else
    echo "Execution of Plotter file failed."
fi

gnuplot -persist -e "set term pngcairo size 800,600 enhanced font 'Verdana,10'; \
                     set output './images/${TYPE}_sort.png'; \
                     set title '${TYPE^} sort Algorithm analysis'; \
                     set xlabel 'Size of the array'; \
                     set ylabel 'Comparisons took for sorting'; \
                     set grid; \
                     set key outside; \
                     plot './data/${TYPE}_sort.dat' using 1:2 title 'Best Case' with linespoints, \
                          './data/${TYPE}_sort.dat' using 1:3 title 'Average Case' with linespoints, \
                          './data/${TYPE}_sort.dat' using 1:4 title 'Worst Case' with linespoints"

echo "Plotted the graph for $TYPE"
