#include <iostream>
#include <string.h>
#include <stdio.h>
#include <mylib.h>
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
	int phai; // 0: Nu, 1 Nam
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
		if (strcmp(tree_hk->HK.cmnd, cmnd)== 0)
			return true;
		if (strcmp(tree_hk->HK.cmnd, cmnd) > 0)
			CheckCMNDIsExisted(tree_hk->pLeft, cmnd);
		else if (strcmp(tree_hk->HK.cmnd, cmnd) < 0)
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






// ========== THOI GIAN ============
struct ThoiGian{
	int gio, phut, ngay, thang, nam;
};


// ==========================


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
	return dsMB.soluong == 3;
}

int CheckSoHieu_MB(ListMayBay listMBCheckSoHieu, char sohieu[])
{
	if (Empty_MB(listMBCheckSoHieu))
		return 0;
	else
	{
		for (int i = 0; i < listMBCheckSoHieu.soluong; i++)
		{
			if (strcmp(listMBCheckSoHieu.listMB[i]->soHieuMB, sohieu) == 0)
				return i;
		}
		return 0;
	}
}

bool Check_MaMB(ListMayBay l, char mamb[])
{
	for (int i = 0; i < l.soluong; i++)
	{
		if (strcmp(l.listMB[i]->loaiMB, mamb) == 0)
			return true;
	}
	return false;
}

bool Insert_MB (ListMayBay &listMB_Add, char sohieu[],  char loai[], int cho)
{
	int empty = Empty_MB(listMB_Add);
	int full = Full_MB(listMB_Add);
	if (empty == 1)
	{
		cout<<"\nEmpty\n";
		listMB_Add.listMB[0] = new MayBay;
 		strcpy(listMB_Add.listMB[0]->soHieuMB, sohieu);
		listMB_Add.listMB[0]->soCho = cho;
		strcpy(listMB_Add.listMB[0]->loaiMB , loai);
		listMB_Add.soluong = 1;
		return true;
	}
	else if (full)
	{
		cout<<"\nFull\n";
		return false;
	}
		
	else
	{
		cout<<"\nChua day\n";
		listMB_Add.listMB[listMB_Add.soluong] = new MayBay;
		strcpy(listMB_Add.listMB[listMB_Add.soluong]->soHieuMB, sohieu);
		listMB_Add.listMB[listMB_Add.soluong]->soCho = cho;
		strcpy(listMB_Add.listMB[listMB_Add.soluong]->loaiMB ,loai);
		listMB_Add.soluong++;
		return true;
	}
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
	for (int i = 0; i < listmb.soluong; i++)
	{
		cout<<listmb.listMB[i]->soHieuMB<<"\t"<<listmb.listMB[i]->loaiMB<<"\t"<<listmb.listMB[i]->soCho<<endl;
	}
}





// =======================



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






