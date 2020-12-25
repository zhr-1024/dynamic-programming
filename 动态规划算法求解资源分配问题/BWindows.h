//////////////////////////////////////////////////////////////////////////
// Bwindows.h �����˱�д Windows �����������ͷ�ļ���
//            һЩ�����Զ��庯�������������͡���������Ķ���
//   �������
// 		CBHashLK��   �������� key �Ĺ�ϣ����
//		CBArrLink��  ��Ч����������
// 		CHeapMemory����ȫ�ֶ���ά������ͨ�� new ������ڴ�ָ����
//      CBApp �ࣺ   ����Ӧ�ó���ȫ����Ϣ
//
// ������ h �ļ�����ʹ��ȫ�ֶ���ָ�룺pApp��->����ó���ȫ����Ϣ����ֻ��
//   ͬʱ���� BForm ��ģ�飨��װ WinMain ����������ܻ����ȷ����Ϣ
//
// ������ h �ļ�����ʹ��ȫ�ֶ���HM ������ new ���ٵ��ڴ�ָ��
//    ���� HM.AddPtr(p, bArrNew); ��ӹ���һ���� new ���ٵ��ڴ�ָ��
//    ���� HM.Free(p); �ͷ� HM �����һ����̬�ڴ�
//    ���� HM.Dispose(); �ͷ�Ŀǰ��������ж�̬�ڴ棨�������ʱҲ���Զ��ͷţ�
//////////////////////////////////////////////////////////////////////////

#pragma once
#pragma warning(disable:4996) // �ر� warning C4996: �� 'wcscpy': This function or variable may be unsafe. Consider using wcscpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

#define OEMRESOURCE		// to use any of the OBM_ constants
#include <windows.h>
#include <memory.h>	
#include <tchar.h>
#include <string.h>
#include <string>
typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tstring;
using std::string;
using std::wstring;

// EventsGenerator �������ش�ֵ��ʾҪ����Ĭ�ϵĴ��ڳ��򣬷����ٵ���Ĭ�ϵĴ��ڳ���
#define gc_APICEventsGenDefautRet 0xFEEEEEEE  

enum EStandardIcon		// ϵͳͼ��
{
	IDI_Application = (int)IDI_APPLICATION, 
	IDI_Asterisk = (int)IDI_ASTERISK, 
	IDI_Error = (int)IDI_ERROR, 
	IDI_Exclamation = (int)IDI_EXCLAMATION, 
	IDI_Hand = (int)IDI_HAND, 
	IDI_Information = (int)IDI_INFORMATION, 
	IDI_Question = (int)IDI_QUESTION, 
	IDI_Warning = (int)IDI_WARNING, 
	IDI_Winlogo = (int)IDI_WINLOGO
};

#define gc_IDStandCursorIDBase 0x10000  
enum EStandardCursor	// ϵͳ���ָ����״��Ϊ��Ӧ API ���� + gc_IDStandCursorIDBase��Ŀ����Ϊ����Դ ID ���֣���Դ ID ��С�� gc_IDStandCursorIDBase��
{
	IDC_AppStarting	=	(int)IDC_APPSTARTING + gc_IDStandCursorIDBase, 		// Standard arrow and small hourglass 
	IDC_Arrow	=	(int)IDC_ARROW + gc_IDStandCursorIDBase, 				// Standard arrow 
	IDC_Cross	=	(int)IDC_CROSS + gc_IDStandCursorIDBase, 				// Cross hair 
	IDC_Hand	=	(int)MAKEINTRESOURCE(32649) + gc_IDStandCursorIDBase,	// Windows NT 5.0 and later: Hand 
	IDC_Help	=	(int)IDC_HELP + gc_IDStandCursorIDBase, 				// Arrow and question mark 
	IDC_IBeam	=	(int)IDC_IBEAM + gc_IDStandCursorIDBase, 				// I-beam 
	IDC_Icon	=	(int)IDC_ICON + gc_IDStandCursorIDBase, 				// Obsolete for applications marked version 4.0 or later. 
	IDC_No	=	(int)IDC_NO + gc_IDStandCursorIDBase, 						// Slashed circle 
	IDC_Size	=	(int)IDC_SIZE + gc_IDStandCursorIDBase, 				// Obsolete for applications marked version 4.0 or later. Use IDC_SIZEALL. 
	IDC_SizeAll	=	(int)IDC_SIZEALL + gc_IDStandCursorIDBase, 				// Four-pointed arrow pointing north, south, east, and west 
	IDC_SizeNESW	=	(int)IDC_SIZENESW + gc_IDStandCursorIDBase, 		// Double-pointed arrow pointing northeast and southwest 
	IDC_SizeNS	=	(int)IDC_SIZENS + gc_IDStandCursorIDBase, 				// Double-pointed arrow pointing north and south 
	IDC_SizeNWSE	=	(int)IDC_SIZENWSE + gc_IDStandCursorIDBase, 		// Double-pointed arrow pointing northwest and southeast 
	IDC_SizeWE	=	(int)IDC_SIZEWE + gc_IDStandCursorIDBase, 				// Double-pointed arrow pointing west and east 
	IDC_UpArrow	=	(int)IDC_UPARROW + gc_IDStandCursorIDBase, 				// Vertical arrow 
	IDC_Wait	=	(int)IDC_WAIT + gc_IDStandCursorIDBase 					// Hourglass 
};

enum EOEMBmp		// ϵͳ OEM λͼ
{
	Obm_Btncorners = OBM_BTNCORNERS, 
	Obm_Btsize = OBM_BTSIZE, 
	Obm_Check = OBM_CHECK, 
	Obm_Checkboxes = OBM_CHECKBOXES, 
	Obm_Close = OBM_CLOSE, 
	Obm_Reduce = OBM_REDUCE, 
	Obm_Combo = OBM_COMBO, 
	Obm_Reduced = OBM_REDUCED, 
	Obm_Dnarrow = OBM_DNARROW, 
	Obm_Restore = OBM_RESTORE, 
	Obm_Dnarrowd = OBM_DNARROWD, 
	Obm_Restored = OBM_RESTORED, 
	Obm_Dnarrowi = OBM_DNARROWI, 
	Obm_Rgarrow = OBM_RGARROW, 
	Obm_Lfarrow = OBM_LFARROW, 
	Obm_Rgarrowd = OBM_RGARROWD, 
	Obm_Lfarrowd = OBM_LFARROWD, 
	Obm_Rgarrowi = OBM_RGARROWI, 
	Obm_Lfarrowi = OBM_LFARROWI, 
	Obm_Size = OBM_SIZE, 
	Obm_Mnarrow = OBM_MNARROW, 
	Obm_Uparrow = OBM_UPARROW, 
	Obm_Uparrowd = OBM_UPARROWD, 
// 	Obm_Old_Restore = OBM_OLD_RESTORE,		// Bitmap names that begin with OBM_OLD represent bitmaps used by 16-bit versions of Windows earlier than 3.0. 
// 	Obm_Old_Rgarrow = OBM_OLD_RGARROW, 
// 	Obm_Old_Uparrow = OBM_OLD_UPARROW, 
// 	Obm_Old_Zoom = OBM_OLD_ZOOM, 
// 	Obm_Old_Close = OBM_OLD_CLOSE, 
// 	Obm_Old_Dnarrow = OBM_OLD_DNARROW, 
// 	Obm_Old_Lfarrow = OBM_OLD_LFARROW, 
// 	Obm_Old_Reduce = OBM_OLD_REDUCE, 
	Obm_Uparrowi = OBM_UPARROWI, 
	Obm_Zoom = OBM_ZOOM, 
	Obm_Zoomd = OBM_ZOOMD
};

enum EOEMIcon		// ϵͳ OEM ͼ��
{
	Oic_Sample  =	OIC_SAMPLE,	
	Oic_Hand  =	OIC_HAND,	
	Oic_Ques  =	OIC_QUES,	
	Oic_Bang  =	OIC_BANG,	
	Oic_Note  =	OIC_NOTE,

#if(WINVER >= 0x0400)	
	Oic_Winlogo  =	OIC_WINLOGO,
	Oic_Warning  =	OIC_WARNING,	
	Oic_Error  =	OIC_ERROR,	
	Oic_Information  =	OIC_INFORMATION,
#endif 	/* WINVER >= 0x0400 */
};

enum EOEMCursor		// ϵͳ OEM ���
{
	Ocr_Normal  =	OCR_NORMAL,	
	Ocr_Ibeam  =	OCR_IBEAM,
	Ocr_Wait  =	OCR_WAIT,	
	Ocr_Cross  =	OCR_CROSS,	
	Ocr_Up  =	OCR_UP,	
	Ocr_Size  =	OCR_SIZE,	/* OBSOLETE: use OCR_SIZEALL */
	Ocr_Icon  =	OCR_ICON,	/* OBSOLETE: use OCR_NORMAL */
	Ocr_Sizenwse  =	OCR_SIZENWSE,	
	Ocr_Sizenesw  =	OCR_SIZENESW,	
	Ocr_Sizewe  =	OCR_SIZEWE,	
	Ocr_Sizens  =	OCR_SIZENS,	
	Ocr_Sizeall  =	OCR_SIZEALL,	
	Ocr_Icocur  =	OCR_ICOCUR,	/* OBSOLETE: use OIC_WINLOGO */
	Ocr_No  =	OCR_NO,	

#if(WINVER >= 0x0500)	
	Ocr_Hand  =	OCR_HAND,	
#endif 	/* WINVER >= 0x0500 */

#if(WINVER >= 0x0400)	
	Ocr_Appstarting  =	OCR_APPSTARTING,	
#endif 	/* WINVER >= 0x0400 */
};

