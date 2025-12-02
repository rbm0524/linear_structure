#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;
} USERDATA;

USERDATA* g_pHeadNode = NULL;

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
		// head에 넣기 (stack 구조)
		//pNewNode->pNext = g_pHeadNode;
		//g_pHeadNode = pNewNode;
		
		// tail에 넣기 (queue 구조)
		USERDATA* pTail = g_pHeadNode;
		while (pTail -> pNext != NULL) {
			pTail = pTail->pNext;
		}
		pTail->pNext = pNewNode;
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

USERDATA* SearchByName(const char* pszName) {
	USERDATA* pTmp = g_pHeadNode;
	while (pTmp != NULL) {
		if (strcmp(pTmp -> name, pszName) == 0) {
			printf("\"%s\" : Found\n", pszName);
			return pTmp;
		}
		pTmp = pTmp->pNext;
	}

	printf("\"%s\" : is not found\n", pszName);
	return NULL;
}

void InitDummyData(void) {
	//Input
	AddNewNode(10, "Hoon", "010-1111-1111");
	AddNewNode(11, "Goon", "010-1234-5678");
	AddNewNode(12, "Poon", "010-9999-9999");
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

	SearchByName("Hoon");
	SearchByName("Goon");
	SearchByName("Poon");
	SearchByName("Jang");
	SearchByName("Kim");

	ReleaseList();

	return 0;

}