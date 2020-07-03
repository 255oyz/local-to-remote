// Caddcontactsdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Caddcontactsdlg.h"
#include "afxdialogex.h"


// Caddcontactsdlg �Ի���

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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	this->loaddate();  //��������
	this->loadcity();  //���س���
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void Caddcontactsdlg::loaddate()
{
	int y=1900,m=1,d=1;
	SYSTEMTIME st;
	CString strDate;
	GetLocalTime(&st);        //�õ���ǰʱ��
	while(y<=2100)                                     //����Ͽ������1900-2100��
	{
		m_new_birthyearstr.Format("%d",y++);
		m_new_birthyear.AddString(m_new_birthyearstr);
	}
	strDate.Format("%4d",st.wYear);
	m_new_birthyearstr=strDate;                      //��ϵ������Ĭ������Ϊ��ǰ��������
	while(m<=12)                                     //����Ͽ������12����
	{
		m_new_birthmonthstr.Format("%02d",m++);
		m_new_birthmonth.AddString(m_new_birthmonthstr);
	}
	strDate.Format("%02d",st.wMonth);
	m_new_birthmonthstr=strDate;
	/*�жϵ�ǰ�·ݡ��Ƿ�Ϊ���꣬�����������Ӷ�Ӧ������*/
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
	m_new_city.AddString("-��ѡ��-");
	while(!(citybuffer[i].IsEmpty()))
		m_new_city.AddString(citybuffer[i++]);
	m_new_city.GetLBText(0,m_new_citystr);

}


void Caddcontactsdlg::OnCbnSelchangeComboNewMonth()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	int d;
	CString strDate=m_new_birthdaystr;
	m_new_birthmonth.GetLBText(m_new_birthmonth.GetCurSel(),m_new_birthmonthstr);
	UpdateData(FALSE);
	UpdateData();
	/*�жϵ�ǰ�·ݡ��Ƿ�Ϊ���꣬�����������Ӷ�Ӧ������*/
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
	/*����ԭ�����ڿ��е����ݽ��и��£���ԭ���������·��в����ڣ����Զ��������������һ��*/
	if(m_new_birthday.GetCount()>=_ttoi(strDate))
		m_new_birthday.GetLBText(_ttoi(strDate)-1,m_new_birthdaystr);
	else
		m_new_birthday.GetLBText(m_new_birthday.GetCount()-1,m_new_birthdaystr);
	UpdateData(FALSE);
}



void Caddcontactsdlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_new_name.IsEmpty()||m_new_sex==-1||m_new_company.IsEmpty()||m_new_citystr.IsEmpty()||m_new_citystr=="-��ѡ��-"||m_new_officeTel.IsEmpty())
	{
		MessageBox("�������벻ȫ","����",MB_ICONERROR);
		return;
	}
	else
	{
		linkman.name=m_new_name;
		if(m_new_sex)
			linkman.sex="Ů";
		else
			linkman.sex="��";
		linkman.birthday=m_new_birthyearstr+"-"+m_new_birthmonthstr+"-"+m_new_birthdaystr;
		linkman.city=m_new_citystr;
		linkman.company=m_new_company;
		linkman.officeTel=m_new_officeTel;
		linkman.homeTel=m_new_homeTel;
		linkman.postcode=m_new_postcode;
		linkman.email=m_new_email;
		linkman.sign="non";
		MessageBox("�����","ע��",MB_ICONWARNING);
		CDialogEx::OnOK();
	}

	UpdateData(FALSE);
}



void Caddcontactsdlg::OnIdcancel()
{
	// TODO: �ڴ���������������
	if(MessageBox("�������뽫���ᱻ����","ע��",IDOK|MB_ICONWARNING)==IDOK)
		CDialogEx::OnCancel();
	else
		return;
}

