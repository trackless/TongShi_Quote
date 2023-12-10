
/****************************************************************************************
*									������ݽӿڹ淶 V1.0    							*
*									     2010.11										*
*****************************************************************************************/

/****************************************************************************************
*					��ע���� HKEY_LOCAL_MACHINE/SOFTWARE/StockDrv ��					*
*					Driver  = "����DLLȫ·��"											*
*					Provider= "TongShi"													*
*																						*
*	������� LoadLibrary �� GetProcAddress �� FreeLibrary �ķ�ʽ���ù�Ʊ��������		*
*	��Ʊ�����������ļ��������λ���� ע��� HKEY_LOCAL_MACHINE/Software/Stockdrv		*
*	�� Driver ָ��																		*
*																						*
*																						*
*	==========================		���ֽڶ������		===========================		*
*																						*
*																						*
****************************************************************************************/


#ifndef __STOCKDRV_H__
#define __STOCKDRV_H__

// ������ʽ���Ͷ���
#define RCV_WORK_REQUEST			0			// ����Ա��������ʹ�ô˷�ʽ
#define RCV_WORK_SENDMSG			4			// �汾 2 ����ʹ�õķ�ʽ


//	��Ϣ����
#define RCV_REPORT			0x3f001234
#define RCV_FILEDATA		0x3f001235


#define	TS_StockDrv_IdTxt "TongShi_StockDrv_2.00"	// ͨ����Ϣ��������


// ֤ȯ�г�
#define SH_MARKET_EX				'HS'		// �Ϻ�
#define SZ_MARKET_EX				'ZS'		// ����
#define HK_MARKET_EX			    'KH'		// ���
#define EB_MARKET_EX			    'BE'		// ����
#define JB_MARKET_EX			    'JB'		// ����


// �ļ���������
// �ṹ������ʽ���ļ�����

#define FILE_HISTORY_EX				2			// ����ʷ����
#define FILE_MINUTE_EX				4			// ����ʱ����
#define FILE_POWER_EX				6			// ����Ȩ��Ϣ
#define FILE_TYPE_RES				-1			// ����


#define RI_IDSTRING					1			// �������ƣ�����(LPCSTR)������
#define RI_IDCODE					2			// ����
#define RI_VERSION					3			// ��������汾
#define RI_ERRRATE					4			// ȡ�ŵ�����
#define RI_STKNUM					5			// ȡ���й�Ʊ�ܼ���
#define RI_V2SUPPORT				6			// ֧������SJS��ṹ

#define STKLABEL_LEN				10			// �ɺ����ݳ���,�����г��ɺű������Ǯ��
#define STKNAME_LEN					32			// ��������



#pragma pack(1)


///////////////////////////////////////////////////////////////////////////////
// ��������
// ע��
//    ĳЩ�ֶο���Ϊ0�����ϴε����ݴ���
typedef struct tagRCV_REPORT_STRUCTEx
{
	WORD	m_cbSize;									// �ṹ��С
	time_t	m_time;										// ����ʱ��
	WORD	m_wMarket;									// ��Ʊ�г�����
	char	m_szLabel[STKLABEL_LEN];					// ��Ʊ����,��'\0'��β
	char	m_szName[STKNAME_LEN];						// ��Ʊ����,��'\0'��β

	float	m_fLastClose;								// ����
	float	m_fOpen;									// ��
	float	m_fHigh;									// ���
	float	m_fLow;										// ���
	float	m_fNewPrice;								// ����
	float	m_fVolume;									// �ɽ���,�Թ�Ϊ��λ,�ɵĺ�������Ʊ���Ͷ���
	float	m_fAmount;									// �ɽ���,��ԪΪ��λ

	float	m_fBuyPrice[3];								// �����1,2,3
	float	m_fBuyVolume[3];							// ������1,2,3
	float	m_fSellPrice[3];							// ������1,2,3
	float	m_fSellVolume[3];							// ������1,2,3

	float	m_fBuyPrice4;								// �����4
	float	m_fBuyVolume4;								// ������4
	float	m_fSellPrice4;								// ������4
	float	m_fSellVolume4;								// ������4
	float	m_fBuyPrice5;								// �����5
	float	m_fBuyVolume5;								// ������5
	float	m_fSellPrice5;								// ������5
	float	m_fSellVolume5;								// ������5
} RCV_REPORT_STRUCTEx;


//////////////////////////////////////////////////////////////////////////////////
//��������ͷ
//����ͷ m_dwHeadTag == EKE_HEAD_TAG 
#define EKE_HEAD_TAG	0xffffffff

