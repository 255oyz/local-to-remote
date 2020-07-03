// Caddcontactsdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Caddcontactsdlg.h"
#include "afxdialogex.h"


// Caddcontactsdlg 对话框

IMPLEMENT_DYNAMIC(Caddcontactsdlg, CDialogEx)

Caddcontactsdlg::Caddcontactsdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Caddcontactsdlg::IDD, pParent)
	, m_new_name(_T(""))
	, m_new_birthyearstr(_T(""))
	, m_new_birthmonthstr(_T(""))
	, m_new_birthdaystr(_T(""))
	, m_new_citystr(_T(""))
	, m_new_company(_T(""))
	, m_new_officeTel(_T(""))
	, m_new_homeTel(_T(""))
	, m_new_postcode(_T(""))
	, m_new_email(_T(""))
	, m_new_sex(-1)
{
	
}

Caddcontactsdlg::~Caddcontactsdlg()
{
}

void Caddcontactsdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEW_NAME, m_new_name);
	DDX_Radio(pDX, IDC_RADIO_NEW_SEX, m_new_sex);
	DDX_Control(pDX, IDC_COMBO_NEW_YEAR, m_new_birthyear);
	DDX_CBString(pDX, IDC_COMBO_NEW_YEAR, m_new_birthyearstr);
	DDX_Control(pDX, IDC_COMBO_NEW_MONTH, m_new_birthmonth);
	DDX_CBString(pDX, IDC_COMBO_NEW_MONTH, m_new_birthmonthstr);
	DDX_Control(pDX, IDC_COMBO_NEW_DAY, m_new_birthday);
	DDX_CBString(pDX, IDC_COMBO_NEW_DAY, m_new_birthdaystr);
	DDX_Control(pDX, IDC_COMBO_NEW_CITY, m_new_city);
	DDX_CBString(pDX, IDC_COMBO_NEW_CITY, m_new_citystr);
	DDX_Text(pDX, IDC_EDIT_NEW_COMPANY, m_new_company);
	DDX_Text(pDX, IDC_EDIT_NEW_OFFICETEL, m_new_officeTel);
	DDX_Text(pDX, IDC_EDIT_NEW_HOMETEL, m_new_homeTel);
	DDX_Text(pDX, IDC_EDIT_NEW_POSTCODE, m_new_postcode);
	DDX_Text(pDX, IDC_EDIT_NEW_EMAIL, m_new_email);
	
}


BEGIN_MESSAGE_MAP(Caddcontactsdlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_NEW_MONTH, &Caddcontactsdlg::OnCbnSelchangeComboNewMonth)
	ON_BN_CLICKED(IDOK, &Caddcontactsdlg::OnBnClickedOk)
	ON_COMMAND(IDCANCEL, &Caddcontactsdlg::OnIdcancel)
END_MESSAGE_MAP()


BOOL Caddcontactsdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	this->loaddate();  //加载日期
	this->loadcity();  //加载城市
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void Caddcontactsdlg::loaddate()
{
	int y=1900,m=1,d=1;
	SYSTEMTIME st;
	CString strDate;
	GetLocalTime(&st);        //得到当前时间
	while(y<=2100)                                     //年组合框中添加1900-2100年
	{
		m_new_birthyearstr.Format("%d",y++);
		m_new_birthyear.AddString(m_new_birthyearstr);
	}
	strDate.Format("%4d",st.wYear);
	m_new_birthyearstr=strDate;                      //联系人生日默认设置为当前的年月日
	while(m<=12)                                     //月组合框中添加12个月
	{
		m_new_birthmonthstr.Format("%02d",m++);
		m_new_birthmonth.AddString(m_new_birthmonthstr);
	}
	strDate.Format("%02d",st.wMonth);
	m_new_birthmonthstr=strDate;
	/*判断当前月份、是否为闰年，并根据情况添加对应的天数*/
	if(st.wMonth==1||st.wMonth==3||st.wMonth==5||st.wMonth==7||st.wMonth==8||st.wMonth==10||st.wMonth==12)   
	{
		while(d<=31)
		{
			m_new_birthdaystr.Format("%02d",d++);
			m_new_birthday.AddString(m_new_birthdaystr);
		}
	}
	else if(st.wMonth==4||st.wMonth==6||st.wMonth==9||st.wMonth==11)
	{
		while(d<=30)
		{
			m_new_birthdaystr.Format("%02d",d++);
			m_new_birthday.AddString(m_new_birthdaystr);
		}
	}
	else
	{
		if(st.wYear%400==0||(st.wYear%4==0&&(st.wYear%100!=0)))
		{
			while(d<=29)
			{
				m_new_birthdaystr.Format("%02d",d++);
				m_new_birthday.AddString(m_new_birthdaystr);
			}
		}
		else
		{
			while(d<=28)
			{
				m_new_birthdaystr.Format("%02d",d++);
				m_new_birthday.AddString(m_new_birthdaystr);
			}
		}

	}
	strDate.Format("%02d",st.wDay);
	m_new_birthdaystr=strDate;
}

