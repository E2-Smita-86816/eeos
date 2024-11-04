#Write a shell script to accept a filename as argument and displays the last modification time if the file exists and a suitable message if it doesn’t exist.

#!/bin/bash

read -p "Enter filename: " file
if [ -f "$file" ]; then
	echo "Last modification time: $(stat -c %y "$file")"
else
echo "File does not exists."
fi