typedef struct tagRCV_EKE_HEADEx
{
	DWORD	m_dwHeadTag;								// = EKE_HEAD_TAG
	WORD	m_wMarket;									// �г�����
	char	m_szLabel[STKLABEL_LEN];					// ��Ʊ����
} RCV_EKE_HEADEx;


// ��ʷ����
// עһ:
//		ÿһ���ݽṹ��Ӧͨ�� m_time == EKE_HEAD_TAG, �ж��Ƿ�Ϊ m_head, Ȼ����������
typedef union tagRCV_HISTORY_STRUCTEx
{
	struct
	{
		time_t	m_time;				// UCT
		float	m_fOpen;			// ����
		float	m_fHigh;			// ���
		float	m_fLow;				// ���
		float	m_fClose;			// ����
		float	m_fVolume;			// ��
		float	m_fAmount;			// ��
		union
		{
			struct
			{
				WORD m_wAdvance;	// ����, ��������Ч
				WORD m_wDecline;	// ����, ��������Ч
			};
			float m_fActiveBuyVol;	// ��������
		};
	};
	RCV_EKE_HEADEx m_head;
} RCV_HISTORY_STRUCTEx;


// ��ʱ����
// עһ:
//		ÿһ���ݽṹ��Ӧͨ�� m_time == EKE_HEAD_TAG, �ж��Ƿ�Ϊ m_head, Ȼ����������
typedef union tagRCV_MINUTE_STRUCTEx
{
	struct
	{
		time_t	m_time;				// UCT
		float	m_fPrice;			// ��
		float	m_fVolume;			// ��
		float	m_fAmount;			// ��
	};
	RCV_EKE_HEADEx m_head;
} RCV_MINUTE_STRUCTEx;


// ��Ȩ����
// עһ:
//		ÿһ���ݽṹ��Ӧͨ�� m_time == EKE_HEAD_TAG, �ж��Ƿ�Ϊ m_head, Ȼ����������
typedef union tagRCV_POWER_STRUCTEx
{
	struct
	{
		time_t	m_time;				// UCT
		float	m_fGive;			// ÿ����
		float	m_fPei;				// ÿ����
		float	m_fPeiPrice;		// ��ɼ�, ���� m_fPei != 0.0f ʱ��Ч
		float	m_fProfit;			// ÿ�ɺ���
	};
	RCV_EKE_HEADEx m_head;
} RCV_POWER_STRUCTEx;


//////////////////////////////////////////////////////////////////////////////////
// �ļ��������ݰ�ͷ
//  עһ:
//	m_wDataType == FILE_BASE_EX
//				m_dwAttrib = ��Ʊ֤ȯ�г�,m_szFileName�������ļ���
//				m_FileTime = �����������ļ���������
//  m_wDataType == FILE_NEWS_EX
//				m_dwAttrib = ��Ϣ��Դ,m_szFileName ����Ŀ¼���ļ���,Ŀ¼��Ϊ��Ϣ��Դ
//				m_dwSerialNo = ���к�
//				��:  "�Ͻ�����Ϣ\\0501Z012.TXT","������\\XLD0001.TXT"
//  ע��:
//		�����ļ�ѭ������,ÿ���ļ���Ψһ�����к�,�Ա����ظ�����
typedef struct tagRCV_FILE_HEADEx
{
	DWORD	m_dwAttrib;							// �ļ�������
	DWORD	m_dwLen;							// �ļ�����
	union
	{
		DWORD	m_dwSerialNo;					// ���к�,�Թ���
		time_t	m_FileTime;						// �ļ�����ʱ��
	};
	char	m_szFileName[_MAX_PATH];			// �ļ��� or URL
} RCV_FILE_HEADEx;



