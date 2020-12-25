//////////////////////////////////////////////////////////////////////
// BMenuItem.h: CBMenuItem ��Ķ��壬���ڲ���һ���˵���¼����⣩
// ϵͳ�˵�����ͨ�˵��Ĵ�������ͬ���� CBForm ��� Menu �����غ���
//
// ������ϲ˵������������ ��ϣ��ָ��Ϊ m_ptrHashMenuIDs����ʹ�ñ�ģ��
//   ����˵�ʱ��ͬһ��������в˵���� ID ��Ҫ���ֲ�ͬ����Ҫ��λ�ڲ�ͬ
//   �˵��е���ͬ ID �Ĳ˵�����ڣ�����ֻ�е�һ���˵���Ч
//
// ֧�֣���Ҫ BWindows ģ���֧��
//////////////////////////////////////////////////////////////////////

#pragma once

#include "BWindows.h"

class CBMenuItem							// һ���˵���Ĵ������
{
private:
	static const int mc_MaxMenuTextLen;		// �˵�������ı�����

public:
	// ���캯��
	CBMenuItem(HMENU hMenuParent=NULL, UINT idResMenuItem=0, HWND hWndParent=NULL, CBHashLK * ptrHashMenuIDs=NULL);	
	// ��������
	~CBMenuItem();
	
	// ͨ�� ��ԴID ����ʹ�ñ���������һ���˵���
	// �� hMenuParent Ϊ0����ʾ������������ϵͳ�˵��ġ����˵��
	//  �����������Ӳ˵����Ϊ GetSystemMenu���������Ӳ˵��ĵ�һ���ǡ���ԭ����
	//   �� hMenuParent Ϊ0�������� idResMenuItem
	// hWndParent Ϊ�˵��������ڵĸ�����
	// ptrHashMenuIDs Ϊ�˵������� Form ����CBForm�ࣩ��ά���Ĳ˵� ID �Ĺ�ϣ��ĵ�ַ��
	//   ������ɾ�˵�ʱ���´˹�ϣ��
	void SetFromResID(HMENU hMenuParent, UINT idResMenuItem, HWND hWndParent, CBHashLK *ptrHashMenuIDs );
	
	// ͨ�� �˵�λ�� ����ʹ�ñ���������һ���˵���
	// ��һ���˵���λ��Ϊ1��ע����API��ͬ��
	// �� hMenuParent Ϊ0����ʾ������������ϵͳ�˵��ġ����˵��
	//  �����������Ӳ˵����Ϊ GetSystemMenu���������Ӳ˵��ĵ�һ���ǡ���ԭ����
	//   �� hMenuParent Ϊ0�������� pos
	// hWndParent Ϊ�˵��������ڵĸ�����
	// ptrHashMenuIDs Ϊ�˵������� Form ����CBForm�ࣩ��ά���Ĳ˵� ID �Ĺ�ϣ��ĵ�ַ��
	//   ������ɾ�˵�ʱ���´˹�ϣ��
	// ptrHashObjs Ϊ�˵������� Form ����CBForm�ࣩ��ά����λͼ����ꡢͼ��ȶ����
	//   �����ϣ��ĵ�ַ�����ڼ��ز˵����λͼ����Դʱ�������������
	void SetFromPos(HMENU hMenuParent, UINT pos, HWND hWndParent, CBHashLK *ptrHashMenuIDs );

	// ����ֱ�����˵��ľ��
	HMENU hMenuParent() const;

	// ���ر��˵������ԴID
	// ���ͨ�� �˵�λ�� ���õĲ˵��Ҳ���ô˺��������ԴID
	// ����˵�������ԴID�����ǵ����Ӳ˵��Ĳ˵������ 0xFFFFFFFF
	UINT IDRes() const;

	// ��ñ��˵���λ�� m_hMenuParent �˵��е�λ�ã���һ��λ��Ϊ1��ע��API��0��ʼ��ͬ��
	// ��ͨ�� �˵���ԴID ���õĲ˵��Ҳ���ô˺������λ�ã�ʧ�ܷ��� 0
	UINT Position();

	// ɾ�����˵�������˵��������Ӳ˵�������ɾ���Ӳ˵����Ӳ˵��ɱ�
	//   �ظ����ã����������Ƚ��Ӳ˵�������Ʊ��棨���� hSubMenu ������
	BOOL Remove();