enum EColorType			// ϵͳ��ɫ
{
	COLOR_ActiveBorder	=	COLOR_ACTIVEBORDER,
	COLOR_ActiveCaption	=	COLOR_ACTIVECAPTION,
	COLOR_AppWorkspace	=	COLOR_APPWORKSPACE,
	COLOR_BackGround	=	COLOR_BACKGROUND,
	COLOR_BtnFace	=	COLOR_BTNFACE,
	COLOR_BtnShadow	=	COLOR_BTNSHADOW,
	COLOR_BtnText	=	COLOR_BTNTEXT,
	COLOR_CaptionText	=	COLOR_CAPTIONTEXT,
	COLOR_GrayText	=	COLOR_GRAYTEXT,
	COLOR_Highlight	=	COLOR_HIGHLIGHT,
	COLOR_HighlightText	=	COLOR_HIGHLIGHTTEXT,
	COLOR_InactiveBorder	=	COLOR_INACTIVEBORDER,
	COLOR_InactiveCaption	=	COLOR_INACTIVECAPTION,
	COLOR_Menu	=	COLOR_MENU,
	COLOR_MenuText	=	COLOR_MENUTEXT,
	COLOR_ScrollBar	=	COLOR_SCROLLBAR,
	COLOR_Window	=	COLOR_WINDOW,
	COLOR_WindowFrame	=	COLOR_WINDOWFRAME,
	COLOR_WindowText 	=	COLOR_WINDOWTEXT 
};

enum EShowWindowCmd		// ������ʾ״̬
{
	SW_ForceMinimize = SW_FORCEMINIMIZE,	//  Windows NT 5.0 and later: Minimizes a window, even if the thread that owns the window is hung. This flag should only be used when minimizing windows from a different thread. 
	SW_Hide = SW_HIDE,	//  Hides the window and activates another window. 
	SW_Mazimize = SW_MAXIMIZE,	//  Maximizes the specified window. 
	SW_Minimize = SW_MINIMIZE,	//  Minimizes the specified window and activates the next top-level window in the Z order. 
	SW_Restore = SW_RESTORE,	//  Activates and displays the window. If the window is minimized or maximized, the system restores it to its original size and position. An application should specify this flag when restoring a minimized window. 
	SW_Show = SW_SHOW,	//  Activates the window and displays it in its current size and position.  
	SW_ShowDefault = SW_SHOWDEFAULT,	//  Sets the show state based on the SW_ flag specified in theSTARTUPINFO structure passed to theCreateProcess function by the program that started the application.  
	SW_ShowMaximized = SW_SHOWMAXIMIZED,	//  Activates the window and displays it as a maximized window. 
	SW_ShowMinimized = SW_SHOWMINIMIZED,	//  Activates the window and displays it as a minimized window. 
	SW_ShowMinNoactive = SW_SHOWMINNOACTIVE,	//  Displays the window as a minimized window. The active window remains active. 
	SW_ShowNA = SW_SHOWNA,	//  Displays the window in its current state. The active window remains active. 
	SW_ShowNoActivate = SW_SHOWNOACTIVATE,	//  Displays a window in its most recent size and position. The active window remains active. 
	SW_ShowNormal = SW_SHOWNORMAL	//  Activates and displays a window. If the window is minimized or maximized, the system restores it to its original size and position. An application should specify this flag when displaying the window for the first time. 
};


enum EMsgBoxBtn			// ������Ϣ��İ�ť��ʽ
{
	mb_OK = MB_OK,
	mb_OkCancel = MB_OKCANCEL,
	mb_AbortRetryIgnore = MB_ABORTRETRYIGNORE,
	mb_YesNoCancel = MB_YESNOCANCEL,
	mb_YesNo = MB_YESNO,
	mb_RetryCancel = MB_RETRYCANCEL
};

enum EMsgBoxIcon		// ������Ϣ���ͼ����ʽ
{
	mb_IconNone = 0,
	mb_IconError = MB_ICONHAND,
	mb_IconQuestion = MB_ICONQUESTION, 
	mb_IconExclamation = MB_ICONEXCLAMATION, 
	mb_IconInformation = MB_ICONASTERISK 
	#if(WINVER >= 0x0400)
	,mb_UserIcon = MB_USERICON
	#endif /* WINVER >= 0x0400 */
};

enum EDlgBoxDefBtn		// ������Ϣ���Ĭ�ϰ�ť��ʽ
{
		mb_DefButton1 = MB_DEFBUTTON1,
		mb_DefButton2 = MB_DEFBUTTON2,
		mb_DefButton3 = MB_DEFBUTTON3
#if(WINVER >= 0x0400)
		,mb_DefButton4 = MB_DEFBUTTON4
#endif /* WINVER >= 0x0400 */
};

enum EDlgBoxCmdID		//������Ϣ����û����µİ�ť����
{
	NoValue = 0,
	idAbort = IDABORT, 		// Abort button was selected. 
	idCancel = IDCANCEL, 	// Cancel button was selected. 
	idIgnore = IDIGNORE, 	// Ignore button was selected. 
	idNo = IDNO, 			// No button was selected. 
	idOk = IDOK, 			// OK button was selected. 
	idRetry = IDRETRY, 		// Retry button was selected. 
	idYes = IDYES 			// Yes button was selected. 
};


enum EMsgBeep		// ϵͳ��������ʽ
{
	mb_SoundOK = MB_OK,	// SystemDefault
	mb_SoundError = MB_ICONHAND,
	mb_SoundQuestion = MB_ICONQUESTION, 
	mb_SoundExclamation = MB_ICONEXCLAMATION, 
	mb_SoundAsterisk = MB_ICONASTERISK, 
	mb_SoundSpeaker = 0xFFFFFFFF		// Standard beep using the computer speaker
};

enum ESysMenu		// ϵͳ�˵���
{
	eSysMenu_Close = SC_CLOSE,
	eSysMenu_Minimize = SC_MINIMIZE,
	eSysMenu_Maxmize = SC_MAXIMIZE,
	eSysMenu_Move = SC_MOVE,
	eSysMenu_Size = SC_SIZE,
	eSysMenu_Restore = SC_RESTORE
};




//////////////////////////////////////////////////////////////////////////
// �����Զ��庯��
//
//////////////////////////////////////////////////////////////////////////

// ������Ϣ��
//   �� title Ϊ NULL�����Զ�ʹ��Ӧ�ó�������Ϊ title
EDlgBoxCmdID MsgBox(LPCTSTR			szPrompt, 
				 	LPCTSTR			szTitle = NULL,				
					EMsgBoxBtn		buttons = mb_OK, 
					EMsgBoxIcon		icon = mb_IconNone, 
					EDlgBoxDefBtn	defBtn = mb_DefButton1, 
				    bool			bSystemModal = false, 
				    bool			bHelpButton = false, 
				    bool			bRightJustified = false, 
				    bool			bRightToLeftReading = false);
EDlgBoxCmdID MsgBox(char			valueChar, 
				 	LPCTSTR			szTitle = NULL,				
					EMsgBoxBtn		buttons = mb_OK, 
					EMsgBoxIcon		icon = mb_IconNone, 
					EDlgBoxDefBtn	defBtn = mb_DefButton1, 
				    bool			bSystemModal = false, 
				    bool			bHelpButton = false, 
				    bool			bRightJustified = false, 
				    bool			bRightToLeftReading = false);
EDlgBoxCmdID MsgBox(unsigned short int valueInt,				// TCHAR
				 	LPCTSTR			szTitle = NULL,				
					EMsgBoxBtn		buttons = mb_OK, 
					EMsgBoxIcon		icon = mb_IconNone, 
					EDlgBoxDefBtn	defBtn = mb_DefButton1, 
				    bool			bSystemModal = false, 
				    bool			bHelpButton = false, 
				    bool			bRightJustified = false, 
				    bool			bRightToLeftReading = false);
EDlgBoxCmdID MsgBox(int				valueInt, 
				 	LPCTSTR			szTitle = NULL,				
					EMsgBoxBtn		buttons = mb_OK, 
					EMsgBoxIcon		icon = mb_IconNone, 
					EDlgBoxDefBtn	defBtn = mb_DefButton1, 
				    bool			bSystemModal = false, 
				    bool			bHelpButton = false, 
				    bool			bRightJustified = false, 
				    bool			bRightToLeftReading = false);
EDlgBoxCmdID MsgBox(long			valueLong, 
				 	LPCTSTR			szTitle = NULL,				
					EMsgBoxBtn		buttons = mb_OK, 
					EMsgBoxIcon		icon = mb_IconNone, 
					EDlgBoxDefBtn	defBtn = mb_DefButton1, 
				    bool			bSystemModal = false, 
				    bool			bHelpButton = false, 
				    bool			bRightJustified = false, 
				    bool			bRightToLeftReading = false);
EDlgBoxCmdID MsgBox(unsigned int	valueInt, 
				 	LPCTSTR			szTitle = NULL,				
					EMsgBoxBtn		buttons = mb_OK, 
					EMsgBoxIcon		icon = mb_IconNone, 
					EDlgBoxDefBtn	defBtn = mb_DefButton1, 
				    bool			bSystemModal = false, 
				    bool			bHelpButton = false, 
				    bool			bRightJustified = false, 
				    bool			bRightToLeftReading = false);
EDlgBoxCmdID MsgBox(unsigned long	valueInt, 
				 	LPCTSTR			szTitle = NULL,				
					EMsgBoxBtn		buttons = mb_OK, 
					EMsgBoxIcon		icon = mb_IconNone, 
					EDlgBoxDefBtn	defBtn = mb_DefButton1, 
				    bool			bSystemModal = false, 
				    bool			bHelpButton = false, 
				    bool			bRightJustified = false, 
				    bool			bRightToLeftReading = false);
