

socat -t0  STDIO,raw,echo=0,escape=0x03,nonblock=1  file:/dev/ttyUSB0,b19200,cs8,parenb=0,cstopb=0,clocal=0,raw,echo=0,setlk,flock-ex-nb,nonblock=1
