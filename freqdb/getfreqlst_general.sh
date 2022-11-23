#!/bin/bash

# simple script for downloading frequeancy dictionary from: http://practicalcryptography.com/cryptanalysis/letter-frequencies-various-languages/
# all right reserved by practicalcryptography.com
# (this script author does not have any responsibility for the downloaded data)

ENGLISH="english"
GERMAN="german"

echo "input language: (0):English, (1):German"
read input

if [ $input = '0' ] || [ $input = "E" ] || [ $input = "e" ]; then
    language=${ENGLISH}
elif [ $input = '1' ] || [ $input = "G" ] || [ $input = "g" ]; then
    language=${GERMAN}
else
    echo "invalid input"
    exit
fi

baseurl="http://practicalcryptography.com/media/cryptanalysis/files"

echo "${language} frequency dictionary is downloading from ${baseurl}..."

# monograms
sleep 1

rm ${language}_monograms.txt
wget -q ${baseurl}/${language}_monograms.txt

# bigrams
sleep 1
rm ${language}_bigrams.txt
if [ "${language}" = "english" ]; then
    wget -q ${baseurl}/${language}_bigrams_1.txt
    mv ${language}_bigrams_1.txt ${language}_bigrams.txt
else
    wget -q ${baseurl}/${language}_bigrams.txt
fi

# trigrams
sleep 1
rm ${language}_trigrams.txt*
wget -q ${baseurl}/${language}_trigrams.txt.zip
unzip ${language}_trigrams.txt
rm ${language}_trigrams.txt.zip

# quadgrams
sleep 1
rm ${language}_quadgrams.txt*
wget -q ${baseurl}/${language}_quadgrams.txt.zip
unzip ${language}_quadgrams.txt
rm ${language}_quadgrams.txt.zip


sha256sum ${language}*.txt
