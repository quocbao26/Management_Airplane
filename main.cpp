#include <iostream>
#include <string.h>
#include <stdio.h>
#include <mylib.h>
#include <fstream>
#include <ctype.h>
#include <ctime>
#include <conio.h>
#include <sstream> 
#include <string>
#define MAXMB 300
#define MAXVE 30

#define MAX 100
#define UP 72
#define DOWN 80
#define BACKSPACE 8
#define ENTER 13
#define ESC 27
#define RIGHT 77
#define LEFT 75

#define F1 59
#define F2 60
#define F3 61

#define ArrowRIGHT 27
#define ArrowLEFT 26
#define ArrowUP 25
#define ArrowDOWN 24

#define boxx 18 //Vi tri x bat dau cua box
#define boxy 15 //Vi tri y bat dau cua box
#define boxs 60 //Box size
#define tabx 6 // vi tri x bat dau cua table
#define taby 4  // vi tri y bat dau cua table
#define tabs 83 // table box
#define tabw 23 // table hight

#define ColorBLACK			0
#define ColorDARKBLUE		1
#define ColorDARKCYAN		3
#define ColorCDARKRED		4
#define ColorPURPLE			5
#define ColorDARKYELLOW		6
#define ColorDARKWHITE		7
#define ColorGRAY			8
#define ColorBLUE			9
#define ColorGREEN		 	10
#define ColorCYAN			11
#define ColorRED			12
#define ColorPINK			13
#define ColorYELLOW			14
#define ColorWHITE			15



/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;


//void resizeConsole(int width, int height)
//{
//	HWND console = GetConsoleWindow();
//	RECT r;
//	GetWindowRect(console, &r);
//	MoveWindow(console, r.left, r.top, width, height, TRUE);
//}

// ======= VE ===========
//struct Ve{
//	int soGhe;
//	
//};
struct ListVe{
	int n;
//	char cmnd[16];
	string *ve;

};

struct ThoiGian{
	int gio, phut, ngay, thang, nam;
};

// ==========================

// ========== CHUYEN BAY ============
struct ChuyenBay{
	char maCB[15];
	ThoiGian tgKhoiHanh;
	char sanBayDen[150];
	int trangThai;
	char soHieuMB[15];
	ListVe dsVe;	 
};
struct Node_CB{
	ChuyenBay cb;
	Node_CB *pNext;
};
struct SingleList_CB
{
	Node_CB *pHead;
	Node_CB *pTail;
};



// ========= MAY BAY==========
struct MayBay{
	char soHieuMB[15];
	char loaiMB[40];
	int soCho;
};

struct ListMayBay{
	int soluong;
	MayBay *maybay[MAXMB]; 
};


// =========== HANH KHACH ==========
struct HanhKhach{
	char cmnd[16];
	char ho[100];
	char ten[100];
	char phai[10]; 
};

struct Node_HK{
	HanhKhach HK;
	Node_HK *pLeft;
	Node_HK *pRight;
};
//typedef Node_HK *TREE_HK;
typedef Node_HK *NODPTR;
NODPTR tree;

void InitTreeHK(NODPTR &tree_hk)
{
	tree_hk = NULL;
}
bool Empty_HK(NODPTR tree_hk)
{
	return tree_hk == NULL;
}
bool CheckCMNDIsExisted(NODPTR tree_hk, char cmnd[])
{
	if (tree_hk != NULL)
	{
		if (strcmp(tree_hk->HK.cmnd, cmnd) == 0)
			return true;
		if (strcmp(tree_hk->HK.cmnd, cmnd) > 0)
			CheckCMNDIsExisted(tree_hk->pLeft, cmnd);
		else 
			CheckCMNDIsExisted(tree_hk->pRight, cmnd);
	}
	return false;
}
Node_HK *SearchHK(NODPTR tree_hk, char cmnd[])
{
	if (tree_hk != NULL)
	{
		Node_HK *pNode = tree_hk;
		while (pNode != NULL)
		{
			if (strcmp(pNode->HK.cmnd, cmnd) == 0)
				return pNode;
			else if (strcmp(pNode->HK.cmnd, cmnd) > 0)
				pNode = pNode->pLeft;
			else if (strcmp(pNode->HK.cmnd, cmnd) < 0)
				pNode = pNode->pRight;
		}
	}
	return NULL;
}

HanhKhach ThemHanhKhach()
{
	HanhKhach *hk = new HanhKhach;
	cout<<"CMND: ";
	cin>>hk->cmnd; // check cmnd trung
	cin.ignore();
	cout<<"Ho: ";
	gets(hk->ho);
	cout<<"Ten: ";
	gets(hk->ten);
	cout<<"Phai(0:Nu - 1:Nam): ";
	cin>>hk->phai;
	return *hk;
}

void PrintTree(NODPTR tree_hk)
{
	if (tree_hk != NULL)
	{
		string gt = "";
		HanhKhach hk = tree_hk->HK;
	//	if (hk.phai == 0)
		//{
		//	gt = "Nu"
	//	}
		gt = hk.phai==0?"Nu":"Nam";
		cout<<hk.cmnd<<"\t"<<hk.ho<<"\t"<<hk.ten<<"\t"<<gt<<endl;
		PrintTree(tree_hk->pLeft);
		PrintTree(tree_hk->pRight);
	}
}


void InsertHKToTree(NODPTR &tree_hk, HanhKhach hk)
{
	if (tree_hk == NULL)
	{
		Node_HK *pNode = new Node_HK;
		pNode->HK = hk;
		pNode->pLeft = pNode->pRight = NULL;
		tree_hk = pNode;
	}
	else
	{
		if (strcmp(tree_hk->HK.cmnd, hk.cmnd) > 0)
			InsertHKToTree(tree_hk->pLeft, hk);
		else if (strcmp(tree_hk->HK.cmnd, hk.cmnd) < 0)
			InsertHKToTree(tree_hk->pRight, hk);
	}
}

void XoaKiTu(char s[], int vitrixoa)
{
	int n = strlen(s);
	for (int i = vitrixoa + 1; i < n; i++)
		s[i-1] = s[i];
	s[n-1] = '\0';
}
char *fix_Ma(char ma[])
{
	if( strcmp(ma, "\0") == 0)
		return ma;
	int dai = strlen(ma);
	int dem = 0;
	for(int i = 0; i < dai; i++)
	{
		if (ma[i] == ' ')
			dem++;
	}
	if (dem == dai)
	{
		while (true)
		{
			if (ma[0] == ' ')
				XoaKiTu(ma, 0);
			else if (ma[strlen(ma)-1] == ' ')
				XoaKiTu(ma, strlen(ma)-1);
			else
				break;
		}
		return ma;
	}
		
	while (true)
	{
		if (ma[0] == ' ')
			XoaKiTu(ma, 0);
		else if (ma[strlen(ma)-1] == ' ')
			XoaKiTu(ma, strlen(ma)-1);
		else
			break;
	}
	// Xoa khoang tang o giua
	for (int i = 0; i < strlen(ma) - 1; i++)
	{
		if ((ma[i] == ' ' && ma[i+1] == ' ') || (ma[i] == ' ' && ma[i+1] != ' '))
		{
			XoaKiTu(ma, i);
			i--;
		}
	}
	if (strcmp(ma, "") != 0)
	{
		// Chuyen chu thuong thanh chu hoa
		for (int i = 0; i < strlen(ma); i++)
		{
			if (ma[i] >= 'a' && ma[i] <= 'z')
				ma[i] -= 32;
		}
	}
	return ma;
}


char *tach_Ten(char str[])
{
	char *ten = new char[100];
	
	for (int i = strlen(str)-1; i >= 0; i--)
		if (str[i] == ' ')
		{
			int k = 0;
			for (int j = i + 1; j < strlen(str); j++)
			{
				ten[k++] = str[j];
			}
			ten[k]='\0';
			break;
		}
	return ten;
}

char *tach_ho_dem(char str[])
{
	char *hodem = new char[100];

	for (int i = strlen(str)-1; i >= 0; i--)
		if (str[i] == ' ')
		{
			int k = 0;
			for (int j = 0; j < i; j++)
			{
				hodem[k++] = str[j];
			}
			hodem[k]='\0';
			break;
		}
	return hodem;
}
char *fix_HoTen(char *hoten)
{
	if( strcmp(hoten, "\0") == 0)
		return hoten;
		
	int dai = strlen(hoten);
	int dem = 0;
	for(int i = 0; i < dai; i++)
	{
		if (hoten[i] == ' ')
			dem++;
	}
	if (dem == dai)
	{
		while (true)
		{
			if (hoten[0] == ' ')
				XoaKiTu(hoten, 0);
			else if (hoten[strlen(hoten)-1] == ' ')
				XoaKiTu(hoten, strlen(hoten)-1);
			else
				break;
		}
		return hoten;
	}
	// Xoa khoang trang dau va cuoi
	while (true)
	{
		if (hoten[0] == ' ')
			XoaKiTu(hoten, 0);
		else if (hoten[strlen(hoten)-1] == ' ')
			XoaKiTu(hoten, strlen(hoten)-1);
		else
			break;
	}
	// Xoa khoang tang o giua
	for (int i = 0; i < strlen(hoten) - 1; i++)
	{
		if (hoten[i] == ' ' && hoten[i+1] == ' ')
		{
			XoaKiTu(hoten, i);
			i--;
		}
	}
	// Chuyen Hoa thanh thuong
	for(int i = 0; i < strlen(hoten); i++)
		if(hoten[i] >= 'A' && hoten[i] <= 'Z') hoten[i] += 32;
	
	hoten[0] = hoten[0] - 32; // In hoa Ki tu dau tien
	
	for(int i = 1;i < strlen(hoten); i++) // In hoa chu cai dau tien sau moi khoang trang
	{
		if(hoten[i] == ' ')
		{
			if(hoten[i+1] >= 'a' && hoten[i+1] <= 'z')
			{
				hoten[i+1] -= 32;
				i = i+1;
			}
		}
	}
	return hoten;
}
char *fix_Ten(char *ma)
{
	if( strcmp(ma, "\0") == 0)
		return ma;
	int dai = strlen(ma);
	int dem = 0;
	for(int i = 0; i < dai; i++)
	{
		if (ma[i] == ' ')
			dem++;
	}
	if (dem == dai)
	{
		while (true)
		{
			if (ma[0] == ' ')
				XoaKiTu(ma, 0);
			else if (ma[strlen(ma)-1] == ' ')
				XoaKiTu(ma, strlen(ma)-1);
			else
				break;
		}
		return ma;
	}
		
	while (true)
	{
		if (ma[0] == ' ')
			XoaKiTu(ma, 0);
		else if (ma[strlen(ma)-1] == ' ')
			XoaKiTu(ma, strlen(ma)-1);
		else
			break;
	}
	// Xoa khoang tang o giua
	for (int i = 0; i < strlen(ma) - 1; i++)
	{
		if ((ma[i] == ' ' && ma[i+1] == ' ') || (ma[i] == ' ' && ma[i+1] != ' '))
		{
			XoaKiTu(ma, i);
			i--;
		}
	}

	// Chuyen Hoa thanh thuong
	for(int i = 0; i < strlen(ma); i++)
		if(ma[i] >= 'A' && ma[i] <= 'Z') ma[i] += 32;
	
	ma[0] = ma[0] - 32; // In hoa Ki tu dau tien
	return ma;
}

char *fix_GioiTinh(char *phai)
{
	if (strcmp(phai, "\0") == 0)
		return phai;
		
	int dai = strlen(phai);
	int dem = 0;
	for (int i = 0; i < dai; i++)
	{
		if (phai[i] == ' ')
			dem++;
	}
	if (dem == dai)
	{
		while (true)
		{
			if (phai[0] == ' ')
				XoaKiTu(phai, 0);
			else if (phai[strlen(phai)-1] == ' ')
				XoaKiTu(phai, strlen(phai)-1);
			else
				break;
		}
		return phai;
	}
	// Xoa khoang trang dau va cuoi
	while (true)
	{
		if (phai[0] == ' ')
			XoaKiTu(phai, 0);
		else if (phai[strlen(phai)-1] == ' ')
			XoaKiTu(phai, strlen(phai)-1);
		else
			break;
	}
	
	// Chuyen Hoa thanh thuong
	for(int i = 0; i < strlen(phai); i++)
		if(phai[i] >= 'A' && phai[i] <= 'Z') phai[i] += 32;
	return phai;
}

void LuuFileHanhKhach(NODPTR tree_hk, ofstream &fileout)
{
	if (tree_hk != NULL)
	{
		fileout<<tree_hk->HK.cmnd<< ","<<tree_hk->HK.ho<<" "<<tree_hk->HK.ten<<","<<tree_hk->HK.phai;
		LuuFileHanhKhach(tree_hk->pLeft, fileout);
		LuuFileHanhKhach(tree_hk->pRight, fileout);
	}
}
void LuuFileHKKoDeQuy(NODPTR tree_hk)
{
	ofstream fileout;
	fileout.open("hanhkhach.txt", ios::out);
	if (fileout.fail())
	{
		cout<<"Loi mo file hanh khach";
		return;
	}
	const int STACKSIZE = 10000;
	NODPTR Stack[STACKSIZE];
	NODPTR p = tree_hk;
	int sp = -1; //Khai bao Stack rong
	do
	{
		while(p!=NULL)
		{
			Stack[++sp] = p;
			p = p->pLeft;
		}
		if (sp != -1)
		{
			p = Stack[sp--];
			fileout<<p->HK.cmnd<<","<<p->HK.ho<<" "<<p->HK.ten<<","<<p->HK.phai<<endl;
			p = p->pRight;
		}
		else break;
	}while(1);
}

void DocFileHanhKhach(NODPTR &tree_hk)
{
	ifstream filein;
	filein.open("hanhkhach.txt", ios::in);
	HanhKhach hk;
	string tmp; // lay ky tu xuong dong '\0'
	do{
		string cmnd, hoten;
	
		getline(filein, cmnd, ',');
		if(cmnd != ""){
			strcpy(hk.cmnd, cmnd.c_str());
			
			getline(filein, hoten, ',');
			char ho[100], ten[100], hotenc[200];
			strcpy(hotenc, hoten.c_str());
			
			strcpy(hk.ho, tach_ho_dem(hotenc));
		
			strcpy(hk.ten, tach_Ten(hotenc));
		
			filein>>hk.phai;
		
			getline(filein, tmp);
			InsertHKToTree(tree_hk, hk);
		}
	}while(!filein.eof());
	filein.close();
}



// =================================

// ========== VE ===================



void initListVe(ListVe &dsVe, int soCho){
	dsVe.n = 0;
	dsVe.ve = new string[soCho];
	for(int i = 0; i < soCho; i++ )
	{
//		strcpy(dsVe.ve[i], "");
		dsVe.ve[i] = "";
		//cout<<i<<"-"<<dsVe.ve[i]<<"-"<<dsVe.ve[i].length()<<endl;
//		strcpy(dsVe.ve[i].cmnd, "");
	}
}

bool InsertVe(ListVe &list, int soGhe, string cmnd)
{
	
	if ((list.ve[soGhe-1].length()) > 0)
		return false;
	else
	{
		
		list.ve[soGhe-1] = cmnd;
		list.n++;
		return true;
	}
}
bool DeleteVe(ListVe &list, int soGhe)
{
	
	if ((list.ve[soGhe-1].length()) > 0){
		list.ve[soGhe-1] = "";
		list.n--;
		return true;
	}else{
		return false;
	}
}
//bool CheckHK(ListVe list)
//{
//	//danh sach rong , khong ton tai hanh khach
//	if (list.n == 0)
//		return true;
//	int dem = 0;
//	for (int i = 0; i < list.n; i++)
//	{
//		if (strcmp(list.ve[i].hk.cmnd, "") == 0)
//			dem++;
//	}	
//	// may bay moi chua co hk nao
//	if (dem == list.n)
//		return true;
//	else
//	
//}

// ==================================



// ========== CHUYEN BAY ============


