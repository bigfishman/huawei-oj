#include <stdlib.h>
#include "oj.h"
#include <string.h>

#include <string>
#include <vector>
using namespace std;

vector<string> vec; 

/*****************************************************************
功能:存储输入的字符创

输入:字符串

输出:无
     
返回:0表示成功,其它返回-1
****************************************************************/
int  AddString(char *strValue)
{
	if (strValue == NULL || *strValue == '\0') return -1; 
	char temp[9];
	int i = 0;
	while(strValue[i]) {
		int j = 0;
		while(j<8) {
			if (strValue[i]) temp[j++] = strValue[i++];
			else break;
		}
		while(j<8) temp[j++] = '0';
		temp[8] = '\0';
		vec.push_back(string(temp));
	}
	return 0;
}

/****************************************************************
功能:获取补位后的二维数组的长度

输入:无

输出:无
     
返回:二维数组长度
******************************************************************/
int  GetLength()
{
	return vec.size();
}

/*****************************************************************************
功能:将补位后的二维数组，与输入的二维数组做比较

输入:strInput:输入二维数组,iLen：输入的二维数组的长度

输出:无
     
返回:若相等,返回0;不相等,返回-1.其它:-1;
******************************************************************************/
int  ArrCmp(char strInput[][9],int iLen)
{
	if (strInput == NULL || iLen <= 0 || GetLength() != iLen) return -1;
	
	for(int i=0; i<iLen; ++i)
		if (strcmp(strInput[i],vec[i].c_str())) return -1;
	vec.clear(); 
	return 0;
}

/*
#include <cassert>
using namespace std;

#define CPPUNIT_ASSERT assert

int main(void)
{
	AddString("12345678");
	AddString("ABCDEFG1234");
	AddString("1234567890");


	char strRst[][9] = {"12345678","ABCDEFG1","23400000","12345678","90000000"};

	CPPUNIT_ASSERT(5 == GetLength());
	CPPUNIT_ASSERT(0 == ArrCmp(strRst,5));
	CPPUNIT_ASSERT(0 == GetLength());
} */

