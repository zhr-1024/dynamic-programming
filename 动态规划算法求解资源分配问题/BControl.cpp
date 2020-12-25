//////////////////////////////////////////////////////////////////////
// BControl.cpp: CBControl ���ʵ��
// ʵ�ֶԻ����е�һ���ؼ��ĸ��ֹ���
//   
//////////////////////////////////////////////////////////////////////

#include <tchar.h>
#include <stdio.h>	// �� _stprintf
#include "BForm.h"

// ����ģ��ʹ�õ�ȫ�ֿմ��ַ����ռ�
TCHAR mEmptyStr[2]={0};	


// ���캯��
CBControl::CBControl( unsigned short int idResControl /*=0*/)
					 // ���� CBWndBase �ĵ�1���������ؼ�hWnd���Ժ��� SetResID() ����
					 // ���� CBWndBase �ĵ�3��������Ϊ NULL�����Կռ�ĵ�ַ��Ҫʱ������Զ����
{
	SetResID(idResControl);
}

CBControl::CBControl( HWND hWndCtrl /*= NULL*/ )
					  // ���� CBWndBase �ĵ�1���������ؼ�hWnd���Ժ��� SetResID() ����
					  // ���� CBWndBase �ĵ�3��������Ϊ NULL�����Կռ�ĵ�ַ��Ҫʱ������Զ����
{
	SetResID(hWndCtrl);	
}


// ��������
CBControl::~CBControl()
{
	// ��ֹһ���ͷ�ϵͳ��Դ�������� CBControl �Ƕ�̬�󶨵�
	//   �������ж��ʱ����Ӧ�Ŀؼ���һ����ж��
	;
}



HWND CBControl::SetResID( unsigned short int idResControl/*=0*/ )
{
	HWND hWndCtrl;
	
	// ��¼ m_ResCtrlID����������ú����ذ�� SetResID �����ظ�����
	m_ResCtrlID = idResControl;
	
	// ��ÿؼ� hWnd�������Ǵ� ms_hashCtrlResIDs ��ϣ���а��� ID ���
	// ���֮ǰ��������˴��壬���ڼ����� EnumChildProcSubClass��
	//   �ڴ˹�ϣ��������˿ؼ� ID ��Ϣ
	hWndCtrl = (HWND)CBWndBase::ms_hashCtrlResIDs.Item((long)idResControl, false);

	// �������ذ�� SetResID ����2������Ϊ�ؼ����������
	// ��� hWndCtrl Ϊ NULL�����溯�������� m_ResCtrlID Ϊ 0
	return SetResID(hWndCtrl);
}


HWND CBControl::SetResID( HWND hWndCtrl/*=NULL*/ )
{
	ClearWndBase();		// �����Ա��������

	// ==== ���ݲ������ó�Ա���� ====
	if (hWndCtrl)
	{
		// �������Ϣ��¼����Ա����
		m_hWnd = hWndCtrl;
		
		// ������Ψһ��ʶ Atom
		m_atom = GetClassLong(hWndCtrl, GCW_ATOM);
		
		// ��������ַ��� => m_ClassName
		GetClassName(m_hWnd, m_ClassName, sizeof(m_ClassName)/sizeof(TCHAR)-1);

		// �� m_ResCtrlID ��Ϊ 0��˵�������ù���������������ֵ��
		// ��������ͨ�� GetDlgCtrlID ����
		if (! m_ResCtrlID) m_ResCtrlID=GetDlgCtrlID(hWndCtrl);
	}
	else
	{
		// hWndCtrl Ϊ NULL������ m_ResCtrlID Ϊ0����Ҫ�� m_ResCtrlID ������
		m_ResCtrlID = 0;
	}

	return hWndCtrl;
}



void CBControl::EnabledSet( bool enabledValue )
{
	EnableWindow(m_hWnd, (BOOL)enabledValue);

	// �����ͼƬ��ť�����ڰ�ť����ʾ��ʾ��Ӧ Enabled ״̬��ͼƬ
	m_pPro = PropMem(false);
	if (m_pPro)
	{
		if (m_pPro->ePicBtn)
		{
			if (enabledValue) PicButtonStateSet(0); else PicButtonStateSet(4, -1);
		}
	}
}





// ���� CBControl ���� TextInt��
// Text��TextVal �̳� CBWndBase ����
int CBControl::TextInt(BOOL * retSuccess/*=0*/)
{
	return GetDlgItemInt(GetParent(m_hWnd), m_ResCtrlID, retSuccess , 1);	
}





// =================== Static ��ؼ��Ĺ��� ===================


bool CBControl::BackStyleTransparent()
{
	m_pPro = PropMem(false);
	if (m_pPro) 
		return m_pPro->bBackStyleTransparent;
	else
		return false;
}

void CBControl::BackStyleTransparentSet( bool bTransparent )
{
	m_pPro = PropMem(true);
	if (m_pPro) m_pPro->bBackStyleTransparent = bTransparent;
}


// ����һ�� Static �ؼ�ΪͼƬ��ť��
//    ��ť��СΪ�ؼ� Width��Height������ť״̬��λͼ���Ϊһ�Ŵ�λͼ�����λͼ��ԴIDΪ bmpCombResID
// bmpCombResID=0 ʱ��ʹ�� PictureSet() ���õ�λͼ
// btnX, btnY, btnWidth, btnHeight ΪͼƬ��ť��λ�á���С���� >=0 ���Զ������ؼ���СΪ��ֵ����4������ֻΪ���ñ�����ʱ
//   �Զ����ÿؼ�λ�á���С��
// iStateStyle = 1ʱ��ʹ����̬��ť������һ�ΰ��¡��ٵ���һ��̧�𣻿��� ValueChecked() ����䰴��/̧�� ״̬
void CBControl::PicButtonSet( EPicButtonType style/*=epbNone*/, UINT bmpCombResID/*=0*/, 
							 int btnWidth/*=-1*/, int btnHeight/*=-1 */, int btnX/*=-1*/, int btnY/*=-1*/, 
							 int iStateStyle/*=0*/)
{
	if (bmpCombResID) PictureSet(bmpCombResID);
	if (btnX>=0 && btnY>=0 && btnWidth>=0 && btnHeight>=0)
	{
		// btnX��btnY��btnWidth��btnHeight �ĸ�����ȫ������
		// ͨ�� Move ���ÿؼ�λ�á���С�������Ч��
		Move(btnX, btnY, btnWidth, btnHeight);
	}
	else
	{
		// ֻ�ֱ���� Left��Top��Width��Height ��һ���ֲ���������ֱ�����
		if (btnX>=0) LeftSet(btnX);
		if (btnY>=0) TopSet(btnY);
		if (btnWidth>=0) WidthSet(btnWidth);
		if (btnHeight>=0) HeightSet(btnHeight);
	}

	// ���ø�������Ϊ��ͼƬ��ť
	m_pPro = PropMem(true);	// ������Կռ�ĵ�ַ
	if (m_pPro)
	{
		m_pPro->ePicBtn = style;
		m_pPro->iPicBtnStateStyle = iStateStyle;
	}
	
	// Static �ؼ��� SS_NOTIFY ������� EnumChildProcSubClass �����

	// ��ʾ���水ť״̬
	PicButtonStateSet(0);
}



