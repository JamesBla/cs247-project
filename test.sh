#!/bin/bash

for file in tests/case1.txt tests/case2.txt tests/case3.txt tests/case5.txt
do
    echo "Running test $file"
    ./straights < $file > output_own.txt
    ./CS247Straights < $file > output_ofcl.txt
    diff -b output_own.txt output_ofcl.txt
    if [ $? -eq 0 ]
    then
        echo "$(tput setaf 2) Passed " $file
        tput sgr0
    else
        echo "$(tput setaf 1) Failed " $file
        tput sgr0
    fi
    rm output_own.txt output_ofcl.txt
    echo "----------------------------------"
done

for file in tests/case1.txt tests/case2.txt tests/case4.txt
do
    echo "Running test $file"
    ./straights 1337 < $file > output_own.txt
    ./CS247Straights 1337 < $file > output_ofcl.txt
    diff -b output_own.txt output_ofcl.txt
    if [ $? -eq 0 ]
    then
        echo "$(tput setaf 2) Passed " $file
        tput sgr0
    else
        echo "$(tput setaf 1) Failed " $file
        tput sgr0
    fi
    rm output_own.txt output_ofcl.txt
    echo "----------------------------------"
done
