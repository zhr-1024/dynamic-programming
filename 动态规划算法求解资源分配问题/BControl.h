//////////////////////////////////////////////////////////////////////
// BControl.h: CBControl ��Ķ���
// ʵ�ֶԻ����е�һ���ؼ��ĸ��ֹ���
// ���������ȫ�� HM ����̬������ڴ�
//
// ֧�֣�
//     ��Ҫ BWindows��BWndBase��BForm��BMenuItem ģ���֧��
//////////////////////////////////////////////////////////////////////

#pragma once

#include "BWndBase.h"
// BControl.cpp ������ #include "BForm.h"���� BControl.cpp
//   �е� CBControl ���ʵ���У����õ� CBForm ��

class CBForm;	// �������


class CBControl : public CBWndBase
{
public:
	// ���캯����idResControl Ϊ�ؼ�����Դid
	//   Ҳ��ʹ�����ذ汾�� ���캯�������ؼ��ľ��
	CBControl(unsigned short int idResControl=0);		
	CBControl(HWND hWndCtrl);		
	
	// ��������
	~CBControl();

	// ����ʹ�ñ���������һ���ؼ�����δ�ڹ��캯�������ã�Ҳ���ñ�����������
	// idResControl Ϊ�ؼ��� ��ԴID��Ҳ��ʹ�����غ��������ؼ��ľ��
	// ����ͨ�� ��ԴID ��ʽ��֮ǰ��������˴��壬��Ϊ���ڼ����� EnumChildProcSubClass��
	//   �� CBWndBase::ms_hashCtrlResIDs ��ϣ��������˿ؼ� ID ��Ϣ
	// �ɹ������Ӵ��ڿؼ������ʧ�ܷ���0
	HWND SetResID(unsigned short int idResControl=0);	
	HWND SetResID(HWND hWndCtrl=NULL);	
	

	// Ϊ֧��ͼƬ��ť����д EnabledSet
	void EnabledSet(bool enabledValue);	



	// ��ÿؼ��ı��������صĲ����ַ���������ת��Ϊ������
	// retSuccess Ϊһ��ָ�룬ָ�����ݱ�ʾ�����Ƿ�ִ�гɹ�
	// ���� CBControl ���� TextInt��
	// Text��TextVal �̳� CBWndBase ����
	int TextInt(BOOL * retSuccess=0);


	// ======== Static ��ؼ����� ========
	bool BackStyleTransparent();
	void BackStyleTransparentSet(bool bTransparent);

	// ����һ�� Static �ؼ�ΪͼƬ��ť��
	//    ��ť��СΪ�ؼ� Width��Height������ť״̬��λͼ���Ϊһ�Ŵ�λͼ�����λͼ��ԴIDΪ bmpCombResID
	// bmpCombResID=0 ʱ��ʹ�� PictureSet() ���õ�λͼ
	// btnX, btnY, btnWidth, btnHeight ΪͼƬ��ť��λ�á���С���� >=0 ���Զ������ؼ���СΪ��ֵ����4������ֻΪ���ñ�����ʱ
	//   �Զ����ÿؼ�λ�á���С��
	// iStateStyle = 1ʱ��ʹ����̬��ť������һ�ΰ��¡��ٵ���һ��̧�𣻿��� ValueChecked() ����䰴��/̧�� ״̬
	void PicButtonSet(EPicButtonType style=epbNone, UINT bmpCombResID=0, 
		int btnWidth=-1, int btnHeight=-1, int btnX=-1, int btnY=-1, 
		int iStateStyle = 0);

	// ����ͼƬ��ť��״̬��0=���棻1=������2=���£�3=��ɫ
	// iSetOrReleaseCapture���Ƿ�ͬʱ SetCapture (=1) �� ReleaseCapture(=-1) ���� (=0)
	// �� iSetOrReleaseCapture ��0��������ζ����� SetCapture �� ReleaseCapture
	// �����������ÿؼ������״̬��Ҫ���� Checked ״̬����ʹ�� ValueCheckedSet()
	void PicButtonStateSet(int iState, int iSetOrReleaseCapture=0);
	int PicButtonState();

	// ======== Edit��Rich Edit ��ؼ����� ========
	
	// ����ѡ������ʼλ�ã���һ���ַ�λ��Ϊ0��
	// ��������� pLineIdx ��DWORD�����ĵ�ַ�������ɲ�������ѡ��
	//   ��ʼλ�õ��кţ���1�б��Ϊ0����
	// ������ Edit��Rich Edit��Combo ���ı��򲿷֡�List �ؼ�
	// pLineIdx �� ComboBox��List �ؼ� ��Ч
	int SelStart(int *pLineIdx=NULL);

