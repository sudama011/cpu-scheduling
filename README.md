# cpu-scheduling
# fcfs, sjf

## input format

The first line is number of processes <br>
Second line is quantum value<br>
next N lines (where N is number of processes)

pid priority arrival time P processor burst I input burst ......O output burst -1

# input
3 <br>
10 <br>
1 2 0 P 3 I 2 P 4 O 3 P 2 -1<br>
2 1 1 P 2 I 1 P 6 O 4 P 3 -1<br>
3 3 2 P 5 I 2 P 7 O 5 P 2 -1<br>

# FCFS output

Process ID&emsp;	Response Time&emsp;	Turnaround Time	&emsp;Waiting Time <br>

1	&emsp; 			0	&emsp;			29		&emsp;	15 <br>
2	&emsp;			2		&emsp;		31		&emsp;	15<br>
3		&emsp;		3		&emsp;		32		&emsp;	11<br>
<br>
Average Turnaround Time: 30.6667<br>
Average Response Time: 1.66667<br>
Average Waiting Time: 13.6667<br>

# SJF output

Process ID	&emsp;Response Time	&emsp;Turnaround Time	&emsp;Waiting Time<br>
1		&emsp;		0	&emsp;			14	&emsp;	0<br>
2		&emsp;		2	&emsp;			28		&emsp;	12<br>
3			&emsp;	7		&emsp;		37		&emsp;	16<br>
Average Turnaround Time: 26.3333<br>
Average Response Time: 3<br>
Average Waiting Time: 9.33333<br>
