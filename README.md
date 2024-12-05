# QEMU Virtual Machine BSP for QNX

This is a QNX minimal BSP for AARCH64 QEMU VIRT machine.

## How to use

Checkout the source code under QNX SDP BSP directory (tested under SDP 8.0.0) then execute:
```
cd qemu-virt
source ${QNX_SDP_DIR}/qnxsdp-env.sh
make
make run
```
The "make run" will start the QEMU and run QNX on an AARCH64 machine called VIRT.

You need to install qemu-system-aarch64 before run it. Tested under qemu-system-aarch64 8.2 but should work for other versions.

## Networking
When you execute "make run", it uses QEMU user networking mode, which can access from QNX(guest OS) to outside, but cannot access from outside to QNX by default (you can do it by using port forwarding).

Ping 10.0.2.2(represents your host) is working but cannot ping outside world, if you need to do ping test, then execute "make sudo-run".

If you need more flexible networking, please execute "make run-tap", it will use QEMU tap networking mode, need sudo permision although.

More information about QEMU networking mode: https://wiki.qemu.org/Documentation/Networking

## TODO
The PCI is not available yet causes massive devices/drivers cannot be used.