	// ����ѡ������
	// ������ Edit��Rich Edit��Combo ���ı��򲿷֡�List �ؼ�
	int SelLength();

	// ѡ��һ���ı�����һ���ַ�λ��Ϊ0��
	//   ��������Ϊ 0��-1 ʱȫѡ����һ������Ϊ-1ʱȡ��ѡ��
	// ������ Edit��Rich Edit��Combo ���ı��򲿷֡�List �ؼ�
	// ���� List �ؼ�ʱ���ؼ�����Ϊ��ѡ���ѡ��/��ѡ���������Ŀ
	//   selLength>0 ѡ����Ŀ��selLength<0 ȡ��ѡ����Ŀ
	//   ��Ŀ��Ŵ� 1 ��ʼ��selStart==0,selLength==-1 ʱȫѡ
	void SelSet(int selStart=0, int selLength=-1);		
	
	// �滻ѡ���ı���bCanUndo ��ʾ�滻�����ɷ񱻳���
	void SelTextSet(LPCTSTR stringRepl, bool bCanUndo=true);	
	void SelTextSet(tstring stringRepl, bool bCanUndo=true);	

	// �����ı�����֧�� Rich Edit��
	// rgStart��rgLength ��ʾ������Χ��Ĭ�������������ı���Χ������
	// bCaseSensitive==true ʱ���ִ�Сд��bMatchWholeWord==false ʱ�����ִ�Сд
	// bAutoSelFound==true ʱ�������Զ��ڿؼ���ѡ���ҵ����ı�
	// ���ص�һ��ƥ����ı���ʼλ�ã�λ�ô�0��ʼ�������� -1
	int FindText(LPTSTR stringFind, 
				 int rgStart=0, 
				 int rgLength=-1, 
				 bool bCaseSensitive=false, 
				 bool bMatchWholeWord=false, 
				 bool bAutoSelFound=true);
	
	// ���� Edit �ؼ���ͼƬЧ�����
	// ��Ҫһ�� ͼƬ��ؼ���Static�ؼ�����Ϊ��߿����� Edit �ؼ�����ı߿�
	// �����ڶԻ������ʱ�����������н� Edit �ؼ��ġ�Border������ȥ��
	// idPicBorder ΪͼƬ��ؼ���Static�ؼ�������ԴID
	// idBMPBorder ΪͼƬ��ؼ���Static�ؼ����еı���ͼƬ��ԴID
	// x��y��width��height Ϊ����ͼƬ��ؼ�������λ�á���С
	// xOffset Ϊ Edit �ؼ����ͼƬ��ؼ���ˮƽƫ��λ��
	//   Edit �ؼ��Ŀ�Ƚ�������Ϊ width - 2*xOffset
	//   Edit �ؼ��ĸ߶Ƚ�������Ϊ�ʺϿؼ��������壨���� szFontName��
	//     fFontSize ���ã�Ĭ��Ϊ�����塱��10.5������һ�����ָ߶�
	// �� bOnlyMoveSize=true ֻ�ڷſؼ�λ�ã��������ظ�����Ч��
	//   ��ʱ���� idBMPBorder��fFontSize��x��y��width��height
	void EditSetApperance(unsigned short idPicBorder,  unsigned short idBMPBorder,  
					 int x, int y, int width, int height, 
					 LPTSTR szFontName=NULL, float fFontSize=10.5, int xOffset=4, bool bOnlyMoveSize=false);

	// ======== ��ť��ؼ����� ========

	// ���غ����õ�ѡ��ѡ��ť�Ƿ񱻹�ѡ�ˣ�0=δѡ��1=��ѡ��2=��̬
	// ��Ҳ������ Static �ؼ������ġ�ͼƬ��ť��
	unsigned int ValueChecked();			
	void ValueCheckedSet( UINT uCheck );	


	// ======== �б����Ͽ�ListView ��ؼ����� ========