EDlgBoxCmdID MsgBox(float			valueSng, 
				 	LPCTSTR			szTitle = NULL,				
					EMsgBoxBtn		buttons = mb_OK, 
					EMsgBoxIcon		icon = mb_IconNone, 
					EDlgBoxDefBtn	defBtn = mb_DefButton1, 
				    bool			bSystemModal = false, 
				    bool			bHelpButton = false, 
				    bool			bRightJustified = false, 
				    bool			bRightToLeftReading = false);
EDlgBoxCmdID MsgBox(double			valueDbl, 
				 	LPCTSTR			szTitle = NULL,				
					EMsgBoxBtn		buttons = mb_OK, 
					EMsgBoxIcon		icon = mb_IconNone, 
					EDlgBoxDefBtn	defBtn = mb_DefButton1, 
				    bool			bSystemModal = false, 
				    bool			bHelpButton = false, 
				    bool			bRightJustified = false, 
				    bool			bRightToLeftReading = false);
EDlgBoxCmdID MsgBox(long double		valueDbl, 
				 	LPCTSTR			szTitle = NULL,				
					EMsgBoxBtn		buttons = mb_OK, 
					EMsgBoxIcon		icon = mb_IconNone, 
					EDlgBoxDefBtn	defBtn = mb_DefButton1, 
				    bool			bSystemModal = false, 
				    bool			bHelpButton = false, 
				    bool			bRightJustified = false, 
				    bool			bRightToLeftReading = false);
EDlgBoxCmdID MsgBox(tstring			valueString, 
				 	tstring			valueTitle = TEXT(""),				
					EMsgBoxBtn		buttons = mb_OK, 
					EMsgBoxIcon		icon = mb_IconNone, 
					EDlgBoxDefBtn	defBtn = mb_DefButton1, 
				    bool			bSystemModal = false, 
				    bool			bHelpButton = false, 
				    bool			bRightJustified = false, 
				    bool			bRightToLeftReading = false);

BOOL MsgBeep(EMsgBeep soundStyle = mb_SoundSpeaker);

// ��һ������ת��Ϊ�˽��Ƶ��ַ������ַ����ռ��Զ����١��� HM �Զ�����
LPTSTR Oct(long number);

// ��һ������ת��Ϊʮ�����Ƶ��ַ������ַ����ռ��Զ����١��� HM �Զ�����
LPTSTR Hex(long number);


// ��õ�ǰ·���ַ������ַ����ռ��Զ����١��� HM �Զ�����
LPTSTR CurDir();

// ��ȡһ���Զ�����Դ���ֽ����ݣ��ռ��Զ����١��� HM �Զ�����
//   rSize ��Ϊ0ʱ�����Ӵ˲���ָ��Ŀռ䷵����Դ���ֽ���
unsigned char * LoadResData(UINT idRes, UINT typeRes, unsigned long * rSize=0);
unsigned char * LoadResData(UINT idRes, LPCTSTR typeRes, unsigned long * rSize=0 );
unsigned char * LoadResData(LPCTSTR idRes, UINT typeRes, unsigned long * rSize=0 );
unsigned char * LoadResData(LPCTSTR idRes, LPCTSTR typeRes, unsigned long * rSize=0);

//////////////////////////////////////////////////////////////////////////
// ʱ�� ����
//////////////////////////////////////////////////////////////////////////

// ���ص�ǰϵͳ���ڡ�ʱ���һ���ַ������ַ����ռ��Զ����١��� HM �Զ�����
//   �� lpDblTime ��Ϊ0��������ǰϵͳ���ڡ�ʱ��ת��Ϊ double 
//     ��Ϊ1601-1-1���������ĺ�������������ָ��� double �ͱ�����
//   �� lpTime ��Ϊ0��������ǰϵͳ���ڡ�ʱ��洢����ָ��Ľṹ��
LPTSTR Now( double *lpDblTime=0, SYSTEMTIME *lpTime=0);

// ���õ�ǰϵͳ���ڡ�ʱ��
BOOL NowSet( SYSTEMTIME stNow );

// ��һ�����ڡ�ʱ��ת��Ϊ double ���أ�Ϊ1601-1-1���������ĺ�������
double DateTimeDbl( SYSTEMTIME stDatetime );

// �����������ڡ�ʱ���ʱ����ʱ���õļ������
enum eDataTimeDiffStyle
{
	edtYearDiff = 1,
	edtMonthDiff,
	edtDayDiff,
	edtHourDiff,
	edtMinuteDiff,
	edtSecondDiff,
	edtMilliseconds
};

// �����������ڡ�ʱ���ʱ����
// style Ϊָ��ʱ�����ĵ�λ
double DateDiff(eDataTimeDiffStyle style,
				SYSTEMTIME stDatetime1,
				SYSTEMTIME stDatetime2);


// ���ش� 1970-1-1 00:00 ����������
// ������ blClockTicks==True���򷵻ر����̾����� clock ticks ��
long TimeClock( bool blClockTicks=false );


//////////////////////////////////////////////////////////////////////////
// �Զ����ַ��� ����
//////////////////////////////////////////////////////////////////////////

// �� printf ��ʽ����һ���ַ������ַ����ռ��Զ����١��� HM �Զ�����
LPTSTR cdecl StrPrintf( LPCTSTR szFormat, ... );


// ȡ�ַ�����ǰ length ���ַ�������ַ����������������ַ������׵�ַ
//  ��ʹ��Unicodeʱ1��������1�����ȣ�ʹ��ANSIʱ1��������2�����ȣ�
// ���ַ����ռ��Զ����١��� HM �Զ�����
// length�����ַ�������ʱ���������ַ�����length<=0 ʱ���� ָ�� "\0" ���մ�����ָ��
LPTSTR Left(LPCTSTR szStringSrc, int length);		


// ȡ�ַ����ĺ� length ���ַ�������ַ����������������ַ������׵�ַ
//  ��ʹ��Unicodeʱ1��������1�����ȣ�ʹ��ANSIʱ1��������2�����ȣ�
// ���ַ����ռ��Զ����١��� HM �Զ�����
// length�����ַ�������ʱ���������ַ�����length<=0 ʱ���� ָ�� "\0" ���մ�����ָ��
LPTSTR Right(LPCTSTR szStringSrc, int length);				


// ȡ�ַ����Ĵӵ� startPos ���ַ��𣬳� length ���ַ���ɵ��ַ�����
//   �����������ַ������׵�ַ
//  ����һ���ַ�λ��Ϊ1��ʹ��Unicodeʱ1��������1�����ȣ�
//   ʹ��ANSIʱ1��������2�����ȣ�
// ���ַ����ռ��Զ����١��� HM �Զ�����
// startPos+length-1 �����ַ�������ʱ���������ַ�����length<=0 ʱ
//	 �� startPos<=0 �� startPos>Դ�ַ������� ʱ����ָ�� "\0" ���մ�����ָ��
LPTSTR Mid(LPCTSTR szStringSrc, int startPos, int length);	


// ɾ���ַ�����ǰ����β�������пո񣬷���ɾ��������ַ�����
//   ���ַ����ռ��Զ����١��� HM �Զ�����
// bDelOtherSpace=true ʱɾ�����пո����ڵ� isspace() �������
//   �����ַ���bDelOtherSpace=false ʱֻɾ���ո�
LPTSTR LTrim(LPCTSTR szStringSrc, bool bDelOtherSpace=false);
LPTSTR RTrim(LPCTSTR szStringSrc, bool bDelOtherSpace=false);
LPTSTR Trim(LPCTSTR szStringSrc, bool bDelOtherSpace=false);

// ���ַ����е���ĸȫ��ת��Ϊ��д��UCase����Сд��LCase��
//   ����ת��������ַ��������ַ����ռ��Զ����١��� HM �Զ�����
LPTSTR LCase(LPCTSTR szStringSrc);
LPTSTR UCase(LPCTSTR szStringSrc);


enum eBStrCompareMethod		// �ַ����ȽϷ�ʽ
{
	bcmBinaryCompare = 0,	// �����ƱȽϣ����ִ�Сд��
	bcmTextCompare = 1		// �ı��Ƚϣ������ִ�Сд��
};


// �� szSrc �У��ӵ� start ���ַ���ʼ����һ���ַ�λ��Ϊ1����
//	  �����ַ��� szFind �ĵ�һ�γ��ֵ�λ�ã���һ���ַ�λ��Ϊ1����
//    �ҵ�����ֵ>0��û�ҵ�����0
//  ˵����������δ�����κο⺯����strlenҲδ���ã������������Ч��
int InStr(int			start,										
		  LPCTSTR		szSrc, 
		  LPCTSTR		szFind,
	eBStrCompareMethod	compare=bcmBinaryCompare);


// �� szSrc �У��ӵ� 1 ���ַ���ʼ�������ַ��� szFind ��
//   ��һ�γ��ֵ�λ�ã���һ���ַ�λ��Ϊ1����
//   ����λ�úţ���һ���ַ�λ��Ϊ1�����ҵ�����ֵ>0��û�ҵ�����0
int InStr(LPCTSTR		szSrc,								
		  LPCTSTR		szFind,
    eBStrCompareMethod	compare=bcmBinaryCompare);


