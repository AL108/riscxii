#!/bin/bash

test_counter=0
passed_counter=0
failed_counter=0
set_green='\033[0;32m'
set_red='\033[0;31m'
set_col_default='\033[0m'
while IFS=, read -r test_name prog_name; do
    # skip over the header line of the csv file
    if [ $test_counter -eq 0 ]; then
        test_counter=$((test_counter+1))
        continue
    fi
    echo "----------------------------------------------------------------"
    echo "Test $test_counter: '${test_name}' running..."
    echo "$(./vm_riskxvii ./testing/test_programs/${prog_name}/${prog_name}.mi < ./testing/test_stdins/${test_name}.in)" > vm_output_tmp 
    if diff "vm_output_tmp" "testing/test_stdouts/${test_name}.out"; then
        echo "Status: ${set_green}Test Passed${set_col_default}"
        passed_counter=$((passed_counter+1))
    else 
        echo "Status: ${set_red} Test Failed ${set_col_default}"
        failed_counter=$((failed_counter+1))
    fi
    test_counter=$((test_counter+1))
done < ./testing/testcases.csv
rm vm_output_tmp
echo "----------------------------------------------------------------"
echo Summary: "${passed_counter} test(s) passed, ${failed_counter} test(s) failed"
echo 
echo "Test coverage breakdown stored at testing/coverage_data.txt"
echo
echo "Note: If there is an error message below, then you should run make clean.\
 After running make clean, running make and make test should not generate 
the same error."
gcov object_files/*.o > testing/coverage_data.txt