	// �ڱ��˵���ͬһ�˵���������һ���²˵����ָ���
	//   newMenuItemText Ϊ�˵��ı���Ϊ 0 ʱ���һ���ָ��߲����� bPopupSub
	//   bPopupSub Ϊ false ʱ��ʾ���һ������˵��uIDNewItem Ϊ�²˵��� ID
	//   bPopupSub Ϊ true ʱ��ʾ���һ���Ӳ˵���uIDNewItem Ϊ�Ӳ˵���Դ ID
	BOOL Append(LPCTSTR newMenuItemText, UINT uIDNewItem=0, bool bPopupSub=false);
	BOOL Append(tstring stringNewMenuItemText, UINT uIDNewItem=0, bool bPopupSub=false);
	
	// �����˵������һ���Ӳ˵��������Ӳ˵���������һ���²˵����ָ���
	//   �����˵�������Ӳ˵������ô˷�����Ч
	//   newMenuItemText Ϊ�˵��ı���Ϊ 0 ʱ���һ���ָ��߲����� bPopupSub
	//   bPopupSub Ϊ false ʱ��ʾ���һ������˵��uIDNewItem Ϊ�²˵��� ID
	//   bPopupSub Ϊ true ʱ��ʾ���һ���Ӳ˵���uIDNewItem Ϊ�Ӳ˵���Դ ID
	BOOL AppendSubItem(LPCTSTR newMenuItemText, UINT uIDNewItem=0, bool bPopupSub=false);
	BOOL AppendSubItem(tstring stringNewMenuItemText, UINT uIDNewItem=0, bool bPopupSub=false);

	// �ڱ��˵���֮ǰ��ͬһ�˵��У�������һ���²˵����ָ���
	//   newMenuItemText Ϊ�˵��ı���Ϊ 0 ʱ���һ���ָ��߲����� bPopupSub
	//   bPopupSub Ϊ false ʱ��ʾ���һ������˵��uIDNewItem Ϊ�²˵��� ID
	//   bPopupSub Ϊ true ʱ��ʾ���һ���Ӳ˵���uIDNewItem Ϊ�Ӳ˵���Դ ID
	BOOL Insert(LPCTSTR newMenuItemText, UINT uIDNewItem=0, bool bPopupSub=false);
	BOOL Insert(tstring stringNewMenuItemText, UINT uIDNewItem=0, bool bPopupSub=false);

	// ���غ����øò˵���� �ı���������Ϊ�ָ��ߣ���ȡ��Ϊ��λͼ��ʽ��ģʽ��
	// ����Ƿָ��� �� λͼ��ʽ�Ĳ˵������ ""������ newText ����Ϊ 0 ��ʾ�ָ���
	LPTSTR Text();
	void TextSet(LPCTSTR newText);
	void TextSet(tstring stringNewText);

	// ���øò˵�����λͼ��ʽ��ʾ
	// �� idResBmp ���������ذ���Զ� LoadBitmap ���Զ�������غ��λͼ���
	//   �ڴ���ж��ʱ�Զ��ͷŴ˾������ʹ�� hBmp �����ذ汾�����಻���Զ��ͷ�
	void BitmapSet(HBITMAP hBmp);
	void BitmapSet(UINT idResBmp);

	// ���÷�ѡ�С�ѡ��״̬��λͼ
	BOOL SetCheckBitmaps(UINT idResBmpUnChecked, UINT idResBmpChecked);
	BOOL SetCheckBitmaps(EOEMBmp bmpUnChecked, EOEMBmp bmpChecked);

	// ���غ����øò˵���� ʹ��
	bool Enabled();	
	void EnabledSet( bool enabled=true );	

	// ���غ����øò˵���� Checked ״̬���Թ���Բ�㣩
	bool Checked();						
	void CheckedSet(bool checked=true,	// bRadio=true ʱ�������Դ˲���ֵ
					bool bRadio=false,	// bRadio=false ʱΪ�Թ��� bRadio=true ʱΪԲ��
					UINT itemFrom=0,	// bRadio=true ʱ����Ҫ���ò˵�����ķ�Χ��itemFrom��itemTo
					UINT itemTo=0,
					bool fFromToByPosition=false	// �Ƿ� ��λ��ָ�� itemFrom��itemTo������ itemFrom��itemTo �ǲ˵������Դ ID
					);
	
	// ���غ�����һ���˵����Ƿ�Ϊ��Բ�㡱�Ĺ�ѡ��ǣ�true����
    //   ����false���ǡ��Թ����Ĺ�ѡ���
	bool RadioCheck();
	void RadioCheckSet(bool bValue);

	// ���غ����øò˵���ĸ���״̬
	bool Hilited();	
	void HilitedSet();	

