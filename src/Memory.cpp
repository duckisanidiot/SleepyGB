#include <SleepyGB.h>

namespace gb {
	Memory::Memory() {}
	Memory::~Memory() {}

	uint8_t Memory::Read8(uint16_t addr) {
		for (MemoryRegion r : mapped) {
			if (r.start <= addr && addr <= r.end) {
				return r.read(addr);
			}
		}

		return 0;
	}
	
	uint16_t Memory::Read16(uint16_t addr) {
		return Read8(addr) | (Read8(addr + 1) << 8);
	}

	void Memory::Write8(uint16_t addr, uint8_t data) {
		for (MemoryRegion r : mapped) {
			if (r.start <= addr && addr <= r.end) {
				r.write(addr);
				break;
			}
		}
	}

	uint16_t Memory::Write16(uint16_t addr, uint16_t data) {
		Write8(addr, data & 0xFF);
		Write8(addr + 1, data >> 8);
	}
	
	int Memory::MapMemory(MemoryRegion r) {
		mapped.push_back(r);
		return mapped.size() - 1;
	}

	void Memory::UnmapMemory(int id) {
		mapped.erase(mapped.begin() + id);
	}
}