int Empty_MB(ListMayBay dsMB)
{
	return dsMB.soluong == 0;
}
int Full_MB(ListMayBay dsMB)
{
	return dsMB.soluong == MAXMB;
}

void Init_CB(SingleList_CB &listCB)
{
	listCB.pHead = listCB.pTail = NULL;
}

int Dem(SingleList_CB lcb, char soHieu[])
{
	int dem = 0;
	Node_CB *pNode = lcb.pHead;
	while (pNode != NULL)
	{
		if (strcmp(pNode->cb.soHieuMB, soHieu) == 0)
			if (pNode->cb.trangThai == 3)
				dem++;
		pNode = pNode->pNext;
	}
	return dem;
}

int getsocho(ListMayBay lmb, char soHieu[])
{
	for (int i = 0; i < lmb.soluong; i++)
	{
		if (strcmp(lmb.maybay[i]->soHieuMB, soHieu) == 0)
			return lmb.maybay[i]->soCho;
	}
	return -1;
}

void LuuFileChuyenBay(SingleList_CB listCB, ListMayBay lmb)
{
	ofstream fileout;
	fileout.open("chuyenbay.txt", ios::out);
	Node_CB *pTmp = listCB.pHead;
	for ( ; pTmp != NULL; pTmp=pTmp->pNext)	{
		ChuyenBay cb;
		cb = pTmp->cb;
		fileout << cb.soHieuMB << endl;
		fileout << cb.maCB << "," 
				<< cb.tgKhoiHanh.ngay << "/" 
				<< cb.tgKhoiHanh.thang << "/" 
				<< cb.tgKhoiHanh.nam << ","
				<< cb.tgKhoiHanh.gio << ":"
				<< cb.tgKhoiHanh.phut << endl;
		fileout << cb.sanBayDen <<endl;
		fileout << cb.trangThai <<endl;
		int socho = getsocho(lmb, cb.soHieuMB);
		for(int vitri = 0; vitri < socho; vitri++){
			if((cb.dsVe.ve[vitri].length() > 0))
			{
				fileout << vitri+1 << "-" << cb.dsVe.ve[vitri] << endl;
			}
		}
		fileout << endl << endl;
	}

	fileout.close();
}

void LuuFileMayBay(ListMayBay listMB, ofstream &fileout)
{
	fileout << listMB.soluong<<endl;
	for (int i = 0; i < listMB.soluong; i++)
	{
		fileout << listMB.maybay[i]->soHieuMB << ","<<listMB.maybay[i]->loaiMB << ","<<listMB.maybay[i]->soCho<<endl;
	}
	
	fileout.close();
}
int Insert_MB(ListMayBay &listMB, MayBay mb)
{
	int empty = Empty_MB(listMB);
	int full = Full_MB(listMB);
	if (empty == 1)
	{
		listMB.maybay[0] = new MayBay;
 		strcpy(listMB.maybay[0]->soHieuMB, mb.soHieuMB);
		listMB.maybay[0]->soCho = mb.soCho;
		strcpy(listMB.maybay[0]->loaiMB , mb.loaiMB);
		listMB.soluong = 1;
		return 1;
	}
	else if (full)
	{
		return -1;
	}
		
	else
	{
		listMB.maybay[listMB.soluong] = new MayBay;
		strcpy(listMB.maybay[listMB.soluong]->soHieuMB, mb.soHieuMB);
		listMB.maybay[listMB.soluong]->soCho = mb.soCho;
		strcpy(listMB.maybay[listMB.soluong]->loaiMB , mb.loaiMB);
		listMB.soluong++;
		return 1;
	}
}
void DocFileMayBay(ListMayBay &listmb)
{
	ifstream filein;
	filein.open("maybay.txt", ios::in);
	int n; // get so luong may bay
	listmb.soluong = 0;
	string tmp;
	
	filein>>n;
	
	getline(filein,tmp);
	for (int i = 0; i < n; i++)
	{

		MayBay mb;
		getline(filein, tmp, ',');
		strcpy(mb.soHieuMB, tmp.c_str());
		
		getline(filein, tmp, ',');
		strcpy(mb.loaiMB, tmp.c_str());
		
		
		filein >> mb.soCho;
		getline(filein, tmp);
		
		Insert_MB(listmb, mb);
	}
	filein.close();
}

bool Check_ThoiGian_ChuyenBay(ThoiGian tg);
void InsertLast_CB(SingleList_CB &lcb, ChuyenBay cb);
string *splitToTwoString(const string str, char splitchar);
void DocFileChuyenBay(SingleList_CB &lcb, ListMayBay lmb)
{
	ifstream filein;
	filein.open("chuyenbay.txt", ios::in);
	string tmp; 
	do
	{
		ChuyenBay cb;
		
		getline(filein, tmp);
		if (tmp != ""){
			strcpy(cb.soHieuMB, tmp.c_str());
			
			getline(filein, tmp, ',');
			strcpy(cb.maCB, tmp.c_str());
//			cout<<cb.maCB<<endl;
			getline(filein, tmp, '/');
			cb.tgKhoiHanh.ngay = atoi(tmp.c_str());
			
			getline(filein, tmp, '/');
			cb.tgKhoiHanh.thang = atoi(tmp.c_str());
			
			getline(filein, tmp, ',');
			cb.tgKhoiHanh.nam = atoi(tmp.c_str());
			
			getline(filein, tmp, ':');
			cb.tgKhoiHanh.gio = atoi(tmp.c_str());
			
			getline(filein, tmp);
			cb.tgKhoiHanh.phut = atoi(tmp.c_str());
			
			
			getline(filein, tmp);
			strcpy(cb.sanBayDen, tmp.c_str());

			getline(filein, tmp);
			cb.trangThai = atoi(tmp.c_str());
			if (Check_ThoiGian_ChuyenBay(cb.tgKhoiHanh) == false)
				cb.trangThai = 3;
				
			initListVe(cb.dsVe, getsocho(lmb, cb.soHieuMB));

			string tmp1 = "";
			getline(filein, tmp1);
			
			while(tmp1 != "")
			{
				string *arrVe = splitToTwoString(tmp1, '-');
				string ghe = arrVe[0];
				string cmnd = arrVe[1];

				
				InsertVe(cb.dsVe, atoi(ghe.c_str()), cmnd);
				getline(filein, tmp1);
				
			}
			
			InsertLast_CB(lcb, cb);
			tmp = "";
		}
		
	}while (!filein.eof());
}

string* splitToTwoString(const string str, char splitchar){
	int pos = 0;
	string* arr = new string[2];
	arr[0] = "";
	arr[1] = "";
	for(pos; pos < str.length();pos ++){
		if(str.at(pos) == splitchar){
			arr[0] = str.substr(0,pos); // 12-
			arr[1] = str.substr(pos+1, str.length()-pos);
		}
	}
	return arr;
}

int CheckSoHieu_MB(ListMayBay listMB, char sohieu[])
{
	if (Empty_MB(listMB))
		return -1;
	else
	{
		for (int i = 0; i < listMB.soluong; i++)
		{
			if (stricmp(listMB.maybay[i]->soHieuMB, sohieu) == 0)
				return i;
		}
		return -1;
	}
}

ChuyenBay *SearchCB(SingleList_CB lcb, char maCB[])
{
	Node_CB *pNode = lcb.pHead;
	while (pNode != NULL)
	{
		if (strcmp(pNode->cb.maCB, maCB) == 0)
			return &pNode->cb;
	}
	return NULL;
}

int Check_MaCB(SingleList_CB listCB, char macb[])
{
	Node_CB *pTmp = listCB.pHead;
	if (pTmp == NULL)
		return -1;
	else
	{
		for (; pTmp != NULL; pTmp=pTmp->pNext)
		{
			if (strcmp(pTmp->cb.maCB, macb) == 0)
				return 1;
		}
	}
	return -1;
}


int CheckHKTrongCB(ListVe lv, int socho, char cmnd[])
{
	for(int i = 0; i < socho; i++)
	{
		if (lv.ve[i] == cmnd)
			return 1;
	}
	return -1;
}


void Delete_MB(ListMayBay &listMB, char sohieu[])
{
	for (int i = 0; i < listMB.soluong; i++)
	{
		if (strcmp(listMB.maybay[i]->soHieuMB, sohieu) == 0)
		{
			MayBay* temp = listMB.maybay[i];
			int j = i+1;
			for( j ; j < listMB.soluong; j++){
				listMB.maybay[i] = listMB.maybay[j];
				i = j;
			}
			delete temp;
			listMB.maybay[j] = NULL;
			listMB.soluong--;
			cout<<"Da xoa\n";
			break;
		}
	}
}

void Xuat_MB(ListMayBay listMB)
{
	cout<<"So luong: "<<listMB.soluong<<endl;
	for (int i = 0; i < listMB.soluong; i++)
	{
		cout<<listMB.maybay[i]->soHieuMB<<"\t"<<listMB.maybay[i]->loaiMB<<"\t"<<listMB.maybay[i]->soCho<<endl;
	}
}


// =======================





Node_CB *CreateNode_CB(ChuyenBay cb_moi)
{
	Node_CB *pNode = new Node_CB;
	if(pNode != NULL)
	{
		pNode->cb = cb_moi;
		pNode->pNext = NULL;
	}
	else
		cout<<"Tao Node_CB that bai";
	return pNode;
}

void InsertLast_CB(SingleList_CB &listCB, ChuyenBay cb_moi)
{
	Node_CB *pNode = CreateNode_CB(cb_moi);
	if (listCB.pHead == NULL)
	{
		listCB.pHead = listCB.pTail = pNode;
	}
	else
	{
		listCB.pTail->pNext = pNode;
		listCB.pTail = pNode;
	}
}

Node_CB * TimKiem_CB(SingleList_CB listCB, char maCB[])
{
	for (Node_CB *pNode = listCB.pHead; pNode != NULL; pNode = pNode->pNext)
	{
		if (strcmp(pNode->cb.maCB, maCB) == 0)
			return pNode;
	}
	return NULL;
}

bool Delete_CB_Theo_Ma(SingleList_CB &listCB, char ma[])
{
	Node_CB *pDel = listCB.pHead;
	if (pDel == NULL)
		return false;
	else
	{
		Node_CB *pPre = NULL;
		while (pDel != NULL)
		{
			if (strcmp(pDel->cb.maCB, ma) == 0)
				break;
			pPre = pDel;
			pDel = pDel->pNext;
		}
		if (pDel == NULL)
		{
			return false;
		}
		else
		{
			if (pDel->cb.trangThai == 3)
			{
				if (pDel == listCB.pHead)
				{
					listCB.pHead = listCB.pHead->pNext;
					pDel->pNext = NULL;
					delete pDel;
					pDel = NULL;
					return true;
				}
				else if (pDel->pNext == NULL)
				{
					listCB.pTail = pPre;
					pPre->pNext = NULL;
					delete pDel;
					pDel = NULL;
					return true;
				}
				else
				{
					pPre->pNext = pDel->pNext;
					pDel->pNext = NULL;
					delete pDel;
					pDel = NULL;
					return true;
				}	
			}
			else
			{
				return false;
			}
			
		}
	}
	
}


// TEST: in thu Danh sach CB
void PrintList_CB(SingleList_CB listCB)
{
	Node_CB *pTmp = listCB.pHead;
	if(pTmp == NULL)
	{
		cout<<"Danh sach rong!";
		return;
	}
	for (pTmp; pTmp != NULL; pTmp = pTmp->pNext)
	{
		ChuyenBay cb = pTmp->cb;
		cout<<cb.soHieuMB<<"\t"
			<<cb.maCB<<"\t"
			<<cb.tgKhoiHanh.ngay<<"/"<<cb.tgKhoiHanh.thang<<"/"<<cb.tgKhoiHanh.nam<<"  "<<cb.tgKhoiHanh.gio<<":"<<cb.tgKhoiHanh.phut<<"\t"
			<<cb.sanBayDen<<"\t"
			<<cb.trangThai<<endl;
		cout<<" --- DANH SACH VE ---"<<endl;
		for (int i = 0; i < cb.dsVe.n; i++)
		{
			if (cb.dsVe.ve[i] != "")
				cout<<i+1<<"-"<<cb.dsVe.ve[i]<<endl;
		}
	}
}


