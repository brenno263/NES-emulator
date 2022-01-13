//
// Created by b on 1/12/22.
//

#include "Assembler.h"

const std::string Assembler::hexLookup = "0123456789ABCDEF";

std::map<uint16_t, std::string> Assembler::Disassemble(Bus &bus, uint16_t start, uint16_t end)
{
	//uint8_t value, lo, hi = 0x00;
	std::map<uint16_t, std::string> lines;

	uint32_t addr = start;
	uint32_t line_address;
	Cpu::Instruction inst;
	uint8_t high, low = 0x00;

	auto nextByte = [&addr, &bus]() -> uint8_t {
		return bus.read(addr++);
	};

	auto nextInstruction = [&nextByte]() -> Cpu::Instruction {
		return Cpu::lookup[nextByte()];
	};

	while (addr < end)
	{
		line_address = addr;
		inst = nextInstruction();
		auto addrmode = inst.addrmode;
		std::string out = inst.name;

		if (addrmode == &Cpu::IMP)
		{
			out += " {IMP}";
		} else if (addrmode == &Cpu::IMM)
		{
			low = nextByte();
			out += " #$" + Hex(low) + " {IMM}";
		} else if (addrmode == &Cpu::ZP0)
		{
			low = nextByte();
			out += " $" + Hex(low), + " {ZP0}";
		} else if (addrmode == &Cpu::ZPX)
		{
			low = nextByte();
			out += " $" + Hex(low), + ",X {ZP0}";
		} else if (addrmode == &Cpu::ZPY)
		{
			low = nextByte();
			out += " $" + Hex(low), + ",Y {ZP0}";
		} else if (addrmode == &Cpu::REL)
		{
			low = nextByte();
			int8_t offset = (int8_t)low;
			out += " $" + Hex(low) + " [$" + Hex(addr + offset, 2) + "] {REL}";
		} else if (addrmode == &Cpu::ABS)
		{
			low = nextByte();
			high = nextByte();
			out += " $" + Hex(high << 8 | low, 2) + " {ABS}";
		} else if (addrmode == &Cpu::ABX)
		{
			low = nextByte();
			high = nextByte();
			out += " $" + Hex(high << 8 | low, 2) + ",X {ABS}";
		} else if (addrmode == &Cpu::ABY)
		{
			low = nextByte();
			high = nextByte();
			out += " $" + Hex(high << 8 | low, 2) + ",Y {ABS}";
		} else if (addrmode == &Cpu::IND)
		{
			low = nextByte();
			high = nextByte();
			out += " ($" + Hex(high << 8 | low, 2) + ") {IND}";
		} else if (addrmode == &Cpu::IZX)
		{
			low = nextByte();
			out += " ($" + Hex(low) + ",X) {IZX}";
		} else if (addrmode == &Cpu::IZY)
		{
			low = nextByte();
			out += " ($" + Hex(low) + "),Y {IZY}";
		}

		lines[line_address] = out;
	}

	return lines;
}

std::string Assembler::Hex(uint32_t decimal, uint8_t bytes)
{
	std::string out;
	//iterate over 4-bit words
	for(int i = bytes * 2 - 1; i >= 0; i--)
	{
		out += hexLookup[(decimal >> i * 4) & 0x000F];
	}

	return out;
}