// �� szSrc �У��ӵ� start ���ַ���ʼ����һ���ַ�λ��Ϊ1����ĩβ�Ĳ��֣�
//	  �����ַ��� szFind �ĵ�����һ�γ��ֵ�λ�ã���һ���ַ�λ��Ϊ1����
//    �ҵ�����ֵ>0��û�ҵ�����0
//  ˵����������δ�����κο⺯����strlenҲδ���ã������������Ч��
int InStrRev(LPCTSTR		szSrc, 
			 LPCTSTR		szFind, 
			 int			start=1,
			 eBStrCompareMethod	compare=bcmTextCompare);


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
		  TCHAR		** &ptrStrings,				
		  LPCTSTR		delimiters=NULL,			
		  int		    limit=-1,				
	eBStrCompareMethod  compare=bcmBinaryCompare, 
		  int iPtrArrExpandPer = 200);						



// �� delimiter ���Ӷ���ַ������������Ӻõ��ַ���
// ����ַ����ĵ�ַ������ stringSrcArray[] ������������������
//   �����д��±� arrayIndexStart �� arrayIndexEnd ���ַ���
// delimiter Ϊ 0 ʱ��Ĭ���� "\0" �����ַ������������ַ��� delimiter ����
// bTailDoubleNull ��Ϊ true�����ڽ���ַ���������ټ�һ��'\0'�������������'\0'��
// ����ַ������ڴ��Զ����䡢�� HM �Զ�����
LPTSTR Join(TCHAR * stringSrcArray[], 
		    const int    arrayIndexEnd, 
		    LPCTSTR delimiter=0, 
		    const int    arrayIndexStart=1, 
		    const bool   bTailDoubleNull=false);


// �滻�ַ����������滻����ַ���
// �滻����ַ����ռ��Զ����䡢�� HM �Զ�����
LPTSTR Replace(LPCTSTR szStringSrc,		// Ҫ���滻���ַ���
			   LPCTSTR szFind,			// Ҫ���滻�������ַ���
			   LPCTSTR szReplaceWith,	// Ҫ�滻Ϊ������
			   int start=1,			// �� szStringSrc �����ַ��������Ŀ�ʼλ��
			   int countLimit=-1,	// ���ַ��������滻�Ĵ������C1 �����������п��ܵ��滻
			   eBStrCompareMethod  compare=bcmBinaryCompare	// �б����ַ���ʱ���õıȽϷ�ʽ
			   );


// �����ַ������������Ӻ�ĳ��ַ���
// �������Ӻõ��ַ������׵�ַ���Զ��������ַ����Ŀռ䡢�� HM �Զ�����
// ÿ�ε��ÿ��������9���ַ���
LPTSTR StrAppend(LPCTSTR str1=0, 
				 LPCTSTR str2=0, 
				 LPCTSTR str3=0, 
				 LPCTSTR str4=0, 
				 LPCTSTR str5=0, 
				 LPCTSTR str6=0, 
				 LPCTSTR str7=0,
				 LPCTSTR str8=0,
				 LPCTSTR str9=0 );


// �� ANSI �� UTF8 �ַ���ת��Ϊ Unicode�����ؽ���ַ����׵�ַ
//   ���� bToUTF8orANSI Ϊ false ʱת�� ANSI��Ϊ true ʱת�� UTF8
//   ����ַ������ڴ��Զ����䡢�� HM �Զ�����
LPWSTR StrConvUnicode(const char * szAnsi, bool bFromUTF8orANSI=false );   // LPWSTR ���� unsigned short int *


// �� Unicode �ַ���ת��Ϊ ANSI �� UTF8�����ؽ���ַ����׵�ַ
//   ���� bToUTF8orANSI Ϊ false ʱת��Ϊ ANSI��Ϊ true ʱת��Ϊ UTF8
//   ����ַ������ڴ��Զ����䡢�� HM �Զ�����
char * StrConvFromUnicode(LPCWSTR szUnicode, bool bToUTF8orANSI=false );


// ���ַ���ת��Ϊ double ����ֵ
double Val( LPCWSTR stringVal );	// ת�� Unicode �ַ���
double Val( LPCSTR stringVal );		// ת�� ANSI �ַ���


// ��������������ת��Ϊ�ַ���
// �����ַ����׵�ַ���ַ����ռ��Զ����١��� HM �Զ�����
LPTSTR Str(char number);
LPTSTR Str(unsigned short int number);	// TCHAR
LPTSTR Str(int number);
LPTSTR Str(long number);
LPTSTR Str(unsigned int number);
LPTSTR Str(unsigned long number);
LPTSTR Str(float number);
LPTSTR Str(double number);
LPTSTR Str(long double number);
LPTSTR Str(LPCTSTR sText);				// ԭ�������󷵻�


//////////////////////////////////////////////////////////////////////////
// ������ ����
//////////////////////////////////////////////////////////////////////////

LPTSTR ClipboardGetText();				// ��ü������ı���û���ı����� ""������ı��ռ��Զ����١��� HM �Զ�����
void ClipboardSetText(LPCTSTR szText);		// ���ı�������������
void ClipboardSetText(tstring stringText);	// ���ı�������������
void ClipboardClear();					// ��ռ�����
void ClipboardSetBmp(HBITMAP hBmp);		// ����һ��λͼ��������
HBITMAP ClipboardGetBmp();				// ��ü������е�һ��λͼ


//////////////////////////////////////////////////////////////////////////
// �Զ��� ��̬���� ����
//////////////////////////////////////////////////////////////////////////

// �ض��� һ�� REDIMTYPE ����(��int�͡�int *�ͼ�ָ������)������Ĵ�С��
//   �¶���ռ��Զ�����
// arr��Ϊ����ָ�루��Ϊ int *�ͱ�������void **�ͱ���������Ϊ����ָ�룩��
//   ���������޸Ĵ�ָ���ָ��
// toUBound��ΪҪ�ض����������Ͻ磬����Ϊ��[0] to [toUBound]��
//   Ϊ -1 ʱ�����ٿռ䣬������ɾ��ԭ�ռ䣬��ʱ arr �ᱻ��Ϊ0
// uboundCurrent��Ϊ�ض���ǰ������Ͻ� [0] to [uboundCurrent]��
//   Ϊ -1 ��ʾ��δ���ٹ��ռ䣬��һ�ε���ʱ����Ϊ -1
// preserve��=true ��������ԭʼ���ݣ����򲻱���ԭ���ݱ���0
// ��������ֵΪ�¿ռ���ϱ꣬�� toUBound
template <typename REDIMTYPE>
int Redim(  REDIMTYPE *	 &arr, 
			int			  toUBound=-1, 
			int			  uboundCurrent=-1,  
			bool		  preserve=false )	// template ��������Ҫ��ͷ�ļ���
{
	// �����¿ռ䣺[0] to [toUBound]
	if (toUBound >= 0)
	{
		REDIMTYPE * ptrNew = new REDIMTYPE[toUBound + 1];		// +1 Ϊʹ�����±���� toUBound
		if (ptrNew==NULL) return 0;
		// �¿ռ�����
		memset(ptrNew, 0, sizeof(REDIMTYPE)*(toUBound + 1));
		
		// ��ԭ�пռ����ݿ������¿ռ�
		if (preserve && arr!=0 && uboundCurrent>=0)
		{
			int ctToCpy;										// ����ԭ�����ݣ���Ҫ�����ڴ�� REDIMTYPE Ԫ�ظ���
			ctToCpy = uboundCurrent;
			if (uboundCurrent>toUBound) ctToCpy = toUBound;		// ȡ uboundCurrent �� toUBound ����Сֵ
			ctToCpy = ctToCpy + 1;								// ���� +1����Ϊ uboundCurrent �� toUBound ���������Ͻ�
			memcpy(ptrNew, arr, sizeof(REDIMTYPE)*ctToCpy); 
		}
		
		// ɾ��ԭ�пռ�
		if (arr!=0 && uboundCurrent>=0) delete [] arr;
		
		// ָ��ָ���¿ռ�
		arr = ptrNew;
		return toUBound;
	}
	else		// if (toUBound < 0)
	{
		// �����ٿռ䣬ɾ��ԭ�пռ�
		if(arr!=0 && uboundCurrent>=0) delete [] arr;
		arr = 0;
		return 0;
	}
}


// ɾ����̬����Ŀռ䣬������ָ�� arr Ϊ 0
template <typename REDIMTYPE>
void Erase( REDIMTYPE *  &arr)
{
	if(arr!=0) delete [] arr;
	arr=0;
}


//////////////////////////////////////////////////////////////////////////
// �ļ����� ����
// ֧���ļ����ȺͶ�дλ��Ϊ LONGLONG ���͵����ݣ�__int64 �� double��
// �����ļ�λ�ö��� 0 ��ʼ��
// ��ȫ�ֹ�ϣ�� CBHashLK mEFOpenedFiles ���������Ѵ򿪵��ļ���
//   ������ļ����Ķ�Ӧ��ϵ
//////////////////////////////////////////////////////////////////////////

enum eEFLineFeed	// �ı��ļ����з�����
{
	EF_LineSeed_CrLf = 2573,	// �� �س���+���з���\r\n�� ����
	EF_LineSeed_Lf = 10,		// �� ���з���\n�� ����
	EF_LineSeed_Cr = 13,		// �� �س�����\r�� ����
	EF_LineSeed_None = 0		// δ֪���޻��з�
};

enum eEFOpenStyle	// �ļ��򿪷�ʽ
{
	EF_OpStyle_Output = 1,		// ������д
	EF_OpStyle_Input = 2,		// ����ȡ
	EF_OpStyle_Binary = 3,		// ��д
	EF_OpStyle_Append = 4		// ��׷��д
};

