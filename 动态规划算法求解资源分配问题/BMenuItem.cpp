//////////////////////////////////////////////////////////////////////
// BMenuItem.cpp: CBMenuItem ���ʵ�֣����ڲ���һ���˵���¼����⣩
//
//////////////////////////////////////////////////////////////////////

#include "BMenuItem.h"

// ������ֵ
const int CBMenuItem::mc_MaxMenuTextLen = 1024;		// �˵�������ı�����


CBMenuItem::CBMenuItem( HMENU hMenuParent/*=NULL*/, 
					    UINT idResMenuItem/*=0*/, 
						HWND hWndParent/*=NULL*/, 
						CBHashLK *ptrHashMenuIDs/*=NULL*/ )
{
	m_hMenuParent = NULL;
	m_idMenuItemOrPos = 0;
	m_fByPosition = MF_BYCOMMAND;
	m_hWndParent = NULL;
	m_ptrHashMenuIDs = NULL;
	SetFromResID(hMenuParent, idResMenuItem, hWndParent, ptrHashMenuIDs);
}

CBMenuItem::~CBMenuItem()
{
	
}

void CBMenuItem::SetFromResID( HMENU hMenuParent, UINT idResMenuItem, HWND hWndParent, CBHashLK *ptrHashMenuIDs )
{
	m_hMenuParent = hMenuParent;
	m_idMenuItemOrPos = idResMenuItem;
	m_fByPosition = MF_BYCOMMAND;
	m_hWndParent = hWndParent;
	m_ptrHashMenuIDs = ptrHashMenuIDs; 
}

void CBMenuItem::SetFromPos( HMENU hMenuParent, UINT pos, HWND hWndParent, CBHashLK *ptrHashMenuIDs )
{
	m_hMenuParent = hMenuParent;
	m_idMenuItemOrPos = pos-1;		// ת��Ϊλ�ô�0��ʼ����
	m_fByPosition = MF_BYPOSITION;
	m_hWndParent = hWndParent;
	m_ptrHashMenuIDs = ptrHashMenuIDs; 
}

HMENU CBMenuItem::hMenuParent() const
{ 
	return m_hMenuParent;
}

UINT CBMenuItem::IDRes() const
{
	if (MF_BYPOSITION == m_fByPosition)
	{
		// ���� �˵�λ�� ��ʽ���õĹ���˵���� API ���������Դ ID
		return GetMenuItemID(m_hMenuParent, m_idMenuItemOrPos);
	}
	else
		// ���� �˵���ԴID ��ʽ���õĹ���˵��ֱ�ӷ�����Դ ID
		return m_idMenuItemOrPos;
}


UINT CBMenuItem::Position()
{
	if (MF_BYPOSITION == m_fByPosition)
	{
		// ���� �˵�λ�� ��ʽ���õĹ���˵��ֱ�ӷ���λ��
		return m_idMenuItemOrPos+1;
	}
	else
	{
		// ���� �˵���ԴID ��ʽ���õĹ���˵���� GetMenuPositionFromID ���λ��
		UINT r=GetMenuPositionFromID(m_hMenuParent, m_idMenuItemOrPos);
		if (r==0xFFFFFFFF) return 0; else return r+1;	// ת��Ϊ��1��ʼ
	}
}


BOOL CBMenuItem::Remove()
{
	BOOL ret;
	ret = RemoveMenu(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition);
	if (ret)
		m_ptrHashMenuIDs->Remove(this->IDRes(), false);	// ά����ϣ��
	return ret;
}


BOOL CBMenuItem::Append( LPCTSTR newMenuItemText, UINT uIDNewItem/*=0*/, bool bPopupSub/*=false*/ )
{
	BOOL ret;
	// �ڱ��˵����ͬһ�˵�������������
	if (newMenuItemText)
	{
		if (bPopupSub)
		{
			// ����Ӳ˵�
			ret = AppendMenu(m_hMenuParent, MF_POPUP, 
				(UINT)LoadMenu(pApp->hInstance, MAKEINTRESOURCE(uIDNewItem)), newMenuItemText); 
		}
		else
		{
			// �������˵���
			ret = AppendMenu(m_hMenuParent, MF_STRING, uIDNewItem, newMenuItemText);
			m_ptrHashMenuIDs->Add((int)m_hMenuParent, uIDNewItem, 0, 0, 0, 0, 0, false);	// ά����ϣ��
		}
	}
	else
	{
		// newMenuItemText == 0�����һ���ָ���
		ret = AppendMenu(m_hMenuParent, MF_SEPARATOR, uIDNewItem, NULL);
		m_ptrHashMenuIDs->Add((int)m_hMenuParent, uIDNewItem, 0, 0, 0, 0, 0, false);
	}

	// ����Ƕ���˵����޸�����ۣ��Զ��ػ�˵��������� m_hWndParent ����������Ч��
	if (m_hWndParent)
		if (GetMenu(m_hWndParent) == m_hMenuParent) DrawMenuBar(m_hWndParent);

	return ret;
}

