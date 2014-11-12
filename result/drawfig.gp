#!/home/yus08002/Tools/gnuplot/bin/gnuplot

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

set xtics 0, 1000, 5000

# DBLP graphs
sim_eps = "sim_dblp.eps"
sim_nw_log = "../buildnw/simi_result.txt"
sim_org_log = "../buildorg/simi_result.txt"
sim_mix_log = "../buildmix/simi_result.txt"

set terminal postscript eps color enhanced "Times-Roman" fontsize
set output sim_eps
set xlabel "Community Pair Index (DBLP)"
set ylabel "Similarity"
plot sim_nw_log using 3 title "Node-walker graph", \
     sim_org_log using 3 title "Mixed graph", \
     sim_mix_log using 3 title "Original graph"

# DBLP graphs
asim_eps = "sim_amazon.eps"
asim_nw_log = "../abdnw/simi_result.txt"
asim_org_log = "../abdorg/simi_result.txt"
asim_mix_log = "../abdmix/simi_result.txt"

set terminal postscript eps color enhanced "Times-Roman" fontsize
set output asim_eps
set xlabel "Community Pair Index (AMAZON)"
set ylabel "Similarity"
plot asim_nw_log using 3 title "Node-walker graph", \
     asim_org_log using 3 title "Mixed graph", \
     asim_mix_log using 3 title "Orignal graph"
