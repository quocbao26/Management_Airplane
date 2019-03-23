#include <iostream>
#include <string.h>
#include <stdio.h>
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

int InsertVe(ListVe &list, int vitri, HanhKhach hk)
{
	
}

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
typedef Node_CB* SingleList_CB;
SingleList_CB pHead;

void Init_CB(SingleList_CB &listCB)
{
	listCB = NULL;
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
	if (listCB == NULL)
	{
		listCB = pNode;
	}
	else
	{
		Node_CB *pTmp = listCB;
		while (pTmp->pNext != NULL)
			pTmp = pTmp->pNext;
		pTmp->pNext = pNode;
	}
}

// TEST: in thu Danh sach CB
void PrintList_CB(SingleList_CB listCB)
{
	Node_CB *pTmp = listCB;
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

int Insert_MB (ListMayBay &listMB_Add, char sohieu[], int socho)
{
	if (Empty_MB(listMB_Add))
	{
		strcpy(listMB_Add.listMB[0]->soHieuMB, sohieu);
		listMB_Add.listMB[0]->soCho = socho;
//		Initialize((listMB_Add.listMB[0].))
		listMB_Add.soluong = 1;
		return 1;
	}
	else if (Full_MB(listMB_Add))
		return 0;
	else
	{
		
	}
}


// =======================










int main(int argc, char** argv) {
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

	InitTreeHK(tree);
	int yes;
	do{
		HanhKhach hk = ThemHanhKhach();
		InsertHKToTree(tree, hk);
		cout<<"\nBan co muon tiep tuc khong?(1/co - 0/khong): ";
		cin>>yes;
		cin.ignore();
	}while(yes==1);
	PrintTree(tree);
	return 0;
}
