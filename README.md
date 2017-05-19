# CC13:
CarolinaCon13 Badge Jank

## Files: 
- CC13 Badge.pdf - Detailed badge assembly guide
- ino files


## If you need to setup an Arduino build environment:

Download the latest Arduino archive from https://www.arduino.cc/en/Main/Software

Uncompress archive: xz --decompress arduino-1.8.2-linux64.tar.xz

As root untar in /usr/local and create symlink:
```
    # cd /usr/local
    # tar xvf ~/Downloads/arduino-1.8.2-linux64.tar
    # ln -s arduino-1.8.2/ arduino
```

As regular user, download badge code into home directory (--recursive will pull down dependency projects):
```
    cd
    git clone --recursive https://github.com/lockfale/CC13.git
```
