
// 918108320122Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "resource.h"    


// CMy918108320122Dlg �Ի���
class CMy918108320122Dlg : public CDialogEx
{
// ����
public:
	CMy918108320122Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������

	enum { IDD = IDD_MY918108320122_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	/*Ϊ����ؼ���ӵı�������Ӧ����*/
public:
	CListBox m_listofcontacts;
	CString m_name;
	CString m_sex;
	CString m_birthday;
	CString m_city;
	CString m_company;
	CString m_officeTel;
	CString m_homeTel;
	CString m_postcode;
	CString m_email;
	CComboBox m_combobox_city;
	CString m_combobox_str_city;
	CComboBox m_combobox_sex;
	CString m_combobox_str_sex;
	CBitmapButton m_add;             //λͼ��ť
	CBitmapButton m_delete;
	CBitmapButton m_save;
	CString buffer[100];            //���ӵ���ϵ�˵Ļ�����
	int count_of_buffer;
public:
	afx_msg void OnLbnSelchangeListContacts();
	afx_msg void OnLbnKillfocusListContacts();
	afx_msg void OnCbnSelchangeComboCity();
	afx_msg void OnCbnKillfocusComboCity();
	afx_msg void OnCbnSelchangeComboSex();
	afx_msg void OnCbnKillfocusComboSex();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedSave();
	afx_msg void OnIdcancel();
};
