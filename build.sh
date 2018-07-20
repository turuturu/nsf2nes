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

meta_info=`python3 nsfmeta.py $NSF_FILE`
LOAD_ADDR=`echo $meta_info| cut -d' ' -f1`
INIT_ADDR=`echo $meta_info| cut -d' ' -f2`
PLAY_ADDR=`echo $meta_info| cut -d' ' -f3`
echo "load to " $LOAD_ADDR
echo "init addr is " $INIT_ADDR
echo "play addr is " $PLAY_ADDR
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
