#include "stdafx.h"

#include <stdio.h>
#include <string.h>
#include "../include/XApiC.h"
#include "../include/QueueHeader.h"
#include "../include/QueueEnum.h"

#if defined WINDOWS || WIN32
#include <libloaderapi.h>
#else
#include <dlfcn.h>
#include <errno.h>
#endif


void* X_LoadLib(char* libPath)
{
	if (libPath == nullptr)
		return nullptr;

#if defined WINDOWS || WIN32
	return LoadLibraryExA(libPath, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
#else
	return dlopen(libPath, RTLD_NOW);
#endif
}

const char* X_GetLastError()
{
#if defined WINDOWS || WIN32
	char szBuf[256] = { 0 };
	LPVOID lpMsgBuf;
	DWORD dw = GetLastError();
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&lpMsgBuf,
		0, NULL);
	return (char*)lpMsgBuf;
#else
	extern int errno;
	errno = 0;
	return dlerror();
#endif
}

void* X_GetFunction(void* lib, char* ProcName)
{
	if (lib == nullptr)
		return nullptr;
#if defined WINDOWS || WIN32
	return GetProcAddress((HMODULE)lib, ProcName);
#else
	return (dlsym(lib, ProcName));
#endif
}

void X_FreeLib(void* lib)
{
	if (lib == nullptr)
		return;

#if defined WINDOWS || WIN32
	FreeLibrary((HMODULE)lib);
#else
	dlclose(lib);
#endif
}

ApiType X_GetApiTypes(void* pFun)
{
	if (pFun == nullptr)
		return ApiType::ApiType_Nono;

	void* p = ((fnOnRespone)pFun)(RequestType::RequestType_GetApiTypes, nullptr, nullptr, 0, 0, nullptr, 0, nullptr, 0, nullptr, 0);

	return (ApiType)(char)(long long)(p);
}

const char* X_GetApiVersion(void* pFun)
{
	if (pFun == nullptr)
		return nullptr;

	return (char*)((fnOnRespone)pFun)(RequestType::RequestType_GetApiVersion, nullptr, nullptr, 0, 0, nullptr, 0, nullptr, 0, nullptr, 0);
}

const char* X_GetApiName(void* pFun)
{
	if (pFun == nullptr)
		return nullptr;

	return (char*)((fnOnRespone)pFun)(RequestType::RequestType_GetApiName, nullptr, nullptr, 0, 0, nullptr, 0, nullptr, 0, nullptr, 0);
}

void* X_Create(void* pFun)
{
	if (pFun == nullptr)
		return nullptr;

	return ((fnOnRespone)pFun)(RequestType::RequestType_Create, nullptr, nullptr, 0, 0, nullptr, 0, nullptr, 0, nullptr, 0);
}

void X_Register(void* pFun, void* pApi, void* pCallback, void* pClass)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(RequestType::RequestType_Register, pApi, nullptr, 0, 0, pCallback, 0, pClass, 0, nullptr, 0);
}

void X_Connect(void* pFun, void* pApi, char* szPath, ServerInfoField* pServerInfo, UserInfoField* pUserInfo, int count)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(RequestType::RequestType_Connect, pApi, nullptr, 0, 0, pServerInfo, 0, pUserInfo, count, szPath, 0);
}

void X_Disconnect(void* pFun, void* pApi)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(RequestType::RequestType_Disconnect, pApi, nullptr, 0, 0, nullptr, 0, nullptr, 0, nullptr, 0);
}

void X_Subscribe(void* pFun, void* pApi, char* szInstrument, char* szExchange)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(RequestType::RequestType_Subscribe, pApi, nullptr, 0, 0, szInstrument, 0, szExchange, 0, nullptr, 0);
}

void X_Unsubscribe(void* pFun, void* pApi, char* szInstrument, char* szExchange)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(RequestType::RequestType_Unsubscribe, pApi, nullptr, 0, 0, szInstrument, 0, szExchange, 0, nullptr, 0);
}

void X_SubscribeQuote(void* pFun, void* pApi, char* szInstrument, char* szExchange)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(RequestType::RequestType_SubscribeQuote, pApi, nullptr, 0, 0, szInstrument, 0, szExchange, 0, nullptr, 0);
}

void X_UnsubscribeQuote(void* pFun, void* pApi, char* szInstrument, char* szExchange)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(RequestType::RequestType_UnsubscribeQuote, pApi, nullptr, 0, 0, szInstrument, 0, szExchange, 0, nullptr, 0);
}

void X_ReqQryInstrument(void* pFun, void* pApi, char* szInstrument, char* szExchange)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(QueryType::QueryType_ReqQryInstrument, pApi, nullptr, 0, 0, szInstrument, 0, szExchange, 0, nullptr, 0);
}

void X_ReqQryInvestorPosition(void* pFun, void* pApi, char* szInstrument, char* szExchange)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(QueryType::QueryType_ReqQryInvestorPosition, pApi, nullptr, 0, 0, szInstrument, 0, szExchange, 0, nullptr, 0);
}

void X_ReqQryTradingAccount(void* pFun, void* pApi)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(QueryType::QueryType_ReqQryTradingAccount, pApi, nullptr, 0, 0, nullptr, 0, nullptr, 0, nullptr, 0);
}

void X_SendOrder(void* pFun, void* pApi, OrderField* pOrder, OrderIDType* pInOut, int count)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(RequestType::RequestType_ReqOrderInsert, pApi, nullptr, 0, 0, pOrder, count, pInOut, 0, nullptr, 0);
}

void X_CancelOrder(void* pFun, void* pApi, OrderIDType* pIn, OrderIDType* pOut, int count)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(RequestType::RequestType_ReqOrderAction, pApi, nullptr, 0, 0, pIn, count, pOut, 0, nullptr, 0);
}

void X_SendQuote(void* pFun, void* pApi, QuoteField* pQuote, OrderIDType* pAskOut, OrderIDType* pBidOut, int count)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(RequestType::RequestType_ReqQuoteInsert, pApi, nullptr, 0, 0, pQuote, count, pAskOut, 0, pBidOut, 0);
}

void X_CancelQuote(void* pFun, void* pApi, OrderIDType* pIn, OrderIDType* pOut, int count)
{
	if (pFun == nullptr || pApi == nullptr)
		return;

	((fnOnRespone)pFun)(RequestType::RequestType_ReqQuoteAction, pApi, nullptr, 0, 0, pIn, count, pOut, 0, nullptr, 0);
}
