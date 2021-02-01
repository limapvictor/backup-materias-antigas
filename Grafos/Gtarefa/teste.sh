#!/bin/bash
for i in {1..10}; do
    ./028 "$((10*$i))" "$((20*$i))" "$i"    
done