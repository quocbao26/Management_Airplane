#include <iostream>
#include <string.h>
#include <stdio.h>
#include <mylib.h>
#include <fstream>
#include <ctype.h>
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
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

char arrHK[100];
int nHK = 0;


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
int CheckCMNDIsExisted(NODPTR tree_hk, char cmnd[])
{
	if (tree_hk != NULL)
	{
		if (strcmp(tree_hk->HK.cmnd, cmnd)== 0)
			return 1;
		if (strcmp(tree_hk->HK.cmnd, cmnd) > 0)
			CheckCMNDIsExisted(tree_hk->pLeft, cmnd);
		else if (strcmp(tree_hk->HK.cmnd, cmnd) < 0)
			CheckCMNDIsExisted(tree_hk->pRight, cmnd);
	}
	return -1;
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
	char *ten;
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
	char hodem[150];
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
char *fix_HoTen(char hoten[])
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
char *fix_Ten(char ma[])
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

char *fix_GioiTinh(char phai[])
{
	if( strcmp(phai, "\0") == 0)
		return phai;
		
	int dai = strlen(phai);
	int dem = 0;
	for(int i = 0; i < dai; i++)
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
			cout<<"\nCMND:"<<hk.cmnd;
			getline(filein, hoten, ',');
			char ho[100], ten[100], hotenc[200];
			strcpy(hotenc, hoten.c_str());
			cout<<"\nHo ten:"<<hotenc;
			strcpy(hk.ho, tach_ho_dem(hotenc));
			cout<<"\nHo:"<<hk.ho;
			strcpy(hk.ten, tach_Ten(hotenc));
			cout<<"\nTen:"<<hk.ten;
			filein>>hk.phai;
			cout<<"\nPhai:"<<hk.phai;
			getline(filein, tmp);
			InsertHKToTree(tree_hk, hk);
		}
	}while(!filein.eof());
	filein.close();
}



// =================================

// ========== VE ===================

struct Ve{
	int soVe;
	HanhKhach hk;
};
struct ListVe{
	int n;
	Ve listVe[MAXVE];
};
bool Empty(ListVe list)
{
	return list.n == 0;
}
bool Full(ListVe list)
{
	return list.n == MAXVE;
}

