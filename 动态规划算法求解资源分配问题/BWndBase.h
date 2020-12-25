//////////////////////////////////////////////////////////////////////
// BWndBase.h: CBWndBase ��Ķ���
// �������洰�ڹ��ܣ���Ϊ CBForm��CBControl ��Ļ���
//
// ֧�֣�
//     ��Ҫ BWindows ģ���֧��
//////////////////////////////////////////////////////////////////////

#pragma once
#pragma warning(disable:4996) // �ر� warning C4996: �� 'wcscpy': This function or variable may be unsafe. Consider using wcscpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

#if _MSC_VER > 1200   // MSVC++ 6.0  _MSC_VER == 1200
	// VC6 ����� warning LNK4044: �� warning LNK4044: unrecognized option "manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' ...
	#ifdef _M_IX86
	#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#elif _M_IA64
	#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#elif _M_X64
	#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#else
	#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#endif
#endif

#include "BWindows.h"
#include <commctrl.h>
#include <richedit.h>

// ���峣������Щ���� VC6 ��ͷ�ļ�û�У�
// �ڸ߰汾�� VC �У�ͷ�ļ����Ѱ�����Ӧ���ٴ˴�����
#ifndef WS_EX_LAYERED
	#define	WS_EX_LAYERED	0x80000
#endif

#ifndef LWA_COLORKEY
	#define	LWA_COLORKEY	0x1
#endif

#ifndef LWA_ALPHA
	#define	LWA_ALPHA		0x2
#endif

enum EAlign	// �ı�ˮƽ���뷽ʽ
{
	eAlignLeft = DT_LEFT, 
	eAlignCenter = DT_CENTER,
	eAlignRight = DT_RIGHT
};


enum EVAlign	// �ı���ֱ���뷽ʽ
{
	eVAlignTop = DT_TOP, 
	eVAlignVCenter = DT_VCENTER,
	eVAlignBottom = DT_BOTTOM
};


// ͼƬ��ť������
//   ��ť�ĳ���״̬������״̬������״̬����ɫ״̬��ͼƬ���ͬһ�Ŵ�ͼƬ
//   ��ö�����ͱ�ʾ��Щ״̬ͼƬ��������һ�Ŵ�ͼƬ
// ö����ֵ����16λ��ʾ��ֱƫ�ƣ���16λ��ʾˮƽƫ��
//           4��λ��ʾһ��״̬��ͼƬ��ƫ�ƣ�ÿ16λ�дӸߵ�������Ϊ����λ����ʹ��λΪ0����
//			 ����״̬ƫ����������״̬ƫ����������״̬ƫ��������ɫ״̬ƫ����
enum EPicButtonType
{
	epbNone = 0,
	epbVertNormHiltDownDisb = 0x01230000,	// ��ֱ���� ���桢���������¡���ɫ
	epbVertNormHiltDisb = 0x01020000,		// ��ֱ���� ���桢��������ɫ
	epbVertNormHiltDown = 0x01200000,		// ��ֱ���� ���桢����������
	epbVertNormDown = 0x00100000,			// ��ֱ���� ���桢����
	
	epbHoriNormHiltDownDisb = 0x00000123,	// ˮƽ���� ���桢���������¡���ɫ
	epbHoriNormHiltDisb = 0x00000102,		// ˮƽ���� ���桢��������ɫ
	epbHoriNormHiltDown = 0x00000120,		// ˮƽ���� ���桢����������
	epbHoriNormDown = 0x00000010			// ˮƽ���� ���桢����
};


