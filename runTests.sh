#!/bin/sh

echo "n1,n2,mean" > prob2.csv
for i in {10000..100000..250}; do
  ./randGeneoTree $i 0.6 9 > vector.txt
  BENCH=$(hyperfine -w 4 -i -m 2 "./main < vector.txt" | grep -Po "([\\d\\.]+)\\s+[m]?s ±" | head -c-7)
  echo "$i, "0.6",$BENCH" >> prob2.csv
  echo "$i, $i, prob2"
done
