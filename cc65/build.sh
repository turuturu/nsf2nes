#!/bin/bash

USAGE="Usage: ./build.sh [-n -l load_addr -i init_add -p play_addr] src_c_file input_nsf_filename output_nes_file_name";

FLAG_N=0
while getopts hnl:i:p: OPT
do
    case $OPT in
        n)  FLAG_N=1
            ;;
        l)  LOAD_ADDR=$OPTARG
            ;;
        i)  INIT_ADDR=$OPTARG
            ;;
        p)  PLAY_ADDR=$OPTARG
            ;;
        h)  usage_exit
            echo $USAGE;
            exit;
            ;;
        \?) usage_exit
            echo $USAGE;
            exit;
            ;;
    esac
done

shift $((OPTIND - 1))

if [ ! $# = 3 ]; then
        echo $USAGE;
        exit;
fi

. config.ini
TMP_ASM_FILE="tmp.asm"
TMP_CFG_FILE="tmp.cfg"
SRC_FILE=$1
NSF_FILE=$2
OUTPUT_FILE=$3


if [ $FLAG_N = "0" ]; then
  meta_info=`python3 ../nsfmeta.py $NSF_FILE|sed 's/0x//g'`
  LOAD_ADDR=`echo $meta_info | cut -d' ' -f1`
  INIT_ADDR=`echo $meta_info | cut -d' ' -f2`
  PLAY_ADDR=`echo $meta_info | cut -d' ' -f3`
  echo "load to " $LOAD_ADDR
  echo "init addr is " $INIT_ADDR
  echo "play addr is " $PLAY_ADDR
  echo "REMOVE HEADER"
  HEADER_REMOVED_FILE=${NSF_FILE}.noheader
  tail -c +129 ${NSF_FILE} > ${HEADER_REMOVED_FILE}
else
  echo "load to " $LOAD_ADDR
  echo "init addr is " $INIT_ADDR
  echo "play addr is " $PLAY_ADDR
  HEADER_REMOVED_FILE=${NSF_FILE}
fi

echo "GENERATE ASM"
cat $TEMPLATE_ASM_FILE |
  sed "s/%%__LOAD_ADDR__%%/${LOAD_ADDR}/g" |
  sed "s/%%__INIT_ADDR__%%/${INIT_ADDR}/g" |
  sed "s/%%__PLAY_ADDR__%%/${PLAY_ADDR}/g" |
  sed "s/%%__NSF_FILE__%%/${HEADER_REMOVED_FILE}/g" > $TMP_ASM_FILE

echo "GENERATE CFG"
cat $TEMPLATE_CFG_FILE |
  sed "s/%%__LOAD_ADDR__%%/${LOAD_ADDR}/g" |
  sed "s/%%__INIT_ADDR__%%/${INIT_ADDR}/g" |
  sed "s/%%__PLAY_ADDR__%%/${PLAY_ADDR}/g" |
  sed "s/%%__NSF_FILE__%%/${HEADER_REMOVED_FILE}/g" > $TMP_CFG_FILE


echo "compile!!"
echo make OUTPUT_FILE=${OUTPUT_FILE} ASM_FILE=${TMP_ASM_FILE} CFG_FILE=${TMP_CFG_FILE} SRC_FILE=${SRC_FILE}
make OUTPUT_FILE=${OUTPUT_FILE} ASM_FILE=${TMP_ASM_FILE} CFG_FILE=${TMP_CFG_FILE} SRC_FILE=${SRC_FILE}
echo "build complete"