//////////////////////////////////////////////////////////////////////////////////
// ����֪ͨ��Ϣ
// wParam = RCV_WPARAM;
// lParam ָ�� RCV_DATA�ṹ;
// ���� 1 �Ѿ�����, 0 δ������ܴ���, Ŀǰ�÷���ֵ������
// עһ:
//		��¼����ʾ�������ݺͲ�������(���� Header)�����ݰ���, ���ļ���������, = 1
// ע��:
//		�� m_bDISK = FALSE, m_pData Ϊ��Ϣ���������ݻ�����ָ��
//
//		******** ���ݹ���, �����޸����� **********
//
//		m_bDISK = TRUE, m_pData Ϊ���ļ��Ĵ����ļ���, һ�����ֻ��
//		��������ȴ��ļ��ô��̷�ʽ
typedef struct tagRCV_DATA
{
	int					m_wDataType;			// �ļ�����
	int					m_nPacketNum;			// ��¼��, �μ�עһ
	RCV_FILE_HEADEx		m_File;					// �ļ��ӿ�
	BOOL				m_bDISK;				// �ļ��Ƿ��Ѵ��̵��ļ�
	union
	{
		RCV_REPORT_STRUCTEx* m_pReport;			// ��������
		RCV_HISTORY_STRUCTEx* m_pDay;			// ����������
		RCV_MINUTE_STRUCTEx* m_pMinute;			// ����ʱ����
		RCV_POWER_STRUCTEx* m_pPower;			// ����Ȩ����
		void* m_pData;							// �ڴ�ָ��
	};
} RCV_DATA;


/* ��Ϣ������� DEMO
LONG OnStkDataOK(UINT wParam, LONG lParam)
{
	RCV_DATA* pHeader;
	int i;

	pHeader = (RCV_DATA*)lParam;

	//	���ڴ����ٶ�������������,��ý� pHeader->m_pData ָ������ݱ���, ��������
	switch (wParam)
	{
	case RCV_REPORT:						// ��Ʊ����
		for (i = 0; i < pHeader->m_nPacketNum; i++)
		{
			pHeader->m_pReport[i] ...
			// ���ݴ���
		}
		break;

	case RCV_FILEDATA:						// �ļ�
		switch (pHeader->m_wDataType)
		{
		case FILE_HISTORY_EX:				// ����������
			break;

		case FILE_MINUTE_EX:				// ������������
			break;

		case FILE_BASE_EX:					// Ǯ�����ݻ��������ļ�, m_szFileName�������ļ���
			break;

		case FILE_NEWS_EX:					// ������, ��������m_szFileName����Ŀ¼������
			break;

		default:
			return 0;
		}
		break;

	default:
		return 0;							// unknown data
	}

	return 1;
}
*/


// ****************************************************************************
// �°���Ϣ���ͣ���ͨ�ӷ�ʽ���������Ա����
enum STKMessageType
{
	stkMessageLoginAuth = 0x1000,		// ��¼״̬
	stkMessageStkLabel = 0x1001,		// ֤ȯ�����
	stkMessageReport = 0x1234,		// ��������
	stkMessageTick = 0x2001,		// �ֱ�(�̿�����)
	stkMessagePower = 0x2002,		// ��Ȩ
	stkMessageFinance = 0x2003,		// ����
	stkMessageMinute1 = 0x3001,		// һ����
	stkMessageMinute5 = 0x3005,		// �����
	stkMessageHistory = 0x3002,		// ����
};

// ****************************************************************************
// ��¼״̬���ӿڵ�¼�ɹ����յ� stkMessageLoginAuth ���͵���Ϣ
// bAuthorizationState = TRUE����ʾ��¼�ɹ�
typedef struct tagSTK_LOGINAUTH_STRUCTEx
{
	BOOL bAuthorizationState;
} STK_LOGINAUTH_STRUCTEx;

// ****************************************************************************
// ֤ȯ�����
typedef  struct  tagSTK_STKLABEL_STRUCTEx
{
	WORD m_wMarket;								// ��Ʊ�г�����
	char m_szLabel[STKLABEL_LEN];				// ��Ʊ����
	char m_szName[STKNAME_LEN];					// ��Ʊ����
	char m_szPingYing[STKLABEL_LEN];			// ��Ʊ����ƴ��
	float m_fLastClose;							// ǰһ���������̼�
	time_t m_time;								// �������Ʊ��ʱ��
} STK_STKLABEL_STRUCTEx;

// ****************************************************************************
// �ֱ����ݽṹ
typedef union tagSTK_TICK_STRUCTEx
{
	struct
	{
		time_t	m_time;							// UCT
		float	m_fNewPrice;					// ���¼�
		float	m_fVolume;						// �ɽ���
		float	m_fAmount;						// �ɽ���
		float	m_Price[9];						// δʹ��
	};
	RCV_EKE_HEADEx m_head;
} STK_TICK_STRUCTEx;

// ****************************************************************************
// ����ͷ
typedef struct tagSTK_EKE_HEADEx
{
	DWORD	m_dwHeadTag;						// = EKE_HEAD_TAG
	WORD	m_wFlag;							// δʹ�� 00...
	WORD	m_wMarket;							// �г�����
	char	m_szLabel[STKLABEL_LEN];			// ��Ʊ����
} STK_EKE_HEADEx;

