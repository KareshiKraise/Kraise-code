#include <iostream>
#include "KR_Nes.h"

int main(int argc, char *argv[])
{ 
  
	KR_Nes nes;
	if (nes.loadRom("duck_tales.nes") == LOAD_OK)
	{
		std::cout << "rom carregada com sucesso" << std::endl;
	}
	std::cout << (int)nes.m_cart.mapper;

  
	int c;
	std::cin >> c;
  
  return 0;
}
