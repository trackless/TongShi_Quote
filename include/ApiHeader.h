#ifndef _API_HEADER_H_
#define _API_HEADER_H_

#include "CrossPlatform.h"

#ifdef __cplusplus
extern "C" {
#endif
	//���ڷָ�����ĺ��б���ǰ�û���ַ�б����Բ��ܳ��֡�:��һ���
	#define _QUANTBOX_SEPS_ ";"

	DLL_PUBLIC void* __stdcall XRequest(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3);
#ifdef __cplusplus
}
#endif

#endif//end of _API_HEADER_H_