// �����ؼ��ĸ�������
// ����Ŀռ�ʹ�� CBForm �����ݳ�Ա���ؼ��Ŀռ䶯̬����
typedef struct _WndProp			 
{
	long cursorIdx, cursorIdx2;	// cursorIdx Ϊ���嵱ǰ������������ţ���Ӧ���Ϊ hCursor��0 ��ʾʹ��ϵͳĬ��
								// cursorIdx2 Ϊ cursorIdx �ĸ������ڴ��������Զ��϶��߿������С��m_iBorderAutoResizable��
								//   ʱ����Ӧ WM_MouseMove ��Ϣʱ�����ƶ����Ǳ߿������� cursorIdx2 �ָ����ָ��
	HCURSOR hCursor, hCursor2;	// hCursor Ϊ���嵱ǰ������������� cursorIdx �� 0 ʱ����Ч��
								// hCursor2 Ϊ hCursor �ĸ���������ͬ��


	COLORREF backColor;			// �����ؼ� ����ɫ��-1 ��ʾʹ��Ĭ��ɫ
	HBRUSH hBrushBack;			// ����ɫ��ˢ�����ñ���ɫ��ͬʱ�ʹ���
								//   �Դ��壺CBForm ��������ʱ DeleteObject
								//   �Կؼ���EnumChildProcSubClass �е�ж�ز��� DeleteObject
	COLORREF foreColor;			// �����ؼ� ǰ��ɫ��-1 ��ʾʹ��Ĭ��ɫ
	bool bBackStyleTransparent;	// �ؼ������Ƿ�͸��������Static��ĳЩ�ؼ���Ч��
	HFONT hFont;				// �������壨Ϊ0��ʾ��ϵͳ���壻�����ʾ���Զ������壬����� DeleteObject ��
	RECT rcTextOutClip;			// PrintText ����ı�ʱ�����λ�ã�.left��.top���������Χ
	int iTextOutStartLeft;		// ����ı��ķ�Χ��ԭʼ��߽磬�� PrintText ����ʱȷ��������߽�
	unsigned int iTextOutFlags;	// ����ı���ѡ��


	bool stretch;					// �����ؼ� �����ñ���ͼƬʱʹ�ã��Ƿ��Զ�����ͼƬ��С����Ӧ �����ؼ� �Ŀͻ���
	HBITMAP hBmpDisp;				// ������Ϊ����ʹ�ã�Ҫ��Ϊ������λͼͼƬ��stretch=true ʱ����Ϊԭʼδ���ŵ�λͼ���
	RECT rcPictureClip;				// ����Ա>=0ʱ��Ч��Ҫ��ȡͼƬ��һ���ֶ����ǰ�ͼƬȫ����ʾ�� �����ؼ� ��
	
	int iTitleBarBehav;				// �Ƿ���б�������Ϊ��=0�����У�=1 ����϶����ƶ� �����ؼ� ���ڵĴ��壩
	
	bool fFromCls;					// ������Ϊ����ʹ�ã�Ϊһ����־����
									//  �� Cls() ʱ����Ա����Ϊ true���� InvalidateRect��ͨ����Ӧ WM_PAINT ��ʵ�� Cls
									//  ����Ӧ WM_PAINT ʱ�����˳�ԱΪ true �������� Paint �¼�
									//  ������ Paint �¼��������û��ֵ��� Cls ������ݹ�

	LPTSTR tagString;				// �����ַ�������
	int iTag1;						// ������������1
	int iTag2;						// ������������2
	double dTag;					// ���� double ������


	// ���½����ڿؼ��������ڴ��壩
	EPicButtonType ePicBtn;			// �Ƿ���ΪͼƬ��ť����Ϊ���ֵ��Ϊ0����ͼƬ��ť�����ʾλͼ������
	int iPicBtnCurrDisp;			// �����ΪͼƬ��ť����ǰ��ʾ�İ�ť״̬��0=���棻1=������2=���£�3=��ɫ
	int iPicBtnStateStyle;			// �Ƿ���Ϊ Checked ���Ͱ�ť(=1)������һ�ΰ���ȥ���ٵ���һ��̧�𣩣�
	int iPicBtnCheckedState;		// iPicBtnStateStyle<>0 ʱ��Ч�����ڰ�ť Checked() ״̬
									// ���ɿؼ��� ValueChecked() �������Ŀǰ��ť״̬


	// ======================================================================
	// ��������Է�����
	//	1. ��������³�Ա��
	//  2. CBForm ���캯����ʼ�� m_WndProp.��Ա ��ֵ
	//     ���� PropertyMemCtrl() ��̬�����г�ʼ���¿ռ� ��Ա��ֵ����Ϊ0�ɲ���ʼ���������㣩
	//  3. CBForm ��� ClearResource() �����У������Ա��ֵ���ͷų�Ա��Ӧ����Դ
	//     EnumChildProcSubClass �е�ж�ز���ж�ؿؼ��� ��Ա��ֵ����Ӧ��Դ
	//	4. ���������ӻ�ȡ���Ժ��������Եĺ�����������ͨ������
	//	   m_pPro = PropMem(false); ����ͻ�ñ��ṹ�����ݵĿռ䣬
	//	   Ȼ��ʹ�ö�̬�ռ��еı���Ա
	//	   ���ɲμ� BackColor() �� BackColorSet(COLORREF color)��
	//	5. ʵ�ֹ��ܣ��� BForm.cpp �� CBForm_DlgProc �� CBForm_ControlProc ������
	//	   ����� EventsGenerator ��������Ӵ��������Ϣ�Ĵ��롣
	//     ���������CBForm �� CBControl���У��� PropMem() ������Կռ䣬Ҳ�ɣ�
	//     �Դ��壬ֱ���� m_pPro ������Կռ䣻
	//     �Կؼ����� CBWndBase �ľ�̬���� PropertyMemCtrl ���� �ؼ���� ������Կռ䣻
	// ======================================================================



} STWndProp ;