// ����ͼƬ��ť��״̬��0=���棻1=������2=���£�3=��ɫ
// iSetOrReleaseCapture���Ƿ�ͬʱ SetCapture (=1) �� ReleaseCapture(=-1) ���� (=0)
// �� iSetOrReleaseCapture ��0��������ζ����� SetCapture �� ReleaseCapture
// �����������ÿؼ������״̬��Ҫ���� Checked ״̬����ʹ�� ValueCheckedSet()
void CBControl::PicButtonStateSet( int iState, int iSetOrReleaseCapture/*=0*/ )
{
	// SetCapture �� ReleaseCapture
	if (iSetOrReleaseCapture>0) SetCapture(m_hWnd);
	else if (iSetOrReleaseCapture<0) ReleaseCapture(); 

	
	m_pPro = PropMem(true);	// ������Կռ�ĵ�ַ
	if (!m_pPro) return; 
	if (m_pPro->iPicBtnCurrDisp == iState) return;  // �����ǰ�Ѿ���ʾΪ ����״̬���Ͳ��ظ���ʾ��
	

	RECT rc;  
	unsigned uMaskClpLeft=0, uMaskClpTop=0;    // ���ڼ��� rcPictureClip.Left �� .Top ������
	unsigned uMoveLeft=0, uMoveTop=0;	// ���ڼ��� rcPictureClip.Left �� .Top �� >> ��λλ�� 
	GetWindowRect(m_hWnd, &rc);			// rect.right - rect.left Ϊ�ؼ� width	
										// rect.bottom - rect.top Ϊ�ؼ� height


	// ����Ҫ��ʾ��ͬ��״̬���������� => uMaskClpLeft,uMaskClpTop
	switch(iState)
	{
	case 0:		// ����
		uMaskClpLeft = 0xf000;	uMaskClpTop = 0xf0000000;
		uMoveLeft = 12;			uMoveTop = 28;
		break;
	case 1:		// ����
		uMaskClpLeft = 0x0f00;	uMaskClpTop = 0x0f000000;
		uMoveLeft = 8;			uMoveTop = 24;
		break;
	case 2:		// ����
		uMaskClpLeft = 0x00f0;	uMaskClpTop = 0x00f00000;
		uMoveLeft = 4;			uMoveTop = 20;
		break;
	case 3:		// ��ɫ
		uMaskClpLeft = 0x000f;	uMaskClpTop = 0x000f0000;
		uMoveLeft = 0;			uMoveTop = 16;
		break;
	default:
		return;
	}
	
	// ���ñ�ʾͼƬ��ť״̬������
	m_pPro->rcPictureClip.left = (((UINT)m_pPro->ePicBtn & uMaskClpLeft)>>uMoveLeft) * (rc.right - rc.left); 
	m_pPro->rcPictureClip.top = (((UINT)m_pPro->ePicBtn & uMaskClpTop)>>uMoveTop) * (rc.bottom - rc.top);
	m_pPro->rcPictureClip.right = -1;
	m_pPro->rcPictureClip.bottom = -1;
	
	m_pPro->iPicBtnCurrDisp = iState;	// ��¼��ǰ�Ѿ���ʾΪ ����״̬


	// ���� WM_PAINT �л���λͼ��ͼƬ��ť��״̬���ֳ�������֧�� Stretch��
	InvalidateRect(m_hWnd, NULL, TRUE);	
}


int CBControl::PicButtonState()
{
	m_pPro = PropMem(true);	// ������Կռ�ĵ�ַ
	if (!m_pPro) return -1; else return m_pPro->iPicBtnCurrDisp;
}




// =================== Edit��Rich Edit ��ؼ��Ĺ��� ===================


int CBControl::SelStart(int *pLineIdx/*=NULL*/)
{
	if ( IsClassName(TEXT("Edit")) )
	{
		if (pLineIdx)  // �����к�
			(*pLineIdx) = SendMessage(m_hWnd, EM_LINEFROMCHAR, -1, 0);

		int iStart=-1, iEnd=-1;
		SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&iStart, (LPARAM)&iEnd);
		if (iStart<0) return -1; else return iStart;
	}
	else if ( IsClassName( TEXT("ComboBox") ) )
	{
		int iStart=-1, iEnd=-1;
		SendMessage(m_hWnd, CB_GETEDITSEL, (WPARAM)&iStart, (LPARAM)&iEnd);
		if (iStart<0) return -1; else return iStart;
		// pLineIdx �� ComboBox ��Ч
	}
	else if ( IsClassName( TEXT("ListBox") ) )
	{
		// ���� anchor item index
		// A multiple selection spans all items from the anchor item to the caret item.
		return SendMessage(m_hWnd, LB_GETANCHORINDEX, 0, 0) + 1; // +1 ת��Ϊ��Ŵ�1��ʼ
	}
	else if (_tcsstr(ClassName(), TEXT("RICHEDIT")))	// �� Rich Edit �ؼ��ķ�ʽ����
	{
		CHARRANGE cr;
		SendMessage(m_hWnd, EM_EXGETSEL, 0, (LPARAM)&cr);
		if (pLineIdx)  // �����к�
			(*pLineIdx) = SendMessage(m_hWnd, EM_EXLINEFROMCHAR, 0, cr.cpMin);
		return cr.cpMin;
	}
	else
		return -1;	// ��֧�ָÿؼ�
}

int CBControl::SelLength()
{
	if ( IsClassName(TEXT("Edit")) )
	{
		int iStart=-1, iEnd=-1;
		SendMessage(m_hWnd, EM_GETSEL, (WPARAM)&iStart, (LPARAM)&iEnd);
		if (iStart<0 || iEnd<0) return -1; else return iEnd-iStart;	
	}
	else if ( IsClassName( TEXT("ComboBox") ) )
	{
		int iStart=-1, iEnd=-1;
		SendMessage(m_hWnd, CB_GETEDITSEL, (WPARAM)&iStart, (LPARAM)&iEnd);
		if (iStart<0 || iEnd<0) return -1; else return iEnd-iStart;	
		// pLineIdx �� ComboBox ��Ч
	}
	else if ( IsClassName( TEXT("ListBox") ) )
	{
		// A multiple selection spans all items from the anchor item to the caret item.
		int idxAnchor = SendMessage(m_hWnd, LB_GETANCHORINDEX, 0, 0) + 1; // +1 ת��Ϊ��Ŵ�1��ʼ
		int idxCaret = SendMessage(m_hWnd, LB_GETCARETINDEX, 0, 0) + 1; // +1 ת��Ϊ��Ŵ�1��ʼ
		return idxCaret - idxAnchor + 1;
	}
	else if (_tcsstr(ClassName(), TEXT("RICHEDIT")))	// �� Rich Edit �ؼ��ķ�ʽ����
	{
		CHARRANGE cr;
		SendMessage(m_hWnd, EM_EXGETSEL, 0, (LPARAM)&cr);
		return cr.cpMax - cr.cpMin;
	}
	else
		return -1;	// ��֧�ָÿؼ�
}


