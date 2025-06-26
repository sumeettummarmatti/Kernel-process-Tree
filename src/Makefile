# Kernel module name
obj-m += kernul.o

# Kernel build path
KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

# Default target: build both kernel module and user binary
all: module user

# Build the kernel module
module:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# Build the user-space program
user:
	gcc -o user user.c

# Insert the kernel module
load:
	sudo insmod kernul.ko

# Run the user-space program
run:
	./user

# Show kernel logs (requires sudo)
check:
	sudo dmesg | tail -30

# Unload the kernel module
unload:
	sudo rmmod kernul

# Clean all build artifacts
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f user