class CBWndBase
{
protected:
	// ======================================================================================
	// ��̬��Ա�ͳ�Ա����
	// ======================================================================================

	// ����������̬��ϣ�����б�������ã���ms_hashCtrls��ms_hashCtrlResIDs
	//   ���������Ӵ��ڿؼ���Ϣ��λ�����д����ϵĿؼ���ͳһ�ô˱��棩
	// �κδ��屻����ʱ��WM_INITDIALOG���ݹ�ö�������Ӵ��ڣ���֮���໯����
	//   �Ӵ�����Ϣ�����ڴˣ��κδ��屻ж��ʱ��ClearResource�����ݹ�ö����
	//   ���Ӵ��ڣ��Ӹù�ϣ����ɾ����Щ�Ӵ�����Ϣ


	// Key = �ؼ�hwnd��
	// Item = �ؼ�Ĭ�ϴ��ڳ����ַ��
	// ItemLong = ��λ�ڴ���� hWnd�����Դ�Ϊ key �� ms_hashWnd �л�ô���
	//   ��Ӧ�� CBForm ����ĵ�ַ��ע���ֵ���ǿؼ������ڵľ����
	//   ��ֱ������λ�ڴ���� hWnd�������ڵľ������ GetParent ���
	// ItemLong2 = ��̬�����һ�� STRControlProp ���͵����ݵĵ�ַ����ʾ�ؼ�
	//    �ĸ������ԡ�ֻ���������˿ؼ���ĳ����������ʱ���Żᶯ̬����һ��
	//    STRControlProp �Ŀռ䣬ItemLong2 �Ż᲻Ϊ0��
	//    ���� ItemLong2 Ϊ 0 ��ʾ�ؼ�û�б����ù���Щ����
	static CBHashLK ms_hashCtrls;	


	// Key = �ؼ���ԴID
	// Item = �ؼ������ hWnd
	// ItemLong = ֱ�����������ڵ� hWnd���粻λ�������ؼ��ڣ��� ItemLong2 ��ͬ��
	// ItemLong2 = ��λ�ڴ���� hWnd�����Դ�Ϊ key �� ms_hashWnd �л�ô���
	//   ��Ӧ�� CBForm ����ĵ�ַ
	static CBHashLK ms_hashCtrlResIDs;


	// ============================================================
	// �йظ������Ե�˵����
	// �����Ǵ��廹�ǿؼ���һ�������һ���ؼ����� һ�� STWndProp ����
	//   �ռ䱣��ô����ÿؼ������и������ԡ���ͬ���ǣ�
	// ���壨CBForm��Ķ���ʹ��һ�� STWndProp ���͵����ݳ�Ա��Ա m_WndProp
	// �ؼ���CBControl��Ķ��������� STWndProp ���͵����ݳ�Ա����Ϊ
	//   CBControl ��Ķ��󽫱���̬���������٣����������ٿؼ���һ������
	// ��һ���ؼ���CBControl��Ķ��󣩣�����Ҫʱ��̬����һ�� STWndProp ����
	//   �Ŀռ䣬���ɾ�̬��ϣ�� ms_hashCtrls ����ؼ� hWnd �͸ÿռ�Ķ�Ӧ��ϵ
	//   �������Ա���ؼ��� hWnd ��Ӧ�������� CBControl ��Ķ���Ĵ���������
	//   ������Կռ�Ŀ��ٺ��ͷ��޹ء�
	// ��̬���ٿؼ������Կռ䣬���� PropertyMemCtrl() ��̬����ʵ�ֵģ���
	//   PropMem() ��Ա����Ҳ�Զ����� PropertyMemCtrl()
	// �ͷ���Щ��̬���ٵĿؼ������Կռ䣬�� CBForm ��� EnumChildProcSubClass
	//   ��ʵ��
	//
	// ���� ����Ϳؼ� �����Կռ��д˲�ͬ������ BWndBase �д���Ϳؼ�
	//   ���еķ����У���������ͬ�ģ����� BackColorSet() �С�������Ϊ 
	//   BWndBase ����һ�� STWndProp * ���͵�ָ�� m_pPro���ȿ�ָ�����
	//   ���Կռ䣬Ҳ��ָ��ؼ������Կռ䡣
	// ============================================================


