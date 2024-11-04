#Write a shell script to display only executable files of current directory.

#!/bin/bash

echo "Executable files:"
for file in *; do
if [ -x "$file" ]; then
echo "$file"
fi 
done
