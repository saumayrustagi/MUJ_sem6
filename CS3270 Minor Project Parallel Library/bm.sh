#!/bin/bash

# Define the number of times to run the program
NUM_RUNS=50

# Initialize a variable to store the sum of execution times
total_time=0

# Loop to run the program NUM_RUNS times
for ((i = 1; i <= NUM_RUNS; i++)); do
    # Start the timer
    start_time=$(date +%s%N)

    # Run your program (replace './your_program' with the actual command to run your program)
    ./parallel_vector_modify "$1"

    # End the timer
    end_time=$(date +%s%N)

    # Calculate the execution time
    execution_time=$((end_time - start_time))

    # Add the execution time to the total
    total_time=$((total_time + execution_time))

    # Optionally, print the execution time for this run
    # echo "Run $i took $execution_time nanoseconds"
done

# Calculate the average execution time
average_time=$((total_time / NUM_RUNS))

# Print the average execution time
echo "Average execution time over $NUM_RUNS runs: $average_time nanoseconds"