// ****************************************************************************
// �������ݽṹ
typedef union tagSTK_FINANCE_STRUCT
{
	struct
	{
		time_t time;		// ����ʱ��

		float m_fZgb;		// �ܹɱ�
		float m_fGjg;		// ���ҹ�
		float m_fFqrf;		// �����˹�**
		float m_fFrg;		// ���˹�**
		float m_fBg;		// B��
		float m_fHg;		// H��
		float m_fAg;		// ��ͨA��
		float m_fZgg;		// ְ����**
		float m_fA2zp;		// A2ת���**
		float m_fZzc;		// ���ʲ���ǧԪ��
		float m_fLdzc;		// �����ʲ�
		float m_fGdzc;		// �̶��ʲ�
		float m_fWxzc;		// �����ʲ�
		float m_fCqzc;		// �����ʲ�
		float m_fLdfz;		// ������ծ
		float m_fCqfz;		// ���ڸ�ծ
		float m_fZbgjj;		// �ʱ�������
		float m_fMggjj;		// ÿ�ɹ�����
		float m_fGdqy;		// �ɶ�Ȩ��
		float m_fZysr;		// ��Ӫ����
		float m_fZylr;		// ��Ӫ����
		float m_fQtlr;		// ��������
		float m_fYylr;		// Ӫҵ����
		float m_fTzsy;		// Ͷ������
		float m_fBtsr;		// ��������
		float m_fYywsr;		// Ӫҵ����֧
		float m_fSytz;		// �������
		float m_fLrze;		// �����ܶ�
		float m_fYszkl;		// Ӧ���ʿ���ת��**
		float m_fJly;		// ������
		float m_fWfply;		// δ��������
		float m_fMgwfp;		// ÿ��δ����
		float m_fMgsy;		// ÿ������
		float m_fMgjzc;		// ÿ�ɾ��ʲ�
		float m_fTzmgjzc;	// ����ÿ�ɾ���**
		float m_fGdqyb;		// �ɶ�Ȩ�����**
		float m_fJzcsyl;	// ����������
		float m_fJyxjlc;	// ��Ӫ�ֽ�����
		float m_fJyxjlr;	// ��Ӫ�ֽ�ע��
		float m_fJyxjll;	// ��Ӫ�ֽ�����
		float m_fTzxjlr;	// Ͷ���ֽ�����
		float m_fTzxjlc;	// Ͷ���ֽ�����
		float m_fTzxjll;	// Ͷ���ֽ�����
		float m_fCzxjlr;	// �����ֽ�����
		float m_fCzxjlc;	// �����ֽ�����
		float m_fCzxjll;	// �����ֽ�����
		float m_fXjdjw;		// �ֽ𼰵ȼ���
		float m_fYszzzl;	// Ӧ������ת��
		float m_fChzzl;		// �����ת��
		float m_fGdzs;		// �ɶ�����
		float m_fFxj;		// ���м�
		float m_fFxl;		// ������
		float m_fZyywl;		// ��Ӫҵ��������
		float m_fShlyl;		// ˰������������
		float m_fJzcl;		// ���ʲ�������
		float m_fZzcl;		// ���ʲ�������
	};
	STK_EKE_HEADEx m_head;	// 
} STK_FINANCE_STRUCTx;

typedef struct tagSTK_DATA
{
	WORD							m_wDataType;	// ������Ϣ����
	int								m_nPacketNum;	// ��¼����
	union
	{
		STK_LOGINAUTH_STRUCTEx* m_pLoginAuth;
		STK_STKLABEL_STRUCTEx* m_pStkLabel;
		RCV_REPORT_STRUCTEx* m_pReport;
		STK_TICK_STRUCTEx* m_pTick;
		RCV_POWER_STRUCTEx* m_pPower;
		STK_FINANCE_STRUCTx* m_pFinance;
		RCV_HISTORY_STRUCTEx* m_pMinute1;
		RCV_HISTORY_STRUCTEx* m_pMinute5;
		RCV_HISTORY_STRUCTEx* m_pHistory;
		void* m_pData;
	};
} STK_DATA;

#pragma pack()



///////////////////////////////////////////////////////////////////////////////
// APIs