void CBControl::SelSet( int selStart/*=0*/, int selLength/*=-1*/ )
{
	if (IsClassName(TEXT("Edit")))
	{
		SendMessage(m_hWnd, EM_SETSEL, (WPARAM)selStart, (LPARAM)(selStart+selLength));
	}
	else if ( IsClassName( TEXT("ComboBox") ) )
	{
		SendMessage(m_hWnd, CB_SETEDITSEL, 0, MAKELPARAM(selStart, selStart+selLength));
	}
	else if ( IsClassName( TEXT("ListBox") ) )
	{
		// List Box ������ж�ѡ��񣬱��������ܳɹ�
		if (selStart==0 && selLength==-1) 
		{ selStart=1; selLength=ListCount();} // ȫѡ

		if (selStart<1) selStart=1;

		if (selLength>0)	// wParam С��lParam ��ѡ����Ŀ
			SendMessage(m_hWnd, LB_SELITEMRANGEEX, WPARAM(selStart-1),LPARAM(selStart-1+selLength-1));
		else				// lParam С��wParam ��ȡ��ѡ����Ŀ
			SendMessage(m_hWnd, LB_SELITEMRANGEEX, WPARAM(selStart-1-selLength-1),LPARAM(selStart-1));
	}
	else if (_tcsstr(ClassName(), TEXT("RICHEDIT")))	// �� Rich Edit �ؼ��ķ�ʽ����
	{
		CHARRANGE cr;
		cr.cpMin = selStart; cr.cpMax = selStart+selLength;
		SendMessage(m_hWnd, EM_EXSETSEL, 0, (LPARAM)&cr);
	}
}


void CBControl::SelTextSet( LPCTSTR stringRepl, bool bCanUndo /*=true*/ )
{
	SendMessage(m_hWnd,  EM_REPLACESEL, (WPARAM)bCanUndo, (LPARAM)stringRepl );
}

void CBControl::SelTextSet( tstring stringRepl, bool bCanUndo/*=true*/ )
{
	SelTextSet(stringRepl.c_str(), bCanUndo);
}


int CBControl::FindText( LPTSTR stringFind, int rgStart/*=0*/, int rgLength/*=-1*/, bool bCaseSensitive/*=false*/, bool bMatchWholeWord/*=false*/, bool bAutoSelFound/*=true*/ )
{
	if (_tcsstr(ClassName(), TEXT("RICHEDIT"))==0) return -1;	// ��֧�ֿؼ�
	
	WPARAM wpFlag = FR_DOWN;
	FINDTEXTEX ft;
	int ret;
	if (bCaseSensitive) wpFlag |= FR_MATCHCASE;
	if (bMatchWholeWord) wpFlag |= FR_WHOLEWORD;

	ft.chrg.cpMin = rgStart;
	ft.chrg.cpMax = rgStart+rgLength;
	if (rgStart>0 && rgLength<0) ft.chrg.cpMax=0x7fffffff;  // �� rgStart ��ʼ��ȫ�ı�ĩβ
	
	// ���� stringFind�������Ҫ�Ӹ� \0
	TCHAR * szFind = NULL;
	int iFindLength = _tcslen(stringFind);
	szFind = new TCHAR [iFindLength+2];
	_tcscpy(szFind, stringFind);
	*(szFind+iFindLength)=TEXT('\0');
	ft.lpstrText = szFind; 

	// ����
	ret = (int)SendMessage(m_hWnd, EM_FINDTEXTEX, wpFlag, (LPARAM)&ft );
	
	// ѡ���ҵ����ı�
	if (bAutoSelFound)
		SendMessage(m_hWnd, EM_EXSETSEL, 0, (LPARAM)&ft.chrgText);

	// ����ֵ
	return ret;
}


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
void CBControl::EditSetApperance( unsigned short idPicBorder, unsigned short idBMPBorder, int x, int y, int width, int height, LPTSTR szFontName/*=NULL*/, float fFontSize/*=10.5*/, int xOffset/*=4*/, bool bOnlyMoveSize/*=false*/ )
{
	CBControl ctPicBorder;
	if (! szFontName) szFontName=TEXT("����");  // Ĭ��Ϊ�����塱

	if (!bOnlyMoveSize)
	{
		ctPicBorder.SetResID(idPicBorder);
		ctPicBorder.StretchSet(true);
		ctPicBorder.FontNameSet(szFontName);	// �� picture �ؼ�������Ҳ
		ctPicBorder.FontSizeSet(fFontSize);		//   ����Ϊ�� Edit �ؼ���ͬ
		ctPicBorder.PictureSet(idBMPBorder);
		ctPicBorder.MousePointerSet(IDC_IBeam);	// �� picture �ؼ����Ҳ��Ϊ I ��
	}
	ctPicBorder.Move(x, y, width, height);

	if (!bOnlyMoveSize)
	{
		FontNameSet(szFontName);	// ��������
		FontSizeSet(fFontSize);		// �����ֺ�
 		ZOrder(0);
	}
	Move(x+xOffset, ctPicBorder.Top() + (ctPicBorder.Height()-TextHeight())/2, 
		width-2*xOffset, TextHeight());
}


// =================== ��ť��ؼ��Ĺ��� ===================
// ���غ����õ�ѡ��ѡ��ť�Ƿ񱻹�ѡ�ˣ�0=δѡ��1=��ѡ��2=��̬
// ��Ҳ������ Static �ؼ������ġ�ͼƬ��ť��
unsigned int CBControl::ValueChecked()
{
	m_pPro = PropMem(false);
	if (m_pPro)
	{
		if (m_pPro->ePicBtn)
		{
			// ���ء�ͼƬ��ť���İ��� �� ̧�� ״̬
			return m_pPro->iPicBtnCheckedState;
		}
	}

	// ���ص�ѡ��ѡ��ť��״̬
	return IsDlgButtonChecked(GetParent(m_hWnd), m_ResCtrlID);
}