// ==========================
bool Check_Date(int nam, int thang, int ngay)
{
	int Thang[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if ( (nam % 4 == 0 && nam % 100 != 0) || nam % 400 == 0)
	{
		Thang[1] = 29;
	}
	if (thang >= 1 && thang <= 12)
	{
		if (ngay >= 1 && ngay <= Thang[thang - 1])
		{
			return true;	
		}
	}
	return false;
}

bool Check_ThoiGian_ChuyenBay(ThoiGian tg)
{
	int Thang[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (!Check_Date(tg.nam, tg.thang, tg.ngay)) return false;

	time_t baygio = time(0);
	tm *ltm = localtime(&baygio);
	ThoiGian dtNow;
	dtNow.nam = 1900 + ltm->tm_year;
	dtNow.thang = 1 + ltm->tm_mon;
	dtNow.ngay = ltm->tm_mday;
	dtNow.gio = ltm->tm_hour;
	dtNow.phut = ltm->tm_min;

	if (tg.nam < dtNow.nam) return false;
	if ((tg.nam == dtNow.nam) && (tg.thang < dtNow.thang))  return false;
	if ((tg.nam % 400 == 0) || (tg.nam % 4 == 0 && tg.nam % 100 != 0))
		Thang[1] = 29;
	if (tg.nam == dtNow.nam && tg.thang == dtNow.thang && tg.ngay < dtNow.ngay)return false;
	if (tg.nam == dtNow.nam && tg.thang == dtNow.thang && tg.ngay == dtNow.ngay && tg.gio < dtNow.gio)return false;
	if (tg.nam == dtNow.nam && tg.thang == dtNow.thang && tg.ngay == dtNow.ngay && tg.gio == dtNow.gio && tg.phut <= dtNow.phut)return false;
	return true;
}


//kiem tra trung ngay
bool Check_trungDate(SingleList_CB lcb,ThoiGian time) {
	Node_CB *pTmp = lcb.pHead;
	if (pTmp == NULL) {
		return true;
	}
	else {
		while (pTmp != NULL) {
				if (pTmp->cb.tgKhoiHanh.nam == time.nam) {
					if (pTmp->cb.tgKhoiHanh.thang == time.thang) {
						if (pTmp->cb.tgKhoiHanh.ngay == time.ngay) {
							if (pTmp->cb.tgKhoiHanh.gio == time.gio) {
								return false;
							}
						}
					}
				}
				pTmp = pTmp->pNext;
			}
		}
	return true;
}
//kiem tra danh sach ve full chua
bool Them_Ve_Duoc(ChuyenBay cb,int socho) {
	if (0 <= cb.dsVe.n && cb.dsVe.n <= socho)
	{
		return true;
	}
	return false;
}
//kiem tra vi tri ghe trong ko
bool Check_ViTri_Ghe(SingleList_CB lcb, int vitri) {
	Node_CB *pTmp = lcb.pHead;
	if (pTmp->cb.dsVe.ve[vitri] != "") {
		return true;
	}
	else return false;
}



void Box_DatVe() {
	system("cls");
	SetColor(ColorGREEN);
	gotoxy(18, 8);
	cout << "                                                    ";
	gotoxy(30, 2);cout << "CHUONG TRINH QUAN LY CHUYEN BAY";
	gotoxy(53,5);  cout << "Thong tin hanh khach : ";
	gotoxy(2, 5);  cout << "Ma chuyen bay :";
	gotoxy(2, 8);  cout << "Nhap CMND     :";
	gotoxy(2, 11); cout << "Chon ghe so   :";
	gotoxy(53, 7); cout << "Ho  : ";
	gotoxy(53, 9); cout << "Ten : ";
	gotoxy(53, 11); cout <<"Phai: ";


	for (int i = 1; i <= 100; i++)
	{
		gotoxy(i, 1);  cout << "-";
		gotoxy(i, 3);  cout << "-";
		gotoxy(i, 28); cout << "-";
	}
	for (int i = 4; i <= 28; i++)
	{
		gotoxy(50, i); cout << "|";
	}
	for (int i = 51; i <= 100; i++)
	{
		gotoxy(i, 6);  cout << "-";
	}
	for (int i = 1; i <= 28; i++)
	{
		gotoxy(1, i); cout << "|";
		gotoxy(100, i); cout << "|";
	}
}
void Box_HuyVe() {
	system("cls");
	SetColor(ColorGREEN);
	gotoxy(18, 8);
	cout << "                                                    ";
	gotoxy(30, 2);cout << "HUY VE HANH KHACH CHUYEN BAY";
	gotoxy(2, 5);  cout << "Ma chuyen bay :";
	gotoxy(2, 7);  cout << "Chon ghe so   :";
	gotoxy(65,5);  cout << " THONG BAO ";



	for (int i = 1; i <= 100; i++)
	{
		gotoxy(i, 1);  cout << "-";
		gotoxy(i, 3);  cout << "-";
		gotoxy(i, 28); cout << "-";
	}
	for (int i = 4; i <= 28; i++)
	{
		gotoxy(50, i); cout << "|";
	}
	for (int i = 51; i <= 100; i++)
	{
		gotoxy(i, 6);  cout << "-";
	}
	for (int i = 1; i <= 28; i++)
	{
		gotoxy(1, i); cout << "|";
		gotoxy(100, i); cout << "|";
	}
}

void ButtonThem(int color)
{
	gotoxy(15, 31); SetBGColor(color); 						cout << "      ";
	gotoxy(15, 32); SetBGColor(color); SetColor(ColorBLACK);cout << "  F1  ";
	gotoxy(15, 33); SetBGColor(color); 						cout << "      ";
	gotoxy(15, 35); SetBGColor(15); SetColor(ColorBLACK);	cout << " THEM ";
}

void ButtonXoa(int color)
{
	gotoxy(35, 31); SetBGColor(color); 						cout << "      ";
	gotoxy(35, 32); SetBGColor(color); 						cout << "  F2  ";
	gotoxy(35, 33); SetBGColor(color); 						cout << "      ";
	gotoxy(35, 35); SetBGColor(15); SetColor(ColorBLACK); 	cout << "  XOA ";
}

void ButtonSua(int color)
{
	gotoxy(52, 31); SetBGColor(color); 						cout << "      ";
	gotoxy(52, 32); SetBGColor(color); 						cout << "  F3  ";
	gotoxy(52, 33); SetBGColor(color); 						cout << "      ";
	gotoxy(52, 35); SetBGColor(15); SetColor(ColorBLACK);	cout << "  SUA ";
}

void ButtonESC(int color)
{
	gotoxy(70, 31); SetBGColor(color); 						cout << "      		";
	gotoxy(70, 32); SetBGColor(color); 						cout << "    ESC	";
	gotoxy(70, 33); SetBGColor(color); 						cout << "      		";
	gotoxy(65, 35); SetBGColor(15); SetColor(ColorBLACK);	cout << "TRO VE MENU";
}
void Box_NhapMayBay()
{
	SetColor(15);
	gotoxy(boxx, boxy); cout << char(201);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(187);
	
	gotoxy(boxx, boxy + 1); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 1); cout << char(186);
	
	gotoxy(boxx, boxy + 2); cout << char(186)<< " Nhap vao so hieu may bay: "; // boxx+27       boxx + 61
	gotoxy(boxx + boxs + 1, boxy + 2); cout << char(186);
	
	gotoxy(boxx, boxy + 3); cout << char(186) ;
	gotoxy(boxx + boxs + 1, boxy + 3); cout << char(186);
	gotoxy(boxx, boxy + 4); cout << char(186)<< "    Nhap vao loai may bay: ";
	gotoxy(boxx + boxs + 1, boxy + 4); cout << char(186);
	gotoxy(boxx, boxy + 5); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 5); cout << char(186);
	gotoxy(boxx, boxy + 6); cout << char(186)<< "          Nhap vao so cho: ";
	gotoxy(boxx + boxs + 1, boxy + 6); cout << char(186);
	gotoxy(boxx, boxy + 7); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 7); cout << char(186);
	gotoxy(boxx, boxy + 8); cout << char(200);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(188); 
}

void Box_SuaMayBay()
{
	SetColor(15);
	
	gotoxy(boxx + 30, boxy - 1); cout<<"THONG TIN";
	gotoxy(boxx + 65, boxy - 1); cout<<"DANG SUA";
	
	
	gotoxy(boxx, boxy); cout << char(201);
	for(int i = 1; i < boxs + 30; i++) cout << char(205);
	cout << char(187);
	gotoxy(boxx + 58,boxy); cout<<char(203); //  ||``
	
	gotoxy(boxx, boxy + 1); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 1); cout << char(186);
	
	gotoxy((boxx + boxs + 75)/2, boxy + 1); cout << char(186);
	
	gotoxy(boxx, boxy + 2); cout << char(186)<< " Nhap vao so hieu may bay: ";  // boxx + 27      boxx + 61
	gotoxy((boxx + boxs + 75)/2, boxy + 2); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 2); cout << char(186);
	
	gotoxy(boxx, boxy + 3); cout << char(186) ;
	gotoxy(boxx + boxs + 30, boxy + 3); cout << char(186);
	
	gotoxy((boxx + boxs + 75)/2, boxy + 3); cout << char(186);
	
	gotoxy(boxx, boxy + 4); cout << char(186)<< "    Nhap vao loai may bay: ";
	gotoxy((boxx + boxs + 75)/2, boxy + 4); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 4); cout << char(186);
	
	gotoxy(boxx, boxy + 5); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 5); cout << char(186);
	
	gotoxy((boxx + boxs + 75)/2, boxy + 5); cout << char(186);
	
	gotoxy(boxx, boxy + 6); cout << char(186)<< "          Nhap vao so cho: ";
	gotoxy((boxx + boxs + 75)/2, boxy + 6); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 6); cout << char(186);
	
	gotoxy(boxx, boxy + 7); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 7); cout << char(186);
	
	gotoxy((boxx + boxs + 75)/2, boxy + 7); cout << char(186);
	
	gotoxy(boxx, boxy + 8); cout << char(200);
	for(int i = 1; i < boxs + 30; i++) cout << char(205);
	cout << char(188); 
	gotoxy(boxx + 58,boxy + 8); cout<<char(202); //  ||__
}

void Box_NhapChuyenBayBay()
{
	system("cls");
	SetColor(15);
	
	gotoxy(40,4); cout<<"--- THEM CHUYEN BAY ---";
	
	gotoxy(boxx, boxy - 8); cout << char(201);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(187);
	
	gotoxy(boxx, boxy - 7); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy - 7); cout << char(186);
	
	gotoxy(boxx, boxy - 6); cout << char(186)<< " Nhap vao so hieu may bay: ";
	gotoxy(boxx + boxs + 1, boxy - 6); cout << char(186);
	
	gotoxy(boxx, boxy - 5); cout << char(186) ;
	gotoxy(boxx + boxs + 1, boxy - 5); cout << char(186);
	
	gotoxy(boxx, boxy - 4); cout << char(186)<< "       Nhap ma chuyen bay: ";
	gotoxy(boxx + boxs + 1, boxy - 4); cout << char(186);
	
	gotoxy(boxx, boxy - 3); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy - 3); cout << char(186);
	
	gotoxy(boxx, boxy - 2); cout << char(186)<< "                      Nam: ";
	gotoxy(boxx + boxs + 1, boxy - 2); cout << char(186);
	
	gotoxy(boxx, boxy - 1); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy - 1); cout << char(186);
	
	gotoxy(boxx, boxy); 	cout << char(186)<< "                    Thang: ";
	gotoxy(boxx + boxs + 1, boxy); cout << char(186);
	
	gotoxy(boxx, boxy + 1); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 1); cout << char(186);
	
	gotoxy(boxx, boxy + 2); cout << char(186)<< "                     Ngay: ";
	gotoxy(boxx + boxs + 1, boxy + 2); cout << char(186);
	
	gotoxy(boxx, boxy + 3); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 3); cout << char(186);
	
	gotoxy(boxx, boxy + 4); cout << char(186)<< "                      Gio: ";
	gotoxy(boxx + boxs + 1, boxy + 4); cout << char(186);
	
	gotoxy(boxx, boxy + 5); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 5); cout << char(186);
	
	gotoxy(boxx, boxy + 6); cout << char(186)<< "                     Phut: ";
	gotoxy(boxx + boxs + 1, boxy + 6); cout << char(186);
	
	gotoxy(boxx, boxy + 7); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 7); cout << char(186);
	
	gotoxy(boxx, boxy + 8); cout << char(186)<< "              San bay den: ";
	gotoxy(boxx + boxs + 1, boxy + 8); cout << char(186);
	
	gotoxy(boxx, boxy + 9); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 9); cout << char(186);
	
	gotoxy(boxx, boxy + 10); cout << char(200);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(188); 
}

void Box_NhapHanhKhach()
{
	SetColor(15);
	gotoxy(boxx, boxy); cout << char(201);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(187);
	
	gotoxy(boxx, boxy + 1); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 1); cout << char(186);
	
	gotoxy(boxx, boxy + 2); cout << char(186)<< "            Nhap CMND: ";
	gotoxy(boxx + boxs + 1, boxy + 2); cout << char(186);
	
	gotoxy(boxx, boxy + 3); cout << char(186) ;
	gotoxy(boxx + boxs + 1, boxy + 3); cout << char(186);
	
	gotoxy(boxx, boxy + 4); cout << char(186)<< "              Nhap ho: ";
	gotoxy(boxx + boxs + 1, boxy + 4); cout << char(186);
	
	gotoxy(boxx, boxy + 5); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 5); cout << char(186);
	
	gotoxy(boxx, boxy + 6); cout << char(186)<< "             Nhap ten: ";
	gotoxy(boxx + boxs + 1, boxy + 6); cout << char(186);
	
	gotoxy(boxx, boxy + 7); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 7); cout << char(186);
	
	gotoxy(boxx, boxy + 8); cout << char(186);
	gotoxy(boxx, boxy + 8); cout << char(186)<< "    Nhap phai(nam/nu): ";
	gotoxy(boxx + boxs + 1, boxy + 8); cout << char(186);
	
	gotoxy(boxx, boxy + 9); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 9); cout << char(186);

	gotoxy(boxx, boxy + 10); cout << char(200);	
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(188); 
}

void Box_DS_HK_Trong_CB()
{
//	resizeConsole(800,600);
	gotoxy(35, 2);
	cout << "DANH SACH HANH KHACH CUA CHUYEN BAY CO MA: "; // 80,2
	gotoxy(30,3);
	cout << "Ngay gio thoi hanh: "; // 49,3
	gotoxy(51,3); cout<<"/";
	gotoxy(54,3); cout<<"/";
	gotoxy(63,3); cout<<":";
	gotoxy(68,3);
	cout << "Noi den:"; // 77,3
	
	gotoxy(tabx, taby);
	cout << char(218);
	//-------- dong dau
	for(int i = 1; i < tabs ; i++)
	{
		cout << char(196);
	}
	cout << char(191);
	
	//cot dau
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx, taby + i);
		cout << char(179);
	}
	//cot cuoi
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + tabs, taby + i);
		cout << char(179) ;
	}
	
	gotoxy(tabx, taby + tabw);
	cout << char(192);
	//dong cuoi
	for(int i = 1; i < tabs + 1; i++)
	{
		gotoxy(tabx + i, taby + tabw);
		cout << char(196);
	}
	gotoxy(tabx + tabs , taby + tabw);
	cout << char(217);

	// STT
	gotoxy(tabx + 3, taby + 1); cout << "STT";
	gotoxy(tabx + 8, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 8, taby + i); cout << char(179); // cot stt
	}
	
	gotoxy(tabx, taby + 2);
	cout << char(195);
	// dong hai
	for(int i = 1; i < tabs ; i++)
	{
		gotoxy(tabx + i, taby + 2);
		cout << char(196);
	}
	gotoxy(tabx + 8, taby + 2); cout << char(197);
	gotoxy(tabx + tabs , taby + 2); cout << char(180);
	gotoxy(tabx + 8, taby + tabw); cout << char(193);

	// SO HIEU
	gotoxy(tabx + 12, taby + 1); cout << "SO VE";
	gotoxy(tabx + 20, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 20, taby + i); cout << char(179);
	}
	gotoxy(tabx + 20, taby + 2); cout << char(197);
	gotoxy(tabx + 20, taby + tabw); cout << char(193);

	// LOAI
	gotoxy(tabx + 26, taby + 1); cout << "CMND";
	gotoxy(tabx + 38, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 38, taby + i); cout << char(179);
	}
	gotoxy(tabx + 38, taby + 2); cout << char(197);
	gotoxy(tabx + 38, taby + tabw); cout << char(193);

	// SO CHO
	gotoxy(tabx + 50, taby + 1); cout << "HO TEN";
	gotoxy(tabx + 70, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 70, taby + i); cout << char(179);
	}
	gotoxy(tabx + 70, taby + 2); cout << char(197);
	gotoxy(tabx + 70, taby + tabw); cout << char(193);
	
	// PHAI
	gotoxy(tabx + 75, taby + 1); cout << "PHAI";
}

void Box_DS_Ve_Trong_Trong_CB()
{
	/////
//	resizeConsole(800,600);
	gotoxy(35, 2);
	cout << "DANH SACH VE TRONG CUA CHUYEN BAY";
	gotoxy(42,3); cout<<"Ma: "; // 46,3
	
	gotoxy(tabx+20, taby);
	cout << char(218);
	//-------- dong dau
	for(int i = 1; i < tabs - 33 ; i++)
	{
		cout << char(196);
	}
	cout << char(191);
	
	//cot dau
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx+20, taby + i);
		cout << char(179);
	}
	//cot cuoi
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + tabs - 13, taby + i);
		cout << char(179) ;
	}
	
	gotoxy(tabx+20, taby + tabw);
	cout << char(192);
	//dong cuoi
	for(int i = 1; i < tabs - 33; i++)
	{
		gotoxy(tabx + i + 20, taby + tabw);
		cout << char(196);
	}
	gotoxy(tabx + tabs - 13, taby + tabw);
	cout << char(217);

	// STT
	gotoxy(tabx + 30, taby + 1); cout << "STT";
	gotoxy(tabx + 45, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 45, taby + i); cout << char(179); // cot stt
	}
	
	gotoxy(tabx + 20, taby + 2);
	cout << char(195);
	// dong hai
	for(int i = 1; i < tabs - 33 ; i++)
	{
		gotoxy(tabx + i + 20, taby + 2);
		cout << char(196);
	}
	gotoxy(tabx + 45, taby + 2); cout << char(197);
	gotoxy(tabx + tabs - 13, taby + 2); cout << char(180);
	gotoxy(tabx + 45, taby + tabw); cout << char(193);

	// VE TRONG
	gotoxy(tabx + 55, taby + 1); cout << "VE TRONG";

}
void Box_DS_Thong_Ke_So_Luot_Bay()
{
	
//	resizeConsole(800,600);
	gotoxy(35, 2);
	cout << "THONG KE SO LUOT BAY CUA MAY BAY";
	
	gotoxy(tabx+20, taby);
	cout << char(218);
	//-------- dong dau
	for(int i = 1; i < tabs - 33 ; i++)
	{
		cout << char(196);
	}
	cout << char(191);
	
	//cot dau
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx+20, taby + i);
		cout << char(179);
	}
	//cot cuoi
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + tabs - 13, taby + i);
		cout << char(179) ;
	}
	
	gotoxy(tabx+20, taby + tabw);
	cout << char(192);
	//dong cuoi
	for(int i = 1; i < tabs - 33; i++)
	{
		gotoxy(tabx + i + 20, taby + tabw);
		cout << char(196);
	}
	gotoxy(tabx + tabs - 13, taby + tabw);
	cout << char(217);

	// SO HIEU MAY BAY
	gotoxy(tabx + 26, taby + 1); cout << "SO HIEU MAY BAY";
	gotoxy(tabx + 45, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 45, taby + i); cout << char(179); // cot stt
	}
	
	gotoxy(tabx + 20, taby + 2);
	cout << char(195);
	// dong hai
	for(int i = 1; i < tabs - 33 ; i++)
	{
		gotoxy(tabx + i + 20, taby + 2);
		cout << char(196);
	}
	gotoxy(tabx + 45, taby + 2); cout << char(197);
	gotoxy(tabx + tabs - 13, taby + 2); cout << char(180);
	gotoxy(tabx + 45, taby + tabw); cout << char(193);

	// SO LUOT BAY
	gotoxy(tabx + 53, taby + 1); cout << "SO LUOT BAY";

}


