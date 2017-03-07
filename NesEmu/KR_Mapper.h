#ifndef _KR_MAPPER_
#define _KR_MAPPER_

#define UNROM_BANK_SIZE 0x4000

#include <cstring>

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
	
	
	
};







#endif