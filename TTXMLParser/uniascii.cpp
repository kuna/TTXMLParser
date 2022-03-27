// unicode 2 ASCII, ASCII 2 unicode free converter
// by kuna - kuna.wo.tc

#include "uniascii.h"
#include "stdafx.h"

int Unicode2ASCII(WCHAR *uni, char *ascii)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, uni, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, uni, -1, ascii, nLen, 0, 0);
	return nLen;
}
int ASCII2Unicode(char *ascii, WCHAR *uni)
{
	int nLen = MultiByteToWideChar(CP_ACP, 0,ascii, -1, NULL, NULL);
	MultiByteToWideChar(CP_ACP, 0, ascii, -1, uni, nLen);
	return nLen;
}
int DecodetoUtf8(LPCSTR utf8str, WCHAR *str)
{
	int size = MultiByteToWideChar(CP_UTF8, 0, utf8str, -1, NULL, 0);
	LPWSTR wStr = new WCHAR[size];
	MultiByteToWideChar(CP_UTF8, 0, utf8str, -1, wStr, size);
	USES_CONVERSION;
	wcscpy(str, wStr);
	delete[] wStr;
	return size;
}

int DecodeUTF8(char *pszCode, char *str)  
{
     BSTR    bstrWide;  
     char*   pszAnsi;  
     int     nLength;      

     // Get nLength of the Wide Char buffer  
     nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1,NULL, NULL);  
     bstrWide = SysAllocStringLen(NULL, nLength);  

     // Change UTF-8 to Unicode (UTF-16)  
     MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1, bstrWide,nLength);  

     // Get nLength of the multi byte buffer   
     nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);  

    // Change from unicode to mult byte  
     WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, str, nLength, NULL, NULL);  
     SysFreeString(bstrWide);

	 return 0;
}