void TableMayBay()
{
	gotoxy(35, 2);
	cout << "DANH SACH MAY BAY";
	gotoxy(tabx, taby);
	cout << char(218);
	for(int i = 1; i < tabs - 13; i++)
	{
		cout << char(196);
	}
	cout << char(191);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx, taby + i);
		cout << char(179);
	}

	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + tabs - 13, taby + i);
		cout << char(179);
	}
	gotoxy(tabx, taby + tabw);
	cout << char(192);
	for(int i = 1; i < tabs - 13; i++)
	{
		gotoxy(tabx + i, taby + tabw);
		cout << char(196);
	}
	gotoxy(tabx + tabs - 13, taby + tabw);
	cout << char(217);

	// STT
	gotoxy(tabx + 3, taby + 1); cout << "STT";
	gotoxy(tabx + 8, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 8, taby + i); cout << char(179);
	}
	gotoxy(tabx, taby + 2);
	cout << char(195);
	for(int i = 1; i < tabs - 13; i++)
	{
		gotoxy(tabx + i, taby + 2);
		cout << char(196);
	}
	gotoxy(tabx + 8, taby + 2); cout << char(197);
	gotoxy(tabx + tabs - 13, taby + 2); cout << char(180);
	gotoxy(tabx + 8, taby + tabw); cout << char(193);

	// SO HIEU
	gotoxy(tabx + 15, taby + 1); cout << "SO HIEU";
	gotoxy(tabx + 27, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 27, taby + i); cout << char(179);
	}
	gotoxy(tabx + 27, taby + 2); cout << char(197);
	gotoxy(tabx + 27, taby + tabw); cout << char(193);

	// LOAI
	gotoxy(tabx + 37, taby + 1); cout << "LOAI";
	gotoxy(tabx + 55, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 55, taby + i); cout << char(179);
	}
	gotoxy(tabx + 55, taby + 2); cout << char(197);
	gotoxy(tabx + 55, taby + tabw); cout << char(193);

	// SO CHO
	gotoxy(tabx + 58, taby + 1); cout << "SO CHO";
	
	
}
void TableChuyenBay()
{
	gotoxy(45, 2);
	cout << "DANH SACH CHUYEN BAY"; 
	gotoxy(30,3);
	
	gotoxy(tabx, taby);
	cout << char(218);
	//-------- dong dau
	for(int i = 1; i < tabs + 11; i++)
	{
		cout << char(196);
	}
	cout << char(191);
	
	//cot dau
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx, taby + i);
		cout << char(179);
	}
	//cot cuoi
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + tabs + 11, taby + i);
		cout << char(179) ;
	}
	
	gotoxy(tabx , taby + tabw);
	cout << char(192); // L
	//dong cuoi
	for(int i = 1; i < tabs + 11; i++)
	{
		gotoxy(tabx + i, taby + tabw);
		cout << char(196);
	}
	gotoxy(tabx + tabs + 11 , taby + tabw);
	cout << char(217); // _|

	// STT
	gotoxy(tabx + 3, taby + 1); cout << "STT";
	gotoxy(tabx + 8, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 8, taby + i); cout << char(179); // cot stt
	}
	
	gotoxy(tabx, taby + 2);
	cout << char(195);
	// dong hai
	for(int i = 1; i < tabs + 11; i++)
	{
		gotoxy(tabx + i, taby + 2);
		cout << char(196);
	}
	gotoxy(tabx + 8, taby + 2); cout << char(197);
	gotoxy(tabx + tabs + 11, taby + 2); cout << char(180); //-|
	gotoxy(tabx + 8, taby + tabw); cout << char(193);

	// SO HIEU MB
	gotoxy(tabx + 9, taby + 1); cout << "SO HIEU MB";
	gotoxy(tabx + 20, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 20, taby + i); cout << char(179);
	}
	gotoxy(tabx + 20, taby + 2); cout << char(197);
	gotoxy(tabx + 20, taby + tabw); cout << char(193);

	// MA CHUYEN BAY
	gotoxy(tabx + 23, taby + 1); cout << "MA CHUYEN BAY";
	gotoxy(tabx + 38, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 38, taby + i); cout << char(179);
	}
	gotoxy(tabx + 38, taby + 2); cout << char(197);
	gotoxy(tabx + 38, taby + tabw); cout << char(193);

	// NGAY
	gotoxy(tabx + 45, taby + 1); cout << "NGAY";
	gotoxy(tabx + 55, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 55, taby + i); cout << char(179);
	}
	gotoxy(tabx + 55, taby + 2); cout << char(197);
	gotoxy(tabx + 55, taby + tabw); cout << char(193);
	
	// GIO
	gotoxy(tabx + 60, taby + 1); cout << "GIO";
	gotoxy(tabx + 68, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 68, taby + i); cout << char(179);
	}
	gotoxy(tabx + 68, taby + 2); cout << char(197);
	gotoxy(tabx + 68, taby + tabw); cout << char(193);
	
	// SAN BAY DEN
	gotoxy(tabx + 70, taby + 1); cout<<"SAN BAY DEN";
	gotoxy(tabx + 83, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 83, taby + i); cout << char(179);
	}
	gotoxy(tabx + 83, taby + 2); cout << char(197);
	gotoxy(tabx + 83, taby + tabw); cout << char(193);
	
	gotoxy(tabx + 84, taby + 1); cout<<"TRANG THAI";
	
}

int XacNhanSaveFile()
{
	int x = 45, y = 19;
	gotoxy(40, 15);
	SetColor(ColorBLACK);
	SetBGColor(ColorDARKWHITE);
	cout << "                                ";
	gotoxy(40, 16); cout << "                                ";
	gotoxy(40, 17); cout << "  BAN CO MUON SAVE FILE KHONG?  ";
	gotoxy(40, 18); cout << "                                ";
	gotoxy(40, 19); cout << "     YES                NO      ";
	gotoxy(40, 20); cout << "                                ";
	int keyhit;
	do{
		gotoxy(45, 19);
//		SetColor(ColorDARKCYAN);
		switch(x)
		{
		case 45 : gotoxy(45, 19); cout << "YES"; break;
		case 64 : gotoxy(64, 19); cout << "NO"; break;
		}
		keyhit = getch();
		if(keyhit == LEFT)
		{
			gotoxy(45, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 45 : gotoxy(45, 19); cout << "YES"; break;
			case 64 : gotoxy(64, 19); cout << "NO"; break;
			}
			x -= 19;
			if(x != 45)
			{
				x = 64;
			}
		}
		else if(keyhit == RIGHT)
		{
			gotoxy(45, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 45 : gotoxy(45, 19); cout << "YES"; break;
			case 64 : gotoxy(64, 19); cout << "NO"; break;
			}
			x += 19;
			if(x != 64)
			{
				x = 45;
			}
		}
		else if(x == 45 && keyhit == ENTER)
		{
			gotoxy(boxx + 22, 29);
			cout << "LUU FILE THANH CONG";
			Sleep(1000);
			system("cls");
			SetBGColor(ColorBLACK);
			return 1;
		}
		else if(x == 64 && keyhit == ENTER)
		{
			system("cls");
			SetBGColor(ColorBLACK);
			return 0;
		}
	}while(true);
}

int XacNhanHuyVe()
{
	int x = 65, y = 39;
	gotoxy(60, 15);
	SetColor(ColorBLUE);
	SetBGColor(ColorDARKWHITE);
					cout << "                                ";
	gotoxy(60, 16); cout << "                                ";
	gotoxy(60, 17); cout << "  	BAN CO MUON HUY VE KHONG?    ";
	gotoxy(60, 18); cout << "                                ";
	gotoxy(60, 19); cout << "     YES                NO      ";
	gotoxy(60, 20); cout << "                                ";
	int keyhit;
	do{
		gotoxy(65, 19);
//		SetColor(ColorBLACK);
		switch(x)
		{
		case 65 : gotoxy(65, 19); cout << "YES"; break;
		case 84 : gotoxy(84, 19); cout << "NO"; break;
		}
		keyhit = getch();
		if(keyhit == LEFT)
		{
			gotoxy(65, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 65 : gotoxy(65, 19); cout << "YES"; break;
			case 84 : gotoxy(84, 19); cout << "NO"; break;
			}
			x -= 19;
			if(x != 65)
			{
				x = 84;
			}
		}
		else if(keyhit == RIGHT)
		{
			gotoxy(65, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 65 : gotoxy(65, 19); cout << "YES"; break;
			case 84 : gotoxy(84, 19); cout << "NO"; break;
			}
			x += 19;
			if(x != 84)
			{
				x = 65;
			}
		}
		else if(x == 65 && keyhit == ENTER)
		{
			system("cls");
			SetBGColor(ColorBLACK);
			return 1;
		}
		else if(x == 84 && keyhit == ENTER)
		{
			system("cls");
			SetBGColor(ColorBLACK);
			return 0;
		}
	}while(true);
	SetColor(ColorWHITE);
	SetBGColor(ColorBLACK);
}

int XacNhanDatVe()
{
	int x = 65, y = 39;
	gotoxy(60, 15);
	SetColor(ColorBLUE);
	SetBGColor(ColorDARKWHITE);
					cout << "                                ";
	gotoxy(60, 16); cout << "                                ";
	gotoxy(60, 17); cout << "  	BAN CO MUON DAT VE KHONG?    ";
	gotoxy(60, 18); cout << "                                ";
	gotoxy(60, 19); cout << "     YES                NO      ";
	gotoxy(60, 20); cout << "                                ";
	int keyhit;
	do{
		gotoxy(65, 19);
//		SetColor(ColorBLACK);
		switch(x)
		{
		case 65 : gotoxy(65, 19); cout << "YES"; break;
		case 84 : gotoxy(84, 19); cout << "NO"; break;
		}
		keyhit = getch();
		if(keyhit == LEFT)
		{
			gotoxy(65, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 65 : gotoxy(65, 19); cout << "YES"; break;
			case 84 : gotoxy(84, 19); cout << "NO"; break;
			}
			x -= 19;
			if(x != 65)
			{
				x = 84;
			}
		}
		else if(keyhit == RIGHT)
		{
			gotoxy(65, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 65 : gotoxy(65, 19); cout << "YES"; break;
			case 84 : gotoxy(84, 19); cout << "NO"; break;
			}
			x += 19;
			if(x != 84)
			{
				x = 65;
			}
		}
		else if(x == 65 && keyhit == ENTER)
		{
			gotoxy(boxx + 22, 29);
			cout << "DAT VE THANH CONG";
			Sleep(2000);
			system("cls");
			SetBGColor(ColorBLACK);
			return 1;
		}
		else if(x == 84 && keyhit == ENTER)
		{
			system("cls");
			SetBGColor(ColorBLACK);
			return 0;
		}
	}while(true);
}
int XacNhanThemHanhKhach()
{
	int x = 65, y = 19;
	gotoxy(60, 15);
	SetColor(ColorBLACK);
	SetBGColor(ColorDARKWHITE);
					cout << "                                 ";
	gotoxy(60, 16); cout << "   HANH KHACH NAY KHONG TON TAI  ";
	gotoxy(60, 17); cout << "  	BAN CO MUON THEM KHONG?    	  ";
	gotoxy(60, 18); cout << "                                 ";
	gotoxy(60, 19); cout << "     YES                NO       ";
	gotoxy(60, 20); cout << "                                 ";
	int keyhit;
	do{
		gotoxy(65, 19);
//		SetColor(ColorBLACK);
		switch(x)
		{
		case 65 : gotoxy(65, 19); cout << "YES"; break;
		case 84 : gotoxy(84, 19); cout << "NO"; break;
		}
		keyhit = getch();
		if(keyhit == LEFT)
		{
			gotoxy(65, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 65 : gotoxy(65, 19); cout << "YES"; break;
			case 84 : gotoxy(84, 19); cout << "NO"; break;
			}
			x -= 19;
			if(x != 65)
			{
				x = 84;
			}
		}
		else if(keyhit == RIGHT)
		{
			gotoxy(65, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 65 : gotoxy(65, 19); cout << "YES"; break;
			case 84 : gotoxy(84, 19); cout << "NO"; break;
			}
			x += 19;
			if(x != 84)
			{
				x = 65;
			}
		}
		else if(x == 65 && keyhit == ENTER)
		{
			SetBGColor(ColorBLACK);
			return 1;
		}
		else if(x == 84 && keyhit == ENTER)
		{
			SetBGColor(ColorBLACK);
			return 0;
		}
	}while(true);
}
void HienThiTrang(int tongtrang, int tranghientai, int x, int y)
{
	//textcolor(62);
	gotoxy(x, y + 1);
	cout << "Trang :  " << (tranghientai + 1) << " / " << tongtrang << "   ";
}



void Del_Error() {
	SetColor(15);
	gotoxy(boxx+10, 29);
	for(int i = 0; i < 50; i++) cout << " ";
}

void Print_Error_MayBay(int i)
{
	Del_Error();
	string s;
	if (i == 1) s = "MA MAY BAY BI TRUNG!";
	gotoxy(boxx + 15, 29);
	cout<<"CANH BAO: "<<s;
}

