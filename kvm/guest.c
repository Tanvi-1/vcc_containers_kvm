#include <stddef.h>
#include <stdint.h>

static void outb(uint16_t port, uint8_t value) {
	asm("outb %0,%1" : /* empty */ : "a" (value), "Nd" (port) : "memory");
}

static inline void out(uint16_t port, uint32_t value) {

  asm("out %0,%1" : /* empty */ : "a" (value), "Nd" (port) : "memory");

}

static inline uint32_t inb(uint16_t port) {

  uint32_t ret;

  asm("in %1, %0" : "=a"(ret) : "Nd"(port) : "memory" );

  return ret;

}


void HC_print8bit(uint8_t val)
{
	outb(0xE9, val);
}

void HC_print32bit(uint32_t val)
{
	out(0xEA, val);	
}

uint32_t HC_numExits()
{
	// Fill in here
	uint32_t exitcnt = inb(0xEB);
	return exitcnt;
		// Remove this
}

void HC_printStr(char *str)
{
	// Fill in here
	uintptr_t addr = (uintptr_t)str;
	out(0xEC,addr);
	//str++;		// Remove this
}

uint32_t HC_gvaToHva(uint32_t gva)
{
	// Fill in here
	out(0xED,gva);
	uint32_t hva = inb(0xEE);
	return hva;
	// gva++;		// Remove this
	// return 0;	// Remove this
}

uint32_t HC_getTimestamp()
{
	// Fill in here
	uint32_t timest=inb(0xEF);

	return timest;	// Remove this
	//return 0;
}

void
__attribute__((noreturn))
__attribute__((section(".start")))
_start(void) {
	const char *p;

	for (p = "Hello, world!\n"; *p; ++p)
		HC_print8bit(*p);


	/*----------Don't modify this section. We will use grading script---------*/
	/*---Your submission will fail the testcases if you modify this section---*/
	HC_print32bit(2048);
	HC_print32bit(4294967295);

	uint32_t num_exits_a, num_exits_b;
	num_exits_a = HC_numExits();

	char *str = "CS 695 Assignment 3\n";
	HC_printStr(str);

	num_exits_b = HC_numExits();

	HC_print32bit(num_exits_a);
	HC_print32bit(num_exits_b);

	uint32_t hva;
	hva = HC_gvaToHva(1024);
	HC_print32bit(hva);
	hva = HC_gvaToHva(4294967295);
	HC_print32bit(hva);

	uint32_t tsc;
	tsc = HC_getTimestamp();
	HC_print32bit(tsc);
	/*------------------------------------------------------------------------*/

	*(long *) 0x400 = 42;

	for (;;)
		asm("hlt" : /* empty */ : "a" (42) : "memory");
}
