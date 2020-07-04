
// 918108320122Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "918108320122.h"
#include "918108320122Dlg.h"
#include "afxdialogex.h"
#include "Ccontacts.h"   //加入Ccontacts类头文件
#include "Caddcontactsdlg.h" //加入Caddcontactsdlg类头文件

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMy918108320122Dlg 对话框



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


// CMy918108320122Dlg 消息处理程序

BOOL CMy918108320122Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	MessageBox("Test of teamwork based on GitHub","Warning",MB_ICONWARNING|IDOK);
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	if(addressbook.Open("通讯录.txt",CStdioFile::modeCreate|CStdioFile::modeRead|CStdioFile::modeNoTruncate)) //打开并读取文件
	{
		addressbook.SeekToBegin();
		m_combobox_city.AddString("全部");    //城市组合框添加“全部”选项
		while(addressbook.ReadString(info))   //行读取
		{
			if(info.Find("{")==-1||info.Find("}")==-1)     //略去无效字符串行
				continue;
			linkman.Getcontacts(info);       //从读取的每行字符串中分拣出各个变量的值
			if(linkman.sign=="del")
				continue;
			m_listofcontacts.AddString(linkman.name);  //插入列表
			m_combobox_city.AddString(linkman.city);
		}
		addressbook.Close();
		for(int i=1;i<m_combobox_city.GetCount();i++)          //删去重复添加的城市
			for(int j=i+1;j<m_combobox_city.GetCount();j++)
			{
				CString stri,strj;
				m_combobox_city.GetLBText(i,stri);
				m_combobox_city.GetLBText(j,strj);
				if(strj==stri)
					m_combobox_city.DeleteString(j--);       
			}
		m_combobox_sex.AddString("全部");                //为性别组合框添加相关内容（也可先添加再删重）
		m_combobox_sex.AddString("男");
		m_combobox_sex.AddString("女");
		m_combobox_city.GetLBText(0,m_combobox_str_city);
		m_combobox_sex.GetLBText(0,m_combobox_str_sex);
	}
	else                                      //若出现错误,退出程序
	{
		MessageBox("False","failure");
		exit(0);
	}
	m_add.AutoLoad(IDC_ADD,this);     //加载位图按钮
	m_delete.AutoLoad(IDC_DELETE,this);
	m_save.AutoLoad(IDC_SAVE,this);
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy918108320122Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy918108320122Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy918108320122Dlg::OnLbnSelchangeListContacts()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CStdioFile  addressbook;
	CString name,info;
	Ccontacts linkman;
	int choice=m_listofcontacts.GetCurSel();  //定义所选择的行数
	m_listofcontacts.GetText(choice,name);    //获取选择的联系人的姓名
	if(addressbook.Open("通讯录.txt",CFile::modeRead))
	{
		addressbook.SeekToBegin();
		while(addressbook.ReadString(info))  //文件行读取，检索姓名
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
	while(!(buffer[i].IsEmpty()))    //缓存区读取并检索
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	m_combobox_city.GetLBText(m_combobox_city.GetCurSel(),m_combobox_str_city);     //更新组合框中的文字内容
	if(addressbook.Open("通讯录.txt",CFile::modeRead))
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
			/*需判断是否同时符合两个组合框的条件*/
			if((linkman.city==m_combobox_str_city||m_combobox_str_city=="全部")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="全部"))
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
		if((linkman.city==m_combobox_str_city||m_combobox_str_city=="全部")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="全部"))
			m_listofcontacts.AddString(linkman.name);
		i++;
	}
	UpdateData(FALSE);
}


void CMy918108320122Dlg::OnCbnKillfocusComboCity()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	if(addressbook.Open("通讯录.txt",CFile::modeRead))
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
			/*需判断是否同时符合两个组合框的条件*/
			if((linkman.city==m_combobox_str_city||m_combobox_str_city=="全部")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="全部"))
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
		if((linkman.city==m_combobox_str_city||m_combobox_str_city=="全部")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="全部"))
			m_listofcontacts.AddString(linkman.name);
		i++;
	}
	UpdateData(FALSE);
}