char *fix_Ma(char ma[])
{
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
void XoaKiTu(char s[], int vitrixoa)
{
	int n = strlen(s);
	for (int i = vitrixoa + 1; i < n; i++)
		s[i-1] = s[i];
	s[n-1] = '\0';
}
char *fix_HoTen(char hoten[])
{
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

void Menu()
{

	
	int x = 15, y = 16;
	int keyhit;
	char menu_text[10][100] = {" 1. THEM MAY BAY ", 
								" 2. THEM CHUYEN BAY ", 
								" 3. DAT VE ", 
								" 4. DANH SACH MAY BAY ", 
								" 5. DANH SACH CHUYEN BAY ",
								" 6. IN DANH SACH HANH KHACH THUOC CHUYEN BAY THEO MA ", 
								" 7. IN DANH SACH CHUYEN DAY KHOI NGAY TRONG NGAY DEN NOI ? CON VE" , 
								" 8. IN DANH SACH CAC VE CON TRONG THEO MA CHUYEN MA " , 
								" 9. THONG KE SO LAN BAY CUA CAC CHUYEN BAY " , 
								" 10. KET THUC CHUONG TRINH "};
	Menu:

	int c = 0;
	int i = 1;
	SetColor(15);
	gotoxy(25, 35);
	cout << "SINH VIEN : ";
	gotoxy(46, 35);
	cout << "- Ngo Hoang Quoc Bao";
	gotoxy(46, 36);
	cout << "- Phan Huy Phuong";
	
	gotoxy(15, 16); cout << menu_text[0];
	gotoxy(15, 17); cout << menu_text[1];
	gotoxy(15, 18); cout << menu_text[2];
	gotoxy(15, 19); cout << menu_text[3];
	gotoxy(15, 20); cout << menu_text[4];
	gotoxy(15, 21); cout << menu_text[5];
	gotoxy(15, 22); cout << menu_text[6];
	gotoxy(15, 23); cout << menu_text[7];
	gotoxy(15, 24); cout << menu_text[8];
	gotoxy(15, 25); cout << menu_text[9];
	do{
		gotoxy(x, y);
		SetColor(159);
		switch(y)
		{
			case 16 : gotoxy(15, 16); cout << menu_text[0]; break;
			case 17 : gotoxy(15, 17); cout << menu_text[1]; break;
			case 18 : gotoxy(15, 18); cout << menu_text[2]; break;
			case 19 : gotoxy(15, 19); cout << menu_text[3]; break;
			case 20 : gotoxy(15, 20); cout << menu_text[4]; break;
			case 21 : gotoxy(15, 21); cout << menu_text[5]; break;
			case 22 : gotoxy(15, 22); cout << menu_text[6]; break;
			case 23 : gotoxy(15, 23); cout << menu_text[7]; break;
			case 24 : gotoxy(15, 24); cout << menu_text[8]; break;
			case 25 : gotoxy(15, 25); cout << menu_text[9]; break;
			
		}
		keyhit = getch();
		if(keyhit == UP)
		{
			gotoxy(x, y);
			SetColor(15);
			switch(y)
			{
				case 16 : gotoxy(15, 16); cout << menu_text[0]; break;
				case 17 : gotoxy(15, 17); cout << menu_text[1]; break;
				case 18 : gotoxy(15, 18); cout << menu_text[2]; break;
				case 19 : gotoxy(15, 19); cout << menu_text[3]; break;
				case 20 : gotoxy(15, 20); cout << menu_text[4]; break;
				case 21 : gotoxy(15, 21); cout << menu_text[5]; break;
				case 22 : gotoxy(15, 22); cout << menu_text[6]; break;
				case 23 : gotoxy(15, 23); cout << menu_text[7]; break;
				case 24 : gotoxy(15, 24); cout << menu_text[8]; break;
				case 25 : gotoxy(15, 25); cout << menu_text[9]; break;
				
			}
			y--;
			if(y < 16)
			{
				y = 25;
			}
		}
		else if(keyhit == DOWN)
		{
			gotoxy(x, y);
			SetColor(15);
			switch(y)
			{
				case 16 : gotoxy(15, 16); cout << menu_text[0]; break;
				case 17 : gotoxy(15, 17); cout << menu_text[1]; break;
				case 18 : gotoxy(15, 18); cout << menu_text[2]; break;
				case 19 : gotoxy(15, 19); cout << menu_text[3]; break;
				case 20 : gotoxy(15, 20); cout << menu_text[4]; break;
				case 21 : gotoxy(15, 21); cout << menu_text[5]; break;
				case 22 : gotoxy(15, 22); cout << menu_text[6]; break;
				case 23 : gotoxy(15, 23); cout << menu_text[7]; break;
				case 24 : gotoxy(15, 24); cout << menu_text[8]; break;
				case 25 : gotoxy(15, 25); cout << menu_text[9]; break;
			
			}
			y++;
			if(y > 25)
			{
				y = 16;
			}
		}
		
		if(y == 16 && keyhit == ENTER)
		{
			SetColor(15);
			system("cls");

			goto Menu;
		}
		else if(y == 17 && keyhit == ENTER)
		{
			SetColor(15);
			system("cls");

			goto Menu;
		}
		else if(y == 18 && keyhit == ENTER)
		{
			SetColor(15);
			system("cls");

			goto Menu;
		}
		else if(y == 19 && keyhit == ENTER)
		{
			SetColor(15);
			system("cls");

			goto Menu;
		}
		else if(y == 20 && keyhit == ENTER)
		{
			SetColor(15);
			system("cls");

			goto Menu;
		}
		else if(y == 21 && keyhit == ENTER)
		{
			SetColor(15);
			system("cls");

			goto Menu;
		}
		else if(y == 22 && keyhit == ENTER)
		{
			SetColor(15);
			system("cls");

			goto Menu;
		}
		else if(y == 23 && keyhit == ENTER)
		{
			SetColor(15);
			system("cls");

			goto Menu;
		}
		else if(y == 24 && keyhit == ENTER)
		{
			SetColor(15);
			system("cls");

			goto Menu;
		}
		else if(y == 25 && keyhit == ENTER)
		{
			exit(0);
			SetColor(15);
		}
		
	}while(true);
}




int main(int argc, char** argv) {

	ListMayBay lst;
	lst.soluong = 0;
	char sohieu[15], loai[15];
	int cho;
	int y;
	do
	{
		cout<<"So hieu may bay: ";
		gets(sohieu);
		
		cout<<"\nLoai may bay: ";
		gets(loai);
		
		cout<<"\nSo cho: ";
		cin>>cho;
		
		Insert_MB(lst, sohieu, loai, cho);
		cout<<"Tiep tuc(1: co - 0: khong): ";
		cin>>y;
		cin.ignore();
	}while(y==1);
	Xuat_MB(lst);
	char mbdel[50];
	cout<<"So hieu mb xoa: "; gets(mbdel);
	Delete_MB(lst, mbdel);
	Xuat_MB(lst);


	
	return 0;
}
