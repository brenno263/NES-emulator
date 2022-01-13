#include <iostream>
#include <sstream>
#include "Bus.h"
#include "Cpu.h"
#include "Assembler.h"

int main()
{
	Bus nesbus;

	/** load program
	 * (place at addr 0x8000)
	 * *=$8000
			LDX #10
			STX $0000
			LDX #3
			STX $0001
			LDY $0000
			LDA #0
			CLC
			loop
			ADC $0001
			DEY
			BNE loop
			STA $0002
			NOP
			NOP
			NOP
	 */

	std::stringstream ss;
	//assembled code
	ss << "A2 0A 8E 00 00 A2 03 8E 01 00 AC 00 00 A9 00 18 6D 01 00 88 D0 FA 8D 02 00 EA EA EA";
	uint16_t nOffset = 0x8000;

	//take each byte of hex and write it to ram as a uint8_t
	while(!ss.eof())
	{
		std::string str;
		ss >> str;
		uint8_t int8 = (uint8_t)std::stoul(str, nullptr, 16);
		nesbus.ram[nOffset] = int8;
		nOffset++;
	}

	std::cout << Assembler::IntToHexString(0xABCD, 2) << std::endl;

	auto map = Assembler::Disassemble(nesbus, 0x8000, 0x8020);

	for(std::pair<uint16_t, std::string> pair: map)
	{
		std::cout << Assembler::IntToHexString(pair.first, 2) << " " << pair.second << std::endl;
	}

	std::cout << "Hello, World!" << std::endl;
	return 0;
}
