#ifndef __SLEEPYGB_H
#define __SLEEPYGB_H

#include <functional>
#include <vector>
#include <cstdint>
#include <string>

// v is var
// b is bit nr.
// c is condition
#define SET_BIT(v, b) (v |= (1 << (b)))
#define BIT_SET(v, b) ((v) | (1 << (b)))
#define RESET_BIT(v, b) (v &= ~(1 << (b)))
#define BIT_RESET(v, b) ((v) & ~(1 << (b)))
#define SET_BIT_IF(v, b, c) (v = (c) ? ((v) | (1 << b)) : ((v) & ~(1 << (b))))

namespace gb {
	// worst possible implementation of a mmu
	// do not copy
	struct MemoryRegion {
		std::function<void(uint16_t, uint8_t)> write;
		std::function<uint8_t(uint16_t)> read;
		uint16_t start, end;
	};
	
	class Memory {
		std::vector<MemoryRegion> mapped;

	public:
		Memory();
		~Memory();

		uint8_t Read8(uint16_t addr);
		uint16_t Read16(uint16_t addr);
		void Write8(uint16_t addr, uint8_t data);
		void Write16(uint16_t addr, uint16_t data);

		int MapMemory(MemoryRegion m);
		void UnmapMemory(int id);
	};
	
	// this is so bad
	class CPU {
		Memory *mem;

	public:
		union {
			uint16_t af, bc, de, hl;
			struct {
				uint8_t l, h, e, d, c, b, f, a;
			};
		};

		uint16_t pc, sp;
		unsigned cycles_left;

		CPU(Memory *memory);
		void ExecuteCycle();
	};

	// the main class
	class SleepyGB {
		CPU *cpu;
		Memory *memory;
		uint8_t *cartridge; // i should move this to a separate class tbh

	public:
		SleepyGB(const std::string &filename);
		~SleepyGB();
	
		void Run();
	};
}

#endif
