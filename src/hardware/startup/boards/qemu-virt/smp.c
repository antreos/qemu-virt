/*
 * Copyright (c) 2024, Joe Xue(lgxue@hotmail.com)
 */

#include <startup.h>

unsigned board_smp_num_cpu(void)
{
    return fdt_num_cpu();
}

void board_smp_init(struct smp_entry *smp, const unsigned num_cpus)
{
    smp->send_ipi = (void *)&sendipi_gic_v3_sr;
}

int board_smp_start(const unsigned cpu, void (*start)(void))
{
    return 1;
}

unsigned board_smp_adjust_num(const unsigned cpu)
{
    return cpu;
}
