#!/bin/bash

for file in suite_constructor.txt suite_deactivate.txt suite_wrong_pw.txt suite_activate.txt suite_reactivate.txt suite_base.txt suite_hard.txt suite_2.txt
do
    echo "Running test $file"
    ./Passwords < $file > output_own.txt
    ./CS247Passwords < $file > output_ofcl.txt
    diff output_own.txt output_ofcl.txt
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