enum eEFShareStyle		// �ļ��򿪹���Ȩ��
{
	EF_ShareCanRead = FILE_SHARE_READ,
	EF_ShareCanWrite = FILE_SHARE_WRITE,
	EF_ShareCanDelete = FILE_SHARE_DELETE,
	EF_ShareCanReadWrite = FILE_SHARE_READ | FILE_SHARE_WRITE,
	EF_ShareCanReadDelete = FILE_SHARE_READ | FILE_SHARE_DELETE,
	EF_ShareCanWriteDelete = FILE_SHARE_WRITE | FILE_SHARE_DELETE,
	EF_ShareCanReadWriteDelete = FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE
};

class CBHashLK;	// �������

// ȫ�ֹ�ϣ�����������Ѵ򿪵��ļ�����Ԫ�ص� Key=������ַ�������Ϊ�ļ���
extern CBHashLK mEFOpenedFiles;	

// �� API �������ļ��������ļ��ľ����ʧ�ܷ��� -1 ���� INVALID_HANDLE_VALUE ��ֵ��
// openStyle ֵ�Ĳ�ͬ������Ӱ�����ı���ʽ�����Զ����Ʒ�ʽ��д�ļ�
//   �� EF_OpStyle_Binary ���ļ�Ҳ������ EFPrint д���ı���
//   EF_OpStyle_Input ��ʽҲ���� EFGetBytes �����ݡ�����
//   дȨ�޻�������ͬ���� EF_OpStyle_Input ��ʽ�򿪵��ļ�����д��
//   �� EF_OpStyle_Output �� EF_OpStyle_Append ��ʽ�򿪵��ļ����ܶ�
// sFailAddiInfo Ϊʧ��ʱ����ʾ��Ϣ
// bDeleteOnClose���������йظ��ļ��ľ�������رպ��Ƿ���ϵͳ�Զ�ɾ�����ļ�
HANDLE EFOpen(LPCTSTR szFileName, 
			  eEFOpenStyle openStyle = EF_OpStyle_Binary, 
			  bool bShowMsgIfFail = true, 
		      LPCTSTR szFailInfo = TEXT("�޷����ļ���"), 
		      eEFShareStyle shareStyle = EF_ShareCanReadWrite, 
		      bool bDeleteOnClose = false);
HANDLE EFOpen(tstring stringFileName, 
			  eEFOpenStyle openStyle = EF_OpStyle_Binary, 
			  bool bShowMsgIfFail = true, 
		      tstring stringFailInfo = TEXT("�޷����ļ���"), 
		      eEFShareStyle shareStyle = EF_ShareCanReadWrite, 
		      bool bDeleteOnClose = false);

// �رմ򿪵�һ���ļ������� hFile Ϊ EFOpen �������ص��ļ����
// bCloseAll == true ʱ�����ر����д򿪵��ļ�����ʱ���Բ��� hFile��
void EFClose(HANDLE hFile, bool bCloseAll = false);
 
// �����ļ����ȣ��������� LONGLONG ���͵ĳ���
// �ļ��ֽڷ�Χ�� 0 �� EFLOF-1
LONGLONG EFLOF(HANDLE hFile);

// �����ļ���ǰ��дλ��ָ�루LONGLONG ���ͣ����ļ�λ�ô� 0 ��ʼ
// ������ -1
LONGLONG EFSeekGet(HANDLE hFile);

// �����ļ���дλ��ָ��
// bShowResume ָ����������Ƿ񵯳��Ի�����ʾ���������û������ԵĻ���
//   �� iShowResume==1����ʾ�����С����ԡ��͡�ȡ����������ť��
//   �� iShowResume==2������ʱ��ʾ�����С���ֹ���������ԡ��͡����ԡ�������ť��
//   �� iShowResume==0������ʱ��������ʾ�򣬲�������ʾ��Ͳ����ڷ�������ʱ����
// �ɹ�����1����ʧ�ܷ��� < 0�����û������ԡ��򷵻� -2��
// ���û���ֹ��ȡ��������ʾ���򷵻� -1
int EFSeekSet(HANDLE hFile, 
			  LONGLONG llReadPos, 
			  int iShowResume = 1, 
			  LPCTSTR szFailInfo = TEXT("�޷��ƶ��ļ���дָ�롣"));


// ���ļ���дָ���ƶ����ļ�ĩβ
bool EFSeekSetEnd(HANDLE hFile);


// �жϵ�ǰ�ļ���дλ���Ƿ�Ϊ�ļ�ĩβ
bool EFEOF(HANDLE hFile);

// �жϵ�ǰ�ļ���дλ���Ƿ�Ϊ�ļ���ͷ
bool EFBOF(HANDLE hFile);

// ���ļ���� hFile �е� llReadPos λ�ÿ�ʼ��ȡһ���ֽڣ�
// �� llReadPos Ϊ <0 ��ֵ��Ϊ�ӵ�ǰ��дλ�ÿ�ʼ�������ƶ��ļ�λ��ָ��
// ��������������׼����һ����������ָ��Ϊ pBuff���ռ��ֽ���Ϊ iBuffMax
//   ����ȡ�����ݽ����ص��˻�����������ȡ iBuffMax ���ֽ�
// iShowResume ָ�������ȡ�����Ƿ񵯳��Ի�����ʾ
//   �� iShowResume=1����ʾ�����С����ԡ��͡�ȡ����������ť��
//   �� iShowResume=2������ʱ��ʾ�����С���ֹ���������ԡ��͡����ԡ�������ť��
//   �� iShowResume=0������ʱ��������ʾ�򣬲�������ʾ��Ͳ����ڷ�������ʱ����
// ������������ʾ��szFailInfo Ϊ������Ϣ
// ���ض�ȡ���ֽ�������ʧ�ܷ��� < 0�����û������ԡ��򷵻� -2��
//   ���û���ֹ��ȡ��������ʾ���򷵻� -1
LONG EFGetBytes(HANDLE hFile, 
				LONGLONG llReadPos, 
				char * const pBuff, 
				LONG iBuffMax = 131072, 
				int iShowResume = 1,
				LPCTSTR szFailInfo = TEXT("�޷���ȡ�ļ���"));


// ���ļ���� hFile �е� llWritePos λ�ÿ�ʼд��һ���ֽڣ�
// llWritePos ��Ϊ <0 ��ֵ����ʱΪ�ӵ�ǰ��дλ�ÿ�ʼд�����ƶ��ļ�λ��ָ��
// iShowResume ָ�������ȡ�����Ƿ񵯳��Ի�����ʾ
//   �� iShowResume=1����ʾ�����С����ԡ��͡�ȡ����������ť��
//   �� iShowResume=2������ʱ��ʾ�����С���ֹ���������ԡ��͡����ԡ�������ť��
//   �� iShowResume=0������ʱ��������ʾ�򣬲�������ʾ��Ͳ����ڷ�������ʱ����
// ������������ʾ��szFailInfo Ϊ������Ϣ
// ����д����ֽ�������ʧ�ܷ��� < 0�����û������ԡ��򷵻� -2��
//   ���û���ֹ��ȡ��������ʾ���򷵻� -1
LONG EFPutBytes(HANDLE hFile, 
				LONGLONG llWritePos, 
				char * const pBuff, 
				LONG iBuffLen = 131072, 
				int iShowResume = 1,
				LPCTSTR szFailInfo = TEXT("�޷�д���ļ���"));


// ���ļ� llWritePos ��λ�ô�ӡһ���ַ�
//   ��Unicode ��ĳ���ɴ��� Unicode �ַ��������Ὣ��ת��Ϊ Ansi ��д�룩
// llWritePos ��Ϊ <0 ��ֵ����ʱΪ�ӵ�ǰ��дλ�ÿ�ʼд�����ƶ��ļ�λ��ָ��
// iShowResume ָ�������ȡ�����Ƿ񵯳��Ի�����ʾ
//   �� iShowResume=1����ʾ�����С����ԡ��͡�ȡ����������ť��
//   �� iShowResume=2������ʱ��ʾ�����С���ֹ���������ԡ��͡����ԡ�������ť��
//   �� iShowResume=0������ʱ��������ʾ�򣬲�������ʾ��Ͳ����ڷ�������ʱ����
// ����д����ֽ�������ʧ�ܷ��� < 0�����û������ԡ��򷵻� -2��
//   ���û���ֹ��ȡ��������ʾ���򷵻� -1
LONG EFPrint(HANDLE hFile, 
			 LPCTSTR szText, 
			 eEFLineFeed styleLineFeed = EF_LineSeed_CrLf, 
			 LONGLONG llWritePos = -1, 
			 int iShowResume = 1,
			 LPCTSTR szFailInfo = TEXT("�޷����ļ���д���ַ�����")) ;
LONG EFPrint(HANDLE hFile, 
			 tstring stringText, 
			 eEFLineFeed styleLineFeed = EF_LineSeed_CrLf, 
			 LONGLONG llWritePos = -1, 
			 int iShowResume = 1,
			 tstring stringFailInfo = TEXT("�޷����ļ���д���ַ�����")) ;
