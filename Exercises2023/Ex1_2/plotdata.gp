#!/usr/bin/gnuplot

# Get the input data file
data_file = "input2D_float.txt"

set datafile separator ","

# Set plot properties
set title "2D Data Plot"
set xlabel "X"
set ylabel "Y"
set style data points
set xrange [0:6]
set yrange [0:6]

set terminal pngcairo
set output "Outputs/png/plot-withfit.png"

# Plot the data from the specified file, skipping the first line  
# Added fit line from AnalyseData.cpp
plot data_file every ::1 using 1:2 with points ps 1 pt 7 lc black title "Dummy data", 0.126266*x+2.02628 with lines lw 2 lc rgb "red" title "Fit Line" \


