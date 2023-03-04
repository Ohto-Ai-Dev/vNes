#pragma once

#include "stdint.h"


class rominfo_t
{
	//存放解析后的卡带基本信息
public:
	bool is_vmirror;//是否水平 0水平 1垂直
	bool has_battery;//是否有电池支持
	bool is_trainer;//是否有trainer
	bool is_fourScreen;//是否四屏

	uint8_t program_count;//rom程序数量
	uint8_t cha_count;//rom图形数量
	uint8_t* prgrom;//程序镜像指针
	uint8_t* charom;//图像镜像指针

	uint32_t prgrom_size;//程序大小
	uint32_t charom_size;//图像大小
};



class nesheader_t
{
public:
	//存放nes的头部信息
	uint8_t nes[4];//存放nes头部前四个字节数据,验证是否是nes文件
	uint8_t prg_bank_count;//程序镜像数量
	uint8_t cha_bank_count;//图像镜像数量
	uint8_t mapper_l;//低位mapper
	uint8_t mapper_h;//高位mapper
};