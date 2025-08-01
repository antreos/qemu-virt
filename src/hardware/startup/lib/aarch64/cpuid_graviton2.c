/*
 * AWS Graviton2 CPU support
 * Based on ARM Neoverse-N1 core
 */

#include <startup.h>

struct aarch64_cpuid	cpuid_graviton2 = {
	.midr = 0x4100d0c0,  // Same as Neoverse-N1
	.name = "AWS-Graviton2",
};