// ���õ�ѡ��ѡ��ť�Ĺ�ѡ״̬��0=δѡ��1=��ѡ��2=��̬
// Ҫ����Ϊ��2=��̬������ѡ�������� tri-STATE ���
// ��Ҳ������ Static �ؼ������ġ�ͼƬ��ť��
void CBControl::ValueCheckedSet( UINT uCheck )
{
	m_pPro = PropMem(false);
	if (m_pPro)
	{
		if (m_pPro->ePicBtn)
		{
			// ���á�ͼƬ��ť����״̬
			m_pPro->iPicBtnCheckedState = uCheck;
			if (uCheck) PicButtonStateSet(2,0); else PicButtonStateSet(0,0);
			InvalidateRect(m_hWnd, NULL, TRUE);
			return;
		}
	}
	
	// ���õ�ѡ��ѡ��ť��״̬
	CheckDlgButton(GetParent(m_hWnd), m_ResCtrlID, uCheck);
}


// =================== ��Ͽ��б����ؼ��Ĺ��� ===================

// ���һ����Ŀ��������ӵ���Ŀ��ţ���1��ʼ���������� 0
// index=0 ʱ����ĩβ��ӣ�������ָ���� index λ����ӣ����߲����Զ�����
int CBControl::AddItem( LPTSTR szText, int index /*= -1*/, int iImage /*= 0*/, int iTagLong /*= 0*/, int iIndent /*= 0x80000000*/ ) const
{
	// ************************
	// If you create the combo box with an owner-drawn style but without the CBS_HASSTRINGS style, 
	// the value of the lpsz parameter is stored as item data rather than the string it would otherwise point to. 
	
	if ( IsClassName( TEXT("ComboBox") ) )
	{
		// ComboBox
		if (index<=0)
			return SendMessage(m_hWnd, CB_ADDSTRING, 0, (LPARAM)szText)+1;
		else
			return SendMessage(m_hWnd, CB_INSERTSTRING, index-1, (LPARAM)szText)+1;
	}
	else if ( IsClassName( TEXT("ListBox") ) ) 
	{
		// ListBox
		if (index<=0)
			return SendMessage(m_hWnd, LB_ADDSTRING, 0, (LPARAM)szText)+1;
		else
			return SendMessage(m_hWnd, LB_INSERTSTRING, index-1, (LPARAM)szText)+1;
	}
	else if (IsClassName( TEXT("SysListView32") ))
	{
		LVITEM itm;
		itm.mask = LVIF_TEXT | LVIF_PARAM;
		if (iImage != -1) itm.mask |= LVIF_IMAGE;
		if (iIndent != 0x80000000) itm.mask |= LVIF_INDENT;
		if (index <= 0) itm.iItem = 0x7FFFFFFF; else itm.iItem = index - 1;  // ת��Ϊ index ��0��ʼ���
		itm.iSubItem = 0;  // LVM_INSERTITEM ʱ��the iSubItem member of the LVITEM structure must be zero; zero if this structure refers to an item rather than a subitem
		itm.iImage = iImage - 1;
		itm.lParam = iTagLong;
		itm.iIndent = iIndent;
		itm.pszText = (LPTSTR)szText;
		return SendMessage(m_hWnd, LVM_INSERTITEM, 0, (LPARAM)(&itm)) + 1;    // ����ֵת��Ϊ��1��ʼ���
	}

	// �ÿؼ������� AddItem
	return -3;
}

int CBControl::AddItem( tstring stringText, int index /*= -1*/, int iImage /*= 0*/, int iTagLong /*= 0*/, int iIndent /*= 0x80000000*/ ) const
{
	//LPTSTR szText = (LPTSTR)stringText.c_str();
	return AddItem((LPTSTR)stringText.c_str(), index, iImage, iTagLong, iIndent);
}


// ɾ��һ����Ŀ����Ŵ�1��ʼ������ɾ������б�����Ŀ����������0
int CBControl::RemoveItem( int index ) const
{
	if ( IsClassName( TEXT("ComboBox") ) )   
	{
		// ComboBox
		return SendMessage(m_hWnd, CB_DELETESTRING, index-1, 0);
	}
	else if ( IsClassName( TEXT("ListBox") ) )    
	{
		// ListBox
		return SendMessage(m_hWnd, LB_DELETESTRING, index-1, 0);
	}
	else if (IsClassName( TEXT("SysListView32") ))
	{
		SendMessage(m_hWnd, LVM_DELETEITEM, index-1, 0);   // ת��Ϊ index ��0��ʼ���
	}
	
	// �ÿؼ������� RemoveItem
	return -3;
}


// ���ع�����Ŀ����������<0��ֵ
int CBControl::ListCount() const
{
	if ( IsClassName( TEXT("ComboBox") ) )
	{
		// ComboBox
		return SendMessage(m_hWnd, CB_GETCOUNT, 0, 0);
	}
	else if ( IsClassName( TEXT("ListBox") ) )
	{
		// ListBox
		return SendMessage(m_hWnd, LB_GETCOUNT, 0, 0);
	}
	else if ( IsClassName( TEXT("SysListView32") ) )
	{
		return SendMessage(m_hWnd, LVM_GETITEMCOUNT, 0, 0);
	}
	
	// �ÿؼ������� ListCount
	return -3;
}


// ���ص�ǰѡ�����Ŀ��ţ���Ŵ�1��ʼ����������0
// ���Զ�ѡ�б��ʹ�ã��򷵻ص��Ǿ��н������Ŀ���
//   ������Ŀ��û��ѡ��ʱ������1����ʾ��1����Ŀ�н��㣩
int CBControl::ListIndex() const
{

	if ( IsClassName( TEXT("ComboBox") ) )
	{
		// ComboBox
		return SendMessage(m_hWnd, CB_GETCURSEL, 0, 0)+1;	// +1 ��ʾת��Ϊ��Ŵ�1��ʼ
	}
	else if ( IsClassName( TEXT("ListBox") ) )
	{
		// ListBox
		return SendMessage(m_hWnd, LB_GETCURSEL, 0, 0)+1;	// +1 ��ʾת��Ϊ��Ŵ�1��ʼ
	}
	else if ( IsClassName( TEXT("SysListView32") ) )
	{
		return ListViewNextItemIdx(0, false, true);
	}
	// �ÿؼ������� ListIndex
	return -3;
}


// ѡ��һ����Ŀ����Ŀ��Ŵ�1��ʼ
void CBControl::ListIndexSet( int index ) const
{
	if ( IsClassName( TEXT("ComboBox") ) ) 
	{
		// ComboBox
		SendMessage(m_hWnd, CB_SETCURSEL, index-1, 0);
	}
	else if ( IsClassName( TEXT("ListBox") ) )  
	{
		// ListBox
		SendMessage(m_hWnd, LB_SETCURSEL, index-1, 0);
	}
	else if ( IsClassName( TEXT("SysListView32") ) )
	{
		ItemSelectedSet(index, true);
//     Me.SelMarkIndex = vNewValue  // ���� selection mark ΪҪѡ��
	}
	
	// �ÿؼ������� ListIndexSet
}


