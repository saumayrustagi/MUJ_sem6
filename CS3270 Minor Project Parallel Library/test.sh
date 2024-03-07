#!/bin/bash

for ((i = 1; i <= 8; ++i)); do
    echo -ne "i=$i:"
    bash bm.sh "$i"
done
