//////////////////////////////////////////////////////////////////////
// BForm.h: CBForm ��Ķ���
//
// CBForm �ࣺʵ�ֶԻ���ģ̬����ģ̬�����ڳ��������������塱
//   ʵ�ֶԻ�����ʾ�����ء��¼�����Ȳ����������漰�ؼ�
//
// �����а��� BForm �����ٱ�д WinMain �����������Ա�д main ����
//   main �����޲���������ֵ���� int
//       int main();
// ��ʱ�����е� main() ����ִ�н������������򲻻����
//   ������������������� main() ����ִ�н������������д���
//   ȫ��ж�أ���ģ��� WinMain ������
//
// BForm ������Ϣѭ������������ȫ�ֺ��� DoEvents(); 
// ����ֱ�ӵ��� BForm �ľ�̬��Ա������MousePointerGlobal �� 
//   MousePointerSetGlobal ���ػ����� ȫ���������״
//
// ������ͷ�ļ��򲻱ذ��� BWindows.h��BControl.h��BMenuItem.h��
//   ��Ϊ��ͷ�ļ��Ѿ�����������
//
//
// ֧�֣�
//     ��Ҫ BWindows��BWndBase��BControl��BMenuItem ģ���֧��
//////////////////////////////////////////////////////////////////////


// ==== �÷���========================================================
// �ڶ��屾�����ʱ������������� idResDialog����ʾ�Ի�����Դ ID�����磺
//      CBForm form1(IDD_FORM1);
// ��Ҫ�����������ɾֲ������������彫�ڶ�Ӧ��������ʱ��ж�أ�
//   ��Ӧ�����������Ϊȫ�ֱ���
// ��Ҫ�÷�Ϊ��
//   form1.Show();
//   form1.Control(IDCANCEL).EnabledSet(false);
//   form1.Control(IDC_EDIT1).TextSet("abc");
//   form1.EventAdd(IDOK, eCommandButton_Click, cmdOK_Click);
// void cmdOK_Click()
// {
// 	  MsgBox("OK");
// }
//
//
// ���ټ��÷���
// ��ʱ���� SetAccelerator(���ټ���ԴID) ����һ������ļ��ټ�����
//   ��ȡ�����ټ����ܣ�����Ϊ0����
// �����ڱ�����Ϊǰ̨ʱ���ټ�����Ч����ͬ������в�ͬ���ټ���
//   �ĸ�����Ϊǰ̨����Ӧ����ļ��ټ�Ϊ��Ч��
// ���ټ����¼����������Ͳ˵��������¼�������Ϊͬһ����
//   Menu_Click
// ===================================================================


// ==== ������========================================================
// ���಻�� DialogBoxParam �������������ϵġ�ģ̬���Ի������� Form ��
//   �Ƿ�ģ̬�ģ��� DialogBoxParam �޷�������ټ���
// Ҫ��ʾ��ģ̬���Ի��򣬱���Ὣ�����ɱ������Ĵ���� Enabled ����Ϊ
//   false����ģ̬�Ի���������ٻָ������������д���� Enabled��
// ��������ʹ���໹�������Ѿ���ʾ��ģ̬���Ի����ͬʱ������ʾ��һ��
//   ����ģ̬���Ի��򣬱����Զ���������Ϊ Enabled Ϊ false
//
// ��Ϣѭ������ MessageLoop() ���� WinMain �����⣬���ɱ� DoEvents ����
//   �Լ���ʾ��ģ̬���Ի���ʱ�� ShowWindow ֮�󱻵��ã���ʹ������ʾһ��
//   ��ģ̬���Ի���ʱ���ڶԻ��������Show() �����Ż᷵��
// ===================================================================

#pragma once

#include "BWndBase.h"
#include "BControl.h"
#include "BMenuItem.h"



//////////////////////////////////////////////////////////////////////////
// ȫ�ֺ��� �� WinMain ����
//////////////////////////////////////////////////////////////////////////

// ȫ�� DoEvents ��������CPU���������¼�����������ٷ���
//   ������ h �ļ����κ�ģ�鶼�ɵ���
extern void DoEvents();

// ȫ�� End �������������̵߳����У����� PostQuitMessage(nExitCode)
//   ������ h �ļ����κ�ģ�鶼�ɵ���
extern void End(int nExitCode=0);



// WinMain ������дԭ��˵����ֱ���� BForm.cpp ��д����ʵ��

// ���ô��ڹ��̣����б�����󣨴��壩���ô˺�����Ϊ���ڹ���
static BOOL WINAPI CBForm_DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// ���ô��ڹ��̣����б�����󣨴��壩�е��Ӵ��ڿؼ������ô˺�����Ϊ���ڹ��̣������Ӵ��ڿؼ��������ദ��
static BOOL WINAPI CBForm_ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// ö���Ӵ��ڿؼ������ദ��ȡ�����ദ�������Ӵ��ڿؼ��Ļص�������
// lParam �� 0 ʱ��Ϊ�ؼ���������ľ����ͬʱ��ʾ���ش���ʱ�����ദ��
// lParam Ϊ 0 ʱ����ʾж�ش���ʱ�Ļָ����ദ��
static BOOL CALLBACK EnumChildProcSubClass(HWND hwnd, LPARAM lParam);