// ���һ����Ŀ�����ݣ�index��indexSub ���� 1 ��ʼ
// indexSub ������ ListView �ؼ�
LPTSTR CBControl::ItemText( int index/*=-1*/, int indexSub/*=0*/ ) const
{
	// index<0 ʱ��� ListIndex() ���ı�
	if (index<0) index=ListIndex();

	LRESULT ret;
	if ( IsClassName( TEXT("ComboBox") ) )    
	{
		// ********************************************
		// If you create the combo box with an owner-drawn style but without 
		// the CBS_HASSTRINGS style, the buffer pointed to by the lpszBuffer parameter of
		// the message receives the 32-bit value associated with the item (the item data). 

		// ComboBox
		long length = SendMessage(m_hWnd, CB_GETLBTEXTLEN, index-1, 0);
		if (length == CB_ERR) { mEmptyStr[0]=0; return mEmptyStr; }  // ���ؿմ�

		TCHAR * listText = new TCHAR [length + 1];
		HM.AddPtr(listText);
		HM.ZeroMem(listText, sizeof(TCHAR)*(length + 1));
		ret = SendMessage(m_hWnd, CB_GETLBTEXT, index-1, (LPARAM)listText);
		if (ret == CB_ERR)
			{ mEmptyStr[0]=0; return mEmptyStr; }  // ���ؿմ�
		else
			return listText;
	}
	else if  ( IsClassName( TEXT("ListBox") ) )
	{
		// ListBox
		long length = SendMessage(m_hWnd, LB_GETTEXTLEN, index-1, 0);
		if (length == LB_ERR) { mEmptyStr[0]=0; return mEmptyStr; }  // ���ؿմ�

		TCHAR * listText = new TCHAR [length + 1];
		HM.AddPtr(listText);
		HM.ZeroMem(listText, sizeof(TCHAR)*(length + 1));
		ret = SendMessage(m_hWnd, LB_GETTEXT, index-1, (LPARAM)listText);
		if (ret == LB_ERR)
			{ mEmptyStr[0]=0; return mEmptyStr; }  // ���ؿմ�
		else
			return listText;
	}
	else if  ( IsClassName( TEXT("SysListView32") ) )
	{
		// List View
		LVITEM itm;
		TCHAR buff[8192]={0};
		itm.mask = LVIF_TEXT;
		itm.cchTextMax = 8192;
		itm.pszText = buff;
		itm.iItem = index - 1;    // ת��Ϊ�� 0 ��ʼ
		itm.iSubItem = indexSub - 1;
		SendMessage(m_hWnd, LVM_GETITEM, 0, (LPARAM)(&itm));
		
		int len = _tcslen(buff);
		if (len==0)
		{
			// ���� ""
			mEmptyStr[0] = 0;
			return mEmptyStr;
		}
		else
		{
			TCHAR * p = new TCHAR[_tcslen(buff)+1];
			HM.AddPtr(p);
			_tcscpy(p, buff);
			return p;
		}
	}
	
	// �ÿؼ������� List
	return 0;
}


void CBControl::ItemTextSet( int index, LPTSTR szNewText/*=NULL*/, int indexSub/*=0*/ ) const
{
	if ( IsClassName( TEXT("ComboBox") ) || IsClassName( TEXT("ListBox") ))    
	{
		bool blSel = ItemSelected(index) ;
		int idxSel = ListIndex();
		RemoveItem(index);
		AddItem(szNewText, index);
		ItemSelectedSet(index, blSel);
		if (idxSel==index) ListIndexSet(index);
	}
	else if  ( IsClassName( TEXT("SysListView32") ) )
	{
		// �� ����ı�����������ͬ�Ͳ����£�������˸
		LVITEM itm;
		TCHAR buff[8192]={0};
		itm.mask = LVIF_TEXT;
		itm.iItem = index - 1;    // ת��Ϊ�� 0 ��ʼ
		itm.iSubItem = indexSub - 1;
		itm.cchTextMax = 8192;
		itm.pszText = buff;
		SendMessage(m_hWnd, LVM_GETITEM, 0, (LPARAM)(&itm));
		if (_tcscmp(buff, szNewText)==0) return;	// ��������ͬ�Ͳ����£�������˸
		
		itm.mask = LVIF_TEXT;
		itm.iItem = index - 1;    // ת��Ϊ�� 0 ��ʼ
		itm.iSubItem = indexSub - 1;
		itm.pszText = szNewText;
		// .cchTextMax is ignored if the structure specifies item attributes.
		
		SendMessage(m_hWnd, LVM_SETITEM, 0, (LPARAM)(&itm));
	}
}

void CBControl::ItemTextSet( int index, tstring stringNewText/*=NULL*/, int indexSub/*=0*/ ) const
{
	ItemTextSet(index, (LPTSTR)stringNewText.c_str(), indexSub);
}

LPTSTR CBControl::List( int index, int indexSub/*=0*/ ) const
{
	return ItemText(index, indexSub);
}


int CBControl::ItemData( int index ) const
{
	if ( IsClassName( TEXT("ComboBox") ) )    
	{
		return (int)SendMessage(m_hWnd, CB_GETITEMDATA, index-1, 0);
	}
	else if  ( IsClassName( TEXT("ListBox") ) )
	{
		return (int)SendMessage(m_hWnd, LB_GETITEMDATA, index-1, 0);
	}
	else if  ( IsClassName( TEXT("SysListView32") ) )
	{
		LVITEM itm;
		itm.mask = LVIF_PARAM;
		itm.iItem = index-1;  // ת��Ϊ�� 0 ��ʼ
		itm.iSubItem = -1;
		SendMessage(m_hWnd, LVM_GETITEM, 0, (LPARAM)(&itm));
		return itm.lParam;
	}

	// �ÿؼ�����ʹ�� ItemData
	return 0;	
}

void CBControl::ItemDataSet( int index, int itemData )
{
	if ( IsClassName( TEXT("ComboBox") ) )    
	{
		SendMessage(m_hWnd, CB_SETITEMDATA, index-1, (LPARAM)itemData);
	}
	else if  ( IsClassName( TEXT("ListBox") ) )
	{
		SendMessage(m_hWnd, LB_SETITEMDATA, index-1, (LPARAM)itemData);
	}
	else if  ( IsClassName( TEXT("SysListView32") ) )
	{
		LVITEM itm;
		itm.mask = LVIF_PARAM;
		itm.iItem = index-1;  // ת��Ϊ�� 0 ��ʼ
		itm.iSubItem = -1;
		itm.lParam = itemData;
		SendMessage(m_hWnd, LVM_SETITEM, 0, (LPARAM)(&itm));
	}

	// �ÿؼ�����ʹ�� ItemDataSet
}