int Menu();
string nhapChuoi(int x, int y){
	string s = "";
	
	while(true){
		char key = getch();
		switch(int(key)){
			case ESC:{
				return "exit";
				break;
			}
			case ENTER:{
				return s;
				break;
			}
			case BACKSPACE:{
				if(s.length() > 0) s = s.substr(0,s.length()-1);
				else {
					s = "";
				}
				gotoxy(x,y); cout<<"                    ";
				gotoxy(x,y); cout<<s;
				break;
			}
			default:{
				if (s.length() < 20)
				{
					s+= char(key);
					gotoxy(x,y); cout<<"                    ";
					gotoxy(x,y); cout<<s;
				}
				
				break;
			}
		}
	}

}
string nhapSo(int x, int y){
	string s = "";
	
	while(true){
		char key = getch();
		switch(int(key)){
			case ESC:{
				return "exit";
				break;
			}
			case ENTER:{
				return s;
				break;
			}
			case BACKSPACE:{
				if(s.length() > 0) s = s.substr(0,s.length()-1);
				else {
					s = "";
				}
				gotoxy(x,y); cout<<"                    ";
				gotoxy(x,y); cout<<s;
				break;
			}
			default:{
				if (s.length() < 4)
				{
					s+= char(key);
					gotoxy(x,y); cout<<"                    ";
					gotoxy(x,y); cout<<s;
				}
				break;
			}
		}
	}
}
void NhapMayBay(ListMayBay &lmb)
{
	int keyhit,x = 28;
	int demfield = 0;
	while (true)
	{
		if (Full_MB(lmb))
		{
			gotoxy(boxx + 14, boxy + 10); cout<<"SO LUONG MAY BAY DAT GIOI HAN";
			Sleep(1500);  
			gotoxy(boxx + 14, boxy + 10); cout<<"                             ";
			break;
		}
		else
		{
			system("cls");
			Box_NhapMayBay();
			MayBay mb;
			strcpy(mb.soHieuMB, "");
			strcpy(mb.loaiMB, "");
			mb.soCho = 0;
	
				bool trung;
				// NHAP SO HIEU MAY BAY
				
				do{
					gotoxy(boxx + 28, boxy + 2); 
					string tmp = nhapChuoi(boxx + 28, boxy + 2);
	
					if(tmp == "exit"){
						break;
					}
					strcpy(mb.soHieuMB, tmp.c_str()); 
					strcpy(mb.soHieuMB, fix_Ma(mb.soHieuMB));	
					
					if (CheckSoHieu_MB(lmb, mb.soHieuMB) != -1)
					{
						gotoxy(boxx + 14, boxy + 10); cout<<"SO HIEU MAY BAY TRUNG!";
						Sleep(1000);  
						gotoxy(boxx + 14, boxy + 10); cout<<"                                 ";
						gotoxy(boxx + 28, boxy + 2);  cout<<"                                 ";
					}
					else if (strcmp(mb.soHieuMB, "\0") == 0)
					{
						gotoxy(boxx + 14, boxy + 10); cout<<"KHONG BO TRONG !";
						Sleep(1000);  
						gotoxy(boxx + 14, boxy + 10); cout<<"                                 ";
						gotoxy(boxx + 28, boxy + 2);  cout<<"                                 ";
					}
					else
					{
						demfield++;
						gotoxy(boxx + 28, boxy + 2);  cout<<"                                 ";
						gotoxy(boxx + 28, boxy + 2); cout<<mb.soHieuMB;
						trung = true;
					}	
				}while(trung == false);
	//			gotoxy(5,6); cout<<"KQ1: "<<mb.soHieuMB;
				if (strcmp(mb.soHieuMB, "") == 0) break;
				
				// NHAP LOAI MAY BAY
				do{
					trung = false;
					gotoxy(boxx + 28, boxy + 4);
					string tmp = nhapChuoi(boxx + 28, boxy + 4);
	
					if(tmp == "exit"){
						break;
					}
					strcpy(mb.loaiMB, tmp.c_str()); 
					strcpy(mb.loaiMB, fix_HoTen(mb.loaiMB));
					
					if (strcmp(mb.loaiMB, "\0") == 0)
					{
						gotoxy(boxx + 14, boxy + 10); cout<<"KHONG BO TRONG!";
						Sleep(1000);  
						gotoxy(boxx + 14, boxy + 10); cout<<"                                 ";
						gotoxy(boxx + 28, boxy + 4);  cout<<"                                 ";
					}
					else
					{
						demfield++;
						gotoxy(boxx + 28, boxy + 4);  cout<<"                                 ";
						gotoxy(boxx + 28, boxy + 4);cout<<mb.loaiMB;
						trung = true;
					}
				}while(trung == false);
				if (strcmp(mb.loaiMB, "") == 0) break;
				
				// NHAP SO CHO MAY BAY >= 20
				do{
					trung = false;
					gotoxy(boxx + 28, boxy + 6);
					char cho[10];
					string tmp = nhapChuoi(boxx + 28, boxy + 6);
	
					if(tmp == "exit"){
						break;
					}
					strcpy(cho, tmp.c_str()); 
					
					strcpy(cho, fix_Ma(cho));
					if (strcmp(cho, "\0") == 0)
					{
						gotoxy(boxx + 14, boxy + 10); cout<<"KHONG BO TRONG";
						Sleep(1000);  
						gotoxy(boxx + 14, boxy + 10); cout<<"                                ";
						gotoxy(boxx + 28, boxy + 6);  cout<<"                                ";
					}
					else
					{
						int soCho = atoi(cho);
						if (soCho < 20)
						{
							gotoxy(boxx + 14, boxy + 10); cout<<"CHI NHAN SO VA PHAI LON HON 20!";
							Sleep(1000);  
							gotoxy(boxx + 14, boxy + 10); cout<<"                                 ";
							gotoxy(boxx + 28, boxy + 6);  cout<<"                                 ";
						}
						else
						{
							demfield++;
							mb.soCho = soCho;
							gotoxy(boxx + 28, boxy + 6);  cout<<"                                 ";
							gotoxy(boxx + 28, boxy + 6);cout<<mb.soCho;
							trung = true;
						}
					}
			
				}while(trung == false);
				if (mb.soCho == 0) break;
				
				if (demfield == 3)
				{
					Insert_MB(lmb, mb);
					gotoxy(boxx + 14, boxy + 10); cout<<"DA THEM THANH CONG";
					Sleep(1500);  
					gotoxy(boxx + 14, boxy + 10); cout<<"                             ";
					demfield = 0;
				}	
		}
		
		
	}
	int a = XacNhanSaveFile();
	if(a == 1)
	{
		ofstream fileout;
		fileout.open("maybay.txt", ios::out);
		LuuFileMayBay(lmb,fileout);
	}
}
void frame_NhapMaMayBay(int x, int y)
{
	gotoxy(x, y); SetBGColor(ColorDARKBLUE); SetColor(ColorDARKYELLOW);	cout << "    NHAP VAO MA MAY BAY    ";
	gotoxy(x, y + 1); SetBGColor(ColorDARKBLUE);		cout << " ";
	gotoxy(x + 1, y + 1);  SetBGColor(ColorWHITE); 	cout << "                         ";
	gotoxy(x + 26, y + 1); SetBGColor(ColorDARKBLUE); 	cout << " ";
	gotoxy(x, y + 2); SetBGColor(ColorDARKBLUE);		cout << "                           ";
	SetBGColor(ColorBLACK); SetColor(ColorWHITE);
}

MayBay *SearchMB(ListMayBay lmb, char sohieu[])
{
	
	for (int i = 0; i < lmb.soluong; i++){
		if (strcmp(lmb.maybay[i]->soHieuMB, sohieu) == 0)
			return lmb.maybay[i];
	}
	return NULL;
}

void SuaMayBay(ListMayBay &lmb){
		
	NhapMA:
		system("cls");
		frame_NhapMaMayBay(40,8);
		char soHieu[15];
		gotoxy(45, 9); SetColor(ColorPURPLE); SetBGColor(ColorWHITE);
		string ma = nhapChuoi(45,9);
		if (ma == "exit")
			return;
		strcpy(soHieu, ma.c_str());
		strcpy(soHieu, fix_Ma(soHieu));
		int x = CheckSoHieu_MB(lmb, soHieu);
		if (x == -1)
		{
			SetColor(ColorWHITE); SetBGColor(ColorBLACK);
			gotoxy(35,12); cout<<"Khong tim thay chuyen bay nay!";
			Sleep(1000);
			gotoxy(35,12); cout<<"            					";
			goto NhapMA;
		}
		
		while(1)
		{
			SetColor(ColorWHITE); SetBGColor(ColorBLACK);
			int demfield = 0;
			bool trung;
			system("cls");
			Box_SuaMayBay();
			MayBay *mb = SearchMB(lmb, soHieu);
			gotoxy(boxx + 27, boxy + 2); cout<<mb->soHieuMB;
			gotoxy(boxx + 27, boxy + 4); cout<<mb->loaiMB;
			gotoxy(boxx + 27, boxy + 6); cout<<mb->soCho;
			
			gotoxy(boxx + 61, boxy + 2); cout<<mb->soHieuMB;
			
			char loai[40];
			strcpy(loai,"");
			int cho_edit = 0;
			do{
					trung = false;
					gotoxy(boxx + 61, boxy + 4);
					string tmp = nhapChuoi(boxx + 61, boxy + 4);
	
					if(tmp == "exit"){
						break;
					}
					strcpy(loai, tmp.c_str()); 
					strcpy(loai, fix_HoTen(loai));
					
					if (strcmp(loai, "\0") == 0)
					{
						gotoxy(boxx + 14, boxy + 10); cout<<"KHONG BO TRONG!";
						Sleep(1000);  
						gotoxy(boxx + 14, boxy + 10); cout<<"                 ";
						gotoxy(boxx + 61, boxy + 4);  cout<<"                 ";
					}
					else
					{
						demfield++;
						gotoxy(boxx + 61, boxy + 4);  cout<<"                 ";
						gotoxy(boxx + 61, boxy + 4);  cout<<loai;
						trung = true;
					}
				}while(trung == false);
				if (strcmp(loai, "") == 0) break;
				
				// NHAP SO CHO MAY BAY >= 20
				do{
					trung = false;
					gotoxy(boxx + 61, boxy + 6);
					char cho[10];
					string tmp = nhapChuoi(boxx + 61, boxy + 6);
	
					if(tmp == "exit"){
						break;
					}
					strcpy(cho, tmp.c_str()); 
					
					strcpy(cho, fix_Ma(cho));
					if (strcmp(cho, "\0") == 0)
					{
						gotoxy(boxx + 14, boxy + 10); cout<<"KHONG BO TRONG";
						Sleep(1000);  
						gotoxy(boxx + 14, boxy + 10); cout<<"               ";
						gotoxy(boxx + 61, boxy + 6);  cout<<"               ";
					}
					else
					{
						int soCho = atoi(cho);
						if (soCho < 20)
						{
							gotoxy(boxx + 14, boxy + 10); cout<<"CHI NHAN SO VA PHAI LON HON 20!";
							Sleep(1000);  
							gotoxy(boxx + 14, boxy + 10); cout<<"                                 ";
							gotoxy(boxx + 61, boxy + 6);  cout<<"                                 ";
						}
						else
						{
							demfield++;
							cho_edit = soCho;
							gotoxy(boxx + 61, boxy + 6);  cout<<"                                 ";
							gotoxy(boxx + 61, boxy + 6);  cout<<cho_edit;
							trung = true;
						}
					}
			
				}while(trung == false);
				if (cho_edit == 0) break;
				
				if (demfield == 2)
				{
					for (int i = 0; i < lmb.soluong; i++){
						if (strcmp(lmb.maybay[i]->soHieuMB, mb->soHieuMB) == 0){
							strcpy(lmb.maybay[i]->loaiMB, loai);
							lmb.maybay[i]->soCho = cho_edit;
							break;
						}
					}
					
					gotoxy(boxx + 14, boxy + 10); cout<<"SUA THANH CONG";
					Sleep(1500);  
					gotoxy(boxx + 14, boxy + 10); cout<<"               ";
					ofstream fileout;
					fileout.open("maybay.txt", ios::out);
					LuuFileMayBay(lmb,fileout);
					demfield = 0;
					break;
				}	
		}
		
}

void XoaMayBay(ListMayBay &lmb)
{
	NhapMA:
		system("cls");
		frame_NhapMaMayBay(40,8);
		char soHieu[15];
		gotoxy(45, 9); SetColor(ColorPURPLE); SetBGColor(ColorWHITE);
		string ma = nhapChuoi(45,9);
		if (ma == "exit")
			return;
		strcpy(soHieu, ma.c_str());
		strcpy(soHieu, fix_Ma(soHieu));
		int x = CheckSoHieu_MB(lmb, soHieu);
		if (x == -1)
		{
			SetColor(ColorWHITE); SetBGColor(ColorBLACK);
			gotoxy(35,12); cout<<"Khong tim thay may bay nay!";
			Sleep(1000);
			gotoxy(35,12); cout<<"            					";
			goto NhapMA;
		}
		int i;	
		for (i = x; i < lmb.soluong; i++)
		{
			lmb.maybay[i] = lmb.maybay[i+1];
		}
		lmb.soluong--;
}

void Danh_Sach_MayBay(ListMayBay &lmb)
{	
	int trang = 0, tongtrang = 0;
	if (lmb.soluong <= 20)
	{
		trang = 0;
		tongtrang = 1;
	}
	else
	{
		tongtrang = (lmb.soluong / 21) + 1;
	}
	while(1)
	{
	Xuat:	
		SetColor(ColorWHITE); SetBGColor(ColorBLACK);
		system("cls");
		TableMayBay();
		HienThiTrang(tongtrang, trang, 20, 28);
		ButtonThem(ColorDARKWHITE);
		ButtonXoa(ColorDARKWHITE);
		ButtonSua(ColorDARKWHITE);
		ButtonESC(ColorDARKWHITE);
		
		SetColor(ColorWHITE); SetBGColor(ColorBLACK);
		gotoxy(tabx + 4, taby + 3);
		int dem = 0;
		for (int i = 0 + trang * 20; i < 20 + trang * 20 && i < lmb.soluong; i++)
		{
			gotoxy(tabx + 4, taby + 3 + dem); cout <<dem+1;
			gotoxy(tabx + 14, taby + 3 + dem); cout<<lmb.maybay[i]->soHieuMB;
			gotoxy(tabx + 35, taby + 3 + dem); cout <<lmb.maybay[i]->loaiMB;
			gotoxy(tabx + 60, taby + 3 + dem); cout <<lmb.maybay[i]->soCho;
			dem++;
		}
		gotoxy(40, 29);
		cout << "[<-] Tro lai | Tiep Theo [->]"; 
		
		int c = 0;
		do{
			c = getch();
		}while(c != LEFT && c != RIGHT && c!= ESC && c != F1 && c != F2 && c != F3);
		if (c == ESC)
		{
			ButtonESC(127);
			Sleep(500);
			int a = XacNhanSaveFile();
			if(a == 1)
			{
				ofstream fileout;
				fileout.open("maybay.txt", ios::out);
				LuuFileMayBay(lmb, fileout);
			}
			break;
		}
		else if (c == LEFT)
		{
			if(tongtrang > 1 && trang > 0)
			{
				trang--;
				goto Xuat;
			}
		}
		else if (c == RIGHT)
		{
			if(tongtrang > 1 && trang  + 1 < tongtrang)
			{
				trang++;
				goto Xuat;
			}
		}
		else if (c == F1)
		{
			Sleep(500);
			NhapMayBay(lmb);
			goto Xuat;
		}
		else if (c == F2)
		{
			Sleep(500);
			XoaMayBay(lmb);
			system("cls");
			goto Xuat;
		}
		else if (c == F3)
		{
			Sleep(500);
			SuaMayBay(lmb);
			system("cls");
			goto Xuat;
		}
	}	
}