// ��Ϣѭ������
// bExitStyle=0ʱ��Ϊ����Ϣѭ��������Ϣ�����޴���ʱ�� return
// bExitStyle>1ʱ��ʵ���� +1 ��� ms_iModalLevel ��ֵ
//   ����ģ̬�Ի�����ʾ�����Ϣѭ����ÿ��ʾһ��ģ̬�Ի����½�һ��
//   �µ� MessageLoop���� ms_iModalLevel<iExitStyle�����޴���ʱ return
// bExitStyle=-1ʱ������ DoEvents()��
//   ��ǰ�߳�����Ϣ��PeekMessage ����0��ʱ�� return
// ���� bExitStyle Ϊ���٣��� GetMessage �յ� 0 ���� return 
//   ���� return ǰ�ٴ� PostQuitMessage(0); �Խ��˳���Ϣ����
//   ��ǰ������ MessageLoop ʹǰ������ MessageLoop �����˳�
static void MessageLoop(int iExitStyle=0);



//////////////////////////////////////////////////////////////////////////
// CBForm ��
//////////////////////////////////////////////////////////////////////////


// ��֪ͨ��Ϣ��WM_COMMAND �� WM_NOTIFY���������Ӵ��ڿؼ����¼�����
// 1. ��֪ͨ��Ϣ���������пؼ��¼���ö��ֵ �� | ��ֵ����Ӧ������λΪ1
// 2. ��������Ϣ���������д����¼����ؼ��¼���ö��ֵ ��û�д˶����Ʊ�־λ
//   (�� enum ECBFormCtrlEventsVoid��enum ECBFormCtrlEventsI ���ж���ö��ֵ)
#define c_CBNotifyEventBase 0x20000000

// �˵�������ϵͳ�˵�������ټ������µ��¼�
// �� m_hashEventNotify �� Key ֵΪ��ֵ�� Item Ϊ���¼��� �¼��������ĵ�ַ
#define c_CBMenuClickEventKey -1


// ======================================================================
// ����¼�������
//   ��������һ��ö��ֵ
//   ����������¼������� EventsGenerator �� EventsGeneratorCtrl 
//   �������ش��뼴�ɣ����������޸�
// ======================================================================

// ������֧�ֵĴ����¼����ؼ��¼���ö��ֵ
//   ��ֻ���� �¼��������޲����޷���ֵ�� �¼���
enum ECBFormCtrlEventsVoid		
{
	// ��֪ͨ��Ϣ�����Ŀؼ��¼���ö��ֵ = ֪ͨ�� | c_CBNotifyEventBase
	//   ��ö��ֵ����Ϊ m_hashEventNotify �ĸ��� Key �ĸ� 2 λ
	//   Key �ĵ���λΪ�ؼ�ID
	eCommandButton_Click = BN_CLICKED | c_CBNotifyEventBase,		// void cmd1_click(); ��ѡ�򡢸�ѡ��ĸı�ѡ�Ҳ�������Ϣ
	eCommandButton_GotFocus = BN_SETFOCUS | c_CBNotifyEventBase,	// void cmd1_GotFocus();
	eCommandButton_LostFocus = BN_KILLFOCUS | c_CBNotifyEventBase,	// void cmd1_LostFocus();
	
	eStatic_Click = STN_CLICKED | c_CBNotifyEventBase,				// void pic1_Click();
	eStatic_DblClick = STN_DBLCLK | c_CBNotifyEventBase,			// void pic1_DblClick();
	eStatic_Disable = STN_DISABLE | c_CBNotifyEventBase,			// void pic1_Disable();
	eStatic_Enable = STN_ENABLE | c_CBNotifyEventBase,				// void pic1_Enable();

	eEdit_Change = EN_CHANGE | c_CBNotifyEventBase,					// void Text1_Change();		ͬ��֧�� Rich Edit
	eEdit_GotFocus = EN_SETFOCUS | c_CBNotifyEventBase,				// void Text1_GotFocus();	ͬ��֧�� Rich Edit
	eEdit_LostFocus = EN_KILLFOCUS | c_CBNotifyEventBase,			// void Text1_LostFocus();	ͬ��֧�� Rich Edit
	eEditRtf_SelChange = EN_SELCHANGE | c_CBNotifyEventBase,		// void Rtf1_SelChange();	��֧�� Rich Edit
	
	eListBox_SelChange = LBN_SELCHANGE | c_CBNotifyEventBase,		// void List1_SelChange(); 
			// �� ListIndex ѡ��ʱ���������¼�����ѡ�б�ʱ���û����¼�ͷ����ͻ�������¼�������ѡ�����ޱ仯��
	eListBox_SelCancel = LBN_SELCANCEL | c_CBNotifyEventBase,		// void List1_SelCancel();	// �û�ȡ��ѡ����¼�
	eListBox_DblClick = LBN_DBLCLK | c_CBNotifyEventBase,			// void List1_DblClick();
	eListBox_GotFocus = LBN_SETFOCUS | c_CBNotifyEventBase,			// void List1_GotFocus();
	eListBox_LostFocus = LBN_KILLFOCUS | c_CBNotifyEventBase,		// void List1_LostFocus();
	
