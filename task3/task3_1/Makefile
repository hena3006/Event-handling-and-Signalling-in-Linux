
CC=gcc
MAKE=make
KDIR=/lib/modules/$(shell uname -r)/build

#CC=$(TOOLDIR)/i586-poky-linux-gcc
#MAKE=make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)
#KDIR:=/opt/iot-devkit/1.7.2/sysroots/i586-poky-linux/usr/src/kernel

APP = main
  

all:
	
	$(CC) -Wall -o $(APP) main.c -pthread -lm 

clean:
	rm -f *.o
	rm -f $(APP)