	// ��һ���ؼ��� hWnd�����һ�� �ؼ� �ĸ������� STWndProp �ռ�ĵ�ַ�������ڴ��壩
	// �Դ���Ӧ���ڴ��� CBForm ����ʱ����ഫ�� m_WndProp �ĵ�ַ��Ȼ����ö����
	//   PropMem() ��Ա������Ҳ�ǻ���ĳ�Ա���������
	// �Կؼ�������û�и������Կռ䣬�� bCreate=false ʱ���� NULL��
	//   �� bCreate=true ʱ�¿��ٸ������ԵĿռ䣬���� �¿ռ��ַ
	// �Կؼ��������и������Կռ䣬�������¿����¿ռ䣬��ֱ�ӷ���ԭ��
	//   �ռ�ĵ�ַ
	// �Կؼ������һ�� CBControl ������ֱ�ӻ�øö����Ӧ�ؼ������Կռ�
	//   Ҳ�ɵ��� CBControl ����� PropMem() ��Ա�����������ͬ
	// ԭ���ǹ��� ms_hashCtrls.ItemLong2
	static STWndProp * PropertyMemCtrl(HWND hWndCtrl, bool bCreate=false);


public:
	
	// ======================================================================================
	// ��Ԫ����
	// ======================================================================================
	
	// WinMain ����
	int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, char * lpCmdLine, int nShowCmd );

	// ���ô��ڹ��̣����б�����󣨴��壩���ô˺�����Ϊ���ڹ���
	friend BOOL WINAPI CBForm_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	// ���ô��ڹ��̣����б�����󣨴��壩�е��Ӵ��ڿؼ������ô˺�����Ϊ���ڹ��̣������Ӵ��ڿؼ��������ദ��
	friend BOOL WINAPI CBForm_ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	// ö���Ӵ��ڿؼ������ദ��ȡ�����ദ�������Ӵ��ڿؼ��Ļص�������
	// lParam Ϊ�ؼ���������ľ������0��ʱ����ʾ���ش���ʱ�����ദ��
	// lParam Ϊ 0 ʱ����ʾж�ش���ʱ�Ļָ����ദ��
	friend BOOL CALLBACK EnumChildProcSubClass(HWND hwnd, LPARAM lParam);
	
	// ��Ϣѭ������
	friend void MessageLoop(int iExitStyle/*=0*/);

