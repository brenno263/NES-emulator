//
// Created by b on 1/12/22.
//

#ifndef NES_BUS_H
#define NES_BUS_H

#include <cstdint>
#include <array>
#include "Cpu.h"

class Bus
{
public:
	Bus();
	~Bus();

public: //Devices on the bus
	Cpu cpu;
	//temporary fake ram on the stack
	std::array<uint8_t, 64 * 1024> ram;

public: //Bus Read & Write
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool readOnly = false);
};


#endif //NES_BUS_H
