#define _CRT_SECURE_NO_WARNINGS
#include "kr_nes.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

KR_Nes::KR_Nes()
{
	//
}

KR_Nes::~KR_Nes()
{
	//
}

void KR_Nes::printRomHeader(void)
{
	printf("%x ", m_header.HEAD[0]);
	printf("%x ", m_header.HEAD[1]);
	printf("%x ", m_header.HEAD[2]);
	printf("%x ", m_header.HEAD[3]);

	printf("%x ", m_header.PRG_ROM_NUM);
	printf("%x ", m_header.CHR_ROM_NUM);
	printf("%x ", m_header.ROM_CTRL1);
	printf("%x ", m_header.ROM_CTRL2);
	printf("%x ", m_header.RAM_BANK_8K);
	printf("%x ", m_header.RESERVED[0]);
	printf("%x ", m_header.RESERVED[1]);
	printf("%x ", m_header.RESERVED[2]);
	printf("%x ", m_header.RESERVED[3]);
	printf("%x ", m_header.RESERVED[4]);
	printf("%x ", m_header.RESERVED[5]);
	printf("%x ", m_header.RESERVED[6]);
} //utilitary for debug purposes

int8 KR_Nes::loadRom(const char* path)
{
	//load rom and verify header

	FILE *file = NULL;
	file = fopen(path, "rb");  

	if(file == NULL)
	{
		printf("error opening rom\n");
		return ROM_LOADING_FAIL;
	}

	fseek(file, 0, SEEK_END);
	long lsize = ftell(file);
	rewind(file);

	m_rom = (byte *)malloc(sizeof(byte)*lsize);
	if(m_rom == NULL)
	{
	  printf("memory error during loading process\n");
	  return BAD_ROM_ALLOC;
	}

	size_t result = fread(m_rom, 1, lsize, file);
	if(result != lsize) 
	{
	   printf("problem reading the rom into the buffer\n");
	   return BAD_ROM_COPY;
	} 

	fclose(file);

	printf("tamanho da rom em bytes %d \n", result );
	memcpy(&m_header, m_rom, 16);

	//fread(&m_header,sizeof(byte),16, file); //for tests

	if(memcmp(m_header.HEAD, "NES\x1A", sizeof(m_header.HEAD)) != 0)
	{
		printf("not a valid nes file");
		return NOT_NES_FILE;
	}
	
	m_cart.prg_size = m_header.PRG_ROM_NUM * 0x4000;
	m_cart.chr_size = m_header.CHR_ROM_NUM * 0x2000;

	//check mapper
	m_cart.mapper = ((m_header.ROM_CTRL1 & 0xF0) >> 4) + (m_header.ROM_CTRL2 & 0xF0);

	//check for (battery packed) prg ram   from 0x6000 to 0x7FFF
	m_cart.battery = (m_header.ROM_CTRL1 & 0x02);  
		
	//check for trainer, always ignore it from 0x7000 to 0x71FF
	m_cart.trainer = (m_header.ROM_CTRL1 & 0x04);
	
	initCPU();
	
	
	return LOAD_OK;
  
}

void KR_Nes::initMapper(void)
{
	switch (m_cart.mapper)
	{

	case UNROM:
		m_mapper.type = UNROM;
		m_mapper.num_banks = m_header.PRG_ROM_NUM;
		m_mapper.alloc_banks();
		m_mapper.assign_banks(m_rom, m_cart);
		break;
	}

}


uint8 KR_Nes::readFrom(uint16 addr)
{
	//work with hexadecimals
	return cpu_mem[addr];
}


void KR_Nes::writeTo(uint16 addr, uint8 data)
{	
	//work with hexadecimals
	cpu_mem[addr] = data;
}



void KR_Nes::initNes(void)
{
	//init the cpu
	initCPU();

}

void KR_Nes::initCPU(void)
{
	//Initialize by reading address 0xfffc
	m6052.PC = cpu_mem[0xFFFC];
	//Stack at 0x1FF
	m6052.SP = cpu_mem[0x01FF];
	//mapper
	initMapper();
	
}
