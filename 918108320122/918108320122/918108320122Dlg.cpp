
// 918108320122Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "918108320122.h"
#include "918108320122Dlg.h"
#include "afxdialogex.h"
#include "Ccontacts.h"   //����Ccontacts��ͷ�ļ�
#include "Caddcontactsdlg.h" //����Caddcontactsdlg��ͷ�ļ�

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy918108320122Dlg �Ի���



CMy918108320122Dlg::CMy918108320122Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy918108320122Dlg::IDD, pParent)
	, m_name(_T(""))
	, m_sex(_T(""))
	, m_birthday(_T(""))
	, m_city(_T(""))
	, m_company(_T(""))
	, m_officeTel(_T(""))
	, m_homeTel(_T(""))
	, m_postcode(_T(""))
	, m_email(_T(""))
	, m_combobox_str_city(_T(""))
	, m_combobox_str_sex(_T(""))
	, count_of_buffer(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CMy918108320122Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CONTACTS, m_listofcontacts);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_SEX, m_sex);
	DDX_Text(pDX, IDC_EDIT_BIRTHDAY, m_birthday);
	DDX_Text(pDX, IDC_EDIT_CITY, m_city);
	DDX_Text(pDX, IDC_EDIT_COMPANY, m_company);
	DDX_Text(pDX, IDC_EDIT_OFFICETEL, m_officeTel);
	DDX_Text(pDX, IDC_EDIT_HOMETEL, m_homeTel);
	DDX_Text(pDX, IDC_EDIT_POSTCODE, m_postcode);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_email);
	DDX_Control(pDX, IDC_COMBO_CITY, m_combobox_city);
	DDX_CBString(pDX, IDC_COMBO_CITY, m_combobox_str_city);
	DDX_Control(pDX, IDC_COMBO_SEX, m_combobox_sex);
	DDX_CBString(pDX, IDC_COMBO_SEX, m_combobox_str_sex);
}

BEGIN_MESSAGE_MAP(CMy918108320122Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST_CONTACTS, &CMy918108320122Dlg::OnLbnSelchangeListContacts)
	ON_LBN_KILLFOCUS(IDC_LIST_CONTACTS, &CMy918108320122Dlg::OnLbnKillfocusListContacts)
	ON_CBN_SELCHANGE(IDC_COMBO_CITY, &CMy918108320122Dlg::OnCbnSelchangeComboCity)
	ON_CBN_KILLFOCUS(IDC_COMBO_CITY, &CMy918108320122Dlg::OnCbnKillfocusComboCity)
	ON_CBN_SELCHANGE(IDC_COMBO_SEX, &CMy918108320122Dlg::OnCbnSelchangeComboSex)
	ON_CBN_KILLFOCUS(IDC_COMBO_SEX, &CMy918108320122Dlg::OnCbnKillfocusComboSex)
	ON_BN_CLICKED(IDC_ADD, &CMy918108320122Dlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CMy918108320122Dlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_SAVE, &CMy918108320122Dlg::OnBnClickedSave)
	ON_COMMAND(IDCANCEL, &CMy918108320122Dlg::OnIdcancel)
END_MESSAGE_MAP()


// CMy918108320122Dlg ��Ϣ�������

BOOL CMy918108320122Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	if(addressbook.Open("ͨѶ¼.txt",CStdioFile::modeCreate|CStdioFile::modeRead|CStdioFile::modeNoTruncate)) //�򿪲���ȡ�ļ�
	{
		addressbook.SeekToBegin();
		m_combobox_city.AddString("ȫ��");    //������Ͽ���ӡ�ȫ����ѡ��
		while(addressbook.ReadString(info))   //�ж�ȡ
		{
			if(info.Find("{")==-1||info.Find("}")==-1)     //��ȥ��Ч�ַ�����
				continue;
			linkman.Getcontacts(info);       //�Ӷ�ȡ��ÿ���ַ����зּ������������ֵ
			if(linkman.sign=="del")
				continue;
			m_listofcontacts.AddString(linkman.name);  //�����б�
			m_combobox_city.AddString(linkman.city);
		}
		addressbook.Close();
		for(int i=1;i<m_combobox_city.GetCount();i++)          //ɾȥ�ظ���ӵĳ���
			for(int j=i+1;j<m_combobox_city.GetCount();j++)
			{
				CString stri,strj;
				m_combobox_city.GetLBText(i,stri);
				m_combobox_city.GetLBText(j,strj);
				if(strj==stri)
					m_combobox_city.DeleteString(j--);       
			}
		m_combobox_sex.AddString("ȫ��");                //Ϊ�Ա���Ͽ����������ݣ�Ҳ���������ɾ�أ�
		m_combobox_sex.AddString("��");
		m_combobox_sex.AddString("Ů");
		m_combobox_city.GetLBText(0,m_combobox_str_city);
		m_combobox_sex.GetLBText(0,m_combobox_str_sex);
	}
	else                                      //�����ִ���,�˳�����
	{
		MessageBox("False","failure");
		exit(0);
	}
	m_add.AutoLoad(IDC_ADD,this);     //����λͼ��ť
	m_delete.AutoLoad(IDC_DELETE,this);
	m_save.AutoLoad(IDC_SAVE,this);
	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy918108320122Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy918108320122Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy918108320122Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy918108320122Dlg::OnLbnSelchangeListContacts()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CStdioFile  addressbook;
	CString name,info;
	Ccontacts linkman;
	int choice=m_listofcontacts.GetCurSel();  //������ѡ�������
	m_listofcontacts.GetText(choice,name);    //��ȡѡ�����ϵ�˵�����
	if(addressbook.Open("ͨѶ¼.txt",CFile::modeRead))
	{
		addressbook.SeekToBegin();
		while(addressbook.ReadString(info))  //�ļ��ж�ȡ����������
		{
			if(info.Find("{")==-1||info.Find("}")==-1)
				continue;
			linkman.Getcontacts(info);
			if(linkman.sign=="del")
				continue;
			if(linkman.name==name)
			{
				linkman.transinfo(this);
				break;
			}
		}
		addressbook.Close();
	}
	else
		MessageBox("False","failure");
	int i=0;
	while(!(buffer[i].IsEmpty()))    //��������ȡ������
	{
		linkman.Getcontacts(buffer[i]);
		if(linkman.sign=="del")
		{
			i++;
			continue;
		}
		if(linkman.name==name)
		{
			linkman.transinfo(this);
			break;
		}
		i++;
	}
	UpdateData(FALSE);
}

void CMy918108320122Dlg::OnLbnKillfocusListContacts()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	m_name="";
	m_sex="";
	m_birthday="";
	m_city="";
	m_company="";
	m_officeTel="";
	m_homeTel=""; 
	m_postcode="";
	m_email="";
	UpdateData(FALSE);
}


void CMy918108320122Dlg::OnCbnSelchangeComboCity()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	m_combobox_city.GetLBText(m_combobox_city.GetCurSel(),m_combobox_str_city);     //������Ͽ��е���������
	if(addressbook.Open("ͨѶ¼.txt",CFile::modeRead))
	{
		addressbook.SeekToBegin();
		m_listofcontacts.ResetContent();
		while(addressbook.ReadString(info))   
		{
			if(info.Find("{")==-1||info.Find("}")==-1)
				continue;
			linkman.Getcontacts(info);
			if(linkman.sign=="del")
				continue;
			/*���ж��Ƿ�ͬʱ����������Ͽ������*/
			if((linkman.city==m_combobox_str_city||m_combobox_str_city=="ȫ��")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="ȫ��"))
				m_listofcontacts.AddString(linkman.name);
		}
		addressbook.Close();
	}
	else
		MessageBox("False","failure");
	int i=0;
	while(!(buffer[i].IsEmpty()))
	{
		linkman.Getcontacts(buffer[i]);
		if(linkman.sign=="del")
		{
			i++;
			continue;
		}
		if((linkman.city==m_combobox_str_city||m_combobox_str_city=="ȫ��")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="ȫ��"))
			m_listofcontacts.AddString(linkman.name);
		i++;
	}
	UpdateData(FALSE);
}