BOOL CBMenuItem::Append( tstring stringNewMenuItemText, UINT uIDNewItem/*=0*/, bool bPopupSub/*=false*/ )
{
	return Append(stringNewMenuItemText.c_str(), uIDNewItem, bPopupSub);
}


BOOL CBMenuItem::AppendSubItem( LPCTSTR newMenuItemText, UINT uIDNewItem/*=0*/, bool bPopupSub/*=false*/ )
{
	// �����˵��������Ӳ˵������Ӳ˵�������������
	BOOL ret;
	HMENU hMenuParent;
	hMenuParent = hSubMenu();		// ���˵��������Ӳ˵��ľ��
	if (hMenuParent == 0) return 0;	// ���˵�������Ӳ˵�

	if (newMenuItemText)
	{
		if (bPopupSub)
		{
			// ����Ӳ˵�
			ret = AppendMenu(hMenuParent, MF_POPUP, 
				(UINT)LoadMenu(pApp->hInstance, MAKEINTRESOURCE(uIDNewItem)), newMenuItemText); 
		}
		else
		{
			// �������˵���
			ret = AppendMenu(hMenuParent, MF_STRING, uIDNewItem, newMenuItemText);
			m_ptrHashMenuIDs->Add((int)hMenuParent, uIDNewItem, 0, 0, 0, 0, 0, false);
		}
	}
	else
	{
		// newMenuItemText == 0�����һ���ָ���
		ret = AppendMenu(hMenuParent, MF_SEPARATOR, uIDNewItem, NULL);
		m_ptrHashMenuIDs->Add((int)hMenuParent, uIDNewItem, 0, 0, 0, 0, 0, false);
	}

	// ����Ƕ���˵����޸�����ۣ��Զ��ػ�˵��������� m_hWndParent ����������Ч��
	if (m_hWndParent)
		if (GetMenu(m_hWndParent) == hMenuParent) DrawMenuBar(m_hWndParent);

	return ret;
}

BOOL CBMenuItem::AppendSubItem( tstring stringNewMenuItemText, UINT uIDNewItem/*=0*/, bool bPopupSub/*=false*/ )
{
	return AppendSubItem(stringNewMenuItemText.c_str(),uIDNewItem,bPopupSub);
}


BOOL CBMenuItem::Insert( LPCTSTR newMenuItemText, UINT uIDNewItem/*=0*/, bool bPopupSub/*=false*/ )
{
	BOOL ret;
	// �ڱ��˵���֮ǰ��ͬһ�˵�����������
	if (newMenuItemText)
	{
		if (bPopupSub)
		{
			// �����Ӳ˵�
			ret = InsertMenu(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition | MF_POPUP, 
				(UINT)LoadMenu(pApp->hInstance, MAKEINTRESOURCE(uIDNewItem)), newMenuItemText); 
		}
		else
		{
			// ��������˵���
			ret = InsertMenu(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition | MF_STRING, uIDNewItem, newMenuItemText);
			m_ptrHashMenuIDs->Add((int)m_hMenuParent, uIDNewItem, 0, 0, 0, 0, 0, false);
		}
	}
	else
	{
		// newMenuItemText == 0������һ���ָ���
		ret = InsertMenu(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition | MF_SEPARATOR, uIDNewItem, NULL);
		m_ptrHashMenuIDs->Add((int)m_hMenuParent, uIDNewItem, 0, 0, 0, 0, 0, false);
	}
	
	// ����Ƕ���˵����޸�����ۣ��Զ��ػ�˵��������� m_hWndParent ����������Ч��
	if (m_hWndParent)
		if (GetMenu(m_hWndParent) == m_hMenuParent) DrawMenuBar(m_hWndParent);
		
	return ret;	
}

BOOL CBMenuItem::Insert( tstring stringNewMenuItemText, UINT uIDNewItem/*=0*/, bool bPopupSub/*=false*/ )
{
	return Insert(stringNewMenuItemText.c_str(), uIDNewItem, bPopupSub);
}