bool InsertVe(ListVe &list, int vitri, HanhKhach hk)
{
	if (list.listVe[vitri].soVe != -1)
		return false;
	else
	{
		list.listVe[vitri].soVe = vitri;
		list.listVe[vitri].hk = hk;
		list.n += 1;
		return true;
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
//		if (strcmp(list.listVe[i].hk.cmnd, "") == 0)
//			dem++;
//	}	
//	// may bay moi chua co hk nao
//	if (dem == list.n)
//		return true;
//	else
//	
//}

// ==================================









// ========= MAY BAY==========
struct MayBay{
	char soHieuMB[15];
	char loaiMB[40];
	int soCho;
};

struct ListMayBay{
	int soluong;
	MayBay *listMB[MAXMB]; 
};

int Empty_MB(ListMayBay dsMB)
{
	return dsMB.soluong == 0;
}
int Full_MB(ListMayBay dsMB)
{
	return dsMB.soluong == MAXMB;
}
// ========== THOI GIAN ============
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
	string *dsVe;	 
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


void Init_CB(SingleList_CB &listCB)
{
	listCB.pHead = listCB.pTail = NULL;
}

void LuuFileMayBay(ListMayBay listMB, ofstream &fileout)
{
	fileout << listMB.soluong<<endl;
	for (int i = 0; i < listMB.soluong; i++)
	{
		fileout << listMB.listMB[i]->soHieuMB << ","<<listMB.listMB[i]->loaiMB << ","<<listMB.listMB[i]->soCho<<endl;
	}
	
	fileout.close();
}
int Insert_MB(ListMayBay &listMB_Add, MayBay mb)
{
	int empty = Empty_MB(listMB_Add);
	int full = Full_MB(listMB_Add);
	if (empty == 1)
	{
		listMB_Add.listMB[0] = new MayBay;
 		strcpy(listMB_Add.listMB[0]->soHieuMB, mb.soHieuMB);
		listMB_Add.listMB[0]->soCho = mb.soCho;
		strcpy(listMB_Add.listMB[0]->loaiMB , mb.loaiMB);
		listMB_Add.soluong = 1;
		return 1;
	}
	else if (full)
	{
		return -1;
	}
		
	else
	{
		listMB_Add.listMB[listMB_Add.soluong] = new MayBay;
		strcpy(listMB_Add.listMB[listMB_Add.soluong]->soHieuMB, mb.soHieuMB);
		listMB_Add.listMB[listMB_Add.soluong]->soCho = mb.soCho;
		strcpy(listMB_Add.listMB[listMB_Add.soluong]->loaiMB , mb.loaiMB);
		listMB_Add.soluong++;
		return 1;
	}
}
void DocFileMayBay(ListMayBay &listmb, ifstream &filein)
{
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

int CheckSoHieu_MB(ListMayBay listMBCheckSoHieu, char sohieu[])
{
	if (Empty_MB(listMBCheckSoHieu))
		return -1;
	else
	{
		for (int i = 0; i < listMBCheckSoHieu.soluong; i++)
		{
			if (stricmp(listMBCheckSoHieu.listMB[i]->soHieuMB, sohieu) == 0)
				return i;
		}
		return -1;
	}
}

int Check_MaCB(SingleList_CB listCB, char macb[])
{
	Node_CB *pTmp = listCB.pHead;
	for (; pTmp != NULL; pTmp=pTmp->pNext)
	{
		if (strcmp(pTmp->cb.maCB, macb) == 0)
			return 1;
	}
	return -1;
}


void Delete_MB(ListMayBay &listMBDel, char sohieu[])
{
	for (int i = 0; i < listMBDel.soluong; i++)
	{
		if (strcmp(listMBDel.listMB[i]->soHieuMB, sohieu) == 0)
		{
			MayBay* temp = listMBDel.listMB[i];
			int j = i+1;
			for( j ; j < listMBDel.soluong; j++){
				listMBDel.listMB[i] = listMBDel.listMB[j];
				i = j;
			}
			delete temp;
			listMBDel.listMB[j] = NULL;
			listMBDel.soluong--;
			cout<<"Da xoa\n";
			break;
		}
		
	}
	
}

void Xuat_MB(ListMayBay listmb)
{
	cout<<"So luong: "<<listmb.soluong<<endl;
	for (int i = 0; i < listmb.soluong; i++)
	{
		cout<<listmb.listMB[i]->soHieuMB<<"\t"<<listmb.listMB[i]->loaiMB<<"\t"<<listmb.listMB[i]->soCho<<endl;
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
	for (; pTmp != NULL; pTmp = pTmp->pNext)
	{
		ChuyenBay cb = pTmp->cb;
		cout<<cb.maCB<<"\t"
			<<cb.soHieuMB<<"\t"
			<<cb.tgKhoiHanh.ngay<<"/"<<cb.tgKhoiHanh.thang<<"/"<<cb.tgKhoiHanh.nam<<"  "<<cb.tgKhoiHanh.gio<<":"<<cb.tgKhoiHanh.phut<<"\t"
			<<cb.sanBayDen<<"\t"
			<<cb.dsVe<<"\t"
			<<cb.trangThai<<endl;
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
		if (ngay >= 1 && ngay <= Thang[thang])
		{
			if (nam >= 2019 && nam <= 2050)
			{
				return true;	
			}
		}
	}
	return false;
}

//bool Check_Date_Copy(ThoiGian time)
//{
//	int Thang[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
//	if (((time.nam % 4 == 0 && time.nam % 100) != 0) || time.nam % 400 == 0)
//	{
//		Thang[2] = 29;
//	}
//	if (time.thang >= 1 && time.thang <= 12)
//	{
//		if (time.ngay >= 1 && time.ngay <= Thang[time.thang])
//		{
//			if (time.nam >= 1900 && time.nam <= 2050)
//			{
//				if (time.gio > 0 && time.gio < 25) {
//					if (time.phut > 0 && time.phut < 61) {
//						return true;
//					}
//				}
//			}
//		}
//	}
//	return false;
//}
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
bool Check_ListVe(SingleList_CB lcb,int socho) {
	Node_CB *pTmp = lcb.pHead;
	int dem = 0;
	for (int i = 0; i < socho; i++) {
		if (pTmp->cb.dsVe[i] != ""){
			dem++;
		}
	}
	if (dem == socho) {
		return false;
	}
	else {
		return true;
	}
}
//kiem tra vi tri ghe trong ko
bool Check_ViTri_Ghe(SingleList_CB lcb, int vitri) {
	Node_CB *pTmp = lcb.pHead;
	if (pTmp->cb.dsVe[vitri] == "") {
		return true;
	}
	else return false;
}
//khoi tao danh sach ve =""
void Khoitao_ListVe(ChuyenBay cb,int socho) {
	for (int i = 0; i < socho; i++) {
		cb.dsVe[i] = "";
	}
}





void Box_NhapMayBay()
{
	SetColor(15);
	gotoxy(boxx, boxy); cout << char(201);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(187);
	
	gotoxy(boxx, boxy + 1); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 1); cout << char(186);
	
	gotoxy(boxx, boxy + 2); cout << char(186)<< " Nhap vao so hieu may bay: ";
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

void Box_NhapChuyenBayBay()
{
	SetColor(15);
	gotoxy(boxx, boxy); cout << char(201);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(187);
	
	gotoxy(boxx, boxy + 1); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 1); cout << char(186);
	
	gotoxy(boxx, boxy + 2); cout << char(186)<< " Nhap vao so hieu may bay: ";
	gotoxy(boxx + boxs + 1, boxy + 2); cout << char(186);
	
	gotoxy(boxx, boxy + 3); cout << char(186) ;
	gotoxy(boxx + boxs + 1, boxy + 3); cout << char(186);
	gotoxy(boxx, boxy + 4); cout << char(186)<< "       Nhap ma chuyen bay: ";
	gotoxy(boxx + boxs + 1, boxy + 4); cout << char(186);
	gotoxy(boxx, boxy + 5); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 5); cout << char(186);
	gotoxy(boxx, boxy + 6); cout << char(186)<< "    Nam: ";
	gotoxy(boxx + 15, boxy + 6); cout << "Thang: ";
	gotoxy(boxx + 25, boxy + 6); cout << "Ngay: ";
	gotoxy(boxx + 35, boxy + 6); cout << "Gio: ";
	gotoxy(boxx + 45, boxy + 6); cout << "Phut: ";
	gotoxy(boxx + boxs + 1, boxy + 6); cout << char(186);
	gotoxy(boxx, boxy + 7); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 7); cout << char(186);
	gotoxy(boxx, boxy + 8); cout << char(186)<<"              San bay den: ";
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
void TableMayBay()
{
	//resizeConsole(1000, 450);
	//	SetWindow(90, 40);
	resizeConsole(800,600);
	gotoxy(35, 2);
	cout << "DANH SACH MAY BAY";
	//textcolor(59);
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
void LoadMayBay(ListMayBay &lmb)
{	
	ifstream filein;
	filein.open("maybay.txt", ios::in);
	DocFileMayBay(lmb, filein);
	TableMayBay();
	gotoxy(tabx + 4, taby + 3);
	for (int i = 0; i < lmb.soluong; i++)
	{
		gotoxy(tabx + 4, taby + 3 + i); cout <<i+1;
		gotoxy(tabx + 14, taby + 3 + i); cout<<lmb.listMB[i]->soHieuMB;
		gotoxy(tabx + 35, taby + 3 + i); cout <<lmb.listMB[i]->loaiMB;
		gotoxy(tabx + 60, taby + 3 + i); cout <<lmb.listMB[i]->soCho;
	}
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
				gotoxy(x,y); cout<<"                                 ";
				gotoxy(x,y); cout<<s;
				break;
			}
			default:{
				if (s.length() < 30)
				{
					s+= char(key);
					gotoxy(x,y); cout<<"                                 ";
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
				gotoxy(x,y); cout<<"                                 ";
				gotoxy(x,y); cout<<s;
				break;
			}
			default:{
				if (s.length() < 5)
				{
					s+= char(key);
					gotoxy(x,y); cout<<"                                 ";
					gotoxy(x,y); cout<<s;
				}
				break;
			}
		}
	}
}

void NhapMayBay(ListMayBay &lmb)
{
	ifstream filein;
	filein.open("maybay.txt", ios::in);
	DocFileMayBay(lmb,filein);
	int keyhit,x = 28;
	int demfield = 0;
	while (true)
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

void NhapChuyenBay(ListMayBay lmb, SingleList_CB &listCB)
{
	ifstream filein;
	filein.open("maybay.txt", ios::in);
	DocFileMayBay(lmb,filein);
	int keyhit,xThongBao = 14, yThongBao = 12;
	int demfield = 0;
	while (true)
	{
		
		system("cls");
		Box_NhapChuyenBayBay();
		ChuyenBay cb;
		strcpy(cb.soHieuMB, "");
		strcpy(cb.maCB, "");
		cb.tgKhoiHanh.ngay = 0;
		cb.tgKhoiHanh.thang = 0;
		cb.tgKhoiHanh.nam = 0;
		cb.tgKhoiHanh.gio = 0;
		cb.tgKhoiHanh.phut = 0;
		strcpy(cb.sanBayDen, "");
		cb.trangThai = 1;
		

			bool trung;
			// NHAP SO HIEU MAY BAY
			
			do{
				gotoxy(boxx + 28, boxy + 2); 
				string tmp = nhapChuoi(boxx + 28, boxy + 2);

				if(tmp == "exit"){
					break;
				}
				strcpy(cb.soHieuMB, tmp.c_str()); 
				strcpy(cb.soHieuMB, fix_Ma(cb.soHieuMB));	
				
				if (CheckSoHieu_MB(lmb, cb.soHieuMB) != -1)
				{
					demfield++;
					trung = true;
				}
				else if (strcmp(cb.soHieuMB, "\0") == 0)
				{
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"KHONG BO TRONG !";
					Sleep(1000);  
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                                 ";
					gotoxy(boxx + 28, boxy + 2);  cout<<"                                 ";
				}
				else
				{
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"SO HIEU MAY BAY NAY KHONG CO !";
					Sleep(1000);  
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                                 ";
					gotoxy(boxx + 28, boxy + 2);  cout<<"                                 ";
				}	
			}while(trung == false);
			if (strcmp(cb.soHieuMB, "") == 0) break;
			
			// NHAP MA CHUYEN BAY
			do{
				trung = false;
				gotoxy(boxx + 28, boxy + 4);
				string tmp = nhapChuoi(boxx + 28, boxy + 4);

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
					gotoxy(boxx + 28, boxy + 4);  cout<<"                                 ";
				}
				else if (strcmp(cb.maCB, "\0") == 0)
				{
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"KHONG BO TRONG!";
					Sleep(1000);  
					gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                                 ";
					gotoxy(boxx + 28, boxy + 4);  cout<<"                                 ";
				}
				else
				{
					demfield++;
					gotoxy(boxx + 28, boxy + 4);  cout<<"                                 ";
					gotoxy(boxx + 28, boxy + 4);cout<<cb.maCB;
					trung = true;
				}
			}while(trung == false);
			if (strcmp(cb.maCB, "") == 0) break;
			
			// NHAP NAM
			do{
				trung = false;
				gotoxy(boxx + 4, boxy + 6);
				char nam[10];
				string tmp = nhapSo(boxx + 4, boxy + 6);

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
					gotoxy(boxx + 4, boxy + 6);  cout<<"    ";
				}
				else
				{
					int namBay = atoi(nam);
					if (namBay < 2019)
					{
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"CHI NHAN SO VA >= 2019!";
						Sleep(1000);  
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"                                 ";
						gotoxy(boxx + 4, boxy + 6);  	cout<<"    ";
					}
					else
					{
						demfield++;
						cb.tgKhoiHanh.nam = namBay;
						gotoxy(boxx + 4, boxy + 6);  	cout<<"                                 ";
						gotoxy(boxx + 4, boxy + 6);	cout<<cb.tgKhoiHanh.nam;
						trung = true;
					}
				}
		
			}while(trung == false);
			if (cb.tgKhoiHanh.nam == 0) break;
			
			// NHAP THANG
			do{
				trung = false;
				gotoxy(boxx + 21, boxy + 6);
				char thang[10];
				string tmp = nhapSo(boxx + 21, boxy + 6);

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
					gotoxy(boxx + 21, boxy + 6);  cout<<"    ";
				}
				else
				{
					int thangBay = atoi(thang);
					if (thangBay < 0 || thangBay > 12)
					{
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"THANG KHONG HOP LE ";
						Sleep(1000);  
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"                        ";
						gotoxy(boxx + 21, boxy + 6);  	cout<<"    ";
					}
					else
					{
						demfield++;
						cb.tgKhoiHanh.thang = thangBay;
						gotoxy(boxx + 21, boxy + 6);  	cout<<"    ";
						gotoxy(boxx + 21, boxy + 6);	cout<<cb.tgKhoiHanh.thang;
						trung = true;
					}
				}
		
			}while(trung == false);
			if (cb.tgKhoiHanh.thang == 0) break;
			
			// NHAP NGAY
			do{
				trung = false;
				gotoxy(boxx + 30, boxy + 6);
				char ngay[10];
				string tmp = nhapSo(boxx + 30, boxy + 6);

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
					gotoxy(boxx + 30, boxy + 6);  cout<<"    ";
				}
				else
				{
					int ngayBay = atoi(ngay);
					if (ngayBay < 0 || ngayBay > 31 || !Check_Date(cb.tgKhoiHanh.nam, cb.tgKhoiHanh.thang, ngayBay))
					{
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"NGAY KHONG HOP LE ";
						Sleep(1000);  
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"                                ";
						gotoxy(boxx + 30, boxy + 6);  	cout<<"    ";
					}
					else 
					{
						demfield++;
						cb.tgKhoiHanh.ngay = ngayBay;
						gotoxy(boxx + 30, boxy + 6);  	cout<<"    ";
						gotoxy(boxx + 30, boxy + 6);	cout<<cb.tgKhoiHanh.ngay;
						trung = true;
					}
				}
		
			}while(trung == false);
			if (cb.tgKhoiHanh.ngay == 0) break;
			
			// NHAP GIO
			do{
				trung = false;
				gotoxy(boxx + 39, boxy + 6);
				char gio[10];
				string tmp = nhapSo(boxx + 39, boxy + 6);

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
					gotoxy(boxx + 39, boxy + 6);  cout<<"    ";
				}
				else
				{
					int gioBay = atoi(gio);
					if (gioBay < 0 || gioBay > 24 )
					{
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"GIO KHONG HOP LE ";
						Sleep(1000);  
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"                                ";
						gotoxy(boxx + 39, boxy + 6);  	cout<<"    ";
					}
					else 
					{
						demfield++;
						cb.tgKhoiHanh.gio = gioBay;
						gotoxy(boxx + 39, boxy + 6);  	cout<<"    ";
						gotoxy(boxx + 39, boxy + 6);	cout<<cb.tgKhoiHanh.gio;
						trung = true;
					}
				}
		
			}while(trung == false);
			if (cb.tgKhoiHanh.gio == 0) break;
			
			// NHAP PHUT
			do{
				trung = false;
				gotoxy(boxx + 50, boxy + 6);
				char phut[10];
				string tmp = nhapSo(boxx + 50, boxy + 6);

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
					gotoxy(boxx + 50, boxy + 6);  cout<<"    ";
				}
				else
				{
					int phutBay = atoi(phut);
					if (phutBay < 0 || phutBay > 59)
					{
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"PHUT KHONG HOP LE ";
						Sleep(1000);  
						gotoxy(boxx + xThongBao, boxy + yThongBao); 	cout<<"                                ";
						gotoxy(boxx + 50, boxy + 6);  	cout<<"    ";
					}
					else 
					{
						demfield++;
						cb.tgKhoiHanh.phut = phutBay;
						gotoxy(boxx + 50, boxy + 6);  	cout<<"    ";
						gotoxy(boxx + 50, boxy + 6);	cout<<cb.tgKhoiHanh.phut;
						trung = true;
					}
				}
		
			}while(trung == false);
			if (cb.tgKhoiHanh.phut == 0) break;
			
			// NHAP SAN BAY DEN
			do{
				trung = false;
				gotoxy(boxx + 27, boxy + 8);
				char sanBayDen[150];
				string tmp = nhapSo(boxx + 27, boxy + 8);

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
					gotoxy(boxx + 27, boxy + 8);  cout<<"    ";
				}
				else
				{
					demfield++;
					strcpy(cb.sanBayDen, sanBayDen);
					gotoxy(boxx + 27, boxy + 8);  	cout<<"    ";
					gotoxy(boxx + 27, boxy + 8);	cout<<cb.sanBayDen;
					trung = true;
				}
		
			}while(trung == false);
			if (cb.sanBayDen == 0) break;
			
			if (demfield == 8)
			{
				InsertLast_CB(listCB, cb);
				gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"DA THEM THANH CONG";
				Sleep(1500);  
				gotoxy(boxx + xThongBao, boxy + yThongBao); cout<<"                             ";
				demfield = 0;
			}
	}
}

