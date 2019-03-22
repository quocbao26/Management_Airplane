#include <iostream>
#include <string.h>
#define MAXMB 300
#define MAXVE 30

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;


// ========== CHUYEN BAY ============
struct ThoiGian{
	int gio, phut, ngay, thang, nam;
};
struct ChuyenBay{
	char maCB[15];
	ThoiGian tgKhoiHanh;
	char sanBayDen[150];
	int trangThai;
	char soHieuMB[15];
	char dsVe[10];	
};

struct Node_CB{
	ChuyenBay cb;
	Node_CB *pNext;
};
struct SingleList_CB
{
	Node_CB *pHead;
};
void Initialize(SingleList_CB &listCB)
{
	listCB.pHead = NULL;
}

ChuyenBay *NhapChuyenBay()
{
	ChuyenBay *cb = new ChuyenBay;
	cout<<"Ma CB: ";	gets(cb->maCB); fflush(stdin);
	cout<<"Thoi gian:\tNgay: ";	cin>>cb->tgKhoiHanh.ngay; fflush(stdin); cout<<endl;
	cout<<"Thang: ";	cin>>cb->tgKhoiHanh.thang; fflush(stdin); cout<<endl;
	cout<<"Nam: ";	cin>>cb->tgKhoiHanh.nam; fflush(stdin); cout<<endl;
	cout<<"Gio: ";	cin>>cb->tgKhoiHanh.gio; fflush(stdin); cout<<endl;
	cout<<"Phut: ";	cin>>cb->tgKhoiHanh.phut; fflush(stdin); cout<<endl;
	cout<<"So hieu MB: "; gets(cb->soHieuMB); fflush(stdin);
	cout<<"San bay den: "; gets(cb->sanBayDen); fflush(stdin);
	cout<<"Danh sach ve: "; gets(cb->dsVe); fflush(stdin);
	cout<<"Trang thai: "; cin>>cb->trangThai; fflush(stdin);
	return cb;
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

void InsertLast_CB(SingleList_CB &listCB, ChuyenBay *cb_moi)
{
	Node_CB *pNode = CreateNode_CB(cb_moi);
	if (listCB.pHead == NULL)
	{
		listCB.pHead =pNode;
	}
	else
	{
		Node_CB *pTmp = listCB.pHead;
		while (pTmp->pNext != NULL)
			pTmp = pTmp->pNext;
		pTmp->pNext = pNode;
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
	MayBay listMB[MAXMB];
};

int Empty_MB(ListMayBay dsMB)
{
	return dsMB.soluong == 0;
}
int Full_MB(ListMayBay dsMB)
{
	return dsMB.soluong == MAXMB;
}

int KiemTraSoHieu_MB(ListMayBay listMBCheckSoHieu, char *sohieu)
{
	if (Empty_MB(listMBCheckSoHieu))
		return 0;
	else
	{
		for (int i = 0; i < listMBCheckSoHieu.soluong; i++)
		{
			if (listMBCheckSoHieu.listMB[i].soHieuMB)
				return 1;
			else
				return 0;
		}
	}
}

int Insert_MB (ListMayBay &listMB_Add, char *sohieu, int socho)
{
	if (Empty_MB(listMB_Add))
	{
		listMB_Add.listMB[0].soHieuMB = sohieu;
		listMB_Add.listMB[0].soCho = socho;
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

// =========== HANH KHACH ==========
struct HanhKhach{
	string cmnd;
	char ho[100];
	char ten[100];
	bool phai;
};

struct Node_HK{
	HanhKhach *KH;
	Node_HK *pLeft;
	Node_HK *pRight;
};


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

// ==================================








int main(int argc, char** argv) {
	SingleList_CB list;
	Initialize(list);
	int yes;
	do{
		ChuyenBay *cb = NhapChuyenBay();
		InsertLast_CB(list,cb);
		cout<<"\nBan co muon tiep tuc khong?(1/co - 0/khong): ";
		cin>>yes;
		cin.ignore();
	}while(yes==1);
	cout<<"\n\t--------Danh sach chuyen bay--------\n";
	PrintList_CB(list);
	return 0;
}
