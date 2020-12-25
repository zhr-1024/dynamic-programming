#include "resource.h"
#include "BForm.h"

CBForm form1(ID_form1);

//退出按钮功能的实现
void cmdExit_Click()
{
	form1.UnLoad();
}


bool DoPartResource(int iItems,int iMoneys,float **g,tstring &sRetResult,float &retMaxprofit,tstring &sRetIntermedia)
{
	//准备保存中间结果的动态二维数组
	float *fArray=new float [iItems*(iMoneys+1)];
	float **f=new float *[iItems];
	int i,j,k;
	float fMax;
	for(i=0;i<iItems;i++)
	{
		//让每个f[i]指向线性空间fArray的分行处
		f[i]=fArray+i*(iMoneys+1);
	}

	//准备动态数组y[][]
	//y（i，x）表示把x万元分给前i个项目时，给第i个项目分配多少，此时f（i，x）最大
	float *yArray=new float [iItems*(iMoneys+1)];
	float ** y=new float *[iItems];
	for(i=0;i<iItems;i++)
	{
		y[i]=yArray+i*(iMoneys+1);
	}

	//开始计算
	//先对f和y的第0行开始赋值
	//当只有一个项目时，显然f就是把资金j都投到项目1上得到的总利润
	//y显然第一个项目得到所有的资金j
	for(j=0;j<=iMoneys;j++)
	{
		f[0][j]=g[0][j];
		y[0][j]=j;
	}

	//从第2个项目开始
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

	//返回结果
	//返回最大利润
	retMaxprofit=f[iItems-1][iMoneys];
	//返回分配结果，即第i个项目分配多少钱
	int iSumX=iMoneys;
	sRetResult=TEXT("");
	for(i=iItems-1;i>=0;i--)
	{
		//从最后一个项目查看到第一个项目
		sRetResult=TEXT("\r\n")+sRetResult;
		sRetResult=Str(y[i][iSumX])+sRetResult;
		iSumX-=y[i][iSumX];
		//现在ISumX是前i-1个项目总共分多少钱
	}
	//返回中间结果，即前i个项目总利润最大为多少，此时第i个项目分得多少钱
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


	//释放资源
	delete []y;
	delete []yArray;
	delete []f;
	delete []fArray;

	//返回函数
	return true;
}


//求解按钮功能的实现
void cmdDo_Click()
{
	//获得正确的项目数和资金总数
	int iItems=form1.Control(ID_txtItems).TextInt();
	int iMoneys=form1.Control(ID_txtMoneys).TextInt();
	if(iItems<=0||iMoneys<=0)
	{
		MsgBox(TEXT("请输入正确的项目数和资金总数（必须为正整数）"),TEXT("数据错误"),mb_OK,mb_IconExclamation);
		return;
	}



	//把g(i,x)的原始数据输入到动态二维数组

	//首先，获得正确的g(i,x)的原始数据
	TCHAR *szGsText=form1.Control(ID_txtSrcGs).Text();
	if(*szGsText==TEXT('\0'))
	{
		MsgBox(TEXT("请输入g(i,x)的原始数据！"),TEXT("数据错误"),mb_OK,mb_IconExclamation);
		return;
	}

	//其次，开辟动态数组的空间，+1是因为存在分得0万元的情况
	float *gArray=new float [iItems*(iMoneys+1)];
	float **g=new float *[iItems];
	int i,j;
	//让每个g[i]指向线性空间gArray的分行处
	for(i=0;i<iItems;i++)
	{
		g[0]=gArray+i*(iMoneys+1);
	}

	//然后，调用BWindows的Split函数，把szGsText的内容，按照回车+换行符分解
	TCHAR **lines=NULL;
	//把每行数据都存到lines中
	int iLines=Split(szGsText,lines,TEXT("\r\n"));
	if(iLines<iItems)
	{
		tstring sErrInfo;
		sErrInfo=TEXT("要包含");
		sErrInfo+=Str(iItems);
		sErrInfo+=TEXT("行数据");
		MsgBox(sErrInfo,TEXT("数据错误"),mb_OK,mb_IconExclamation);
		return ;
	}
	//将lines中每行数据存入二维数组
	for(i=1;i<=iLines;i++)
	{
		TCHAR ** flds=NULL;
		int iFields=0;
		//忽略空行
		if(*lines[i]==TEXT('\0'))
		{
			continue;
		}

		//智能兼容，以tab或者空格分隔都可以
		if(InStr(lines[i],TEXT("\t"))==0)
		{
			iFields=Split(lines[i],flds,TEXT(" "));
		}else{
			iFields=Split(lines[i],flds,TEXT("\t"));
		}

		//检查本行lines[i]中的字段数是否正确
		if(iFields!=iMoneys+1)
		{
			tstring sErrInfo;
			sErrInfo=TEXT("第");
			sErrInfo+=lines[i];
			sErrInfo+=TEXT("行应该包含");
			sErrInfo+=Str(iMoneys+1);
			sErrInfo+=TEXT("个字段");
			MsgBox(sErrInfo,TEXT("数据错误"),mb_OK,mb_IconExclamation);
			return;
		}

		//将本行的g(i,x)数据，存入二维动态数组中
		for(j=1;j<=iFields;j++)
		{
			g[i-1][j-1]=Val(flds[j]);
		}
	}



	//调用函数计算
	float fMaxProfit=0;
	tstring sResults,sIntermedia;
	DoPartResource(iItems,iMoneys,g,sResults,fMaxProfit,sIntermedia);


	//将计算结果显示到控件
	form1.Control(ID_txtFs).TextSet(sIntermedia);
	form1.Control(ID_txtMaxProfit).TextSet(fMaxProfit);
	iLines=Split(sResults.c_str(),lines,TEXT("\r\n"));
	form1.Control(ID_lstResult).ListClear();
	for(i=1;i<=iLines;i++)
	{
		//忽略空行
		if(*lines[i]==TEXT('\0'))
		{
			continue;
		}
		tstring sItem;
		sItem=TEXT("项目");
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
	//EventAdd一定要写在全部语句之前
	form1.EventAdd(ID_cmdExit,eCommandButton_Click,cmdExit_Click);
	form1.EventAdd(ID_cmdDo,eCommandButton_Click,cmdDo_Click);

	form1.IconSet(IDI_ICON1);
	form1.Show();
	return 0;
}