#ifndef _KR_NES
#define _KR_NES_

#define LOAD_OK 0
#define ROM_LOADING_FAIL -1
#define BAD_ROM_ALLOC -2
#define BAD_ROM_COPY -3
#define NOT_NES_FILE -4


#include "Utils.h"
#include<SDL2\SDL.h>
#include "KR_Opcodes.h"
#include "KR_Mapper.h"

const float CLOCK = 1.789773f;//ntsc clock

const int MEM_SIZE = 0x10000;

const int PPUCC = 3; //Pixels Drawn Per Clock

const int HEADER_SIZE = 16;   //in bytes
const int TRAINER_SIZE = 512; //in bytes



enum interrupts :uint8
{
	NOITR,      //NOINTERRUPT
	NMI,        //NMI
	IRQ,        //IRQ
	BREAK,      //BRK
	RST,		//RESET
};  


/*============================================================================*/
// iNES header																  //	
//bytes 0->2 = NES															  //
//bytes 3 = 1A																  //
//bytes 4 = NUMBER OF PRG-ROM BANKS											  //
//bytes 5 = NUMBER OF 8KB CHR-ROM/VROM BANKS								  //
//bytes 6 = ROM CONTROL BYTE 1												  //
//bytes 7 = ROM CONTROL BYTE 2												  //
//bytes 8 = NUMBER OF 8KB RAM BANKS											  //
//bytes 9->15 = RESERVED/SHOULD BE ZERO 									  //
/*============================================================================*/
struct iNES
{
  //16 bytes in total
  byte HEAD[4];
  byte PRG_ROM_NUM;
  byte CHR_ROM_NUM;
  byte ROM_CTRL1;
  byte ROM_CTRL2;
  byte RAM_BANK_8K;
  byte RESERVED[7];
};


struct ROM
{ 
	
  uint16 trainer;		   //has trainer?
  uint16 battery;		   //has battery packed prg_ram? if so, sacorrectly allocate it and save in a file;
					  
  uint8  mapper;	       
  byte   region;		//NTSC or PAL
	
  uint32 prg_size;    
  uint32 chr_size;    
					  
  //byte *trainer;         //maybe someday i'll give it some attention
  //byte *battery_sram;      //for save games
  //byte *prg_rom;      
  //byte *chr_rom;      
 
};


union P
{
  struct bit
  {
	byte C : 1;        //Carry if the last instruction was overflown or underflown
	byte Z : 1;        //Zero flag, if the last instruction's result was zero
	byte I : 1;        //Interrupt disable, prevent IRQs(interruption requests I guess)
	byte D : 1;        //The cpu doesnt have a decimal mode, so it can be ignored
	byte B : 1;        //BREAK command, causing IRQ
	byte n : 1;        //not used
	byte V : 1;        //Overflow flag, when a negative result is given when a positive one was expected
	byte N : 1;        //Negative flag, 0 = positive 1 = negative
  } bits;
  byte pstatus;
};



struct CPU
{
  int16 PC;			   //Program Counter -> Hold the address of the next instruction
  int8  SP;			   //Stack Pointer -> points to the top of the stack
  int8  A;			   //Accumulator -> stores the result of logic and arithmetic ops
					   //can also be set to a value retrieved from memory.
  int8  X;			   //Index X register -> can be set to a value retrieved from memory
					   //can get or set value of stack pointer
  int8  Y;			   //Index Y register
  P     P;			   //Processor status 

  inline void zero(void) { A = 0x00, X = 0x00, Y = 0x00, PC = 0x00, P.pstatus = 0x00; SP = 0x00; };
 
};      

/*============================================================================*/
//MEMORY LAYOUT																  //	
//0X0100 ->  ZERO PAGE														  //
//0X0200 ->  STACK															  //
//0X0800 ->  RAM															  //
//0X2000 ->  MIRRORS (0X0000 - 0X07FF)										  //
//0X2008 ->  IO REGISTERS													  //
//0X4000 ->  MIRRORS (0X2000 - 0X2007)										  //
//0X4020 ->  IO REGISTERS													  //
//0X6000 ->  EXPANSION ROM													  //
//0X8000 ->  SRAM															  //
//0XC000 ->  PRG-ROM(LOW)													  //
//0X10000 -> PRG-ROM(HIGH)													  //
/*============================================================================*/




class KR_Nes
{

  public:
	  KR_Nes();
	  ~KR_Nes();
  
	int8 loadRom(const char *path);
	void printRomHeader(void);
	void initNes(void); 
	

  public:
	void initCPU(void);
	void initMapper(void);
	uint8 readFrom(uint16 addr);
	void writeTo(uint16 addr, uint8 data);
	bool interrupt = false;		

	CPU	 m6052;
	
	iNES m_header;
	ROM  m_cart;
	byte *m_rom; //temporary data; TODO - verify if its necessary at all

	mapper m_mapper;

	byte cpu_mem[MEM_SIZE]; //0x10000, from 0x0000 -> 0xFFFF
	

};

 #endif
