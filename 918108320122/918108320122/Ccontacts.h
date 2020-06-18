#pragma once
#include "918108320122Dlg.h"//加入对话框的头文件
class Ccontacts
{
public:                  //添加的成员变量
	CString name;
	CString sex;
	CString birthday;
	CString city;
	CString company;
	CString officeTel;
	CString homeTel;
	CString postcode;
	CString email;
	CString sign;   //标记，用于识别联系人是否为潜在删除对象
public:
	Ccontacts(void);
	~Ccontacts(void);
	void Getcontacts(CString str);   //从读取的每行字符串中分拣出各个变量的值
	void transinfo(CMy918108320122Dlg *obj); //将各个变量的值传递给控件
	CString putout();    //格式化输出为一个字符串
};

