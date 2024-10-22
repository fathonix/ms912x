ms912x-y := \
	ms912x_registers.o \
	ms912x_connector.o \
	ms912x_transfer.o \
	ms912x_drv.o

obj-m := ms912x.o

ccflags-y += -Wno-error
