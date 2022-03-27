const int BUFSIZE = 100000;					// 100KB ... I/O 읽기 단위 - 클수록 성능향상
const int BIGBUFSIZE = 100 * 1024 * 1024;	// 100MB ... 포스트의 최대 크기 단위 - 클수록 대용량 포스트 호환
const char c_ps[] = "<post slogan";
const char c_pe[] = "</post>";
const char c_ns[] = "<notice ";
const char c_ne[] = "</notice>";

class TTXMLParseEngine
{
/************************
// Reader Part 
************************/

// common variables
public:
	TTXMLParseEngine();

public:
	struct _pd {
		int s, e;
		char title[80];
		char cate[80];
	} postData[100000];
	int postCnt;

	char migrational[10];
	char categories[100][80];
	int catecnt;
	int pds, pde;
	int nds, nde;
	DWORD fileLen;
	char orgFilename[512];

public:
	int searchStr(char *orgdat, char *str, int size, int sindex=0);
	int searchStrReverse(char *orgdat, char *str, int size);
	int searchStrFromFile(FILE *fp, char *str, int sindex = 0);
	int searchStrFromFileReverse(FILE *fp, char *str, int eindex = 0);
	bool parseTTXMLData(FILE *fp);
	int getNextPostIndex(int index, FILE *fp);
	int getPostEndIndex(int index, FILE *fp);
	int readData(int si, int ei, FILE *fp, char *dest);
	int getBetweenIndex(char *data, int dataLen, char *s, char *e, char *dest, int index=0);
	int getInnerXML(char *data, int dataLen, char *tag, char *dest, int sindex=0);
	int getCategoryName(char *data, char *dest);
	bool getPostTagContent(char *data, int dataLen, char *tag, char *dest);
	int getPostData(FILE *fp, int index, _pd &pd);
	bool analyzeFile(char *filename);


/************************
// Writer Part 
************************/
public:
	int queue[100000];
	int queueCnt;

public:
	void emptyQueue();
	void addQueue(int index);
	void addQueueFromCategory(char *cate);
	int calcPostSize();
	bool out_Guestbook;
	bool out_Notice;
	bool outputTTXMLFile(char *filepath);
};