	// ���һ����Ŀ��������ӵ���Ŀ��ţ���1��ʼ���������� 0
	// index<=0 ʱ����ĩβ��ӣ�������ָ���� index λ����ӣ����б����Ͽ���߲����Զ�����
	// iImage��iTagLong��iIndent �������� ListView �ؼ���Ч
	//   iImage Ϊ�� image list �еĴ�ͼ���Сͼ��ı�ţ��� 1 ��ʼ��0 ��ʾ�ݲ����ô���
	//   iIndent Ϊ��Ŀ��������ͼ��Ŀ�ȣ��� =1 Ϊ����һ��ͼ��Ŀ�ȣ�=-&H80000000 ���ݲ����ô���
	// ��������Ŀ�������ţ�>=1����0��ʾ����
	int AddItem(LPTSTR szText, int index = -1, int iImage = 0, int iTagLong = 0, int iIndent = 0x80000000) const;	
	int AddItem(tstring stringText, int index = -1, int iImage = 0, int iTagLong = 0, int iIndent = 0x80000000) const;	

	// ɾ��һ����Ŀ����Ŵ�1��ʼ������ɾ������б�����Ŀ����������0
	int RemoveItem(int index) const;

	// ���ع�����Ŀ����������<0��ֵ
	int ListCount() const;

	// ���ص�ǰѡ�����Ŀ��ţ���Ŵ�1��ʼ����������0
	// ���Զ�ѡ�б��ʹ�ã��򷵻ص��Ǿ��н������Ŀ���
	//   ������Ŀ��û��ѡ��ʱ������1����ʾ��1����Ŀ�н��㣩
	int ListIndex() const;

	// ѡ��һ����Ŀ����Ŀ��Ŵ�1��ʼ
	// �ú����Զ�ѡ�б��ʹ����Ч
	void ListIndexSet(int index) const;

	// ��ȡ������ һ����Ŀ�����ݣ�index ��1��ʼ
	//   ��index<0ʱ��� ListIndex() ���ı���
	// indexSub �������� ListView �ؼ���Ч
	// �� ListView �ؼ���subItemIndex Ϊ 1 �ľ��� ListItem.Text ����
	//   �ڶ��е� subItemIndex Ϊ 2��
	// ��˿����� .ItemText(row, col) ֱ�ӻ�ȡ������ Set ���ã��ı���row��col ���Ǵ� 1 ��ʼ��
	// �����ı���ListViewItemText��ʱ���Զ����ٺ��� HM �Զ������ڴ�ռ�
	LPTSTR ItemText(int index=-1, int indexSub=0) const;
	void ItemTextSet(int index, LPTSTR szNewText=NULL, int indexSub=0) const;
	void ItemTextSet(int index, tstring stringNewText=NULL, int indexSub=0) const;
	LPTSTR List(int index=-1, int indexSub=0) const;			// ͬ ItemText()

	// ��ȡ������ �б���и���Ŀ�ĸ����������ݣ�index ��1��ʼ
	int ItemData(int index) const;
	void ItemDataSet(int index, int itemData);

	// ��ȡ������ ��ѡ�б��һ����Ŀ�Ƿ�ѡ�е�״̬��index ��1��ʼ
	bool ItemSelected(int index) const;
	void ItemSelectedSet(int index, bool bSel) const;
	
	// ȫѡ(iSelStyle=1)����ѡ(iSelStyle=-1)��ȡ��ѡ��(iSelStyle=0)
	//  ListBox �� ListView �ؼ��е���Ŀ
	void ItemsSelDo(int iSelStyle=1);	

	// ���ض�ѡ�б�����ѡ��Ŀ��
	int ListSelCount() const;

	// �� List��ListView �е�ѡ������������ı�������������
	void ItemsCopyToClipboard(bool bOnlySel=true, LPCTSTR szSpliter=TEXT("\t"));

	// ���غ������б��е�һ���ɼ���������ţ��� 1 ��ʼ��
	int ListTopIndex();
	void ListTopIndexSet(int idxTop);


	// ���һ���б��������ѡ����Ŀ�������ţ�����һ�� int ������
	//   ����Ŀ�����Ŵ� 1 ��ʼ
	// �����±�� 1 ��ʼ���ɱ������Զ���������ռ�
	// �������������׵�ַ��û��ѡ���������� 0
	// ����Ԫ�ظ������ص����� pSelCount ��ָ�ռ䣬pSelCount Ϊ0ʱ������
	//   ���� ListSelCount ���ѡ���Ԫ�ظ���
	// �Ե�ѡ�б��������ֻ��һ��Ԫ��
	int * ListSelItems(int *pSelCount=0) const;

	// ����б����������
	void ListClear() const;

	// ��ȡ�������б���߶�
	int ListItemsHeight() const;
	void ListItemsHeightSet(int newHeight);
	
