# qemu-virt-qnx-bsp
This is a QNX minimal BSP for AARCH64 QEMU VIRT machine.

## How to use

Checkout the source code under QNX SDP BSP directory.
```
cd qemu-virt-qnx-bsp
source ${QNX_SDP}/qnxsdp-env.sh
make
make run
```
The "make run" will start the QEMU and run QNX on an AARCH64 machine which called VIRT.

You need to install qemu-system-aarch64 before run it. Tested under qemu-system-aarch64 8.2 but should work for other versions.

## Networking
When you execute "make run" we use QEMU user mode, which can access from QNX(guest OS) to outside, but cannot access from outside to QNX.

Ping 10.0.2.2(represent your host) is working.

If you need more flexible networking, please execute "make run-tap", it will use QEMU tap mode, need sudo permision although.

More information about QEMU networking mode: https://wiki.qemu.org/Documentation/Networking

## TODO
The PCI is not available yet which causes massive devices/drivers cannot be used.
