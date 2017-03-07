#ifndef _KR_OPCODES_
#define _KR_OPCODES_

#include "Utils.h"

enum addr_mode :uint8
{
	ZERO_PAGE,
	INDEXED_ZERO_PAGE,
	ABSOLUTE,
	INDEXED_ABSOLUTE,
	INDIRECT,
	IMPLIED,
	ACCUMULATOR,
	IMMEDIATE,
	RELATIVE,
	INDEXED_INDIRECT,
	INDIRECT_INDEXED,
};

enum op_inst :uint8 //listed by OPCODE from 0x00 -> 0xFE
{
	ADC = 0,	AND,	ASL,	BCC,	BCS,	BEQ,	BIT,	BMI,	BNE,	BPL,	BRK,
	BVC,	BVS,	CLC,	CLD,	CLI,	CLV,	CMP,	CPX,	CPY,	DEC,	DEX,	DEY,	
	EOR,	INC,	INX,	INY,	JMP,	JSR,	LDA,	LDX,	LDY,	LSR,	NOP,	ORA,
	PHA,	PHP,	PLA,	PLP,	ROL,	ROR,	RTI,	RTS,	SBC,	SEC,	SED,	SEI,
	STA,	STX,	STY,	TAX,	TAY,	TSX,	TXA,	TXS,	TYA

};


typedef struct OP_CODE
{
	addr_mode mod;  //addressing mode enum
	op_inst   inst; //instruction enum
	uint8     len;  //length of opcode in bytes
	uint8     cyc;  //how many cycles
	
} OP;

static OP opcode_table[] = {
	{},











};




#endif
