//
// Created by b on 1/12/22.
//

#ifndef NES_CPU_H
#define NES_CPU_H

#include <string>
#include <vector>

//forward declaration
class Bus;

class Cpu
{
public:
	Cpu();
	~Cpu();

	enum Flag
	{
		C = (1 << 0), //Carry Bit			(Unimplemented)
		Z = (1 << 1), //Zero				(Unimplemented)
		I = (1 << 2), //Disable Interrupt	(Unimplemented)
		D = (1 << 3), //Decimal Mode		(Unimplemented)
		B = (1 << 4), //Break				(Unimplemented)
		U = (1 << 5), //Unused				(Unimplemented)
		V = (1 << 6), // Overflow			(Unimplemented)
		N = (1 << 7), // Negative			(Unimplemented)
	};

	uint8_t a = 0x00; //Accumulator
	uint8_t x = 0x00; //X
	uint8_t y = 0x00; //Y
	uint8_t stkp = 0x00; //Stack Pointer
	uint16_t pc = 0x0000; //Program Counter
	uint8_t status; //Status flags

	void ConnectBus(Bus *b);

	Bus *bus = nullptr;

private:
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint8_t addr);

	// helper functions to access status register
	uint8_t GetFlag(Flag f);
	void SetFlag(Flag f, bool v);

public:
	void clock(); //run a clock cycle
	void reset(); //reset
	void irq(); //interrupt request signal
	void nmi(); //non-maskable interrupt request signal

	uint8_t fetch();
	uint8_t fetched = 0x00;

	uint16_t addr_abs = 0x0000;
	uint16_t addr_rel = 0x0000;
	uint8_t opcode = 0x00;
	uint8_t cycles = 0;

public:

	struct Instruction
	{
		std::string name;
		uint8_t (Cpu::*operate)(void) = nullptr;
		uint8_t (Cpu::*addrmode)(void) = nullptr;
		uint8_t cycles = 0;
	};

	static const std::vector<Instruction> lookup;

	//Addressing Modes

	/**
	 * Implied:\n
	 * This instruction either needs no additional data or uses the accumulator.
	 * @return
	 */
	uint8_t IMP();

	/**
	 * Immediate:\n
	 * This instruction expects the next byte to be read in as a value
	 * @return
	*/
	uint8_t IMM();

	/**
	 * Zero Page:\n
	 * This instruction uses data in the zeroth page, so it needs only the lower byte of the address.
	 * @return
	 */
	uint8_t ZP0();

	/**
	 * Zero Page with X Offset:\n
	 * Similar to the Zero Page mode, but the value in the X register is added to our single byte address.
	 * @return
	 */
	uint8_t ZPX();

	/**
	 * Zero Page with Y Offset:\n
	 * Similar to the Zero Page mode, but the value in the Y register is added to our single byte address.
	 * @return
	 */
	uint8_t ZPY();

	/**
	 * Relative:\n
	 * This address mode is exclusively for branch insructions. Takes a signed offset byte and targets the PC + offset
	 * Note that this is restricted to [PC - 128, PC + 127]
	 * @return
	 */
	uint8_t REL();

	/**
	 * Absolute:\n
	 * A full two byte address is used
	 * @return
	 */
	uint8_t ABS();

	/**
	 * Absolute with X Offset:\n
	 * Similar to Absolute, but add X register to supplied two byte address
	 * @return
	 */
	uint8_t ABX();

	/**
	 * Absolute with Y Offset:\n
	 * Similar to Absolute, but add Y register to supplied two byte address
	 * @return
	 */
	uint8_t ABY();

	/**
	 * Indirect:\n
	 * The supplied two byte address points to another two byte address, which is used.
	 *
	 * This address type contains a bug where if the low byte of our supplied address is 0xFF, the high byte addresses
	 * the next page. Instead of working properly, in this case the high byte wraps around and reads the start of the page.
	 * @return
	 */
	uint8_t IND();

	/**
	 * Indirect X:\n
	 * The supplied one byte address is offset by the X register to index a location in page 0x00. The actual 16 bit
	 * address is read from this location.
	 * @return
	 */
	uint8_t IZX();

	/**
	 * Indirect Y:\n
	 * The supplied one byte address indexes a location in page 0x00. The actual 16 bit address is read from this
	 * location then offset by Y.
	 * @return
	 */
	uint8_t IZY();

	//OPCODES (listed alphabetically)
	uint8_t ADC();
	uint8_t AND();
	uint8_t ASL();
	uint8_t BCC();
	uint8_t BCS();
	uint8_t BEQ();
	uint8_t BIT();
	uint8_t BMI();
	uint8_t BNE();
	uint8_t BPL();
	uint8_t BRK();
	uint8_t BVC();
	uint8_t BVS();
	uint8_t CLC();
	uint8_t CLD();
	uint8_t CLI();
	uint8_t CLV();
	uint8_t CMP();
	uint8_t CPX();
	uint8_t CPY();
	uint8_t DEC();
	uint8_t DEX();
	uint8_t DEY();
	uint8_t EOR();
	uint8_t INC();
	uint8_t INX();
	uint8_t INY();
	uint8_t JMP();
	uint8_t JSR();
	uint8_t LDA();
	uint8_t LDX();
	uint8_t LDY();
	uint8_t LSR();
	uint8_t NOP();
	uint8_t ORA();
	uint8_t PHA();
	uint8_t PHP();
	uint8_t PLA();
	uint8_t PLP();
	uint8_t ROL();
	uint8_t ROR();
	uint8_t RTI();
	uint8_t RTS();
	uint8_t SBC();
	uint8_t SEC();
	uint8_t SED();
	uint8_t SEI();
	uint8_t STA();
	uint8_t STX();
	uint8_t STY();
	uint8_t TAX();
	uint8_t TAY();
	uint8_t TSX();
	uint8_t TXA();
	uint8_t TXS();
	uint8_t TYA();
	// ... and the "unknown" function for unknown opcodes. Functionally a NOP.
	uint8_t XXX();
};


#endif //NES_CPU_H