LPTSTR CBMenuItem::Text()
{
	MENUITEMINFO mi;
	TCHAR *buff = new TCHAR [mc_MaxMenuTextLen];	
	HM.AddPtr(buff);		// ʹ�� HM ����̬������ڴ棨���ջ��գ�

	mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_TYPE;
	mi.fType = 0;
    mi.cch = mc_MaxMenuTextLen;
    mi.dwTypeData = buff;

	GetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);

	if ((mi.fType & MFT_SEPARATOR) || (mi.fType & MFT_BITMAP))
	{
		// �Ƿָ��ߣ���λͼ��ʽ�Ĳ˵������ ""
		*buff = 0;
	}
	return buff;
}

void CBMenuItem::TextSet( LPCTSTR newText )
{
	MENUITEMINFO mi;

	// �Ȼ�ò˵�����Ϣ����Ҫ����ԭ���� mi.fType��
	TCHAR buff[mc_MaxMenuTextLen];
	mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_TYPE;
	mi.fType = 0;
	mi.cch = mc_MaxMenuTextLen;
    mi.dwTypeData = buff;
	GetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);
	
	// �����Ƿ�Ҫ������Ϊ�ָ��ߣ�����ͬ����
	if (newText == 0)	// ����Ϊ�ָ���
	{
		mi.fType = mi.fType | MFT_SEPARATOR;
		mi.dwTypeData=0;  mi.cch=0;			 // ������ dwTypeData �� cch ��Ա
	}
	else
	{
		mi.fType = mi.fType & ~MFT_SEPARATOR;
		mi.dwTypeData = (LPTSTR)newText;	
        mi.cch = 1024;							// ������ cch ��Ա

	}

	// ���ò˵���
	mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_TYPE;
	SetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);

	// ����Ƕ���˵����޸�����ۣ��Զ��ػ�˵��������� m_hWndParent ����������Ч��
	if (m_hWndParent)
		if (GetMenu(m_hWndParent) == m_hMenuParent) DrawMenuBar(m_hWndParent);
}

void CBMenuItem::TextSet( tstring stringNewText )
{
	TextSet(stringNewText.c_str());
}


void CBMenuItem::BitmapSet( HBITMAP hBmp )
{
	MENUITEMINFO mi;
	TCHAR buff[mc_MaxMenuTextLen];
	mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_TYPE;
	mi.dwTypeData = buff;
	mi.cch = mc_MaxMenuTextLen;
	GetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);
	
	mi.fType = mi.fType | MFT_BITMAP;
	mi.dwTypeData = (LPTSTR)hBmp;
	SetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);	
	
	// ����Ƕ���˵����޸�����ۣ��Զ��ػ�˵��������� m_hWndParent ����������Ч��
	if (m_hWndParent)
		if (GetMenu(m_hWndParent) == m_hMenuParent) DrawMenuBar(m_hWndParent);
}

void CBMenuItem::BitmapSet( UINT idResBmp )
{
	HBITMAP hBmp = LoadBitmap(pApp->hInstance, MAKEINTRESOURCE(idResBmp));
	if (hBmp)
	{
		pApp->AddImageObjHandle((HANDLE)hBmp, eImgBitmap);	// ��¼����Ա�����˳�ǰ�Զ��ͷ���
		BitmapSet(hBmp);
	}
}


BOOL CBMenuItem::SetCheckBitmaps( UINT idResBmpUnChecked, UINT idResBmpChecked )
{
	HBITMAP hBmpUnCheck, hBMPCheck; 
	BOOL ret;

	// ���λͼ�����С��LOWORD(lSize) ������λͼ��ȣ�HIWORD(lSize) ������λͼ�߶�
	LONG lSize = GetMenuCheckMarkDimensions();
	
	// �������С����λͼ
	hBmpUnCheck = (HBITMAP)LoadImage(pApp->hInstance, MAKEINTRESOURCE(idResBmpUnChecked),
		IMAGE_BITMAP, LOWORD(lSize), HIWORD(lSize), LR_SHARED ); 
	hBMPCheck = (HBITMAP)LoadImage(pApp->hInstance, MAKEINTRESOURCE(idResBmpChecked),
		IMAGE_BITMAP, LOWORD(lSize), HIWORD(lSize), LR_SHARED );

	// ����λͼ
	ret=SetMenuItemBitmaps(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, hBmpUnCheck, hBMPCheck);
	
	// λͼ������� pApp ��ָ�����У����ڳ����˳�ǰ�Զ� DeleteObject
	pApp->AddImageObjHandle((HANDLE)hBmpUnCheck, eImgBitmap); 
	pApp->AddImageObjHandle((HANDLE)hBMPCheck, eImgBitmap);	 
	
	return ret;
}

