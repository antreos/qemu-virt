/*
 * Copyright (c) 2024, Joe Xue(lgxue@hotmail.com)
 */

#include <startup.h>
#include <aarch64/gic.h>
#include <sys/libfdt_private.h>

void init_raminfo(void)
{
    kprintf("QEMU-VIRT: === BOOT STAGE: init_raminfo() ===\n");
    /* Don't let QNX flush the FDT, we use it later */
    avoid_ram((paddr_t)fdt, fdt_size);

    init_raminfo_fdt();
    kprintf("QEMU-VIRT: init_raminfo() completed\n");
}

void init_asinfo(const unsigned mem)
{
    kprintf("QEMU-VIRT: === BOOT STAGE: init_asinfo() ===\n");
    kprintf("QEMU-VIRT: init_asinfo() completed (no-op)\n");
}

void init_intrinfo(void)
{
	int node = -1;
    paddr_t gicd = NULL_PADDR, gicr = NULL_PADDR, gits = NULL_PADDR;
    size_t gicr_size, anyone;

    kprintf("QEMU-VIRT: === BOOT STAGE: init_intrinfo() - CRITICAL FOR KVM ===\n");
    
    node = fdt_find_node(fdt, node, NULL, "arm,gic-v3");
    kprintf("QEMU-VIRT: GICv3 FDT node search result: %d\n", node);
    
    if (node > 0) {
        kprintf("QEMU-VIRT: Found GICv3 node, reading register addresses\n");
        fdt_get_reg64(fdt, node, 0, &gicd, &anyone);
        fdt_get_reg64(fdt, node, 1, &gicr, &gicr_size);
        kprintf("QEMU-VIRT: GICD addr=0x%lx, GICR addr=0x%lx, size=0x%lx\n", 
                (unsigned long)gicd, (unsigned long)gicr, (unsigned long)gicr_size);

        node = fdt_find_node(fdt, node, NULL, "arm,gic-v3-its");
        kprintf("QEMU-VIRT: GICv3-ITS FDT node search result: %d\n", node);
        if (node > 0) {
            fdt_get_reg64(fdt, node, 0, &gits, &anyone);
            kprintf("QEMU-VIRT: GITS addr=0x%lx\n", (unsigned long)gits);
        }
        
        kprintf("QEMU-VIRT: About to call gic_v3_set_paddr_range\n");
        gic_v3_set_paddr_range(gicd, gicr, gicr_size, gits);
        kprintf("QEMU-VIRT: gic_v3_set_paddr_range completed\n");
        
        kprintf("QEMU-VIRT: About to call gic_v3_initialize - THIS IS WHERE KVM LIKELY HANGS\n");
        gic_v3_initialize();
        kprintf("QEMU-VIRT: gic_v3_initialize completed successfully - KVM BOOT SUCCESS!\n");
    } else {
        kprintf("QEMU-VIRT: ERROR - No GICv3 node found in device tree\n");
    }
    kprintf("QEMU-VIRT: Interrupt controller initialization complete\n");
}