	eComboBox_SelChange = CBN_SELENDOK | c_CBNotifyEventBase,		// void Combo1_SelChange();
	eComboBox_SelOK = CBN_SELENDOK | c_CBNotifyEventBase,			// void Combo1_SelOK();
	eComboBox_TextChange = CBN_EDITCHANGE | c_CBNotifyEventBase,	// void Combo1_TextChange(); �ı��򲿷ַ����仯���¼���CBS_DROPDOWNLIST ������Ͽ�û�д��¼�
	eComboBox_DropDown = CBN_DROPDOWN | c_CBNotifyEventBase,		// void Combo1_DropDown();   �����б��ּ���Ҫ������
	eComboBox_DblClick = CBS_SIMPLE | c_CBNotifyEventBase,			// void Combo1_DblClick();	 ���� CBS_SIMPLE ������Ͽ���Ч


	// ��������Ϣ�������¼���ö��ֵ = WM_XXX
	//   ��ö��ֵ����Ϊ m_hashEventNotify �ĸ��� Key �ĵ� 2 λ
	//   ��ע�ⲻ�Ǹ�2λ����2λΪ0��ʾ�����¼���Ϊ�ؼ�ID(��0)��ʾ�ؼ��¼���
	eForm_Load = WM_INITDIALOG,					// Form1_Load();
												// ���������жԴ���Ĳ���֮ǰ EventAdd ���¼���
												//   �������ȼ��ش�������ô��¼����¼����������ᱻִ��
	eForm_Unload = WM_DESTROY, 					// Form1_UnLoad();
	eForm_Resize = WM_SIZE,						// Form1_Resize();	// �ڴ����С����֮����
	ePaint = WM_PAINT,							// Form1OrCtrl1_Paint();
	eGotFocus = WM_SETFOCUS,					// void Form1OrCtrl1_GotFocus()
	eLostFocus = WM_KILLFOCUS					// void Form1OrCtrl1_LostFocus()
};
#define eCheck_Click		eCommandButton_Click		// CheckBox ��֪ͨ��Ϣͬ CommandButton
#define eCheck_GotFocus		eCommandButton_GotFocus
#define eCheck_LostFocus	eCommandButton_LostFocus
#define eRadio_Click		eCommandButton_Click		// Radio Button ��֪ͨ��Ϣͬ CommandButton
#define eRadio_GotFocus		eCommandButton_GotFocus
#define eRadio_LostFocus	eCommandButton_LostFocus

#define eTextBox_Change		eEdit_Change				// Edit �ؼ�����
#define eTextBox_GotFocus	eEdit_GotFocus	
#define eTextBox_LostFocus	eEdit_LostFocus
#define eTextRTF_SelChange	eEditRtf_SelChange


// ������֧�ֵĴ����¼����ؼ��¼���ö��ֵ
//   ��ֻ���� �¼���������1��int�Ĳ������޷���ֵ�� �¼���
enum ECBFormCtrlEventsI
{
	// ��֪ͨ��Ϣ�����Ŀؼ��¼���ö��ֵ = ֪ͨ�� | c_CBNotifyEventBase
	//   ��ö��ֵ����Ϊ m_hashEventNotify �ĸ��� Key �ĸ� 2 λ
	//   Key �ĵ���λΪ�ؼ�ID


	// ��������Ϣ�������¼���ö��ֵ = WM_XXX
	//   ��ö��ֵ����Ϊ m_hashEventNotify �ĸ��� Key �ĵ� 2 λ
	//   ��ע�ⲻ�Ǹ�2λ����2λΪ0��ʾ�����¼���Ϊ�ؼ�ID(��0)��ʾ�ؼ��¼���
	eForm_ActiDeactivate = WM_ACTIVATE,	// void Form1_ActiDeactivate(int bActiOrDeacti); // bActiOrDeacti=��0Ϊ���屻���=0Ϊʧ��
	eForm_QueryUnload = WM_CLOSE,		// void Form1_QueryUnLoad(int pbCancel);	�� *((int *)pbCancel) = ��0ֵ����ȡ��ж��
	eMenu_Select = WM_MENUSELECT,		// void Menu_Select(int ptrCBMenuItem);	// δָ��˵���ʱ���ϴ�ָ�������ƿ�����ptrCBMenuItem Ϊ0
	eMenu_InitPopup = WM_INITMENUPOPUP,	// void Menu_InitPopup(int wParam)
};


// ������֧�ֵĴ����¼����ؼ��¼���ö��ֵ
//   ��ֻ���� �¼���������2��int�Ĳ������޷���ֵ�� �¼���
enum ECBFormCtrlEventsII
{
	// ��֪ͨ��Ϣ�����Ŀؼ��¼���ö��ֵ = ֪ͨ�� | c_CBNotifyEventBase
	//   ��ö��ֵ����Ϊ m_hashEventNotify �ĸ��� Key �ĸ� 2 λ
	//   Key �ĵ���λΪ�ؼ�ID


	// ��������Ϣ�������¼���ö��ֵ = WM_XXX
	//   ��ö��ֵ����Ϊ m_hashEventNotify �ĸ��� Key �ĵ� 2 λ
	//   ��ע�ⲻ�Ǹ�2λ����2λΪ0��ʾ�����¼���Ϊ�ؼ�ID(��0)��ʾ�ؼ��¼���
	eKeyPress = WM_CHAR					// void Form1OrCtrl1_KeyPress(int keyAscii, int pbCancel);  // �� *((int *)pbCancel) = ��0ֵ����ȡ��
};

// ������֧�ֵĴ����¼����ؼ��¼���ö��ֵ
//   ��ֻ���� �¼���������3��int�Ĳ������޷���ֵ�� �¼���
enum ECBFormCtrlEventsIII
{
	
