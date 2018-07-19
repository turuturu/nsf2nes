#!/bin/sh

USAGE="Usage: ./build.sh input_nsf_filename output_nes_file_name";
if [ ! $# = 2 ]; then
        echo $USAGE;
        exit;
fi

. config.ini
TMP_FILE=".tmpasm"
NSF_FILE=$1
OUTPUT_FILE=$2

echo "REMOVE HEADER"
HEADER_REMOVED_FILE=${NSF_FILE}.noheader
tail -c +129 ${NSF_FILE} > ${HEADER_REMOVED_FILE}

echo "GENERATE ASM"
cat $TEMPLATE_FILE |
  sed "s/%%__LOAD_ADDR__%%/${LOAD_ADDR}/g" |
  sed "s/%%__INIT_ADDR__%%/${INIT_ADDR}/g" |
  sed "s/%%__PLAY_ADDR__%%/${PLAY_ADDR}/g" |
  sed "s/%%__NSF_FILE__%%/${HEADER_REMOVED_FILE}/g" > $TMP_FILE

echo "assemble!!"
nesasm $TMP_FILE
mv .nes $OUTPUT_FILE
echo "build complete"
# rm $TMP_FILE
