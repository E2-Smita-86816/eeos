#!/bin/bash

echo -e -n "Enter year : "
read year

if [ `expr $year % 4` -eq 0 -a `expr $year % 100` -ne 0 -o `expr $year % 4` -eq 0 ]
then
	echo "Year is leap year : $year"
else
	echo "year is not leap year : $year"
fi