void NhapHanhKhach(NODPTR &tree)
{
	ifstream filein;
	filein.open("hanhkhach.txt", ios::in);
	DocFileHanhKhach(tree);
	int  x = 28;
	int demfield = 0;
	while (true)
	{
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
			if (strcmp(hk.cmnd, "") == 0) break;
			
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
			if (strcmp(hk.ho, "") == 0) break;
			
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
			if (strcmp(hk.ten, "") == 0) break;
			
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
			if (strcmp(hk.phai, "") == 0) break;
			
			if (demfield == 4)
			{
				gotoxy(boxx + 14, boxy + 10); cout<<"THANH CONG" <<" >>"<<hk.phai<<"<<";
				Sleep(1500);  
				gotoxy(boxx + 14, boxy + 10); cout<<"                             ";
				demfield = 0;
			}
	}
}
	
int Menu()
{
	
	ListMayBay lmb;
	int x = 15, y = 16;
	int keyhit;
	char menu_text[10][100] = {" 1. THEM MAY BAY                                                  ", 
							   " 2. THEM CHUYEN BAY                                               ", 
							   " 3. DAT VE                                                        ", 
							   " 4. DANH SACH MAY BAY                                             ", 
							   " 5. DANH SACH CHUYEN BAY                                          ",
							   " 6. IN DANH SACH HANH KHACH THUOC CHUYEN BAY THEO MA              ", 
							   " 7. IN DANH SACH CHUYEN DAY KHOI NGAY TRONG NGAY DEN NOI ? CON VE ", 
							   " 8. IN DANH SACH CAC VE CON TRONG THEO MA CHUYEN MA               ", 
							   " 9. THONG KE SO LAN BAY CUA CAC CHUYEN BAY                        ", 
							   " 10. KET THUC CHUONG TRINH                                        "};
	Menu:
	system("cls");
//	int c = 0;
//	int i = 1;
	SetColor(15);
	gotoxy(25, 35);
	cout << "SINH VIEN : ";
	gotoxy(46, 35);
	cout << "- Ngo Hoang Quoc Bao";
	gotoxy(46, 36);
	cout << "- Phan Huy Phuong";
	
	for(int i = 1; i <= 9; i++){
		gotoxy(x, y+i); cout << menu_text[i];
	}
	SetBGColor(9);
	gotoxy(x, 16); cout << menu_text[0];

	do{

		keyhit = getch();
		switch(keyhit){
			case UP:{
				gotoxy(15, y); 
				SetBGColor(0);
				cout << menu_text[y-16];
				y--;
				if (y < 16) y = 25;
				break;
			}
			case DOWN:{
				gotoxy(15, y); 
				SetBGColor(0);
				cout << menu_text[y-16];
				y++;
				if(y > 25) y = 16; 
				break;
			}
			case ENTER:{
//				cout << "Chon "<< (y - 16)<<endl;
//				system("pause");
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
						
						goto Menu;
					}
					case 2:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						
						goto Menu;
					}
					case 3:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						TableMayBay();
						goto Menu;
					}
					case 4:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						
						goto Menu;
					}
					case 5:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						
						goto Menu;
					}
					case 6:
					{
						SetBGColor(0);
						SetColor(15);
						system("cls");
						
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
						
						goto Menu;
					}
					case 9:
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
//		if(keyhit == UP)
//		{
//			gotoxy(x, y);
//			SetColor(15);
//			SetBGColor(9);
//			switch(y)
//			{
//				case 16 : gotoxy(15, 16); cout << menu_text[0]; break;
//				case 17 : gotoxy(15, 17); cout << menu_text[1]; break;
//				case 18 : gotoxy(15, 18); cout << menu_text[2]; break;
//				case 19 : gotoxy(15, 19); cout << menu_text[3]; break;
//				case 20 : gotoxy(15, 20); cout << menu_text[4]; break;
//				case 21 : gotoxy(15, 21); cout << menu_text[5]; break;
//				case 22 : gotoxy(15, 22); cout << menu_text[6]; break;
//				case 23 : gotoxy(15, 23); cout << menu_text[7]; break;
//				case 24 : gotoxy(15, 24); cout << menu_text[8]; break;
//				case 25 : gotoxy(15, 25); cout << menu_text[9]; break;
//				
//			}
//			y--;
//			if(y < 16)
//			{
//				y = 25;
//			}
//		}
//		else if(keyhit == DOWN)
//		{
//			gotoxy(x, y);
//			SetColor(15);
//			SetBGColor(9);
//			switch(y)
//			{
//				case 16 : gotoxy(15, 16); cout << menu_text[0]; break;
//				case 17 : gotoxy(15, 17); cout << menu_text[1]; break;
//				case 18 : gotoxy(15, 18); cout << menu_text[2]; break;
//				case 19 : gotoxy(15, 19); cout << menu_text[3]; break;
//				case 20 : gotoxy(15, 20); cout << menu_text[4]; break;
//				case 21 : gotoxy(15, 21); cout << menu_text[5]; break;
//				case 22 : gotoxy(15, 22); cout << menu_text[6]; break;
//				case 23 : gotoxy(15, 23); cout << menu_text[7]; break;
//				case 24 : gotoxy(15, 24); cout << menu_text[8]; break;
//				case 25 : gotoxy(15, 25); cout << menu_text[9]; break;
//			
//			}
//			y++;
//			if(y > 25)
//			{
//				y = 16;
//			}
//		}
//		
//		if(y == 16 && keyhit == ENTER)
//		{
//			SetColor(15);
//			system("cls");
//
//			goto Menu;
//		}
//		else if(y == 17 && keyhit == ENTER)
//		{
//			SetColor(15);
//			system("cls");
//
//			goto Menu;
//		}
//		else if(y == 18 && keyhit == ENTER)
//		{
//			SetColor(15);
//			system("cls");
//
//			goto Menu;
//		}
//		else if(y == 19 && keyhit == ENTER)
//		{
//			SetColor(15);
//			system("cls");
//
//			goto Menu;
//		}
//		else if(y == 20 && keyhit == ENTER)
//		{
//			SetColor(15);
//			system("cls");
//
//			goto Menu;
//		}
//		else if(y == 21 && keyhit == ENTER)
//		{
//			SetColor(15);
//			system("cls");
//
//			goto Menu;
//		}
//		else if(y == 22 && keyhit == ENTER)
//		{
//			SetColor(15);
//			system("cls");
//
//			goto Menu;
//		}
//		else if(y == 23 && keyhit == ENTER)
//		{
//			SetColor(15);
//			system("cls");
//
//			goto Menu;
//		}
//		else if(y == 24 && keyhit == ENTER)
//		{
//			SetColor(15);
//			system("cls");
//
//			goto Menu;
//		}
//		else if(y == 25 && keyhit == ENTER)
//		{
//			exit(0);
//			SetColor(15);
//		}
		
	}while(true);
}