	// ���⣺
	// �˵��ͼ��ټ������£�����ϵͳ�˵������£��¼������ĵ�ַ������ m_hashEventNotify 
	//   �� Key Ϊ c_CBMenuClickEventKey (-1) ������
	eMenu_Click = 0x70000000,					// void Menu_Click(int menuID, int bIsFromAcce, int bIsFromSysMenu);


	// ��֪ͨ��Ϣ�����Ŀؼ��¼���ö��ֵ = ֪ͨ�� | c_CBNotifyEventBase
	//   ��ö��ֵ����Ϊ m_hashEventNotify �ĸ��� Key �ĸ� 2 λ
	//   Key �ĵ���λΪ�ؼ�ID




	// ��������Ϣ�������¼���ö��ֵ = WM_XXX
	//   ��ö��ֵ����Ϊ m_hashEventNotify �ĸ��� Key �ĵ� 2 λ
	//   ��ע�ⲻ�Ǹ�2λ����2λΪ0��ʾ�����¼���Ϊ�ؼ�ID(��0)��ʾ�ؼ��¼���
	eKeyDown = WM_KEYDOWN,			// void Form1OrCtrl1_KeyDown(int keyCode, int shift, int pbCancel);   // �� *((int *)pbCancel) = ��0ֵ����ȡ��
	eKeyUp = WM_KEYUP,				// void Form1OrCtrl1_KeyUp(int keyCode, int shift, int pbCancel);     // �� *((int *)pbCancel) = ��0ֵ����ȡ��

};

// ������֧�ֵĴ����¼����ؼ��¼���ö��ֵ
//   ��ֻ���� �¼���������4��int�Ĳ������޷���ֵ�� �¼���
enum ECBFormCtrlEventsIIII
{

	// ��֪ͨ��Ϣ�����Ŀؼ��¼���ö��ֵ = ֪ͨ�� | c_CBNotifyEventBase
	//   ��ö��ֵ����Ϊ m_hashEventNotify �ĸ��� Key �ĸ� 2 λ
	//   Key �ĵ���λΪ�ؼ�ID



	// ��������Ϣ�������¼���ö��ֵ = WM_XXX
	//   ��ö��ֵ����Ϊ m_hashEventNotify �ĸ��� Key �ĵ� 2 λ
	//   ��ע�ⲻ�Ǹ�2λ����2λΪ0��ʾ�����¼���Ϊ�ؼ�ID(��0)��ʾ�ؼ��¼���

	eMouseDown = WM_LBUTTONDOWN,	// void Form1OrCtrl1_MouseDown(int button, int shift, int x, int y);
									//   button =1,2,4�ֱ��ʾ������ҡ��м������£�
									//   shift=1,2,4 �ֱ��ʾͬʱ Shift��Ctrl��Alt ��������
									//   x,y ��ʾ����ڿؼ��е����꣨�ؼ�����ϵ��
									// ���ҡ��м������µ��¼�ö��ֵ��ͳһ�� WM_LBUTTONDOWN�������ֱ���3��ֵ

	eMouseUp = WM_LBUTTONUP,		// void Form1OrCtrl1_MouseUp(int button, int shift, int x, int y);
									//   button =1,2,4�ֱ��ʾ������ҡ��м������£�
									//   shift=1,2,4 �ֱ��ʾͬʱ Shift��Ctrl��Alt ��������
									//   x,y ��ʾ����ڿؼ��е����꣨�ؼ�����ϵ��
									// ���ҡ��м���̧����¼�ö��ֵ��ͳһ�� WM_LBUTTONUP�������ֱ���3��ֵ

	eDblClick = WM_LBUTTONDBLCLK,	// void Form1OrCtrl1_DblClick(int button, int shift, int x, int y);
									//   button =1,2,4�ֱ��ʾ������ҡ��м������£�
									//   shift=1,2,4 �ֱ��ʾͬʱ Shift��Ctrl��Alt ��������
									//   x,y ��ʾ����ڿؼ��е����꣨�ؼ�����ϵ��
									// ���ҡ��м���˫�����¼�ö��ֵ��ͳһ�� WM_LBUTTONDBLCLK�������ֱ���3��ֵ

	eMouseMove = WM_MOUSEMOVE,		// void Form1OrCtrl1_MouseMove(int button, int shift, int x, int y);
									//   button =1,2,4�ֱ��ʾ������ҡ��м������£�
									//   shift=1,2,4 �ֱ��ʾͬʱ Shift��Ctrl��Alt ��������
									//   x,y ��ʾ����ڿؼ��е����꣨�ؼ�����ϵ��
	
	eFilesDrop = WM_DROPFILES		// void Form1OrCtrl1_eFilesDrop(int ptrArrFiles, int count, int x, int y);
									// �轫 ptrArrFiles ת������Ϊ (TCHAR **)ptrArrFiles��Ȼ���� [1]��[count]
									//   ���ÿ���ļ����ļ�������ȫ·������x,y Ϊ�Ϸ��ļ�ʱ�����������λ��

}; 


// �����¼��������ĺ���ָ������
typedef void (*ONEventVoid)();					// �޷���ֵ�޲����� �¼��������ĵ�ַ
typedef void (*ONEventI)(int);					// �޷���ֵ�� 1 ��int�Ͳ����� �¼��������ĵ�ַ
typedef void (*ONEventII)(int,int);				// �޷���ֵ�� 2 ��int�Ͳ����� �¼��������ĵ�ַ
typedef void (*ONEventIII)(int,int,int);		// �޷���ֵ�� 3 ��int�Ͳ����� �¼��������ĵ�ַ
typedef void (*ONEventIIII)(int,int,int,int);	// �޷���ֵ�� 4 ��int�Ͳ����� �¼��������ĵ�ַ

