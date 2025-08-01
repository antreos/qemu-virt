/*
 * Generic ARM64 CPU fallback support
 * Used when specific CPU ID is not recognized
 */

#include <startup.h>

struct aarch64_cpuid	cpuid_generic = {
	.midr = 0x00000000,  // Will match any CPU as fallback
	.name = "Generic-ARM64",
};