void NhapChuyenBay(ListMayBay lmb, SingleList_CB &listCB)
{
	while (true)
	{
		int keyhit,xThongBao = 14, yThongBao = 12;
		int demfield = 0;
		int socho = 0;
		
		system("cls");
		Box_NhapChuyenBayBay();
		ChuyenBay cb;
		strcpy(cb.soHieuMB, "");
		strcpy(cb.maCB, "");
		cb.tgKhoiHanh.ngay = -1;
		cb.tgKhoiHanh.thang = -1;
		cb.tgKhoiHanh.nam = -1;
		cb.tgKhoiHanh.gio = -1;
		cb.tgKhoiHanh.phut = -1;
		strcpy(cb.sanBayDen, "");
		cb.trangThai = 1;
		

			bool trung;
			// NHAP SO HIEU MAY BAY
			
			do{
				gotoxy(boxx + 28, boxy - 6); 
				string tmp = nhapChuoi(boxx + 28, boxy - 6);

				if(tmp == "exit"){
					break;
				}
				strcpy(cb.soHieuMB, tmp.c_str()); 
				strcpy(cb.soHieuMB, fix_Ma(cb.soHieuMB));	
				socho = getsocho(lmb, cb.soHieuMB);
				if (CheckSoHieu_MB(lmb, cb.soHieuMB) != -1)
				{
					demfield++;
					gotoxy(boxx + 28, boxy - 6);  	cout<<"                                 ";
					gotoxy(boxx + 28, boxy - 6); 	cout<<cb.soHieuMB;
					trung = true;
				}
				else if (strcmp(cb.soHieuMB, "\0") == 0)
				{
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"KHONG BO TRONG !";
					Sleep(1000);  
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                                 ";
					gotoxy(boxx + 28, boxy - 6);  cout<<"                                 ";
				}
				else
				{
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"SO HIEU MAY BAY NAY KHONG CO !";
					Sleep(1000);  
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                                 ";
					gotoxy(boxx + 28, boxy - 6);  cout<<"                                 ";
				}	
			}while(trung == false);
			if (strcmp(cb.soHieuMB, "") == 0) break;
			
			// NHAP MA CHUYEN BAY
			do{
				trung = false;
				gotoxy(boxx + 28, boxy - 4);
				string tmp = nhapChuoi(boxx + 28, boxy - 4);

				if(tmp == "exit"){
					break;
				}
				strcpy(cb.maCB, tmp.c_str()); 
				strcpy(cb.maCB, fix_Ma(cb.maCB));
				
				if (Check_MaCB(listCB, cb.maCB) == 1)
				{
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"MA CHUYEN BAY NAY DA CO!";
					Sleep(1000);  
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                                 ";
					gotoxy(boxx + 28, boxy - 4);  cout<<"                                 ";
				}
				else if (strcmp(cb.maCB, "\0") == 0)
				{
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"KHONG BO TRONG!";
					Sleep(1000);  
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                                 ";
					gotoxy(boxx + 28, boxy - 4);  cout<<"                                 ";
				}
				else
				{
					demfield++;
					gotoxy(boxx + 28, boxy - 4);  cout<<"                                 ";
					gotoxy(boxx + 28, boxy - 4);cout<<cb.maCB;
					trung = true;
				}
			}while(trung == false);
			if (strcmp(cb.maCB, "") == 0) break;
			
			// NHAP NAM
			do{
				trung = false;
				gotoxy(boxx + 28, boxy - 2);
				char nam[10];
				string tmp = nhapSo(boxx + 28, boxy - 2);

				if(tmp == "exit"){
					break;
				}
				strcpy(nam, tmp.c_str()); 
				
				strcpy(nam, fix_Ma(nam));
				if (strcmp(nam, "\0") == 0)
				{
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"KHONG BO TRONG";
					Sleep(1000);  
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                                ";
					gotoxy(boxx + 28, boxy - 2);  cout<<"    ";
				}
				else
				{
					int namBay = atoi(nam);
					if (namBay < 2019)
					{
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"CHI NHAN SO VA >= 2019!";
						Sleep(1000);  
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"                                 ";
						gotoxy(boxx + 28, boxy - 2);  	cout<<"    ";
					}
					else
					{
						demfield++;
						cb.tgKhoiHanh.nam = namBay;
						gotoxy(boxx + 28, boxy - 2);  	cout<<"                                 ";
						gotoxy(boxx + 28, boxy - 2);	cout<<cb.tgKhoiHanh.nam;
						trung = true;
					}
				}
		
			}while(trung == false);
			if (cb.tgKhoiHanh.nam == -1) break;
			
			// NHAP THANG
			do{
				trung = false;
				gotoxy(boxx + 28, boxy);
				char thang[10];
				string tmp = nhapSo(boxx + 28, boxy);

				if(tmp == "exit"){
					break;
				}
				strcpy(thang, tmp.c_str()); 
				
				strcpy(thang, fix_Ma(thang));
				if (strcmp(thang, "\0") == 0)
				{
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"KHONG BO TRONG";
					Sleep(1000);  
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                                ";
					gotoxy(boxx + 28, boxy);  cout<<"    ";
				}
				else
				{
					int thangBay = atoi(thang);
					if (thangBay <= 0 || thangBay > 12)
					{
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"THANG KHONG HOP LE ";
						Sleep(1000);  
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"                        ";
						gotoxy(boxx + 28, boxy);  	cout<<"    ";
					}
					else
					{
						demfield++;
						cb.tgKhoiHanh.thang = thangBay;
						gotoxy(boxx + 28, boxy);  	cout<<"    ";
						gotoxy(boxx + 28, boxy);	cout<<cb.tgKhoiHanh.thang;
						trung = true;
					}
				}
		
			}while(trung == false);
			if (cb.tgKhoiHanh.thang == -1) break;
			
			// NHAP NGAY
			do{
				trung = false;
				gotoxy(boxx + 28, boxy + 2);
				char ngay[10];
				string tmp = nhapSo(boxx + 28, boxy + 2);

				if(tmp == "exit"){
					break;
				}
				strcpy(ngay, tmp.c_str()); 
				
				strcpy(ngay, fix_Ma(ngay));
				if (strcmp(ngay, "\0") == 0)
				{
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"KHONG BO TRONG";
					Sleep(1000);  
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                                ";
					gotoxy(boxx + 28, boxy + 2);  cout<<"    ";
				}
				else
				{
					int ngayBay = atoi(ngay);
					if (ngayBay <= 0 || ngayBay > 31 || !Check_Date(cb.tgKhoiHanh.nam, cb.tgKhoiHanh.thang, ngayBay))
					{
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"NGAY KHONG HOP LE ";
						Sleep(1000);  
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"                                ";
						gotoxy(boxx + 28, boxy + 2);  	cout<<"    ";
					}
					else 
					{
						demfield++;
						cb.tgKhoiHanh.ngay = ngayBay;
						gotoxy(boxx + 28, boxy + 2);  	cout<<"    ";
						gotoxy(boxx + 28, boxy + 2);	cout<<cb.tgKhoiHanh.ngay;
						trung = true;
					}
				}
		
			}while(trung == false);
			if (cb.tgKhoiHanh.ngay == -1) break;
			
			// NHAP GIO
			do{
				trung = false;
				gotoxy(boxx + 28, boxy + 4);
				char gio[10];
				string tmp = nhapSo(boxx + 28, boxy + 4);

				if(tmp == "exit"){
					break;
				}
				strcpy(gio, tmp.c_str()); 
				
				strcpy(gio, fix_Ma(gio));
				if (strcmp(gio, "\0") == 0)
				{
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"KHONG BO TRONG";
					Sleep(1000);  
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                                ";
					gotoxy(boxx + 28, boxy + 4);  cout<<"    ";
				}
				else
				{
					int gioBay = atoi(gio);
					if (gioBay < 0 || gioBay > 23 )
					{
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"GIO KHONG HOP LE ";
						Sleep(1000);  
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"                                ";
						gotoxy(boxx + 28, boxy + 4);  	cout<<"    ";
					}
					else 
					{
						demfield++;
						cb.tgKhoiHanh.gio = gioBay;
						gotoxy(boxx + 28, boxy + 4);  	cout<<"    ";
						gotoxy(boxx + 28, boxy + 4);	cout<<cb.tgKhoiHanh.gio;
						trung = true;
					}
				}
		
			}while(trung == false);
			if (cb.tgKhoiHanh.gio == -1) break;
			
			// NHAP PHUT
			do{
				trung = false;
				gotoxy(boxx + 28, boxy + 6);
				char phut[10];
				string tmp = nhapSo(boxx + 28, boxy + 6);

				if(tmp == "exit"){
					break;
				}
				strcpy(phut, tmp.c_str()); 
				
				strcpy(phut, fix_Ma(phut));
				if (strcmp(phut, "\0") == 0)
				{
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"KHONG BO TRONG";
					Sleep(1000);  
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                                ";
					gotoxy(boxx + 28, boxy + 6);  cout<<"    ";
				}
				else
				{
					int phutBay = atoi(phut);
					if (phutBay < 0 || phutBay > 59)
					{
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"PHUT KHONG HOP LE ";
						Sleep(1000);  
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"                                ";
						gotoxy(boxx + 28, boxy + 6);  	cout<<"    ";
					}
					else 
					{
						demfield++;
						cb.tgKhoiHanh.phut = phutBay;
						gotoxy(boxx + 28, boxy + 6);  	cout<<"    ";
						gotoxy(boxx + 28, boxy + 6);	cout<<cb.tgKhoiHanh.phut;
						trung = true;
					}
				}
		
			}while(trung == false);
			if (cb.tgKhoiHanh.phut == -1) break;
			
			if (!Check_ThoiGian_ChuyenBay(cb.tgKhoiHanh))
			{
				gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"THOI GIAN CUA BAN DA QUA HAN";
				Sleep(1000);  
				gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"                                ";
				continue;
			}
			
			// NHAP SAN BAY DEN
			do{
				trung = false;
				gotoxy(boxx + 28, boxy + 8);
				char sanBayDen[150];
				string tmp = nhapChuoi(boxx + 28, boxy + 8);

				if(tmp == "exit"){
					break;
				}
				strcpy(sanBayDen, tmp.c_str()); 
				
				strcpy(sanBayDen, fix_HoTen(sanBayDen));
				if (strcmp(sanBayDen, "\0") == 0)
				{
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"KHONG BO TRONG";
					Sleep(1000);  
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                                ";
					gotoxy(boxx + 28, boxy + 8);  cout<<"    ";
				}
				else
				{
					demfield++;
					strcpy(cb.sanBayDen, sanBayDen);
					gotoxy(boxx + 28, boxy + 8);  	cout<<"    ";
					gotoxy(boxx + 28, boxy + 8);	cout<<cb.sanBayDen;
					trung = true;
				}
		
			}while(trung == false);
			if (cb.sanBayDen == 0) break;
			
			int soCho = getsocho(lmb, cb.soHieuMB);
			
			
			if (demfield == 8)
			{
				initListVe(cb.dsVe, soCho);
				InsertLast_CB(listCB, cb);
				gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"DA THEM THANH CONG";
				Sleep(1500);  
				gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                             ";
				demfield = 0;
			}
	}
	int a = XacNhanSaveFile();
	if(a == 1)
	{
		LuuFileChuyenBay(listCB, lmb);
	}
}
 void XoaChuyenBay(SingleList_CB &lcb){
 	NhapMA:
		system("cls");
		frame_NhapMaMayBay(40,8);
		char maCB[15];
		gotoxy(45, 9); SetColor(ColorPURPLE); SetBGColor(ColorWHITE);
		string ma = nhapChuoi(45,9);
		if (ma == "exit")
			return;
		strcpy(maCB, ma.c_str());
		strcpy(maCB, fix_Ma(maCB));
		int x = Check_MaCB(lcb, maCB);
		if (x == -1)
		{
			SetColor(ColorWHITE); SetBGColor(ColorBLACK);
			gotoxy(35,12); cout<<"Khong tim thay chuyen bay nay!";
			Sleep(1000);
			gotoxy(35,12); cout<<"            					";
			goto NhapMA;
		}
		else{
//			ChuyenBay *cb = SearchCB(lcb, maCB);
			bool flag = Delete_CB_Theo_Ma(lcb, maCB);
			if (flag){
				gotoxy(35,12); cout<<"Xoa chuyen bay thang cong!";
				Sleep(1000);
				gotoxy(35,12); cout<<"            					";
			}
			else
			{
				gotoxy(35,12); cout<<"Chuyen bay nay khong co hoac chua bay. Khong the xoa";
				Sleep(1000);
				gotoxy(35,12); cout<<"            										  ";
				goto NhapM
			}
		}
		
 }

int CountCB(SingleList_CB lcb)
{
	int count = 0;
	for (Node_CB *pNode = lcb.pHead; pNode != NULL; pNode=pNode->pNext){
		count++;
	}
	return count;
}

void Danh_Sach_ChuyenBay(SingleList_CB &lcb, ListMayBay lmb)
{	
	int trang = 0, tongtrang = 0, i = 0;
	int soluong = CountCB(lcb);
	if (soluong <= 20)
	{
		trang = 0;
		tongtrang = 1;
	}
	else
	{
		tongtrang = (soluong / 21) + 1;
	}
	while(1)
	{
	Xuat:	
		SetColor(ColorWHITE); SetBGColor(ColorBLACK);
		system("cls");
		TableChuyenBay();
		HienThiTrang(tongtrang, trang, 20, 28);
		ButtonThem(ColorDARKWHITE);
		ButtonXoa(ColorDARKWHITE);
		ButtonSua(ColorDARKWHITE);
		ButtonESC(ColorDARKWHITE);
		
		SetColor(ColorWHITE); SetBGColor(ColorBLACK);
		
		gotoxy(tabx + 4, taby + 3);
		int dem = 0;
		int item = 0 + trang * 20;
		int itemtoida = 20 + trang * 20;
		
		for (Node_CB *pNode = lcb.pHead; pNode != NULL; pNode=pNode->pNext)
		{
			if (item < itemtoida && item < soluong)
			{
				int ngay = pNode->cb.tgKhoiHanh.ngay;
				int thang = pNode->cb.tgKhoiHanh.thang;
				int nam = pNode->cb.tgKhoiHanh.nam;
				int gio = pNode->cb.tgKhoiHanh.gio;
				int phut = pNode->cb.tgKhoiHanh.phut;
				
				
				gotoxy(tabx + 4, taby + 3 + dem); cout <<dem+1;
				gotoxy(tabx + 12, taby + 3 + dem); cout<<pNode->cb.soHieuMB;
				gotoxy(tabx + 27, taby + 3 + dem); cout<<pNode->cb.maCB;
				gotoxy(tabx + 42, taby + 3 + dem); cout <<ngay<<"/"<<thang<<"/"<<nam;
				gotoxy(tabx + 60, taby + 3 + dem); cout<<gio<<":"<<phut;
				gotoxy(tabx + 73, taby + 3 + dem); cout <<pNode->cb.sanBayDen;
				gotoxy(tabx + 88, taby + 3 + dem); cout <<pNode->cb.trangThai;
				dem++;
				item++;
			}
		
		}
		
		gotoxy(40, 29);
		cout << "[<-] Tro lai | Tiep Theo [->]"; 
		
		int c = 0;
		do{
			c = getch();
		}while(c != LEFT && c != RIGHT && c!= ESC && c != F1 && c != F2 && c != F3);
		if (c == ESC)
		{
			ButtonESC(127);
			Sleep(500);
			int a = XacNhanSaveFile();
			if(a == 1)
			{
				LuuFileChuyenBay(lcb, lmb);
			}
			break;
		}
		else if (c == LEFT)
		{
			if(tongtrang > 1 && trang > 0)
			{
				trang--;
				goto Xuat;
			}
		}
		else if (c == RIGHT)
		{
			if(tongtrang > 1 && trang  + 1 < tongtrang)
			{
				trang++;
				goto Xuat;
			}
		}
		else if (c == F1)
		{
			Sleep(500);
			NhapChuyenBay(lmb, lcb);
			goto Xuat;
		}
		else if (c == F2)
		{
			Sleep(500);
			XoaChuyenBay(lcb);
			system("cls");
			goto Xuat;
		}
		else if (c == F3)
		{
			Sleep(500);
//			SuaMayBay(lmb);
			system("cls");
			goto Xuat;
		}
	}	
}




