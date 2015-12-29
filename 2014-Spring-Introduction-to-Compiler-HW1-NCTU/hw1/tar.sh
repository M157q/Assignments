#!/bin/bash
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

if [ "$#" -lt 3 ]; then
    echo "Usage: "
    echo "./tar.sh source_directory studentID1_studentID2 (all student IDs in your team) version_number"
    echo "Example: ./tar.sh hw1 12345_12346 ver1"
    echo "Output: 12345_12346_ver1.tar.bz2 (submit this file)"
else
    tar -jpc -f $2_$3.tar.bz2 $1
fi

exit 0