	// ����һ���˵����ϵĲ˵����硰�ļ��������༭������ pos �ʼ�ĺ����˵�
    //   ����ƶ����˵������Ҳ��Ҷ���
	bool RightJustify();
	void RightJustifySet(bool bValue);

	// ���غ�����һ���˵��������Ϊtrueʱ���Ӵ˲˵��ʼ�ĺ����˵���
	//  ����һ�������С��У��Բ˵������� һ���µ�"����"�У��������˵���
	//  �Ӳ˵����ݲ˵���
	// bWithLine ��ʾ�����Ƿ������ߣ����˵��������У�����Դ˲���
	bool BreakMenu(); 
	void BreakMenuSet(bool bBreak, bool bWithLine=true);

	// ���غ����ñ��˵����������Ӳ˵���Ĭ����λ�ã�λ�ô�1��ʼ
	//   0��ʾ��Ĭ������˵����������Ӳ˵�����ʹ������2��������
	// bGoIntoPopups=true ʱ����Ĭ�������һ���˵���������һ���˵��м���
	//   ����Ĭ�������һ����Ĭ����Ƿ��ص�ǰ�˵���Ĭ����
	// bUseDisabled=true ʱ����Ĭ������û�һ� Ҳ���ظ�����򲻷���
	UINT DefaultItemPos(bool bGoIntoPopups = false, bool bUseDisabled = true);
	void DefaultItemPosSet(UINT pos);

	// ���غ�����һ���˵����Ƿ�Ϊ���ҵ�����Ķ�˳��
	bool RightToLeft();
	void RightToLeftSet(bool bValue);

	// ���غ�����һ���˵����Ƿ�Ϊ �Ի�˵���
	bool OwnerDraw();
	void OwnerDrawSet(bool bValue);

	// ���غ����øò˵���ĸ������� dwItemData
	unsigned long Tag();
	void TagSet(unsigned long ulNewValue);

	// ���ظò˵����Ƿ�Ϊһ���ָ���
	bool IsSeparator();

	// ���ò˵�������һ���Ӳ˵��������Ӳ˵����������ֵ��Ϊ0��
	//   ���������Ӳ˵�������0
	HMENU hSubMenu();
	
	// ���ز˵����λ�ã���������ϵ������ڲ˵����Ͻ�λ�ã�
	long LeftRelative();
	long TopRelative();
	// ���ز˵���Ĵ�С
	long Width();
	long Height();
	
	// ���ظò˵������������Ӳ˵��Ĳ˵�������
	//  �����˵����������Ӳ˵�����ʹ�����º�����
	int CountSubItems();

private:
	// ��ò˵� hMenu �У���ԴID Ϊ idResMenuItem �Ĳ˵����λ��
	// ����һ���˵���λ��Ϊ0����ʧ�ܷ��� 0xFFFFFFFF
	UINT GetMenuPositionFromID(HMENU hMenu, UINT idResMenuItem);

	// ��ȡ������һ�� fType ���ԵĹ��ú���
	bool GetfType(UINT fTypeValue);
	void SetfType(UINT fTypeValue, bool bAddOrDelValue);

private:
	HMENU m_hMenuParent;		// ������˵����ֱ�����˵����
								// ������Ϊ0���� m_idMenuItemOrPos >0 ʱ����ʾ���������������塰����˵�������������Ӳ˵����Ϊ GetMenu���������Ӳ˵��ĵ�һ���ǡ��ļ��������� hSubMenu ��ô��嶥��˵����
								// ������Ϊ0���� m_idMenuItemOrPos ==0 ʱ����ʾ������������ϵͳ�˵��ġ����˵�������������Ӳ˵����Ϊ GetSystemMenu���������Ӳ˵��ĵ�һ���ǡ���ԭ�������� hSubMenu ���ϵͳ�˵����
	UINT m_idMenuItemOrPos;		// ������˵�����Դ ID �� λ�ã�����ĵ�һ���˵���λ��Ϊ0����APIһ�£���
	UINT m_fByPosition;			// Ϊ MF_BYCOMMAND ʱ m_idMenuItemOrPos Ϊ��ԴID��Ϊ MF_BYPOSITION ʱ m_idMenuItemOrPos Ϊλ��
	HWND m_hWndParent;			// �˵��������ڵĸ�����
	CBHashLK * m_ptrHashMenuIDs;// �˵������� Form ����CBForm�ࣩ��ά���Ĳ˵� ID �Ĺ�ϣ��ĵ�ַ��������ɾ�˵�ʱ���´˹�ϣ��
};



