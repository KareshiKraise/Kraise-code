#ifndef _KR_MAPPER_
#define _KR_MAPPER_

#define UNROM_BANK_SIZE 0x4000

class ROM;

/*============================================================================*/
//MEMORY MAPPERS															  //
//NO MAPPER = 0															      //
//MMC1         = 1															  //
//UNROM SWITCH = 2															  //
//CNROM SWITCH = 3															  //
//MMC3         = 4															  //
// APPARENTLY ONLY THESE ARE RELEVANT										  //
/* ========================================================================== */
enum mapper_t :uint8
{
	NROM,
	MMC1,
	UNROM,
	CNROM,
	MMC3

};

struct mapper
{
	mapper_t type;
	uint8    num_banks;
	byte     **bank;
	void     alloc_banks();
	void     assign_banks(byte *data, ROM nes_rom);
	
};


void mapper::alloc_banks()
{
	switch (type)
	{
	case UNROM:
		bank = new byte*[num_banks];
		for (int i = 0; i < num_banks; i++)
			bank[i] = new byte[UNROM_BANK_SIZE];
		break;

	}
};


void mapper::assign_banks(byte *data, ROM nes_rom)
{
	int offset = 0x10; //16 bytes of header
	if (nes_rom.trainer)
	{
		offset += 0x200; //512 bytes of trainer
	}
	
	for (int i = 0; i < num_banks; i++)
	{
		memcpy(bank[i], &data[offset + UNROM_BANK_SIZE*i], UNROM_BANK_SIZE);
	}
};


#endif