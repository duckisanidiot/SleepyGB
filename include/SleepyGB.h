#ifndef __SLEEPYGB_H
#define __SLEEPYGB_H

#include <functional>
#include <vector>
#include <cstdint>

namespace gb {
	// worst possible implementation of a mmu
	// do not copy
	struct MemoryRegion {
		std::function<void(uint16_t, uint8_t)> write;
		std::function<uint16_t(uint8_t)> read;
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
		uint16_t Write16(uint16_t addr, uint16_t data);

		int MapMemory(MemoryRegion m);
		void UnmapMemory(int id);
	};
}

#endif