void CMy918108320122Dlg::OnCbnKillfocusComboCity()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	if(addressbook.Open("ͨѶ¼.txt",CFile::modeRead))
	{
		addressbook.SeekToBegin();
		m_listofcontacts.ResetContent();
		while(addressbook.ReadString(info))   
		{
			if(info.Find("{")==-1||info.Find("}")==-1)
				continue;
			linkman.Getcontacts(info);
			if(linkman.sign=="del")
				continue; 
			/*���ж��Ƿ�ͬʱ����������Ͽ������*/
			if((linkman.city==m_combobox_str_city||m_combobox_str_city=="ȫ��")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="ȫ��"))
				m_listofcontacts.AddString(linkman.name);
		}
		addressbook.Close();
	}
	else
		MessageBox("False","failure");
	int i=0;
	while(!(buffer[i].IsEmpty()))
	{
		linkman.Getcontacts(buffer[i]);
		if(linkman.sign=="del")
		{
			i++;
			continue;
		}
		if((linkman.city==m_combobox_str_city||m_combobox_str_city=="ȫ��")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="ȫ��"))
			m_listofcontacts.AddString(linkman.name);
		i++;
	}
	UpdateData(FALSE);
}


void CMy918108320122Dlg::OnCbnSelchangeComboSex()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	m_combobox_sex.GetLBText(m_combobox_sex.GetCurSel(),m_combobox_str_sex);    //������Ͽ��е���������
	if(addressbook.Open("ͨѶ¼.txt",CFile::modeRead))
	{
		addressbook.SeekToBegin();
		m_listofcontacts.ResetContent();
		while(addressbook.ReadString(info))   
		{
			if(info.Find("{")==-1||info.Find("}")==-1)
				continue;
			linkman.Getcontacts(info);
			if(linkman.sign=="del")
				continue; 
			/*���ж��Ƿ�ͬʱ����������Ͽ������*/
			if((linkman.city==m_combobox_str_city||m_combobox_str_city=="ȫ��")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="ȫ��"))
				m_listofcontacts.AddString(linkman.name);
		}
		addressbook.Close();
	}
	else
		MessageBox("False","failure");
	int i=0;
	while(!(buffer[i].IsEmpty()))
	{
		linkman.Getcontacts(buffer[i]);
		if(linkman.sign=="del")
		{
			i++;
			continue;
		}
		if((linkman.city==m_combobox_str_city||m_combobox_str_city=="ȫ��")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="ȫ��"))
			m_listofcontacts.AddString(linkman.name);
		i++;
	}
	UpdateData(FALSE);
}


void CMy918108320122Dlg::OnCbnKillfocusComboSex()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	if(addressbook.Open("ͨѶ¼.txt",CFile::modeRead))
	{
		addressbook.SeekToBegin();
		m_listofcontacts.ResetContent();
		while(addressbook.ReadString(info))   
		{
			if(info.Find("{")==-1||info.Find("}")==-1)
				continue;
			linkman.Getcontacts(info);
			if(linkman.sign=="del")
				continue;
			/*���ж��Ƿ�ͬʱ����������Ͽ������*/
			if((linkman.city==m_combobox_str_city||m_combobox_str_city=="ȫ��")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="ȫ��"))
				m_listofcontacts.AddString(linkman.name);
		}
		addressbook.Close();
	}
	else
		MessageBox("False","failure");
	int i=0;
	while(!(buffer[i].IsEmpty()))
	{
		linkman.Getcontacts(buffer[i]);
		if(linkman.sign=="del")
		{
			i++;
			continue;
		}
		if((linkman.city==m_combobox_str_city||m_combobox_str_city=="ȫ��")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="ȫ��"))
			m_listofcontacts.AddString(linkman.name);
		i++;
	}
	UpdateData(FALSE);
}


void CMy918108320122Dlg::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bool flag=true;
	CString str;
	Caddcontactsdlg newlinkman;
	UpdateData();
	for(int j=1;j<m_combobox_city.GetCount();j++)
	{
		m_combobox_city.GetLBText(j,str);
		newlinkman.citybuffer[j]=str;          //�������Ի���ĳ�����Ͽ�����ݵ������ϵ�˶Ի���ĳ�����Ͽ�
	}
	newlinkman.DoModal();
	if(!(newlinkman.linkman.name.IsEmpty()))
		m_listofcontacts.AddString(newlinkman.linkman.name);
	for(int i=1;i<m_combobox_city.GetCount();i++)          //�ж��Ƿ��Ѻ�����
	{	
		CString stri;
		m_combobox_city.GetLBText(i,stri);
		if((newlinkman.linkman.city!=stri)&&(!(newlinkman.linkman.city.IsEmpty())))
			flag=true;
		else
		{
			flag=false;
			break;
		}
	}
	if(flag)
	{
		m_combobox_city.AddString(newlinkman.linkman.city);
	}
	buffer[count_of_buffer++]=newlinkman.linkman.putout();
	
}


