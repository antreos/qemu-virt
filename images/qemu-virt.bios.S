/*
 * Copyright (c) 2024, Joe Xue(lgxue@hotmail.com)
 *
 * This is a very simple BIOS for QEMU VIRT machine to boot QNX ifs image.
 * It just does two things:
 * 1. Print the logo to indicate it is running correctly;
 * 2. Set the fdt address which from QEMU to register x0, then jump to the ifs
 *    image address.
 *
 * The ifs image is loaded by QEMU start argument:
 *   -device loader,file=ifs-$(BOARD).bin,addr=$(IMAGE_LOAD_ADDR),force-raw=true
 *
 * Why not U-boot? Convenience!
 */

_start:
	ldr  x0,  =0x9000000
	adr  x1,  _logo

_print_logo:
    ldrb w2, [x1], #1
    cbz  w2, _boot_ifs
    str  w2, [x0]
    b    _print_logo

_boot_ifs:
	ldr  x0,  =0x40000000
	ldr  x19, =0x40200000
	br   x19

_logo:
.ascii "                   ___           ___\n"
.ascii "                  /\\  \\         /|  |\n"
.ascii "     ___          \\:\\  \\       |:|  |\n"
.ascii "    /\\  \\          \\:\\  \\      |:|  |\n"
.ascii "   /::\\  \\     _____\\:\\  \\   __|:|__|\n"
.ascii "  /:/\\:\\  \\   /::::::::\\__\\ /::::\\__\\_____\n"
.ascii " /:/ /::\\  \\  \\:\\~~\\~~\\/__/ ~~~~\\::::/___/\n"
.ascii "/:/_/:/\\:\\__\\  \\:\\  \\           |:|~~|\n"
.ascii "\\:\\/:/  \\/__/   \\:\\  \\          |:|  |\n"
.ascii " \\::/  /         \\:\\__\\         |:|__|\n"
.ascii "  \\/__/           \\/__/         |/__/\n"
.ascii "\n"
.ascii "     QEMU VIRT BIOS for QNX ifs image\n"
.ascii "\n"
.byte 0
