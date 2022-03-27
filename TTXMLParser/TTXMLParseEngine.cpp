#include "stdafx.h"
#include "TTXMLParseEngine.h"
#include "uniascii.h"

TTXMLParseEngine::TTXMLParseEngine()
{
	fileLen=0;
	postCnt=0;
	catecnt=0;
	queueCnt=0;
	out_Guestbook = true;
	out_Notice = true;
	strcpy(orgFilename, "");
}

int TTXMLParseEngine::searchStr(char *orgdat, char *str, int size, int sindex)
{
	int l = strlen(str);
	for (int i=sindex; i<size-l; i++)
		if (memcmp(orgdat+i, str, l) == 0) return i;
	return -1;
}
int TTXMLParseEngine::searchStrReverse(char *orgdat, char *str, int size)
{
	int l = strlen(str);
	for (int i=size-l-1; i>=0; i--)
		if (memcmp(orgdat+i, str, l) == 0) return i;
	return -1;
}
int TTXMLParseEngine::searchStrFromFile(FILE *fp, char *str, int sindex)
{
	fseek(fp, 0, SEEK_END);
	DWORD flen = ftell(fp);

	DWORD seekpos = sindex;
	char *buf = (char *)malloc(BUFSIZE);

	while (seekpos < flen)
	{
		fseek(fp, seekpos, SEEK_SET);
		fread(buf, 1, BUFSIZE, fp);
		int r = searchStr(buf, (char *)str, BUFSIZE);
		if (r >= 0)
		{
			// check vaildation
			seekpos += r;
			fseek(fp, seekpos, SEEK_SET);
			int l = strlen(str);
			while (1)
			{
				fseek(fp, seekpos, SEEK_SET);
				fread(buf, 1, l, fp);
				if (memcmp(buf, str, l) == 0)
				{
					// exit func
					delete buf;
					return seekpos;
				}
				seekpos++;
			}
			break;
		}

		seekpos += BUFSIZE - 10;
	}

	delete buf;
	return -1;
}
int TTXMLParseEngine::searchStrFromFileReverse(FILE *fp, char *str, int eindex)
{
	fseek(fp, 0, SEEK_END);
	DWORD flen = ftell(fp);

	DWORD seekpos = flen - BUFSIZE - eindex;
	if (flen < BUFSIZE) seekpos = 0;
	char *buf = (char *)malloc(BUFSIZE);

	while (seekpos > 0)
	{
		fseek(fp, seekpos, SEEK_SET);
		fread(buf, 1, BUFSIZE, fp);
		int r = searchStrReverse(buf, (char *)str, BUFSIZE);
		if (r >= 0)
		{
			// check vaildation
			seekpos += r;
			fseek(fp, seekpos, SEEK_END);
			int l = strlen(str);
			while (1)
			{
				fseek(fp, seekpos, SEEK_SET);
				fread(buf, 1, l, fp);
				if (memcmp(buf, str, l) == 0) {
					seekpos+=l;/*문자열 길이만큼 추가해야함*/
					delete buf;
					return seekpos;
				}
				seekpos++;
			}
			break;
		}

		seekpos -= BUFSIZE - 10;
	}

	delete buf;
	return -1;
}

// start main code
bool TTXMLParseEngine::parseTTXMLData(FILE *fp)
{
	if (!fp) return false;

	char *buf = (char *)malloc(BUFSIZE);
	fseek(fp, 0 ,SEEK_END);
	fileLen = ftell(fp);

	pds = searchStrFromFile(fp, (char *)c_ps);
	pde = searchStrFromFileReverse(fp, (char *)c_pe);
	nds = searchStrFromFile(fp, (char *)c_ns, pde);
	nde = searchStrFromFileReverse(fp, (char *)c_ne);

	delete buf;
	return true;
}

