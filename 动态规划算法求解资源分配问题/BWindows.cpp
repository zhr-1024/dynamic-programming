//////////////////////////////////////////////////////////////////////////
// Bwindows.cpp����д Windows �����õ�һЩ�Զ��庯�������ʵ��
//   �������
// 		CBHashLK���������� key �Ĺ�ϣ����
//		CBArrLink�� ��Ч����������
// 		CHeapMemory�� ��ȫ�ֶ���ά������ͨ�� new ������ڴ�ָ����
//      CBApp �ࣺ ����Ӧ�ó���ȫ����Ϣ
//
//   ͬʱ���� CBHeapMemory ���ȫ�ֶ��� HM �Ķ��塢
//      CBApp ��ȫ�� pApp ָ��Ķ���
//
//////////////////////////////////////////////////////////////////////////

#include "Bwindows.h"
#include <stdio.h>		// ʹ�� _vsntprintf ��
#include <stdlib.h>		// ���� atoi��atof �Ⱥ���
#include <time.h>

// pApp��ȫ�� App �����ָ�롣��ָ��Ķ������ڻ�ñ������ĳЩ������Ϣ��
//   �� hInstance �ȡ�����ͬʱ���� BForm ģ�����ʹ���������ȷ��Ϣ
// ����ָ���������Ϊ��������ָ����ָ��������Բ��ܱ��ı�
// ��ȫ�� App ����Ĺ��캯���У��ó�Ա��ʼ��������еĳ���Ա��ֵ
CBApp *pApp=0;	


// ȫ�ֶ���HM�Ķ���
// ��������������� new ���ٵ��ڴ�ռ�ĵ�ַ���ö�������ʱ���Զ� delete ��Щ�ڴ�
//   Bwindows.h ���д�ȫ�ֶ�����������κ�ģ����� Bwindows.h ����ʹ�ô�ȫ�ֶ���
CBHeapMemory HM; 


// ���ÿռ乩�ַ��������ݴ�ʹ�ã�
//��gEmptyTSTR���ڼ���Unicode��Ansi��gEmptySTR������Ansi��gEmptyWSTR ������ Unicode��
// ����ʱ����ָ��Ϊ0�����ݴ��ؿ��ַ������ͷ��ش˿ռ������
// �˿ռ��� BWindows.h ��δ������������ģ�鲻��ʹ��
TCHAR gEmptyTSTR[1];
char gEmptySTR[1];
WCHAR gEmptyWSTR[1];


//////////////////////////////////////////////////////////////////////////
// �����Զ��庯��
//
//////////////////////////////////////////////////////////////////////////


// ������Ϣ��
//   �� title Ϊ NULL�����Զ�ʹ��Ӧ�ó�������Ϊ title
EDlgBoxCmdID MsgBox(LPCTSTR szPrompt, 
					LPCTSTR szTitle,	
					EMsgBoxBtn buttons, 
					EMsgBoxIcon icon, 
					EDlgBoxDefBtn defBtn, 
					bool bSystemModal, 
					bool bHelpButton, 
					bool bRightJustified, 
					bool bRightToLeftReading)
{
	UINT uType;
	if (szTitle == NULL) 
	{
		// ��� title Ϊ NULL���ͻ��Ӧ�ó�������Ϊ title
		TCHAR fName[2048] = {0};
		TCHAR * slash, * dot;

		// ���Ӧ�ó�����
		if (GetModuleFileName(0, fName, sizeof(fName)) == 0)
		{
			// ���Ӧ�ó�����ʧ��
			szTitle=TEXT("Message");		// �ݴ�����ʹ�� "Message"
		}
		else	// if (GetModuleFileName(0, fName, 2048) == 0)
		{
			// ���Ӧ�ó������ɹ�
			szTitle = fName;	// ������Ϊ����Ӧ�ó���������������ȡ�����ļ�������
								//   �����ȡ�ļ�������ʧ�ܣ���ʹ��������Ӧ�ó�����
			// �������һ�� '\\'
			slash=fName;
			while(*slash) slash++;
			while(*slash != TCHAR('\\') && slash>=fName) slash--;
			if (slash>=fName)
			{
				// ��ȡ�� slash + 1 ��ʼ�����һ�� '.' ֮ǰ�Ĳ���Ϊ�ļ�����
				szTitle = slash + 1;	// �����ý�ȡ�� '\\' ��ĩβ�Ĳ��֣�
										//   �����ٲ��� '.'��������� '.' ʧ�ܣ�
										//    ��ʹ�ô� '\\' ��ĩβ�Ĳ���

				// ���� slash + 1 ������һ�� '.'
				dot = slash+1;
				while(*dot) dot++;
				while(*dot != TCHAR('.') && dot>slash+1) dot--;
				if (*dot == TCHAR('.')) * dot = '\0';		// ���� '.' �ɹ����� '.' ��λ��
															//   ��Ϊ '\0' ʹ�ض��ַ���
			}	// end if (slash)
		}	// end if (GetModuleFileName(0, fName, 2048) == 0)
	}	// end if (title == NULL) 
	
	uType = buttons + icon + defBtn;
	uType += MB_TASKMODAL;				// hWnd == 0 ʱ����� MB_TASKMODAL 
										//	��ʹ��ǰ�߳������Ķ��㴰�ڶ�������
	if (bSystemModal) 
	{
		// hWnd == 0 ʱ���� MB_TASKMODAL�������� MB_SYSTEMMODAL
		uType += MB_TOPMOST;
	}
	if (bHelpButton) uType += MB_HELP;
	if (bRightJustified) uType += MB_RIGHT;
	if (bRightToLeftReading) uType += MB_RTLREADING;
	return (EDlgBoxCmdID)MessageBox(0, szPrompt, szTitle, uType);
}

EDlgBoxCmdID MsgBox( char valueChar, LPCTSTR szTitle /*= NULL*/, EMsgBoxBtn buttons /*= mb_OK*/, EMsgBoxIcon icon /*= mb_IconNone*/, EDlgBoxDefBtn defBtn /*= mb_DefButton1*/, bool bSystemModal /*= false*/, bool bHelpButton /*= false*/, bool bRightJustified /*= false*/, bool bRightToLeftReading /*= false*/ )
{
	LPTSTR buff=Str(valueChar);
	EDlgBoxCmdID ret;
	ret = MsgBox(buff, szTitle, buttons, icon, defBtn, bSystemModal, bHelpButton, bRightJustified, bRightToLeftReading);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
	return ret;
}

EDlgBoxCmdID MsgBox( unsigned short int valueInt, /* TCHAR */ LPCTSTR szTitle /*= NULL*/, EMsgBoxBtn buttons /*= mb_OK*/, EMsgBoxIcon icon /*= mb_IconNone*/, EDlgBoxDefBtn defBtn /*= mb_DefButton1*/, bool bSystemModal /*= false*/, bool bHelpButton /*= false*/, bool bRightJustified /*= false*/, bool bRightToLeftReading /*= false*/ )
{
	LPTSTR buff=Str(valueInt);
	EDlgBoxCmdID ret;
	ret = MsgBox(buff, szTitle, buttons, icon, defBtn, bSystemModal, bHelpButton, bRightJustified, bRightToLeftReading);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
	return ret;
}

EDlgBoxCmdID MsgBox( int valueInt, LPCTSTR szTitle /*= NULL*/, EMsgBoxBtn buttons /*= mb_OK*/, EMsgBoxIcon icon /*= mb_IconNone*/, EDlgBoxDefBtn defBtn /*= mb_DefButton1*/, bool bSystemModal /*= false*/, bool bHelpButton /*= false*/, bool bRightJustified /*= false*/, bool bRightToLeftReading /*= false*/ )
{
	LPTSTR buff=Str(valueInt);
	EDlgBoxCmdID ret;
	ret = MsgBox(buff, szTitle, buttons, icon, defBtn, bSystemModal, bHelpButton, bRightJustified, bRightToLeftReading);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
	return ret;
}

EDlgBoxCmdID MsgBox( long valueLong, LPCTSTR szTitle /*= NULL*/, EMsgBoxBtn buttons /*= mb_OK*/, EMsgBoxIcon icon /*= mb_IconNone*/, EDlgBoxDefBtn defBtn /*= mb_DefButton1*/, bool bSystemModal /*= false*/, bool bHelpButton /*= false*/, bool bRightJustified /*= false*/, bool bRightToLeftReading /*= false*/ )
{
	LPTSTR buff=Str(valueLong);
	EDlgBoxCmdID ret;
	ret = MsgBox(buff, szTitle, buttons, icon, defBtn, bSystemModal, bHelpButton, bRightJustified, bRightToLeftReading);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
	return ret;
}

EDlgBoxCmdID MsgBox( unsigned int valueInt, LPCTSTR szTitle /*= NULL*/, EMsgBoxBtn buttons /*= mb_OK*/, EMsgBoxIcon icon /*= mb_IconNone*/, EDlgBoxDefBtn defBtn /*= mb_DefButton1*/, bool bSystemModal /*= false*/, bool bHelpButton /*= false*/, bool bRightJustified /*= false*/, bool bRightToLeftReading /*= false*/ )
{
	LPTSTR buff=Str(valueInt);
	EDlgBoxCmdID ret;
	ret = MsgBox(buff, szTitle, buttons, icon, defBtn, bSystemModal, bHelpButton, bRightJustified, bRightToLeftReading);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
	return ret;
}

EDlgBoxCmdID MsgBox( unsigned long valueInt, LPCTSTR szTitle /*= NULL*/, EMsgBoxBtn buttons /*= mb_OK*/, EMsgBoxIcon icon /*= mb_IconNone*/, EDlgBoxDefBtn defBtn /*= mb_DefButton1*/, bool bSystemModal /*= false*/, bool bHelpButton /*= false*/, bool bRightJustified /*= false*/, bool bRightToLeftReading /*= false*/ )
{
	LPTSTR buff=Str(valueInt);
	EDlgBoxCmdID ret;
	ret = MsgBox(buff, szTitle, buttons, icon, defBtn, bSystemModal, bHelpButton, bRightJustified, bRightToLeftReading);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
	return ret;
}

EDlgBoxCmdID MsgBox( float valueSng, LPCTSTR szTitle /*= NULL*/, EMsgBoxBtn buttons /*= mb_OK*/, EMsgBoxIcon icon /*= mb_IconNone*/, EDlgBoxDefBtn defBtn /*= mb_DefButton1*/, bool bSystemModal /*= false*/, bool bHelpButton /*= false*/, bool bRightJustified /*= false*/, bool bRightToLeftReading /*= false*/ )
{
	LPTSTR buff=Str(valueSng);
	EDlgBoxCmdID ret;
	ret = MsgBox(buff, szTitle, buttons, icon, defBtn, bSystemModal, bHelpButton, bRightJustified, bRightToLeftReading);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
	return ret;
}

EDlgBoxCmdID MsgBox( double valueDbl, LPCTSTR szTitle /*= NULL*/, EMsgBoxBtn buttons /*= mb_OK*/, EMsgBoxIcon icon /*= mb_IconNone*/, EDlgBoxDefBtn defBtn /*= mb_DefButton1*/, bool bSystemModal /*= false*/, bool bHelpButton /*= false*/, bool bRightJustified /*= false*/, bool bRightToLeftReading /*= false*/ )
{
	LPTSTR buff=Str(valueDbl);
	EDlgBoxCmdID ret;
	ret = MsgBox(buff, szTitle, buttons, icon, defBtn, bSystemModal, bHelpButton, bRightJustified, bRightToLeftReading);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
	return ret;
}

EDlgBoxCmdID MsgBox( long double valueDbl, LPCTSTR szTitle /*= NULL*/, EMsgBoxBtn buttons /*= mb_OK*/, EMsgBoxIcon icon /*= mb_IconNone*/, EDlgBoxDefBtn defBtn /*= mb_DefButton1*/, bool bSystemModal /*= false*/, bool bHelpButton /*= false*/, bool bRightJustified /*= false*/, bool bRightToLeftReading /*= false*/ )
{
	LPTSTR buff=Str(valueDbl);
	EDlgBoxCmdID ret;
	ret = MsgBox(buff, szTitle, buttons, icon, defBtn, bSystemModal, bHelpButton, bRightJustified, bRightToLeftReading);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
	return ret;
}

EDlgBoxCmdID MsgBox( tstring valueString, tstring valueTitle /*= TEXT("")*/, EMsgBoxBtn buttons /*= mb_OK*/, EMsgBoxIcon icon /*= mb_IconNone*/, EDlgBoxDefBtn defBtn /*= mb_DefButton1*/, bool bSystemModal /*= false*/, bool bHelpButton /*= false*/, bool bRightJustified /*= false*/, bool bRightToLeftReading /*= false*/ )
{
	LPCTSTR szTitle;
	if (*(valueTitle.c_str())==0) szTitle=NULL; else szTitle=valueTitle.c_str();
	return MsgBox(valueString.c_str(), szTitle, buttons, icon, defBtn, bSystemModal, bHelpButton, bRightJustified, bRightToLeftReading);
}



BOOL MsgBeep( EMsgBeep soundStyle/* = mb_SoundSpeaker*/ )
{
	return MessageBeep(soundStyle);
}

// ��һ������ת��Ϊ�˽��Ƶ��ַ������ַ����ռ��Զ����١��� HM �Զ�����
LPTSTR Oct(long number)
{
	return StrPrintf(TEXT("%o"), number);
}

// ��һ������ת��Ϊʮ�����Ƶ��ַ������ַ����ռ��Զ����١��� HM �Զ�����
LPTSTR Hex(long number)
{
	return StrPrintf(TEXT("%X"), number);
}

// ��õ�ǰ·���ַ������ַ����ռ��Զ����١��� HM �Զ�����
LPTSTR CurDir()
{
	LPTSTR curDirBuff = new TCHAR[1024];
	HM.AddPtr(curDirBuff);
	GetCurrentDirectory(1024, curDirBuff);
	return curDirBuff;
}

// ��ȡһ���Զ�����Դ���ֽ����ݣ��ռ��Զ����١��� HM �Զ�����
//   rSize ��Ϊ0ʱ�����Ӵ˲���ָ��Ŀռ䷵����Դ���ֽ���
unsigned char * LoadResData( UINT idRes, UINT typeRes, unsigned long * rSize/*=0*/ )
{
	return LoadResData(MAKEINTRESOURCE(idRes), MAKEINTRESOURCE(typeRes), rSize); 
}

unsigned char * LoadResData( UINT idRes, LPCTSTR typeRes, unsigned long * rSize/*=0*/ )
{
	return LoadResData(MAKEINTRESOURCE(idRes), typeRes, rSize); 
}

unsigned char * LoadResData( LPCTSTR idRes, UINT typeRes, unsigned long * rSize/*=0*/ )
{
	return LoadResData(idRes, MAKEINTRESOURCE(typeRes), rSize); 
}

unsigned char * LoadResData( LPCTSTR idRes, LPCTSTR typeRes, unsigned long * rSize/*=0*/ )
{
	HRSRC hRes = FindResource(0, idRes, typeRes);
	if (rSize) *rSize = SizeofResource(0, hRes);
	HGLOBAL hGlob = LoadResource(0, hRes);
	return (unsigned char *)LockResource(hGlob); 
}

//////////////////////////////////////////////////////////////////////////
// ʱ�� ����
//////////////////////////////////////////////////////////////////////////

// ���ص�ǰϵͳ���ڡ�ʱ���һ���ַ������ַ����ռ��Զ����١��� HM �Զ�����
//   �� lpDblTime ��Ϊ0��������ǰϵͳ���ڡ�ʱ��ת��Ϊ double 
//     ��Ϊ1601-1-1���������ĺ�������������ָ��� double �ͱ�����
//   �� lpTime ��Ϊ0��������ǰϵͳ���ڡ�ʱ��洢����ָ��Ľṹ��
LPTSTR Now( double *lpDblTime/*=0*/, SYSTEMTIME *lpTime/*=0*/ )
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	if (lpTime) *lpTime = st;
	if (lpDblTime) *lpDblTime = DateTimeDbl(st);

	return StrPrintf(TEXT("%d-%d-%d %02d:%02d:%02d"),	// %02d������2λ������ǰ��0���Ǽӿո���2λ
		st.wYear, st.wMonth, st.wDay, 
		st.wHour, st.wMinute, st.wSecond);
}

// ���õ�ǰϵͳ���ڡ�ʱ��
BOOL NowSet( SYSTEMTIME stNow )
{
	return SetLocalTime (&stNow);
}

// ��һ�����ڡ�ʱ��ת��Ϊ double ���أ�Ϊ1601-1-1���������ĺ�������
double DateTimeDbl( SYSTEMTIME stDatetime )
{
	FILETIME ft;
	SystemTimeToFileTime(&stDatetime, &ft);
	return ((double)ft.dwLowDateTime  
		+ 4294967296.0 * ft.dwHighDateTime)/1e4;
}

// �����������ڡ�ʱ���ʱ����
// style Ϊָ��ʱ�����ĵ�λ
double DateDiff( eDataTimeDiffStyle style, 
				 SYSTEMTIME stDatetime1, 
				 SYSTEMTIME stDatetime2 )
{
	double diff=DateTimeDbl(stDatetime2)-DateTimeDbl(stDatetime1);
	switch (style)
	{
	case edtYearDiff:
		diff /= 365;	// ��������ִ������ case �����
	case edtMonthDiff:
		diff /= 12;		// ��������ִ������ case �����
	case edtDayDiff:
		diff /= 24;		// ��������ִ������ case �����
	case edtHourDiff:
		diff /= 60;		// ��������ִ������ case �����
	case edtMinuteDiff:
		diff /= 60;		// ��������ִ������ case �����
	case edtSecondDiff:
		diff /= 1000;	// ��������ִ������ case �����
	case edtMilliseconds:
		break;
	}
	return diff;
}

// ���ش� 1970-1-1 00:00 ����������
// ������ blClockTicks==True���򷵻ر����̾����� clock ticks ��
long TimeClock( bool blClockTicks/*=false */ )
{
	if (blClockTicks)
		return clock();
	else
		return (long)time(NULL);  // time() �������ܷ��� long long �������ݣ�����ֻ�������4λ
}




