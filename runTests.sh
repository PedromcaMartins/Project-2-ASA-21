#!/usr/bin/env bash

./tests/tests/test.sh
/usr/bin/env /usr/lib/jvm/java-16-openjdk-amd64/bin/java -XX:+ShowCodeDetailsInExceptionMessages -cp /home/bernardo/.config/Code/User/workspaceStorage/3a0d3b06cd1ab5a09a9c85ed8b8ec12f/redhat.java/jdt_ws/Project-2-ASA-21_6f4fa2d5/bin test > results.txt
cat results.txt

./tests/smol_tests/test.sh
cd /home/bernardo/Desktop/PROJASA2/Project-2-ASA-21 ; /usr/bin/env /usr/lib/jvm/java-16-openjdk-amd64/bin/java -XX:+ShowCodeDetailsInExceptionMessages -cp /home/bernardo/.config/Code/User/workspaceStorage/3a0d3b06cd1ab5a09a9c85ed8b8ec12f/redhat.java/jdt_ws/Project-2-ASA-21_6f4fa2d5/bin smol_test > results.txt

cat results.txt