#ifdef __cplusplus
extern "C"
{
#endif

	///////////////////////////////////////////////////////////////////////////////
	// ע�ắ��

	// ��Ʊ��ʼ��
	// ��ڲ���:
	//		hWnd			������Ϣ�Ĵ��ھ��
	//		Msg				�û��Զ�����Ϣ
	//		nWorkMode		�ӿڹ�����ʽ������Ա����ʹ������ķ�ʽ RCV_WORK_REQUEST��ע����Ϣ��������
	//                      Ҫ�� STKMessageType �����ֵ����
	// ���ز���:
	//		 1				�ɹ�
	//		-1				ʧ��
	// ע:
	//		ע���,��������������ڷ�����Ϣ; ����ע��,ͨ����ѯ��ʽ���ȡ������
	//		����Ʊ����û����,��������Ʊ���ճ���
	int WINAPI Stock_Init(HWND hWnd, UINT Msg, int nWorkMode);

	// �˳�,ֹͣ������Ϣ
	// ��ڲ���:
	//		hWnd			������Ϣ�Ĵ��ھ��,ͬ Stock_Init �ĵ�����ڲ���
	//	���ز���:
	//		 1				�ɹ�
	//		-1				ʧ��
	int WINAPI Stock_Quit(HWND hWnd);

	///////////////////////////////////////////////////////////////////////////////
	// ����ӿ�

	// ȡ�ѽ��յ��Ĺ�Ʊ����
	int WINAPI GetTotalNumber();

	// �����ȡ��Ʊ����(��չ)
	// ��ڲ���:
	//			nNo			���
	//			pBuf		��Ź�Ʊ���ݵĻ�����
	// ���ز���:
	//		    NoStockData	�޹�Ʊ����
	// ע:
	//			�ú����ṩ��Ʊ���ݵ���Ҫ����;�������������ʱ,���Կ��ٽ������ݿ��
	int WINAPI GetStockByNoEx(int nNo, RCV_REPORT_STRUCTEx* pBuf);

	// �ɹɺ�ȡ��Ʊ����(��չ)
	// ��ڲ���:	
	//			pszStockCode��Ʊ����
	//			nMarket		֤ȯ�г�
	//			pBuf		��Ź�Ʊ���ݵĻ�����
	// ���ز���:
	//		    NoStockData	�޹�Ʊ����
	// ע:
	//			�ú����ṩ��Ʊ���ݵ���Ҫ����;�������������ʱ,���Կ��ٽ������ݿ��
	int WINAPI GetStockByCodeEx(char* pszStockCode, int nMarket, RCV_REPORT_STRUCTEx* pBuf);

	// ������ճ���,��������
	// ��ڲ���:
	//			bSetup		TRUE		��ʾ����,��������
	// ���ز���:
	//			 1			�ɹ�
	//			-1			ʧ��
	int	WINAPI SetupReceiver(BOOL bSetup);

	//	ȡ�ù�Ʊ������Ϣ
	//	��ڲ���:
	//			nInfo		����
	//			pBuf		������
	//	���ڲ���:
	//			nInfo == RI_IDSTRING,	���������ַ�������, pBuf Ϊ�����ַ���
	//									��:	"TongShi_StockDrv_1.00"
	//			nInfo == RI_IDCODE,		������Ϣ�� ID ��, pBuf Ϊ�ַ�����ʽ�� ID ��
	//									��:	0x78001234	  "78001234"
	//			nInfo == RI_VERSION,	������Ϣ���汾��, pBuf Ϊ�ַ����汾
	//									��:  1.00		  "1.00"
	//			nInfo == RI_ERRRATE,	ȡ�ŵ�����,
	//			nInfo == RI_STKNUM,		ȡ���й�Ʊ�ܼ���
	DWORD WINAPI GetStockDrvInfo(int nInfo, void* pBuf);


	// �����Ʊ��������
	enum
	{
		stkRequestTick = 0x00,		// �̿ڷֱʣ������̿ڻ�ͬʱ���������Ʊ��Ȩ���ݺͲ�������
		stkRequestMin1 = 0x01,		// һ����
		stkRequestMin5 = 0x02,		// �����
		stkRequestDay = 0x05,		// ����
	};

	//  �����Ʊ����
	//  ��ڲ���:
	//          wMarket     ��Ʊ�г� 'HS' 'ZS' ....
	//          szCode      ��Ʊ���� '600001' ....
	//          nType       �������������
	BOOL WINAPI RequestData(WORD wMarket, LPTSTR szCode, int nType);


#ifdef __cplusplus
}
#endif


#endif // __STOCKDRV_H__
