#include "stdafx.h"
#include "RemoteQueue.h"


CRemoteQueue::CRemoteQueue(char* address) :CMsgQueue()
{
	m_pubisher = nullptr;

	strncpy_s(m_Address, sizeof(m_Address), address, strlen(address));
#ifdef _REMOTE
	m_ctx = nullptr;
#endif
}


CRemoteQueue::~CRemoteQueue()
{
}


void CRemoteQueue::RunInThread()
{
#ifdef _REMOTE
	m_ctx = zctx_new();
	m_pubisher = zsocket_new(m_ctx, ZMQ_PUB);
	int port = zsocket_bind(m_pubisher, m_Address);
#endif

	while (m_bRunning)
	{
		if (Process())
		{
		}
		else
		{
			// ����ʱ��1ms,����������¼�����������1ms
			//this_thread::sleep_for(chrono::milliseconds(1));

			// ����ʱ������1ms,û�ȵ��ͻ�ȥ����
			// ������õȵ��ˣ�������ȥ�ԣ�Ӧ�����һ���?
			unique_lock<mutex> lck(m_mtx);
			m_cv.wait_for(lck, std::chrono::seconds(1));
		}
	}

#ifdef _REMOTE
	if (m_ctx)
	{
		zctx_destroy(&m_ctx);
		m_ctx = nullptr;
	}
#endif
	// �����߳�
	m_hThread = nullptr;
	m_bRunning = false;
}

void CRemoteQueue::Output(ResponeItem* pItem)
{
#ifdef _REMOTE
	// ��������
	if (pItem->ptr1 && pItem->size1 > 0)
	{
		int ret = zsocket_sendmem(m_pubisher, pItem->ptr1, pItem->size1, ZFRAME_DONTWAIT);
	}
#endif	
	return;
}