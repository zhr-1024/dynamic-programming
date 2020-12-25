//////////////////////////////////////////////////////////////////////
// BWndBase.cpp: CBWndBase ���ʵ��
// �������洰�ڹ��ܣ���Ϊ CBForm��CBControl ��Ļ���
//   
//////////////////////////////////////////////////////////////////////

#include "BWndBase.h"


// ����ģ��ʹ�õ�ȫ�ֿմ��ַ����ռ�
TCHAR mEmptyStrBase[2]={0};	



//////////////////////////////////////////////////////////////////////////
// �������е� static ��Ա�� static ����

CBHashLK CBWndBase::ms_hashCtrls;
CBHashLK CBWndBase::ms_hashCtrlResIDs;

STWndProp * CBWndBase::PropertyMemCtrl( HWND hWndCtrl, bool bCreate/*=false*/ )
{
	STWndProp * pProp = 
		(STWndProp *)ms_hashCtrls.ItemLong2((long)hWndCtrl, false);
	if (bCreate && pProp==NULL)
	{
		pProp=new STWndProp;
		HM.ZeroMem(pProp, sizeof(STWndProp));	// �¿ռ���0
		
		// �����¿ռ�ĸ���Ա��ʼ����ֵ
		pProp->backColor = -1;	// -1 ��ʾʹ��Ĭ����ɫ
		pProp->hBrushBack = NULL;
		pProp->foreColor = -1;	// -1 ��ʾʹ��Ĭ����ɫ
		SetRect(&pProp->rcPictureClip, -1, -1, -1, -1);		// ��Ϊ-1 ��ʾ����ȡͼƬ��һ������ʾ
		
		// �¿ռ��ַ��¼�� ms_hashCtrls.ItemLong2Set
		if (! ms_hashCtrls.ItemLong2Set((long)hWndCtrl, (long)pProp, false))
		{ delete pProp;  pProp = NULL;  }   // ʧ���ݴ�
	}

	return pProp;
}


//////////////////////////////////////////////////////////////////////////
// ���������

CBWndBase::CBWndBase( HWND hWndToManage /*= NULL*/, 
					  STWndProp * pProperty /*= NULL */ )
{
	// ��Ա��������
	// ���㲻�ܽ��ڹ��캯���н��У����� CBControl ��һ�������
	//   SetResID �Ⱥ�󶨲�ͬ�ؼ�ʱ�������ù��캯����Ҫ�����Ա
	ClearWndBase();

	// ��Ա������ֵ
	m_hWnd = hWndToManage;
	m_pPro = pProperty;
}


CBWndBase::~CBWndBase()
{
	// ��ֹһ���ͷ�ϵͳ��Դ�������� CBControl ��̳б���ʱ��
	//   CBControl �Ƕ�̬�󶨵ģ�����ж��ʱ����Ӧ�Ŀؼ���һ����ж��
	
}



//////////////////////////////////////////////////////////////////////////
// ��Ա����


STWndProp * CBWndBase::PropMem( bool bCreate/*=false*/ )
{
	if (m_pPro)	
	{
		// �����пռ��ַ���� CBForm ���󴴽�ʱ���ù����� CBControl �����ϴ�ָ������
		// ֱ�ӷ���
		return m_pPro;
	}
	else
	{
		// ��û�пռ��ַ�������� CBControl ����
		// ���ϴ�Ϊͬһ�ؼ���hWnd�����ٹ��ռ䣬�򻹷����Ǹ��ռ�ĵ�ַ��
		// ������ bCreate==true���¿���һ���ռ䣬�����¿ռ�ĵ�ַ
		//       �� bCreate==false������ NULL
		// �����ǵ��� PropertyMemCtrl ��̬�������Կؼ��� hWnd ���
		m_pPro = PropertyMemCtrl(m_hWnd, bCreate);	
		return m_pPro;
	}
}


// ���úͷ��� Enabled
void CBWndBase::EnabledSet( bool enabledValue ) const
{
	EnableWindow(m_hWnd, (BOOL)enabledValue);
}

bool CBWndBase::Enabled() const
{
	if (IsWindowEnabled(m_hWnd)) return true; else return false;
}

// ���úͷ��� Visible
void CBWndBase::VisibleSet( bool visibleValue ) const
{
	if (visibleValue)
		ShowWindow(m_hWnd, SW_SHOWNA);
	else
		ShowWindow(m_hWnd, SW_HIDE);
}

bool CBWndBase::Visible() const
{
	if (IsWindowVisible(m_hWnd)) return true; else return false;
}


bool CBWndBase::HScrollBar()
{
	if (Style() & WS_HSCROLL) return true; else return false;
}

void CBWndBase::HScrollBarSet(bool bValue)
{
	if (bValue) 
		StyleSet(WS_HSCROLL);
	else
		StyleSet(WS_HSCROLL, -1);
	Refresh();
}

bool CBWndBase::VScrollBar()
{
	if (Style() & WS_VSCROLL) return true; else return false;
}

void CBWndBase::VScrollBarSet(bool bValue)
{
	if (bValue) 
		StyleSet(WS_VSCROLL);
	else
		StyleSet(WS_VSCROLL, -1);
	Refresh();
}




bool CBWndBase::TabStop()
{
	if (Style() & WS_TABSTOP) return true; else return false;
}

void CBWndBase::TabStopSet( bool bValue )
{
	if (bValue) 
		StyleSet(WS_TABSTOP);
	else
		StyleSet(WS_TABSTOP, -1);
	Refresh();
}


bool CBWndBase::Group()
{
	if (Style() & WS_GROUP) return true; else return false;
}

void CBWndBase::GroupSet( bool bValue )
{
	if (bValue) 
		StyleSet(WS_GROUP);
	else
		StyleSet(WS_GROUP, -1);
	Refresh();
}


LPTSTR CBWndBase::TagString()
{
	m_pPro = PropMem(false);
	if (m_pPro)   
		if (m_pPro->tagString) 
			return m_pPro->tagString;
	
	// û�����ù��������ԣ��򸽼����Ե� tagString == NULL��
	//  ������ȫ�� mEmptyStrBase �ռ�� ""
	mEmptyStrBase[0]=0; return mEmptyStrBase; 	
}

void CBWndBase::TagStringSet( LPCTSTR tagString )
{
	if (tagString==NULL)	// ���ǿ�ָ�����Ϊ���ַ���
	{ mEmptyStrBase[0]=0; tagString=mEmptyStrBase;	}
	
	m_pPro = PropMem(false);// ����Ϊ false�������ٸ������ԵĿռ�
	// ����ǿ��ַ������һ�δ���ù��������ԣ����ֻ�δ���ü���
	if (m_pPro==NULL && *tagString==0) return;

	
	// ���ø������ԣ���ȡ�ռ�
	m_pPro = PropMem(true);
		// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro==NULL)  return; 
		// ������������Ϊ true���� m_pPro ��Ϊ NULL ��ʾ����
	
	// ɾ��ԭ�ַ����Ŀռ䣬����еĻ���m_pPro->tagString δ�� HM ����
	if (m_pPro->tagString) delete [](m_pPro->tagString);	
	m_pPro->tagString = new TCHAR[lstrlen(tagString)+1];
	_tcscpy(m_pPro->tagString, tagString);	
}

int CBWndBase::TagInt()
{
	m_pPro = PropMem(false);
	if (m_pPro)  
		return m_pPro->iTag1;
	else
		return 0;
}

void CBWndBase::TagIntSet( int iTag )
{
	m_pPro = PropMem(true);
		// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro) m_pPro->iTag1 = iTag;	
}

int CBWndBase::TagInt2()
{
	m_pPro = PropMem(false);
	if (m_pPro)  
		return m_pPro->iTag2;
	else
		return 0;	
}

void CBWndBase::TagInt2Set( int iTag2 )
{
	m_pPro = PropMem(true);
	// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro) m_pPro->iTag2 = iTag2;	
}