class CBForm : public CBWndBase		// ����һ�����壨�Ի��򣩵Ķ���
{
private:

	// ======================================================================================
	// ˽�о�̬��Ա�ͳ�Ա����
	// ======================================================================================

	// ��̬��ϣ�����б�������ã���
	//   ��������ͨ������������ġ�����������д������Ϣ
	// Key=hWnd, Item = (unsigned int)�������ַ��this, 
	// ItemLong = ���ټ������ItemLong2 = ��ģ̬�Ի���Ӱ��ı�����Enabled״̬��
	//   0 = ��Ӱ�죻
	//   >0 = �ۼ���ָ�Ϊ Enabled �����
	//   ��������ԭΪ Disabled������ʾģ̬�Ի���ʱ��ֵ�Ա�����Ϊ0��
	// ����ʾһ��ģ̬�Ի���ʱ��
	//   ������ĳ����ĿǰΪ Disabled �Ҵ�ֵΪ0����ά�ָô��ڵĴ�ֵ���䣻
	//   ��������ĳ����ĿǰΪ Enabled�����߸ô��ڴ�ֵ >0�����Ὣ�ô��ڵĴ�ֵ +1
	// ������һ��ģ̬�Ի���ʱ��
	//   ��ĳ���ڴ�ֵΪ0�������κβ��������򽫴�ֵ-1����-1��Ϊ0����ָ�Ϊ Enabled ״̬
	// �� DialogBoxParam �� CreateDialogParam �����У����ý������ݵ� DlgProc �� 
	//   WM_INITDIALOG ��Ϣ�� lParam ����Ϊ�������ַ�� this
	//   �� DlgProc �����д��� WM_INITDIALOG ��Ϣʱ�����ϣ�������һ����Ŀ
	static CBHashLK ms_hashWnd;

	// ��̬��Ա�����б�������ã���
	//   ģ̬�Ի��� �Ĳ��
	// �˱���ֵ��0ʱ����ʾ���� ms_iModalLevel �����㣩ģ̬�Ի�������ʾ
	// ÿ��ʾһ��ģ̬�Ի��򣬴˱���ֵ+1��ÿ����һ��ģ̬�Ի��򣬴˱���ֵ-1
	static int ms_iModalLevel;

	// ��̬��Ա�����б�������ã���
	//   ��ǰλ��ǰ̨�Ĵ���� hWnd�������ڽ����л���WM_ACTIVATE��ʱ���ô�ֵ
	static HWND ms_hWndActiForm;

	// ��̬��Ա�����б�������ã���
	//   ���д����У�Ŀǰʹ�õļ��ټ����
	// һ���̵߳ļ��ټ�ֻ����һ�ף��ҷ���һ�����ڣ�Ϊʹ�����ͬ�������ʹ�ò�ͬ��
	//   ���ټ���ÿ�������Ӧ�ı�����󶼿ɼ�¼һ�׼��ټ����� ���ټ���� ��¼�� 
	//   ms_hashWnd.ItemLong��
	// ���ټ�Ҫ���͵���Ŀ�괰��Ϊ ms_hWndActiForm�������ڽ����л���WM_ACTIVATE��
	//   ʱ���������� ms_hWndActiForm �� ms_hAccelCurrUsed
	// ����Ϣѭ������ MessageLoop �У�ֻ������ ms_hWndActiForm �� 
	//   ms_hAccelCurrUsed ���ɷ����ټ���Ϣ������Ϊ 0 ʱ��ʾ�޼��ټ���
	static HACCEL ms_hAccelCurrUsed;  

public:
	
	// ======================================================================================
	// ���о�̬��Ա�ͳ�Ա����
	// ======================================================================================

	// ��̬��Ա���������б�������ã���
	// ��ñ���������Ĵ���ĸ���
	static int FormsCount();
	
	// ��̬��Ա���������б�������ã���
	// ��ñ����������һ������ı������ĵ�ַ
	// �����ô˵�ַ -> ���ñ�������Է�����������
	// ���磺CBForm::FormsObj(1)->Menu(1,0).TextSet(TEXT("OK"));
	static CBForm * FormsObj(int index);


public:

	// ======================================================================================
	// ��Ԫ����
	// ======================================================================================

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

	// CBControl ���һЩ����
	friend CBForm * CBControl::ParentFormPtr() const;
	friend HWND CBControl::hWndParentForm() const;
	friend unsigned long CBControl::PtrWndProcDef() const;

public:

	// ======================================================================================
	// �๫�г�Ա
	// ======================================================================================
	bool KeyPreview;	// �Ƿ������ɴ��崦�����пؼ��ļ��̰�����Ϣ


public:

	// ======================================================================================
	// �๫�г�Ա����
	// ======================================================================================

	// ���캯����idResDialog Ϊ�Ի������Դid������������� idResDialog
	CBForm(unsigned short int idResDialog=0);	
	// ��������
	~CBForm();

	// ��ñ�����Ŀǰ������Ĵ���ľ��
	HWND hWnd();