//////////////////////////////////////////////////////////////////////////
// �Զ����ַ��� ����
//////////////////////////////////////////////////////////////////////////


// �� printf ��ʽ����һ���ַ������ַ����ռ��Զ����١��� HM �Զ�����
LPTSTR cdecl StrPrintf( LPCTSTR szFormat, ... )
{
	if (szFormat==0) {gEmptyTSTR[0]=0; return gEmptyTSTR;}  // �ݴ�

	// ���ٱ������ַ����Ŀռ� lpszResult
	TCHAR * lpszResult = new TCHAR [2048];
	HM.AddPtr(lpszResult);			// �����·�����ڴ��׵�ַ���浽 HM ���Զ�����
	
	va_list pArgList;
	va_start(pArgList, szFormat);
	_vsntprintf(lpszResult, 2047, szFormat, pArgList);
	va_end(pArgList);
	
	return lpszResult;
}

// ȡ�ַ�����ǰ length ���ַ�������ַ����������������ַ������׵�ַ
//  ��ʹ��Unicodeʱ1��������1�����ȣ�ʹ��ANSIʱ1��������2�����ȣ�
// ���ַ����ռ��Զ����١��� HM �Զ�����
// length�����ַ�������ʱ���������ַ�����length<=0 ʱ���� ָ�� "\0" ���մ�����ָ��
LPTSTR Left(LPCTSTR szStringSrc, int length)  // LPCTSTR ���� const TCHAR *
{
	if (szStringSrc==0) {gEmptyTSTR[0]=0; return gEmptyTSTR;}  // �ݴ�

	int lenSrc = lstrlen(szStringSrc);
	
	// ��Ҫ��ȡ�Ĳ��ֳ��� length �޶��� 0���ַ�����󳤶�
	if (length < 1) length = 0;
	if (length > lenSrc) length = lenSrc;

	// ���ٱ������ַ����Ŀռ� lpszResult
	TCHAR * lpszResult = new TCHAR [length+1];
	HM.AddPtr(lpszResult);			// �����·�����ڴ�ָ�뱣�浽 HM ���Զ�����

	// ��������
	_tcsncpy(lpszResult, szStringSrc, length);
	*(lpszResult+length)='\0';		// ����ַ��������� '\0'

	return lpszResult;
}



// ȡ�ַ����ĺ� length ���ַ�������ַ����������������ַ������׵�ַ
//  ��ʹ��Unicodeʱ1��������1�����ȣ�ʹ��ANSIʱ1��������2�����ȣ�
// ���ַ����ռ��Զ����١��� HM �Զ�����
// length�����ַ�������ʱ���������ַ�����length<=0 ʱ���� ָ�� "\0" ���մ�����ָ��
LPTSTR Right(LPCTSTR szStringSrc, int length)
{
	if (szStringSrc==0) {gEmptyTSTR[0]=0; return gEmptyTSTR;}  // �ݴ�

	int lenSrc = lstrlen(szStringSrc);
	
	// ��Ҫ��ȡ�Ĳ��ֳ��� length �޶��� 0���ַ�����󳤶�
	if (length < 1) length = 0;
	if (length > lenSrc) length = lenSrc;
	
	// ���ٱ������ַ����Ŀռ� lpszResult
	TCHAR * lpszResult = new TCHAR [length+1];
	HM.AddPtr(lpszResult);	// �����·�����ڴ�ָ�뱣�浽 HM ���Զ�����
	
	// ���ɽ���ַ�������
	lstrcpy(lpszResult, szStringSrc+lenSrc-length);
	return lpszResult;
}



// ȡ�ַ����Ĵӵ� startPos ���ַ��𣬳� length ���ַ���ɵ��ַ�����
//   �����������ַ������׵�ַ
//  ����һ���ַ�λ��Ϊ1��ʹ��Unicodeʱ1��������1�����ȣ�
//   ʹ��ANSIʱ1��������2�����ȣ�
// ���ַ����ռ��Զ����١��� HM �Զ�����
// startPos+length-1 �����ַ�������ʱ���������ַ�����length<=0 ʱ
//	 �� startPos<=0 �� startPos>Դ�ַ������� ʱ����ָ�� "\0" ���մ�����ָ��
LPTSTR Mid(LPCTSTR szStringSrc, int startPos, int length)
{
	if (szStringSrc==0) {gEmptyTSTR[0]=0; return gEmptyTSTR;}  // �ݴ�

	int lenSrc = lstrlen(szStringSrc);
	
	// ��Ҫ��ȡ����ʼλ�� startPos �޶��� 1���ַ�����󳤶�+1��
	//	 �� startPos Ϊ���ַ�����󳤶�+1��ʱ����ȡ����Ϊ ""
	if (startPos < 1 || startPos>lenSrc) startPos = lenSrc+1;
	
	// ��Ҫ��ȡ�Ĳ��ִ� startPos ��ʼ������Ϊ length �޶��� 
	//	�ַ������ȷ�Χ֮�ڣ����� length��
	if (length < 1) length = 0;
	if (startPos+length-1 > lenSrc) length = lenSrc-startPos+1;
	
	// ���ٱ������ַ����Ŀռ� lpszResult
	TCHAR * lpszResult = new TCHAR [length+1];
	HM.AddPtr(lpszResult);			// ���·�����ڴ�ָ�뱣���� HM
	
	// ��������
	_tcsncpy(lpszResult, szStringSrc+startPos-1, length);
	*(lpszResult+length)='\0';		// ����ַ��������� '\0'
	
	return lpszResult;
}


// ɾ���ַ�����ǰ����β�������пո񣬷���ɾ��������ַ�����
//   ���ַ����ռ��Զ����١��� HM �Զ�����
// bDelOtherSpace=true ʱɾ�����пո����ڵ� isspace() �������
//   �����ַ���bDelOtherSpace=false ʱֻɾ���ո�
LPTSTR LTrim( LPCTSTR szStringSrc, bool bDelOtherSpace/*=false*/ )
{
	if (szStringSrc==0) {gEmptyTSTR[0]=0; return gEmptyTSTR;}  // �ݴ�
	
	// ���ٱ������ַ����Ŀռ� lpszResult����������
	TCHAR * lpszResult = new TCHAR [lstrlen(szStringSrc)+1];
	HM.AddPtr(lpszResult);			// ���·�����ڴ�ָ�뱣���� HM
	
	// �����ַ�����ִ��ɾ��
	TCHAR *p=(TCHAR *)szStringSrc;
	while (*p && (*p == TEXT(' ') || (bDelOtherSpace && _istspace(*p))) ) p++;	// ָ��Դ�ַ����ĵ�һ���ǿո�
	_tcscpy(lpszResult, p);	// �� p ��λ�ÿ����ַ���

	// �������ַ���
	return lpszResult;
}

LPTSTR RTrim( LPCTSTR szStringSrc, bool bDelOtherSpace/*=false*/ )
{
	if (szStringSrc==0) {gEmptyTSTR[0]=0; return gEmptyTSTR;}  // �ݴ�
	
	// ���ٱ������ַ����Ŀռ� lpszResult����������
	TCHAR * lpszResult = new TCHAR [lstrlen(szStringSrc)+1];
	HM.AddPtr(lpszResult);			// ���·�����ڴ�ָ�뱣���� HM
	_tcscpy(lpszResult, szStringSrc);
	
	// �����ַ�����ִ��ɾ��
	TCHAR *p=(TCHAR *)lpszResult;
	while (*p) p++; p--;	// ָ�����һ���ַ�
	while (*p==TEXT(' ') || (bDelOtherSpace && _istspace(*p))) p--;
	p++;
	*p=0;

	// �������ַ���
	return lpszResult;

}

LPTSTR Trim( LPCTSTR szStringSrc, bool bDelOtherSpace/*=false*/ )
{
	if (szStringSrc==0) {gEmptyTSTR[0]=0; return gEmptyTSTR;}  // �ݴ�
	
	// ���ٱ������ַ����Ŀռ� lpszResult����������
	TCHAR * lpszResult = new TCHAR [lstrlen(szStringSrc)+1];
	HM.AddPtr(lpszResult);			// ���·�����ڴ�ָ�뱣���� HM
	
	// �����ַ�����ִ��ɾ��ǰ���ո�
	TCHAR *p=(TCHAR *)szStringSrc;
	while (*p && (*p==TEXT(' ') || (bDelOtherSpace && _istspace(*p))) ) p++;	// ָ��Դ�ַ����ĵ�һ���ǿո�
	_tcscpy(lpszResult, p);	// �� p ��λ�ÿ����ַ���
	
	// �����ַ�����ִ��ɾ��β���ո�
	p=(TCHAR *)lpszResult;
	while (*p) p++; p--;	// ָ�����һ���ַ�
	while (*p==TEXT(' ') || (bDelOtherSpace && _istspace(*p))) p--;
	p++;
	*p=0;
	
	// �������ַ���
	return lpszResult;
}


// �� szSrc �У��ӵ� start ���ַ���ʼ����һ���ַ�λ��Ϊ1����
//	  �����ַ��� szFind �ĵ�һ�γ��ֵ�λ�ã���һ���ַ�λ��Ϊ1����
//    �ҵ�����ֵ>0��û�ҵ�����0
//  ˵����������δ�����κο⺯����strlenҲδ���ã������������Ч��
int InStr(int			start, 
		  LPCTSTR		szSrc, 
		  LPCTSTR		szFind, 
	eBStrCompareMethod	compare/*=bcmTextCompare*/)
{
	TCHAR * pSrcCompPos = (TCHAR *)(szSrc + start - 1);	// Դ�ַ����п�ʼ�Ƚϵ�λ�ã���ַ��

	if ( szSrc==0 || szFind==0 ) return 0;
	
	// Ҫ�����ҵ��ַ���Ϊ�մ���szSrc ָ�� '\0'�������� 0
	if (*szSrc == 0) return 0;							
	// Ҫ���ҵ�����Ϊ�մ���szFind ָ�� '\0'�������� start
	if (*szFind == 0) return start;							

	// ͨ���ƶ�ָ�� pSrcComp ��Դ�ַ�����ĩβ��ɨ��Դ�ַ���
	while (*pSrcCompPos)
	{
		// ------------------------------------------------------------------------
		// �Ƚ�Դ�ַ����� pSrcCompPos ��ʼ��һ�����ݣ��Ƿ��� stringFind �ַ�����ͬ
		// ------------------------------------------------------------------------
		TCHAR *p1, *p2;	
		p1 = pSrcCompPos;		// Դ�ַ����� pSrcCompPos ��ʼ���ַ�ɨ��
		p2 = (TCHAR *)szFind;	// �����ַ����� szFind ��ʼ���ַ�ɨ��

		// ��� Դ�ַ��� �� �����ַ��� ��δ��ĩβ���ͼ�������ַ��Ƚ�
		while (*p1 && *p2)
		{
			// ���Ҫ�Ƚϵ������ַ���=> c1��c2
			TCHAR c1= *p1, c2= *p2;		// ͨ���� *p1��*p2 ���ݴ�������������Ժ󷴸����� * ���㣬�������Ч��
			if (compare == bcmTextCompare)
			{
				// �������ִ�Сд�Ƚϣ����ڽ� c1��c2 ͳһΪ��д
				if (c1>='a' && c1<='z') c1-=32;
				if (c2>='a' && c2<='z') c2-=32;
			}

			// ��� c1��c2 ����ȣ��������ڲ� while
			if (c1 != c2) break;

			// �Ƚ���һ���ַ�
			p1++;
			p2++;
		}	// end while (*p1 && *p2)

		// �����ڲ� while ѭ�������������
		//	 (1) �����ַ��� ����ĩβ����ʱ���� Դ�ַ��� �Ƿ񵽴�ĩβ����ʾ�Ѿ��ҵ�
		//	 (2) Դ�ַ��� ����ĩβ���������ַ���û�е���ĩβ����ʾû���ҵ�
		//	 (3) Դ�ַ��� �� Ŀ���ַ��� ��û�е���ĩβ��˵������ break �����ģ���ʾû���ҵ�
		// ֻ���ڵ� (1) �����(�Ѿ��ҵ�)ʱ�������أ��������������������Դ�ַ�������һ��λ�ÿ�ʼ����
		if (*p2 == 0)
		{
			// �� (1) ������������ַ��� ����ĩβ
			// �������أ��������
			return pSrcCompPos - szSrc + 1;
		}


		// ------------------------------------------------------------------------
		// ��Դ�ַ���������ƶ�һ���Ƚ�λ��
		// ------------------------------------------------------------------------
		pSrcCompPos++;
	}	// end while (*pSrcCompPos)

	// û���ҵ�
	return 0;
}


int InStr(LPCTSTR szSrc,								// InStr �����ذ�
		  LPCTSTR szFind,
		  eBStrCompareMethod compare/*=bcmBinaryCompare*/)
{
	return InStr(1, szSrc, szFind, compare);
}


// �� szSrc �У��ӵ� start ���ַ���ʼ����һ���ַ�λ��Ϊ1����ĩβ�Ĳ��֣�
//	  �����ַ��� szFind �ĵ�����һ�γ��ֵ�λ�ã���һ���ַ�λ��Ϊ1����
//    �ҵ�����ֵ>0��û�ҵ�����0
//  ˵����������δ�����κο⺯����strlenҲδ���ã������������Ч��
int InStrRev(LPCTSTR		szSrc, 
			 LPCTSTR		szFind, 
			 int			start/*=1*/,
			 eBStrCompareMethod	compare/*=bcmTextCompare*/)
{
	TCHAR * pSrcCompStartPos = (TCHAR *)(szSrc + start - 1);	// Դ�ַ����п�ʼ�Ƚϵ�λ�ã���ַ��
	TCHAR * pSrcCompPos = pSrcCompStartPos; 
	
	if ( szSrc==0 || szFind==0 ) return 0;
	
	// Ҫ�����ҵ��ַ���Ϊ�մ���szSrc ָ�� '\0'�������� 0
	if (*szSrc == 0) return 0;							
	// Ҫ���ҵ�����Ϊ�մ���szFind ָ�� '\0'�������� start
	if (*szFind == 0) return start;	
	
	// �ƶ�ָ�� pSrcComp �����һ���ַ�
	while (*pSrcCompPos) pSrcCompPos++; pSrcCompPos--;

	// ͨ����ǰ�ƶ�ָ�� pSrcComp ��Դ�ַ����� pSrcCompStartPos��ɨ��Դ�ַ���
	while (pSrcCompPos>=pSrcCompStartPos)
	{
		// ------------------------------------------------------------------------
		// �Ƚ�Դ�ַ����� pSrcCompPos ��ʼ��һ�����ݣ��Ƿ��� stringFind �ַ�����ͬ
		// ------------------------------------------------------------------------
		TCHAR *p1, *p2;	
		p1 = pSrcCompPos;		// Դ�ַ����� pSrcCompPos ��ʼ���ַ�ɨ��
		p2 = (TCHAR *)szFind;	// �����ַ����� szFind ��ʼ���ַ�ɨ��
		
		// ��� Դ�ַ��� �� �����ַ��� ��δ��ĩβ���ͼ�������ַ��Ƚ�
		while (*p1 && *p2)
		{
			// ���Ҫ�Ƚϵ������ַ���=> c1��c2
			TCHAR c1= *p1, c2= *p2;		// ͨ���� *p1��*p2 ���ݴ�������������Ժ󷴸����� * ���㣬�������Ч��
			if (compare == bcmTextCompare)
			{
				// �������ִ�Сд�Ƚϣ����ڽ� c1��c2 ͳһΪ��д
				if (c1>='a' && c1<='z') c1-=32;
				if (c2>='a' && c2<='z') c2-=32;
			}
			
			// ��� c1��c2 ����ȣ��������ڲ� while
			if (c1 != c2) break;
			
			// �Ƚ���һ���ַ�
			p1++;
			p2++;
		}	// end while (*p1 && *p2)
		
		// �����ڲ� while ѭ�������������
		//	 (1) �����ַ��� ����ĩβ����ʱ���� Դ�ַ��� �Ƿ񵽴�ĩβ����ʾ�Ѿ��ҵ�
		//	 (2) Դ�ַ��� ����ĩβ���������ַ���û�е���ĩβ����ʾû���ҵ�
		//	 (3) Դ�ַ��� �� Ŀ���ַ��� ��û�е���ĩβ��˵������ break �����ģ���ʾû���ҵ�
		// ֻ���ڵ� (1) �����(�Ѿ��ҵ�)ʱ�������أ��������������������Դ�ַ�������һ��λ�ÿ�ʼ����
		if (*p2 == 0)
		{
			// �� (1) ������������ַ��� ����ĩβ
			// �������أ��������
			return pSrcCompPos - szSrc + 1;
		}
		
		
		// ------------------------------------------------------------------------
		// ��Դ�ַ�������ǰ�ƶ�һ���Ƚ�λ��
		// ------------------------------------------------------------------------
		pSrcCompPos--;
	}	// end while (*pSrcCompPos)
	
	// û���ҵ�
	return 0;
}


