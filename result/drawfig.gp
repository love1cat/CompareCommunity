#!/Users/andy/Tools/gnuplot/bin/gnuplot

# set style
lwidth = 1
psize =  1 
fontsize = 30
set autoscale
set style data linespoints
set key right top 
set style line 1 lt 1 pi -1 lw lwidth pt 4 ps psize 
set style line 2 lt 3 pi -3 lw lwidth pt 3 ps psize
set style line 3 lt 7 pi -7 lw lwidth pt 7 ps psize
# set yrange [0:1.25]
# set ytics 0, 0.2, 1
set style increment user
set grid ytics lt 0 lw 1 lc rgb "#bbbbbb"
set grid xtics lt 0 lw 1 lc rgb "#bbbbbb"

# plot limited opt with diff area results
# set yrange [340:480]
set xtics 0, 1000, 5000
sim_eps = "sim.eps"
sim_nw_log = "nw/simi_result.txt"
sim_org_log = "org/simi_result.txt"
sim_mix_log = "mix/simi_result.txt"

set terminal postscript eps color enhanced "Times-Roman" fontsize
set output sim_eps
set xlabel "Community Pair Index"
set ylabel "Similarity"
plot sim_nw_log using 3 title "Node-walker graph", \
     sim_org_log using 3 title "Original graph", \
     sim_mix_log using 3 title "Mixed graph"

