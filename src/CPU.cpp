#include <SleepyGB.h>
#include <exceptions>

namespace gb {
	CPU::CPU(Memory *memory) {
		this->mem = memory;
		cycles_left = 0;

		AddOpcode("00000000", [] (CPU *cpu, Memory *, uint8_t) { cpu->cycles_left += 4; });
		// todo: finish
	}

	void CPU::AddOpcode(const std::string &fmt, std::function<void(CPU *, Memory *, uint8_t)> func) {
		CPU::opcode o{};
		o.function = func;

		for (unsigned i = 0; i < 8; ++i) {
			switch (fmt[i]) {
				case '0':
					o.mask = (o.mask << 1) | 1;
					o.comp <<= 1;
					break;

				case '1':
					o.mask = (o.mask << 1) | 1;
					o.comp = (o.comp << 1) | 1;
					break;

				case 'x':
					o.mask <<= 1;
					o.comp <<= 1;
					break;
			}
		}

		opcodes.push_back(o);
	}
	
	CPU::Opcode CPU::FindOpcode(uint8_t op) {
		for (CPU::Opcode o : opcodes) {
			if (op & o.mask == o.comp) {
				return o;
			}
		}

		throw std::runtime_error("Opcode does not exist?");
	}

	void CPU::ExecuteCycle() {
		if (cycles_left > 0) {
			cycles_left--;
			return;
		}

		auto byte = this->mem->Read8(this->pc++);
		auto op = FindOpcode(byte);
		op.function(this, this->mem, byte);
	}
}
