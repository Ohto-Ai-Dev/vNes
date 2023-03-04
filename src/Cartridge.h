#pragma once


#include "stdint.h"//ʹ��uint_8���� һ���ֽ�
#include "Rominfo.h"
#include "Mapper.h"


class Cartridge
{
private:
	//�������ֹ���ʵ��
	rominfo_t rominfo;//rom��Ϣ
	
	

public:
	Cartridge();//���캯�� ��ʼ��

	bool loadRom(char * rom,int size);//���ز�����Rom

	uint8_t ReadViaCpu(uint16_t address);//�ṩCPU���ӿ�

	uint8_t ReadViaPpu(uint16_t address);//�ṩPPU���ӿ�

	void WriteViaCpu(uint16_t address,uint8_t data);//�ṩCPUд�ӿ�

	void WriteViaPpu(uint16_t address,uint8_t data);//�ṩPPUд�ӿ�
};