// ���ض�ѡ�б�����ѡ��Ŀ��
int CBControl::ListSelCount() const
{
	if  ( IsClassName( TEXT("ListBox") ) )
	{
		// ��ѡ�б�򽫷��� 0
		return SendMessage(m_hWnd, LB_GETSELCOUNT, 0, 0);
	}
	else if  ( IsClassName( TEXT("SysListView32") ) )
	{
		return SendMessage(m_hWnd, LVM_GETSELECTEDCOUNT, 0, 0);
	}

	return 0;
	// �ÿؼ������� ListSelCount
}


void CBControl::ItemsCopyToClipboard( bool bOnlySel/*=true*/, LPCTSTR szSpliter/*=TEXT('\t')*/ )
{
	const int c_iStrExpPer = 16383;

	TCHAR * buffResult = NULL;
	int iBuffResultUbound = 0, buffUsedLen = 0;
	int i, j;

	if  ( IsClassName( TEXT("SysListView32") ) )
	{
		LVITEM itm;
		TCHAR buff[8192]={0};
		int iLen = 0, iLenSep = _tcslen(szSpliter);
		int iColCount = ListViewColumnsCount();
		if (iColCount<=0) iColCount=1;	// ����Ӧ��һ�У�iColCount<=0���������ڷ���ϸ������ͼ��ɵ�
		
		iBuffResultUbound = c_iStrExpPer;
		Redim(buffResult, iBuffResultUbound, -1, false);
		if (buffResult==NULL) return;
		buffUsedLen = 0;

		i = ListViewNextItemIdx(0, ! bOnlySel, bOnlySel );	// ��û����һ����ѡ�е���Ŀ������ 0
		while (i)
		{
			// ����� i �е���Ŀ
			itm.mask = LVIF_TEXT;
			itm.iItem = i - 1;    // ת��Ϊ�� 0 ��ʼ
			itm.cchTextMax = 8192;
			itm.pszText = buff;

			for (j=1; j<=iColCount; j++)
			{
				// ��ȡ�� j �е��ı�
				itm.iSubItem = j - 1;
				SendMessage(m_hWnd, LVM_GETITEM, 0, (LPARAM)(&itm));
				iLen = _tcslen(itm.pszText);

				// ���ռ䲻��������ռ�
				if (buffUsedLen+iLen+iLenSep+2 > iBuffResultUbound)	// +2 �����н����� \r\n Ҳ������
				{
					Redim(buffResult, iBuffResultUbound+c_iStrExpPer, iBuffResultUbound, true);
					if (buffResult==NULL) return;
					iBuffResultUbound += c_iStrExpPer;
				}

				// ���ӵ� j �е��ı�
				int aaa=lstrlen(buffResult);
				_tcscat(buffResult, itm.pszText);
				buffUsedLen += iLen;
				
				// �����һ��ʱ�������зָ��� szSpliter
				if (j<iColCount)	
				{
					_tcscat(buffResult, szSpliter);
					buffUsedLen += iLenSep;
				}
			}
			// ���ӻ��з�
			_tcscat(buffResult, TEXT("\r\n"));
			buffUsedLen += 2;

				
			// �����һ����ѡ��Ŀ�������� => i
			i = ListViewNextItemIdx(i, !bOnlySel, bOnlySel);  // ��û����һ����ѡ�е���Ŀ������ 0
		}	// end while (i)

		ClipboardSetText(buffResult);
		Erase(buffResult);
	}	// end else if  ( IsClassName( TEXT("SysListView32") ) )
}


bool CBControl::ItemSelected( int index ) const
{
	if ( IsClassName( TEXT("ListBox") ) ) 
	{
		if ( SendMessage(m_hWnd, LB_GETSEL, index-1, 0) >0 )	// <0 ��ʾ����(-1)������ return false
			return true;
		else
			return false;
	}
	else if ( IsClassName( TEXT("SysListView32") ) )
	{
		LVITEM itm;
		itm.mask = LVIF_STATE;
		itm.stateMask = LVIS_SELECTED;
		itm.iItem = index - 1;			// ת��Ϊ�� 0 ��ʼ
		itm.iSubItem = - 1;
		SendMessage(m_hWnd, LVM_GETITEM, 0, (LPARAM)(&itm));
		if (itm.state & LVIS_SELECTED) return true; else return false;
	}

	return false;

	// �ÿؼ������� ItemSelected��Combo �ؼ������� ItemSelected��
}

void CBControl::ItemSelectedSet( int index, bool bSel ) const
{
	if ( IsClassName( TEXT("ListBox") ) )
	{
		if (index<1) return;	// ����SendMessage: -1 ���ؼ�������ȫ��ѡ�У�ȡ��ѡ�У�
		SendMessage(m_hWnd, LB_SETSEL, (BOOL)bSel, index-1);
	}
	else if ( IsClassName( TEXT("SysListView32") ) )
	{
		LVITEM itm;
		itm.mask = LVIF_STATE;
		itm.stateMask = LVIS_SELECTED;
		itm.iItem = index - 1;			// ת��Ϊ�� 0 ��ʼ
		itm.iSubItem = - 1;
		if (bSel) itm.state = LVIS_SELECTED; else itm.state = 0;
		SendMessage(m_hWnd, LVM_SETITEM, 0, (LPARAM)(&itm));
	}

	// �ÿؼ������� ItemSelectedSet��Combo �ؼ������� ItemSelectedSet��
}


