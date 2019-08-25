#include <SleepyGB.h>
#include <fstream>

namespace gb {
	SleepyGB::SleepyGB(const std::string &filename) {
		std::ifstream file(filename, std::ios::binary | std::ios::ate);
		size_t filesize = file.tellg();
		file.seek(0, file.beg);
		this->cartridge = new uint8_t[filesize];
		file.read(this->cartridge, filesize);
		file.close();

		MemoryRegion mr;
		mr.start = 0;
		mr.end = 0x8000;
		mr.read = [this->cartridge] (uint16_t addr) { return this->cartridge[addr]; };
		mr.write = [] (uint16_t, uint16_t) {};
		this->memory = new Memory;
		this->memory->MapMemory(mr);

		this->cpu = new CPU(this->memory);
		// todo: finish
	}

	SleepyGB::~SleepyGB() {
		delete this->cpu;
		delete this->memory;
		delete []this->cartridge;
	}

	void SleepyGB::ExecuteCycle() {
		// todo: finish
	}
}
