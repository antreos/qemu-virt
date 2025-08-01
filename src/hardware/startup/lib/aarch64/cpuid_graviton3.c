/*
 * AWS Graviton3 CPU support
 * Based on ARM Cortex-A76/Neoverse-V1 core
 */

#include <startup.h>

struct aarch64_cpuid	cpuid_graviton3 = {
	.midr = 0x4100d400,  // Same as Neoverse-V1
	.name = "AWS-Graviton3",
};