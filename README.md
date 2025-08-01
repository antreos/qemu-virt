# QEMU Virtual Machine BSP for QNX

This is a QNX minimal BSP for aarch64 QEMU Virt machine. 

Run QNX on a Qemu aarch64 virt machine with networking, serial port etc.

You can use this to learn QNX OS, driver writting, app writting.

A very tiny bootloader called Q-Boot is included to boot QNX Ifs image on QEMU Virt. You don't have to care it, make run will do all job.

## Dependencies

* qemu-system-arm

* QNX software center (to download the QNX software packages) , choose target: aarch64

* SDP (QNX Software Development Platform)
  
* Virtulization Drivers for SDP
![image](https://github.com/user-attachments/assets/55e33750-238d-41df-9fc4-3825a3950407)


## How to use

After you installed SDP and related packages.
```
cd ${QNX_SDP_DIR}/bsp
git clone git@github.com:joexue/qemu-virt.git
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

## Screenshot
![image](https://github.com/user-attachments/assets/08565842-612e-46f4-9f72-64707ad484e7)


If you need more flexible networking, please execute "make run-tap", it will use QEMU tap networking mode, need sudo permision although.

More information about QEMU networking mode: https://wiki.qemu.org/Documentation/Networking

## KVM Acceleration

For ARM64 hosts, you can use hardware acceleration with KVM:

```bash
make run-kvm        # Basic KVM with user networking
make run-kvm-sudo   # KVM with enhanced networking (requires sudo)
make run-kvm-tap    # KVM with TAP networking (requires sudo)
```

KVM acceleration provides significant performance improvements on ARM64 hosts such as AWS Graviton instances.

## TODO
The PCI is not available yet causes massive devices/drivers cannot be used.

## Verification
Tested under SDP 8.0.0