void CBControl::ItemsSelDo( int iSelStyle/*=1*/ )
{
	int i;
	if  ( IsClassName( TEXT("ListBox") ) )
	{
		switch(iSelStyle)
		{
		case 1:  // ȫѡ
			SendMessage(m_hWnd, LB_SETSEL, 1, -1);
			break;
		case 0:  // ȡ��ѡ��
			SendMessage(m_hWnd, LB_SETSEL, 0, -1);
			break;
		case -1:  // ��ѡ
			for(i=0; i<ListCount(); i++)
			{
				if (SendMessage(m_hWnd, LB_GETSEL, i, 0) >0)
					SendMessage(m_hWnd, LB_SETSEL, 0, i);
				else
					SendMessage(m_hWnd, LB_SETSEL, 1, i);
			}
			break;
		}
	}
	else if ( IsClassName( TEXT("SysListView32") ) )
	{
		LVITEM itm;
		int total = SendMessage(m_hWnd, LVM_GETITEMCOUNT, 0, 0);

		itm.mask = LVIF_STATE;
		itm.stateMask = LVIS_SELECTED;
		itm.iSubItem = -1;
		switch(iSelStyle)
		{
		case 1:   // ȫѡ
			if ( (Style() & LVS_SINGLESEL) == 0) return;	// �Ƕ�ѡ����˳�
			itm.state = LVIS_SELECTED;
			for (i=0; i<total; i++)
			{
				itm.iItem = i;
				SendMessage(m_hWnd, LVM_SETITEM, 0, (LPARAM)(&itm));
			}
			break;

		case 0:  // ȡ��ѡ��
			itm.state = 0;
			// ������һ����ѡ�i��0��ʼ����û����һ����ѡ�е���Ŀ������ i��=-1
			i = SendMessage(m_hWnd, LVM_GETNEXTITEM, -1, LVNI_SELECTED); 
			while (i>=0)
			{
				// ȡ��ѡ��� i ����Ŀ
				itm.iItem = i;
				SendMessage(m_hWnd, LVM_SETITEM, 0, (LPARAM)(&itm));
				// �����һ����ѡ��Ŀ�������� => i
				i = SendMessage(m_hWnd, LVM_GETNEXTITEM, i, LVNI_SELECTED);  // ��û����һ����ѡ�е���Ŀ������  -1
			}
			break;

		case -1:  // ��ѡ
			if ( (Style() & LVS_SINGLESEL) == 0) return;	// �Ƕ�ѡ����˳�
			for (i=0; i<total; i++)
			{
				// ������ڸ���Ŀ�Ǳ�ѡ����δѡ
				itm.iItem = i;
				SendMessage(m_hWnd, LVM_GETITEM, 0, (LPARAM)(&itm));
				if (itm.state & LVIS_SELECTED) itm.state = 0; else itm.state = LVIS_SELECTED;
				// ����Ϊ��ѡ״̬ 
				itm.iItem = i;
				SendMessage(m_hWnd, LVM_SETITEM, 0, (LPARAM)(&itm));
			}
			break;
		}
	}

	// �ÿؼ������� ListSelItemsDo��Combo �ؼ������� ItemSelectedSet��
}





int * CBControl::ListSelItems( int *pSelCount/*=0*/ ) const
{
	if  ( ! IsClassName( TEXT("ListBox") ) ) 
	{
		if (pSelCount) *pSelCount = 0;
		return 0;	// �ú���ֻ������ ListBox �ؼ�
	}

	int count = ListSelCount();
	if (pSelCount) *pSelCount = count;
	if (count == 0) return 0;

	int *pSels = new int [count+1];		// ����ռ䣨��ʹ���±�Ϊ0��Ԫ�أ�
	HM.AddPtr(pSels);
	HM.ZeroMem(pSels, sizeof(int)*(count+1) );

	int *pSelsTemp = new int [count];	// ��ʱ�ռ�
	SendMessage(m_hWnd, LB_GETSELITEMS, (WPARAM)count, (LPARAM)pSelsTemp);

	// ����ʱ�ռ��ֵ����������ռ䣨��ʹ�ý���ռ��±�Ϊ0��Ԫ�أ�
	HM.CopyMem(pSels+1, pSelsTemp, sizeof(int)*count);

	// ����������Ÿ��� +1��ʹ�����Ŷ��� 1 ��ʼ
	int i;
	for (i=1; i<=count; i++) pSels[i]+=1;

	delete []pSelsTemp;	// ��ɾ�� pSels������ HM ����

	return pSels;
}


int CBControl::ListTopIndex()
{
	if ( IsClassName( TEXT("ComboBox") ) )
	{
		return (int)SendMessage(m_hWnd, CB_GETTOPINDEX, 0, 0) + 1;
	}
	else if ( IsClassName( TEXT("ListBox") ) )
	{
		return (int)SendMessage(m_hWnd, LB_SETTOPINDEX, 0, 0) + 1;
	}
	else if ( IsClassName( TEXT("SysListView32") ) )
	{
		return SendMessage(m_hWnd, LVM_GETTOPINDEX, 0, 0) + 1;
	}
	else
		return 0;
}

void CBControl::ListTopIndexSet( int idxTop )
{
	if ( IsClassName( TEXT("ComboBox") ) )
	{
		SendMessage(m_hWnd, CB_SETTOPINDEX, idxTop-1, 0);
	}
	else if ( IsClassName( TEXT("ListBox") ) )
	{
		SendMessage(m_hWnd, LB_SETTOPINDEX, idxTop-1, 0);
	}
	else if ( IsClassName( TEXT("SysListView32") ) )
	{
		SendMessage(m_hWnd, LVM_ENSUREVISIBLE, idxTop-1, 0);
	}
}



// ����б����������
void CBControl::ListClear() const
{
	if ( IsClassName( TEXT("ComboBox") ) ) 
	{
		// ComboBox
		SendMessage(m_hWnd, CB_RESETCONTENT, 0, 0);
	}
	else if ( IsClassName( TEXT("ListBox") ) )
	{
		// ListBox
		SendMessage(m_hWnd, LB_RESETCONTENT, 0, 0);
	}
	else if ( IsClassName( TEXT("SysListView32") ) )
	{
		SendMessage(m_hWnd, LVM_DELETEALLITEMS, 0, 0);
	}

	// �ÿؼ������� ListClear
}


int CBControl::ListItemsHeight() const
{
	if ( IsClassName( TEXT("ComboBox") ) ) 
	{
		// ComboBox
		return (int)SendMessage(m_hWnd, CB_GETITEMHEIGHT, 0, 0 );
	}
	else if ( IsClassName( TEXT("ListBox") ) )
	{
		// ListBox
		return (int)SendMessage(m_hWnd, LB_GETITEMHEIGHT, 0, 0 );
	}

	// �ÿؼ�����ʹ�� ListItemsHeight
	return 0;
}

void CBControl::ListItemsHeightSet( int newHeight )
{
	if ( IsClassName( TEXT("ComboBox") ) ) 
	{
		// ComboBox
		SendMessage(m_hWnd, CB_SETITEMHEIGHT, 0, MAKELPARAM(newHeight, 0) );
	}
	else if ( IsClassName( TEXT("ListBox") ) )
	{
		// ListBox
		SendMessage(m_hWnd, LB_SETITEMHEIGHT, 0, MAKELPARAM(newHeight, 0) );
	}

	Refresh();
}


// =================== ListView �ؼ����� ===================

int CBControl::ListViewAddColumn( LPTSTR szColText, int iWidth /*= 60*/, int iAlign /*= 0*/, int iSubItemIndex /*= 0*/, int iImageIdx /*= -1*/, int iIndex /*= 0x7FFFFFFF*/ )
{
	LVCOLUMN col;
	col.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT | LVCF_SUBITEM;
	if (iImageIdx != -1) col.mask |= LVCF_IMAGE;
	col.cx = iWidth;
	col.fmt = iAlign;
	col.iSubItem = iSubItemIndex;
    col.iImage = iImageIdx;
	col.pszText = szColText;

    return SendMessage(m_hWnd, LVM_INSERTCOLUMN, (WPARAM)iIndex, (LPARAM)(&col)) + 1; // ����ֵת��Ϊ��1��ʼ���
}