int main(int argc, char** argv) {

	ListMayBay lst;
//	lst.soluong = 0;
//	char sohieu[15], loai[15];
//	int cho;
//	int y;
//	do
//	{
//		cout<<"So hieu may bay: ";
//		gets(sohieu);
//		
//		cout<<"\nLoai may bay: ";
//		gets(loai);
//		
//		cout<<"\nSo cho: ";
//		cin>>cho;
//		
//		Insert_MB(lst, sohieu, loai, cho);
//		cout<<"Tiep tuc(1: co - 0: khong): ";
//		cin>>y;
//		cin.ignore();
//	}while(y==1);
//	Xuat_MB(lst);
//	LuuFileMayBay(lst);
//	DocFileMayBay(lst);
//	Xuat_MB(lst);

//	NhapMayBay(lst);
	

//	char cmnd[16], ho[100], ten[100];
//	int phai;
//	
//	int y;
//	do
//	{
//		HanhKhach hk;
//		cout<<"CMND: ";
//		gets(hk.cmnd);
//		
//		cout<<"\nHo: ";
//		gets(hk.ho);
//		
//		cout<<"\nTen: ";
//		gets(hk.ten);
//		
//		cout<<"\nPhai(1:Nam - 0:Nu): ";
//		cin>>hk.phai;
//		
//		
//		InsertHKToTree(tree, hk);
//		cout<<"Tiep tuc(1: co - 0: khong): ";
//		cin>>y;
//		cin.ignore();
//	}while(y==1);
//	
//	LuuFileHKKoDeQuy(tree);
//	ofstream fileout;
//	fileout.open("hanhkhach.txt", ios::out);
//	LuuFileHanhKhach(tree, fileout);
//	fileout.close();
	
//	DocFileHanhKhach(tree);
//	cout<<endl;
//	PrintTree(tree);

//	NhapHanhKhach(tree);
//	NhapMayBay(lst); 
//	Menu();
//	LoadMayBay(lst);
	SingleList_CB listCB;
	NhapChuyenBay(lst, listCB);
//	NhapHanhKhach(tree);
	return 0;
}