double CBWndBase::TagDouble()
{
	m_pPro = PropMem(false);
	if (m_pPro)  
		return m_pPro->dTag;
	else
		return 0;	
}

void CBWndBase::TagDoubleSet( double dTag )
{
	m_pPro = PropMem(true);
	// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro) m_pPro->dTag = dTag;		
}







// ================================================
// λ�ô�С
// ================================================

// �ؼ���С��λ��
int CBWndBase::Left() const
{
	RECT rect;
	POINT pt;
	if (GetWindowRect(m_hWnd, &rect)) 
	{
		pt.x = rect.left; pt.y = rect.top; 

		// �� ������ ��Ϊ NULL����ת��Ϊ���ĸ����ڵ�����ϵ
		HWND hWndParent = GetParent(m_hWnd);
		if (hWndParent) ScreenToClient(hWndParent, &pt);	

		return pt.x;
	}
	else
	{
		return 0;
	}
}

int CBWndBase::Top() const
{
	RECT rect;
	POINT pt;
	if (GetWindowRect(m_hWnd, &rect)) 
	{
		pt.x = rect.left; pt.y = rect.top; 

		// �� ������ ��Ϊ NULL����ת��Ϊ���ĸ����ڵ�����ϵ
		HWND hWndParent = GetParent(m_hWnd);
		if (hWndParent) ScreenToClient(hWndParent, &pt);	

		return pt.y;
	}
	else
	{
		return 0;
	}
}

int CBWndBase::Width() const
{
	RECT rect;
	POINT pt1, pt2;
	if (GetWindowRect(m_hWnd, &rect)) 
	{
		pt1.x = rect.left; pt1.y = rect.top; 
		pt2.x = rect.right; pt2.y = rect.bottom; 

		// �� ������ ��Ϊ NULL����ת��Ϊ���ĸ����ڵ�����ϵ
		HWND hWndParent = GetParent(m_hWnd);
		if (hWndParent)
		{
			ScreenToClient(hWndParent, &pt1);	
			ScreenToClient(hWndParent, &pt2);
		}

		return pt2.x - pt1.x;
	}
	else
	{
		return 0;
	}
}

int CBWndBase::Height() const
{
	RECT rect;
	POINT pt1, pt2;
	if (GetWindowRect(m_hWnd, &rect)) 
	{
		pt1.x = rect.left; pt1.y = rect.top; 
		pt2.x = rect.right; pt2.y = rect.bottom; 

		// �� ������ ��Ϊ NULL����ת��Ϊ���ĸ����ڵ�����ϵ
		HWND hWndParent = GetParent(m_hWnd);
		if (hWndParent)
		{
			ScreenToClient(hWndParent, &pt1);	
			ScreenToClient(hWndParent, &pt2);
		}

		return pt2.y - pt1.y;
	}
	else
	{
		return 0;
	}

}


int CBWndBase::ClientWidth() const
{
	RECT rect;
	if (GetClientRect(m_hWnd, &rect))
		return rect.right - rect.left;
	else
		return 0;
}

int CBWndBase::ClientHeight() const
{
	RECT rect;
	if (GetClientRect(m_hWnd, &rect))
		return rect.bottom - rect.top;
	else
		return 0;	
}


void CBWndBase::LeftSet(int left) const
{
	Move(left);
}

void CBWndBase::TopSet(int top) const
{
	Move(0x7FFFFFFF, top);
}

void CBWndBase::WidthSet(int width) const
{
	Move(0x7FFFFFFF, 0x7FFFFFFF, width);
}

void CBWndBase::HeightSet(int height) const
{
	Move(0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, height);
}

void CBWndBase::Move( int left/*=0x7FFFFFFF*/, 
					  int top/*=0x7FFFFFFF*/, 
					  int width/*=0x7FFFFFFF*/, 
					  int height/*=0x7FFFFFFF*/ ) const
{
	RECT rect;
	POINT pt1, pt2;
	if (! GetWindowRect(m_hWnd, &rect)) 
	{
		// ���ܻ�ô��ڵ�ǰ��С��Ϊ�ݴ�����Ϊһ��Ĭ�ϴ�С
		rect.left=0; rect.top=0;
		rect.right=100; rect.bottom=100;
	}
	pt1.x = rect.left; pt1.y = rect.top; 
	pt2.x = rect.right; pt2.y = rect.bottom; 

	// �� ������ ��Ϊ NULL����ת��Ϊ���ĸ����ڵ�����ϵ
	HWND hWndParent = GetParent(m_hWnd);
	if (hWndParent)
	{
		ScreenToClient(hWndParent, &pt1);	
		ScreenToClient(hWndParent, &pt2);
	}

	// �����µ�λ�úʹ�С => rect
	if (left!=0x7FFFFFFF) { pt2.x += (left-pt1.x); pt1.x = left;  }
	if (top!=0x7FFFFFFF) { pt2.y += (top-pt1.y); pt1.y = top; }
	if (width!=0x7FFFFFFF) pt2.x = pt1.x + width;
	if (height!=0x7FFFFFFF) pt2.y = pt1.y + height;
	
	// �ƶ��ؼ�λ�ú͵�����С
	MoveWindow(m_hWnd, pt1.x, pt1.y, 
		pt2.x-pt1.x, pt2.y-pt1.y, 1);

	InvalidateRect(m_hWnd, NULL, 0);
}








// ================================================
// ���
// ================================================




long CBWndBase::MousePointer()
{
	m_pPro = PropMem(false);
	if (m_pPro==NULL) return 0;

	return m_pPro->cursorIdx;
}

void CBWndBase::MousePointerSet( EStandardCursor cursor )
{
	MousePointerSet((long)cursor, 0);
}

void CBWndBase::MousePointerSet( long idResCursor, LPCTSTR typeRes/*=0*/ )
{
	m_pPro = PropMem(true);
		// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro==NULL) return; 
		//������������Ϊ true���� m_pPro ��Ϊ NULL ��ʾ����

	m_pPro->cursorIdx = idResCursor;  m_pPro->cursorIdx2 = idResCursor;  // m_CursorIdx2 �Ǹ���
	if (m_pPro->cursorIdx)
	{
		// ���ع�꣬������� m_hCursor
		// =============================================================
		// LoadCursor ������ʹ�ظ������ã�Ҳ�����ظ�������Դ��ϵͳ���ж�
		//   �����Ӧ����Ѿ����أ�LoadCursor ֱ�ӷ��ؾ��
		// =============================================================
		if ( m_pPro->cursorIdx > gc_IDStandCursorIDBase)
		{
			// ��׼���
			// m_CursorIdx-gc_IDStandCursorIDBase ���Ǳ�׼����ID��
			m_pPro->hCursor = 
				LoadCursor(NULL, 
				  MAKEINTRESOURCE(m_pPro->cursorIdx - gc_IDStandCursorIDBase));
			m_pPro->hCursor2 = m_pPro->hCursor;		// ���渱��
		}
		else
		{
			// ��Դ���
			// m_CursorIdx ������Դ ID
			if (typeRes==0)
			{
				// ���� Cursor ���͵���Դ
				m_pPro->hCursor = LoadCursor(pApp->hInstance, MAKEINTRESOURCE(m_pPro->cursorIdx));
				m_pPro->hCursor2 = m_pPro->hCursor;		// ���渱��
			}
			else
			{
				// �����Զ������͵���Դ��typeRes ���͵���Դ��
				unsigned long size=0; 
				unsigned char * p= LoadResData(m_pPro->cursorIdx, typeRes, &size);
				m_pPro->hCursor = (HCURSOR)CreateIconFromResource(p, size, 0, 0x00030000);
				m_pPro->hCursor2 = m_pPro->hCursor;		// ���渱��
			}

			// ��¼�ù�������Ա�����˳�ǰ�Զ�ɾ��
			pApp->AddImageObjHandle((HANDLE)m_pPro->hCursor, eImgCursor);
		}
	}	
	else	// if (m_CursorIdx)
	{
		// ���������ù�꣬ʹ��Ĭ�ϣ����� m_hCursor Ϊ 0
		m_pPro->hCursor = NULL; 
		m_pPro->hCursor2 = m_pPro->hCursor;		// ���渱��
	}		// end if (m_CursorIdx)


	// ����� Static �ؼ�����������Ϊ���� SS_NOTIFY ��񣬷���ؼ������� WM_SETCURSOR ��Ϣ
	// -------------------------------------------------------------------------------------------------
	// From: http://stackoverflow.com/questions/19257237/reset-cursor-in-wm-setcursor-handler-properly
	//   Static controls are normally transparent (not in the visual sense, but meaning that even when 
	// the mouse is over the transparent window, Windows will consider the mouse to be over the window 
	// underneath the transparent window).
	//   ... did not work when the static control was created without SS_NOTIFY because without this 
	// style the static control was transparent, which meant that the WARAM in the WM_SETCURSOR message 
	// was never equal to the static control (in other words Windows never considered the mouse to be over 
	// the static control because it was transparent).
	// -------------------------------------------------------------------------------------------------
	if (IsClassName(TEXT("Static"))) StyleSet(SS_NOTIFY, 1);

	// �򱾴��ڷ��� WM_SETCURSOR����ʹ���������Ч
	SendMessage(m_hWnd, WM_SETCURSOR, (WPARAM)m_hWnd, 0);
	// �ڱ����ڲ��Ͻ��յ��� WM_SETCURSOR ��Ϣ�л�ı������
}