BOOL CBMenuItem::SetCheckBitmaps( EOEMBmp bmpUnChecked, EOEMBmp bmpChecked )
{
	HBITMAP hBmpUnCheck, hBMPCheck; 
	BOOL ret;
	
	// ���λͼ�����С��LOWORD(lSize) ������λͼ��ȣ�HIWORD(lSize) ������λͼ�߶�
	LONG lSize = GetMenuCheckMarkDimensions();
	
	// �������С����λͼ
	hBmpUnCheck = (HBITMAP)LoadImage(NULL, MAKEINTRESOURCE(bmpUnChecked),
		IMAGE_BITMAP, LOWORD(lSize), HIWORD(lSize), 0 ); 
	hBMPCheck = (HBITMAP)LoadImage(NULL, MAKEINTRESOURCE(bmpChecked),
		IMAGE_BITMAP, LOWORD(lSize), HIWORD(lSize), 0 );
	
	// ����λͼ
	ret=SetMenuItemBitmaps(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, hBmpUnCheck, hBMPCheck);
	
	// λͼ������� pApp ��ָ�����У����ڳ����˳�ǰ�Զ� DeleteObject
	pApp->AddImageObjHandle((HANDLE)hBmpUnCheck, eImgBitmap); 
	pApp->AddImageObjHandle((HANDLE)hBMPCheck, eImgBitmap);	 
	
	return ret;	
}

bool CBMenuItem::Enabled()
{
	UINT r;
	r = GetMenuState(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition);
	if (r & MFS_GRAYED || r & MFS_DISABLED)
		return false;
	else
		return true;
}

void CBMenuItem::EnabledSet( bool enabled/*=true*/ )
{
	if (enabled)
		EnableMenuItem(m_hMenuParent, m_idMenuItemOrPos, MF_ENABLED | m_fByPosition);
	else
		EnableMenuItem(m_hMenuParent, m_idMenuItemOrPos, MF_GRAYED  | m_fByPosition);
	// ����Ƕ���˵����޸�����ۣ��Զ��ػ�˵��������� m_hWndParent ����������Ч��
	if (m_hWndParent)
		if (GetMenu(m_hWndParent) == m_hMenuParent) DrawMenuBar(m_hWndParent);
}

bool CBMenuItem::Checked()
{
	UINT r;
	r = GetMenuState(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition);
	return (r & MF_CHECKED) !=0;
}

void CBMenuItem::CheckedSet( bool checked/*=true*/,		// bRadio=true ʱ�������Դ˲���ֵ
							 bool bRadio/*=false*/,		// bRadio=false ʱΪ�Թ��� bRadio=true ʱΪԲ��
							 UINT itemFrom/*=0*/,		// bRadio=true ʱ����Ҫ���ò˵�����ķ�Χ��itemFrom��itemTo 
							 UINT itemTo/*=0 */,
							 bool fFromToByPosition/*=false*/	// �Ƿ� ��λ��ָ�� itemFrom��itemTo������ itemFrom��itemTo �ǲ˵������Դ ID
							)
{
	if (bRadio)
	{
		// ��Բ�㷽ʽ��ѡ����ʱ���Բ��� checked

		UINT idMenuItem=m_idMenuItemOrPos; 
		if (fFromToByPosition)
		{
			// ======== itemFrom��itemTo ʹ��λ�� ========
			UINT posItem = m_idMenuItemOrPos;
			// ��Ŀ��˵���ת��Ϊλ��
			if (m_fByPosition==MF_BYCOMMAND)
				posItem = GetMenuPositionFromID(m_hMenuParent, m_idMenuItemOrPos);
			// ��λ������
			CheckMenuRadioItem(m_hMenuParent, itemFrom, itemTo, posItem, MF_BYPOSITION);
		}
		else
		{
			// ======== itemFrom��itemTo ʹ����ԴID ========
			if (m_fByPosition==MF_BYPOSITION)
			{
				// �� itemFrom��itemTo ת��Ϊλ��
				itemFrom = GetMenuPositionFromID(m_hMenuParent, itemFrom);
				itemTo = GetMenuPositionFromID(m_hMenuParent, itemTo);
				// ��λ������
				CheckMenuRadioItem(m_hMenuParent, itemFrom, itemTo, m_idMenuItemOrPos, MF_BYPOSITION);
			}
			else
			{
				// ����ԴID����
				CheckMenuRadioItem(m_hMenuParent, itemFrom, itemTo, m_idMenuItemOrPos,MF_BYCOMMAND);
			}
		}
	}
	else
	{
		// �ԶԹ���ʽ��ѡ����ʱ���Բ��� itemFrom��itemTo
		if (checked)
			CheckMenuItem(m_hMenuParent, m_idMenuItemOrPos, MF_CHECKED | m_fByPosition);
		else
			CheckMenuItem(m_hMenuParent, m_idMenuItemOrPos, MF_UNCHECKED | m_fByPosition);
	}	

	// ����Ƕ���˵����޸�����ۣ��Զ��ػ�˵��������� m_hWndParent ����������Ч��
	if (m_hWndParent)
		if (GetMenu(m_hWndParent) == m_hMenuParent) DrawMenuBar(m_hWndParent);
}


