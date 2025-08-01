/*
 * AWS Graviton4 CPU support  
 * Based on ARM Cortex-A78/Neoverse cores
 */

#include <startup.h>

struct aarch64_cpuid	cpuid_graviton4 = {
	.midr = 0x4100d4a0,  // Graviton4 specific MIDR
	.name = "AWS-Graviton4",
};