	// ��ú����ô��������˵��ľ��������Ϊ 0 ��ʾȡ���˵����޲˵�����
	HMENU hMenu();
	void hMenuSet( HMENU hMenuNew );

	// ��ú����ñ��������ü��ټ��ľ��������Ϊ 0 ��ʾȡ�����ټ�
	HACCEL hAccel();
	void hAccelSet( HACCEL hAccelNew );

	// ��ʾ�Ի���
	//   modal=0 ��ģ̬��ʹ������Ϣѭ�����������������أ�
	//   modal=1 ģ̬���½�����һ�� MessageLoop(>1) ����Ϣѭ����������ֱ��
	//           ģ̬���屻���ػ�ж�غ���ܷ��أ�
	//   hwndOwner �Ի����������ڵľ����NULL�����������ڣ����Ǹ����ڣ�
	bool Show(int modal=0, HWND hwndOwner=NULL);	
	
	// ���ضԻ���
	long Hide();

	// ���ضԻ��򵫲�����ʾ�������Ի�����Դ�в��ܰ��� WS_VISIBLE ��ʽ�������ǻ���ʾ ��
	// ĳЩ��Ա�����Ĺ�������Ҫ�Ի��򱻼��غ������Ч���� SetAccelerator ��Ա������
	//   ��������Щ����ʱ������δ���أ���Щ�������Զ����ñ������ȼ��ش���
	// ����سɹ������ش��ھ����ʧ�ܷ��� 0
	HWND Load(HWND hwndOwner=NULL, bool fRaiseErrIfFail=true);

	// �رնԻ�����Ի����� WM_CLOSE ��Ϣ��
	void UnLoad() const;				


	// ���úͷ�����С��(=1)�����(=2)����ԭ״̬(=0)
	int WindowState();
	void WindowStateSet(int iState);



	// ���ñ����ڽ�������ټ� idResAcce
	// ��ȡ�����ټ�����������Ϊ 0 ����
	// Ҳ��ͨ�� hAccelSet ֱ���Ծ������
	void SetAccelerator(unsigned short int idResAcce);

	// �������ñ����ڵĲ˵�
	// ��ȡ���˵�����������Ϊ 0 ����
	// Ҳ��ͨ�� hMenuSet ֱ���Ծ������
	void SetMenuMain(unsigned short idResMenu);

	// ����һ���ؼ���CBControl ����ʵ�ʷ��ذ󶨾���ؼ���� m_Control����
	//   ֮��ɶԸÿؼ����в��������� CBControl ������Է�����
	CBControl Control(unsigned short int idResControl, bool fRaiseErrIfFail=true);	

	// ����һ���˵��CBMenuItem ����ʵ�ʷ��ذ󶨾���˵����� m_MenuItem����
	//   ֮��ɶԸò˵�����в��������� CBMenuItem ������Է�����
	// ����ԴIDָ���˵�������ذ治��ָ��Ϊ �����Ӳ˵� �Ĳ˵��������ֲ˵�������ԴID��
	// ��λ��ָ���˵������ذ棺λ�þ���1��ʼ��0��ʾ���ô˼������7������
	//   pos1>0 ��ʾ�������˵�����λ�ã�
	//   pos1<0 ��ʾϵͳ�˵�����ʱ pos2 Ϊϵͳ�˵�һ���˵���λ��
	// ���磺Menu(0, 0) ��ô��嶥���˵������Menu(-1, 0) ���ϵͳ�˵����
	//   Menu(1, 0)  ��ʾ���ļ�������2��0Ϊ���൫����д��; Menu(-1, 1) ��ʾ����ԭ��
	// Form1.Menu(0, 0).CountSubItems() ��ö���˵� �˵���������2��0Ϊ���൫����д��
	// Form1.Menu(-1, 0).CountSubItems() ���ϵͳ�˵� �˵���������2��0Ϊ���൫����д��
	// Ҫָ��Ϊһ�� �����Ӳ˵� �Ĳ˵�������á���λ��ָ�������ذ桱
	CBMenuItem Menu( UINT idResMenuItem );
	CBMenuItem Menu( int pos1, int pos2, 
		int pos3=0, int pos4=0, 
		int pos5=0, int pos6=0, int pos7=0);
	CBMenuItem Menu(ESysMenu idSysMenu);	
	
	// �ָ�ϵͳ�˵�
	void MenuSysRestore() const;

	// �� (x,y) ��λ�õ���һ����ݲ˵�
	// idResMenu Ϊ�˵���Դ ID�����������������ĵ� 0 ���Ӳ˵�
	// bAllowRightClick ��ʾ�Ƿ������Ҽ�����ѡ��˵��������ֻ���������ѡ��
	BOOL PopupMenu(UINT idResMenu, int x, int y, bool bAllowRightClick=true);

	// ���ô���ͼ��
	void IconSet(EStandardIcon icon);
	void IconSet(unsigned short iconRes);





	// �Ƿ��ô���ΪԲ�Ǿ�����ۣ�0=��Բ����ۣ�>0ΪԲ����ۣ�ֵ��ʾԲ�ǻ��ȣ�
	//   >0 �� <65536 ʱ��Բ�ǻ��ȵĿ�ȡ��߶ȶ�Ϊ��ֵ��
	//   >65536ʱ����2λΪԲ�ǻ��ȸ߶ȣ���2λΪԲ�ǻ��ȿ��									 								
	long RoundRectForm();
	void RoundRectFormSet(long newRoundCorner);
	