public:
	// ���캯������������
	// pProperty �Ǳ��洰���ؼ����ԵĽṹ��ռ�ĵ�ַ
	//   ����� CBForm �̳У�Ӧ�� pProperty ָ�� CBForm �����е� m_WndProp ��Ա
	//   ����� CBControl �̳У��ɱ��� pProperty Ϊ�գ�����Ҫ���Կռ�ʱ�������
	//    �Զ���̬���䣻��ͬһ�ؼ���hWnd ��ͬ�ģ���δ�����ͬ�� CBControl ����
	//    ������Զ�����ϴ�Ϊ������Ŀռ䣬�����ϴε��������ݣ�����ÿ�η����¿ռ�
	CBWndBase( HWND hWndToManage = NULL, STWndProp * pProperty = NULL );	
	virtual ~CBWndBase();

	// ��ú����ô��ڵ� ʹ�� ״̬
	void EnabledSet(bool enabledValue) const;
	bool Enabled() const;	
	
	// ��ú����ô��ڵ� ���� ״̬
	void VisibleSet(bool visibleValue) const;	
	bool Visible() const;
	
	// ���غ����ô����Ƿ��й�����
	bool HScrollBar();
	void HScrollBarSet(bool bValue);
	bool VScrollBar();
	void VScrollBarSet(bool bValue);
	
	// ���غ����� �ؼ��Ƿ���հ� Tab ���ƶ�����
	bool TabStop();
	void TabStopSet(bool bValue);
	
	// ���غ�����Group����
	// �ӵ�һ�� Group=true �Ŀؼ���ʼ ����һ�� Group=True �Ŀ�
    //   ��Ϊֹ��֮������пؼ�Ϊһ��
	bool Group();
	void GroupSet(bool bValue);

	// �����ַ�������
	LPTSTR TagString();
	void TagStringSet(LPCTSTR tagString);
	
	// ��������1
	int TagInt();
	void TagIntSet(int iTag);

	// ��������2
	int TagInt2();
	void TagInt2Set(int iTag2);

	// ���� double
	double TagDouble();
	void TagDoubleSet(double dTag);


	// ================================================
	// λ�á���С
	// ================================================

	// ��ú͸ı䴰�ڴ�С��λ�ã��ƶ����ڡ��ı䴰�ڴ�С��
	void Move(int left=0x7FFFFFFF, int top=0x7FFFFFFF, 
		int width=0x7FFFFFFF, int height=0x7FFFFFFF) const;
	int Left() const;
	int Top() const;
	int Width() const;
	int Height() const;
	int ClientWidth() const;
	int ClientHeight() const;
	void LeftSet(int left) const;
	void TopSet(int top) const;
	void WidthSet(int width) const;
	void HeightSet(int height) const;


	

	// ================================================
	// ���
	// ================================================

	// ���غ����� �����ؼ� �������״������ֵ�����޸Ĵ����࣬����ͨ����Ӧ WM_SETCURSOR ʵ�֣�
	//   typeRes Ϊ 0 ʱ������ idResCursor Ϊ Cursor ���͵���Դ ID
	//   Ҳ�������������͵���Դ����ʱ typeRes Ϊ�����ַ������������ʱʹ�ã�
	// ���ô���� MousePointerSet �������ô�������ָ�벻Ӱ���Ӵ��ڿؼ������������Ӵ��ڿؼ�
	//   �Ĺ�꣬Ӧ���ö�Ӧ�ؼ��� MousePointerSet
	long MousePointer();
	void MousePointerSet(EStandardCursor cursor);		
	void MousePointerSet(long idResCursor, LPCTSTR typeRes=0);


	// ���غ����� �����ؼ� �ı���ɫ����Ϊ -1 ��ʾʹ��Ĭ����ɫ��
	// Ҳ���������ý������ؼ�����ɫ����ʹ��XP���6.0�ؼ�ʱ����Ч��
	COLORREF BackColor();
	void BackColorSet(EColorType color);
	void BackColorSet(COLORREF color);

	// ���غ����� �����ؼ� ��ǰ��ɫ������������ı����ı���ɫ��
	// Ҳ���������ý������ؼ�ǰ��ɫ������������ɫ������ʹ��XP���6.0�ؼ�ʱ����Ч��
	COLORREF ForeColor();
	void ForeColorSet(EColorType color);
	void ForeColorSet(COLORREF color);




	// ================================================
	// �ı�
	// ================================================

	// ���ô����ı����������ذ汾��
	void TextSet(LPCTSTR newText) const;
	void TextSet(char valueChar) const;
	void TextSet(unsigned short int valueInt) const;	// TCHAR
	void TextSet(int valueInt) const;
	void TextSet(unsigned int valueInt) const; 
	void TextSet(long valueLong) const;
	void TextSet(unsigned long valueInt) const;
	void TextSet(float valueSng) const;
	void TextSet(double valueDbl) const;
	void TextSet(long double valueDbl) const;
	void TextSet(tstring valueString) const;
	
	// ���ô����ı����������ذ汾��
	void TextAdd(LPCTSTR newText) const;
	void TextAdd(char valueChar) const;
	void TextAdd(unsigned short int valueInt) const;
	void TextAdd(int valueInt) const;
	void TextAdd(unsigned int valueInt) const;
	void TextAdd(long valueLong) const;
	void TextAdd(unsigned long valueInt) const;
	void TextAdd(float valueSng) const;
	void TextAdd(double valueDbl) const;
	void TextAdd(long double valueDbl) const;
	void TextAdd(tstring valueString) const;

	// ��ô����ı��������ַ���
	TCHAR * Text() const;
	// ��ô����ı�ת��Ϊ�� double ����
	double TextVal() const; 


	// ================================================
	// ����
	// ================================================
	
	// ���غ����� ������������������ַ���
	// �ַ����������Զ����١��� HM �Զ�����
	LPTSTR FontName();
	void   FontNameSet(LPCTSTR szFontName);
	void   FontNameSet(tstring stringFontName);

	// ���غ����� ��������Ĵ�С
	float FontSize();
	void  FontSizeSet(float fSize);

	// ���غ����� ���������Ƿ�Ӵ�
	bool FontBold();
	void FontBoldSet(bool value);

	// ���غ����� ���������Ƿ���»���
	bool FontUnderline();
	void FontUnderlineSet(bool value);

	// ���غ����� ���������Ƿ���б
	bool FontItalic();
	void FontItalicSet(bool value);

	// ���غ����� �����������ת�Ƕȣ���λ��1/10 �ȣ�
	float FontRotateDegree();
	void  FontRotateDegreeSet(float fDegree);

	// ���غ����� ����������ַ���
	BYTE FontCharSet();
	void FontCharSetSet(BYTE ucValue);

	// ��õ�ǰ���������µ����ֿ�ȡ��߶�
	// ��ø߶�ʱ������ TextHeight() ��ʡ���ַ��� sText
	int TextWidth(LPCTSTR sText);
	int TextHeight(LPCTSTR sText=NULL);

	// ������ɫ�� ForeColor() �� ForeColorSet()
	


	// ================================================
	// �߿�
	// ================================================

	// ���غ����ô����Ƿ��б߿�
	bool Border();
	void BorderSet(bool bValue);
	
	// ���غ����� �Ƿ��ǶԻ������͵ı߿�
	// A border of a style typically used with dialog boxes. 
	//   A window with this style cannot have a title bar.
	bool BorderFrameDlg();
	void BorderFrameDlgSet(bool bValue);
	
	// ���غ����� �߿���Ա��϶��Ըı䴰�ڴ�С
	// A sizing border. Same as the WS_SIZEBOX style.
	bool BorderFrameThick();
	void BorderFrameThickSet(bool bValue);

	// ���غ����� �Ƿ�Ϊ��͹��еı߿�
	// A border with a raised edge.
	bool BorderRaised();
	void BorderRaisedSet(bool bValue);

	// ���غ����� �Ƿ�Ϊ�а��ݸеı߿�
	// Specifies that a window has a 3D look 
	//   �� that is, a border with a sunken edge.
	bool BorderSunken();
	void BorderSunkenSet(bool bValue);

	// ���غ����� �Ƿ�Ϊ��ʴ�̵ı߿�
	bool BorderEtched();
	void BorderEtchedSet(bool bValue);

	// ���غ����� �Ƿ�Ϊ��̬�߿�
	// Creates a window with a three-dimensional border style
	//   intended to be used for items that do not accept user input.
	bool BorderStatic();
	void BorderStaticSet(bool bValue);

	// ���غ����ô����Ƿ��б�����
	bool BorderTitleBar();
	void BorderTitleBarSet(bool bValue);
	
	// ���غ����� �Ƿ�Ϊ�������ߴ�����ʽ��խ��������
	// A tool window, which is a window intended to be 
	//   used as a floating toolbar. A tool window has a title bar 
	//   that is shorter than a normal title bar, and the window 
	//   title is drawn using a smaller font. A tool window does not 
	//   appear in the task bar or in the window that appears when 
	//   the user presses ALT+TAB.
	bool BorderToolWindow();
	void BorderToolWindowSet(bool bValue);



	// ======== ��ͼ ========

	// ����λͼͼƬ�������ذ汾��
	// ����Ϊλͼʱ��Ϊ֧�����ţ����� WM_PAINT �л��Ƶģ����ǹ���λͼ���
	// ֧�� ����(�����֧��λͼ)��Picture �ؼ���Button �ؼ�����ѡ�򡢸�ѡ��
	void PictureSet(UINT bmpResID);
	void PictureSet(LPCTSTR bmpFile);
	
	// ֱ���Ծ������ͼƬ��
	// picType ΪͼƬ���ͣ�λͼ��ͼ�ꡢ��ꡢenhͼԪ
	// ����Ϊλͼʱ��Ϊ֧�����ţ����� WM_PAINT �л��Ƶģ����ǹ���λͼ���
	// ֧�� ����(�����֧��λͼ)��Picture �ؼ���Button �ؼ�����ѡ�򡢸�ѡ��
	void PictureSet(HANDLE hPic, EImgObjType picType);	
	
	// ���ý�ȡλͼ��һ������ʾ�� �����ؼ� �ϣ�����λͼ��ȫ�����ݶ�����ʾ�� �����ؼ� ��
	// ����ֵ����Ϊ -1��xClip��yClip Ϊ -1 ʱ���Զ���ͼƬ���Ͻǿ�ʼ��ȡ
	//    widthClip��heightClip Ϊ -1 ʱ���Զ���ȡ��ͼƬ���ҡ��±߽�λ��
	// ��֧�������˵�ͼƬ����Ϊλͼ
	void PictureClipSet(int xClip=-1, int yClip=-1, int widthClip=-1, int heightClip=-1);
	
	
	// ��ʾͼƬʱʹ�ã��Ƿ��Զ�����λͼͼƬ����Ӧ�ؼ���С
	bool Stretch();
	void StretchSet( bool stretchVal );


	// PictureSetIcon �ɼ���ͼ�꣬Ҳ�ɼ��ض������
	//   typeRes ��Ϊ0ʱ��ָ���Զ�����Դ�����ͣ�Ϊ0��ʾIcon���ͣ�
	// ֧�� Picture �ؼ���Button �ؼ�����ѡ�򡢸�ѡ�򣨷�Picture�ؼ�������겻���˶���
	// ==== ���ض����������ַ�����=====
	// �� Form1.Control(ID_pic1).PictureSetIcon(TEXT("APPLE.ANI")); 
	//	// ���ض�������ļ�
	// �� Form1.Control(ID_pic1).PictureSetIcon(IDR_MYANI1, TEXT("MYANI"));   
	//	// ����Դ�ļ��м��� "MYANI" ���͵�һ����Դ��ani�ļ����ȱ�����Ϊ����Դ��
	void PictureSetIcon(EStandardIcon iconStd);
	void PictureSetIcon(UINT iconResID, LPCTSTR typeRes=0);
	void PictureSetIcon(LPCTSTR iconFile);
	
	



	// ����ı�
	// x��y ȱʡ�� (0,0) λ�ÿ�ʼ
	// �������� x�����Զ����к����һ��Ҳ���� x ��ʼ�������ı����� \n ��������һ�д� 0 ��ʼ
	// fLineFeed ������Ƿ��Զ����У������´����λ���Զ��ƶ������ı�����һ�п�ͷ
	//   �� fLineFeed=false ���´����λ���Զ��ƶ����������ı������
	// fBkTransparent: ���ֱ����Ƿ�͸��
	// fSingleLine: �Ƿ�ֻ��������ı�����Ϊ false ��֧�ִ�ֱ���룩
	bool PrintText(LPCTSTR sText, int x=-65536, int y=-65536, 
		bool fLineFeed=true, bool fBkTransparent=true, bool fSingleLine=true);
	bool PrintText(tstring stringText, int x=-65536, int y=-65536, 
		bool fLineFeed=true, bool fBkTransparent=true, bool fSingleLine=true);
	

	// ��������ı���ʽ�����ú����� PrintText ����ı�
	// clipX��clipY��clipWidth��clipHeight �����ı������Χ
	//   clipX��clipY ȱʡĬ��Ϊ(0,0)��clipWidth��clipHeight ȱʡĬ��Ϊ���ͻ����߽�
	//   �������� clipX��clipY���� PrintText ʱȱʡ x��y ��������
	// align: �������Χ�е�ˮƽ���뷽ʽ
	// valign: �������Χ�еĴ�ֱ���뷽ʽ
	// fEndEllipsis: �ַ����Ƿ�ɱ�ѹ����ĩβ��� ...
	// fPathEllipsis: �ļ�·���ַ����Ƿ�ɱ�ѹ�����м��� ...
	// fANDPrefix: �Ƿ� & ����»���
	// iTabSpace: Tab �Ʊ����࣬Ϊ 0 ʱ����չ Tab ��
	// bEditControlStyle: ������ı���ؼ�������ʾ�ı���ƽ���ַ���ȵļ������ı�����ͬ��
	//   �����һ�в��ֿɼ�����ʾ���һ��
	bool PrintTextFormat(int clipX=0, int clipY=0, int clipWidth=-1, int clipHeight=-1, 
		EAlign align=eAlignLeft, EVAlign valign=eVAlignVCenter,
		bool fEndEllipsis=false, bool fPathEllipsis=false, bool fANDPrefix=true, 
		bool bEditControlStyle=false, int iTabSpace=8);


	// �ñ�����ɫ���
	void Cls();

	// ˢ��λͼ����ʾ������ PictureSet ����λͼ����Ч��
	// xEdge��yEdge Ϊˮƽ����ֱ����ͼƬ���������Ŀհ�
	//   Ϊ 0 ʱͼƬ�� ���ڻ�ؼ� �������ͻ�������
	// ��ô����ؼ���������ͼƬ������ͼƬ���� true
	//   ��ô����ؼ�û�б�����ͼƬ������ false
	// �����û����ã��û�ֻҪ PictureSet ����
	bool RefreshPicture(HDC hDC, int xEdge=0, int yEdge=0);	



	// ================================================
	// �߼�
	// ================================================

	// ���غ����ÿؼ��Ƿ�͸��
	bool Transparent();
	void TransparentSet(bool bTransparent);
	
	// ���غ����� �����͸���ȣ�0-255��0Ϊ��ȫ͸����255Ϊ��͸����
	//							����Ϊ����ȡ����Ч��
	//            ����δ�����ô���ʽ����-1��ϵͳ��֧�ַ��� -2
	// win2000���Ͽ����ã�winXP���Ͽɷ���
	int Opacity();
	void OpacitySet(int iOpacity);

	// ���غ����� ���塰�ڿա�����ɫ������Ϊ -1 ȡ����Ч��
	// ����-1���޴�Ч��
	// win2000���Ͽ����ã�winXP���Ͽɷ���
	COLORREF TransparencyKey();
	void TransparencyKeySet(COLORREF iTransColor);


	// �Ƿ��϶���������λ�ã����϶��ؼ��������ڴ���
	//   �����б�������Ϊ��=0�����У�=1 ����϶����ƶ����壩
	int TitleBarBehavior();
	void TitleBarBehaviorSet(int iBehav=1);


	// ��ô��ڵ�����������ͨ��ָ��ı������ַ��������ݣ�
	const TCHAR * ClassName() const;	
	
	// �жϴ��ڵ����Ƿ���һ������
	bool IsClassName(LPCTSTR lpTestClassName) const;
	bool IsClassName(tstring stringTestClassName) const;

	// ���ػ����ô��ڷ��
	// ����ʱ���� bOr > 0�� �������з��������
	//         �� bOr < 0���������з����ȡ�� newStyle
	//         �� bOr == 0�������з���Ϊ newStyle
	unsigned long Style();
	void StyleSet(unsigned long newStyle, int bOr=1);
	
	// ���ػ����ô��ڵ���չ���
	// ����ʱ���� bOr > 0�� ����������չ���������
	//         �� bOr < 0������������չ�����ȡ�� newStyleEx
	//         �� bOr == 0����������չ����Ϊ newStyleEx
	unsigned long StyleEx();
	void StyleExSet(unsigned long newStyleEx, int bOr=1);





	// ================================================
	// ����
	// ================================================

	// ˢ�´�����ʾ
	void Refresh();
	
	// ���ý��㵽������
	void SetFocus();
	
	// ���ô��ڻ�ؼ��� Z-˳�򣬼��Ǹ����������ڿؼ������Ǳ��������ڿؼ�������
	// position=0����λ���������ڿؼ�����ǰ�棻���� λ�������
	void ZOrder(int position=0);

	
	// ���и���ճ��
	void Cut();
	void Copy();
	void Paste();


	// ��Ա��������
	// ���㲻�ܽ��ڹ��캯���н��У����� CBControl ��һ�������
	//   SetResID �Ⱥ�󶨲�ͬ�ؼ�ʱ�������ù��캯����Ҫ�����Ա
	void ClearWndBase();
	

