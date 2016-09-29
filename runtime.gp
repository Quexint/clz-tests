reset
set ylabel 'time(sec)'
set style histogram cluster gap 1
set style fill solid
set title 'perfomance comparison'
set boxwidth 0.8
set term png enhanced font 'Verdana,10'
set output 'png/runtimeAll.png'
plot for [COL=2:6] 'result_clock_gettime.csv' using COL:xticlabels(1) title columnheader
set output 'png/runtimeIter.png'
plot for [COL=2:2] 'result_clock_gettime.csv' using COL:xticlabels(1) title columnheader
set output 'png/runtimeRecur.png'
plot for [COL=3:3] 'result_clock_gettime.csv' using COL:xticlabels(1) title columnheader
set output 'png/runtimeBShift.png'
plot for [COL=4:4] 'result_clock_gettime.csv' using COL:xticlabels(1) title columnheader
set output 'png/runtimeBSearch.png'
plot for [COL=5:5] 'result_clock_gettime.csv' using COL:xticlabels(1) title columnheader
set output 'png/runtimeHarley.png'
plot for [COL=6:6] 'result_clock_gettime.csv' using COL:xticlabels(1) title columnheader