COLORREF CBWndBase::BackColor()
{
	m_pPro = PropMem(false);
	if (m_pPro==NULL)   // δ���ù�������ɫ������ϵͳ COLOR_BTNFACE ��ɫ
		return GetSysColor(COLOR_BTNFACE);

	if (-1 == m_pPro->backColor)
	{
		// ��ô�����ı���ɫ
		HBRUSH hBrush;
		LOGBRUSH lb;
		hBrush=(HBRUSH)GetClassLong(m_hWnd, GCL_HBRBACKGROUND);
		if (hBrush) 
		{
			GetObject((HGDIOBJ)hBrush, sizeof(lb), &lb);
			return lb.lbColor;
		}
		else
		{
			// GetClassLong ʧ�ܣ��򴰿����޻�ˢ������ϵͳ COLOR_BTNFACE ��ɫ
			return GetSysColor(COLOR_BTNFACE);
		}
	}
	else
		// ֱ�ӷ��������е� backColor
		return m_pPro->backColor;	
}

void CBWndBase::BackColorSet( EColorType color )
{
	BackColorSet( (COLORREF)GetSysColor(color) );
}

void CBWndBase::BackColorSet( COLORREF color )
{
	if ( IsClassName( TEXT("msctls_progress32") ) ) 
	{
		// ProgressBar����ʹ��XP���6.0�ؼ�ʱ����Ч
		SendMessage(m_hWnd, PBM_SETBKCOLOR, 0, (LPARAM)color); 
	}

	m_pPro = PropMem(true);
		// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro==NULL) return; 
		// ������������Ϊ true���� m_pPro ��Ϊ NULL ��ʾ����
	
	// �����Խṹ��� backColor ��Ա��¼����ɫ
	m_pPro->backColor = color;
	// ͬʱ����ˢ�ӣ������¿ռ�� hBrushBack ��Ա��¼ˢ�Ӿ��
	if (m_pPro->hBrushBack) DeleteObject(m_pPro->hBrushBack);
	m_pPro->hBrushBack = CreateSolidBrush(color); 

	InvalidateRect(m_hWnd, NULL, TRUE);	// ʹ������Ч
}



COLORREF CBWndBase::ForeColor()
{
	m_pPro = PropMem(false);
	if (m_pPro)
		if (-1 != m_pPro->foreColor) 
			return m_pPro->foreColor;
	
	return GetSysColor(COLOR_WINDOWTEXT);
}

void CBWndBase::ForeColorSet( EColorType color )
{
	ForeColorSet( (COLORREF)GetSysColor(color) );
}

void CBWndBase::ForeColorSet( COLORREF color )
{
	if ( IsClassName( TEXT("msctls_progress32") ) ) 
	{
		// ProgressBar����ʹ��XP���6.0�ؼ�ʱ����Ч
		SendMessage(m_hWnd, PBM_SETBARCOLOR, 0, (LPARAM)color);  
	}

	m_pPro = PropMem(true);
	// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro==NULL) return; 
		//������������Ϊ true���� m_pPro ��Ϊ NULL ��ʾ����

	m_pPro->foreColor = color;

	InvalidateRect(m_hWnd, NULL, TRUE);	// ʹ������Ч
}


// ================================================
// �ı�
// ================================================

