#!/bin/bash

echo "Enter Basic Salary:"
read basic

echo "Enter TA:"
read ta

gs=$(bc -l <<< "$basic + $ta + (0.10 * $basic)")

echo "Gross Salary is $gs"