// ���ָ��ַ��� delimiters ���ָ�һ���ַ����������������ַ���
//	 �� ���ַ��� �ĵ�ַ�� ptrStrings[] ���鷵�أ������������ַ����ĸ���
//   ptrStrings[] �����±��1��ʼ����󵽺�������ֵ
// delimiters Ϊ�ָ����ַ�����ʡ�Ի�Ϊ "" ʱʹ�ã��ո�
// limit ���Ʒ������ַ�������������Ϊ -1 ʱ�����ƣ������������ַ���
//   ���ַ����ڴ漰 ptrStrings[] �����ڴ涼�Զ����䡢�Զ�����
// iPtrArrExpandPer Ϊ���ֶε�ָ������ ÿ�ζ�̬����Ĵ�С��Ӧ�����ֶ�
//   ���������������Ч��
//
// �������� Split���ڶ��μ��Ժ���ò������ϴε� ptrStrings ����ʱ��
//   ���������Զ� free ǰһ�ε� ptrStrings ������ָ������Ŀռ䣬
//   ��ָ������ĸ�Ԫ����ָ�ռ�
//
// �÷�������================================
// 	TCHAR ** s;
// 	int n,i;
// 	n=Split(TEXT("a,bc, d,efg, 123"), s, TEXT(","));
// 	for (i=1;i<=n;i++)
// 		MsgBox(s[i]);
// ================================================================
int Split(LPCTSTR		stringSrc, 
		  TCHAR		** &ptrStrings,						// һ���ַ�ָ�����飬����ÿ��Ԫ��Ϊһ�����ַ������׵�ַ�����齫�ڱ������б�����ռ䣬�±� [0]��[��������ֵ]��[0]�ռ䲻��
		  LPCTSTR		delimiters/*=NULL*/,			// �ָ����ַ�����ʡ�Ի�Ϊ""ʱʹ�� �ո�
		  int		    limit/*=-1*/,					// limit, ���Ʒ��ص����ַ����������C1��ʾ�������е����ַ���
	eBStrCompareMethod  compare/*=bcmBinaryCompare*/,	// ���֡��ָ��ַ��������ַ����Ƚ��Ƿ����ִ�Сд
		  int iPtrArrExpandPer/*=200*/)					// ptrStrings[] ÿ������Ĵ�С
{
	void **ptrArr=0;
	int iArrUbound=0, iSubstrCount=0;
	LPTSTR sep=NULL;

	if (delimiters==NULL ) 
	{
		// ʹ�ÿո�
		sep = new TCHAR [2];
		sep[0]=' '; sep[1]='\0';
	}
	else if(*delimiters=='\0')
	{
		// ʹ�ÿո�
		sep = new TCHAR [2];
		sep[0]=' '; sep[1]='\0';
	}
	else
	{
		// ���� delimiters �� sep
		sep = new TCHAR [lstrlen(delimiters)+1];
		_tcscpy(sep, delimiters);
	}
	
	if (stringSrc == NULL) { ptrStrings = NULL; return 0; 	}
	
	// ��� ptrStrings �Ѿ��� HM ���棬�ͷ�ԭ���Ŀռ�
	if ( HM.IsPtrManaged(ptrStrings) )
	{
		void * pStrLast = NULL;	// ptrStrings �ĸ������ݣ���һ�������ַ����ռ䣬ָ�������Ԫ�ض�ָ���м��ĳ��λ��
		pStrLast = (void *)HM.UserData(ptrStrings);
		HM.Free(pStrLast);		// �ͷ������ַ����ռ�
		HM.Free(ptrStrings);	// �ͷ�ָ�����鱾��Ŀռ�
	}

	// ����Դ�ַ�����һ����ʱ�ռ� => stringBak; stringBak �Ŀռ�Ҳ��¼�� HM �
	//   �Ժ�Ҳ��¼�ڷ���ֵ ptrStrings �� HM �� UserData ��
	//   ʹ�ȿ��� HM �ڳ�������Զ� free��Ҳ���ɱ����� free�����϶γ���
	LPTSTR stringBak = new TCHAR [ lstrlen(stringSrc)+1 ];
	HM.AddPtr(stringBak);
	_tcscpy(stringBak, stringSrc);

	// ����ָ������ĳ�ʼ��С
	iArrUbound = iPtrArrExpandPer;
	Redim(ptrArr, iArrUbound);

	// �� stringSrc �ַ����в�����һ�� sep
	int pos=1, pos2=0;
	pos2 = InStr(pos, stringSrc, sep, compare);
	while (pos2)
	{
		// ���� pos �� pos2 �����ַ��������� ptrArr[]
		// ������ ptrArr[] �� stringBak �� pos λ�õĵ�ַ
		// ���� stringBak �� pos2 λ����Ϊ '\0'
		iSubstrCount++;
		if (iSubstrCount > iArrUbound)
		{
			// �ض���ָ������ ptrArr �ĳ�ʼ��С
			Redim(ptrArr, iArrUbound+iPtrArrExpandPer, iArrUbound, true);
			iArrUbound = iArrUbound+iPtrArrExpandPer;
		}
		ptrArr[iSubstrCount] = stringBak+pos-1;		// ptrArr[] �� stringBak �� pos λ�õĵ�ַ
		*(stringBak+pos2-1) = TEXT('\0');					// �� stringBak �� pos2 λ����Ϊ '\0'
		if (limit>0 && iSubstrCount >= limit) goto FinishSub;

		// pos ����ƶ���������һ�� sep
		pos = pos2 + lstrlen(sep);
		pos2 = InStr(pos, stringSrc, sep, compare);
	}

	// ���һ����
	pos2 = lstrlen(stringSrc) + 1;
	// ���� pos �� pos2 �����ַ��������� ptrArr[]
	iSubstrCount++;
	if (iSubstrCount > iArrUbound)
	{
		// �ض���ָ������ ptrArr �ĳ�ʼ��С
		Redim(ptrArr, iArrUbound+iPtrArrExpandPer, iArrUbound, true);
		iArrUbound = iArrUbound+iPtrArrExpandPer;
	}
	ptrArr[iSubstrCount] = stringBak+pos-1;		// ptrArr[] �� stringBak �� pos λ�õĵ�ַ
	*(stringBak+pos2-1) = TEXT('\0');					// �� stringBak �� pos2 λ����Ϊ '\0'

FinishSub:
	if (iSubstrCount)
	{
		// �ض���ָ������ ptrArr �������С
		Redim(ptrArr, iSubstrCount, iArrUbound, true);

		// ���·�����ڴ�ָ�뱣���� mHM
		// ͬʱ���ø�������Ϊָ�� stringBak��ʹ�´ε��� Split 
		//   ������ͬ�� ptrArr ʱ��free���ε� stringBak
		HM.AddPtr(ptrArr, true, (long)stringBak);	
		
		// ����ֵ�����ò��� ptrStrings �ķ���ֵ
		ptrStrings = (TCHAR **)ptrArr;
	}
	else
	{
		// �����ַ���
		Erase(ptrArr);
		ptrStrings = 0;
	}


	if (sep) { delete []sep; sep=NULL; }

	// �������ַ����ĸ���
	return iSubstrCount;
}


// �� delimiter ���Ӷ���ַ������������Ӻõ��ַ���
// ����ַ����ĵ�ַ������ stringSrcArray[] ������������������
//   �����д��±� arrayIndexStart �� arrayIndexEnd ���ַ���
// delimiter Ϊ 0 ʱ��Ĭ���� "\0" �����ַ������������ַ��� delimiter ����
// bTailDoubleNull ��Ϊ true�����ڽ���ַ���������ټ�һ��'\0'�������������'\0'��
// ����ַ������ڴ��Զ����䡢�� HM �Զ�����
LPTSTR Join(TCHAR * stringSrcArray[], 
		   const int    arrayIndexEnd, 
		   LPCTSTR delimiter/*=0*/, 
		   const int    arrayIndexStart/*=1*/, 
		   const bool   bTailDoubleNull/*=false*/)
{
	if (stringSrcArray==0) {gEmptyTSTR[0]=0; return gEmptyTSTR;}  // �ݴ�

	// ��ý���ַ������ܳ��� => lenResult
	int lenResult = 0;
	int lenDelimiter;
	int i;

	if (delimiter)
		lenDelimiter = lstrlen(delimiter);
	else
		lenDelimiter = 1;					// �ַ����м���� '\0'��һ���ַ���

	for(i=arrayIndexStart; i<=arrayIndexEnd; i++)
	{
		if (stringSrcArray[i]==0) {gEmptyTSTR[0]=0; return gEmptyTSTR;}  // �ݴ�
		lenResult += lstrlen(stringSrcArray[i]);
		lenResult += lenDelimiter;
	}
	lenResult -= lenDelimiter;				// ���һ���ַ������治�� delimiter
	if (bTailDoubleNull) lenResult += 1;	// ������Ҫ����'\0'���ټ�һ������

	// �������ַ������ڴ�ռ�
	TCHAR * stringResult = new TCHAR[lenResult + 1];	// +1Ϊ���� '\0' �ռ䣨˫'\0'ʱָ���һ��'\0'��
	HM.AddPtr(stringResult);						// ���·�����ڴ�ָ�뱣���� HM

	// �����ַ���
	TCHAR *p = stringResult;
	for(i=arrayIndexStart; i<=arrayIndexEnd; i++)
	{
		// ���� stringSrcArray[i]
		lstrcpy(p, stringSrcArray[i]);
		p += lstrlen(stringSrcArray[i]);

		// ���� �����ַ���
		if (i<arrayIndexEnd)	// �������һ���ַ��������� delimiter
		{
			if (delimiter)
			{
				// ���ַ��� delimiter ��Ϊ�����ַ�
				lstrcpy(p, delimiter);
				p += lstrlen(delimiter);
			}
			else
			{
				// �� '\0' ��Ϊ�����ַ�
				*p = '\0';
				p++;
			}
		}
	}

	// ��ӽ�β�� '\0'
	if (bTailDoubleNull) {*p = '\0'; p++;}
	*p = '\0';

	// ���ؽ���ַ���ָ��
	return stringResult;
}


// �����ַ������������Ӻ�ĳ��ַ���
// �������Ӻõ��ַ������׵�ַ���Զ��������ַ����Ŀռ䡢�� HM �Զ�����
// ÿ�ε��ÿ��������9���ַ���
LPTSTR StrAppend( LPCTSTR str1/*=0*/, 
				  LPCTSTR str2/*=0*/, 
			  	  LPCTSTR str3/*=0*/, 
				  LPCTSTR str4/*=0*/, 
				  LPCTSTR str5/*=0*/, 
				  LPCTSTR str6/*=0*/, 
				  LPCTSTR str7/*=0*/,
				  LPCTSTR str8/*=0*/,
				  LPCTSTR str9/*=0*/ )
{
	// �����ַ������ܳ��� => resultStrLen
	int resultStrLen=0;
	if (str1) resultStrLen+=_tcslen(str1);
	if (str2) resultStrLen+=_tcslen(str2);
	if (str3) resultStrLen+=_tcslen(str3);
	if (str4) resultStrLen+=_tcslen(str4);
	if (str5) resultStrLen+=_tcslen(str5);
	if (str6) resultStrLen+=_tcslen(str6);
	if (str7) resultStrLen+=_tcslen(str7);
	if (str8) resultStrLen+=_tcslen(str8);
	if (str9) resultStrLen+=_tcslen(str9);
	
	// ���ٽ���ַ����Ŀռ�
	TCHAR * resultStr = new TCHAR[resultStrLen+1];
	HM.AddPtr(resultStr);
	memset(resultStr, 0, resultStrLen+1);
	
	// ���������ַ���
	if (str1) _tcscat(resultStr, str1);
	if (str2) _tcscat(resultStr, str2);
	if (str3) _tcscat(resultStr, str3);
	if (str4) _tcscat(resultStr, str4);
	if (str5) _tcscat(resultStr, str5);
	if (str6) _tcscat(resultStr, str6);
	if (str7) _tcscat(resultStr, str7);
	if (str8) _tcscat(resultStr, str8);
	if (str9) _tcscat(resultStr, str9);
	
	// ���ֵ '\0'
	*(resultStr + resultStrLen)='\0';
	
	// ����
	return resultStr;
}



// �� ANSI �� UTF8 �ַ���ת��Ϊ Unicode�����ؽ���ַ����׵�ַ
//   ���� bToUTF8orANSI Ϊ false ʱת�� ANSI��Ϊ true ʱת�� UTF8
//   ����ַ������ڴ��Զ����䡢�� HM �Զ�����
LPWSTR StrConvUnicode(const char * szAnsi, bool bFromUTF8orANSI /*=false*/)   // LPWSTR ���� unsigned short int *
{
	if (szAnsi==0) {gEmptyWSTR[0]=0; return gEmptyWSTR;}  // �ݴ�

	UINT codePage;
	WCHAR * wszResult=0;  
	int wLen=0; 
	
	if (bFromUTF8orANSI) codePage=CP_UTF8; else codePage=CP_ACP;

	// ��ý���ַ��������ַ����������� -1 ʹ�����Զ����� szAnsi �ĳ���
	wLen = MultiByteToWideChar(codePage, 0, szAnsi, -1, NULL, 0);
	// �������ַ����Ŀռ�
	wszResult = new WCHAR [wLen+1];
	HM.AddPtr(wszResult);
	// ת��
	MultiByteToWideChar(codePage, 0, szAnsi, -1, wszResult, wLen);
	wszResult[wLen]='\0';

	return wszResult; 
}


// �� Unicode �ַ���ת��Ϊ ANSI �� UTF8�����ؽ���ַ����׵�ַ
//   ���� bToUTF8orANSI Ϊ false ʱת��Ϊ ANSI��Ϊ true ʱת��Ϊ UTF8
//   ����ַ������ڴ��Զ����䡢�� HM �Զ�����
char * StrConvFromUnicode(LPCWSTR szUnicode, bool bToUTF8orANSI /*=false*/ )
{
	if (szUnicode==0) {gEmptySTR[0]=0; return gEmptySTR;}  // �ݴ�

	UINT codePage;
	char * szResult=0;
	int aLenBytes=0;

	if (bToUTF8orANSI) codePage=CP_UTF8; else codePage=CP_ACP;

	// ��ý���ַ��������ַ����������� -1 ʹ�����Զ����� szUnicode �ĳ���
	aLenBytes=WideCharToMultiByte(codePage, 0, szUnicode, -1, NULL, 0, NULL, NULL);
	// �������ַ����Ŀռ�
	szResult = new char [aLenBytes];
	HM.AddPtr(szResult);
	// ת������ aLenBytes ������Ҫ�����ֽ������ַ���
	WideCharToMultiByte(codePage, 0, szUnicode, -1, szResult, aLenBytes, NULL, NULL);  

	return szResult;
}

// ���ַ���ת��Ϊ double ����ֵ
double Val( LPCWSTR stringVal )
{
	if (stringVal==0) {return 0;}  // �ݴ�

	// �� stringVal ת��Ϊ ANSI ��ʽ���ַ��� => szResult
	char * szResult = NULL;
	int aLenBytes=0;
	double dblResult = 0.0;

	// ��ý���ַ��������ַ����������� -1 ʹ�����Զ����� szUnicode �ĳ���
	aLenBytes=WideCharToMultiByte(CP_ACP, 0, stringVal, -1, NULL, 0, NULL, NULL);
	// �������ַ����Ŀռ�
	szResult = new char [aLenBytes];
	// ת������ aLenBytes ������Ҫ�����ֽ������ַ���
	WideCharToMultiByte(CP_ACP, 0, stringVal, -1, szResult, aLenBytes, NULL, NULL);  
	
	dblResult = atof(szResult);
	delete [] szResult;

	return dblResult;
}

double Val( LPCSTR stringVal )
{
	if (stringVal==0) {return 0;}  // �ݴ�
	return atof(stringVal);
}


// ��������������ת��Ϊ�ַ���
// �����ַ����׵�ַ���ַ����ռ��Զ����١��� HM �Զ�����
LPTSTR Str(char character)
{
	LPTSTR buff=new TCHAR [10];
	HM.AddPtr(buff);	// �� HM ����̬�ռ�
	_stprintf(buff, TEXT("%c"), character);
	return buff;
}

LPTSTR Str(unsigned short int number)	// TCHAR
{
	LPTSTR buff=new TCHAR [20];
	HM.AddPtr(buff);	// �� HM ����̬�ռ�
#ifdef UNICODE
	*buff=number;		// ���ַ����ķ�ʽ���һ���ַ�
	*(buff+1)='\0';		// ���� TEXT �긳ֵ�ַ�����TCHAR tch=TEXT('��');
#else
	_stprintf(buff, TEXT("%u"), number);
#endif
	return buff;
}

LPTSTR Str(int number)
{
	LPTSTR buff=new TCHAR [20];
	HM.AddPtr(buff);	// �� HM ����̬�ռ�
	_stprintf(buff, TEXT("%d"), number);
	return buff;
}

LPTSTR Str(long number)
{
	LPTSTR buff=new TCHAR [20];
	HM.AddPtr(buff);	// �� HM ����̬�ռ�
	_stprintf(buff, TEXT("%ld"), number);
	return buff;
}

LPTSTR Str(unsigned int number)
{
	LPTSTR buff=new TCHAR [20];
	HM.AddPtr(buff);	// �� HM ����̬�ռ�
	_stprintf(buff, TEXT("%u"), number);
	return buff;
}

LPTSTR Str(unsigned long number)
{
	LPTSTR buff=new TCHAR [20];
	HM.AddPtr(buff);	// �� HM ����̬�ռ�
	_stprintf(buff, TEXT("%lu"), number);
	return buff;
}

LPTSTR Str(float number)
{
	LPTSTR buff=new TCHAR [40];
	HM.AddPtr(buff);	// �� HM ����̬�ռ�
	_stprintf(buff, TEXT("%.7g"), number);
	return buff;
}

LPTSTR Str(double number)
{
	LPTSTR buff=new TCHAR [40];
	HM.AddPtr(buff);	// �� HM ����̬�ռ�
	_stprintf(buff, TEXT("%.15g"), number);
	return buff;
}

LPTSTR Str(long double number)
{
	LPTSTR buff=new TCHAR [40];
	HM.AddPtr(buff);	// �� HM ����̬�ռ�
	_stprintf(buff, TEXT("%.15g"), number);
	return buff;
}

LPTSTR Str( LPCTSTR sText )	// ԭ�������󷵻�
{
	if (sText==0) {gEmptyTSTR[0]=0; return gEmptyTSTR;}  // �ݴ�

	LPTSTR buff =0;
	buff = new TCHAR [lstrlen(sText)+1];
	HM.AddPtr(buff);	// �� HM ����̬�ռ�
	_tcscpy(buff, sText); 

	return buff;
}



