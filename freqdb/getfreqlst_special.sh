#!/bin/bash

# simple script for downloading frequeancy dictionary from: http://www.bytereef.org/dict/
# all right reserved by bytereef.org
# (this script author does not have any responsibility for the downloaded data)

baseurl="http://www.bytereef.org/dict/"

echo "frequency dictionary is downloading from ${baseurl}..."

# bigrams
sleep 1
rm german_special_bigrams.txt
wget ${baseurl}/00bigr.cur
mv 00bigr.cur german_special_bigrams.txt

# trigrams
sleep 1
rm german_special_trigrams.txt
wget -q ${baseurl}/00trigr.cur
mv 00trigr.cur german_special_trigrams.txt

sha256sum german_special_*.txt
