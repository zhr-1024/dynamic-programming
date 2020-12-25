#include "resource.h"
#include "BForm.h"

CBForm form1(ID_form1);

//�˳���ť���ܵ�ʵ��
void cmdExit_Click()
{
	form1.UnLoad();
}


bool DoPartResource(int iItems,int iMoneys,float **g,tstring &sRetResult,float &retMaxprofit,tstring &sRetIntermedia)
{
	//׼�������м����Ķ�̬��ά����
	float *fArray=new float [iItems*(iMoneys+1)];
	float **f=new float *[iItems];
	int i,j,k;
	float fMax;
	for(i=0;i<iItems;i++)
	{
		//��ÿ��f[i]ָ�����Կռ�fArray�ķ��д�
		f[i]=fArray+i*(iMoneys+1);
	}

	//׼����̬����y[][]
	//y��i��x����ʾ��x��Ԫ�ָ�ǰi����Ŀʱ������i����Ŀ������٣���ʱf��i��x�����
	float *yArray=new float [iItems*(iMoneys+1)];
	float ** y=new float *[iItems];
	for(i=0;i<iItems;i++)
	{
		y[i]=yArray+i*(iMoneys+1);
	}

	//��ʼ����
	//�ȶ�f��y�ĵ�0�п�ʼ��ֵ
	//��ֻ��һ����Ŀʱ����Ȼf���ǰ��ʽ�j��Ͷ����Ŀ1�ϵõ���������
	//y��Ȼ��һ����Ŀ�õ����е��ʽ�j
	for(j=0;j<=iMoneys;j++)
	{
		f[0][j]=g[0][j];
		y[0][j]=j;
	}

	//�ӵ�2����Ŀ��ʼ
	for(i=1;i<iItems;i++)
	{
		for(j=0;j<=iMoneys;j++)
		{
			fMax=-1;
			for(k=0;k<=j;k++)
			{
				if(fMax<g[i][k]+f[i-1][j-k])
				{
					fMax=g[i][k]+f[i-1][j-k];
					y[i][j]=k;
				}
			}
			f[i][j]=fMax;
		}
	}

	//���ؽ��
	//�����������
	retMaxprofit=f[iItems-1][iMoneys];
	//���ط�����������i����Ŀ�������Ǯ
	int iSumX=iMoneys;
	sRetResult=TEXT("");
	for(i=iItems-1;i>=0;i--)
	{
		//�����һ����Ŀ�鿴����һ����Ŀ
		sRetResult=TEXT("\r\n")+sRetResult;
		sRetResult=Str(y[i][iSumX])+sRetResult;
		iSumX-=y[i][iSumX];
		//����ISumX��ǰi-1����Ŀ�ܹ��ֶ���Ǯ
	}
	//�����м�������ǰi����Ŀ���������Ϊ���٣���ʱ��i����Ŀ�ֵö���Ǯ
	sRetIntermedia=TEXT("");
	for(i=0;i<iItems;i++)
	{
		for(j=0;j<=iMoneys;j++)
		{
			sRetIntermedia+=Str(f[i][j]);
			sRetIntermedia+=TEXT("(y=");
			sRetIntermedia+=Str(y[i][j]);
			sRetIntermedia+=TEXT(")");
			if(j<iMoneys)
			{
				sRetIntermedia+=TEXT("\t");
			}
		}
		sRetIntermedia+=TEXT("\r\n");
	}


	//�ͷ���Դ
	delete []y;
	delete []yArray;
	delete []f;
	delete []fArray;

	//���غ���
	return true;
}


