#include <iostream>
#include <string.h>
#include <stdio.h>
#include <mylib.h>
#define MAXMB 300
#define MAXVE 30

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
		//strcpy(arrHK[++nHK], hk.cmnd);
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

//typedef Node_CB* SingleList_CB;
//SingleList_CB pHead;

struct SingleList_CB
{
	Node_CB *pHead;
	Node_CB *pTail;
};


void Init_CB(SingleList_CB &listCB)
{
//	listCB = NULL;
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
//	int dem = 0;
//	while (dem < l.soluong)
//	{
//		while (l.listMB[dem]->loaiMB != NULL)
//		{
//			if (strcmp(l.listMB[dem]->loaiMB, mamb) == 0)
//				return true;	
//			
//		}	
//	}	
//	return false;
	for (int i = 0; i < l.soluong; i++)
	{
		if (strcmp(l.listMB[i]->loaiMB, mamb) == 0)
			return true;
	}
	return false;
}

//int Insert_MB (ListMayBay &listMB_Add, char sohieu[], int socho, char loai[])
//{
//	if (Empty_MB(listMB_Add))
//	{
//		strcpy(listMB_Add.listMB[0]->soHieuMB, sohieu);
//		listMB_Add.listMB[0]->soCho = socho;
//
//		strcpy(listMB_Add.listMB[0]->loaiMB , loai);
////		Initialize((listMB_Add.listMB[0].))
//		listMB_Add.soluong = 1;
//		return 1;
//	}
//	else if (Full_MB(listMB_Add))
//		return 0;
//	else
//	{
//		
//	}
//}


int Insert_MB(ListMayBay &listMB_Add, MayBay *mb)
{
	int i;
 	for (i = listMB_Add.soluong - 1; i >= 0; i--)
   {
      	listMB_Add.listMB[i+1] = listMB_Add.listMB[i];
   }
   listMB_Add.listMB[i] = mb;
   listMB_Add.soluong++;
   return 1;
   
}


// =======================


//int charCounter(char a[])
//{
//	int x = 0;
//	while(a[x] != '\0')
//		x++;
//	return x;
//}
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



int main(int argc, char** argv) {
	
	char a[100];
	cout<<"Ho ten: "; 
	gets(a);
	cout<<strlen(a)<<endl;
	cout<<fix_HoTen(a)<<endl;
	cout<<strlen(fix_HoTen(a))<<endl;
//	SingleList_CB list;
//	Initialize(list);
//	int yes;
//	do{
//		ChuyenBay *cb = NhapChuyenBay();
//		InsertLast_CB(list,cb);
//		cout<<"\nBan co muon tiep tuc khong?(1/co - 0/khong): ";
//		cin>>yes;
//		cin.ignore();
//	}while(yes==1);
//	cout<<"\n\t--------Danh sach chuyen bay--------\n";
//	PrintList_CB(list);

//	InitTreeHK(tree);
//	int yes;
//	do{
//		HanhKhach hk = ThemHanhKhach();
//		InsertHKToTree(tree, hk);
//		cout<<"\nBan co muon tiep tuc khong?(1/co - 0/khong): ";
//		cin>>yes;
//		cin.ignore();
//	}while(yes==1);
//	PrintTree(tree);
	return 0;
}
