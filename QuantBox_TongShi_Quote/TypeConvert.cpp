#include "stdafx.h"
#include "TypeConvert.h"

ExchangeType Market_2_ExchangeType(WORD In)
{
	switch (In)
	{
	case SH_MARKET_EX:
		return ExchangeType::ExchangeType_SSE;
	case SZ_MARKET_EX:
		return ExchangeType::ExchangeType_SZSE;
	case HK_MARKET_EX:
		return ExchangeType::ExchangeType_HKEx;
	case JB_MARKET_EX:
		return ExchangeType::ExchangeType_NEEQ;
	default:
		return ExchangeType::ExchangeType_Undefined;
	}
}

char* Market_2_ExchangeID(WORD In)
{
	switch (In)
	{
	case SH_MARKET_EX:
		return "SH";
	case SZ_MARKET_EX:
		return "SZ";
	case HK_MARKET_EX:
		return "HKEx";
	case EB_MARKET_EX:
		return "EB";
	case JB_MARKET_EX:
		return "BJ";
	default:
		return "";
	}
}

char _OldSymbol_2_NewSymbol[18][2][7] = {
	{ "1A0001", "000001" }, // ��ָ֤��
	{ "1A0002", "000002" }, // ����ָ��
	{ "1A0003", "000003" }, // �¹�ָ��

	{ "1B0001", "000004" }, // ��ҵָ��
	{ "1B0002", "000005" }, // ��ҵָ��
	{ "1B0004", "000006" }, // �ز�ָ��
	{ "1B0005", "000007" }, // ����ָ��
	{ "1B0006", "000008" }, // �ۺ�ָ��
	{ "1B0007", "000010" }, // ��֤180
	{ "1B0008", "000011" }, // ����ָ��
	{ "1B0009", "000012" }, // ��ծָ��
	{ "1B0010", "000013" }, // ��ծָ��

	{ "1B0015", "000015" }, // ����ָ��
	{ "1B0016", "000016" }, // ��֤50
	{ "1B0017", "000017" }, // ����ָ

	{ "1C0002", "000015" }, // ����ָ��
	{ "1C0003", "000016" }, // ��֤50
	{ "1C0004", "000017" }, // ����ָ
};

char* OldSymbol_2_NewSymbol(char* In, WORD In2)
{
	if (In2 != SH_MARKET_EX)
		return In;
	if (In[1] >= 'A')
	{
		for (int i = 0; i < 18; ++i)
		{
			if (strcmp(In, _OldSymbol_2_NewSymbol[i][0]) == 0)
			{
				return _OldSymbol_2_NewSymbol[i][1];
			}
		}
	}
	return In;
}