void CMy918108320122Dlg::OnBnClickedDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CStdioFile  addressbook;
	CString name,info;
	Ccontacts linkman;
	int choice=m_listofcontacts.GetCurSel();  //������ѡ�������
	if(choice!=-1)
	{
		m_listofcontacts.GetText(choice,name);    //��ȡѡ�����ϵ�˵�����
		m_listofcontacts.DeleteString(choice);
	}
	else
	{
		MessageBox("δѡ���κ���Ŀ","����",MB_ICONERROR);
		return;
	}
	if(addressbook.Open("ͨѶ¼.txt",CFile::modeReadWrite))   //�ļ��ж�ȡ����ӱ��
	{
		addressbook.SeekToBegin();
		while(addressbook.ReadString(info))  //�ж�ȡ
		{
			if(info.Find("{")==-1||info.Find("}")==-1)
				continue;
			linkman.Getcontacts(info);
			if(linkman.name==name)
			{
				addressbook.Seek(-info.GetLength()-2,CFile::current);
				linkman.sign="del";
		        info=linkman.putout();
		        addressbook.Write(info,info.GetLength());
		        addressbook.Close();
				break;
			}
		}
	}
	else
		MessageBox("False","failure");
	int i=0;
	while(!(buffer[i].IsEmpty()))      //�������еĶ�Ӧ����ӱ��
	{
		linkman.Getcontacts(buffer[i]);
		if(linkman.name==name)
		{
			linkman.sign="del";
			buffer[i]=linkman.putout();
			break;
		}
		i++;
	}
	UpdateData(FALSE);
}


void CMy918108320122Dlg::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	if(addressbook.Open("ͨѶ¼.txt",CFile::modeReadWrite))
	{
		addressbook.SeekToEnd();             //ĩβд��

		for(int i=0;i<100;i++)                //������д�루�Թ���ǵ�ɾ���
		{
			if(buffer[i].IsEmpty())
				continue;
			linkman.Getcontacts(info);
			if(linkman.sign=="del")
				continue;
			buffer[i]="\n"+buffer[i]+"\n";
			addressbook.WriteString(buffer[i]);
			
		}

		addressbook.SeekToBegin();

		while(addressbook.ReadString(info))  //�ļ���ɾ�������
		{

			if(info.Find("{")==-1||info.Find("}")==-1)
				continue;
			linkman.Getcontacts(info);
			if(linkman.sign=="del")
			{
				addressbook.Seek(-info.GetLength()-2,CFile::current);
				CString str="---------------------------------------------------";
				addressbook.Write(str,info.GetLength());
				addressbook.Seek(str.GetLength(),CFile::current);
			}
		}
		addressbook.Close();
		/*��ջ�����*/
		count_of_buffer=0;
		for(int i=0;i<100;i++)
		{
			buffer[i].Empty();
		}
		MessageBox("�ѱ���","ע��",MB_ICONWARNING);
	}
	else
		MessageBox("False","failure");
	UpdateData(FALSE);
}


void CMy918108320122Dlg::OnIdcancel()
{
	// TODO: �ڴ���������������
	UpdateData();
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	if(MessageBox("�����˳������ϴα���֮��Ĳ������ᱻ��¼���һ��������ݽ������","����",MB_ICONWARNING|IDOK)==IDOK)
	{
		if(addressbook.Open("ͨѶ¼.txt",CFile::modeReadWrite))
		{
			while(addressbook.ReadString(info))  //�ļ��и�дδ��ɾ����ı��
			{
				if(info.Find("{")!=-1&&info.Find("}")!=-1)
				{
					linkman.Getcontacts(info);
					if(linkman.sign=="del")
						linkman.sign="non";
					info=linkman.putout();
					addressbook.Seek(-info.GetLength()-2,CFile::current);
					addressbook.Write(info,info.GetLength());
					addressbook.Seek(info.GetLength(),CFile::current);
				}
			}
			addressbook.Close();
		}
		else
			MessageBox("False","failure");
		UpdateData(FALSE);
		CDialogEx::OnCancel(); //�������򣬻�����ֱ���ͷ�
	}
	else
	{
		UpdateData(FALSE);
		return;
	}
	
}