	// >0 ʱ��ʾҪ�� WM_PAINT �¼����Զ����ƴ���߿򣬴�Ϊ�߿��ȣ�֧��Բ�Ǿ��α߿�
	int EdgeWidth();
	void EdgeWidthSet(int newEdgeWidth);

	// EdgeWidth >0 ʱ��ʾҪ�� WM_PAINT �¼����Զ����ƴ���߿����ɫ��֧��Բ�Ǿ��α߿�
	COLORREF EdgeColor();
	void EdgeColorSet(COLORREF newEdgeColor);

	// �������ƶ�����Ļ�м�
	// �� width��height ��>0�������������ô���� Width��Height
	void MoveToScreenCenter(int width=-1, int height=-1, bool bHorizontalCenter=true, bool bVerticalCenter=true);


	// �����ޱ߿��壩�Ƿ��������϶��������ܸı䴰���С��������>0��ֵΪ�ɸı��С�ı߿�Χ��
	int BorderAutoResizable();
	void BorderAutoResizableSet(int iNewValue=1);


	

	// =================== �¼��������� ===================

	// ����һ������Ļ��Ӵ��ڿؼ����¼���������ذ汾��
	// ptrFunHandler Ϊһ���¼��������ĵ�ַ
	// idResControl ������
	//   ����Ǵ����¼���idResControl ����Ӧ��Ϊ0
	//   ����ǿؼ��¼���idResControl ����Ӧ��Ϊ �ؼ�����ԴID
	//   ����ǲ˵�������ϵͳ�˵��������ټ��¼�����2������Ϊ eMenu_Click�������� idResControl ����
	// ʹ�ö�����ذ汾���ɽ�������ϵͳ������ͣ����磺
	//   ���� ECBFormCtrlEventsVoid ���͵��¼��������� ONEventVoid ���͵ĺ���
	//   ���� ECBFormCtrlEventsII ���͵��¼��������� ONEventII ���͵ĺ���
	// ���� EventAdd ������ǰ���ش��壬Ҳ�����Զ����ش���
	// ����¼�����ĳЩ֪ͨ��Ϣ�������¼���Ӧ����Ӧ�ؼ���Ϊ���� Notify ��ʽ��
	//   �ڵ��� EventAdd ʱ������֪ͨ��Ϣ�¼������������Զ�Ϊ�ؼ�����Ϊ���� Notify ��ʽ
	//   �������ȼ��ش��壬֮��� EventAdd �����вſ��Զ����ã��細�廹δ���أ��޷��Զ�����
	void EventAdd( unsigned short int idResControl, 
				   ECBFormCtrlEventsVoid eventType, 
				   ONEventVoid ptrFunHandler
		);
	void EventAdd( unsigned short int idResControl, 
				   ECBFormCtrlEventsI eventType, 
				   ONEventI ptrFunHandler
		);
	void EventAdd( unsigned short int idResControl, 
				   ECBFormCtrlEventsII eventType,
				   ONEventII ptrFunHandler
		);	
	void EventAdd( unsigned short int idResControl, 
				   ECBFormCtrlEventsIII eventType,
				   ONEventIII ptrFunHandler
		);	
	void EventAdd( unsigned short int idResControl, 
				   ECBFormCtrlEventsIIII eventType,
				   ONEventIIII ptrFunHandler
		);	

	// �������һ�������¼��Ŀؼ�ID�������¼����˵��¼�����Ӱ���ֵ
	int IDRaisingEvent();

private:

	// ======================================================================================
	// ��˽�г�Ա
	// ======================================================================================

	// m_hWnd���Ի��򣨴��壩�ľ����ʹ�û��� BWndBase �ĳ�Ա����ֵ���� CBForm_DlgProc ��
	//   WM_INITDIALOG ��Ϣ�Ĵ����б�����
	// TCHAR m_ClassName[128]�����ڿؼ���������ʹ�û��� BWndBase �ĳ�Ա
	// long m_atom�����ڿؼ���� atom �ţ�Ψһ��ʶһ���࣬ʹ�û��� BWndBase �ĳ�Ա
	//				������ֵ���� CBForm_DlgProc �� WM_INITDIALOG ���Զ�������
	// STWndProp * m_pPro�������ؼ��������Խṹ������ĵ�ַ��ʹ�û��� BWndBase �ĳ�Ա

	unsigned short int mResDlgID;	// �Ի��򣨴��壩����Դid����ֵ�����ڹ��캯���и���
	STWndProp m_WndProp;			// ��������

	bool m_ModalShown;				// �Ƿ���ģ̬�Ի�����ʾ�ı�־��Ϊ true ��ʾ����������ģ̬�Ի�����ʾ

	long m_RoundRect;				// �Ƿ��ô���ΪԲ�Ǿ�����ۣ�0=��Բ����ۣ�>0ΪԲ����ۣ�ֵ��ʾԲ�ǻ��ȣ�
									// >0 �� <65536 ʱ��Բ�ǻ��ȵĿ�ȡ��߶ȶ�Ϊ��ֵ��
									// >65536ʱ����2λΪԲ�ǻ��ȸ߶ȣ���2λΪԲ�ǻ��ȿ��									 								
	HRGN m_hRgnRoundRect;			// �細����Բ�Ǿ��Σ�Բ�Ǿ�������ľ��
	

