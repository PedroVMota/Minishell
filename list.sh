#!/bin/bash

# Define color codes
RED='\033[1;31m'
GREEN='\033[1;32m'
NC='\033[0m' # No Color

# Define directories
dirs=("src/" "inc/lib/Builtin" "inc/lib/Var" "src/syntax/")

# Loop through the directories
for dir in "${dirs[@]}"; do
    # Check if directory exists
    if [ -d "$dir" ]; then
        # Loop through all .c files in the directory
        for file in $(find "$dir" -name "*.c"); do
            # Get the filename
            filename=$(basename "$file")
            # Get the number of lines
            line_count=$(wc -l < "$file")
            # Run norminette and capture the exit status
            norminette "$file" > /dev/null 2>&1
            norm_status=$?
            # Print the information
            if [ $norm_status -eq 0 ]; then
                printf "\t\t%-20s | %-10s | ${GREEN}OK${NC}\n" "$filename" "$line_count"
            else
                printf "\t\t%-20s | %-10s | ${RED}KO${NC}\n" "$filename" "$line_count"
            fi
        done
    else
        echo "Directory $dir does not exist."
    fi
done




dirs=("src/" "inc/lib/Builtin" "inc/lib/Var")

# Iterate through each directory
for dir in "${dirs[@]}"; do
  # Use find to locate all the .c files in the specified directory and its subdirectories
  c_files=$(find "$dir" -type f -name "*.c")

  # Iterate through each found file
  for file in $c_files; do
    # Print the file path
    echo -n "$file "

    # Increment the file counter
    ((file_count++))

    # Check if 4 files have been printed, then end the line with '\'
    if ((file_count % 4 == 0)); then
      echo -n "\\"
    fi

    # Move to the next line if 4 files have been printed
    if ((file_count % 4 == 0)); then
      echo ""
    fi
  done
done

# Add a newline at the end of the output if the last line is incomplete
if ((file_count % 4 != 0)); then
  echo ""
fi