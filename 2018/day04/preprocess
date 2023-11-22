#!/bin/bash

# Sort handles dates in the format that was given, which was fantastic
# Then strip away the brackets
cat "$1" | sort | sed 's/\[//g;s/\]//g'
