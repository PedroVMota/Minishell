#!/bin/bash

while true; do
    # Set the name of the current folder
    current_folder="."

    # Set the name of the backup folder
    backup_folder=".temp"

    # Check if the backup folder exists
    if [ ! -d "$backup_folder" ]; then
        # Create the backup folder if it doesn't exist
        mkdir "$backup_folder"
    fi

    # Copy everything in the current folder that is not a .o file or inside the .git folder to the backup folder
    find "$current_folder" -type f ! -name "*.o" ! -path "./.git/*" -exec cp {} "$backup_folder" \;

    # Print a message indicating that the backup was created
    echo "Backup created: $backup_folder"

    # Wait for 30 seconds
    for i in {1..30}; do
        echo $i Seconds
        sleep 1
    done
done