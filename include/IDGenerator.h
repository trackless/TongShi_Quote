#pragma once

#include <atomic>

#include "ApiStruct.h"

using namespace std;

class CIDGenerator
{
public:
	CIDGenerator();
	~CIDGenerator();

	// ����̫���ˣ���Ҫ�Զ��ضϣ�Ŀǰ�ƻ����ܳ���32
	void SetPrefix(const char* prefix);

	const char* GetIDString();
	long GetID();
private:
	atomic<long> m_id;
	OrderIDType m_IDString;
	OrderIDType m_Prefix;
};

