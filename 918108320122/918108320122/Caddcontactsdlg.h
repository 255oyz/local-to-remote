#pragma once
#include "afxwin.h"
#include "Ccontacts.h"   //������ϵ����


// Caddcontactsdlg �Ի���

class Caddcontactsdlg : public CDialogEx
{
	DECLARE_DYNAMIC(Caddcontactsdlg)

public:
	Caddcontactsdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Caddcontactsdlg();

// �Ի�������
	enum { IDD = IDD_ADDCONTACTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
	CString citybuffer[50];           //��ȡ���Ի���ĳ�����Ͽ�����ݻ�����
public:
	virtual BOOL OnInitDialog();//������д��ʼ������
	void loaddate(); //���ڼ������ڵ�������Ͽ��е���Ŀ
	void loadcity(); //���ڼ��س�����Ͽ��е���Ŀ
	afx_msg void OnCbnSelchangeComboNewMonth();
	afx_msg void OnBnClickedOk();
	afx_msg void OnIdcancel();
};