	// ��ͼ�б�������µ�һ�У�iAlign=0,1,2 �ֱ��ʾ���ҡ��ж���
	// index ��1��ʼ��ţ�ָ��Ҫ�����λ�ã�Ĭ�������һ������
	// �ɹ������������ţ���1��ʼ����ʧ�ܷ���0
	int ListViewAddColumn(LPTSTR szColText, int iWidth = 60, int iAlign = 0, int iSubItemIndex = 0, int iImageIdx = -1, int iIndex = 0x7FFFFFFF);
	int ListViewAddColumn(tstring stringColText, int iWidth = 60, int iAlign = 0, int iSubItemIndex = 0, int iImageIdx = -1, int iIndex = 0x7FFFFFFF);

	// ���� ListView ��������������ϸ������ͼ����Ч��
	int ListViewColumnsCount();

	// ���ء���һ�� Item����������
	// idxStart ���ĸ���ʼ���ң�����������0��ʾ�������м����ҵ�һ����
	// bFindAll=true ʱ����������������ԣ����򰴺��������Ϲ��ɵ��������в���
	// �ҵ����������ţ���1��ʼ����û�ҵ����� 0
	//-------------------------------------------------------------------------------
	// �ô˺����ɷ���ر������б�ѡ��Ŀ���磺
	// i = ...ListViewNextItemIdx(0, false, true);  // ��û����һ����ѡ�е���Ŀ������ 0
	// While(i)
	// {
	//	  ����� i ����Ŀ
	//    // �����һ����ѡ��Ŀ�������� -> i
	//    i = ...ListViewNextItemIdx(i, false, true)  // ��û����һ����ѡ�е���Ŀ������ 0
	//  }
	//-------------------------------------------------------------------------------
	int ListViewNextItemIdx(int idxStart=0, bool bFindAll=true, bool bFindSelected=true, 
		bool bFindCut=false, bool bFindDropHilited=false, bool bFindFocused=false, 
		bool bFindAbove=false, bool bFindBelow=false, bool bFindLeft=false, bool bFindRight=false) const;

	// ���ػ����� �Ƿ�����ѡ����ϸ������ͼ��Ч����LVS_EX_FULLROWSELECT
	bool ListViewFullRowSelect();
	void ListViewFullRowSelectSet(bool blNewValue);

	// ���ػ����� �Ƿ��������ߣ���ϸ������ͼ��Ч����LVS_EX_GRIDLINES
	bool ListViewGridLines();
	void ListViewGridLinesSet(bool blNewValue);

	// ======== ProgressBar ��ؼ����� ========
	int Value();
	void ValueSet(int iNewValue);

	int Max();
	void MaxSet(int iNewValue);

	int Min();
	void MinSet(int iNewValue);



	// ======== �߼�ͨ�ù��� ========
	
	// ����Ӵ��ڿؼ��Ĵ��ھ��
	HWND hWnd() const;				
	
	// �������������Ĵ��ھ��
	HWND hWndParentForm() const;		

	// ���ػ����ø����ڵľ��
	//  ���粻�������ؼ��ڣ����ֵ�� hWndParentForm ��ͬ��
	HWND Parent();
	HWND ParentSet(HWND hWndParent);	// �ɹ�����֮ǰ�����ڵľ����ʧ�ܷ��� NULL

	// ����һ��������� CBForm ����ĵ�ַָ������ͨ���ؼ����ʸ�����
	// ���磺Form1.Control(ID_cmd1).ParentFormPtr()->BackColorSet(...);
	CBForm * ParentFormPtr() const;		

	// ����Ӵ��ڿؼ���Ĭ�ϴ��ڳ���ĵ�ַ��עʵ�ʴ˵�ַ�ĺ������ܲ���ʹ�ã����ѱ����໯��
	unsigned long PtrWndProcDef() const;			
	
private:
	// HWND m_hWnd���Ӵ��ڿؼ��ľ����ʹ�û��� BWndBase �ĳ�Ա����ֵ�� SetResID �����б�����
	// TCHAR m_ClassName[128]�����ڿؼ���������ʹ�û��� BWndBase �ĳ�Ա
	// long m_atom�����ڿؼ���� atom �ţ�Ψһ��ʶһ���࣬ʹ�û��� BWndBase �ĳ�Ա
	//				������ֵ���� SetResID ���Զ�������
	// STWndProp * m_pPro�������ؼ��������Խṹ������ĵ�ַ��ʹ�û��� BWndBase �ĳ�Ա

	unsigned short int m_ResCtrlID;	// �ؼ�����Դid����ֵ�� SetResID �����б�����
};