/*****************************************
// 포스트 정보를 얻어올 때				//

1. 전체를 읽지 않으며 <title>, <category>부분만 읽는다
2. </post> 태그를 찾아서, 위와 같이 "vaildation" 작업을 통해 끝부분 check
... 쭉.읽다가, (getNextPostIndex < 0)일때 Exit
*****************************************/
int TTXMLParseEngine::getNextPostIndex(int index, FILE *fp)
{
	return searchStrFromFile(fp, (char *)c_ps, index);
}
int TTXMLParseEngine::getPostEndIndex(int index, FILE *fp)
{
	int _r = searchStrFromFile(fp, (char *)c_pe, index);
	if (_r<0) return -1; else return _r + strlen(c_pe);
}
int TTXMLParseEngine::readData(int si, int ei, FILE *fp, char *dest)
{
	fseek(fp, si, SEEK_SET);
	fread(dest, 1, ei-si, fp);
	return ei-si;	//len
}
int TTXMLParseEngine::getBetweenIndex(char *data, int dataLen, char *s, char *e, char *dest, int index)
{
	char *nd = data + index;
	int si = searchStr(nd, s, dataLen-index);
	int ei = searchStr(nd, e, dataLen-index, si+strlen(s));
	if (si < 0 || ei < 0) return -1;
	si += strlen(s);
	memcpy(dest, nd+si, ei-si);
	dest[ei-si] = '\0';

	return ei;
}
bool TTXMLParseEngine::getPostTagContent(char *data, int dataLen, char *tag, char *dest)
{
	// create start & end tag
	char ts[100], te[100];
	sprintf(ts, "<%s>", tag);
	sprintf(te, "</%s>", tag);

	return getBetweenIndex(data, dataLen, ts, te, dest);
}
int TTXMLParseEngine::getInnerXML(char *data, int dataLen, char *tag, char *dest, int sindex)
{
	// create start & end tag
	char ts[100], te[100];
	sprintf(ts, "<%s>", tag);
	sprintf(te, "</%s>", tag);

	// determine with level
	int p = sindex-1;
	int lv = -1;
	int s = -1;

	while (p < dataLen)
	{
		int s1 = searchStr(data, ts, dataLen, p+1);
		int s2 = searchStr(data, te, dataLen, p+1);
		if (s1 < 0 || s2 < 0) break;
		if (s1 < s2) {
			p = s1;
			lv++;
			if (s < 0) s = p + strlen(ts);
		} else {
			p = s2;
			if (lv == 0)
			{
				// exit Func
				memcpy(dest, data+s, p-s);
				dest[p-s] = 0x00;
				return p+strlen(te);
			}
			lv--;
		}
	}

	return -1;
}
int TTXMLParseEngine::getCategoryName(char *data, char *dest)
{
	int l = strlen(data);
	int si = searchStr(data, "<name>", l);
	int ei = searchStr(data, "</name>", l, si+10);
	if (si < 0 || ei < 0) return -1;

	memcpy(dest, data+si+6, ei-si-6);
	dest[ei-si-6] = 0x00;

	return ei+10;
}
int TTXMLParseEngine::getPostData(FILE *fp, int index, _pd &pd)
{
	int si = getNextPostIndex(index, fp);
	int ei = getPostEndIndex(index, fp);
	if (si < 0 || ei < 0) return -1;

	pd.s = si;
	pd.e = ei;

	// returns next point (end point)
	return ei;
}

