#pragma once
#include "918108320122Dlg.h"//����Ի����ͷ�ļ�
class Ccontacts
{
public:                  //��ӵĳ�Ա����
	CString name;
	CString sex;
	CString birthday;
	CString city;
	CString company;
	CString officeTel;
	CString homeTel;
	CString postcode;
	CString email;
	CString sign;   //��ǣ�����ʶ����ϵ���Ƿ�ΪǱ��ɾ������
public:
	Ccontacts(void);
	~Ccontacts(void);
	void Getcontacts(CString str);   //�Ӷ�ȡ��ÿ���ַ����зּ������������ֵ
	void transinfo(CMy918108320122Dlg *obj); //������������ֵ���ݸ��ؼ�
	CString putout();    //��ʽ�����Ϊһ���ַ���
};