// ���ַ����е���ĸȫ��ת��Ϊ��д��UCase����Сд��LCase��
//   ����ת��������ַ��������ַ����ռ��Զ����١��� HM �Զ�����
LPTSTR LCase( LPCTSTR szStringSrc )
{
	if (szStringSrc==0) {gEmptyTSTR[0]=0; return gEmptyTSTR;}  // �ݴ�

	// ����һ���ַ����� buff
	LPTSTR buff =0;
	buff = new TCHAR [lstrlen(szStringSrc)+1];
	HM.AddPtr(buff);	// �� HM ����̬�ռ�
	_tcscpy(buff, szStringSrc); 
	
	// ת�� buff �е��ַ���
	CharLower(buff);

	// �������ַ�����buff��
	return buff;
}

LPTSTR UCase( LPCTSTR szStringSrc )
{
	if (szStringSrc==0) {gEmptyTSTR[0]=0; return gEmptyTSTR;}  // �ݴ�

	// ����һ���ַ����� buff
	LPTSTR buff =0;
	buff = new TCHAR [lstrlen(szStringSrc)+1];
	HM.AddPtr(buff);	// �� HM ����̬�ռ�
	_tcscpy(buff, szStringSrc); 
	
	// ת�� buff �е��ַ���
	CharUpper(buff);
	
	// �������ַ�����buff��
	return buff;
}


// �滻�ַ����������滻����ַ���
// �滻����ַ����ռ��Զ����䡢�� HM �Զ�����
LPTSTR Replace( LPCTSTR szStringSrc, 
			    LPCTSTR szFind, 
				LPCTSTR szReplaceWith, 
				int start/*=1*/, 
				int countLimit/*=-1*/, 
				eBStrCompareMethod compare/*=bcmBinaryCompare*/ )
{
	// ======================== ׼������ ========================
	// ��Դ�ַ���ָ��Ϊ0����Դ�ַ���Ϊ ""������ ""
	if (szStringSrc == 0) { gEmptyTSTR[0]=0; return gEmptyTSTR; } 
	if (*szStringSrc == 0) { gEmptyTSTR[0]=0; return gEmptyTSTR;} 
	
	// ��Ҫ�滻Ϊ�����ַ���ָ��Ϊ�գ�����Ҫ�滻Ϊ�����ַ���Ϊ�մ�
	if (szReplaceWith == 0) { gEmptyTSTR[0]=0; szReplaceWith=gEmptyTSTR; }

	// ����һ���ַ����� buff
	//   buff ��������Ϊ Դ�ַ������� + һ�� szReplaceWith �ĳ���
	LPTSTR buff = 0;
	int iFindLen = lstrlen(szFind);
	int iReplLen = lstrlen(szReplaceWith);
	int buffLen = lstrlen(szStringSrc) + iReplLen +1;
	buff = new TCHAR [buffLen];
	// ������� HM.AddPtr(buff); �� HM ����̬�ռ䣬����ܻ�Ҫ����ռ�
	_tcscpy(buff, szStringSrc); 

	// ��Ҫ���ҵ����ַ���ָ��Ϊ�գ������ַ���Ϊ ""������Դ�ַ���
	if (szFind == 0) return buff;
	if (*szFind == 0) return buff;

	// ���ý����� buff �ռ䲻��ʱ������ռ�ʱ�����󲽳� => ibuffLenExpandPer
	int ibuffLenExpandPer = 200;	
	if (iReplLen > ibuffLenExpandPer) ibuffLenExpandPer=iReplLen;
	
	// ======================== ���Һ��滻 ========================
	// ��Դ�ַ����е��ַ���һ������ buff��
	// �������� szFind�������� szFind ������ szReplaceWith
	TCHAR *p=(TCHAR *)(szStringSrc+start-1), *p1, *p2, *p3;
	TCHAR *buffWrite=buff;
	int iReplacedCount=0; 
	while (*p)
	{
		// ��Դ�ַ����� p λ�ò����Ƿ��� szFind ���
		p1=p; p2=(TCHAR *)szFind;
		while (*p1 && *p2)
		{
			// ���Ҫ�Ƚϵ������ַ���=> c1��c2
			TCHAR c1= *p1, c2= *p2;		// ͨ���� *p1��*p2 ���ݴ�������������Ժ󷴸����� * ���㣬�������Ч��
			if (compare == bcmTextCompare)
			{
				// �������ִ�Сд�Ƚϣ����ڽ� c1��c2 ͳһΪ��д
				if (c1>='a' && c1<='z') c1-=32;
				if (c2>='a' && c2<='z') c2-=32;
			}
			
			// ��� c1��c2 ����ȣ��������ڲ� while
			if (c1 != c2) break;
			
			// �Ƚ���һ���ַ�
			p1++;
			p2++;
		}	// end while (*p1 && *p2)

		// �����ڲ� while ѭ�������������
		//	 (1) �����ַ��� ����ĩβ����ʱ���� Դ�ַ��� �Ƿ񵽴�ĩβ����ʾ�Ѿ��ҵ�
		//	 (2) Դ�ַ��� ����ĩβ���������ַ���û�е���ĩβ����ʾû���ҵ�
		//	 (3) Դ�ַ��� �� Ŀ���ַ��� ��û�е���ĩβ��˵������ break �����ģ���ʾû���ҵ�
		// ֻ���ڵ� (1) �����(�Ѿ��ҵ�)ʱ��Ҫ�滻���������������ֱ�ӿ���Դ�ַ����� *p 
		if (*p2 == 0)
		{
			// �� (1) �������ִ���滻��
			//   ������ szReplaceWith ��������Դ�ַ�����
			//   ������ p ��λ��Խ��һ�� szFind �ĳ���
			p3 = (TCHAR *)szReplaceWith;
			while (*p3)
			{  *buffWrite = *p3; buffWrite++; p3++;  }
			p += (iFindLen-1);	// -1 ����Ϊ����� while ���Ҫִ�� p++
			
			// �����滻�������ж��滻��������
			iReplacedCount++;
			if (countLimit>0 && iReplacedCount>=countLimit) break; // ��������� while
		}
		else
		{
			// �� (2)��(3) �������ֱ�ӿ���Դ�ַ���
			*buffWrite = *p; buffWrite++;
		}

		// buff ��ʣ�೤������Ҫ���һ�� szReplaceWith �ĳ���
		if ( buffLen - (buffWrite-buff+1) < iReplLen )
		{
			// ��Ҫ���� buff
			// buff �ĳ�������Ҫ���һ�� szReplaceWith �ĳ���
			int buffSizeLast = buffLen * sizeof(TCHAR);
			buffLen += ibuffLenExpandPer;			// �¿ռ��С���ַ�������
			TCHAR *buff2=new TCHAR [buffLen];		// �����¿ռ�
			HM.CopyMem(buff2, buff, buffSizeLast);	// ���Ͽռ����ݿ������¿ռ�
			buffWrite = buff2 + (buffWrite-buff);	// ʹ buffWrite ָ���¿ռ����ͬλ��
			delete []buff;	// ɾ���Ͽռ�
			buff = buff2;		// ����ִ�� HM.AddPtr(buff); �����¿ռ�
		}

		// Դ�ַ���ָ�� p ָ����һ�ַ�
		p++;
	}	// end while (*p)

	*buffWrite = '\0';

	// ======================== ���ؽ�� ========================
	HM.AddPtr(buff);
	return buff;
}	




//////////////////////////////////////////////////////////////////////////
// ������ ����
//////////////////////////////////////////////////////////////////////////

LPTSTR ClipboardGetText()
{
	if (! OpenClipboard(NULL)) 	// OpenClipboard ʧ��
	{
		// ���� ""
		gEmptyTSTR[0] = TEXT('\0');
		return gEmptyTSTR;
	}

#ifdef UNICODE
	HANDLE hHandle = GetClipboardData(CF_UNICODETEXT);
#else
	HANDLE hHandle = GetClipboardData(CF_TEXT);
#endif
	
    if (hHandle == NULL) 
	{
		// ���� ""
		gEmptyTSTR[0] = TEXT('\0');
		CloseClipboard();
		return gEmptyTSTR;
	}
	else
	{
        LPTSTR szGlobal = (LPTSTR)GlobalLock(hHandle);
		if (szGlobal == NULL )
		{
			// ���� ""
			gEmptyTSTR[0] = TEXT('\0');
			GlobalUnlock(hHandle);
			CloseClipboard();
			return gEmptyTSTR;
		}
		else
		{
			int iLen = _tcslen(szGlobal);
			LPTSTR szText = new TCHAR [iLen + 1];
			HM.AddPtr(szText, true);
			_tcscpy(szText, szGlobal);
			GlobalUnlock(hHandle);
			CloseClipboard();
			return szText;
		}
    }
}

void ClipboardSetText( LPCTSTR szText )
{
	if (! OpenClipboard(NULL)) return;		// OpenClipboard ʧ��
	EmptyClipboard();

	HANDLE hHandle = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, (_tcslen(szText) + 1) * sizeof(TCHAR));
	LPTSTR szGlobal = (LPTSTR)GlobalLock(hHandle);
	_tcscpy(szGlobal, szText);
	GlobalUnlock(hHandle);
	
#ifdef UNICODE
	SetClipboardData (CF_UNICODETEXT, hHandle);
#else
    SetClipboardData (CF_TEXT, hHandle);
#endif

	CloseClipboard();
}

void ClipboardSetText( tstring stringText )
{
	ClipboardSetText(stringText.c_str());
}


void ClipboardSetBmp( HBITMAP hBmp )
{
	if (! OpenClipboard(NULL)) return;		// OpenClipboard ʧ��
	EmptyClipboard();
	SetClipboardData (CF_BITMAP, hBmp);
	CloseClipboard();
}

HBITMAP ClipboardGetBmp()
{
	HBITMAP hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
	CloseClipboard();
	return hBitmap;
}



void ClipboardClear()
{
	if (! OpenClipboard(NULL)) return;		// OpenClipboard ʧ��
	EmptyClipboard();
	CloseClipboard();
}



//////////////////////////////////////////////////////////////////////////
// �Զ��� ��̬���� ����
//////////////////////////////////////////////////////////////////////////

// template <typename REDIMTYPE>
// int Redim( REDIMTYPE *  &arr, int uboundCurrent, int toUBound, bool preserve=false )	// template ��������Ҫ��ͷ�ļ���




//////////////////////////////////////////////////////////////////////////
// �ļ����� ����
// �����ļ�λ�ö��� 0 ��ʼ
//////////////////////////////////////////////////////////////////////////


// ȫ�ֹ�ϣ���������д򿪵��ļ���Key=������ַ�������Ϊ�ļ���
CBHashLK mEFOpenedFiles;	


HANDLE EFOpen( LPCTSTR szFileName, 
			   eEFOpenStyle openStyle /*= EF_OpStyle_Binary*/, 
			   bool bShowMsgIfFail /*= true*/, 
			   LPCTSTR szFailInfo /*= TEXT("�޷����ļ���")*/, 
			   eEFShareStyle shareStyle /*= EF_ShareCanReadWrite*/, 
			   bool bDeleteOnClose /*= false*/ )
{
	DWORD iAccess=0, iDisposition=0, iAttr=0;
	HANDLE hFile = INVALID_HANDLE_VALUE;

	switch(openStyle)
	{
	case EF_OpStyle_Append:
		iAccess = GENERIC_WRITE;
		iDisposition = OPEN_EXISTING;
		iAttr = FILE_FLAG_SEQUENTIAL_SCAN;   // Indicates that the file is to be accessed sequentially from beginning to end. The system can use this as a hint to optimize file caching. If an application moves the file pointer for random access, optimum caching may not occur; however, correct operation is still guaranteed.
		break;
	case EF_OpStyle_Binary:
        iAccess = GENERIC_READ | GENERIC_WRITE;
        iDisposition = OPEN_ALWAYS;
        iAttr = FILE_FLAG_RANDOM_ACCESS;     // Indicates that the file is accessed randomly. The system can use this as a hint to optimize file caching.
		break;
	case EF_OpStyle_Input:
        iAccess = GENERIC_READ;
        iDisposition = OPEN_EXISTING;
        iAttr = FILE_FLAG_SEQUENTIAL_SCAN;
		break;
	case EF_OpStyle_Output:
        iAccess = GENERIC_WRITE;
        iDisposition = CREATE_ALWAYS;
        iAttr = FILE_FLAG_SEQUENTIAL_SCAN;
		break;
	default:
        goto errH;
		break;
	}

	if (bDeleteOnClose) iAttr |= FILE_FLAG_DELETE_ON_CLOSE;
	hFile = CreateFile(szFileName, iAccess, (DWORD)shareStyle, 0, iDisposition, iAttr, 0);
	if (hFile == INVALID_HANDLE_VALUE) goto errH;

    // ����� EF_OpStyle_Append ģʽ�����ļ���дָ���ƶ���ĩβ��λ�ô�0��ʼ��
	// ��Чλ��Ϊ��0-�ļ�����-1������Ϊ�ƶ����ļ����ȵ�λ�ü�ָ���´�д���λ�ã�
	if (openStyle == EF_OpStyle_Append) SetFilePointer(hFile, 0, 0, FILE_END);

	// ���ļ�����Ϣ�����ϣ��
	mEFOpenedFiles.Add(0, (long)hFile, 0, 0, szFileName);

	return hFile;

errH:
	int sizeErr = (lstrlen(szFileName) + lstrlen(szFailInfo) + 2);
	TCHAR * szErr = new TCHAR [sizeErr+1];
	_tcscpy(szErr, szFileName);
	_tcscat(szErr, TEXT("\r\n"));
	_tcscat(szErr, szFailInfo);
	if (bShowMsgIfFail) MsgBox(szErr);
	delete []szErr;

	//sFailAddiInfo = strTemp '�� sFailAddiInfo �ɷ���ʧ����Ϣ
        
    return INVALID_HANDLE_VALUE;
}

HANDLE EFOpen( tstring stringFileName, eEFOpenStyle openStyle /*= EF_OpStyle_Binary*/, bool bShowMsgIfFail /*= true*/, tstring stringFailInfo /*= TEXT("�� ����ļ��?)*/, eEFShareStyle shareStyle /*= EF_ShareCanReadWrite*/, bool bDeleteOnClose /*= false*/ )
{
	return EFOpen(stringFileName.c_str(), openStyle, bShowMsgIfFail, stringFailInfo.c_str(), shareStyle, bDeleteOnClose);
}


void EFClose( HANDLE hFile, bool bCloseAll/* = false*/ )
{
	if (bCloseAll)
	{
		// �ر������ļ�
		int i; 
		for (i=1; i<=mEFOpenedFiles.Count(); i++)
			CloseHandle((void *)mEFOpenedFiles.IndexToKey(i, false));
		mEFOpenedFiles.Clear();
	}
	else
	{
		// ���ر��ļ� hFile
		CloseHandle(hFile);

		// ���ļ�����Ϣ�ӹ�ϣ����ɾ��
		mEFOpenedFiles.Remove((long)hFile, false);
	}
}


LONGLONG EFLOF( HANDLE hFile )
{
	LARGE_INTEGER li = {0,0};
	li.LowPart = GetFileSize(hFile, (LPDWORD)&li.HighPart);
	return li.QuadPart;
}


LONGLONG EFSeekGet( HANDLE hFile )
{
	LARGE_INTEGER li={0,0};
	li.LowPart = SetFilePointer(hFile, li.LowPart, &li.HighPart, FILE_CURRENT);
	if (li.LowPart == 0xFFFFFFFF && GetLastError() != NO_ERROR)	// ���ó���
		li.QuadPart = -1;	
	return li.QuadPart; 
}


int EFSeekSet( HANDLE hFile, 
			   LONGLONG llReadPos, 
			   int iShowResume /*= 1*/, 
			   LPCTSTR szFailInfo /*= TEXT("�޷��ƶ��ļ���дָ�롣")*/ )
{
	LARGE_INTEGER li;
	bool blSuccess = false;
	EDlgBoxCmdID ms = idOk;

	li.QuadPart = llReadPos;
	do
    {
		li.LowPart = SetFilePointer(hFile, li.LowPart, &li.HighPart, FILE_BEGIN);
		if (li.LowPart == 0xFFFFFFFF && GetLastError() != NO_ERROR)	// ���ó���
		{
			blSuccess = false;
			ms = _EFRetryBox(hFile, iShowResume, szFailInfo, TEXT("Error") );
		}
		else	// if (li.LowPart == 0xFFFFFFFF && GetLa ...
		{
			blSuccess = true;
		}		// end if (li.LowPart == 0xFFFFFFFF && GetLa ...
	}
	while (!blSuccess && ms == idRetry );
	
	if (blSuccess)
		return 1;
	else
		{	if (ms == idIgnore) return -2; else return -1;  }
}


bool EFSeekSetEnd( HANDLE hFile )
{
	LARGE_INTEGER li={0,0};
	li.LowPart = SetFilePointer(hFile, li.LowPart, &li.HighPart, FILE_END);
	if (li.LowPart == 0xFFFFFFFF && GetLastError() != NO_ERROR)	// ���ó���
		return false;
	else
		return true;
}


bool EFEOF( HANDLE hFile )
{
	// ����ļ���ǰ��дλ��
	LARGE_INTEGER li={0,0};
	li.LowPart = SetFilePointer(hFile, li.LowPart, &li.HighPart, FILE_CURRENT);
	if (li.LowPart == 0xFFFFFFFF && GetLastError() != NO_ERROR)	// ���ó���
		return false;

	// ����ļ�����
	LONGLONG fileLen = EFLOF(hFile);

	// �жϵ�ǰ��дλ���Ƿ�Ϊ�ļ�ĩβ
	return (li.QuadPart>=fileLen);
}


bool EFBOF( HANDLE hFile )
{
	// ����ļ���ǰ��дλ��
	LARGE_INTEGER li={0,0};
	li.LowPart = SetFilePointer(hFile, li.LowPart, &li.HighPart, FILE_CURRENT);
	if (li.LowPart == 0xFFFFFFFF && GetLastError() != NO_ERROR)	// ���ó���
		return false;
	return (li.QuadPart == 0);
}