void Danh_Sach_HK_Trong_CB(SingleList_CB lcb, ListMayBay lmb)
{
	int trang = 0, tongtrang = 0;
	char maCB[15];
	Node_CB *pNodeCB;
	bool flag = false;
	while(flag == false)
	{
		system("cls");
		Box_DS_HK_Trong_CB();
		gotoxy(80,2);
		string ma = nhapChuoi(80,2);
		if (maCB == "exit") break;
		strcpy(maCB, ma.c_str());
		strcpy(maCB, fix_Ma(maCB)); // chua xet TH rong, ko co ma CB
		gotoxy(80,2); cout<<"                    ";
		gotoxy(80,2); cout<<maCB;
		if (strcmp(maCB, "\0") == 0)
		{
			gotoxy(35,28); cout <<"Khong bo trong";
			Sleep(1500);
			gotoxy(35,28); cout <<"					";
			goto Xuat;
		}
		int x = Check_MaCB(lcb, maCB);
		if (x == -1){
			gotoxy(35,28); cout <<"Ma Chuyen Bay khong ton tai!	";
			Sleep(1500);
			gotoxy(35,28); cout <<"								";
			goto Xuat;
		}else if (x == 1){
			pNodeCB = TimKiem_CB(lcb, maCB);
			flag = true;
		}
		
		gotoxy(49,3); cout<<pNodeCB->cb.tgKhoiHanh.ngay;
		gotoxy(52,3); cout<<pNodeCB->cb.tgKhoiHanh.thang;
		gotoxy(55,3); cout<<pNodeCB->cb.tgKhoiHanh.nam;
		gotoxy(61,3); cout<<pNodeCB->cb.tgKhoiHanh.gio;
		gotoxy(64,3); cout<<pNodeCB->cb.tgKhoiHanh.phut;
		gotoxy(77,3); cout<<pNodeCB->cb.sanBayDen;
		
		if (pNodeCB->cb.dsVe.n <= 20)
		{
			trang = 0;
			tongtrang = 1;
		}
		else
		{
			tongtrang = (pNodeCB->cb.dsVe.n / 21) + 1;
		}
	}
	
	while(1)
	{
	Xuat:	
		system("cls");
		Box_DS_HK_Trong_CB();
		gotoxy(80,2); cout<<maCB;
		gotoxy(49,3); cout<<pNodeCB->cb.tgKhoiHanh.ngay;
		gotoxy(52,3); cout<<pNodeCB->cb.tgKhoiHanh.thang;
		gotoxy(55,3); cout<<pNodeCB->cb.tgKhoiHanh.nam;
		gotoxy(61,3); cout<<pNodeCB->cb.tgKhoiHanh.gio;
		gotoxy(64,3); cout<<pNodeCB->cb.tgKhoiHanh.phut;
		gotoxy(77,3); cout<<pNodeCB->cb.sanBayDen;
		HienThiTrang(tongtrang, trang, 20, 28);
		SetColor(ColorBLACK);
		ButtonESC(ColorDARKWHITE);
		
		SetColor(ColorWHITE); SetBGColor(ColorBLACK);
		gotoxy(tabx + 4, taby + 3);
		int socho = getsocho(lmb, pNodeCB->cb.soHieuMB);
		int dem = 0;
		for (int i = 0 + trang * 20; i < 20 + trang * 20 && i < socho; i++)
		{
			if (pNodeCB->cb.dsVe.ve[i] != ""){
				char cmnd[16];
				strcpy(cmnd,"");
				strcpy(cmnd,pNodeCB->cb.dsVe.ve[i].c_str());
				Node_HK *pHK = SearchHK(tree, cmnd);
				char hoten[150]; 
				strcpy(hoten,"");
				strcat(hoten, pHK->HK.ho );
				strcat(hoten, " ");
				strcat(hoten, pHK->HK.ten);
			
				gotoxy(tabx + 4, taby + 3 + dem); 	cout<<dem+1;
				gotoxy(tabx + 14, taby + 3 + dem); 	cout<<i+1;
				gotoxy(tabx + 25, taby + 3 + dem); 	cout<<pNodeCB->cb.dsVe.ve[i];
				gotoxy(tabx + 47, taby + 3 + dem); cout<<hoten;
				gotoxy(tabx + 75, taby + 3 + dem); cout<<pHK->HK.phai;
				dem++;
			}
			
		}
		gotoxy(40, 29);
		cout << "[<-] Tro lai | Tiep Theo [->]"; 
		
		int c = 0;
		do{
			c = getch();
		}while(c != LEFT && c != RIGHT && c != ESC);
		 if (c == LEFT)
		{
			if(tongtrang > 1 && trang > 0)
			{
				trang--;
				goto Xuat;
			}
		}
		else if (c == RIGHT)
		{
			if(tongtrang > 1 && trang  + 1 < tongtrang)
			{
				trang++;
				goto Xuat;
			}
		}
		else if (c == ESC)
		{
			break;
		}
	}	
}
void frame_NhapMaCB(int x, int y)
{
	gotoxy(x, y); SetBGColor(ColorDARKBLUE); SetColor(ColorDARKYELLOW);	cout << "    NHAP VAO MA CHUYEN BAY    ";
	gotoxy(x, y + 1); SetBGColor(ColorDARKBLUE);						cout << "    ";
	gotoxy(x + 4, y + 1);  SetBGColor(ColorWHITE); 							 cout << "                         ";
	gotoxy(x + 26, y + 1); SetBGColor(ColorDARKBLUE); 											  cout << "    ";
	gotoxy(x, y + 2); SetBGColor(ColorDARKBLUE);						cout << "                              ";
	SetBGColor(ColorBLACK); SetColor(ColorWHITE);
}


void Danh_Sach_Ve_Trong_CB(SingleList_CB lcb, ListMayBay lmb)
{
	frame_NhapMaCB(40,8);
	ChuyenBay cb;
	int trang = 0, tongtrang = 0, socho = 0;
	NhapMACB:
		gotoxy(47,9); SetColor(ColorPURPLE); SetBGColor(ColorWHITE); 	
		char maCB[15];
		string macb = nhapChuoi(47,9);
		if (macb == "exit") return; // ra Menu
		strcpy(maCB, macb.c_str());
		strcpy(maCB, fix_Ma(maCB));
		if (strcmp(maCB, "\0") == 0){
			gotoxy(50, 12); SetColor(ColorWHITE); SetBGColor(ColorBLACK);  cout<<"Khong bo trong";
			Sleep(1000);
			gotoxy(50, 12); cout<<"                       ";
			gotoxy(47,9); SetBGColor(ColorWHITE);cout<<"                     ";
			goto NhapMACB;
		}else{
			int x = Check_MaCB(lcb, maCB);
			if (x == 1)
			{
				cb = TimKiem_CB(lcb, maCB)->cb;
				goto DanhSachVeTrong;
			}else{
				gotoxy(50, 12); SetColor(ColorWHITE); SetBGColor(ColorBLACK);  cout<<"Khong ton tai ma nay!";
				Sleep(1000);
				gotoxy(50, 12); cout<<"                       ";
				gotoxy(47,9); SetBGColor(ColorWHITE);cout<<"                     ";
				goto NhapMACB;
			}
		}
	DanhSachVeTrong:
//		gotoxy(1,1); cout<<cb.dsVe.n;
//		system("pause");
		socho = getsocho(lmb, cb.soHieuMB);
		int vetrong = socho - cb.dsVe.n;	
		if (vetrong <= 20)
		{
			trang = 0;
			tongtrang = 1;
		}
		else
		{
			tongtrang = (vetrong / 21) + 1;
		}
		while(1)
		{
		Xuat:	
			system("cls");
			SetColor(ColorWHITE);
			SetBGColor(ColorBLACK);
			Box_DS_Ve_Trong_Trong_CB();
			HienThiTrang(tongtrang, trang, 20, 28);
			SetColor(ColorBLACK);
			ButtonESC(ColorDARKWHITE);
			SetColor(ColorWHITE); SetBGColor(ColorBLACK);
			gotoxy(46,3); cout<<cb.maCB;
			gotoxy(tabx + 30, taby + 3);
 	
 			
 			// Neu ve trong < 20 ve
			int dem = 0;
			if (tongtrang == 1){
				for (int i = 0 + trang * 20; i < 20 + tongtrang * 20 && i < socho; i++) 
				{
					if (cb.dsVe.ve[i] == ""){
						gotoxy(tabx + 30, taby + 3 + dem); 	cout<<dem+1;
						gotoxy(tabx + 56, taby + 3 + dem); 	cout<<i+1;
						dem++;
					}	
				}
			}	
			else if (tongtrang > 1) // Neu ve trong > 20 ve
			{			// DE NGHI BO COT STT
				for (int i = 0 + trang * 20; i < 20 + trang * 20 && i < socho; i++) 
				{
					if (cb.dsVe.ve[i] == ""){
						gotoxy(tabx + 30, taby + 3 + dem); 	cout<<dem+1;
						gotoxy(tabx + 56, taby + 3 + dem); 	cout<<i+1;
						dem++;
					}	
				}
			}
			gotoxy(40, 29);
			cout << "[<-] Tro lai | Tiep Theo [->]"; 
			
			int c = 0;
			do{
				c = getch();
			}while(c != LEFT && c != RIGHT && c != ESC);
			 if (c == LEFT)
			{
				if(tongtrang > 1 && trang > 0)
				{
					trang--;
					goto Xuat;
				}
			}
			else if (c == RIGHT)
			{
				if(tongtrang > 1 && trang  + 1 < tongtrang)
				{
					trang++;
					goto Xuat;
				}
			}
			else if (c == ESC)
			{
				break;
			}
		}	
}

void Danh_Sach_Thong_Ke_So_Luot_Bay(SingleList_CB lcb, ListMayBay lmb)
{
	int trang = 0, tongtrang = 0;
	int soluongcb = CountCB(lcb);
	if (soluongcb <= 20)
	{
		trang = 0;
		tongtrang = 1;
	}
	else
	{
		tongtrang = (soluongcb / 21) + 1;
	}
	
	while(1)
	{
		Xuat:
			system("cls");
			SetColor(ColorWHITE);
			SetBGColor(ColorBLACK);
			Box_DS_Thong_Ke_So_Luot_Bay();
			HienThiTrang(tongtrang, trang, 20, 28);
			SetColor(ColorBLACK);
			ButtonESC(ColorDARKWHITE);
			SetColor(ColorWHITE); SetBGColor(ColorBLACK);
			
			gotoxy(tabx + 30, taby + 3);
 	
 			int dem = 0;
 			Node_CB *pNode = lcb.pHead;
 			
 			for (int i = 0 + trang * 20; i < 20 + tongtrang * 20 && i < soluongcb; i++) 
			{
				while (pNode != NULL)
				{
					gotoxy(tabx + 30, taby + 3 + dem); cout<<pNode->cb.soHieuMB;
					gotoxy(tabx + 56, taby + 3 + dem); cout<<Dem(lcb,pNode->cb.soHieuMB);
					pNode = pNode->pNext;
					dem++;
				}
			}
 				
			
			gotoxy(40, 29);
			cout << "[<-] Tro lai | Tiep Theo [->]"; 
			
			int c = 0;
			do{
				c = getch();
			}while(c != LEFT && c != RIGHT && c != ESC);
			 if (c == LEFT)
			{
				if(tongtrang > 1 && trang > 0)
				{
					trang--;
					goto Xuat;
				}
			}
			else if (c == RIGHT)
			{
				if(tongtrang > 1 && trang  + 1 < tongtrang)
				{
					trang++;
					goto Xuat;
				}
			}
			else if (c == ESC)
			{
				break;
			}
			
	}
}


void NhapHanhKhach(NODPTR &tree)
{
	int  x = 28;
	int demfield = 0;
	
	system("cls");
	Box_NhapHanhKhach();
	HanhKhach hk;
	strcpy(hk.cmnd,  "");
	strcpy(hk.ho,  "");
	strcpy(hk.ten,  "");
	strcpy(hk.phai,  "");
	
	bool trung;
	// NHAP CMND
	do{
		trung = false;
		gotoxy(boxx + 28, boxy + 2); 
		string tmp = nhapChuoi(boxx + 28, boxy + 2);
		if(tmp == "exit"){
			break;
		}
		strcpy(hk.cmnd, tmp.c_str());
		strcpy(hk.cmnd, fix_Ma(hk.cmnd));
		if (CheckCMNDIsExisted(tree, hk.cmnd) == 1)
		{
			gotoxy(boxx + 14, boxy + 12); cout<<"CMND TRUNG!";
			Sleep(1000);  
			gotoxy(boxx + 14, boxy + 12); cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 2);  cout<<"                                 ";
		}
		else if (strcmp(hk.cmnd, "\0") == 0)
		{
			gotoxy(boxx + 14, boxy + 12); cout<<"KHONG BO TRONG !";
			Sleep(1000);  
			gotoxy(boxx + 14, boxy + 12); cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 2);  cout<<"                                 ";
		}
		else
		{
			demfield++;
			gotoxy(boxx + 28, boxy + 2);  cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 2); cout<<hk.cmnd;
			trung = true;
		}
	}while(trung == false);
//	if (strcmp(hk.cmnd, "") == 0) break;
	
	// NHAP HO
	do{
		trung = false;
		gotoxy(boxx + 28, boxy + 4);
		string tmp = nhapChuoi(boxx + 28, boxy + 4);
		if(tmp == "exit"){
			break;
		}
		strcpy(hk.ho, tmp.c_str());
		strcpy(hk.ho, fix_HoTen(hk.ho));
		
		if (strcmp(hk.ho, "\0") == 0)
		{
			gotoxy(boxx + 14, boxy + 12); cout<<"KHONG BO TRONG!";
			Sleep(1000);  
			gotoxy(boxx + 14, boxy + 12); cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 4);  cout<<"                                 ";
		}
		else
		{
			demfield++;
			gotoxy(boxx + 28, boxy + 4);  cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 4);cout<<hk.ho;
			trung = true;
		}
	}while(trung == false);
//	if (strcmp(hk.ho, "") == 0) break;
	
	// NHAP TEN
	do{
		trung = false;
		gotoxy(boxx + 28, boxy + 6);
		string tmp = nhapChuoi(boxx + 28, boxy + 6);
		if(tmp == "exit"){
			break;
		}
		strcpy(hk.ten, tmp.c_str());
		strcpy(hk.ten, fix_Ten(hk.ten));
		
		if (strcmp(hk.ten, "\0") == 0)
		{
			gotoxy(boxx + 14, boxy + 12); cout<<"KHONG BO TRONG!";
			Sleep(1000);  
			gotoxy(boxx + 14, boxy + 12); cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 6);  cout<<"                                 ";
		}
		else
		{
			demfield++;
			gotoxy(boxx + 28, boxy + 6);  cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 6);cout<<hk.ten;
			trung = true;
		}
	}while(trung == false);
	//if (strcmp(hk.ten, "") == 0) break;
	
	// NHAP PHAI (NAM/NU)
	do{
		trung = false;
		gotoxy(boxx + 28, boxy + 8);
		char phai[10];
		string tmp = nhapChuoi(boxx + 28, boxy + 8);
		if(tmp == "exit"){
			break;
		}
		char temp[10];
		strcpy(temp, tmp.c_str());
		strcpy(phai, fix_GioiTinh(temp));
		if (strcmp(phai, "\0") == 0)
		{
			gotoxy(boxx + 14, boxy + 12); cout<<"KHONG BO TRONG!";
			Sleep(1000);  
			gotoxy(boxx + 14, boxy + 12); cout<<"                                ";
			gotoxy(boxx + 28, boxy + 8);  cout<<"                                ";
		}
		else if ((strncmp(phai, "nam", 3) == 0 ) || (strncmp(phai, "nu", 2) == 0) )
		{
			demfield++;
			strcpy(hk.phai, phai);
			gotoxy(boxx + 28, boxy + 8);  cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 8);cout<<hk.phai;
			trung = true;
		}
		else
		{
			gotoxy(boxx + 14, boxy + 12); cout<<"KHONG DUNG YEU CAU!";
			Sleep(1000);  
			gotoxy(boxx + 14, boxy + 12); cout<<"                                ";
			gotoxy(boxx + 28, boxy + 8);  cout<<"                                ";
			
		}
	}while(trung == false);
//	if (strcmp(hk.phai, "") == 0) break;
	
	if (demfield == 4)
	{
		gotoxy(boxx + 14, boxy + 11); cout<<"DA THEM THANH CONG HANG KHACH";
		InsertHKToTree(tree, hk);
		Sleep(1500);  
		gotoxy(boxx + 14, boxy + 11); cout<<"                             ";
		demfield = 0;
	}
	
	int a = XacNhanSaveFile();
	if(a == 1)
	{
		LuuFileHKKoDeQuy(tree);
	}
}
bool Check_ListVe_Full(ChuyenBay cb,int socho) {
	int dem = 0;
	for (int i = 0; i < socho; i++) {
		if (cb.dsVe.ve[i] != ""){
			dem++;
		}
	}
	if (dem == socho) {
		return true;
	}
	else {
		return false;
	}
}

