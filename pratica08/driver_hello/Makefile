# Makefile for driver
# if KERNELRELEASE is defined, we’ve been invoked from the
# kernel build system and can use its language.
ifneq (${KERNELRELEASE},)
	obj-m := hello.o
# Otherwise we were called directly from the command line.
# Invoke the kernel build system.
else
	KERNEL_SOURCE := ${HOME}/8Semestre/TPSE2/lab03/linux
	PWD := $(shell pwd)
	# Linux kernel 5.10 (one line)
	CC=${HOME}/8Semestre/TPSE2/lab02/toolchain/bin/arm-linux-
	BUILD=boneblack
	address=0x80008000
	CORES=15
	image=uImage
	PUBLIC_DRIVER_PWD=${HOME}/8Semestre/TPSE2/lab05/buildrootfs/lib/modules/5.10.131/kernel/drivers/hello
default:
# Trigger kernel build for this module
	${MAKE} -C ${KERNEL_SOURCE} M=${PWD} -j${CORES} ARCH=arm \
	LOCALVERSION=${BUILD} CROSS_COMPILE=${CC} LOADADDR=${address} \
	${image} modules
	# copy result to public folder
	sudo cp *.ko ${PUBLIC_DRIVER_PWD}
	@echo >&2 "Done";
clean:
	${MAKE} -C ${KERNEL_SOURCE} M=${PWD} clean
endif