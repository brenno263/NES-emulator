//
// Created by b on 1/12/22.
//

#ifndef NES_ASSEMBLER_H
#define NES_ASSEMBLER_H

#include <vector>
#include <string>
#include <cstdint>
#include <array>
#include <map>
#include "Cpu.h"
#include "Bus.h"

class Assembler
{
public:
	static const std::string hexLookup;

	static std::map<uint16_t, std::string> Disassemble(Bus &bus, uint16_t start, uint16_t end);
	static std::string IntToHexString(uint32_t word, uint8_t bytes);
};


#endif //NES_ASSEMBLER_H