// �� dblStartPos ��ʼ������ dblStartPos ���λ�ã����ҵ���һ���� sFoundChars 
//   �ַ����е�����һ���ַ��ĵط���
// ���� �� sFoundChars=="\r\n"�����ǲ��ҵ�һ���� \r �� \n �ĵط�
// sFoundChars ����ת��Ϊ ANSI��Ȼ������ÿ���ֽڶ���Ϊ����Ŀ��
// ע�� dblStartPos �� 0 ��ʼ����Ϊ -1����ӵ�ǰ��дλ�ÿ�ʼ
// �ҵ���������ĸ��ַ������Ӧ�ֽ��� rFoundChar ����
// ��ע������������ <=0���� rFoundChar ֵ��û�������
// bShowResume ָ�������ȡ�����Ƿ񵯳��Ի�����ʾ
// �� bShowResume=1����ʾ������"����"��"ȡ��"������ť��
// �� bShowResume=2������ʱ��ʾ������"��ֹ"��"����"��"����"������ť��
// �� bShowResume=0������ʱ��������ʾ�򣬲�������ʾ��Ͳ����ڷ�������ʱ����
// �ҵ���λ���� rPosLow��rPosHigh ���أ�
// �ҵ���λ�õ� Double ���ɺ���ֵ���أ��ɹ�ʱ���� >=0�� _
// ѭ�����ļ���β��δ�ҵ������� -99��dblStartPos �����ļ�ĩβ(��������-1)Ҳ���� -99�������� -1
// �������ԶԻ���ʱ���û������ԡ����� -2�����û���ֹ��ȡ����������ʾ�򣬷��� -1
// ע�⣺����������ı䵱ǰ��дλ��ָ�룬ֻ������
// LONGLONG EFFindNextPos( HANDLE hFile,  
// 						LONGLONG llStartPos = -1, 
// 						LPCTSTR szFoundChars = TEXT("\r\n"), 
// 						TCHAR * rFoundChar, 
// 						int iShowResume = 1,
// 						LPCTSTR szFailInfo = TEXT("�޷�д���ļ���")) ;



// ������д�뻺��д������ļ���Ȼ�����д�뻺��
BOOL EFFlushFile(HANDLE hFile);

// �����ļ�����λ�ã��ļ�������� GENERIC_WRITE �Ĵ����ԡ�
// �ú��������ڽض��ļ����ӳ��ļ���
// ���ӳ��ļ���MSDN��˵�����ӳ��Ĳ���Ϊ���ֵ����ʵ���ƺ���Ϊ 0 ֵ
// �� llPosEnd>=0����λ���� llPosEnd ������
// �� llPosEnd<0��Ϊ���ӵ�ǰ��дλ������Ϊ�ļ�����
BOOL EFSetEndOfFile(HANDLE hFile, LONGLONG llPosEnd);


// ���ļ���д�ã�����������Ϣ��ʾ�򣨲���������ģ����ñ�������
//  �� iShowResume=1����ʾ�����С����ԡ��͡�ȡ����������ť��
//  �� iShowResume=2����ʾ�����С���ֹ���������ԡ��͡����ԡ�������ť��
//  �� iShowResume=0 ��Ϊ����ֵ ��������ʾ�򣬺��������κ��£�ֱ�ӷ��� idOK
// ���������û�����ʾ���������İ�ť�������δ������ʾ�򣬷��� idOK
static EDlgBoxCmdID _EFRetryBox(HANDLE hFile, int iShowResume, LPCTSTR szFailInfo, LPCTSTR szTitle);




// ===============================================================
// CBHashLK���������� key �Ĺ�ϣ����
// ֧��ÿ��Ԫ������ 1 �� long �͵����ݡ� 2 �� long �͵ĸ������ݡ�
//    1 �� double �͵ĸ������� �� 2 �� �ַ����ĸ�������
//
// �����׳����쳣��
// throw (unsigned char)7;	// �����ڴ�
// throw (unsigned char)5;	// ��Ч�Ĺ��̵��û��������ֵ����
//                          // ����ͼ����Ѵ��ڵ�ͬ����ֵ����Ԫ�أ����ʼ������ڵ�Ԫ��
// throw (unsigned char)9;	// �±�Խ�磺�޷����������ݿռ�
//
// ---- ����ʹ�� Index �ķ�ʽ�������й�ϣ��Ԫ�� ----
//     for (i = 1; i<=hash.Count; i++)
//         cout<<hash.KeyFromIdx(i)
//     
//     for (i = 1; i<=hash.Count; i++)
//         cout<<hash.ItemFromIdx(i)
//     
// ע�� Index ���������ݶ�Ӧ��������ɾ�����ţ����ݵ� Index �����ܻ�仯
// ����ͬһʱ�̣�Index ��ͬ��һ�����ݣ�Key,Data,DataLong,DataString����ͬһ��
// ===============================================================

class CBHashLK
{
private:
	typedef long KeyType;		// key ������
	typedef long DataType;		// ���ݵ�����
	typedef long DataLongType;	// �������ݵ�����
	typedef long DataLong2Type;	// ��������2������
	
	typedef struct _MemType
	{
		KeyType Key;
		DataType Data;
		DataLongType DataLong;
		DataLong2Type DataLong2;
		double DataDouble;
		LPTSTR DataStr;
		LPTSTR DataStr2;
		bool Used;
		int Index;		// mArrTable[] ����� mArrTable[index] Ԫ�أ��Ǳ��汾 MemType ����
						//   ���ڵ� mem[] �е��±꣨index>0������ mem2[] �е��±꣨index<0��
						//   mArrTableCount == memUsedCount + memUsedCount2 ʱ�� index !=0 ʱ ��Ч
						//   �� RefreshArrTable �����ô˳�Ա
	} MemType;
	
	static const int	mcIniMemSize;  			// ��ʼ mem[] �Ĵ�С
	static const int	mcMaxItemCount; 		// ���Ԫ�ظ������������ֵ�� long ��ʾ�ķ�Χ֮�ڣ�
	static const float	mcExpandMaxPort;  		// ����Ԫ�ظ������� 0.75*memCount ʱ������ mem[] �Ŀռ�
	static const int	mcExpandCountThres; 	// ���� mem[] �ռ�ʱ���� memCount С�ڴ�ֵ��ÿ������ memCount*2���� memCount ���ڴ�ֵ��ÿ������ Count+Count/2
	static const int	mcExpandCountThresMax;	// ���� mem[] �ռ�ʱ���� memCount �Ѵ��ڴ�ֵ����ÿ�β������� Count+Count/2����ֻ���� Count+mcExpandBigPer
	static const int	mcExpandBigPer; 		// ���� mem[] �ռ�ʱ���� memCount �Ѵ��� mcExpandCountThresMax����ÿ�β������󵽵� Count+Count/2����ֻ���� Count+mcExpandBigPer
	static const int	mcExpandMem2Per; 		// ÿ������ mem2[] �Ĵ�С
	static const int	mcSeqMax; 				// ˳��������ֵ

private:
	MemType * mem;					// ��̬����ָ�룬�����鲻ʹ�� [0] ��Ԫ��
	int memCount, memUsedCount;		// ��̬��������±꣬mem[] �����±�Ϊ [0] �� [memCount]����ϣ������Ԫ�ظ���
	MemType * mem2;					// �ռ��ͻ��Ԫ�صı���ռ䣬˳��ʹ��
	int memCount2, memUsedCount2;	// mem2[] �����±�Ϊ [0] �� [memCount2]������ [0] ���ã���ʹ�ÿռ�Ϊ [1] �� [memUsedCount2]
	int mTravIdxCurr;				// �� NextXXX ���������ĵ�ǰ index����ֵ��ʾ mem[] �е��±꣬��ֵ��ʾ mem2[] �е��±�

	
	// ֧��ͨ�������±� Index ����һ����ϣ�����ݣ�mArrTable ָ��̬���飬
	//   ����Ԫ�ر��棺���й�ϣ������������˳�����ڵ� mem[] �е��±꣨>0��
	//   �� mem2[] �е��±ꡣ
	// ����һ�Σ������й�ϣ������ mem[] �� mem2[] ���±���ڴ����飬
	//   �Ժ����ظ�������ֱ��ͨ�������±� Index ����һ����ϣ�����ݡ�
	//   mArrTableCount != memUsedCount + memUsedCount2 Ϊ��־��
	//   �� !=����־Ҫ����ˢ�±�����ע�����±�����Ԫ��˳����ܻ����š�
	//   ����ϣ�����ݵ� Index ������һֱ�����
	int * mArrTable;
	int mArrTableCount;
	
public:
	CBHashLK(int memSize=0);		// memSize=0 �򿪱ٳ�ʼ mcIniMemSize ���ռ䣬���򿪱� memSize ���ռ䣬memSize Ӧ��ʵ�����ݸ�����һЩ
	~CBHashLK();
	void AlloMem(int memSize);		// ���ȿ��ô˺��������㹻��Ŀռ䣬�Լ����Ժ��Զ�����ռ�Ĵ��������Ч��
	bool Add(DataType data, KeyType key=0, DataLongType dataLong=0, DataLong2Type dataLong2=0, LPCTSTR dataStr=0, LPCTSTR dataStr2=0, double dataDouble=0.0, bool raiseErrorIfNotHas=true);	// ���Ԫ��
	bool Remove(KeyType key, bool raiseErrorIfNotHas=true);					// ɾ��Ԫ��

	// ���� key ���Ԫ�ء���������
	DataType Item(KeyType key, bool raiseErrorIfNotHas=true);				
	DataLongType ItemLong(KeyType key, bool raiseErrorIfNotHas=true);
	DataLong2Type ItemLong2(KeyType key, bool raiseErrorIfNotHas=true);
	double ItemDouble(KeyType key, bool raiseErrorIfNotHas=true);
	LPTSTR ItemStr(KeyType key, bool raiseErrorIfNotHas=true);
	LPTSTR ItemStr2(KeyType key, bool raiseErrorIfNotHas=true);

	// ���� key ����Ԫ�ء���������
	bool ItemSet(KeyType key, DataType vNewValue, bool raiseErrorIfNotHas=true);				
	bool ItemLongSet(KeyType key, DataLongType vNewValue, bool raiseErrorIfNotHas=true);
	bool ItemLong2Set(KeyType key, DataLong2Type vNewValue, bool raiseErrorIfNotHas=true);
	bool ItemDoubleSet(KeyType key, double vNewValue, bool raiseErrorIfNotHas=true);
	bool ItemStrSet(KeyType key, LPCTSTR vNewValue, bool raiseErrorIfNotHas=true);
	bool ItemStr2Set(KeyType key, LPCTSTR vNewValue, bool raiseErrorIfNotHas=true);