//��ⰴť���ܵ�ʵ��
void cmdDo_Click()
{
	//�����ȷ����Ŀ�����ʽ�����
	int iItems=form1.Control(ID_txtItems).TextInt();
	int iMoneys=form1.Control(ID_txtMoneys).TextInt();
	if(iItems<=0||iMoneys<=0)
	{
		MsgBox(TEXT("��������ȷ����Ŀ�����ʽ�����������Ϊ��������"),TEXT("���ݴ���"),mb_OK,mb_IconExclamation);
		return;
	}



	//��g(i,x)��ԭʼ�������뵽��̬��ά����

	//���ȣ������ȷ��g(i,x)��ԭʼ����
	TCHAR *szGsText=form1.Control(ID_txtSrcGs).Text();
	if(*szGsText==TEXT('\0'))
	{
		MsgBox(TEXT("������g(i,x)��ԭʼ���ݣ�"),TEXT("���ݴ���"),mb_OK,mb_IconExclamation);
		return;
	}

	//��Σ����ٶ�̬����Ŀռ䣬+1����Ϊ���ڷֵ�0��Ԫ�����
	float *gArray=new float [iItems*(iMoneys+1)];
	float **g=new float *[iItems];
	int i,j;
	//��ÿ��g[i]ָ�����Կռ�gArray�ķ��д�
	for(i=0;i<iItems;i++)
	{
		g[0]=gArray+i*(iMoneys+1);
	}

	//Ȼ�󣬵���BWindows��Split��������szGsText�����ݣ����ջس�+���з��ֽ�
	TCHAR **lines=NULL;
	//��ÿ�����ݶ��浽lines��
	int iLines=Split(szGsText,lines,TEXT("\r\n"));
	if(iLines<iItems)
	{
		tstring sErrInfo;
		sErrInfo=TEXT("Ҫ����");
		sErrInfo+=Str(iItems);
		sErrInfo+=TEXT("������");
		MsgBox(sErrInfo,TEXT("���ݴ���"),mb_OK,mb_IconExclamation);
		return ;
	}
	//��lines��ÿ�����ݴ����ά����
	for(i=1;i<=iLines;i++)
	{
		TCHAR ** flds=NULL;
		int iFields=0;
		//���Կ���
		if(*lines[i]==TEXT('\0'))
		{
			continue;
		}

		//���ܼ��ݣ���tab���߿ո�ָ�������
		if(InStr(lines[i],TEXT("\t"))==0)
		{
			iFields=Split(lines[i],flds,TEXT(" "));
		}else{
			iFields=Split(lines[i],flds,TEXT("\t"));
		}

		//��鱾��lines[i]�е��ֶ����Ƿ���ȷ
		if(iFields!=iMoneys+1)
		{
			tstring sErrInfo;
			sErrInfo=TEXT("��");
			sErrInfo+=lines[i];
			sErrInfo+=TEXT("��Ӧ�ð���");
			sErrInfo+=Str(iMoneys+1);
			sErrInfo+=TEXT("���ֶ�");
			MsgBox(sErrInfo,TEXT("���ݴ���"),mb_OK,mb_IconExclamation);
			return;
		}

		//�����е�g(i,x)���ݣ������ά��̬������
		for(j=1;j<=iFields;j++)
		{
			g[i-1][j-1]=Val(flds[j]);
		}
	}



	//���ú�������
	float fMaxProfit=0;
	tstring sResults,sIntermedia;
	DoPartResource(iItems,iMoneys,g,sResults,fMaxProfit,sIntermedia);


	//����������ʾ���ؼ�
	form1.Control(ID_txtFs).TextSet(sIntermedia);
	form1.Control(ID_txtMaxProfit).TextSet(fMaxProfit);
	iLines=Split(sResults.c_str(),lines,TEXT("\r\n"));
	form1.Control(ID_lstResult).ListClear();
	for(i=1;i<=iLines;i++)
	{
		//���Կ���
		if(*lines[i]==TEXT('\0'))
		{
			continue;
		}
		tstring sItem;
		sItem=TEXT("��Ŀ");
		sItem+=Str(i);
		sItem+=TEXT(" ");
		sItem+=lines[i];
		form1.Control(ID_lstResult).AddItem(sItem);
	}


	delete [] g;
	delete [] gArray;
}




int main()
{
	//EventAddһ��Ҫд��ȫ�����֮ǰ
	form1.EventAdd(ID_cmdExit,eCommandButton_Click,cmdExit_Click);
	form1.EventAdd(ID_cmdDo,eCommandButton_Click,cmdDo_Click);

	form1.IconSet(IDI_ICON1);
	form1.Show();
	return 0;
}