LONG EFGetBytes( HANDLE hFile, 
				 LONGLONG llReadPos, 
				 char * const pBuff, 
				 LONG iBuffMax /*= 131072*/, 
				 int iShowResume /*= 1*/ ,
				 LPCTSTR szFailInfo /*= TEXT("�޷���ȡ�ļ���")*/)
{
	LONG iBytesRead=0;	// ��ʵ��ȡ�˶����ֽ�
	int r=0;
	EDlgBoxCmdID ms = idOk;

	// �ƶ��ļ���дָ��
	if (llReadPos >= 0)  // llReadPos<0 ʱ���ƶ���дָ�룬Ϊ�ӵ�ǰ��дλ�ÿ�ʼ��
	{
		r = EFSeekSet(hFile, llReadPos, iShowResume, szFailInfo);  // �˺���������ᵯ�����ԶԻ���
		if (r < 0)  // �ƶ���дָ��ʧ��
			{ if (r == -2)  return -2; else return -1; }
	}
	
	// ��ȡ����
	ms = idOk;
	do 
	{
		r = ReadFile(hFile, pBuff, iBuffMax, (LPDWORD)&iBytesRead, 0);  // ���� ReadFile ���� 0���ɹ����� ��0
		int ii=GetLastError();
		if (r==0)
			ms = _EFRetryBox(hFile, iShowResume, szFailInfo, TEXT("Read Error") );
		else
			break;
	} while ( ms==idRetry );
	
	// ���غ���ֵΪʵ�ʶ�ȡ���ֽ���
	return iBytesRead;
}


LONG EFPutBytes( HANDLE hFile, 
				 LONGLONG llWritePos, 
				 char * const pBuff, 
				 LONG iBuffLen /*= 131072*/, 
				 int iShowResume /*= 1*/, 
				 LPCTSTR szFailInfo /*= TEXT("�޷���ȡ�ļ���")*/)
{
	LONG iBytesWritten=0;	// ��ʵд���˶����ֽ�
	int r=0;
	EDlgBoxCmdID ms = idOk;
	
	// �ƶ��ļ���дָ��
	if (llWritePos >= 0)  // llWritePos<0 ʱ���ƶ���дָ�룬Ϊ�ӵ�ǰ��дλ�ÿ�ʼд
	{
		r = EFSeekSet(hFile, llWritePos, iShowResume, szFailInfo);  // �˺���������ᵯ�����ԶԻ���
		if (r < 0)  // �ƶ���дָ��ʧ��
			{ if (r == -2)  return -2; else return -1; }
	}

	// д������
	ms = idOk;
	do 
	{
		r = WriteFile(hFile, pBuff, iBuffLen, (LPDWORD)&iBytesWritten, 0);  // ���� ReadFile ���� 0���ɹ����� ��0
		if (r==0)
			ms = _EFRetryBox(hFile, iShowResume, szFailInfo, TEXT("Write Error") );
		else
			break;
	} while ( ms==idRetry );

	// ���غ���ֵΪʵ��д����ֽ���
	return iBytesWritten;
}


BOOL EFFlushFile( HANDLE hFile )
{
	return FlushFileBuffers(hFile);
}


BOOL EFSetEndOfFile( HANDLE hFile, LONGLONG llPosEnd )
{
	if (llPosEnd >=0)  // �����µ��ļ���дλ��
        if (EFSeekSet(hFile, llPosEnd, 0) <0 ) return false; // ������λ��ʱ�������������ԶԻ���
    return SetEndOfFile(hFile);
}



EDlgBoxCmdID _EFRetryBox( HANDLE hFile, int iShowResume, LPCTSTR szFailInfo, LPCTSTR szTitle )
{
	if (iShowResume==0) return idOk;
	
	int sizeErr = (lstrlen(szFailInfo) + 50);	// ������Ϣ�ַ����ܳ���
	
	// �ӹ�ϣ���л�ȡ hFile ���ļ����ַ��� => szFile
	LPTSTR szFile = mEFOpenedFiles.ItemStr((long)hFile, false);
	if (szFile) sizeErr += lstrlen(szFile); 
	
	// �����ļ���дλ���ַ��� => szPos
	TCHAR szPos[30];						// ��ʾ�ļ���ǰλ�õ��ַ���
	_stprintf(szPos, TEXT("%.15g"), (double)EFSeekGet(hFile) );
	
	// ������ʾ��Ϣ => szErr
	TCHAR * szErr = new TCHAR [sizeErr+1];
	*szErr = 0;		// �� szErr �Ŀռ�׼��Ϊ�մ�
	if (szFile) { _tcscat(szErr, szFile); _tcscat(szErr, TEXT("\r\n")); }
	_tcscat(szErr, szFailInfo); _tcscat(szErr, TEXT("\r\n"));
	_tcscat(szErr, TEXT("position:")); 	_tcscat(szErr, szPos);
	
	// ��ʾ��ʾ��
	if (iShowResume==1)
		return MsgBox(szErr, szTitle, mb_RetryCancel, mb_IconError);
	else if (iShowResume==2)
		return MsgBox(szErr, TEXT("Error"), mb_AbortRetryIgnore, mb_IconError);
	else
		return idOk;	// �����δ������ʾ�򣬶����� idOK
	
	delete []szErr;
}


LONG EFPrint( HANDLE hFile, 
			  LPCTSTR szText, 
			  eEFLineFeed styleLineFeed /*= EF_LineSeed_CrLf*/, 
			  LONGLONG llWritePos /*= -1*/, 
			  int iShowResume /*= 1*/, 
			  LPCTSTR szFailInfo /*= TEXT("�޷����ļ���д���ַ�����")*/ )
{
	// ʹ�� char һ��д�� Ansi ��ʽ���ı�
	char * buff = 0; 
	int iLenBytes=0;

	if (szText==0 || *szText==0) 
	{
		// ���ַ������ַ���Ϊ�մ�������ӡ�մ�	
		iLenBytes = 1;
		buff = new char [iLenBytes + 2]; 
	}
	else
	{
		#ifdef UNICODE
			// ��ý���ַ��������ַ����������� -1 ʹ�����Զ����� szText �ĳ���
			// iLenBytes Ϊ�������� \0 ���ܹ��ֽ���
			iLenBytes = WideCharToMultiByte(CP_ACP, 0, szText, -1, NULL, 0, NULL, NULL);
			// �������ַ����Ŀռ�
			buff = new char [iLenBytes + 2];  // �����ı�����+\0�ĳ��ȶ�2���ֽڣ�\0(\r) \n \0
			// ת��Ϊ Ansi ���ַ������� aLenBytes ������Ҫ�����ֽ������ַ���
			WideCharToMultiByte(CP_ACP, 0, szText, -1, buff, iLenBytes, NULL, NULL);  
		#else
			iLenBytes = lstrlen(szText) + 1;
			buff = new char [ iLenBytes + 2 ];  // �����ı�����+\0�ĳ��ȶ�2���ֽڣ�\0(\r) \n \0
			strcpy(buff, szText);
		#endif
	}
    
    switch (styleLineFeed)
	{
	case EF_LineSeed_Lf:
		buff[iLenBytes-1] = 10;	// \n
		buff[iLenBytes] = 0;	// \0
		iLenBytes += 1;
		break;
	case EF_LineSeed_Cr:
		buff[iLenBytes-1] = 13;	// \r
		buff[iLenBytes] = 0;	// \0
		iLenBytes += 1;
		break;
	case EF_LineSeed_CrLf:
		buff[iLenBytes-1] = 13;	// \n
		buff[iLenBytes] = 10;	// \0
		buff[iLenBytes+1] = 0;	// \0
		iLenBytes += 2;
		break;
	case EF_LineSeed_None:
		break;
	}
	
    // iLenBytes-1 ȥ������ \0 �ֽ�
	LONG ret = EFPutBytes(hFile, llWritePos, buff, iLenBytes-1, iShowResume, szFailInfo);
	delete []buff;
	return ret;
}

LONG EFPrint( HANDLE hFile, tstring stringText, eEFLineFeed styleLineFeed /*= EF_LineSeed_CrLf*/, LONGLONG llWritePos /*= -1*/, int iShowResume /*= 1*/, tstring stringFailInfo /*= TEXT("�� ����ļ���д���?����?)*/ )
{
	return EFPrint(hFile, stringText.c_str(), styleLineFeed, llWritePos, iShowResume, stringFailInfo.c_str());
}





//////////////////////////////////////////////////////////////////////////
// CBHashLK ���ʵ��: �����ͼ�ֵ�Ĺ�ϣ��
//
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
// Static ������ֵ
//////////////////////////////////////////////////////////////////////
const int   CBHashLK::mcIniMemSize = 7;					// ��ʼ mem[] �Ĵ�С
const int   CBHashLK::mcMaxItemCount = 100000000;		// ���Ԫ�ظ������������ֵ�� long ��ʾ�ķ�Χ֮�ڣ�
const float CBHashLK::mcExpandMaxPort = 0.75;			// ����Ԫ�ظ������� 0.75*memCount ʱ������ mem[] �Ŀռ�
const int   CBHashLK::mcExpandCountThres = 10000;		// ���� mem[] �ռ�ʱ���� memCount С�ڴ�ֵ��ÿ������ memCount*2���� memCount ���ڴ�ֵ��ÿ������ Count+Count/2
const int   CBHashLK::mcExpandCountThresMax = 10000000;	// ���� mem[] �ռ�ʱ���� memCount �Ѵ��ڴ�ֵ����ÿ�β������� Count+Count/2����ֻ���� Count+mcExpandBigPer
const int   CBHashLK::mcExpandBigPer = 1000000;			// ���� mem[] �ռ�ʱ���� memCount �Ѵ��� mcExpandCountThresMax����ÿ�β������󵽵� Count+Count/2����ֻ���� Count+mcExpandBigPer
const int   CBHashLK::mcExpandMem2Per = 10;				// ÿ������ mem2[] �Ĵ�С
const int   CBHashLK::mcSeqMax = 5;						// ˳��������ֵ


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CBHashLK::CBHashLK(int memSize/*=0*/)
{
	mArrTable=0; mArrTableCount = -1;	// �޻�������

	memUsedCount = 0; 
	mem2 = 0;
	memCount2 = 0;
    memUsedCount2 = 0;
	
	if (memSize)
	{
		// ��ʼ���� memSize ���� mem[] �ռ䣬�� mem2[] �Ŀռ�
		RedimArrMemType(mem, memSize);
		memCount = memSize;
	}
	else
	{
		// ��ʼ���� mcIniMemSize ���� mem[] �ռ䣬�� mem2[] �Ŀռ�
		RedimArrMemType(mem, mcIniMemSize);
		memCount = mcIniMemSize;
	}
}

CBHashLK::~CBHashLK()
{
	Clear();
	// Clear() �����У����¿����˳�ʼ��С�� mem[] �ռ䣬�ٽ���ɾ������
	if (mem) delete[] mem;
	memCount = 0;
}



//////////////////////////////////////////////////////////////////////
// ���з���
//////////////////////////////////////////////////////////////////////

void CBHashLK::AlloMem(int memSize )
{
	/*
	�����ʼ��ʱֻ������ mcIniMemSize ��С�� l_Mem[]���Ժ���ʹ�����Զ��� \
	  �󣻵�������֪���ж�󣬿������ñ����������㹻�������Ժ󲻶� \
	  �Զ������ʱ��ע����ʱҪ��Ԥ�õ�Ԫ�ظ����ඨ��һЩ���������ռ� \
	  ʱ���ռ��ͻ���໹���Զ�����
	�˺���Ҳ�����ڽض� l_Mem[] ����û��ʹ�õĿռ�
      ע��memSize <= memUsedCount ʱ���ܾ����¶��壬��ȷ�����ݲ��ᶪʧ 
	*/

	if (memSize <= memUsedCount || memSize > mcMaxItemCount) return;
	int iPreMemCount;
	iPreMemCount = memCount;

	// ReDim Preserve mem(1 To memSize)
	RedimArrMemType(mem, memSize, memCount, true);
	memCount = memSize;

	if (iPreMemCount <= memCount) ReLocaMem(iPreMemCount); else ReLocaMem(memCount);

	// ��ϣ�������ָ������
	mTravIdxCurr = 0;

	// �� Index ���ʸ�Ԫ�صĻ�����������
    mArrTableCount = -1;
}

bool CBHashLK::Add( DataType data, KeyType key/*=0*/, DataLongType dataLong/*=0*/, DataLong2Type dataLong2/*=0*/, LPCTSTR dataStr/*=NULL*/, LPCTSTR dataStr2/*=NULL*/, double dataDouble/*=0.0*/, bool raiseErrorIfNotHas/*=true*/ )
{
	int idx;
	
	// ��ϣ���е����ݸ�����಻�ܳ��� mcMaxItemCount
	if (memUsedCount + memUsedCount2 >= mcMaxItemCount)
    {		
		if (raiseErrorIfNotHas)  throw (unsigned char)7;	// �����ڴ�
		return false;
	}
	
	// ��ǰ��ϣ���в�������ͬ�ġ���������
	if (IsKeyExist(key))
	{
		if (raiseErrorIfNotHas)  throw (unsigned char)5;	// ��Ч�Ĺ��̵��û����
		return false;
	}
	
	// ͨ������ AlloMemIndex �������һ�����ÿռ���±꣺idx
	idx = AlloMemIndex(key);
	
	if (idx > 0)
	{
		// ��õ��±�ֵΪ����ʱ��ʹ�� mem[] ����Ŀռ�
		mem[idx].Data = data;
		mem[idx].DataLong = dataLong;
		mem[idx].DataLong2 = dataLong2;
		mem[idx].DataDouble = dataDouble;
		mem[idx].Key = key;

		SaveItemString(&(mem[idx].DataStr), dataStr);
		SaveItemString(&(mem[idx].DataStr2), dataStr2);

		mem[idx].Used = true;

		memUsedCount = memUsedCount + 1;
	}
	else if (idx < 0)
	{
		// ��õ��±�ֵΪ����ʱ��ʹ�� mem2[] ����Ŀռ䣬_
		// �ռ��±�Ϊ idx �ľ���ֵ
		mem2[-idx].Data = data;
		mem2[-idx].DataLong = dataLong;
		mem2[-idx].DataLong2 = dataLong2;
		mem2[-idx].DataDouble = dataDouble;
		mem2[-idx].Key = key;

		SaveItemString(&(mem2[-idx].DataStr), dataStr);
		SaveItemString(&(mem2[-idx].DataStr2), dataStr2);

		mem2[-idx].Used = true;

		memUsedCount2 = memUsedCount2 + 1;
	}
	else // idx == 0
	{
		if (raiseErrorIfNotHas)  throw (unsigned char)9;	// �±�Խ�磺�޷����������ݿռ�
	}
	
	// ��ϣ�������ָ������
	mTravIdxCurr = 0;
	
	// �� Index ���ʸ�Ԫ�صĻ�����������
    mArrTableCount = -1;

	// �������سɹ�
    return true;
}


CBHashLK::DataType CBHashLK::Item( KeyType key, bool raiseErrorIfNotHas/*=true*/ )
{
	int idx;
	idx = GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (idx > 0)
		return mem[idx].Data;
	else if (idx < 0)
		return mem2[-idx].Data;
	else
		return 0;
}


CBHashLK::DataLongType CBHashLK::ItemLong( KeyType key, bool raiseErrorIfNotHas/*=true*/ )
{
	int idx;
	idx = GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (idx > 0)
		return mem[idx].DataLong;
	else if (idx < 0)
		return mem2[-idx].DataLong;
	else
		return 0;
}


CBHashLK::DataLong2Type CBHashLK::ItemLong2( KeyType key, bool raiseErrorIfNotHas/*=true*/ )
{
	int idx;
	idx = GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (idx > 0)
		return mem[idx].DataLong2;
	else if (idx < 0)
		return mem2[-idx].DataLong2;
	else
		return 0;
}

double CBHashLK::ItemDouble( KeyType key, bool raiseErrorIfNotHas/*=true*/ )
{
	int idx;
	idx = GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (idx > 0)
		return mem[idx].DataDouble;
	else if (idx < 0)
		return mem2[-idx].DataDouble;
	else
		return 0;

}


LPTSTR CBHashLK::ItemStr( KeyType key, bool raiseErrorIfNotHas/*=true*/ )
{
	int idx;
	idx = GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (idx > 0)
		return mem[idx].DataStr;
	else if (idx < 0)
		return mem2[-idx].DataStr;
	else
		return 0;

}

LPTSTR CBHashLK::ItemStr2( KeyType key, bool raiseErrorIfNotHas/*=true*/ )
{
	int idx;
	idx = GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (idx > 0)
		return mem[idx].DataStr2;
	else if (idx < 0)
		return mem2[-idx].DataStr2;
	else
		return 0;

}


// �ж�һ�� Key �Ƿ��ڵ�ǰ�����д���
bool CBHashLK::IsKeyExist( KeyType key )
{
	int idx;
	idx = GetMemIndexFromKey(key, false);
    return (idx != 0);
}

bool CBHashLK::Remove( KeyType key, bool raiseErrorIfNotHas/*=True*/ )
{
	int idx;
	
	// ���� GetMemIndexFromKey ������á�����Ϊ Key ���������ڿռ���±�
	idx = GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (idx == 0)
		return false;
	else if (idx > 0)
	{
		// ��ϣ���С�����Ϊ Key �������� mem[] �����У��±�Ϊ idx
		mem[idx].Used = false;
		mem[idx].Key = 0;
		SaveItemString(&(mem[idx].DataStr), 0);  // �ڶ�������Ϊ0��ɾ�� mem[idx].DataStr ָ��Ŀռ䣬���� mem[idx].DataStr=0;
		SaveItemString(&(mem[idx].DataStr2), 0); 

		memUsedCount = memUsedCount - 1;
	}
	else
	{
		// idx<0 ��ʾ����ϣ���С�����Ϊ Key �������� mem2[] ������ \
		// �±�Ϊ idx �ľ���ֵ
		// ɾ���±�Ϊ��-idx����Ԫ��

		SaveItemString(&(mem[-idx].DataStr), 0); // �ڶ�������Ϊ0��ɾ�� mem[-idx].DataStr ָ��Ŀռ䣬���� mem[-idx].DataStr=0;
		SaveItemString(&(mem[-idx].DataStr2), 0); 

		for(int i=-idx; i<= - 1; i++)
			mem2[i] = mem2[i+1];
		mem2[memUsedCount2].DataStr=0;		// ֱ������Ϊ0����˿ռ��Ѿ����ݸ���һԪ��
		mem2[memUsedCount2].DataStr2=0;		// ֱ������Ϊ0����˿ռ��Ѿ����ݸ���һԪ��
		memUsedCount2 = memUsedCount2 - 1;
	}

	// ��ϣ�������ָ������
	mTravIdxCurr = 0;

	// �� Index ���ʸ�Ԫ�صĻ�����������
    mArrTableCount = -1;

	// �������سɹ�
	return true;
}