bool CBMenuItem::RadioCheck()
{
	return GetfType(MFT_RADIOCHECK);
}

void CBMenuItem::RadioCheckSet( bool bValue )
{
	SetfType(MFT_RADIOCHECK, bValue);
}


bool CBMenuItem::Hilited()
{
	UINT r;
	r = GetMenuState(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition);
	return (r & MF_HILITE) != 0;
}

void CBMenuItem::HilitedSet()
{ 
	MENUITEMINFO mi;
	mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_STATE;
	GetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);
	mi.fState = mi.fState | MFS_HILITE;
	SetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);
	// ���� HiliteMenuItem���������ˢ��������
	// ����ȡ������

	// ����Ƕ���˵����޸�����ۣ��Զ��ػ�˵��������� m_hWndParent ����������Ч��
	if (m_hWndParent)
		if (GetMenu(m_hWndParent) == m_hMenuParent) DrawMenuBar(m_hWndParent);
}


bool CBMenuItem::RightJustify()
{
	return GetfType(MFT_RIGHTJUSTIFY);
}


void CBMenuItem::RightJustifySet( bool bValue )
{
	SetfType(MFT_RIGHTJUSTIFY, bValue);
}


bool CBMenuItem::OwnerDraw()
{
	return GetfType(MF_OWNERDRAW);
}

void CBMenuItem::OwnerDrawSet( bool bValue )
{
	SetfType(MF_OWNERDRAW, bValue);
}


unsigned long CBMenuItem::Tag()
{
	MENUITEMINFO mi;
	mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_DATA;
	GetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);
	return mi.dwItemData;
}

void CBMenuItem::TagSet(unsigned long ulNewValue)
{
	MENUITEMINFO mi;
	mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_DATA;
	mi.dwItemData = ulNewValue;
	SetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);
}



bool CBMenuItem::IsSeparator()
{
	MENUITEMINFO mi;
	mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_TYPE;
	mi.dwTypeData = 0;
	mi.cch = 0;
	GetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);
	if (mi.fType & MFT_SEPARATOR) return true; else return false;
}



HMENU CBMenuItem::hSubMenu()
{
	if (m_hMenuParent==NULL)
	{
		if (m_idMenuItemOrPos>0)
			// �����Ӳ˵����Ϊ������˵����
			return GetMenu(m_hWndParent);
		else
			// �����Ӳ˵����Ϊ��ϵͳ�˵����
			return GetSystemMenu(m_hWndParent, 0);
	}
	else
	{
		MENUITEMINFO mi;
		mi.cbSize = sizeof(mi);
		mi.fMask = MIIM_SUBMENU;
		GetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);
		return mi.hSubMenu;
	}
}

long CBMenuItem::LeftRelative()
{
	RECT rRc; POINT pt;
	rRc.left=0; rRc.top=0;
	rRc.right=0; rRc.bottom=0;
	GetMenuItemRect(m_hWndParent,m_hMenuParent, this->Position()-1, &rRc);
	
	// ת��Ϊ��������
	pt.x = rRc.left; pt.y = rRc.top;
	ScreenToClient(m_hWndParent, &pt);
	return pt.x; 
}

long CBMenuItem::TopRelative()
{
	RECT rRc; POINT pt;
	rRc.left=0; rRc.top=0;
	rRc.right=0; rRc.bottom=0;
	GetMenuItemRect(m_hWndParent,m_hMenuParent, this->Position()-1, &rRc);
	
	// ת��Ϊ��������
	pt.x = rRc.left; pt.y = rRc.top;
	ScreenToClient(m_hWndParent, &pt);
	return pt.y; 	
}