void Caddcontactsdlg::loadcity()
{
	int i=1;
	m_new_city.AddString("-请选择-");
	while(!(citybuffer[i].IsEmpty()))
		m_new_city.AddString(citybuffer[i++]);
	m_new_city.GetLBText(0,m_new_citystr);

}


void Caddcontactsdlg::OnCbnSelchangeComboNewMonth()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	int d;
	CString strDate=m_new_birthdaystr;
	m_new_birthmonth.GetLBText(m_new_birthmonth.GetCurSel(),m_new_birthmonthstr);
	UpdateData(FALSE);
	UpdateData();
	/*判断当前月份、是否为闰年，并根据情况添加对应的天数*/
	if(m_new_birthmonthstr=="01"||m_new_birthmonthstr=="03"||m_new_birthmonthstr=="05"||m_new_birthmonthstr=="07"||m_new_birthmonthstr=="08"||m_new_birthmonthstr=="10"||m_new_birthmonthstr=="12")   
	{
		m_new_birthday.ResetContent();
		d=1;
		while(d<=31)
		{
			m_new_birthdaystr.Format("%02d",d++);
			m_new_birthday.AddString(m_new_birthdaystr);
		}
	}
	else if(m_new_birthmonthstr=="04"||m_new_birthmonthstr=="06"||m_new_birthmonthstr=="09"||m_new_birthmonthstr=="11")
	{
		m_new_birthday.ResetContent();
		d=1;
		while(d<=30)
		{
			m_new_birthdaystr.Format("%02d",d++);
			m_new_birthday.AddString(m_new_birthdaystr);
		}
	}
	else
	{
		if(_ttoi(m_new_birthyearstr)%400==0||(_ttoi(m_new_birthyearstr)%4==0&&(_ttoi(m_new_birthyearstr)%100!=0)))
		{
			m_new_birthday.ResetContent();
			d=1;
			while(d<=29)
			{
				m_new_birthdaystr.Format("%02d",d++);
				m_new_birthday.AddString(m_new_birthdaystr);
			}
		}
		else
		{
			m_new_birthday.ResetContent();
			d=1;
			while(d<=28)
			{
				m_new_birthdaystr.Format("%02d",d++);
				m_new_birthday.AddString(m_new_birthdaystr);
			}
		}

	}
	/*根据原先日期框中的数据进行更新，若原日期在新月份中不存在，则自动调整至新月最后一天*/
	if(m_new_birthday.GetCount()>=_ttoi(strDate))
		m_new_birthday.GetLBText(_ttoi(strDate)-1,m_new_birthdaystr);
	else
		m_new_birthday.GetLBText(m_new_birthday.GetCount()-1,m_new_birthdaystr);
	UpdateData(FALSE);
}



void Caddcontactsdlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_new_name.IsEmpty()||m_new_sex==-1||m_new_company.IsEmpty()||m_new_citystr.IsEmpty()||m_new_citystr=="-请选择-"||m_new_officeTel.IsEmpty())
	{
		MessageBox("您的输入不全","错误",MB_ICONERROR);
		return;
	}
	else
	{
		linkman.name=m_new_name;
		if(m_new_sex)
			linkman.sex="女";
		else
			linkman.sex="男";
		linkman.birthday=m_new_birthyearstr+"-"+m_new_birthmonthstr+"-"+m_new_birthdaystr;
		linkman.city=m_new_citystr;
		linkman.company=m_new_company;
		linkman.officeTel=m_new_officeTel;
		linkman.homeTel=m_new_homeTel;
		linkman.postcode=m_new_postcode;
		linkman.email=m_new_email;
		linkman.sign="non";
		MessageBox("已添加","注意",MB_ICONWARNING);
		CDialogEx::OnOK();
	}

	UpdateData(FALSE);
}



void Caddcontactsdlg::OnIdcancel()
{
	// TODO: 在此添加命令处理程序代码
	if(MessageBox("您的输入将不会被保存","注意",IDOK|MB_ICONWARNING)==IDOK)
		CDialogEx::OnCancel();
	else
		return;
}

