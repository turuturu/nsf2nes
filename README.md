# nsf2nes

## How to run
### for nesasm

```
cd nesasm;
./build.sh INPUT_NSF_FILE_NAME OUTPUT_NES_FILE_NAME;
```

### for cc65
```
cd cc65;
./build.sh [-n -l load_addr -i init_add -p play_addr] src_c_file input_nsf_filename output_nes_file_name
```

## System Requirements
You will need (4nesasm):
- nesasm
- Python3

You will need (cc65):
- cc65 tool chain
- Python3