protected:	// ����Ϊ�̳���ı�����Ա
	HWND m_hWnd;			// ���ھ��

	TCHAR m_ClassName[128];	// ���ڿؼ�������
	long m_atom;			// ���ڿؼ���� atom �ţ�Ψһ��ʶһ���࣬ʹ�û��� BWndBase �ĳ�Ա
							// CBControl ��̳�ʱ���� SetResID ���Զ��� GetClassName ����
							// CBForm ��̳�ʱ���� CBForm_DlgProc �� WM_INITDIALOG ������

	STWndProp * m_pPro;		// �����ؼ��������Խṹ������ĵ�ַ
							// ����Ķ���ֱ�ӱ����������ݣ��� CBControl �Ķ��󣨴�������Ϊ����ĳ�Ա��
							//   �Ƕ�̬��������̬���ٵġ�һ���ؼ��������ݱ�����һ�� STWndProp �ռ��У�
							//   ���ַ���� ms_hashCtrls.ItemLong2 ���档ÿ�δ���һ�� CBControl �Ķ���
							//   ���� hWnd �� ms_hashCtrls �ҵ��������ݵĵ�ַ���ɱ���Աָ����
							// �� CBForm �Ķ��󣬲��Ƕ�̬�����ģ����������� CBForm ����ĳ�Ա m_WndProp
							//   ֱ�ӱ��棬��Ҳ�ñ���Աָ�������ԺͿؼ�ͳһ����

protected:
	
	// ���һ�� �����ؼ� �ĸ������� STWndProp �ռ�ĵ�ַ
	// �Դ���Ӧ�÷��ش������� m_WndProp �ĵ�ַ
	// �Կؼ�������û�и������Կռ䣬�� bCreate=false ʱ���� NULL��
	//   �� bCreate=true ʱ�¿��ٸ������ԵĿռ䣬���� �¿ռ��ַ
	// �Կؼ��������и������Կռ䣬�������¿����¿ռ䣬��ֱ�ӷ���ԭ��
	//   �ռ�ĵ�ַ
	// �Կؼ������������ڴ�һ�� CBControl ������ֱ�ӻ�øö����Ӧ�ؼ������Կռ�
	//   ��û�� CBControl ���󣬶�ֻ�пؼ��� hWnd��Ӧ���� PropertyMemCtrl() 
	//   ��̬������ÿؼ������Կռ�
	// ԭ���ǹ��� ms_hashCtrls.ItemLong2
	STWndProp * PropMem(bool bCreate=false);

	HFONT GetFontMLF(LOGFONT * lpLf=NULL);	// �����ڵ�ǰ����������Ϣ��ȡ�� lpLf ��ָ��Ľṹ��
											//   ������Ŀǰ�������������
											// �� lpLf Ϊ��ָ�룬ֱ�ӷ���������������ȡ������Ϣ
													
	HFONT SetFontMLF(LOGFONT * lpLf);		// ���� lpLf ��ָ��Ľṹ����һ�����壬�����ô���ʹ�ø������壻
											//   �����������������ľ��
	
};