void Dat_Ve(ListMayBay lmb, SingleList_CB &lcb, NODPTR &tree)
{
	DatVeTiep:
	char cmnd[16];
	while (true)
	{
		system("cls");
		Box_DatVe();
		SetColor(ColorWHITE);
		ChuyenBay cb;
		string temp;
		char macb[15], cmnd[16], chonGhe[15];
		int vitri = 0, soGhe = -1, socho = 0;
		int xThongBao = 54, yThongBao = 19;
	NhapMaCB:
		do{
			gotoxy(17,5);
			temp = nhapChuoi(17,5);
			if (temp == "exit")
				goto THOAT;
			strcpy(macb, temp.c_str());
			strcpy(macb, fix_Ma(macb));
			if (Check_MaCB(lcb, macb) == true)
			{
				if (lmb.soluong > 0)
				{
					for (int i = 0; i < lmb.soluong; i++)
					{
						if (TimKiem_CB(lcb, macb) != NULL)
						{
							socho = lmb.maybay[i]->soCho;
							
							if (Check_ListVe_Full(TimKiem_CB(lcb, macb)->cb, socho) == false)
							{
								cb = TimKiem_CB(lcb, macb)->cb;
								if (cb.trangThai == 3){
									gotoxy(xThongBao, yThongBao); cout << "Chuyen bay da cat canh vui long chon chuyen bay khac!!";
									Sleep(1500);
									gotoxy(xThongBao, yThongBao); cout << "                                                       ";
									gotoxy(41, 5); cout<<"                    ";
									strcpy(macb,"");
									goto NhapMaCB;
								}
								else if (cb.trangThai == 0){
									gotoxy(xThongBao, yThongBao); cout << "Chuyen bay da huy vui long chon chuyen bay khac!!";
									Sleep(1500);
									gotoxy(xThongBao, yThongBao); cout << "                                                  ";
									gotoxy(41, 5); cout<<"                    ";
									strcpy(macb,"");
									goto NhapMaCB;
								}
								else{
									int cot = 10, dong = 15;
									for (int i = 0; i < socho; i++) {
										if (cb.dsVe.ve[i] == "") {
											SetColor(ColorWHITE);
											SetBGColor(ColorGREEN);
											gotoxy(cot, dong); cout << i+1;
											cot = cot + 5;
										}
										else if (cb.dsVe.ve[i] != "") {
											SetColor(ColorWHITE);
											SetBGColor(ColorRED);
											gotoxy(cot, dong); cout << i+1;
											cot = cot + 5;
										}
										if (cot % 40 == 0) {
											dong = dong + 2;
											cot = 10;
										}
									}
									SetColor(ColorWHITE);
									SetBGColor(ColorBLACK);
									goto ChonGhe;
								}
							}
						}
						else if (Check_ListVe_Full(TimKiem_CB(lcb, macb)->cb, socho) == true) {
							gotoxy(xThongBao, yThongBao); cout << "Ve da ban het vui long chon chuyen bay khac!!";
							Sleep(1000);
							gotoxy(xThongBao, yThongBao); cout << "                                             ";
							
							strcpy(macb, "");
							goto NhapMaCB;
						}
					}
				}	
			}
			else{
				gotoxy(xThongBao, yThongBao); cout << "Ma chuyen bay khong ton tai!";
				Sleep(1000);
				gotoxy(xThongBao, yThongBao); cout << "                            ";
				gotoxy(41, 5); cout<<"                              ";
				strcpy(macb, "");
				goto NhapMaCB;
			}
		}while(strcmp(macb, "") == 0);
		
	ChonGhe:
		do
		{
			strcpy(chonGhe,"");
			gotoxy(18,11);
			temp = nhapSo(18, 11);
			strcpy(chonGhe, temp.c_str());
			strcpy(chonGhe, fix_Ma(chonGhe));
			if (temp == "exit") {
				goto THOAT;
			}
			if (strcmp(chonGhe, "\0") == 0)
			{
				gotoxy(xThongBao, yThongBao); cout << "Khong bo trong";
				Sleep(1000);
				gotoxy(xThongBao, yThongBao); cout << "               ";
				goto ChonGhe;
			}
			else
			{
				soGhe = atoi(chonGhe);
				if (soGhe <= 0)
				{
					gotoxy(xThongBao, yThongBao); cout << "Vi tri ghe khong hop le!";
					Sleep(2000);
					gotoxy(xThongBao, yThongBao); cout << "                                           ";
					gotoxy(18, 11); cout<<"                              ";
					strcpy(chonGhe, "");
					goto ChonGhe;
				}
				else 
				{
					if (soGhe < socho) {
						if (cb.dsVe.ve[soGhe-1] != "") {
							gotoxy(xThongBao, yThongBao); cout << "Vi tri da duoc chon vui long chon lai!";
							Sleep(2000);
							gotoxy(xThongBao, yThongBao); cout << "                                      ";
							gotoxy(18, 11); cout<<"                              ";
							strcpy(chonGhe, "");
							goto ChonGhe;
						}
						else if (cb.dsVe.ve[soGhe-1] == "") {
							goto NhapCMND;
						}
					}
					else if (soGhe > socho) {
						gotoxy(xThongBao, yThongBao); cout << "Vi tri ghe khong ton tai vui long chon lai!";
						Sleep(2000);
						gotoxy(xThongBao, yThongBao); cout << "                                           ";
						gotoxy(18, 11); cout<<"                              ";
						strcpy(chonGhe, "");
						goto ChonGhe;
					}
				}
				
			}
		} while (temp ==  "exit");
	NhapCMND:
		do{
			gotoxy(18,8);
			temp = nhapChuoi(18, 8);
			if (temp == "exit")
				goto THOAT;
			strcpy(cmnd, temp.c_str());
			strcpy(cmnd, fix_Ma(cmnd));
			if (temp != "exit")
			{
				if (SearchHK(tree, cmnd) != NULL)
				{
					
					if (CheckHKTrongCB(cb.dsVe, socho, cmnd) == 1)
					{
						gotoxy(xThongBao, yThongBao); cout << "Ban da mua ve trong chuyen nay roi!";
						Sleep(2000);
						gotoxy(xThongBao, yThongBao); cout << "                                           ";
						gotoxy(18, 8); cout<<"                              ";
						goto NhapCMND;
					}
					else
					{
						Node_HK *pHK = SearchHK(tree, cmnd);
						gotoxy(59, 7); 	cout << pHK->HK.ho;
						gotoxy(59, 9); 	cout << pHK->HK.ten;
						gotoxy(59, 11); cout <<	pHK->HK.phai;
						
						int datve = XacNhanDatVe();
						if (datve == 1)
						{
							InsertVe(cb.dsVe, soGhe, cmnd);
							goto DatVeTiep;
						}
					}
					
					
				}
				else if (SearchHK(tree, cmnd) == NULL)
				{
					int a = XacNhanThemHanhKhach();
					if (a == 1){
						NhapHanhKhach(tree);
						goto DatVeTiep;
					}else{
						SetColor(ColorWHITE);
						SetBGColor(ColorBLACK);
						gotoxy(60, 15); cout << "                                 ";
						gotoxy(60, 16); cout << "                                 ";
						gotoxy(60, 17); cout << "                                 ";
						gotoxy(60, 18); cout << "                                 ";
						gotoxy(60, 19); cout << "                                 ";
						gotoxy(60, 20); cout << "                                 ";
						gotoxy(18,8); cout << "                    ";
						goto NhapCMND;
					}
					
				}
			}
		}while(strcmp(cmnd, "") == 0);
	THOAT:
		int a = XacNhanSaveFile();
		if(a == 1){
			LuuFileChuyenBay(lcb, lmb);
			system("cls");
		}
		system("cls");
		break;
	
	}
}

void HuyVe(SingleList_CB &lcb, ListMayBay lmb){
	HuyVeTiep:
	char cmnd[16];
	while (true)
	{
		system("cls");
		Box_HuyVe();
		SetColor(ColorWHITE);
		ChuyenBay cb;
		string temp;
		char macb[15], cmnd[16], chonGhe[15];
		int vitri = 0, soGhe = -1, socho = 0;
		int xThongBao = 54, yThongBao = 19;
	NhapMaCB:
		do{
			gotoxy(17,5);
			temp = nhapChuoi(17,5);
			if (temp == "exit")
				goto THOAT;
			strcpy(macb, temp.c_str());
			strcpy(macb, fix_Ma(macb));
			if (Check_MaCB(lcb, macb) == true)
			{
				if (lmb.soluong > 0)
				{
					for (int i = 0; i < lmb.soluong; i++)
					{
						if (TimKiem_CB(lcb, macb) != NULL)
						{
							socho = lmb.maybay[i]->soCho;
							
							cb = TimKiem_CB(lcb, macb)->cb;
							if (cb.trangThai == 3){
								gotoxy(xThongBao, yThongBao); cout << "Chuyen bay da cat canh khong huy ve duoc!!";
								Sleep(1500);
								gotoxy(xThongBao, yThongBao); cout << "                                                       ";
								gotoxy(41, 5); cout<<"                    ";
								strcpy(macb,"");
								goto NhapMaCB;
							}
							else if (cb.trangThai == 0){
								gotoxy(xThongBao, yThongBao); cout << "Chuyen bay da huy!!";
								Sleep(1500);
								gotoxy(xThongBao, yThongBao); cout << "                                                  ";
								gotoxy(41, 5); cout<<"                    ";
								strcpy(macb,"");
								goto NhapMaCB;
							}
							else{
								int cot = 10, dong = 10;
								for (int i = 0; i < socho; i++) {
									if (cb.dsVe.ve[i] != "") {
										SetColor(ColorWHITE);
										SetBGColor(ColorRED);
										gotoxy(cot, dong); cout << i+1;
										cot = cot + 5;
									}
									if (cot % 40 == 0) {
										dong = dong + 2;
										cot = 10;
									}
								}
								SetColor(ColorWHITE);
								SetBGColor(ColorBLACK);
								goto ChonGhe;
							}	
						}	
					}
				}	
			}
			else{
				gotoxy(xThongBao, yThongBao); cout << "Ma chuyen bay khong ton tai!";
				Sleep(1000);
				gotoxy(xThongBao, yThongBao); cout << "                            ";
				gotoxy(41, 5); cout<<"                              ";
				strcpy(macb, "");
				goto NhapMaCB;
			}
		}while(strcmp(macb, "") == 0);
		
	ChonGhe:
		do
		{
			strcpy(chonGhe,"");
			gotoxy(17,7);
			temp = nhapSo(17, 7);
			strcpy(chonGhe, temp.c_str());
			strcpy(chonGhe, fix_Ma(chonGhe));
			if (temp == "exit") {
				goto THOAT;
			}
			if (strcmp(chonGhe, "\0") == 0)
			{
				gotoxy(xThongBao, yThongBao); cout << "Khong bo trong";
				Sleep(1000);
				gotoxy(xThongBao, yThongBao); cout << "               ";
				goto ChonGhe;
			}
			else
			{
				soGhe = atoi(chonGhe);
				if (soGhe <= 0)
				{
					gotoxy(xThongBao, yThongBao); cout << "Vi tri ghe khong hop le!";
					Sleep(2000);
					gotoxy(xThongBao, yThongBao); cout << "                                           ";
					gotoxy(17, 7); cout<<"                              ";
					strcpy(chonGhe, "");
					goto ChonGhe;
				}
				else 
				{
					if (soGhe < socho) {
						if (cb.dsVe.ve[soGhe-1] != "") 
						{
							int huyve = XacNhanHuyVe();
							if (huyve == 1)
							{
								if (DeleteVe(cb.dsVe, soGhe) == true){
									gotoxy(boxx + 22, 29);
									cout << "HUY VE THANH CONG";
									Sleep(2000);
									goto HuyVeTiep;
								}else
								{
									gotoxy(boxx + 22, 29);
									cout << "HUY VE THAT BAI";
									Sleep(2000);
									goto HuyVeTiep;
								}
								
							}
							else{
								goto HuyVeTiep;
							}
						}
						else if (cb.dsVe.ve[soGhe-1] == "") {
							gotoxy(xThongBao, yThongBao); cout << "Vi tri ghe khong hop le!!";
							Sleep(2000);
							gotoxy(xThongBao, yThongBao); cout << "                                      ";
							gotoxy(17, 7); cout<<"                              ";
							strcpy(chonGhe, "");
							goto ChonGhe;
						}
					}
					else if (soGhe > socho) {
						gotoxy(xThongBao, yThongBao); cout << "Vi tri ghe khong ton tai vui long chon lai!";
						Sleep(2000);
						gotoxy(xThongBao, yThongBao); cout << "                                           ";
						gotoxy(17, 7); cout<<"                              ";
						strcpy(chonGhe, "");
						goto ChonGhe;
					}
				}
				
			}
		} while (temp ==  "exit");
	
	THOAT:
		int a = XacNhanSaveFile();
		if(a == 1){
			LuuFileChuyenBay(lcb, lmb);
			system("cls");
		}
		system("cls");
		break;
	
	}
	
}

	
void Menu(ListMayBay &lmb, SingleList_CB &lcb)
{	
	

	int keyhit;
	char menu_text[11][100] = {" 1. THEM MAY BAY                                                  ", 
							   " 2. THEM CHUYEN BAY                                               ", 
							   " 3. DAT VE                                                        ", 
							   " 4. DANH SACH MAY BAY                                             ", 
							   " 5. DANH SACH CHUYEN BAY                                          ",
							   " 6. HUY VE CUA HANH KHACH TRONG CHUYEN BAY                        ",
							   " 7. IN DANH SACH HANH KHACH THUOC CHUYEN BAY THEO MA              ", 
							   " 8. IN DANH SACH CHUYEN DAY KHOI NGAY TRONG NGAY DEN NOI ? CON VE ", 
							   " 9. IN DANH SACH CAC VE CON TRONG THEO MA CHUYEN BAY              ", 
							   " 10. THONG KE SO LAN BAY CUA CAC CHUYEN BAY                        ", 
							   " 11. KET THUC CHUONG TRINH                                        "};
	Menu:
	int x = 15, y = 16;
	system("cls");
	SetColor(15);
	gotoxy(25, 35);
	cout << "SINH VIEN : ";
	gotoxy(46, 35);
	cout << "- Ngo Hoang Quoc Bao";
	gotoxy(46, 36);
	cout << "- Phan Huy Phuong";
	
	for(int i = 0; i < 11; i++){
		gotoxy(x, y+i); cout << menu_text[i];
	}
	SetBGColor(ColorBLUE);
	gotoxy(x, 16); cout << menu_text[0];

	do{

		keyhit = getch();
		switch(keyhit){
			case UP:{
				gotoxy(15, y); 
				SetBGColor(0);
				cout << menu_text[y-16];
				y--;
				if (y < 16) y = 26;
				break;
			}
			case DOWN:{
				gotoxy(15, y); 
				SetBGColor(0);
				cout << menu_text[y-16];
				y++;
				if(y > 26) y = 16; 
				break;
			}
			case ENTER:{
				switch(y-16)
				{
					case 0:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						NhapMayBay(lmb);
						goto Menu;
					}	
					case 1:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						NhapChuyenBay(lmb, lcb);
						goto Menu;
					}
					case 2:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						Dat_Ve(lmb, lcb, tree);
						goto Menu;
					}
					case 3:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						Danh_Sach_MayBay(lmb);
						goto Menu;
					}
					case 4:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						Danh_Sach_ChuyenBay(lcb,lmb);
						goto Menu;
					}
					case 5:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						HuyVe(lcb, lmb);
						goto Menu;
					}
					case 6:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						Danh_Sach_HK_Trong_CB(lcb,lmb);
						goto Menu;
					}
					case 7:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						
						goto Menu;
					}
					case 8:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						Danh_Sach_Ve_Trong_CB(lcb,lmb);
						goto Menu;
					}
					case 9:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						Danh_Sach_Thong_Ke_So_Luot_Bay(lcb,lmb);
						goto Menu;
					}
					case 10:
					{
						SetBGColor(0);
						SetColor(15);
						exit(0);
					}	
				}
			}
		}
		gotoxy(15, y); 
		SetBGColor(9);
		cout << menu_text[y-16];
	
	}while(true);
}




int main(int argc, char** argv) {
	resizeConsole(960,700);
	ListMayBay lmb;
	SingleList_CB lcb;
	Init_CB(lcb);
	InitTreeHK(tree);
	DocFileHanhKhach(tree);
	DocFileMayBay(lmb);
	DocFileChuyenBay(lcb, lmb);
//	Box_HuyVe();



	Menu(lmb, lcb);
//	Box_SuaMayBay();
////	Box_DS_HK_Trong_CB();
////	XacNhanDatVe();
//	Danh_Sach_HK_Trong_CB(lcb, lmb);
//	Box_DS_Ve_Trong_Trong_CB();
//	NhapHanhKhach(tree);
//	Danh_Sach_Ve_Trong_CB(lcb,lmb);
//	TableChuyenBay();
//	Danh_Sach_ChuyenBay(lcb, lmb);
	return 0;
}