// ֱ�������ı����и������ذ汾��
void CBWndBase::TextSet( LPCTSTR newText ) const
{
	SetWindowText(m_hWnd, newText);
}
void CBWndBase::TextSet(char valueChar) const
{  
	LPTSTR buff=Str(valueChar);
	TextSet(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextSet(unsigned short int valueInt) const	// TCHAR
{
	LPTSTR buff=Str(valueInt);
	TextSet(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextSet(int valueInt) const
{ 
	LPTSTR buff=Str(valueInt);
	TextSet(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}	
void CBWndBase::TextSet(long valueLong) const
{ 
	LPTSTR buff=Str(valueLong);
	TextSet(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextSet(unsigned int valueInt) const
{ 
	LPTSTR buff=Str(valueInt);
	TextSet(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextSet(unsigned long valueInt) const
{ 
	LPTSTR buff=Str(valueInt);
	TextSet(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextSet(float valueSng) const
{
	LPTSTR buff=Str(valueSng);
	TextSet(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextSet(double valueDbl) const
{
	LPTSTR buff=Str(valueDbl);
	TextSet(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextSet(long double valueDbl) const
{
	LPTSTR buff=Str(valueDbl);
	TextSet(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}

void CBWndBase::TextSet( tstring valueString ) const
{
	TextSet(valueString.c_str());
}

// �����ı�����������ı������ã��и������ذ汾��
void CBWndBase::TextAdd( LPCTSTR newText ) const
{
	int lenText;
	lenText=GetWindowTextLength(m_hWnd);
		
	TCHAR * pText=new TCHAR[lenText+lstrlen(newText)+1];
	GetWindowText(m_hWnd, pText, lenText+1);
	_tcscat(pText, newText);

	SetWindowText(m_hWnd, pText);
	delete []pText;
}
void CBWndBase::TextAdd(char valueChar) const
{
	LPTSTR buff=Str(valueChar);
	TextAdd(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextAdd(unsigned short int valueInt) const
{
	LPTSTR buff=Str(valueInt);
	TextAdd(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextAdd(int valueInt) const
{
	LPTSTR buff=Str(valueInt);
	TextAdd(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextAdd(long valueLong) const
{
	LPTSTR buff=Str(valueLong);
	TextAdd(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextAdd(unsigned int valueInt) const
{
	LPTSTR buff=Str(valueInt);
	TextAdd(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextAdd(unsigned long valueInt) const
{
	LPTSTR buff=Str(valueInt);
	TextAdd(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextAdd(float valueSng) const
{
	LPTSTR buff=Str(valueSng);
	TextAdd(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextAdd(double valueDbl) const
{
	LPTSTR buff=Str(valueDbl);
	TextAdd(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}
void CBWndBase::TextAdd(long double valueDbl) const
{
	LPTSTR buff=Str(valueDbl);
	TextAdd(buff);
	HM.Free(buff);	// �ɼ�ʱ�ͷ� buff �Ŀռ�
}

void CBWndBase::TextAdd( tstring valueString ) const
{
	TextAdd(valueString.c_str());
}


// ����ı����ɻ���ַ����ģ��Լ�ת��Ϊ���͡�double�͵ģ�
LPTSTR CBWndBase::Text() const
{
	int lenText;
	lenText=GetWindowTextLength(m_hWnd);

	TCHAR * pText=new TCHAR[lenText+1];
	HM.AddPtr(pText);

	GetWindowText(m_hWnd, pText, lenText+1);
	return pText;
}

double CBWndBase::TextVal() const
{
	int lenText;
	double dblRet=0.0;
	lenText=GetWindowTextLength(m_hWnd);

	TCHAR * pText=new TCHAR[lenText+1];
	GetWindowText(m_hWnd, pText, lenText+1);
	
	dblRet = Val(pText);
	delete []pText;
	return dblRet;
}



// ================================================
// ����
// ================================================



LPTSTR CBWndBase::FontName()
{
	LOGFONT lf;  GetFontMLF(&lf);
	TCHAR * pStr = new TCHAR [lstrlen(lf.lfFaceName) + 1];
	HM.AddPtr(pStr);
	_tcscpy(pStr, lf.lfFaceName);
	return pStr;
}

void CBWndBase::FontNameSet( LPCTSTR szFontName )
{
	LOGFONT lf;  GetFontMLF(&lf);

	if ( lstrlen(szFontName) > LF_FACESIZE )
	{
		// ���������ַ����������ض�֮
		_tcsncpy(lf.lfFaceName, szFontName, LF_FACESIZE-1 );
		*(lf.lfFaceName + LF_FACESIZE - 1) = 0;	
	}
	else
	{
		_tcscpy( lf.lfFaceName, szFontName );
	}

	SetFontMLF(&lf);
}

void CBWndBase::FontNameSet( tstring stringFontName )
{
	FontNameSet(stringFontName.c_str());
}

float CBWndBase::FontSize()
{
	LOGFONT lf;  GetFontMLF(&lf);

	HDC hDC=GetDC(m_hWnd);
	float fheight =
		(float)(lf.lfHeight * (-72.0) / GetDeviceCaps(hDC, LOGPIXELSY));
	fheight = (float)((int)(fheight * 100 + 0.5)/100.0);	// ���� 2 λС��
	ReleaseDC(m_hWnd, hDC);

	return fheight;
}

void CBWndBase::FontSizeSet( float fSize )
{
	LOGFONT lf;  GetFontMLF(&lf);

	HDC hDC=GetDC(m_hWnd);
	float fheight = 
		(float)(- fSize * GetDeviceCaps(hDC, LOGPIXELSY) / 72.0);
	lf.lfHeight = (long)(fheight+0.5);	// �������� fheight
	ReleaseDC(m_hWnd, hDC);

	SetFontMLF(&lf);
}

bool CBWndBase::FontBold()
{
	LOGFONT lf;  GetFontMLF(&lf);
	return (lf.lfWeight >= 700);
}

void CBWndBase::FontBoldSet( bool value )
{
	LOGFONT lf;  GetFontMLF(&lf);

	if (value)
		lf.lfWeight = 700;
	else
		lf.lfWeight = 400;

	SetFontMLF(&lf);
}

bool CBWndBase::FontUnderline()
{
	LOGFONT lf;  GetFontMLF(&lf);
	return (lf.lfUnderline != 0);
}

void CBWndBase::FontUnderlineSet( bool value )
{
	LOGFONT lf;  GetFontMLF(&lf);

	if (value)
		lf.lfUnderline = 1;
	else
		lf.lfUnderline = 0;

	SetFontMLF(&lf);
}

bool CBWndBase::FontItalic()
{
	LOGFONT lf;  GetFontMLF(&lf);
	return (lf.lfItalic != 0);	
}

void CBWndBase::FontItalicSet( bool value )
{
	LOGFONT lf;  GetFontMLF(&lf);
	
	if (value)
		lf.lfItalic = 1;
	else
		lf.lfItalic = 0;

	SetFontMLF(&lf);
}

float CBWndBase::FontRotateDegree()
{
	LOGFONT lf;  GetFontMLF(&lf);
	return (float)(lf.lfEscapement / 10);
}

void CBWndBase::FontRotateDegreeSet( float fDegree )
{
	LOGFONT lf;  GetFontMLF(&lf);
	lf.lfEscapement = (long)(fDegree * 10+0.5);
	SetFontMLF(&lf);
}

BYTE CBWndBase::FontCharSet()
{
	LOGFONT lf;  GetFontMLF(&lf);
	return lf.lfCharSet;
}

void CBWndBase::FontCharSetSet( BYTE ucValue )
{
	LOGFONT lf;  GetFontMLF(&lf);
	lf.lfCharSet = ucValue;
	SetFontMLF(&lf);
}


int CBWndBase::TextWidth( LPCTSTR sText )
{
	HDC hDC = GetDC(m_hWnd);
	HFONT hFontOld = (HFONT)SelectObject(hDC, GetFontMLF(NULL));
	SIZE sz;
	GetTextExtentPoint32(hDC, sText, lstrlen(sText), &sz);
	SelectObject(hDC, hFontOld);
	ReleaseDC(m_hWnd, hDC);
	return sz.cx;
}

int CBWndBase::TextHeight(LPCTSTR sText/*=NULL*/)
{
	TEXTMETRIC tm;
	HDC hDC = GetDC(m_hWnd);
	HFONT hFontOld = (HFONT)SelectObject(hDC, GetFontMLF(NULL));
	if (sText==NULL)
	{
		GetTextMetrics(hDC, &tm);
	}
	else
	{
		SIZE sz;
		GetTextExtentPoint32(hDC, sText, lstrlen(sText), &sz);
		tm.tmHeight = sz.cy;	// �����Ҳ���� tm.tmHeight ������ǰһ�����ͳһ
	}
	
	SelectObject(hDC, hFontOld);
	ReleaseDC(m_hWnd, hDC);

	return tm.tmHeight;
}


// protected:

HFONT CBWndBase::GetFontMLF( LOGFONT * lpLf /*=NULL*/ )
{
	HFONT hFont = NULL; 

	m_pPro = PropMem(false);
	if (m_pPro==NULL) 
	{
		// ==== δ���ù����ԣ��ؼ�����ʹ��ϵͳ���� ====
		// ������и����ڣ���ʾ�ǿؼ������Ǵ��壩������ WM_GETFONT ��Ϣ���ϵͳ��������
		if (GetParent(m_hWnd))
			hFont = (HFONT)SendMessage (m_hWnd, WM_GETFONT, 0, 0);	// hFont ����Ϊ NULL
		else
			hFont = NULL;
	}
	else
	{
		hFont = m_pPro->hFont;
	}

	// ��ȡ������Ϣ
	if (lpLf) 	// �� lpLf Ϊ��ָ�룬����ȡ������Ϣ
	{
		HM.ZeroMem((void *)lpLf, sizeof(LOGFONT));		// ȫ����Ա����
		if (hFont)
		{
			// �ɹ�����������������������Ϣ
			GetObject( (HGDIOBJ)hFont, sizeof(LOGFONT), lpLf );
		}
		else
		{
			// ������������� lpLf ΪĬ������
			lpLf->lfHeight = -15;
			lpLf->lfWeight = 400;
			_tcscpy(lpLf->lfFaceName, TEXT("����"));
		}
	}
	
	// ����������������Ϊ NULL��
	return hFont;
}


HFONT CBWndBase::SetFontMLF( LOGFONT * lpLf )
{
	HFONT hFontNew = CreateFontIndirect(lpLf);

	if (GetParent(m_hWnd))	// ����и����ڱ�ʾ�ǶԿؼ������ǶԴ��壩���ͷ��� WM_SETFONT ��Ϣ
	{
		// causes the control to redraw itself immediately upon setting the font
		SendMessage (m_hWnd, WM_SETFONT, (WPARAM)hFontNew, 1);
	}

	m_pPro = PropMem(true);
		// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro==NULL) return hFontNew; 
		// ������������Ϊ true���� m_pPro ��Ϊ NULL ��ʾ�������Է��� hFontNew
	
	// ���½�����������������浽���Կռ�
	if (m_pPro->hFont)			
		DeleteObject(m_pPro->hFont);	// ɾ�����������	
	m_pPro->hFont = hFontNew;			// �����Կռ��¼���������
	
	// ���������������
	return hFontNew;
}



// ================================================
// �߿�
// ================================================

bool CBWndBase::Border()
{
	if (Style() & WS_BORDER) return true; else return false;
}

void CBWndBase::BorderSet( bool bValue )
{
	if (bValue) 
		StyleSet(WS_BORDER);
	else
		StyleSet(WS_BORDER, -1);
	Refresh();
}

bool CBWndBase::BorderFrameDlg()
{
	if (Style() & WS_DLGFRAME) return true; else return false;
}

void CBWndBase::BorderFrameDlgSet( bool bValue )
{
	if (bValue) 
		StyleSet(WS_DLGFRAME);
	else
		StyleSet(WS_DLGFRAME, -1);
	Refresh();
}

bool CBWndBase::BorderFrameThick()
{
	if (Style() & WS_THICKFRAME) return true; else return false;
}

void CBWndBase::BorderFrameThickSet( bool bValue )
{
	if (bValue) 
		StyleSet(WS_THICKFRAME);
	else
		StyleSet(WS_THICKFRAME, -1);
	Refresh();
}

bool CBWndBase::BorderRaised()
{
	if (StyleEx() & WS_EX_WINDOWEDGE) return true; else return false;
}

void CBWndBase::BorderRaisedSet( bool bValue )
{
	if (bValue) 
	{
		// ������ WS_THICKFRAME �� WS_DLGFRAME������������
		if ( ! ( Style() & (WS_THICKFRAME | WS_DLGFRAME) ) )
			StyleSet(WS_DLGFRAME);
		StyleExSet(WS_EX_WINDOWEDGE);
	}
	else
		StyleExSet(WS_EX_WINDOWEDGE, -1);
	Refresh();
}


bool CBWndBase::BorderSunken()
{
	if (StyleEx() & WS_EX_CLIENTEDGE) return true; else return false;
}

void CBWndBase::BorderSunkenSet( bool bValue )
{
	if (bValue) 
		StyleExSet(WS_EX_CLIENTEDGE);
	else
		StyleExSet(WS_EX_CLIENTEDGE, -1);
	Refresh();
}


bool CBWndBase::BorderEtched()
{
	if (Style() & SS_ETCHEDFRAME) return true; else return false;
}

void CBWndBase::BorderEtchedSet( bool bValue )
{
	if (bValue) 
		StyleSet(SS_ETCHEDFRAME);
	else
		StyleSet(SS_ETCHEDFRAME, -1);
	Refresh();	
}

bool CBWndBase::BorderStatic()
{
	if (StyleEx() & WS_EX_STATICEDGE) return true; else return false;
}

void CBWndBase::BorderStaticSet( bool bValue )
{
	if (bValue) 
		StyleExSet(WS_EX_STATICEDGE);
	else
		StyleExSet(WS_EX_STATICEDGE, -1);
	Refresh();
}

bool CBWndBase::BorderTitleBar()
{
	if (Style() & WS_CAPTION) return true; else return false;
}

void CBWndBase::BorderTitleBarSet( bool bValue )
{
	if (bValue) 
		StyleSet(WS_CAPTION);
	else
		StyleSet(WS_CAPTION, -1);
	Refresh();
}


bool CBWndBase::BorderToolWindow()
{
	if (StyleEx() & WS_EX_TOOLWINDOW) return true; else return false;
}

void CBWndBase::BorderToolWindowSet( bool bValue )
{
	if (bValue) 
		StyleExSet(WS_EX_TOOLWINDOW);
	else
		StyleExSet(WS_EX_TOOLWINDOW, -1);
	Refresh();
}





// ================================================
// ��ͼ
// ================================================


void CBWndBase::PictureSet( UINT bmpResID )
{
	m_pPro = PropMem(true);
		// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro) 
	{
		HANDLE hBmp = LoadImage(pApp->hInstance, (LPCTSTR)bmpResID, IMAGE_BITMAP, 0, 0, LR_SHARED);
			// LR_SHARED��Shares the image handle, returning the same handle, 
			//            if the image is loaded multiple times. not load the image again

		m_pPro->hBmpDisp = (HBITMAP)hBmp;

		InvalidateRect(m_hWnd, NULL, true);	// ʹ������Ч
	}
}

void CBWndBase::PictureSet( LPCTSTR bmpFile )
{
	m_pPro = PropMem(true);
		// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro) 
	{
		HANDLE hBmp = LoadImage(NULL, bmpFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			// Do not use LR_SHARED for images that have non-standard sizes, 
			//   that may change after loading, or that are loaded from a file.

		m_pPro->hBmpDisp = (HBITMAP)hBmp;

		InvalidateRect(m_hWnd, NULL, true);	// ʹ������Ч	
	}
}

void CBWndBase::PictureSet( HANDLE hPic, EImgObjType picType )
{
	LONG stl = GetWindowLong(m_hWnd, GWL_STYLE);
	if ( IsClassName(TEXT("Button")) )
	{
		//////////////////////////////////////////////////////////////////////////
		// Button �ؼ�

		// �ı� Style 
		// BM_SETSTYLE
		
		if ( picType == IMAGE_BITMAP )
		{
			// ���� Button �ؼ�Ϊ BS_BITMAP ���
			stl = stl & ~BS_ICON;
			stl = stl | BS_BITMAP;
			SetWindowLong(m_hWnd, GWL_STYLE, stl);
		}
		else if ( picType == IMAGE_ICON )
		{
			// ���� Button �ؼ�Ϊ BS_ICON ���
			stl = stl & ~BS_BITMAP;
			stl = stl | BS_ICON;
			SetWindowLong(m_hWnd, GWL_STYLE, stl);
		}
		
		// ����ͼƬ
		SendMessage(m_hWnd, BM_SETIMAGE, (WPARAM)picType, (LPARAM)hPic);
	}
	else if ( IsClassName(TEXT("Static")) )
	{
		//////////////////////////////////////////////////////////////////////////
		// Static �ؼ�

		bool bRestoreCENTERIMAGE=false; 
		
		// ���� SS_CENTERIMAGE �������ʾͼƬʱ���ܻ������⣺
		//   �� hPic Ϊ 0 ��ʾɾ��ͼƬ����������ˢ��ɾ��
		//   ת��Ϊ SS_ICON ���ʱԭλͼ���ܱ���� 
		// ���д˷������Ҫȡ�� SS_CENTERIMAGE ֮���ٻָ�
		if (stl & SS_CENTERIMAGE)
		{
			// ��ʱȡ�� SS_CENTERIMAGE
			stl = stl & ~SS_CENTERIMAGE;
			SetWindowLong(m_hWnd, GWL_STYLE, stl);
			bRestoreCENTERIMAGE=true;
		}
		
		// ����ͼƬ���ͣ������ؼ���񣬲�����ͼƬ
		if ( picType == IMAGE_BITMAP )
		{
			// ���� Static �ؼ�Ϊ SS_BITMAP ���
			stl = stl & ~SS_ICON;
			stl = stl & ~SS_ENHMETAFILE;
			stl = stl | SS_BITMAP;
			SetWindowLong(m_hWnd, GWL_STYLE, stl);
			
			// ����λͼ
			m_pPro = PropMem(true);
			if (m_pPro) m_pPro->hBmpDisp = (HBITMAP)hPic;  // ��λͼ��������� pProp->hBmpAsso

			InvalidateRect(m_hWnd, NULL, TRUE);			 // �� WM_Paint ʱ����λͼ����֧�� Stretch��
		}
		else if ( picType == IMAGE_ICON )
		{
			// ���� Static �ؼ�Ϊ SS_ICON ���
			stl = stl & ~SS_BITMAP;
			stl = stl & ~SS_ENHMETAFILE;
			stl = stl | SS_ICON;
			SetWindowLong(m_hWnd, GWL_STYLE, stl);
			
			// ����ͼ��
			SendMessage(m_hWnd, STM_SETIMAGE, (WPARAM)picType, (LPARAM)hPic);
		}
		else	// ��������ͼƬ
		{
			SendMessage(m_hWnd, STM_SETIMAGE, (WPARAM)picType, (LPARAM)hPic);
		}
		
		// ����Ҫ���ָ� SS_CENTERIMAGE
		if (bRestoreCENTERIMAGE)
			SetWindowLong(m_hWnd, GWL_STYLE, stl | SS_CENTERIMAGE);
	}
	else	// �������Ϳؼ����壨��֧��λͼ��
	{
		//////////////////////////////////////////////////////////////////////////
		// �������Ϳؼ����壨��֧��λͼ��
		if ( picType == IMAGE_BITMAP )
		{
			// ����λͼ
			m_pPro = PropMem(true);
			if (m_pPro) m_pPro->hBmpDisp = (HBITMAP)hPic;  // ��λͼ��������� pProp->hBmpAsso
			InvalidateRect(m_hWnd, NULL, TRUE);			 // �� WM_Paint ʱ����λͼ����֧�� Stretch��
		}
	}
	
	// ��ͼ������¼�� pApp���Ա�������ǰ���Զ� DeleteObject
	pApp->AddImageObjHandle((HANDLE)hPic, picType);
}

void CBWndBase::PictureClipSet( int xClip/*=-1*/, int yClip/*=-1*/, int widthClip/*=-1*/, int heightClip/*=-1*/ )
{
	m_pPro = PropMem(true);
	// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro) 
	{
		m_pPro->rcPictureClip.left = xClip; 
		m_pPro->rcPictureClip.top = yClip;

		if (widthClip>=0) 
			m_pPro->rcPictureClip.right = xClip + widthClip; 
		else 
			m_pPro->rcPictureClip.right=-1; 

		if (heightClip>=0) 
			m_pPro->rcPictureClip.bottom = yClip + heightClip; 
		else 
			m_pPro->rcPictureClip.bottom=-1; 

		InvalidateRect(m_hWnd, NULL, true);	// ʹ������Ч���� WM_Paint ʱ����λͼ����֧�� Stretch��	
	}
}





bool CBWndBase::Stretch()
{
	m_pPro = PropMem(false);
	if (m_pPro==NULL)   // δ���ù�����
		return false;
	else
		return m_pPro->stretch;
}

void CBWndBase::StretchSet( bool stretchVal )
{
	m_pPro = PropMem(true);
		// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro==NULL) return; 
		// ������������Ϊ true���� m_pPro ��Ϊ NULL ��ʾ����
	
	// �����Խṹ��� stretch ��Ա��¼
	m_pPro->stretch = stretchVal;
	
	InvalidateRect(m_hWnd, NULL, TRUE);	// ʹ������Ч
}







void CBWndBase::PictureSetIcon( EStandardIcon iconStd )
{
	HANDLE hIco = (HANDLE)LoadIcon(NULL, (LPCTSTR)iconStd);
	PictureSet(hIco, eImgIcon);
}

void CBWndBase::PictureSetIcon( UINT iconResID, LPCTSTR typeRes/*=0*/ )
{
	HANDLE hIco = 0; 
	if (typeRes==0)
	{
		// ���� Icon ���͵���Դ
		hIco = LoadImage(pApp->hInstance, (LPCTSTR)iconResID, IMAGE_ICON, 0, 0, LR_SHARED);	
	}
	else
	{
		// �����Զ������͵���Դ��typeRes ���͵���Դ��
		unsigned long size=0; 
		unsigned char * p= LoadResData(iconResID, typeRes, &size);
		hIco = CreateIconFromResource(p, size, 0, 0x00030000);
	}
	PictureSet(hIco, eImgIcon);	
}

void CBWndBase::PictureSetIcon( LPCTSTR iconFile )
{
	HANDLE hIco = LoadImage(NULL, iconFile, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	PictureSet(hIco, eImgIcon);	
}









bool CBWndBase::PrintText( LPCTSTR sText, int x/*=-65536*/, int y/*=-65536*/, bool fLineFeed/*=true*/, 
						  bool fBkTransparent/*=true*/, bool fSingleLine/*=true*/ )
{
	HDC hDC = GetDC(m_hWnd);
	HFONT hFont = GetFontMLF(), hFontOld = NULL;
	RECT rcClip;

	m_pPro = PropMem(true);
		// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro==NULL) return false; 
		// ������������Ϊ true���� m_pPro ��Ϊ NULL ��ʾ����

	// ======== ѡ������ ========
	if (hFont)
		hFontOld = (HFONT)SelectObject(hDC, hFont);
	// else �� hFont==NULL����ѡ�����壬�� hDC �е�Ĭ������
	
	// ======== ����������ɫ�ͱ��� ========
	if ( -1 != m_pPro->foreColor )
		SetTextColor (hDC, m_pPro->foreColor);
	if (fBkTransparent)
		SetBkMode(hDC, TRANSPARENT);	// ���ֱ���͸��
	else
		SetBkMode(hDC, OPAQUE);			// ���ֱ�����͸��
	
	// ======== ���������Χ ========
	if ( x > -65536 )  
	{ 
		m_pPro->rcTextOutClip.left = x;  
		m_pPro->iTextOutStartLeft = x; 
	}  // ���򱣳�ԭ����ʾ�ϴ�������״̬
	
	if ( y > -65536 )  
		m_pPro->rcTextOutClip.top = y;  
	   // ���򱣳�ԭ����ʾ�ϴ�������״̬
	
	rcClip.left = m_pPro->rcTextOutClip.left;
	rcClip.top = m_pPro->rcTextOutClip.top;
	rcClip.right = m_pPro->rcTextOutClip.right;
	rcClip.bottom = m_pPro->rcTextOutClip.bottom;
	
	// m_pPro->rcTextOutClip.right��m_pPro->rcTextOutClip.bottom ������ PrintTextFormat() �����ù�
	//   �ֿ��� <=0 ���Զ���֮����Ϊ�ͻ�����С
	if (m_pPro->rcTextOutClip.right<=0 || m_pPro->rcTextOutClip.bottom<=0)
	{
		RECT rc;
		GetClientRect(m_hWnd, &rc);
		if (m_pPro->rcTextOutClip.right <= 0) rcClip.right = rc.right;
		if (m_pPro->rcTextOutClip.bottom <= 0) rcClip.bottom = rc.bottom;
		// ���޸� m_TextOutClip������ <=0 ��Ϊ�Զ����������ΧΪ�ͻ�����С�ı�־
		//   �����С���ܸı䣬��Ҳ <=0����ʱ�´����ʱ�������ΧҲӦ��Ӧ�ı�
	}
	
	// ======== ��ӡ�ı� ========
	RECT rcText;
	// ��ô�ӡ�ı��Ŀ�Ⱥ͸߶� => rectText
    DrawText(hDC, sText, -1, &rcText, DT_CALCRECT);
	// ��ӡ�ı�
	if (fSingleLine)
		DrawText(hDC, sText, -1, &rcClip, m_pPro->iTextOutFlags | DT_SINGLELINE);
	else
		DrawText(hDC, sText, -1, &rcClip, m_pPro->iTextOutFlags & ~DT_SINGLELINE);
	
	// ======== �����´����λ�� => m_TextOutClip ========
	if (fLineFeed)
	{
		m_pPro->rcTextOutClip.top += (rcText.bottom - rcText.top);
		m_pPro->rcTextOutClip.left = m_pPro->iTextOutStartLeft;	// ������߽���ӦΪԭʼ��ʼ��߽�
	}
	else
	{
		m_pPro->rcTextOutClip.left += (rcText.right - rcText.left); 
		// �ı�����߽磬�Ժ���ʱ�ɻָ���߽�Ϊ m_TextOutStartLeft
		if ( m_pPro->rcTextOutClip.left > rcClip.right )
		{
			// ��ȳ�����Χ�������ƶ�һ��
			m_pPro->rcTextOutClip.top += (rcText.bottom - rcText.top);
			m_pPro->rcTextOutClip.left = m_pPro->iTextOutStartLeft;  // ������߽���ӦΪԭʼ��ʼ��߽�
		}
	}
	
	// ======== �ͷ���Դ ========
	if (hFontOld) SelectObject(hDC, hFontOld);
	ReleaseDC(m_hWnd, hDC);	

	return true;
}

bool CBWndBase::PrintText( tstring stringText, int x/*=-65536*/, int y/*=-65536*/, bool fLineFeed/*=true*/, bool fBkTransparent/*=true*/, bool fSingleLine/*=true*/ )
{
	return PrintText(stringText.c_str(), x, y, fLineFeed, fBkTransparent, fSingleLine);
}

bool CBWndBase::PrintTextFormat( int clipX/*=0*/, int clipY/*=0*/, int clipWidth/*=-1*/, int clipHeight/*=-1*/, 
								EAlign align/*=eAlignLeft*/, EVAlign valign/*=eVAlignVCenter*/, 
								bool fEndEllipsis/*=false*/, bool fPathEllipsis/*=false*/, 
								bool fANDPrefix/*=true*/, bool bEditControlStyle/*=false*/, int iTabSpace/*=8*/ )
{
	m_pPro = PropMem(true);
		// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro==NULL) return false; 
		// ������������Ϊ true���� m_pPro ��Ϊ NULL ��ʾ����

	SetRect(&m_pPro->rcTextOutClip, clipX, clipY, clipX+clipWidth, clipY+clipHeight);
	if (clipWidth<0) m_pPro->rcTextOutClip.right = -1;
	if (clipHeight<0) m_pPro->rcTextOutClip.bottom = -1;


	m_pPro->iTextOutFlags = 0;
	m_pPro->iTextOutFlags |= align;
	m_pPro->iTextOutFlags |= valign;
	if (fEndEllipsis) m_pPro->iTextOutFlags |= DT_END_ELLIPSIS;
	if (fPathEllipsis) m_pPro->iTextOutFlags |= DT_PATH_ELLIPSIS;
	if (!fANDPrefix) m_pPro->iTextOutFlags |= DT_NOPREFIX;
	if (bEditControlStyle) m_pPro->iTextOutFlags |= DT_EDITCONTROL;
	if (iTabSpace) 
	{
		m_pPro->iTextOutFlags |= DT_EXPANDTABS;
		if (iTabSpace!=8)
		{
			m_pPro->iTextOutFlags |= DT_TABSTOP;
			m_pPro->iTextOutFlags |= (iTabSpace<<8);
		}
	}	

	return true;
}






void CBWndBase::Cls()
{
	// ������ͨ�� InvalidateRect��WM_PAINT ʱʵ�� Cls �Ĺ���
	// �� InvalidateRect ֮ǰ�������ø������Ե� fFromCls ��־Ϊ true
	//  ����Ӧ WM_PAINT ʱ�����˳�ԱΪ true �������� Paint �¼�
	//  ������ Paint �¼��������û��ֵ��� Cls ������ݹ�

	// �������� fFromCls ��־�����޷����丽�����Կռ䣬����
	m_pPro = PropMem(true);
		// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro==NULL) return; 
		// ������������Ϊ true���� m_pPro ��Ϊ NULL ��ʾ����
	
	m_pPro->fFromCls = true;
	SetRect(&m_pPro->rcTextOutClip, 0, 0, 0, 0);
	m_pPro -> iTextOutStartLeft = 0;

	InvalidateRect(m_hWnd, NULL, TRUE);

// 	HDC hDC = GetDC(m_hWnd);
// 	HBRUSH hBrush = CreateSolidBrush(BackColor());
// 	RECT rectBK;
// 	
// 	GetClientRect(m_hWnd, &rectBK);
// 	FillRect(hDC, &rectBK, hBrush);
// 	
// 	DeleteObject(hBrush);
// 	ReleaseDC(m_hWnd, hDC);
}








bool CBWndBase::RefreshPicture( HDC hDC, int xEdge/*=0*/, int yEdge/*=0*/ )
{
	m_pPro = PropMem(false);
	if (! m_pPro) return false;				// ���� false ��ʾ�����ؼ�û�����ù�ͼƬ
	
	HBITMAP hBmp = m_pPro->hBmpDisp;		// ���ԭʼ��С��λͼ���
	if (! hBmp) return false;				// ���� false ��ʾ�����ؼ�û�����ù�ͼƬ
	
	HDC hDcMem = CreateCompatibleDC(hDC);
	HBITMAP hBmpOld = (HBITMAP)SelectObject(hDcMem, hBmp);
	BITMAP bm;
	int xSrc=0, ySrc=0, widSrc=0, heiSrc=0;	// Ҫ���Ƶ��ؼ���λͼ�еķ�Χ
	
	GetObject(hBmp, sizeof(bm), &bm);
	
	// ��� pProp->rcPicture ��ָ���� left��top�����ڵ��� xSrc��ySrc
	if ( m_pPro->rcPictureClip.left >= 0) 
		xSrc = m_pPro->rcPictureClip.left;
	if ( m_pPro->rcPictureClip.top >= 0) 
		ySrc = m_pPro->rcPictureClip.top;
	
	// ���� widSrc��heiSrc������������Ϊ�ұ߽硢�±߽磬�������Ƿֱ��ȥ xSrc��ySrc
	//   ��ָ���� pProp->rcPicture �е� left��top ��δָ�� right��bottom ʱ��
	//   ������ left��top ��ʼ��λͼ�߽�Ĳ���
	if ( m_pPro->rcPictureClip.right >= 0) 
		widSrc = m_pPro->rcPictureClip.right;	
	else 
		widSrc = bm.bmWidth;
	
	if ( m_pPro->rcPictureClip.bottom >= 0) 
		heiSrc = m_pPro->rcPictureClip.bottom;
	else
		heiSrc = bm.bmHeight;
	
	widSrc -= xSrc;
	heiSrc -= ySrc;
	
	// ����λͼ���ؼ�
	if ( m_pPro->stretch )
	{
		SetStretchBltMode(hDC, HALFTONE);
		StretchBlt(hDC, xEdge, yEdge, ClientWidth()-xEdge, ClientHeight()-yEdge, 
			hDcMem, xSrc,ySrc,widSrc,heiSrc, SRCCOPY);
	}
	else
	{
		BitBlt(hDC, xEdge, yEdge, widSrc-xEdge, heiSrc-yEdge, 
			hDcMem, xSrc, ySrc, SRCCOPY);
	}
	
	// �����ʱ��Դ
	SelectObject(hDcMem, hBmpOld);
	DeleteDC(hDcMem);

	return true; // ���� true ��ʾ�����ؼ����ù�ͼƬ������������ͼƬ
}









// ================================================
// �߼�
// ================================================


bool CBWndBase::Transparent()
{
	if (StyleEx() & WS_EX_TRANSPARENT) return true; else return false;
}

void CBWndBase::TransparentSet( bool bTransparent )
{
	if (bTransparent)
		StyleExSet(WS_EX_TRANSPARENT);
	else
		StyleExSet(WS_EX_TRANSPARENT, -1);
}	

int CBWndBase::Opacity()
{
	typedef BOOL (WINAPI *PFUNType)(HWND, COLORREF *, BYTE *, DWORD *);

	if (StyleEx() & WS_EX_LAYERED)
	{
		PFUNType pfun = NULL;
		pfun = (PFUNType)GetProcAddress(GetModuleHandle(TEXT("USER32.dll")), 
			"GetLayeredWindowAttributes");
		if (pfun == 0) return -2;	// �޷���� GetLayeredWindowAttributes ��������ڵ�ַ

		BYTE ret; DWORD retFlags; 
		(*pfun)(m_hWnd, 0, &ret, &retFlags);
		if (retFlags & LWA_ALPHA)
			return (int)ret; 
		else
			return -1;	// ����δ�����ô���ʽ
	}
	else
	{
		return -1;		// ����δ�����ô���ʽ
	}
}

void CBWndBase::OpacitySet( int iOpacity )
{
	typedef BOOL (WINAPI *PFUNType)(HWND, COLORREF, BYTE, DWORD);

	if (iOpacity < 0)
	{
		// ȡ�� WS_EX_LAYERED ��ʽ
		StyleExSet(WS_EX_LAYERED, -1);
	}
	else
	{
		PFUNType pfun = NULL;
		pfun = (PFUNType)GetProcAddress(GetModuleHandle(TEXT("USER32.dll")), 
			"SetLayeredWindowAttributes");
		if (pfun == 0) return;	// �޷���� SetLayeredWindowAttributes ��������ڵ�ַ

		BYTE byt = (BYTE)iOpacity;
		// ���� WS_EX_LAYERED ��ʽ
		StyleExSet(WS_EX_LAYERED, 1);
		if (iOpacity > 255) iOpacity = 255;	// ���Ʒ�Χ�� 0��255
		(*pfun)(m_hWnd, 0, byt, LWA_ALPHA);
	}
}

COLORREF CBWndBase::TransparencyKey()
{
	typedef BOOL (WINAPI *PFUNType)(HWND, COLORREF *, BYTE *, DWORD *);

	if (StyleEx() & WS_EX_LAYERED)
	{
		PFUNType pfun = NULL;
		pfun = (PFUNType)GetProcAddress(GetModuleHandle(TEXT("USER32.dll")), 
			"GetLayeredWindowAttributes");
		if (pfun == 0) return -2;	// �޷���� GetLayeredWindowAttributes ��������ڵ�ַ

		BYTE ret; DWORD retFlags; COLORREF color;
		(*pfun)(m_hWnd, &color, &ret, &retFlags);
		if (retFlags & LWA_COLORKEY)
			return (int)ret; 
		else
			return -1;	// ����δ�����ô���ʽ
	}
	else
	{
		return -1;		// ����δ�����ô���ʽ
	}
}

void CBWndBase::TransparencyKeySet(COLORREF iTransColor)
{
	typedef BOOL (WINAPI *PFUNType)(HWND, COLORREF, BYTE, DWORD);
	
	if (iTransColor < 0)
	{
		// ȡ�� WS_EX_LAYERED ��ʽ
		StyleExSet(WS_EX_LAYERED, -1);
	}
	else
	{
		PFUNType pfun = NULL;
		pfun = (PFUNType)GetProcAddress(GetModuleHandle(TEXT("USER32.dll")), 
			"SetLayeredWindowAttributes");
		if (pfun == 0) return;	// �޷���� SetLayeredWindowAttributes ��������ڵ�ַ
		
		// ���� WS_EX_LAYERED ��ʽ
		StyleExSet(WS_EX_LAYERED, 1);
		(*pfun)(m_hWnd, iTransColor, 0, LWA_COLORKEY);
	}
}



int CBWndBase::TitleBarBehavior()
{
	m_pPro = PropMem(false);
	if (m_pPro==NULL)   // δ���ù�����
		return false;
	else
		return m_pPro->iTitleBarBehav;

}

void CBWndBase::TitleBarBehaviorSet( int iBehav/*=1*/ )
{
	m_pPro = PropMem(true);
		// ����Ϊ true����û�����ù��������ԣ����ڿ��ٸ������ԵĿռ�
	if (m_pPro) m_pPro->iTitleBarBehav = true;

	// ���ӷ�� SS_NOTIFY����������Ӧ MouseMove ����Ϣ
	if (iBehav && IsClassName(TEXT("Static")))
		StyleSet(SS_NOTIFY, 1);
}



// ��ô��ڵ�����������ͨ��ָ��ı������ַ��������ݣ�
const TCHAR * CBWndBase::ClassName() const
{
	return m_ClassName;
}


bool CBWndBase::IsClassName( LPCTSTR lpTestClassName ) const
{
	return (_tcscmp(m_ClassName, lpTestClassName)==0); 
}

bool CBWndBase::IsClassName( tstring stringTestClassName ) const
{
	return IsClassName(stringTestClassName.c_str());
}



unsigned long CBWndBase::Style()
{
	return (unsigned long)GetWindowLong(m_hWnd, GWL_STYLE);
}

void CBWndBase::StyleSet( unsigned long newStyle, int bOr/*=1*/ )
{
	unsigned long r, rNew;
	r = (unsigned long)GetWindowLong(m_hWnd, GWL_STYLE);
	if (bOr > 0) 
		rNew = r | newStyle;	// �� bOr > 0�� �������з��������
	else if (bOr < 0)
		rNew = r & ~newStyle;	// �� bOr < 0���������з����ȡ�� newStyle
	else	// bOr == 0
		rNew = newStyle;		// �� bOr == 0�������з���Ϊ newStyle

	if (rNew != r) 
		SetWindowLong(m_hWnd, GWL_STYLE, (LONG)rNew);	
}

unsigned long CBWndBase::StyleEx()
{
	return (unsigned long)GetWindowLong(m_hWnd, GWL_EXSTYLE);	
}

void CBWndBase::StyleExSet( unsigned long newStyleEx, int bOr/*=1*/ )
{
	unsigned long r, rNew;
	r = (unsigned long)GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if (bOr > 0) 
		rNew = r | newStyleEx;	// �� bOr > 0�� ����������չ���������
	else if (bOr < 0)			
		rNew = r & ~newStyleEx;	// �� bOr < 0������������չ�����ȡ�� newStyleEx
	else
		rNew = newStyleEx;		// �� bOr < 0������������չ�����ȡ�� newStyleEx

	if (rNew != r) 
		SetWindowLong(m_hWnd, GWL_EXSTYLE, (LONG)rNew);
}




// ================================================
// ����
// ================================================

void CBWndBase::Refresh()
{
	SetWindowPos(m_hWnd, 0, 0, 0, 0, 0, 
		SWP_FRAMECHANGED | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE); 
	InvalidateRect(m_hWnd, NULL, 1);
}

void CBWndBase::SetFocus()
{
	::SetFocus(m_hWnd);		// ����ȫ�� API �������뱾����ͬ����
}

void CBWndBase::ZOrder( int position/*=0*/ )
{
	// ���ô��ڻ�ؼ��� Z-˳�򣬼��Ǹ��������ؼ������Ǳ������ؼ�������
	// position=0����λ�������ؼ�����ǰ�棻���� λ�������
	if (m_hWnd==NULL) return;
	UINT flags = SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE;
	if (position==0)
		SetWindowPos(m_hWnd, HWND_TOP, 0, 0, 0, 0, flags);
	else
		SetWindowPos(m_hWnd, HWND_BOTTOM, 0, 0, 0, 0, flags);
}












void CBWndBase::Cut()
{
	SendMessage(m_hWnd, WM_CUT, 0, 0);
}

void CBWndBase::Copy()
{
	SendMessage(m_hWnd, WM_COPY, 0, 0);
}

void CBWndBase::Paste()
{
	SendMessage(m_hWnd, WM_PASTE, 0, 0);
}






void CBWndBase::ClearWndBase()
{
	m_hWnd = NULL;
	HM.ZeroMem(m_ClassName, sizeof(m_ClassName));
	m_atom = 0;
	m_pPro = NULL;
}




