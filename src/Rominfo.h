#pragma once

#include "stdint.h"


class rominfo_t
{
	//��Ž�����Ŀ���������Ϣ
public:
	bool is_vmirror;//�Ƿ�ˮƽ 0ˮƽ 1��ֱ
	bool has_battery;//�Ƿ��е��֧��
	bool is_trainer;//�Ƿ���trainer
	bool is_fourScreen;//�Ƿ�����

	uint8_t program_count;//rom��������
	uint8_t cha_count;//romͼ������
	uint8_t* prgrom;//������ָ��
	uint8_t* charom;//ͼ����ָ��

	uint32_t prgrom_size;//�����С
	uint32_t charom_size;//ͼ���С
};



class nesheader_t
{
public:
	//���nes��ͷ����Ϣ
	uint8_t nes[4];//���nesͷ��ǰ�ĸ��ֽ�����,��֤�Ƿ���nes�ļ�
	uint8_t prg_bank_count;//����������
	uint8_t cha_bank_count;//ͼ��������
	uint8_t mapper_l;//��λmapper
	uint8_t mapper_h;//��λmapper
};