void CMy918108320122Dlg::OnCbnSelchangeComboSex()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	m_combobox_sex.GetLBText(m_combobox_sex.GetCurSel(),m_combobox_str_sex);    //更新组合框中的文字内容
	if(addressbook.Open("通讯录.txt",CFile::modeRead))
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
			/*需判断是否同时符合两个组合框的条件*/
			if((linkman.city==m_combobox_str_city||m_combobox_str_city=="全部")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="全部"))
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
		if((linkman.city==m_combobox_str_city||m_combobox_str_city=="全部")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="全部"))
			m_listofcontacts.AddString(linkman.name);
		i++;
	}
	UpdateData(FALSE);
}


void CMy918108320122Dlg::OnCbnKillfocusComboSex()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	if(addressbook.Open("通讯录.txt",CFile::modeRead))
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
			/*需判断是否同时符合两个组合框的条件*/
			if((linkman.city==m_combobox_str_city||m_combobox_str_city=="全部")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="全部"))
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
		if((linkman.city==m_combobox_str_city||m_combobox_str_city=="全部")&&(linkman.sex==m_combobox_str_sex||m_combobox_str_sex=="全部"))
			m_listofcontacts.AddString(linkman.name);
		i++;
	}
	UpdateData(FALSE);
}


void CMy918108320122Dlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	bool flag=true;
	CString str;
	Caddcontactsdlg newlinkman;
	UpdateData();
	for(int j=1;j<m_combobox_city.GetCount();j++)
	{
		m_combobox_city.GetLBText(j,str);
		newlinkman.citybuffer[j]=str;          //传递主对话框的城市组合框的数据到添加联系人对话框的城市组合框
	}
	newlinkman.DoModal();
	if(!(newlinkman.linkman.name.IsEmpty()))
		m_listofcontacts.AddString(newlinkman.linkman.name);
	for(int i=1;i<m_combobox_city.GetCount();i++)          //判断是否已含城市
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CStdioFile  addressbook;
	CString name,info;
	Ccontacts linkman;
	int choice=m_listofcontacts.GetCurSel();  //定义所选择的行数
	if(choice!=-1)
	{
		m_listofcontacts.GetText(choice,name);    //获取选择的联系人的姓名
		m_listofcontacts.DeleteString(choice);
	}
	else
	{
		MessageBox("未选中任何项目","错误",MB_ICONERROR);
		return;
	}
	if(addressbook.Open("通讯录.txt",CFile::modeReadWrite))   //文件中读取并添加标记
	{
		addressbook.SeekToBegin();
		while(addressbook.ReadString(info))  //行读取
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
	while(!(buffer[i].IsEmpty()))      //缓存区中的对应项添加标记
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	if(addressbook.Open("通讯录.txt",CFile::modeReadWrite))
	{
		addressbook.SeekToEnd();             //末尾写入

		for(int i=0;i<100;i++)                //缓存区写入（略过标记的删除项）
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

		while(addressbook.ReadString(info))  //文件中删除标记项
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
		/*清空缓存区*/
		count_of_buffer=0;
		for(int i=0;i<100;i++)
		{
			buffer[i].Empty();
		}
		MessageBox("已保存","注意",MB_ICONWARNING);
	}
	else
		MessageBox("False","failure");
	UpdateData(FALSE);
}


void CMy918108320122Dlg::OnIdcancel()
{
	// TODO: 在此添加命令处理程序代码
	UpdateData();
	CStdioFile  addressbook;
	CString info;
	Ccontacts linkman;
	if(MessageBox("您将退出程序，上次保存之后的操作不会被记录，且缓存区数据将被清除","警告",MB_ICONWARNING|IDOK)==IDOK)
	{
		if(addressbook.Open("通讯录.txt",CFile::modeReadWrite))
		{
			while(addressbook.ReadString(info))  //文件中改写未被删除项的标记
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
		CDialogEx::OnCancel(); //结束程序，缓存区直接释放
	}
	else
	{
		UpdateData(FALSE);
		return;
	}
	
}