void CBHashLK::StartTraversal()
{
	// ��ʼ�� NextXXX ... ��������
    mTravIdxCurr = 1;
}


CBHashLK::DataType CBHashLK::NextItem( bool &bRetNotValid )
{
	// ���� StartTraversal ���ô˺������� Data
    // �� bRetNotValid ���� True����˴α����ѽ�������ʱ��������ֵҲ��Ч��
	int idx;
	idx = TraversalGetNextIdx();
	if (idx > 0)
	{
		bRetNotValid = false;
		return mem[idx].Data;
	}
	else if (idx < 0)
	{
		bRetNotValid = false;
		return mem2[-idx].Data;
	}
	else
	{
		bRetNotValid = true;
		return 0;
	}
}

CBHashLK::DataLongType CBHashLK::NextItemLong( bool &bRetNotValid )
{
	// ���� StartTraversal ���ô˺������� DataLong
    // �� bRetEndNotValid ���� True����˴α����ѽ�������ʱ��������ֵҲ��Ч��
	int idx;
	idx = TraversalGetNextIdx();
	if (idx > 0)
	{
		bRetNotValid = false;
		return mem[idx].DataLong;
	}
	else if (idx < 0)
	{
		bRetNotValid = false;
		return mem2[-idx].DataLong;
	}
	else
	{
		bRetNotValid = true;
		return 0;
	}
}


CBHashLK::DataLong2Type CBHashLK::NextItemLong2( bool &bRetNotValid )
{
	// ���� StartTraversal ���ô˺������� DataLong
    // �� bRetEndNotValid ���� True����˴α����ѽ�������ʱ��������ֵҲ��Ч��
	int idx;
	idx = TraversalGetNextIdx();
	if (idx > 0)
	{
		bRetNotValid = false;
		return mem[idx].DataLong2;
	}
	else if (idx < 0)
	{
		bRetNotValid = false;
		return mem2[-idx].DataLong2;
	}
	else
	{
		bRetNotValid = true;
		return 0;
	}
}

double CBHashLK::NextItemDouble( bool &bRetNotValid )
{
	// ���� StartTraversal ���ô˺������� DataLong
    // �� bRetEndNotValid ���� True����˴α����ѽ�������ʱ��������ֵҲ��Ч��
	int idx;
	idx = TraversalGetNextIdx();
	if (idx > 0)
	{
		bRetNotValid = false;
		return mem[idx].DataDouble;
	}
	else if (idx < 0)
	{
		bRetNotValid = false;
		return mem2[-idx].DataDouble;
	}
	else
	{
		bRetNotValid = true;
		return 0;
	}
}

LPTSTR CBHashLK::NextItemStr( bool &bRetNotValid )
{
	// ���� StartTraversal ���ô˺������� DataLong
    // �� bRetEndNotValid ���� True����˴α����ѽ�������ʱ��������ֵҲ��Ч��
	int idx;
	idx = TraversalGetNextIdx();
	if (idx > 0)
	{
		bRetNotValid = false;
		return mem[idx].DataStr;
	}
	else if (idx < 0)
	{
		bRetNotValid = false;
		return mem2[-idx].DataStr;
	}
	else
	{
		bRetNotValid = true;
		return 0;
	}
}

LPTSTR CBHashLK::NextItemStr2( bool &bRetNotValid )
{
	// ���� StartTraversal ���ô˺������� DataLong
    // �� bRetEndNotValid ���� True����˴α����ѽ�������ʱ��������ֵҲ��Ч��
	int idx;
	idx = TraversalGetNextIdx();
	if (idx > 0)
	{
		bRetNotValid = false;
		return mem[idx].DataStr2;
	}
	else if (idx < 0)
	{
		bRetNotValid = false;
		return mem2[-idx].DataStr2;
	}
	else
	{
		bRetNotValid = true;
		return 0;
	}
}

CBHashLK::KeyType CBHashLK::NextKey( bool &bRetNotValid )
{
	// ���� StartTraversal ���ô˺������� String
    // �� bRetEndNotValid ���� True����˴α����ѽ�������ʱ��������ֵҲ��Ч��
	int idx;
	idx = TraversalGetNextIdx();
	if (idx > 0)
	{
		bRetNotValid = false;
		return mem[idx].Key;
	}
	else if (idx < 0)
	{
		bRetNotValid = false;
		return mem2[-idx].Key;
	}
	else
	{
		bRetNotValid = true;
		return 0;
	}
}

// �������Ԫ�أ��ض��� mcIniMemSize ���洢�ռ�
void CBHashLK::Clear( void )
{
	// ���	�� Index ���ʸ�Ԫ�صĻ�������
	if (mArrTable) {delete []mArrTable; mArrTable=0;}
	mArrTableCount=-1;

	// ɾ�� mem[] �� mem2[] �е�ÿ��Ԫ�ص� �ַ������� ָ��Ŀռ�
	int i;
	for (i=1; i<=memCount; i++)
	{
		if (mem[i].DataStr) {delete [] mem[i].DataStr; mem[i].DataStr=0; }
		if (mem[i].DataStr2) {delete [] mem[i].DataStr2; mem[i].DataStr2=0; }
	}
	for (i=1; i<=memCount2; i++)
	{
		if (mem2[i].DataStr) {delete [] mem2[i].DataStr; mem2[i].DataStr=0; }
		if (mem2[i].DataStr2) {delete [] mem2[i].DataStr2; mem2[i].DataStr2=0; }
	}

	// ɾ�� mem[] �� mem2[] �Ŀռ�
	delete [] mem; mem=0;
	delete [] mem2; mem2=0;
	memCount = 0; memUsedCount = 0;
	memCount2 = 0; memUsedCount2 = 0;

	// ���¿��ٿռ�
	RedimArrMemType(mem, mcIniMemSize, memCount, false);
	memCount = mcIniMemSize;

	mTravIdxCurr = 0;
}


// ���ع���Ԫ�ظ���
int CBHashLK::Count( void )
{
	return memUsedCount + memUsedCount2;
}




//////////////////////////////////////////////////////////////////////
// ˽�з���
//////////////////////////////////////////////////////////////////////

void CBHashLK::ReLocaMem( int preMemCountTo )
{
	/*
	���·��� mem[], mem2[] �ĸ�Ԫ�صĿռ䣬mem2[] ��ĳЩԪ�ؿ��ܱ� \
	�����ƶ��� mem
	���޸� memUsedCount,memUsedCount2, memCount2, mem2[] ��ֵ
	preMemCountTo ֻ���� mem[1 to preMemCountTo]��preMemCountTo �Ժ��Ԫ�ر���Ϊ \
	δ�ã������ǣ���������ζ����� mem2[] �е�����Ԫ��
	*/
	
	// �� mem[] �е���ʹ��Ԫ�غ� mem2[] �е�����Ԫ���ȷ��� memUsed[] �У� \
	// �� memUsed[] ����Ϊ�㹻��ʵ�� memUsed[] ֻʹ���� lngUsedCount ��Ԫ��
	MemType * memUsed;
	RedimArrMemType(memUsed, preMemCountTo + memUsedCount2);

	int iUsedCount=0;		
	int i;

	// �� mem[] ����ʹ�õ�Ԫ�ش��� memUsed[]
	for (i=1; i<=preMemCountTo; i++)
		if (mem[i].Used)
		{
			iUsedCount = iUsedCount + 1;
			memUsed[iUsedCount] = mem[i];
		}

	// �� mem2[] �е�����Ԫ�ش��� memUsed[]
	for (i=1; i<=memUsedCount2; i++)
	{
		iUsedCount = iUsedCount + 1;
		memUsed[iUsedCount] = mem2[i];
	}


	/*
	��ʱ memUsed[1 To lngUsedCount] ��Ϊ���� mem[] \
	�е���ʹ��Ԫ�� �� mem2[] �е�����Ԫ��
	*/

	// ��� mem��Ҳ��������� Used ��
	RedimArrMemType(mem, memCount, memCount, false); 
	memUsedCount=0;  // memUsedCount ��0���������ƶ���+1

	// ��� mem2��Ҳ��������� Used ��
	RedimArrMemType(mem2, -1, memCount2, false);
	memCount2 = 0;
	memUsedCount2 = 0; 

	// ����� memUsed[1 To lngUsedCount] �е�Ԫ�ذ��������Сӳ���±���� mem[]
	int idx;
	for (i=1; i<=iUsedCount; i++)
	{
		idx = AlloMemIndex(memUsed[i].Key, false);
		if (idx > 0)
		{
			mem[idx] = memUsed[i];
			mem[idx].Used = 1;
			memUsedCount = memUsedCount + 1;
		}
		else
		{
			mem2[-idx] = memUsed[i];
			mem2[-idx].Used = 1;
			memUsedCount2 = memUsedCount2 + 1;
		}
	}

	// ɾ����ʱ�ռ� memUsed
	delete [] memUsed; memUsed=0;

	// ��ϣ�������ָ������
	mTravIdxCurr = 0;
	
	// �� Index ���ʸ�Ԫ�صĻ�����������
    mArrTableCount = -1;
}


// �ض��� mem[] �����С������ mem[] �Ŀռ�
void CBHashLK::ExpandMem( void )
{
	int iCount, iPreMemCount;

	// �����ϣ���й�����������
	iCount = memUsedCount + memUsedCount2;

	// ȡ�����������������͡���ǰ mem[] �Ŀռ����������ߵĽϴ�ֵ
	if (iCount < memCount) iCount = memCount;

	// ���������ռ�֮ǰ�ġ�ԭ���� mem[] �Ŀռ�����
	iPreMemCount = memCount;

	
	if (iCount<1) iCount=1;		// ���� iCount Ϊ0ʱ���޷�����ռ�
	if (iCount < mcExpandCountThres)
	{
		// ��������������Ƚ��١����������ռ�Ϊԭ����2��
		iCount = iCount * 2;

	}
	else if (iCount < mcExpandCountThresMax)
	{
		// ������������Ѿ����е�ࡱ���������ռ�Ϊԭ����1.5��
		iCount = iCount * 3 / 2;
	}
	else
	{
		// ��������������ܶࡱ�������� mcExpandBigPer ���ռ�
		iCount = iCount + mcExpandBigPer;
	}

	// �ض��������С
	// ReDim Preserve mem(1 To lngCount)
	RedimArrMemType(mem, iCount, memCount, true);
	memCount = iCount;

	// ���������С�����°��������������ݵ���λ�ã�������Ҫ����
	// �����ռ�֮ǰ�ġ�ԭ���� mem[] �Ŀռ�����
	ReLocaMem(iPreMemCount);

	// ��ϣ�������ָ������
	mTravIdxCurr = 0;
	
	// �� Index ���ʸ�Ԫ�صĻ�����������
    mArrTableCount = -1;
}

int CBHashLK::AlloSeqIdx( int fromIndex, int toIndex )
{
    /*
	 �� mem[] ��һ��ûʹ�õĿռ䣬�� fromIndex ��ʼ�� \
		�� toIndex ����
	 ���� mem[] ��һ��ûʹ��Ԫ�ص��±꣬û�ҵ����� 0
	*/
	int i;
	if (fromIndex <= 0)  fromIndex = 1;
	if (toIndex > memCount) toIndex = memCount;
	
	for (i=fromIndex; i<=toIndex; i++)
		if (! mem[i].Used) return i; 

	return 0;
}

// ������ϣ�������ݴ��� mArrTable()������ mArrTableCount Ϊ���ݸ��������سɹ���ʧ�ܣ�
bool CBHashLK::RefreshArrTable()
{
	int iCount;
	int i,j;
	
	// �����ϣ���й�����������
	iCount = memUsedCount + memUsedCount2;
	
	mArrTableCount=iCount;
	if (mArrTableCount<=0) return false;
	
	if (mArrTable) {delete []mArrTable; mArrTable=0;}
	mArrTable=new int [iCount+1];	// ʹ�����±��1��ʼ
	
	j=1;
	for (i=1; i<=memCount; i++)
	{
		if (mem[i].Used)
		{
			if (j > iCount) return false;
			
			mArrTable[j] = i;		// �� ��ϣ��ı��������ڵ� mem[] ���±� i ���� mArrTable[j]
			mem[i].Index = j;		// �� ��ϣ��ı����� �� Index ��Ա�м�¼ mArrTable ���±� j

			j=j+1;
		}
	}
	
	for (i=1; i<=memUsedCount2; i++)
	{
		if (mem2[i].Used)
		{
			if (j > iCount) return false;
			
			mArrTable[j] = -i;		// �� ��ϣ��ı��������ڵ� mem2[] ���±� i ��ȡ�������� mArrTable[j]
			mem[i].Index = j;		// �� ��ϣ��ı����� �� Index ��Ա�м�¼ mArrTable ���±� j
			
			j=j+1;
		}
	}
	
	return true;
}




int CBHashLK::AlloMemIndex( KeyType key, bool CanExpandMem/*=true */ )
{
	/* 
	  ���� Key ����һ�� mem[] �е�δ�ô洢�ռ䣬���� mem[] �����±�
	  ��� Key �Ǹ�ֵ����ת��Ϊ�����������Ĵ洢�ռ�
		���ظ�ֵ������ mem[] ���ҵ��ռ䣺����ֵ�ľ���ֵΪ mem2[] �� \
		��һ�������±�ռ䣨mem2[]�Զ�Redim�����Դ��� mem2[]
	  ������ȷ������һ����ʹ�õĿռ䣬���������� mem2[] �еĿռ�
	  �����������޸� memUsedCount2 ��ֵ���� redim mem2[]
		CanExpandMem=true ʱ�����������Զ����� mem[]�����򲻻��Զ�����
		
		������
		1. ���� Key Mod memCount + 1���� Index -> idxMod
		2. �������Ԫ���Ѿ�ʹ�ã���Key�Ƿ� < cMaxNumForSquare (sqr(2^31)=46340) \
		�� <����ƽ�� Key��Ȼ�� mod memCount + 1�� \
		�� >=�����ð�λ����λ���㣬����� key �ĸ������֣�Ȼ�� mod memCount + 1
		��������������˲� Index -> idxSq
		3. �� memCount-idxMod+1 -> idxModRev
		4. �� memCount-idxSq+1 -> idxSqRev
		5. �������ҵ��� Index ����ʹ���ˣ��� Count �Ƿ� > \
		mcExpandMaxPort*Count�����ǣ��� CanExpandMem=true�� \
		������ mem[] �Ĵ洢�ռ䣬Ȼ��ݹ鱾���̣��ظ� 1-4 ��
		6. �� idxMod+1,+2,...,+mcSeqMax���� idxMod-1,-2,...,-mcSeqMax
		7. ��û�У����ظ�ֵ������ֵΪ mem2[] ����һ�����ÿռ䣬�Դ��� mem2[]
	*/


	const int cMaxNumForSquare = 46340;
	
	int idxMod=0, idxSq=0;
    int idxModRev=0, idxSqRev=0;
    int iCount=0;
    int keyToCalc=key; // ������ Key����ԶΪ>0����

	keyToCalc = key;
	if (keyToCalc < 0) keyToCalc = 0 - keyToCalc;	// ��� Key �Ǹ�ֵ����ת��Ϊ�����������Ĵ洢�ռ�
	iCount = memUsedCount + memUsedCount2;
    
	if (memCount) 
	{		
		// 1: ���� Key Mod memCount + 1���� Index -> idxMod
		idxMod = keyToCalc % memCount + 1;
		if (! mem[idxMod].Used) return idxMod;
    
		// 2: �� ƽ��Key ���ٳ���ȡ�࣬�� Index -> idxSq
		if (keyToCalc <= cMaxNumForSquare)
		{
			idxSq = (keyToCalc * keyToCalc) % memCount + 1;
		}
		else
		{
			int kBitSum=0;
			kBitSum = (keyToCalc & 0xFFFF0000)>>16;
			kBitSum += (keyToCalc & 0xFF00)>>8;
			kBitSum += (keyToCalc & 0xF0)>>4;
			kBitSum += (keyToCalc & 0xF);
			idxSq = kBitSum % memCount + 1;
		}
		if (! mem[idxSq].Used) return idxSq;

		// 3: ���Ե����� idxMod ���ռ� -> idxModRev
		idxModRev = memCount - idxMod + 1; 
		if (! mem[idxModRev].Used) return idxModRev;
    
		// 4: ���Ե����� idxSq ���ռ� -> idxSqRev
		idxSqRev = memCount - idxSq + 1;
		if (! mem[idxSqRev].Used) return idxSqRev;
	}
    
    // 5: ����ռ�ʹ�ðٷֱȳ�����ֵ�������� mem[] �� �ռ�
    if (CanExpandMem && iCount > mcExpandMaxPort * memCount)
	{
		ExpandMem();  // ���� mem[] �Ŀռ�
		return AlloMemIndex(key, CanExpandMem); // �ݹ飬�ظ�1-4��
	}
        
    
    int lngRetIdx;
    
    // 6: �� idxMod ��ʼ��ǰ������������� mcSeqMax ���ռ�
    int idxMdSta, idxMdEnd; 
    idxMdSta = idxMod - mcSeqMax; idxMdEnd = idxMod + mcSeqMax;
    lngRetIdx = AlloSeqIdx(idxMdSta, idxMod - 1); 
    if (lngRetIdx > 0) return lngRetIdx;
    lngRetIdx = AlloSeqIdx(idxMod + 1, idxMdEnd);
    if (lngRetIdx > 0) return lngRetIdx; 
    
    // 8: ���ظ�ֵ������ֵΪ mem2[] ����һ��Ԫ�أ��Դ��� mem2[]
    if (memUsedCount2 + 1 > memCount2)
    {    
        // ReDim Preserve mem2(1 To mcExpandMem2Per)
		RedimArrMemType(mem2, memCount2 + mcExpandMem2Per, memCount2, true);
		memCount2 = memCount2 + mcExpandMem2Per;
	}

    return -(memUsedCount2 + 1);
}


