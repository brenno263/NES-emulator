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

	/**
	 * Convert an integer of up to four bytes into a hex string
	 * @param decimal decimal number to be converted
	 * @param bytes how many bytes to convert
	 * @return
	 */
	static std::string Hex(uint32_t decimal, uint8_t bytes = 1);
};


#endif //NES_ASSEMBLER_H
