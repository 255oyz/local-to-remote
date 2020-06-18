#include "stdafx.h"
#include "Ccontacts.h"

Ccontacts::Ccontacts(void)
{
}


Ccontacts::~Ccontacts(void)
{
}


void Ccontacts::Getcontacts(CString info)
{
	name=info.Mid(info.Find("{")+1,info.Find("_")-info.Find("{")-1);
	sex=info.Mid(info.Find("_")+1,info.Find("|")-info.Find("_")-1);
	birthday=info.Mid(info.Find("|")+1,info.Find(",")-info.Find("|")-1);
	city=info.Mid(info.Find(",")+1,info.Find(".")-info.Find(",")-1);
	company=info.Mid(info.Find(".")+1,info.Find("*")-info.Find(".")-1);
	officeTel=info.Mid(info.Find("*")+1,info.Find("+")-info.Find("*")-1);
	homeTel=info.Mid(info.Find("+")+1,info.Find("/")-info.Find("+")-1);
	postcode=info.Mid(info.Find("/")+1,info.Find("=")-info.Find("/")-1);
	email=info.Mid(info.Find("=")+1,info.Find("$")-info.Find("=")-1);
	sign=info.Mid(info.Find("$")+1,info.Find("}")-info.Find("$")-1);
	if(sign.IsEmpty())
		sign="non";
}


void Ccontacts::transinfo(CMy918108320122Dlg *obj)
{
	obj->m_name=name;
	obj->m_sex=sex;
	obj->m_birthday=birthday;
	obj->m_city=city;
	obj->m_company=company;
	obj->m_officeTel=officeTel;
	obj->m_homeTel=homeTel; 
	obj->m_postcode=postcode;
	obj->m_email=email;
}


CString Ccontacts::putout()
{
	CString out;
	out.Format("{%s_%s|%s,%s.%s*%s+%s/%s=%s$%s}",name,sex,birthday,city,company,officeTel,homeTel,postcode,email,sign);
	return out;
}


