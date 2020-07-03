#pragma once
#include "afxwin.h"
#include "Ccontacts.h"   //加入联系人类


// Caddcontactsdlg 对话框

class Caddcontactsdlg : public CDialogEx
{
	DECLARE_DYNAMIC(Caddcontactsdlg)

public:
	Caddcontactsdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Caddcontactsdlg();

// 对话框数据
	enum { IDD = IDD_ADDCONTACTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	CString m_new_name;
	int m_new_sex;
	CComboBox m_new_birthyear;
	CString m_new_birthyearstr;
	CComboBox m_new_birthmonth;
	CString m_new_birthmonthstr;
	CComboBox m_new_birthday;
	CString m_new_birthdaystr;
	CComboBox m_new_city;
	CString m_new_citystr;
	CString m_new_company;
	CString m_new_officeTel;
	CString m_new_homeTel;
	CString m_new_postcode;
	CString m_new_email;
	Ccontacts linkman;
	CString citybuffer[50];           //获取主对话框的城市组合框的数据缓存区
public:
	virtual BOOL OnInitDialog();//增加重写初始化函数
	void loaddate(); //用于加载日期的三个组合框中的项目
	void loadcity(); //用于加载城市组合框中的项目
	afx_msg void OnCbnSelchangeComboNewMonth();
	afx_msg void OnBnClickedOk();
	afx_msg void OnIdcancel();
};