int CBHashLK::FindSeqIdx( KeyType key, int fromIndex, int toIndex )
{
	
    // �� mem[] �м�ΪKey��Ԫ���±꣬�� fromIndex ��ʼ�� \
	//	�� toIndex ����
	//	���� mem[] ���ҵ������±꣨>0����û�ҵ����� 0

	int i;
	if (fromIndex < 1) fromIndex = 1;
	if (toIndex > memCount) toIndex = memCount;
	
	for (i=fromIndex; i<=toIndex; i++)
		if ((mem[i].Used) && mem[i].Key == key )
			return i;
	
	return 0;
}




int CBHashLK::TraversalGetNextIdx( void )
{
	// �� NextXXX ��������ʱ��������һ����Next���� mem[]�±꣨����ֵ>0���� \
	// �� mem2[] ���±꣨����ֵ<0�������ѱ�������������ֵ=0��
	
	int iRetIdx;
	
	if (mTravIdxCurr > memCount ||
		-mTravIdxCurr > memCount2 ||
		mTravIdxCurr == 0) return 0;
	
	if (mTravIdxCurr > 0)
	{
		//////////// �� mem[] ���� ////////////
		while (! mem[mTravIdxCurr].Used)
		{
			mTravIdxCurr = mTravIdxCurr + 1;
			if (mTravIdxCurr > memCount) break;
		}
		
		if (mTravIdxCurr > memCount)
		{
			//// �ѱ������������� mem2[] �л������ݼ������� mem2[] ////
			if (memCount2 > 0)
			{
				// �����´α��� mem2[] �����ݵ��±�ĸ���
				mTravIdxCurr = -1;
				// ִ������� if mTravIdxCurr < 0 Then 
			}
			else
			{
				// ���ؽ���
				iRetIdx = 0;
				return iRetIdx;
			}
		}
		else
		{
			//// ���� mTravIdxCurr ////
			iRetIdx = mTravIdxCurr;
			// �����´α���ָ�� ָ����һ��λ�ã����� mem[] ����һ���� \
			// ���� mem2[] ����ʼ��
			mTravIdxCurr = mTravIdxCurr + 1;
			if (mTravIdxCurr > memCount) if (memCount2 > 0) mTravIdxCurr = -1;
			return iRetIdx;
		}
	}
	
	if (mTravIdxCurr < 0)
	{
		//////////// �� mem2[] ���� ////////////
		while (! mem2[-mTravIdxCurr].Used)
		{	
			mTravIdxCurr = mTravIdxCurr - 1;
			if (-mTravIdxCurr > memCount2) break;
		}
		
		if (-mTravIdxCurr > memCount2)
		{
			//// �ѱ������� ////
			// ���ؽ���
			iRetIdx = 0; 
		}
		else
		{
			// ���ظ�ֵ�� mTravIdxCurr
			iRetIdx = mTravIdxCurr;
			// ���� mTravIdxCurr ��ָ��
			mTravIdxCurr = mTravIdxCurr - 1;
		}
		return iRetIdx;
	}
	
	return 0;
}




// �ض��� һ�� MemType ���͵����飨������� mem[] �� mem2[]���Ĵ�С���¶���ռ��Զ�����
// arr��Ϊ����ָ�룬�ɴ��ݣ�mem �� mem2�����������޸Ĵ�ָ���ָ��
// toUBound��ΪҪ�ض����������Ͻ磬����Ϊ��[0] to [toUBound]��Ϊ -1 ʱ�����ٿռ䣬������ɾ��ԭ
//	 �ռ䣬�� arr �ᱻ��Ϊ0
// uboundCurrent��Ϊ�ض���ǰ������Ͻ� [0] to [uboundCurrent]��Ϊ -1 ��ʾ��δ���ٹ��ռ�Ϊ��һ�ε���
// preserve����������ԭʼ���ݷ��򲻱���
// �����¿ռ��ϱ꣬�� toUBound
int CBHashLK::RedimArrMemType( MemType * &arr, int toUBound/*=-1*/, int uboundCurrent/*=-1*/, bool preserve/*=false*/ )
{
	// �����¿ռ䣺[0] to [toUBound]
	if (toUBound >= 0)
	{
		MemType * ptrNew = new MemType [toUBound + 1];		// +1 Ϊʹ�����±���� toUBound
		// �¿ռ�����
		memset(ptrNew, 0, sizeof(MemType)*(toUBound + 1));
		
		// ��ԭ�пռ����ݿ������¿ռ�
		if (preserve && arr!=0 && uboundCurrent>=0)
		{
			int ctToCpy;										// ����ԭ�����ݣ���Ҫ�����ڴ�� MemType Ԫ�ظ���
			ctToCpy = uboundCurrent;
			if (uboundCurrent>toUBound) ctToCpy = toUBound;		// ȡ uboundCurrent �� toUBound ����Сֵ
			ctToCpy = ctToCpy + 1;								// ���� +1����Ϊ uboundCurrent �� toUBound ���������Ͻ�
			memcpy(ptrNew, arr, sizeof(MemType)*ctToCpy); 
		}

		// ɾ��ԭ�пռ�
		if (arr!=0 && uboundCurrent>=0) delete [] arr;

		// ָ��ָ���¿ռ�
		arr = ptrNew;
		return toUBound;
	}
	else		// if (toUBound < 0)�������ٿռ䣬ɾ��ԭ�пռ�
	{
		if(arr!=0 && uboundCurrent>=0) delete [] arr;
		arr = 0;
		return 0;
	}
	
}


int CBHashLK::GetMemIndexFromKey( KeyType key, bool raiseErrorIfNotHas/*=true*/ )
{
	const int cMaxNumForSquare = 46340;  // sqrt(2^31)=46340
    
    int idxMod=0, idxSq=0;
    int idxModRev=0, idxSqRev=0;
    int keyToCalc=key; // ������ Key����ԶΪ>=0����
    if (keyToCalc < 0) keyToCalc = 0 - keyToCalc;

	if (memCount)
	{
		// 1: ���� Key Mod memCount + 1���� Index -> idxMod
		idxMod = keyToCalc % memCount + 1;
		if (mem[idxMod].Used && mem[idxMod].Key == key) 
			return idxMod;
    
		// 2: �� ƽ��Key���ٳ���ȡ�࣬�� Index -> idxSq
		if (keyToCalc <= cMaxNumForSquare)
		{
			idxSq = (keyToCalc * keyToCalc) % memCount + 1;
		}
		else
		{
			int kBitSum=0;
			kBitSum = (keyToCalc & 0xFFFF0000)>>16;
			kBitSum += (keyToCalc & 0xFF00)>>8;
			kBitSum += (keyToCalc & 0xF0)>>4;
			kBitSum += (keyToCalc & 0xF);
			idxSq = kBitSum % memCount + 1;
		}
		if (mem[idxSq].Used && mem[idxSq].Key == key)
			return idxSq;
    
		// 3: ���Ե����� idxMod ���ռ� -> idxModRev
		idxModRev = memCount - idxMod + 1;
		if (mem[idxModRev].Used && mem[idxModRev].Key == key)
		   return idxModRev;
    
		// 4: ���Ե����� idxSq ���ռ� -> idxSqRev
		idxSqRev = memCount - idxSq + 1;
		if (mem[idxSqRev].Used && mem[idxSqRev].Key == key)
		   return idxSqRev;
	}

    int lngRetIdx=0;
    
    // 6: �� idxMod ��ʼ��ǰ������������� mcSeqMax ���ռ�
    int idxMdSta, idxMdEnd;
    idxMdSta = idxMod - mcSeqMax; idxMdEnd = idxMod + mcSeqMax;
    lngRetIdx = FindSeqIdx(key, idxMdSta, idxMod - 1);
    if (lngRetIdx > 0)  return  lngRetIdx;
    lngRetIdx = FindSeqIdx(key, idxMod + 1, idxMdEnd);
    if (lngRetIdx > 0)  return  lngRetIdx;
    
    // 7: �ٲ鿴 mem2[] �е�Ԫ����û��
    for (int i=1; i<=memUsedCount2; i++)
        if (mem2[i].Used && mem2[i].Key == key) return -i;
	
	if (raiseErrorIfNotHas) throw (unsigned char)5;	// ��Ч�Ĺ��̵��û����
	return 0;
}

// �� index ��������� mem[] �е��±꣨����ֵ>0������ mem2[] �е��±꣨����ֵ<0���������� 0
int CBHashLK::GetMemIndexFromIndex( int index, bool raiseErrorIfNotHas/*=true*/ )
{
	if (mArrTableCount != memUsedCount + memUsedCount2) RefreshArrTable(); // ˢ�����黺��
	if (index<1 || index>mArrTableCount)
	{
		if (raiseErrorIfNotHas)  throw (unsigned char)5;	// ��Ч�Ĺ��̵��û����
		return 0;
	}
	
	int idx=mArrTable[index];
	if (idx==0) 
	{
		if (raiseErrorIfNotHas)  throw (unsigned char)7;	// �����ڴ棨mArrTable[index]����Ϊ0��
		return 0;
	}
	else
		return idx;
}


// �� new �������ַ����ռ䣬�� ptrNewString ָ����ַ����������¿ռ䣻
//   ptrSaveTo ��һ�������ַ�����ַ��ָ������ĵ�ַ����ָ���ָ�����������
//   ���� new ���ٵ����ַ����ռ�ĵ�ַ�������� ��*ptrSaveTo = �¿ռ��ַ��
// �����ͷš�*ptrSaveTo����ָ��Ŀռ�Ĺ���
//   �� ptrSaveTo �����ɱ����� &(mem[i].key) ��ָ���ָ�룻ptrNewString �ɱ������µ� key
//   ����ɡ�mem[i].key=key���Ĳ������������޸� mem[i].key �����ݣ�
//   ��ɾ������ָ��Ŀռ䣬������ָ���¿ռ�
// ��� key Ϊ��ָ�룬���ͷš�*ptrSaveTo����ָ��Ŀռ�
void CBHashLK::SaveItemString( TCHAR ** ptrSaveTo, LPCTSTR ptrNewString )
{
	// ע�� ptrSaveTo �Ǹ�����ָ��
	if (ptrSaveTo==0) return;  // û�б����λ��
	
	// ��� ptrSaveTo ָ���ָ�������Ϊ����ָ�롱����ʾҪ����֮������
	//   ������һ����ǰ���ٵĿռ��ַ��Ӧ��ɾ����ǰ���ٵĿռ�
	if (*ptrSaveTo != 0) {delete [] (*ptrSaveTo); *ptrSaveTo=0; }
	
	if (ptrNewString)
	{
		// �����¿ռ䣬���� ptrNewString ����ַ������¿ռ�
		TCHAR * p = new TCHAR [lstrlen(ptrNewString)+1];
		lstrcpy(p, ptrNewString);
		
		// ʹ *ptrSaveTo ָ���¿ռ�
		*ptrSaveTo = p;
	}
}



// ---------------- �� Index ������������(����Key����KeyΪֻ��) ----------------
// ע������������ɾ��Index ���ܻ�仯��ĳ���ݵ� Index ����������һһ��Ӧ

CBHashLK::DataType CBHashLK::ItemFromIndex( int index, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromIndex(index, raiseErrorIfNotHas);
	if (ii > 0)
		return mem[ii].Data;
	else if (ii < 0)
		return mem2[-ii].Data;
	else
		return 0;
}

CBHashLK::DataLong2Type CBHashLK::ItemLong2FromIndex( int index, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromIndex(index, raiseErrorIfNotHas);
	if (ii > 0)
		return mem[ii].DataLong2;
	else if (ii < 0)
		return mem2[-ii].DataLong2;
	else
		return 0;
}

CBHashLK::DataLongType CBHashLK::ItemLongFromIndex( int index, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromIndex(index, raiseErrorIfNotHas);
	if (ii > 0)
		return mem[ii].DataLong;
	else if (ii < 0)
		return mem2[-ii].DataLong;
	else	
		return 0;
}

double CBHashLK::ItemDoubleFromIndex( int index, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromIndex(index, raiseErrorIfNotHas);
	if (ii > 0)
		return mem[ii].DataDouble;
	else if (ii < 0)
		return mem2[-ii].DataDouble;
	else
		return 0;
}

LPTSTR CBHashLK::ItemStrFromIndex( int index, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromIndex(index, raiseErrorIfNotHas);
	if (ii > 0)
		return mem[ii].DataStr;
	else if (ii < 0)
		return mem2[-ii].DataStr;
	else			
		return 0;
}

LPTSTR CBHashLK::ItemStr2FromIndex( int index, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromIndex(index, raiseErrorIfNotHas);
	if (ii > 0)
		return mem[ii].DataStr2;
	else if (ii < 0)
		return mem2[-ii].DataStr2;
	else			
		return 0;	
}

CBHashLK::KeyType CBHashLK::IndexToKey( int index, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromIndex(index, raiseErrorIfNotHas);
	if (ii > 0)
		return mem[ii].Key;
	else if (ii < 0)
		return mem2[-ii].Key;
	else			
		return 0;	
}


int CBHashLK::KeyToIndex( KeyType key, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	if (mArrTableCount != memUsedCount + memUsedCount2) RefreshArrTable(); // ˢ�����黺��
	ii=GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (ii > 0)
		return mem[ii].Index;
	else if (ii < 0)
		return mem2[-ii].Index;
	else
		return 0;
}


// ---------------- �� Key ������������ ----------------

bool CBHashLK::ItemSet( KeyType key, DataType vNewValue, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (ii == 0)
		return false;
	else if (ii > 0)
		mem[ii].Data = vNewValue;
	else if (ii < 0)
		mem2[-ii].Data = vNewValue;
	return true;
}

bool CBHashLK::ItemLongSet( KeyType key, DataLongType vNewValue, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (ii == 0)
		return false;
	else if (ii > 0)
		mem[ii].DataLong = vNewValue;
	else if (ii < 0)
		mem2[-ii].DataLong = vNewValue;
	return true;	
}


bool CBHashLK::ItemLong2Set( KeyType key, DataLong2Type vNewValue, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (ii == 0)
		return false;
	else if (ii > 0)
		mem[ii].DataLong2 = vNewValue;
	else if (ii < 0)
		mem2[-ii].DataLong2 = vNewValue;
	return true;	
}

bool CBHashLK::ItemDoubleSet( KeyType key, double vNewValue, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (ii == 0)
		return false;
	else if (ii > 0)
		mem[ii].DataDouble = vNewValue;
	else if (ii < 0)
		mem2[-ii].DataDouble = vNewValue;
	return true;	
}

bool CBHashLK::ItemStrSet( KeyType key, LPCTSTR vNewValue, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (ii == 0)
		return false;
	else if (ii > 0)
		SaveItemString(&(mem[ii].DataStr), vNewValue);
	else if (ii < 0)
		SaveItemString(&(mem2[-ii].DataStr), vNewValue);
	return true;	
}

bool CBHashLK::ItemStr2Set( KeyType key, LPCTSTR vNewValue,bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromKey(key, raiseErrorIfNotHas);
	if (ii == 0)
		return false;
	else if (ii > 0)
		SaveItemString(&(mem[ii].DataStr2), vNewValue);
	else if (ii < 0)
		SaveItemString(&(mem2[-ii].DataStr2), vNewValue);
	return true;	
}

// ---------------- �� Index ������������(KeyΪֻ����������Key) ----------------
// ע������������ɾ��Index ���ܻ�仯��ĳ���ݵ� Index ����������һһ��Ӧ

bool CBHashLK::ItemFromIndexSet( int index, DataType vNewValue, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromIndex(index, raiseErrorIfNotHas);
	if (ii == 0)
		return false;
	else if (ii > 0)
		mem[ii].Data = vNewValue;
	else if (ii < 0)
		mem2[-ii].Data = vNewValue;
	return true;
}

bool CBHashLK::ItemLongFromIndexSet( int index, DataLongType vNewValue, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromIndex(index, raiseErrorIfNotHas);
	if (ii == 0)
		return false;
	else if (ii > 0)
		mem[ii].DataLong = vNewValue;
	else if (ii < 0)
		mem2[-ii].DataLong = vNewValue;
	return true;
}

bool CBHashLK::ItemLong2FromIndexSet( int index, DataLong2Type vNewValue, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromIndex(index, raiseErrorIfNotHas);
	if (ii == 0)
		return false;
	else if (ii > 0)
		mem[ii].DataLong2 = vNewValue;
	else if (ii < 0)
		mem2[-ii].DataLong2 = vNewValue;
	return true;	
}

bool CBHashLK::ItemDoubleFromIndexSet( int index, double vNewValue, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromIndex(index, raiseErrorIfNotHas);
	if (ii == 0)
		return false;
	else if (ii > 0)
		mem[ii].DataDouble = vNewValue;
	else if (ii < 0)
		mem2[-ii].DataDouble = vNewValue;
	return true;	
}

bool CBHashLK::ItemStrFromIndexSet( int index, LPCTSTR vNewValue, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromIndex(index, raiseErrorIfNotHas);
	if (ii == 0)
		return false;
	else if (ii > 0)
		SaveItemString(&(mem[ii].DataStr), vNewValue);
	else if (ii < 0)
		SaveItemString(&(mem2[-ii].DataStr), vNewValue);
	return true;	
}

bool CBHashLK::ItemStr2FromIndexSet( int index, LPCTSTR vNewValue, bool raiseErrorIfNotHas/*=true*/ )
{
	int ii;
	ii=GetMemIndexFromIndex(index, raiseErrorIfNotHas);
	if (ii == 0)
		return false;
	else if (ii > 0)
		SaveItemString(&(mem[ii].DataStr2), vNewValue);
	else if (ii < 0)
		SaveItemString(&(mem2[-ii].DataStr2), vNewValue);
	return true;
}









