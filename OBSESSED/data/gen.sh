#!/bin/sh

g++ -o general general.cpp -O2
g++ -o subtask3 subtask3.cpp -O2

mkdir tests

# Subtask 1
echo '2 15 1 1 1 1' | ./general 6666101 > tests/1-01.in
echo '2 15 1 1 1 1' | ./general 6666102 > tests/1-02.in
echo '2 1000 1 1 1 1' | ./general 6666103 > tests/1-03.in
echo '2 1000 1 1 1 1' | ./general 6666104 > tests/1-04.in
echo '2 150000 1 1 1 1' | ./general 6666105 > tests/1-05.in
echo '2 150000 1 1 1 1' | ./general 6666106 > tests/1-06.in
echo '2 300000 1 1 1 1' | ./general 6666107 > tests/1-07.in
echo '2 300000 1 1 1 1' | ./general 6666108 > tests/1-08.in
echo '2 300000 1 1 1 0.1' | ./general 6666109 > tests/1-09.in
echo '2 300000 0.1 1 1 1' | ./general 6666110 > tests/1-10.in

# Subtask 2
echo '25 40 1 1 1 1' | ./general 6666201 > tests/2-01.in
echo '25 40 1 1 1 1' | ./general 6666202 > tests/2-02.in
echo '250 400 1 1 1 0' | ./general 6666203 > tests/2-03.in
echo '250 400 1 1 1 1' | ./general 6666204 > tests/2-04.in
echo '1000 1000 1 1 1 1' | ./general 6666205 > tests/2-05.in
echo '1000 1000 1 1 1 1' | ./general 6666206 > tests/2-06.in
echo '1000 1000 1 1 1 1' | ./general 6666207 > tests/2-07.in
echo '1000 1000 1 0 10 10' | ./general 6666208 > tests/2-08.in
echo '1000 1000 1 1 20 20' | ./general 6666209 > tests/2-09.in
echo '1000 1000 1 1 40 20' | ./general 6666210 > tests/2-10.in

# Subtask 3
echo '100 150 150' | ./subtask3 6666301 > tests/3-01.in
echo '100 150 150' | ./subtask3 6666302 > tests/3-02.in
echo '5000 1500 1500' | ./subtask3 6666301 > tests/3-03.in
echo '5000 1500 1500' | ./subtask3 6666302 > tests/3-04.in
echo '50000 1500 50000' | ./subtask3 6666305 > tests/3-05.in
echo '50000 50000 1500' | ./subtask3 6666306 > tests/3-06.in
echo '300000 5000 295000' | ./subtask3 6666307 > tests/3-07.in
echo '300000 295000 5000' | ./subtask3 6666308 > tests/3-08.in
echo '300000 150000 150000' | ./subtask3 6666309 > tests/3-09.in
echo '300000 150000 150000' | ./subtask3 6666310 > tests/3-10.in

# Subtask 4
echo '10000 10000 1 1 0 1' | ./general 6666401 > tests/4-01.in
echo '10000 10000 1 1 0 1' | ./general 6666402 > tests/4-02.in
echo '300000 300000 1 1 0 1' | ./general 6666403 > tests/4-03.in
echo '300000 300000 1 1 0 1' | ./general 6666404 > tests/4-04.in
echo '300000 300000 1 1 0 1' | ./general 6666405 > tests/4-05.in
echo '300000 300000 1 1 0 25' | ./general 6666406 > tests/4-06.in
echo '300000 300000 1 1 0 25' | ./general 6666407 > tests/4-07.in
echo '300000 300000 25 25 0 1' | ./general 6666408 > tests/4-08.in
echo '300000 300000 25 25 0 1' | ./general 6666409 > tests/4-09.in
echo '300000 300000 0 0 0 1' | ./general 6666410 > tests/4-10.in

# Subtask 5
echo '10000 10000 1 1 1 1' | ./general 6666501 > tests/5-01.in
echo '10000 10000 1 1 1 1' | ./general 6666502 > tests/5-02.in
echo '300000 300000 1 1 1 1' | ./general 6666503 > tests/5-03.in
echo '300000 300000 1 1 1 1' | ./general 6666504 > tests/5-04.in
echo '300000 300000 1 1 1 1' | ./general 6666505 > tests/5-05.in
echo '300000 300000 100 1 1 1' | ./general 6666506 > tests/5-06.in
echo '300000 300000 1 1 100 1' | ./general 6666507 > tests/5-07.in
echo '300000 300000 1 1 1 100' | ./general 6666508 > tests/5-08.in
echo '300000 300000 0 0 1 1' | ./general 6666509 > tests/5-09.in
echo '300000 300000 1 1 100 100' | ./general 6666510 > tests/5-10.in

rm  general subtask3

