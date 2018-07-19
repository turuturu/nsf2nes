import sys
from struct import *
args = sys.argv

if __name__ == "__main__":
    nsf_file_name = args[1]
    with open(nsf_file_name, 'rb') as f:
        f.seek(8)
        sys.stdout.write('0x%X ' % unpack('<H', f.read(2))[0])
        sys.stdout.write('0x%X ' % unpack('<H', f.read(2))[0])
        sys.stdout.write('0x%X' % unpack('<H', f.read(2))[0])
        exit()
