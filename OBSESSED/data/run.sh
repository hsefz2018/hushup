#!/bin/sh

for i in {1..5}
do
    for j in {1..9}
    do
        echo "$i-0$j"
        ./a.out < tests/$i-0$j.in > tests/$i-0$j.ans
    done
    echo "$i-10"
    ./a.out < tests/$i-10.in > tests/$i-10.ans
done

