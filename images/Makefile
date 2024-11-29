#Copyright (c) 2024, Joe Xue(lgxue@hotmail.com)

ROOT_DIR := $(notdir $(CURDIR))
ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

# NOTE: This value must match the '[image=<start_addr>]' value in the build file.
IMAGE_LOAD_ADDR = 0x40200000
FDT_ADDR = 0x40000000

HOST_MKIFS := mkifs

BOARD=qemu-virt
INSTALL=../install

.PHONY: all clean run

all: ifs-$(BOARD).bin $(BOARD).bios

ifs-$(BOARD).bin: $(BOARD).build
	$(HOST_MKIFS) -v -r$(INSTALL) $(MKIFSFLAGS) $^ $@

$(BOARD).bios: $(BOARD).bios.o
	$(OC_nto_aarch64_gcc) -O binary $< $@

$(BOARD).bios.o: $(BOARD).bios.S
	$(CC_nto_aarch64_gcc) $< -o $@

run: ifs-$(BOARD).bin $(BOARD).bios
	@qemu-system-aarch64 \
      -M virt,gic-version=3 \
      -cpu cortex-a72 \
      -m 256M \
      -nographic \
      -nic none \
      -netdev user,id=qnxnet \
      -device virtio-net-device,netdev=qnxnet \
      -bios $(BOARD).bios \
      -device loader,file=ifs-$(BOARD).bin,addr=$(IMAGE_LOAD_ADDR),force-raw=true

run-tap:
	@sudo qemu-system-aarch64 \
      -M virt,gic-version=3 \
      -cpu cortex-a72 \
      -m 256M \
      -nographic \
      -nic none \
      -netdev tap,id=qnxnet \
      -device virtio-net-device,netdev=qnxnet \
      -bios $(BOARD).bios \
      -device loader,file=ifs-$(BOARD).bin,addr=$(IMAGE_LOAD_ADDR),force-raw=true

clean:
	$(RM_HOST) ifs-$(BOARD).* $(BOARD).bios $(BOARD).bios.o *.sym
