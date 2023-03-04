#pragma once


#include "stdint.h"//使用uint_8类型 一个字节
#include "Rominfo.h"
#include "Mapper.h"


class Cartridge
{
private:
	//卡带部分功能实现
	rominfo_t rominfo;//rom信息
	
	

public:
	Cartridge();//构造函数 初始化

	bool loadRom(char * rom,int size);//加载并解析Rom

	uint8_t ReadViaCpu(uint16_t address);//提供CPU读接口

	uint8_t ReadViaPpu(uint16_t address);//提供PPU读接口

	void WriteViaCpu(uint16_t address,uint8_t data);//提供CPU写接口

	void WriteViaPpu(uint16_t address,uint8_t data);//提供PPU写接口
};