int CBControl::ListViewAddColumn( tstring stringColText, int iWidth /*= 60*/, int iAlign /*= 0*/, int iSubItemIndex /*= 0*/, int iImageIdx /*= -1*/, int iIndex /*= 0x7FFFFFFF*/ )
{
	return ListViewAddColumn((LPTSTR)stringColText.c_str(), iWidth, iAlign, iSubItemIndex,iImageIdx, iIndex);
}

int CBControl::ListViewColumnsCount()
{
	return SendMessage((HWND)SendMessage(m_hWnd, LVM_GETHEADER, 0, 0), HDM_GETITEMCOUNT, 0, 0);
}

int CBControl::ListViewNextItemIdx( int idxStart/*=0*/, bool bFindAll/*=true*/, bool bFindSelected/*=true*/, bool bFindCut/*=true*/, bool bFindDropHilited/*=false*/, bool bFindFocused/*=false*/, bool bFindAbove/*=false*/, bool bFindBelow/*=false*/, bool bFindLeft/*=false*/, bool bFindRight/*=false*/ ) const
{
	int iFlag = 0;
	if (bFindAll) 
		iFlag = LVNI_ALL;
	else
	{
		iFlag = 0;
		if (bFindSelected) iFlag |= LVNI_SELECTED;
		if (bFindCut) iFlag |= LVNI_CUT;
		if (bFindDropHilited) iFlag |= LVNI_DROPHILITED;
		if (bFindFocused) iFlag |= LVNI_FOCUSED;
		if (bFindAbove) iFlag |= LVNI_ABOVE;
		if (bFindBelow) iFlag |= LVNI_BELOW;
		if (bFindLeft) iFlag |= LVNI_TOLEFT;
		if (bFindRight) iFlag |= LVNI_TORIGHT;
	}

	return SendMessage(m_hWnd, LVM_GETNEXTITEM, idxStart-1, iFlag) + 1 ;
}

bool CBControl::ListViewFullRowSelect()
{
	if (SendMessage(m_hWnd, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0) & LVS_EX_FULLROWSELECT)
		return true;
	else
		return false;
}

void CBControl::ListViewFullRowSelectSet( bool blNewValue )
{
	if (blNewValue)
		SendMessage (m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);    
	else
		SendMessage (m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, 0);
}

bool CBControl::ListViewGridLines()
{
	if (SendMessage(m_hWnd, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0) & LVS_EX_GRIDLINES)
		return true;
	else
		return false;
}

void CBControl::ListViewGridLinesSet( bool blNewValue )
{
	if (blNewValue)
		SendMessage (m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);  
	else
		SendMessage (m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_GRIDLINES, 0);  
}


// ======== ProgressBar ��ؼ����� ========

int CBControl::Value()
{
	if ( IsClassName( TEXT("msctls_progress32") ) ) 
	{
		// ProgressBar
		return SendMessage(m_hWnd, PBM_GETPOS, 0, 0 );
	}
	
	return 0;
}

void CBControl::ValueSet( int iNewValue )
{
	if ( IsClassName( TEXT("msctls_progress32") ) ) 
	{
		// ProgressBar
		SendMessage(m_hWnd, PBM_SETPOS, (WPARAM)iNewValue, 0);
	}
}

int CBControl::Max()
{
	if ( IsClassName( TEXT("msctls_progress32") ) ) 
	{
		// ProgressBar
		return SendMessage(m_hWnd, PBM_GETRANGE, 0, 0);
	}
	
	return 0;
}

void CBControl::MaxSet( int iNewValue )
{
	if ( IsClassName( TEXT("msctls_progress32") ) ) 
	{
		// ProgressBar
		SendMessage(m_hWnd, PBM_SETRANGE32, (WPARAM)Min(), (LPARAM)iNewValue );
	}
}

int CBControl::Min()
{
	if ( IsClassName( TEXT("msctls_progress32") ) ) 
	{
		// ProgressBar
		return SendMessage(m_hWnd, PBM_GETRANGE, 1, 0 );
	}

	return 0;
}

void CBControl::MinSet( int iNewValue )
{
	if ( IsClassName( TEXT("msctls_progress32") ) ) 
	{
		// ProgressBar
		SendMessage(m_hWnd, PBM_SETRANGE32, (WPARAM)iNewValue, (LPARAM)Max() );
	}
}






// =================== �߼�ͨ�ù��� ===================


HWND CBControl::hWnd() const
{
	return m_hWnd;	
}

HWND CBControl::hWndParentForm() const
{
	return (HWND)(CBWndBase::ms_hashCtrls.ItemLong((long)m_hWnd, false));
}



HWND CBControl::Parent()
{
	return GetParent(m_hWnd);
}

HWND CBControl::ParentSet( HWND hWndParent )
{
	if (! hWndParent) return NULL;	// �������¸���������Ϊ NULL

	// �ɹ�����֮ǰ�����ڵľ����ʧ�ܷ��� NULL
	HWND hWndParentPrev = SetParent(m_hWnd, hWndParent);
	if (! hWndParentPrev) return NULL;

	// ���� CBWndBase::ms_hashCtrlResIDs ��ϣ���жԱ��ؼ������ڵļ�¼
	//   ���������
	CBWndBase::ms_hashCtrlResIDs.ItemLongSet( (long)m_hWnd, (long)hWndParent, false );

// 	// For compatibility reasons, SetParent does not modify the WS_CHILD or WS_POPUP 
// 	//   window styles of the window whose parent is being changed. 
// 	if (hWndParent)
// 	{
// 		// if hWndNewParent is not NULL and the window was previously a child 
// 		//   of the desktop, you should clear the WS_POPUP style and set 
// 		//   the WS_CHILD style before calling SetParent.
// 		StyleSet(WS_POPUP, -1);
// 		StyleSet(WS_CHILD, 1);.
// 	}
// 	else
// 	{
// 		// if hWndNewParent is NULL, you should also clear the WS_CHILD bit and set 
// 		//   the WS_POPUP style after calling SetParent.
// 		StyleSet(WS_CHILD, -1);
// 		StyleSet(WS_POPUP, 1);
// 	}


	
	return hWndParentPrev;
}


// ����һ��������� CBForm ����ĵ�ַָ������ͨ���ؼ����ʸ�����
CBForm * CBControl::ParentFormPtr() const
{
	return (CBForm *)(CBForm::ms_hashWnd.Item((long)hWndParentForm(),false));
}

// ����Ӵ��ڿؼ���Ĭ�ϴ��ڳ���ĵ�ַ��עʵ�ʴ˵�ַ�ĺ������ܲ���ʹ�ã����ѱ����໯��
unsigned long CBControl::PtrWndProcDef() const
{
	return (unsigned long)(CBWndBase::ms_hashCtrls.Item((long)m_hWnd, false));
}












