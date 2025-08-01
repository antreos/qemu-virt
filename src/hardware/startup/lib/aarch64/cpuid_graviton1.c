/*
 * AWS Graviton (First Generation) CPU support
 * Based on ARM Cortex-A72 cores (16 cores @ 2.3GHz)
 * Used in AWS A1 instances
 */

#include <startup.h>

struct aarch64_cpuid	cpuid_graviton1 = {
	.midr = 0x4100d080,  // ARM Cortex-A72 MIDR value
	.name = "AWS-Graviton1",
};