	// ���� index ���Ԫ�ء���������
	DataType ItemFromIndex(int index, bool raiseErrorIfNotHas=true);			
	DataLongType ItemLongFromIndex(int index, bool raiseErrorIfNotHas=true);
	DataLong2Type ItemLong2FromIndex(int index, bool raiseErrorIfNotHas=true);
	double ItemDoubleFromIndex(int index, bool raiseErrorIfNotHas=true);
	LPTSTR ItemStrFromIndex(int index, bool raiseErrorIfNotHas=true);
	LPTSTR ItemStr2FromIndex(int index, bool raiseErrorIfNotHas=true);

	// ���� index ����Ԫ�ء��������ݣ����������� Key��KeyΪֻ����
	bool ItemFromIndexSet(int index, DataType vNewValue, bool raiseErrorIfNotHas=true);			
	bool ItemLongFromIndexSet(int index, DataLongType vNewValue, bool raiseErrorIfNotHas=true);
	bool ItemLong2FromIndexSet(int index, DataLong2Type vNewValue, bool raiseErrorIfNotHas=true);
	bool ItemDoubleFromIndexSet(int index, double vNewValue, bool raiseErrorIfNotHas=true);
	bool ItemStrFromIndexSet(int index, LPCTSTR vNewValue, bool raiseErrorIfNotHas=true);
	bool ItemStr2FromIndexSet(int index, LPCTSTR vNewValue, bool raiseErrorIfNotHas=true);

	KeyType IndexToKey(int index, bool raiseErrorIfNotHas=true);
	int KeyToIndex(KeyType key, bool raiseErrorIfNotHas=true);

	bool IsKeyExist(KeyType key);					// �ж�ĳ�� key ��Ԫ���Ƿ����
	void Clear(void);								// �������Ԫ�أ��ض��� mcIniMemSize ���洢�ռ�
	
	void StartTraversal();							// ��ʼһ����������
	DataType NextItem(bool &bRetNotValid);			// �������̿�ʼ�󣬲��ϵ��ô˺��������ÿ��Ԫ�أ�ֱ�� bRetNotValid ���� true
	DataLongType NextItemLong(bool &bRetNotValid);	// �������̿�ʼ�󣬲��ϵ��ô˺��������ÿ��Ԫ�صĸ������ݣ�ֱ�� bRetNotValid ���� true
	DataLong2Type NextItemLong2(bool &bRetNotValid);
	double NextItemDouble(bool &bRetNotValid);
	LPTSTR NextItemStr(bool &bRetNotValid);
	LPTSTR NextItemStr2(bool &bRetNotValid);

	KeyType NextKey(bool &bRetNotValid);			// �������̿�ʼ�󣬲��ϵ��ô˺��������ÿ��Ԫ�ص� key��ֱ�� bRetNotValid ���� true

	int Count(void);								// ���ع���Ԫ�ظ���


private:
	int AlloMemIndex(KeyType key, bool CanExpandMem=true );			// ���� Key ����һ�� mem[] �е�δ�ô洢�ռ䣬���� mem[] �����±�
	int FindMemIndex(KeyType key) const;							// ���� Key ���� mem[] ��Ԫ�أ����� mem[] �����±�
	int FindSeqIdx(KeyType key, int fromIndex, int toIndex);		// �� mem[] �м�Ϊ key ��Ԫ���±꣬�����ҿռ��±�Ϊ�� fromIndex ��ʼ���� toIndex �����Ŀռ�
	void ReLocaMem(int preMemCountTo);								// ���·��� mem[], mem2[] �ĸ�Ԫ�صĵ�ַ��mem2[] ��ĳЩԪ�ؿ��ܱ������ƶ��� mem[]
	void ExpandMem(void);											// �ض��� mem[] �����С������ mem[] �Ŀռ�
	int TraversalGetNextIdx(void);									// �� NextXXX ��������ʱ��������һ����Next���� mem[]�±꣨����ֵ>0������ mem2[] ���±꣨����ֵ<0�������ѱ�������������ֵ=0��
	int AlloSeqIdx(int fromIndex, int toIndex);						// �� mem[] ��һ��ûʹ�õĿռ䣬�����ҿռ��±�Ϊ�� fromIndex ��ʼ���� toIndex �����Ŀռ�
	bool RefreshArrTable();											// ������ϣ���������±���� mArrTable[]������ mArrTableCount Ϊ���ݸ��������سɹ���ʧ�ܣ�

	int RedimArrMemType(MemType * &arr, int toUBound=-1, int uboundCurrent=-1, bool preserve=false);	// �ض��� һ�� MemType ���͵����飨������� lMem[] �� lMem2[]���Ĵ�С���¶���ռ��Զ�����

	int GetMemIndexFromKey(KeyType key, bool raiseErrorIfNotHas=true);	// �� Key ��������� mem[] �е��±꣨����ֵ>0������ mem2[] �е��±꣨����ֵ<0���������� 0
	int GetMemIndexFromIndex(int index, bool raiseErrorIfNotHas=true);	// �� index ��������� mem[] �е��±꣨����ֵ>0������ mem2[] �е��±꣨����ֵ<0���������� 0

	void SaveItemString(TCHAR ** ptrSaveTo, LPCTSTR ptrNewString);			// �� new �������ַ����ռ䣬�� key ָ����ַ����������¿ռ䣻ptrSaveTo ��һ�������ַ�����ַ��ָ������ĵ�ַ����ָ���ָ����������桰�� new ���ٵ����ַ����ռ�ĵ�ַ�������� ��*ptrSaveTo = �¿ռ��ַ��
};






//////////////////////////////////////////////////////////////////////
// CBArrLink�ࣺ��Ч����������
//
// �����ڴ��� Add �����ݣ���ͨ���±�������е�Ԫ�أ��±��1��ʼ��
// ɾ������ʱ�����������ǽ����һ���������ȱ
// ���ʺ�������������ұ������������ֻ������ int
// -------------------------------------------------------------------
// �����ڱ���˫��2.8G CPU/2G�ڴ�Ļ����ϣ�
// ��� 100000�� ����Ȼ�����һ�飬���� 16�� Clock��16���룩
// ��� 500000�� ���ݽ��� 64�� Clock��64���룩��Ȼ�����һ���ٽ��� 
//   16�� Clock��16���룩���������в����ܹ���ʱ��0.1 �����ڣ�
// -------------------------------------------------------------------
//
// ÿ�������� 512 ��Ԫ�أ���ͨ�����캯���ı��ֵ�� 
// �����ȱ����ڵ�1�������У����1�������������Զ� new ��2������
//   ��2������Ҳ��512��Ԫ�أ��������ݼ������浽��2�������С���
//   ���ռ䲻���� new ������ʱ���м䲻�� delete �ɿռ䣬ֻ�ǰѾɿռ�
//   ���¿ռ���������ʹ�ã����Ч��
//////////////////////////////////////////////////////////////////////

/*
	�û��±�	��ģ���ڲ�ʹ�ÿռ�
	1��512		ppArr[1][0] �� ppArr[1][511]
	513��1024	ppArr[2][0] �� ppArr[2][511]
	1025��1536	ppArr[3][0] �� ppArr[3][511]
	1537��2048	ppArr[4][0] �� ppArr[4][511]
	����		����
	index		ppArr[(index-1) / 512 + 1][(index-1) % 512]
*/

// ���� throw �Ĵ���
// throw (unsigned char)9;			// ��������������Χ
class CBArrLink
{
private:
	typedef struct _MemType
	{
		int DataInt;		// ��������1
		int DataInt2;		// ��������2
	} MemType;

	static const int	mcItemsPerArr;  			// ÿ�������Ԫ�ظ�����Ĭ��ֵ����ͨ�����캯���ı�
	static const int	mcppArrInit;  				// ����������ַ��ָ�������ʼ�ռ��С
	static const int	mcppArrExpPer;  			// ����������ַ��ָ������ÿ�������Ŀռ�
													// ����һ���ռ佫�ô˿ռ䱣��һ�� 512����
													// �ĵ�ַ

private:
	// ��ָ������ MemType *pArr[]; ����ÿ�����������顱���׵�ַ��ÿ�����������顱512��Ԫ�أ��±��0��ʼ�ã�
	// ÿ�����������顱��Ϊ pArr[i]�����������顱ÿԪ��Ϊ pArr[i][���������±�]
	// Ȼ��ָ������ pArr ����Ĵ洢�ռ�ҲӦ��̬���䣬ָ�������׵�ַΪ ppArr
	MemType **ppArr;

	// ppArr[] �����±귶Χ��[0] ~ [ppArrUbound]���� [0] ���ã��� [1] ��ʼ��
	// ppArr[1]��ppArr[2]��������ppArr[ppArrUsedCount] �Ѿ�ָ������������
	int m_ppArrUbound, m_ppArrUsedCount;  

	// ÿ�������Ԫ�ظ�����Ĭ�� = mcItemsPerArr
	int m_ItemsPerArr;
 
	int m_DataCount;				// �����ܸ���
	
public:
	CBArrLink(int iItemsPerArr=0);	// ���캯����iItemsPerArrΪÿ��������Ԫ�ظ�����Ϊ0ʱʹ��Ĭ��ֵ512��
	~CBArrLink();					// ��������

	int Add(int data1, int data2=0);	// ��������ݣ�����������ݺ�������ܸ�����>0����ʧ�ܷ���0
	int Remove(int index, bool bRaiseErrIfErr=false);	// ͨ���±�ɾ��һ�����ݣ����������ǽ����һ���������ȱ
														// ����ɾ�����ݺ�������ܸ���
	int Item(int index, bool bRaiseErrIfErr=false);		// ͨ���±���һ�����ݵ� DataInt
	int Item2(int index, bool bRaiseErrIfErr=false);	// ͨ���±���һ�����ݵ� DataInt2
	void * GetItemsArr();								// �������󱣴��������Ϊһ�����飨����ΪMemType�ͣ����أ�
														//   ��ģ���Զ����ٴ洢�ռ䣬���ؿռ��׵�ַ
														//   ���غ��벻Ҫʹ�� [0] �Ŀռ䣬�� ����ֵ[1] ��ʼʹ��
														//   �ÿռ佫���´ε��ñ�����ʱ�� free������ʱҲ free

	int Count();					// ��������ݸ���

	void Clear();					// ����������ݲ����¿��ٳ�ʼ�ռ�

private:
	void Init();					// �����ʼ�ռ�
	void Dispose();					// �����������
	void * m_ptrArrRet;				// GetItemsArr() ��������ʱ���� ��ģ���Զ����ٵĴ洢�ռ�ĵ�ַ
									//   �ÿռ佫���´ε��ñ�����ʱ�� free������ʱҲ free
};





//////////////////////////////////////////////////////////////////////
// CHeapMemory�� ��ȫ�ֶ���ά������ͨ�� new ������ڴ�ָ�룬�ڱ������
//				 ����ʱ���Զ� delete ��Щ�ڴ�
//
//////////////////////////////////////////////////////////////////////

class CBHeapMemory  
{
public:
	CBHeapMemory(int initSize=0);
	virtual ~CBHeapMemory();
	
	// ���һ��Ҫ�ɱ��������ġ�����new����Ŀռ�ĵ�ַ��
	//   �ɹ����ر�����������ĵ�ַ����������������һ����
	// �� bArrayNew=true������ delete ʱ��[]������ delete ʱû��[]
	// iUserData Ϊ����洢�ĸ�������
	int AddPtr(void *ptrNew, bool bArrayNew=true, long iUserData=0);

	// �� new ���� size ���ֽڵĿռ䣬���Զ���0
	//   ���ش˿ռ�ĵ�ַ��������0�������ɱ������Զ���¼�˿ռ�ĵ�ַ
	void * Alloc(int size); 

	// �ͷ� ptr ��ָ���һ���ڴ�ռ�
	//   ptr �������ɱ�����������Ŀռ䣬���򱾺��������ͷ�
	void Free(void *ptr);

	// ���� ptr ��ָ���һ���ڴ�ռ��Ƿ����ɱ��������
	bool IsPtrManaged(void *ptr);

	// ���� ptr ��ָ���һ���ڴ�ռ䣬������������ĸ�������
	long UserData(void *ptr);

	// ���� ������������Ŀռ����
	int CountPtrs();

	// ���� �������������һ���ռ�ĵ�ַ
	//   index ӦΪ 1��CountPtrs() ֮��
	//   �ɲ��� ptrbArrayNew ���ظÿռ� delete ʱ�Ƿ�Ӧ��[]
	void * PtrEach(int index, bool * ptrbArrayNew=0);

	// ����һ���ڴ�ռ䡣ʵ���ǵ��� memset (������ include <memory.h>) ��
	//   Ϊʹ�������򲻱��� include memory.h������Ҳ�ṩ��������ܽӿ�
	void ZeroMem(void * ptr, unsigned int length);	
	
	// �ڴ濽����ʵ���ǵ��� memcpy (������ include <memory.h>) ��
	//   Ϊʹ�������򲻱��� include memory.h������Ҳ�ṩ��������ܽӿڣ�
	void CopyMem(void * dest, void * source, unsigned int length);	
	
	// ǿ���ͷű���������¼�����е�ַָ��Ŀռ�
	//   ����������ʱҲ���Զ����ñ�����
	void Dispose();									
	
private:

	// �����ɱ��������ġ������� new ��̬����Ŀռ��ַ
	//   key=��ַ��data=��ַ��
	//   dataLong  !=0 ʱ��delete ʱ����[]��dataLong=0��delete ʱ��[]
	//   dataLong2 !=0 ʱ����ʾ��������ָ��������׵�ַ��dataLong2 Ϊָ������Ԫ�ظ���
	//      free������ָ�ռ䣨ָ������ռ䣩ǰ���ɰ�����һfreeָ�������Ԫ����ָ�ռ�
	//      �Լ�ʱ�ͷ��ڴ棻Ҳ�ɲ���һfree��Ԫ����ָ�ռ䣬��Ϊ��Ԫ����ָ�ռ��ַҲ�ɱ����󱣴���
	//   dataLong2 ==0 ʱ����ʾ�����Ĳ���ָ��������׵�ַ����û����һfreeָ�������Ԫ����ָ�ռ������
	CBHashLK memHash;
};


// ȫ�ֶ������ HM ����������������������� new ���ٵ��ڴ���׵�ַ���ö���
// ����ʱ���Զ� delete ��Щ�ڴ�ռ䡣�����ı��������� BWindows.cpp �У�����
// �� extern �����˱����������а����� h �ļ���ģ�鶼��ʹ�ô�ȫ�ֱ���
extern CBHeapMemory HM;	







//////////////////////////////////////////////////////////////////////
// CBApp �ࣺ ����Ӧ�ó���ȫ����Ϣ
//
//////////////////////////////////////////////////////////////////////

enum EImgObjType	// �Ѽ��ص�ͼ���������ͣ����� pApp->AddImageObjHandle
{
	eImgBitmap = IMAGE_BITMAP, 
	eImgCursor = IMAGE_CURSOR,
	eImgIcon = IMAGE_ICON,
	eImgEnhMetaFile = IMAGE_ENHMETAFILE
};

class CBApp		// Ӧ�ó���ȫ����Ϣ����
{
public:
	// ���캯������������
	CBApp(HINSTANCE hInst, 
		HINSTANCE hPrevInst, 
		char * lpCmdLine, 
		int nShowCmd);
	~CBApp();
	
	// ����Ա��ֻ�ܻ��ֵ�������޸ģ����ڹ��캯���ĳ�ʼ�������޸ĵģ�
	const HINSTANCE hInstance;	// WinMain �������ݹ����� hInstance
	const int CmdShow;			// WinMain �������ݹ����� nShowCmd
	
	// ���Ӧ�ó���ǰ���е�·������� \��
	LPTSTR Path();	
	
	// ��������в����ַ���������exe�ļ���·�����ַ����ռ��� Windows ά����
	LPTSTR Command() const;
	
	// �����Ļ��ȡ��߶�
	int ScreenWidth() const;
	int ScreenHeight() const;


	// ���غ����ñ�����ȫ���������״������ֵ��EStandardCursor ö��ֵ����ԴID
	// �ڱ������е����д��ں��Ӵ��ڿؼ�����궼�����д������״
	// ����Ϊ 0 ���ʾʹ�ø��Դ��ڻ��Ӵ��ڿؼ��Լ��Ĺ����״
	long MousePointerGlobal();
	HCURSOR MousePointerGlobalHCursor();
	void MousePointerGlobalSet(EStandardCursor cursor);		
	void MousePointerGlobalSet(long idResCursor, LPCTSTR typeRes=0);

	
	// �� m_hashImageObjs �����һ���¼�¼����¼һ���Ѽ��ص�ͼ�����
	//   �ľ�����Ա�������ǰ���Զ�ɾ�����м�¼�Ķ���
	// Ҳ����ʱ���� pApp->ClearImageObjs(); ��ɾ����Щ����
	// hObject Ϊͼ���������
	// iTypeImage Ϊͼ�����ͣ�IMAGE_BITMAP/IMAGE_CURSOR/IMAGE_ICON
	// ����ӳɹ����� true�����򷵻� false�����ظ����ͬһ���Ҳ���� false
	bool AddImageObjHandle(HANDLE hObject, EImgObjType typeImage );
	
	// �ͷ� m_hashImageObjs �м�¼�����ж������ m_hashImageObjs
	void ClearImageObjs();

private:
	// Ӧ�ó���ǰ���е�·���ַ���������
	TCHAR m_path[2048];		

	// ȫ�ִ����������������ֵ��EStandardCursor ö��ֵ����ԴID��
	//   ��Ӧ�����Ϊ m_hCursorGlobal
	// 0 ��ʾʹ�ø��Դ��ڵ�����꣬����ʹ��ȫ��ͳһ���
	long m_CursorGlobalIdx;		
	
	// ȫ�ִ������������������ m_CursorGlobalIdx �� 0 ʱ����Ч��
	HCURSOR m_hCursorGlobal;

	// ���汾�������д�������ϵĿؼ����˵��������ص�λͼ����ꡢͼ���
	//   ����������Щ�����ڳ������ǰ��pApp ��ָ��������ʱ�����Զ��ͷ�
	// Ҳ����ʱ���� pApp->ClearImageObjs(); ���ͷ�
	// Key = ��������Data = ��������ItemLong = IMAGE_BITMAP/IMAGE_CURSOR/IMAGE_ICON
	CBHashLK m_hashImageObjs;
};


// ȫ�ֶ������ pApp����ָ�룩����������ָ��Ķ������ڻ�ñ������ȫ�ֳ�����Ϣ��
//   �� hInstance �ȡ������ı��������� BWindows.cpp �У������� 
//   extern �����˱����������а����� h �ļ���ģ�鶼��ʹ�ô�ȫ�ֱ���
extern CBApp *pApp;	


