#include <stdio.h>
#include <stdlib.h>

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;
} USERDATA;

USERDATA* g_pHeadNode = NULL;

// head에 넣기
void AddNewNode(int age, const char *pszName, const char *pszPhone) {
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	memset(pNewNode, 0, sizeof(USERDATA));

	pNewNode -> age = age;
	strcpy_s(pNewNode->name, sizeof(pNewNode -> name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	pNewNode->pNext = NULL;

	if (g_pHeadNode == NULL) {
		g_pHeadNode = pNewNode;
	} else {
		pNewNode->pNext = g_pHeadNode;
		g_pHeadNode = pNewNode;
	}
}

// 리스트 전체 삭제
void ReleaseList(void) {
	USERDATA* pTmp = g_pHeadNode;
	USERDATA* pDelete;
	while (pTmp != NULL) {
		//pNext값을 백업해놓고 free시킨다.
		pDelete = pTmp;
		pTmp = pTmp->pNext;

		// 뭐가 해제되고 있는지 찍어보기
		printf("Delete: [%p] age : %d\tname : %s\tphone : %s\t[%p]\n", pDelete, pDelete->age, pDelete->name, pDelete->phone, pDelete->pNext);

		free(pDelete);
	}


	g_pHeadNode = NULL;
}

void InitDummyData(void) {
	//Input
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(11, "Goon", "010-1234-5678");
}

void PrintList(void) {
	USERDATA* pTmp = g_pHeadNode;
	while (pTmp != NULL) {
		printf("[%p] age : %d\tname : %s\tphone : %s\t[%p]\n", pTmp, pTmp -> age, pTmp -> name, pTmp -> phone, pTmp -> pNext);
		pTmp = pTmp->pNext;
	}
}

int main() {
	InitDummyData();

	PrintList();

	ReleaseList();

	return 0;

}