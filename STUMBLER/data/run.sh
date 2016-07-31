#!/bin/sh

for i in {1..5}
do
    for j in {1..9}
    do
        echo "$i-0$j"
        cat tests/$i-0$j.in | head -n 1
        ./a.out < tests/$i-0$j.in > tests/$i-0$j.ans
        cat tests/$i-0$j.ans
    done
    echo "$i-10"
    cat tests/$i-10.in | head -n 1
    ./a.out < tests/$i-10.in > tests/$i-10.ans
    cat tests/$i-10.ans
done

