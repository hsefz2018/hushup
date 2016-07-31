#!/bin/sh

g++ -o general general.cpp -O2
g++ -o nooverlap nooverlap.cpp -O2
g++ -o nailed nailed.cpp -O2

mkdir tests

# Generator arguments: <Max_coord> <Min_dist> <Max_radius> <N_C> <N_S>

# Subtask 1
echo '1000 5 10 25 0' | ./nooverlap 2333101 > tests/1-01.in
echo '5000 5 10 80 0' | ./nooverlap 2333102 > tests/1-02.in
echo '50000 30 6 500 0' | ./nooverlap 2333103 > tests/1-03.in
echo '50000 30 8 500 0' | ./nooverlap 2333104 > tests/1-04.in
echo '50000 30 10 1000 0' | ./nooverlap 2333105 > tests/1-05.in
echo '100000 150 200 1000 0' | ./nooverlap 2333106 > tests/1-06.in
echo '100000 250 200 1000 0' | ./nooverlap 2333107 > tests/1-07.in
echo '100000 250 200 1000 0' | ./nooverlap 2333108 > tests/1-08.in
echo '100000 250 300 1000 0' | ./nooverlap 2333109 > tests/1-09.in
echo '100000 250 300 1000 0' | ./nooverlap 2333110 > tests/1-10.in

# Subtask 2
echo '30000 30 10 12 12' | ./nooverlap 2333201 > tests/2-01.in
echo '30000 30 10 36 36' | ./nooverlap 2333202 > tests/2-02.in
echo '100000 50 80 10000 50000' | ./nooverlap 2333203 > tests/2-03.in
echo '100000 50 80 10000 50000' | ./nooverlap 2333204 > tests/2-04.in
echo '100000 150 80 0 90000' | ./nooverlap 2333205 > tests/2-05.in
echo '100000 150 80 0 90000' | ./nooverlap 2333206 > tests/2-06.in
echo '100000 150 50 1500 90000' | ./nooverlap 2333207 > tests/2-07.in
echo '100000 100 6 120000 100000' | ./nooverlap 2333208 > tests/2-08.in
echo '100000 100 8 130000 120000' | ./nooverlap 2333209 > tests/2-09.in
echo '100000 100 8 150000 150000' | ./nooverlap 2333233 > tests/2-10.in

# Subtask 3
echo '1000 10 150 100 100' | ./general 2333301 > tests/3-01.in
echo '1000 10 150 500 500' | ./general 2333302 > tests/3-02.in
echo '30000 100 6000 500 500' | ./general 2333303 > tests/3-03.in
echo '30000 100 6000 500 500' | ./general 2333304 > tests/3-04.in
echo '100000 100 20000 1000 15' | ./general 2333305 > tests/3-05.in
echo '100000 100 20000 15 1000' | ./general 2333306 > tests/3-06.in
echo '100000 100 20000 500 1000' | ./general 2333307 > tests/3-07.in
echo '100000 100 20000 1000 1000' | ./general 2333308 > tests/3-08.in
echo '100000 10000 20000 1000 1000' | ./general 2333309 > tests/3-09.in
echo '100000 10000 20000 1000 1000' | ./general 2333310 > tests/3-10.in

# Subtask 4
echo '30000 100 30000 500 500' | ./nailed 2333401 > tests/4-01.in
echo '60000 100 60000 2000 2000' | ./nailed 2333402 > tests/4-02.in
echo '100000 100 100000 5000 5000' | ./nailed 2333403 > tests/4-03.in
echo '100000 100 100000 50000 0' | ./nailed 2333404 > tests/4-04.in
echo '100000 100 100000 50000 6000' | ./nailed 2333405 > tests/4-05.in
echo '100000 100 100000 50000 10000' | ./nailed 2333406 > tests/4-06.in
echo '100000 100 100000 50000 50000' | ./nailed 2333407 > tests/4-07.in
echo '100000 100 100000 50000 50000' | ./nailed 2333408 > tests/4-08.in
echo '100000 10000 100000 50000 50000' | ./nailed 2333409 > tests/4-09.in
echo '100000 10000 100000 50000 50000' | ./nailed 2333410 > tests/4-10.in

# Subtask 5
echo '30000 100 4000 5000 2500' | ./general 2333501 > tests/5-01.in
echo '30000 100 4000 50000 2500' | ./general 2333502 > tests/5-02.in
echo '100000 100 1000 50000 10000' | ./general 2333503 > tests/5-03.in
echo '100000 100 1000 50000 30000' | ./general 2333504 > tests/5-04.in
echo '100000 100 1000 50000 50000' | ./general 2333505 > tests/5-05.in
echo '100000 100 30000 50000 50000' | ./general 2333506 > tests/5-06.in
echo '100000 100 30000 50000 50000' | ./general 2333507 > tests/5-07.in
echo '100000 1000 30000 50000 50000' | ./general 2333508 > tests/5-08.in
echo '100000 10000 30000 50000 50000' | ./general 2333509 > tests/5-09.in
echo '100000 10000 30000 50000 50000' | ./general 2333510 > tests/5-10.in

rm  general nooverlap nailed