//////////////////////////////////////////////////////////////////////
// CBArrLink ���ʵ�֣���Ч����������
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Static ������ֵ
//////////////////////////////////////////////////////////////////////
const int   CBArrLink::mcItemsPerArr = 512;		// ÿ�������Ԫ�ظ�����Ĭ��ֵ����ֵ����Ϊ0������ͨ�����캯���ı�
const int	CBArrLink::mcppArrInit = 128;  		// ����������ַ��ָ�������ʼ�ռ��С����ֵ����С��2��
const int	CBArrLink::mcppArrExpPer = 128;  	// ����������ַ��ָ������ÿ�������Ŀռ䣨��ֵ����С��1��


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBArrLink::CBArrLink(int iItemsPerArr/*=0*/)
{
	// ��Ա��������ֵ

	// ÿ�������Ԫ�ظ�����Ĭ��ֵ
	if (iItemsPerArr>0)
		m_ItemsPerArr = iItemsPerArr;	
	else
		m_ItemsPerArr = mcItemsPerArr;	

	ppArr = 0; 
	m_ppArrUbound = 0;
	m_ppArrUsedCount = 0;
	m_DataCount = 0;
	m_ptrArrRet = 0;

	// �����ʼ�ռ�
	Init();
}

CBArrLink::~CBArrLink()
{
	Dispose();
}


//////////////////////////////////////////////////////////////////////
// ���к���
//////////////////////////////////////////////////////////////////////

int CBArrLink::Add( int data1, int data2/*=0*/ )
{
	m_DataCount++; 
	int index = m_DataCount;
	int i = (index-1) / m_ItemsPerArr + 1, j = (index-1) % m_ItemsPerArr;
		// �����ݽ��������� ppArr[i][j]
	
	// ������е� �������� �ռ䶼�����꣬�Ϳ����µ� ��������
	if (i>m_ppArrUsedCount)
	{
		m_ppArrUsedCount++; 
				// ���������� ���׵�ַ�������浽 ppArr[ppArrUsedCount]

		// ��� ppArr[ppArrUsedCount] ����Ŀռ��в����ڣ��Ϳ��� ppArr[ppArrUsedCount] �Ŀռ�
		if ( m_ppArrUsedCount>m_ppArrUbound )
		{
			// ָ������ ppArr[] �����¿ռ�
			int sizeNew = m_ppArrUbound+1+mcppArrExpPer;
						// ע�⡰+1����ppArr�±���Ч��Χ [0]��[ppArrUbound]��ppArr ���пռ���� ppArrUbound+1
			MemType ** ppArrTemp = new MemType * [sizeNew];				// ��ָ������
			memset( ppArrTemp, 0, sizeof(MemType *) * sizeNew );		// ������ָ�������еĸ���ַ
			memcpy( ppArrTemp, ppArr, sizeof(MemType *) * (m_ppArrUbound+1));	// ����ԭָ�������е�����
						// ע�⡰+1����ppArr�±���Ч��Χ [0]��[ppArrUbound]��ppArr ���пռ���� ppArrUbound+1

			delete []ppArr;				// ɾ��ԭָ������
			ppArr = ppArrTemp;			// �� ppArr ����Ϊָ����ָ�������ַ
			m_ppArrUbound = sizeNew-1;	// ָ������ռ��ѱ�����
										// ע�⡰-1����ppArr�±���Ч��Χ [0]��[sizeNew-1]

			// ��ʱӦ ppArrUsedCount<=ppArrUbound ���������Ϊ�ݴ�
			if ( m_ppArrUsedCount>m_ppArrUbound ) return 0;
		}
		
		// ���� �� �������飬��ַ => ppArr[ppArrUsedCount]
		ppArr[m_ppArrUsedCount] = new MemType [m_ItemsPerArr];

		// ��ʱӦ i<=ppArrUsedCount���������Ϊ�ݴ�
		if (i>m_ppArrUsedCount) return 0;

	}	// end if (i>ppArrUsedCount)

	// ����������
	ppArr[i][j].DataInt  = data1;
	ppArr[i][j].DataInt2 = data2;

	return m_DataCount;
}


int CBArrLink::Remove( int index, bool bRaiseErrIfErr/*=false*/ )
{
	int i = (index-1) / m_ItemsPerArr + 1, j = (index-1) % m_ItemsPerArr;
	if (index<=m_DataCount && i>0 && i<=m_ppArrUsedCount && j>=0) // ע�� j ���� ==0
	{
		// �����һ�����ݸ��� ppArr[i][j]
		int iEnd = (m_DataCount-1) / m_ItemsPerArr + 1, 
			jEnd = (m_DataCount-1) % m_ItemsPerArr;
		ppArr[i][j] = ppArr[iEnd][jEnd];

		// ɾ�����һ������
		if (jEnd==0)
		{
			// ɾ�����һ�����������顱
			delete []ppArr[iEnd];  ppArr[iEnd]=0;
			m_ppArrUsedCount = iEnd-1;
		}
		m_DataCount--;
	}
	else // if (index<=m_DataCount && i>0 && ...
	{
		if (bRaiseErrIfErr) throw (unsigned char)9;			// ��������������Χ
	}    // end if (index<=m_DataCount && i>0 && ...
	
	return m_DataCount;		// ����Ŀǰ�������ܸ���
}

int CBArrLink::Item( int index, bool bRaiseErrIfErr/*=false*/ )
{
	int i = (index-1) / m_ItemsPerArr + 1, j = (index-1) % m_ItemsPerArr;
 	if (index<=m_DataCount && i>0 && i<=m_ppArrUsedCount && j>=0) // ע�� j ���� ==0
		return ppArr[i][j].DataInt; 
	else
	{
		if (bRaiseErrIfErr) throw (unsigned char)9;			// ��������������Χ
		return -2147483647-1;
	} 
}


int CBArrLink::Item2( int index, bool bRaiseErrIfErr/*=false*/ )
{
	int i = (index-1) / m_ItemsPerArr + 1, j = (index-1) % m_ItemsPerArr;
	if (index<=m_DataCount && i>0 && i<=m_ppArrUsedCount && j>=0) // ע�� j ���� ==0
		return ppArr[i][j].DataInt2; 
	else
	{
		if (bRaiseErrIfErr) throw (unsigned char)9;			// ��������������Χ
		return -2147483647-1;
	} 
}


int CBArrLink::Count()
{
	return m_DataCount;
}


void * CBArrLink::GetItemsArr()
{
	if (m_ptrArrRet) { delete []m_ptrArrRet; m_ptrArrRet=0; }

	// ׼����ʱ�ռ��һ������ ���ڱ����������ݣ��׵�ַ => pArr
	MemType * pArr = new MemType [m_DataCount+1];
	memset( pArr, 0, sizeof(MemType)*(m_DataCount+1) );	// ��������ռ�

	// ������������ => ��ʱ�ռ�
	MemType *p = pArr+1;	// ��ʱ�ռ伴��Ҫ��������λ�ã���ʼλ�ó�ȥ [0] �Ŀռ� 
	int i;

	// �����������������飬��д <=
	for (i=1; i<m_ppArrUsedCount; i++ )	
	{
		memcpy(p, ppArr[i], sizeof(MemType) * m_ItemsPerArr);
		p += m_ItemsPerArr;
	}
	
	// �������һ������������
	memcpy(p, ppArr[i], sizeof(MemType) * (m_DataCount % m_ItemsPerArr) );
	p += (m_DataCount % m_ItemsPerArr);

	// ����ֵ
	m_ptrArrRet = (void *)pArr;
	return m_ptrArrRet;
}

void CBArrLink::Clear()
{
	Dispose();
	Init();
}


//////////////////////////////////////////////////////////////////////
// ˽�к���
//////////////////////////////////////////////////////////////////////

void CBArrLink::Init()
{
	if (ppArr != 0) Dispose();		// ���������ݣ��������������

	// Ϊ ����������ַ��ָ������ ���ٳ�ʼ�ռ�
	ppArr = new MemType * [mcppArrInit];
	memset( ppArr, 0, sizeof(MemType *)*mcppArrInit );	// ����ָ�������еĸ���ַ
	m_ppArrUbound = mcppArrInit-1;	// ע�⡰-1����ppArr�±���Ч��Χ [0]��[mcppArrInit-1]
	m_ppArrUsedCount = 0;
	
	// ���ٵ�1����������Ŀռ䣬��ַ => ppArr[1]
	ppArr[1] = new MemType [m_ItemsPerArr];
	m_ppArrUsedCount = 1;		// ��Чָ������Ԫ��Ϊ��ppArr[1] �� ppArr[1]

	// �������ݣ������ܸ���Ϊ 0
	m_DataCount = 0;
}

void CBArrLink::Dispose()
{
	if (ppArr==0) return;	// �Ѿ� Delete
	
	int i;

	// ɾ����������Ŀռ�
	if (m_ptrArrRet) delete []m_ptrArrRet;
	m_ptrArrRet = 0;

	// ɾ���������������е�Ԫ��
	// ���������� ���׵�ַΪ��ppArr[1] �� ppArr[ppArrUsedCount]
	for (i=1; i<=m_ppArrUsedCount; i++)
	{
		if (ppArr[i]) delete [] ppArr[i];
		ppArr[i] = 0;
	}
	m_ppArrUsedCount = 0;
	m_DataCount = 0;
	
	// ɾ��ָ�����鱾��Ŀռ�
	delete [] ppArr; ppArr=0;
	m_ppArrUbound = 0;	
}


//////////////////////////////////////////////////////////////////////
// CHeapMemory ���ʵ�֣���ȫ�ֶ���ά������ͨ�� new ������ڴ�ָ��
//
//////////////////////////////////////////////////////////////////////



CBHeapMemory::CBHeapMemory(int initSize/*=0*/)
{
	// ���ٳ�ʼ�ռ�
	if (initSize) initSize=1000;
	memHash.AlloMem(initSize);
}

CBHeapMemory::~CBHeapMemory()
{
	Dispose();
}


int CBHeapMemory::AddPtr( void *ptrNew, bool bArrayNew/*=true*/, long iUserData/*=0*/ )
{
	memHash.Add((long)ptrNew, (long)ptrNew, bArrayNew, iUserData, 0, 0, 0, false);
	return memHash.Count();
}


// �� new ���� size ���ֽڵĿռ䣬���Զ���0
void * CBHeapMemory::Alloc( int size )
{
	char * ptr=new char[size];
	memset(ptr, 0, size);
	AddPtr(ptr, true);
	return (void *)ptr;
}

// �ͷ� ptr ��ָ���һ���ڴ�ռ�
//   ptr �������ɱ�����������Ŀռ䣬���򱾺��������ͷ�
void CBHeapMemory::Free( void *ptr )
{
	if ( ptr && memHash.IsKeyExist((long)ptr) )
	{
		if ( memHash.Item((long)ptr,false) == (long)ptr )	// У�飬�� !=���� delete
		{
			if (memHash.ItemLong((long)ptr,false) )
				delete []ptr;
			else
				delete ptr;
		}	
		memHash.Remove((long)ptr, false);
	}
}


bool CBHeapMemory::IsPtrManaged( void *ptr )
{
	return memHash.IsKeyExist((long)ptr);
}

int CBHeapMemory::CountPtrs()
{
	return memHash.Count();
}

void * CBHeapMemory::PtrEach( int index, bool * ptrbArrayNew/*=0*/ )
{
	if ( ptrbArrayNew )
	{
		if ( memHash.ItemLongFromIndex(index,false) )
			*ptrbArrayNew=true; 
		else
			*ptrbArrayNew=false;
	}
	return (void *)memHash.ItemFromIndex(index, false);
}


long CBHeapMemory::UserData( void *ptr )
{
	return memHash.ItemLong2((long)ptr, false);
}

void CBHeapMemory::Dispose()
{
	// ɾ�������м�¼�����пռ�
	int i=0; 
	void * ptr;
	for (i=1; i<=memHash.Count(); i++)
	{
		ptr = (void *)memHash.ItemFromIndex(i,false);
		if ( ptr )
		{
			if ( memHash.ItemLongFromIndex(i,false) )
				delete [] ptr; 
			else
				delete ptr;  
			memHash.ItemFromIndexSet(i, 0, false);
		}
	}
	
	// ��� memHash
	memHash.Clear();
}


// ����һ���ڴ�ռ䣨ʵ���ǵ��� memset (������ include <memory.h>) ��
// Ϊʹ�������򲻱��� include <memory.h>������Ҳ�ṩ��������ܽӿڣ�
void CBHeapMemory::ZeroMem( void * ptr, unsigned int length )
{
	memset(ptr, 0, length);
}


// �ڴ濽����ʵ���ǵ��� memcpy (������ include <memory.h>) ��
// Ϊʹ�������򲻱��� include <memory.h>������Ҳ�ṩ��������ܽӿڣ�
void CBHeapMemory::CopyMem( void * dest, void * source, unsigned int length )
{
	memcpy(dest, source, length);	
}








//////////////////////////////////////////////////////////////////////
// CBApp ���ʵ�֣�����Ӧ�ó���ȫ����Ϣ
//
//////////////////////////////////////////////////////////////////////

CBApp::CBApp( HINSTANCE hInst, 
			 HINSTANCE hPrevInst, 
			 char * lpCmdLine, 
			 int nShowCmd ): 
hInstance(hInst), 
CmdShow(nShowCmd)
{
	m_CursorGlobalIdx = 0;
	m_hCursorGlobal = NULL;
}


CBApp::~CBApp()
{
	ClearImageObjs();	// �ͷ����м�¼��ͼ�����
}


LPTSTR CBApp::Command() const
{
	return GetCommandLine();
}

// ���Ӧ�ó���ǰ���е�·��
LPTSTR CBApp::Path()
{
	if ( GetModuleFileName(0, m_path, sizeof(m_path)) )
	{
		// �ҵ����� \\����һλ�ýض�
		TCHAR *p = m_path;
		while (*p) p++; 
		while (*p != '\\') p--;
		p++; *p='\0';
	}
	else
	{
		// ���Ӧ�ó�����ʧ�ܣ����� ""
		m_path[0] = 0;
	}
	return m_path;
}

int CBApp::ScreenWidth() const
{
	return GetSystemMetrics(SM_CXSCREEN);
}

int CBApp::ScreenHeight() const
{
	return GetSystemMetrics(SM_CYSCREEN);
}



long CBApp::MousePointerGlobal()
{
	return m_CursorGlobalIdx;
}

HCURSOR CBApp::MousePointerGlobalHCursor()
{
	return m_hCursorGlobal;
}

void CBApp::MousePointerGlobalSet( EStandardCursor cursor )
{
	MousePointerGlobalSet((long)cursor, 0);
}

void CBApp::MousePointerGlobalSet( long idResCursor, LPCTSTR typeRes/*=0*/ )
{
	m_CursorGlobalIdx = idResCursor;
	
	if (m_CursorGlobalIdx)
	{
		// ���ع�꣬������� ms_hCursorGlobal
		// =============================================================
		// LoadCursor ������ʹ�ظ������ã�Ҳ�����ظ�������Դ��ϵͳ���ж�
		//   �����Ӧ����Ѿ����أ�LoadCursor ֱ�ӷ��ؾ��
		// =============================================================
		if ( m_CursorGlobalIdx > gc_IDStandCursorIDBase)
		{
			// ��׼���
			// ms_CursorGlobalIdx-gc_IDStandCursorIDBase ���Ǳ�׼����ID��
			m_hCursorGlobal = 
				LoadCursor(NULL, 
				MAKEINTRESOURCE(m_CursorGlobalIdx-gc_IDStandCursorIDBase));
		}
		else
		{
			// ��Դ���
			// ms_CursorGlobalIdx ������Դ ID
			if (typeRes==0)
			{
				// ���� Cursor ���͵���Դ
				m_hCursorGlobal =
					LoadCursor(pApp->hInstance, MAKEINTRESOURCE(m_CursorGlobalIdx));
			}
			else
			{
				// �����Զ������͵���Դ��typeRes ���͵���Դ��
				unsigned long size=0; 
				unsigned char * p= LoadResData(m_CursorGlobalIdx, typeRes, &size);
				m_hCursorGlobal = (HCURSOR)CreateIconFromResource(p, size, 0, 0x00030000);
			}

			// ��¼�ù�������Ա�����˳�ǰ�Զ�ɾ��
			AddImageObjHandle((HANDLE)m_hCursorGlobal, eImgCursor);
		}
	}	
	else	// if (ms_CursorGlobalIdx)
	{
		// ���������ù�꣬ʹ��Ĭ�ϣ����� ms_hCursorGlobal Ϊ 0
		m_hCursorGlobal = 0;
	}		// end if (ms_CursorGlobalIdx)
	
	// ���򱾳���ǰǰ̨���ڷ��� WM_SETCURSOR��ǰ̨���ڴ��� WM_SETCURSOR ��ʹ���������Ч
	SendMessage(GetActiveWindow(), WM_SETCURSOR, (WPARAM)GetActiveWindow(), 0);
	// �ڱ���������д��ڣ������Ӵ��ڣ��ġ����Ͻ��յ��� WM_SETCURSOR ��Ϣ�л�ı������	
}


bool CBApp::AddImageObjHandle( HANDLE hObject, EImgObjType typeImage )
{
	return m_hashImageObjs.Add((long)hObject, (long)hObject, 
		(long)typeImage, 0, 0, 0, 0, false);
}

void CBApp::ClearImageObjs()
{
	int i;
	for (i=1; i<=m_hashImageObjs.Count(); i++)
	{
		switch(m_hashImageObjs.ItemLongFromIndex(i,false))
		{
		case IMAGE_ICON:
			DestroyIcon((HICON)m_hashImageObjs.ItemFromIndex(i, false));
			break;
		case IMAGE_CURSOR:
			DestroyCursor((HCURSOR)m_hashImageObjs.ItemFromIndex(i, false));
			break;
		default:	// ���� IMAGE_BITMAP
			DeleteObject((HGDIOBJ)m_hashImageObjs.ItemFromIndex(i, false));
			break;
		}
	}
	
	// ��� gHashImageObjs �е�����
	m_hashImageObjs.Clear();
}




