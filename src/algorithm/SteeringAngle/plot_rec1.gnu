set terminal pngcairo dashed size 1920,1080
set datafile separator ";"
set output "Rec1_plot.png"
set xlabel "sampleTime (us)"
set ylabel "GroundSteering"
set y2label "Computed Steering"
set y2tics
set key outside
set grid
set label "group 14" at graph 0.8,0.8 center front font ",36" rotate by 20
set y2range [-0.2:0.25]

plot \
    "Rec1Plot.csv" using 2:3 every ::1 title "GroundSteeringRequest" with lines lw 2, \
    "" using 2:4 every ::1 axes x1y2 title "Computed Steering" with lines lw 2 lc rgb "red"