#include <SleepyGB.h>

namespace gb {
	CPU::CPU(Memory *memory) {
		this->mem = memory;
		cycles_left = 0;
		// todo: finish
	}

	void CPU::ExecuteCycle() {
		if (cycles_left > 0) {
			cycles_left--;
			return;
		}

		auto op = this->mem->Read8(this->pc++);
		// todo: finish
	}
}
