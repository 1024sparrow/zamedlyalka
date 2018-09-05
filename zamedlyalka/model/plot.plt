set title "Ток вынужденных колебаний в RLC-контуре"
set xlabel "t, с."
set ylabel "i, усл. ед."
plot "./data.dat" using 1:2 title "" with linespoints
pause -1