bool TTXMLParseEngine::analyzeFile(char *filename)
{
	FILE *fp = fopen(filename, "rb");
	if (!fp) return false;

	/******************
	1. parseTTXMLData로 파일의 전반적인 구조 파악 [헤더/포스트/방명록/레퍼러로그]
	******************/
	if (!parseTTXMLData(fp)) return false;

	/******************
	2. 포스트를 있는데까지 읽음 (메모리제한 100mb ... 설정 가능하게 해볼까나..)
	******************/
	char *buf = (char*)malloc(BIGBUFSIZE);
	int i = pds;
	while (1) {
		i = getPostData(fp, i, postData[ postCnt ]);
		if (i < 0) break;

		int l = readData(postData[postCnt].s, postData[postCnt].e, fp, buf);
		getPostTagContent(buf, l, "title", postData[postCnt].title);
		getPostTagContent(buf, l, "category", postData[postCnt].cate);
		getPostTagContent(postData[postCnt].cate, strlen(postData[postCnt].cate), "name", postData[postCnt].cate);
		DecodeUTF8(postData[postCnt].title, postData[postCnt].title);
		DecodeUTF8(postData[postCnt].cate, postData[postCnt].cate);
		postCnt++;
	}

	/******************
	3. 카테고리 및 migrational 분석
	******************/
	int l = readData(0, pds, fp, buf);
	getBetweenIndex(buf, l, "migrational=\"", "\"", migrational);

	int p = 0;
	char cateData[1000];
	while (1) {
		p = getInnerXML(buf, l, "category", cateData, p);
		if (p < 0) break;
		DecodeUTF8(cateData, cateData);

		int ni = getCategoryName(cateData, categories[catecnt]);
		int oi = catecnt;
		catecnt++;

		while (1)
		{
			char _t[100];
			int r = getCategoryName(cateData+ni, _t);
			if (r < 0) break;
			ni += r;
			sprintf(categories[catecnt], "%s/%s", categories[oi], _t);
			catecnt++;
		}
	}

	delete buf;
	strcpy(orgFilename, filename);
	fclose(fp);

	return true;
}

void TTXMLParseEngine::emptyQueue()
{
	queueCnt = 0;
}
void TTXMLParseEngine::addQueue(int index)
{
	queue[queueCnt] = index;
	queueCnt++;
}
void TTXMLParseEngine::addQueueFromCategory(char *cate)
{
	int l = strlen(cate);
	for (int i=0; i<postCnt; i++)
	{
		if (memcmp(postData[i].cate, cate, l) == 0)
		{
			queue[queueCnt] = i;
			queueCnt++;
		}
	}
}
int TTXMLParseEngine::calcPostSize()
{
	int r = 0;
	for (int i=0; i<queueCnt; i++)
	{
		r += postData[ queue[i] ].e - postData[ queue[i] ].s;
	}
	return r;
}
bool TTXMLParseEngine::outputTTXMLFile(char *filepath)
{
	// 먼저 검사
	if (orgFilename[0] == 0x00) return false;

	FILE *fp = fopen(orgFilename, "rb");
	if (!fp) return false;

	FILE *fpo = fopen(filepath, "wb");
	if (!fpo) return false;

	char *buf = (char*)malloc(BIGBUFSIZE);
	int si, ei, diff;

	/***********************
	// 1. Header을 Output할 것
	***********************/
	readData(0, pds, fp, buf);
	si = searchStr(buf, "migrational=\"", pds);
	if (si < 0) return false;
	ei = searchStr(buf, "\"", pds, si+13);
	if (ei < si) return false;
	fwrite(buf, 1, si+13, fpo);
	fwrite(migrational, 1, strlen(migrational), fpo);
	fwrite(buf+ei, 1, pds-ei, fpo);

	/***********************
	// 2. Queue의 Post들을 Output할것
	***********************/
	for (int i=0; i<queueCnt; i++)
	{
		int n = queue[i];
		si = postData[n].s;
		ei = postData[n].e;

		int l = readData(si, ei, fp, buf);
		fwrite(buf, 1, l, fpo);
	}

	/***********************
	// 3. Notice Output?
	***********************/
	if (out_Notice && nds > 0)
	{
		readData(nds, nde, fp, buf);
		fwrite(buf, 1, nde-nds, fpo);
	}

	/***********************
	// 4. Etc(Guestbook) Output?
	***********************/
	if (out_Guestbook && nde > 0)
	{
		readData(nde, fileLen, fp, buf);
		fwrite(buf, 1, fileLen-nde, fpo);
	} else {
		fwrite("</blog>   ", 1, 8, fpo);
	}

	delete buf;
	fclose(fpo);
	fclose(fp);

	return true;
}