	int m_EdgeWidth;				// >0 ʱ��ʾҪ�� WM_PAINT �¼����Զ����ƴ���߿򣬴�Ϊ�߿��ȣ�֧��Բ�Ǿ��α߿�
	COLORREF m_EdgeColor;			// m_EdgeWidth >0 ʱ��ʾҪ�� WM_PAINT �¼����Զ����ƴ���߿����ɫ��֧��Բ�Ǿ��α߿�

	int m_iBorderAutoResizable;		// �����ޱ߿��壩�Ƿ��������϶��������ܸı䴰���С��������>0��ֵΪ�ɸı��С�ı߿�Χ��

	int m_idRaisingEvent;			// ���һ�������¼��Ŀؼ�ID�������¼����˵��¼�����Ӱ���ֵ

	CBControl m_Control;			// ���ڷ��ʺͿ��ƴ����ϵ�һ���ؼ������Զ�̬�󶨵���ͬ�ؼ�
	CBMenuItem m_MenuItem;			// ���ڷ��ʺͿ��ƴ����ϵ�һ���˵�����Զ�̬�󶨵���ͬ�˵������ϵͳ�˵��
	CBMenuItem m_MenuItemSel;		// ���� Menu_Select ʱ��һ����ѡ�˵�����Զ�̬�󶨵���ͬ�˵���
	
	CBHashLK m_hashMenuIDs;			// ��ϣ��key = �˵������Դid��data = �ò˵��ĸ��˵��ľ��

	// ��֪ͨ��Ϣ��WM_COMMAND �� WM_NOTIFY�������� �Ӵ��ڿؼ��¼��� �¼���������ַ�б�
	//   key = WM_COMMAND ��Ϣ�� wParam����2λΪ֪ͨ�룬��2λΪ�ؼ�ID����
	//    �� = WM_NOTIFY ��Ϣ�� NMHDR �е� .idCtrl �� .code ��ת��Ϊ2�ֽڣ���ƴ�ӣ�
	//         ʹ key �ĸ�2λΪ .code����2λΪ idCtrl 
	//    �� = -1( �� c_CBMenuClickEventKey )����ʾ �˵�������ϵͳ�˵�������ټ�������
	//          ���¼�����Ӧ�� key �� Item Ϊ�����¼��� �¼��������ĵ�ַ
	//   Item = �û��¼��������ĵ�ַ���������¼�Ҫ���õ��¼��������ĵ�ַ
	//   ItemLong = 0 �� 4 �ֱ��ʾ �¼���������Ҫ0�� �� 4�� int�͵Ĳ���
	CBHashLK m_hashEventNotify;	


	// �Դ�����Ϣ����֪ͨ��Ϣ�����������巢�͵� WM_XXX �����Ӵ��ڿؼ�����
	//   �� WM_XXX�������� �����¼����� �Ӵ��ڿؼ����¼��� �¼���������ַ�б�
	//  key = �� 2 λΪ���͵��������Ϣ��WM_XXX������ 2 λΪ0
	//   �� = �� 2 λΪ���͵��Ӵ��ڿؼ�����Ϣ��WM_XXX������ 2 λΪ�ؼ� ID
	//  ��ע�� m_hashEventNotify �ĸߡ���λ���䲻ͬ�������õ�λ��ʾ��Ϣ��ʹ�����¼�
	//     ֱ�ӿ������յ�����Ϣ��Ϊ key ����ϣ���в��ң������ؽ���Ϣ <<16 ���ܻ�� key
	//  Item = �¼���������ַ
	//  ItemLong = 0 �� 4 �ֱ��ʾ�¼���������Ҫ0�� �� 4�� int�͵Ĳ���
	CBHashLK m_hashEventMessage;

private:

	// ======================================================================================
	// ��˽�г�Ա����
	// ======================================================================================

	// ����һ������Ļ��Ӵ��ڿؼ����¼���EventAdd�Ķ�����ذ汾�Ĺ��ò�����
	void EventAddPrivate(unsigned short int idResControl, 
		long eventType, 
		long ptrFunHandler,
		int nParamsIntCount		// 0 �� 4 �ֱ��ʾ�¼���������Ҫ0�� �� 4�� int�͵Ĳ���
		);
	
	// �����¼��ĳ��򣺴�������Ϣ���ɴ��壨�Ի��򣩹��� CBForm_DlgProc ����
	long EventsGenerator(UINT uMsg, WPARAM wParam, LPARAM lParam);

	// �����¼��ĳ��򣺴���ؼ���Ϣ���ɿؼ������ദ���Ŀؼ����ڹ���
	//   CBForm_ControlProc ����
	long EventsGeneratorCtrl(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


	// ��ģ̬�Ի������ػ򱻹ر�ʱ���ָ��������ڵ� Enabled
	void RestoreModalWinEnabled();


	// ��ȡһ���˵��µ����в˵���� id������ id ����ֱ�����˵������
	//   ��Ӧ��ϵ���浽��ϣ�� m_hashMenuIDs
	// ���������ݹ����ʹ���Ӳ˵��µĲ˵���Ҳ������
	// bIsTop==true ʱ�����������ϣ�� m_hashMenuIDs��Ӧ���ڵ�һ�ε��� 
	//   ʱ�Ž��˲�����Ϊ true���ݹ����ʱӦ���˲�����Ϊ false
	void ConstructMenuIDItems(HMENU hMenuParent, bool bIsTop=false);	

	// ���ڱ����ٺ�����ô˺����ͷ���Դ
	void ClearResource();

};

