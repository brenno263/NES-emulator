//
// Created by b on 1/12/22.
//

#include "Bus.h"

Bus::Bus()
{
	//clear ram contents
	for(auto &i : ram) i = 0x00;

	cpu.ConnectBus(this);
}

Bus::~Bus()
{

}

void Bus::write(uint16_t addr, uint8_t data)
{
	//we only have ram right now, but this makes sure the addr is in the right range.
	if(addr >= 0x0000 && addr <= 0xFFFF)
		ram[addr] = data;
}

uint8_t Bus::read(uint16_t addr, bool readOnly)
{
	return 0;
}
