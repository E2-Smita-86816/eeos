#!/bin/bash

echo "1.Date"
echo "2.Cal"
echo "3.Ls"
echo "4.Pwd"
echo "5.Exit"

echo -n -e "Enter choice :"
read choice

case $choice in
		1)	echo "Date : $(date)"
			;;

		2)  echo "Enter the calender year :"
			read year
			cal $year
			;;

		3)  echo "List :"
			ls
			;;

		4)  echo "Present working directory :"
			pwd
			;;

		5)  exit
			;;

		*)  echo "Invalid choice"
	
esac
