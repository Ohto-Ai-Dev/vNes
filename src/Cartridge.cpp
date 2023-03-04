#include "Cartridge.h"
#include "Rominfo.h"
#include "stdint.h"
#include "string"
#include "Mapper.h"



bool Cartridge::loadRom(char *rom,int size)
{
	if (size < 16)
	{//�ļ�С��16���ֽڿ϶�����
		return false;
	}
	nesheader_t* header = (nesheader_t*)rom;
	if(!(header->nes[0] == 'N'
		&& header->nes[1]=='E'
		&& header -> nes[2]=='S'
		&& header ->nes[3]==0x1a))//��֤ͷ�ļ��Ƿ���NES�ļ�
	{
		return false;
	}

	uint8_t map = header->mapper_l >> 4;//��ȡmapper����λ��ֵ
	map = map | header -> mapper_h & 0xf0;//��ȡmapper����λ��ֵ

	//��rom��Ϣ����rominfo��
	rominfo.program_count = header->prg_bank_count;//��ȡ�����������
	rominfo.cha_count = header->cha_bank_count;//��ȡͼ���������

	//program Rom��С=16kb*����
	rominfo.prgrom_size = rominfo.program_count * 16 * 1024;
	//Char Rom��С=8kb*����
	rominfo.charom_size = rominfo.cha_count * 8 * 1024;


	//��̬�����ڴ�
	rominfo.prgrom = new uint8_t[rominfo.prgrom_size];
	rominfo.charom = new uint8_t[rominfo.charom_size];

	//�����ڴ�� ��Ҫstringͷ�ļ�
	//��һ��������Ŀ�ĵأ����Ƶ���
	//�ڶ�������Ҫ���Ƶ�����Դ
	//������������Ҫ���Ƶ��ֽ���
	memcpy(rominfo.prgrom, rom + 16, rominfo.prgrom_size);
	memcpy(rominfo.charom, rom + 8, rominfo.charom_size);


	//��������
	rominfo.is_vmirror = header->mapper_l & 0x1;
	rominfo.has_battery = (header->mapper_l >> 1) & 0x1;
	rominfo.is_trainer = (header->mapper_l >> 2) & 0x1;
	rominfo.is_fourScreen = (header->mapper_l >> 3) & 0x1;

	return true;
}

//CPU��ȡPRG��Rom��ַ�ռ�:0x8000-0xFFFF
uint8_t Cartridge::ReadViaCpu(uint16_t address)
{
	if (address >= 0x8000)
	{
		//���PrgRomֻ��һ��
		//��0xC000-0xFFFF��0x8000-0xBFFF�ľ���
		if (rominfo.program_count == 1)
		{
			address -= 0x4000;
		}
		return this->rominfo.prgrom[address - 0x8000];
	}
	return 0;
}

//PPU��ȡCHR��Rom��ַ�ռ�:0x0000-0x1FFF
uint8_t Cartridge::ReadViaPpu(uint16_t address)
{
	return this->rominfo.charom[address];
}


//CPUд��PRG��ROM��ַ�ռ�
void Cartridge::WriteViaCpu(uint16_t address,uint8_t data)
{
	if (address >= 0x8000)
	{
		//���PrgRomֻ��һ��
		//��0xC000-0xFFFF��0x8000-0xBFFF�ľ���
		if (rominfo.program_count == 1)
		{
			address -= 0x4000;
		}
		this->rominfo.prgrom[address - 0x8000] = data;
	}
}


//PPUд��CHR��ROm��ַ�ռ�
void Cartridge::WriteViaPpu(uint16_t address, uint8_t data)
{
	this->rominfo.charom[address] = data;
}