long CBMenuItem::Width()
{
	RECT rRc; 
	rRc.left=0; rRc.top=0;
	rRc.right=0; rRc.bottom=0;
	GetMenuItemRect(m_hWndParent,m_hMenuParent, this->Position()-1, &rRc);
	return rRc.right-rRc.left; 	
}

long CBMenuItem::Height()
{
	RECT rRc; 
	rRc.left=0; rRc.top=0;
	rRc.right=0; rRc.bottom=0;
	GetMenuItemRect(m_hWndParent,m_hMenuParent, this->Position()-1, &rRc);
	return rRc.bottom-rRc.top; 		
}



bool CBMenuItem::BreakMenu()
{
	return GetfType(MFT_MENUBARBREAK) | GetfType(MFT_MENUBREAK);
}

void CBMenuItem::BreakMenuSet( bool bBreak, bool bWithLine/*=true*/ )
{
	if (bBreak)
		if (bWithLine)
			SetfType(MFT_MENUBARBREAK, true);
		else
			SetfType(MFT_MENUBREAK, true);
	else
		SetfType(MFT_MENUBARBREAK | MFT_MENUBREAK, false); 	
}


UINT CBMenuItem::DefaultItemPos( bool bGoIntoPopups /*= false*/, bool bUseDisabled /*= True*/ )
{
	HMENU hSub;
	hSub = hSubMenu();
	if (hSub==0) return 0;

	UINT flags = 0;
	if (bGoIntoPopups) flags = flags | GMDI_GOINTOPOPUPS;
	if (bUseDisabled) flags = flags | GMDI_USEDISABLED;

    return GetMenuDefaultItem(hSub, true, flags) + 1;
}

void CBMenuItem::DefaultItemPosSet( UINT pos )
{
	HMENU hSub;
	hSub = hSubMenu();
	if (hSub==0) return;
	
	SetMenuDefaultItem(hSub, pos - 1, true);
}

bool CBMenuItem::RightToLeft()
{
	return GetfType(MFT_RIGHTJUSTIFY);
}

void CBMenuItem::RightToLeftSet( bool bValue )
{
	SetfType(MFT_RIGHTJUSTIFY, bValue);
}



int CBMenuItem::CountSubItems()
{ 
	HMENU hSub;
	hSub = hSubMenu();
	if (hSub==0) return 0;
	
	return GetMenuItemCount(hSub);
}






















UINT CBMenuItem::GetMenuPositionFromID( HMENU hMenu, UINT idResMenuItem )
{
	int i, iCount;
	UINT idItem;

	iCount = GetMenuItemCount(hMenu); 
	if (iCount == -1) return 0xFFFFFFFF;		// GetMenuItemCount ����ʧ�ܣ����޲˵���
	
	// ���ɨ�� hMenu �µ����в˵���
	for(i=0; i<=iCount-1; i++)
	{
		idItem = GetMenuItemID(hMenu, i);
		if (idItem==idResMenuItem) return i;
		// hMenu �µĵ� i ���м����˵�ʱ��idItem == 0xFFFFFFFF
	}

	return 0xFFFFFFFF;	// δ�ҵ���Դ ID Ϊ idResMenuItem �Ĳ˵���
}

bool CBMenuItem::GetfType( UINT fTypeValue )
{
	MENUITEMINFO mi;
	TCHAR buff[mc_MaxMenuTextLen];
	mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_TYPE;
	mi.dwTypeData = buff;
	mi.cch = mc_MaxMenuTextLen;
	GetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);
	
	if (mi.fType & fTypeValue) return true; else return false;
}

void CBMenuItem::SetfType( UINT fTypeValue, bool bAddOrDelValue )
{
	MENUITEMINFO mi;
	TCHAR buff[mc_MaxMenuTextLen];
	mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_TYPE;
	mi.dwTypeData = buff;
	mi.cch = mc_MaxMenuTextLen;
	GetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);
	
	if (bAddOrDelValue)
		mi.fType = mi.fType | fTypeValue;
	else
		mi.fType = mi.fType & ~fTypeValue;
	SetMenuItemInfo(m_hMenuParent, m_idMenuItemOrPos, m_fByPosition, &mi);	

	// ����Ƕ���˵����޸�����ۣ��Զ��ػ�˵��������� m_hWndParent ����������Ч��
	if (m_hWndParent)
		if (GetMenu(m_hWndParent) == m_hMenuParent) DrawMenuBar(m_hWndParent);
}









