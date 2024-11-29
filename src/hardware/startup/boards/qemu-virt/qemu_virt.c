/*
 * Copyright (c) 2024, Joe Xue(lgxue@hotmail.com)
 */

#include <startup.h>
#include <aarch64/gic.h>
#include <sys/libfdt_private.h>

void init_raminfo(void)
{
    /* Don't let QNX flush the FDT, we use it later */
    avoid_ram((paddr_t)fdt, fdt_size);

    init_raminfo_fdt();
}

void init_asinfo(const unsigned mem)
{
}

void init_intrinfo(void)
{
	int node = -1;
    paddr_t gicd = NULL_PADDR, gicr = NULL_PADDR, gits = NULL_PADDR;
    size_t gicr_size, anyone;

    node = fdt_find_node(fdt, node, NULL, "arm,gic-v3");
    if (node > 0) {
        fdt_get_reg64(fdt, node, 0, &gicd, &anyone);
        fdt_get_reg64(fdt, node, 1, &gicr, &gicr_size);

        node = fdt_find_node(fdt, node, NULL, "arm,gic-v3-its");
        if (node > 0) {
            fdt_get_reg64(fdt, node, 0, &gits, &anyone);
        }
        gic_v3_set_paddr_range(gicd, gicr, gicr_size, gits);
        gic_v3_initialize();
    }
}
