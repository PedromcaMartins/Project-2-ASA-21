#!/bin/sh

echo "n1,n2,mean" > prob2.csv
for i in {10000..40000..100}; do
  ./randGeneoTree $i 0.7 9 > vector.txt
  BENCH=$(hyperfine -w 4 -i -m 2 "./main < vector.txt" | grep -Po "([\\d\\.]+)\\s+[m]?s ±" | head -c-7)
  echo "$i, "0.7",$BENCH" >> prob2.csv
  echo "$i, $i, prob2"
done
