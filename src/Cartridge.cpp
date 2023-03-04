#include "Cartridge.h"
#include "Rominfo.h"
#include "stdint.h"
#include "string"
#include "Mapper.h"



bool Cartridge::loadRom(char *rom,int size)
{
	if (size < 16)
	{//文件小于16个字节肯定错误
		return false;
	}
	nesheader_t* header = (nesheader_t*)rom;
	if(!(header->nes[0] == 'N'
		&& header->nes[1]=='E'
		&& header -> nes[2]=='S'
		&& header ->nes[3]==0x1a))//验证头文件是否是NES文件
	{
		return false;
	}

	uint8_t map = header->mapper_l >> 4;//获取mapper低四位的值
	map = map | header -> mapper_h & 0xf0;//获取mapper高四位的值

	//将rom信息存入rominfo中
	rominfo.program_count = header->prg_bank_count;//获取程序镜像块数量
	rominfo.cha_count = header->cha_bank_count;//获取图像镜像块数量

	//program Rom大小=16kb*数量
	rominfo.prgrom_size = rominfo.program_count * 16 * 1024;
	//Char Rom大小=8kb*数量
	rominfo.charom_size = rominfo.cha_count * 8 * 1024;


	//动态分配内存
	rominfo.prgrom = new uint8_t[rominfo.prgrom_size];
	rominfo.charom = new uint8_t[rominfo.charom_size];

	//复制内存块 需要string头文件
	//第一个参数是目的地，复制到哪
	//第二个参数要复制的数据源
	//第三个参数是要复制的字节数
	memcpy(rominfo.prgrom, rom + 16, rominfo.prgrom_size);
	memcpy(rominfo.charom, rom + 8, rominfo.charom_size);


	//杂项设置
	rominfo.is_vmirror = header->mapper_l & 0x1;
	rominfo.has_battery = (header->mapper_l >> 1) & 0x1;
	rominfo.is_trainer = (header->mapper_l >> 2) & 0x1;
	rominfo.is_fourScreen = (header->mapper_l >> 3) & 0x1;

	return true;
}

//CPU读取PRG的Rom地址空间:0x8000-0xFFFF
uint8_t Cartridge::ReadViaCpu(uint16_t address)
{
	if (address >= 0x8000)
	{
		//如果PrgRom只有一个
		//则0xC000-0xFFFF是0x8000-0xBFFF的镜像
		if (rominfo.program_count == 1)
		{
			address -= 0x4000;
		}
		return this->rominfo.prgrom[address - 0x8000];
	}
	return 0;
}

//PPU读取CHR的Rom地址空间:0x0000-0x1FFF
uint8_t Cartridge::ReadViaPpu(uint16_t address)
{
	return this->rominfo.charom[address];
}


//CPU写入PRG的ROM地址空间
void Cartridge::WriteViaCpu(uint16_t address,uint8_t data)
{
	if (address >= 0x8000)
	{
		//如果PrgRom只有一个
		//则0xC000-0xFFFF是0x8000-0xBFFF的镜像
		if (rominfo.program_count == 1)
		{
			address -= 0x4000;
		}
		this->rominfo.prgrom[address - 0x8000] = data;
	}
}


//PPU写入CHR的ROm地址空间
void Cartridge::WriteViaPpu(uint16_t address, uint8_t data)
{
	this->rominfo.charom[address] = data;
}


