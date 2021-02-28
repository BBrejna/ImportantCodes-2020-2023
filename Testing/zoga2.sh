#!/bin/bash
# manjaro simps: sudo pacman -Sy time
MEM_LIMIT=256 # in megabytes
TIME_LIMIT=16 # in seconds
for((i=1; i<=100; i++)); do
    for j in {a..z}; do
        if [ -f "ple$i${j}.in" ]; then
            echo -n "ple$i${j}: "
            # can connect with oiejq script
            command time -f "%M %e %x" ./a < ple$i${j}.in > out 2> log
            read MEM TIME STATUS <log
            MEM=$((MEM/1024))
            echo -n "${MEM}/${MEM_LIMIT}Mb ${TIME}/${TIME_LIMIT}s "

            if (( MEM >= MEM_LIMIT )); then  
                echo -e "\e[93mmemory limit\e[39m"
                break
            elif (( $(echo "$TIME > $TIME_LIMIT" | bc -l) )); then
                echo -e "\e[93mtime limit\e[39m"
                break
            elif ! diff -bwq ple$i${j}.out out &> /dev/null; then
                echo -e "\e[91mwrong answer\e[39m"
                break
            fi

            echo -e "\e[92maccepted\e[39m"
        fi
    done
done