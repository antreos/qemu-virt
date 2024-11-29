/*
 * Copyright (c) 2024, Joe Xue(lgxue@hotmail.com)
 */

#include <startup.h>
#include <arm/pl011.h>
#include <hw/hwinfo_private.h>
#include <drvr/hwinfo.h>

int main(const int argc, char ** const argv)
{
    int opt;
    const struct debug_device debug_devices[] = {
        {	.name = "pl011",
            .defaults[DEBUG_DEV_CONSOLE] = "9000000^2.115200.24000000", /* uart 3*/
            .init = init_pl011,
            .put = put_pl011,
            .callouts[DEBUG_DISPLAY_CHAR] = &display_char_pl011,
            .callouts[DEBUG_POLL_KEY] = &poll_key_pl011,
            .callouts[DEBUG_BREAK_DETECT] = &break_detect_pl011,
        },
    };

    /* Initialize the default debug interface for now. */
    select_debug(debug_devices, sizeof(debug_devices));

    while ((opt = getopt(argc, argv, COMMON_OPTIONS_STRING)) != -1) {
        switch (opt) {
            default:
                handle_common_option(opt);
                break;
        }
    }

    init_raminfo();

    /* Enable Hypervisor if requested (and possible) */
    hypervisor_init(0);

    init_smp();

    if (shdr->flags1 & STARTUP_HDR_FLAGS1_VIRTUAL) {
        init_mmu();
    }

    init_intrinfo();

    init_qtime();

    init_cacheattr();

    init_cpuinfo();

    init_hwinfo();

    init_system_private();

    print_syspage();

    return 0;
}
