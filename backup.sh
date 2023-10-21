#!/bin/bash

# Get the name of the current file
filename=$(basename "$0")

# Get the name of the project directory
project=$(basename "$(dirname "$(dirname "$0")")")

# Create the backup directory if it doesn't exist
mkdir -p "../backup/$project"

# Copy the current file to the backup directory
cp "$filename" "../backup/$project/$filename.bak"