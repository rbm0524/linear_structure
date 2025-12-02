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
	putchar('\n');
}

// 지울 노드 찾기
USERDATA* SearchToRemove(USERDATA** ppPrev, const char *pszName) {
	USERDATA* pCurrent = g_pHeadNode;
	USERDATA* pPrev = NULL; // pTmp가 HEAD일 때(초기값) pPrev는 NULL이어야 한다.
	while (pCurrent != NULL) {
		if (strcmp(pCurrent->name, pszName) == 0) {

			*ppPrev = pPrev;
			return pCurrent; // 찾은 노드의 주소 반환
		}
		pPrev = pCurrent;
		pCurrent = pCurrent->pNext;
	}

	return NULL;
}

// 노드 지우기
void RemoveNode(USERDATA* pPrev) { // 지울 노드의 앞 노드만 알아도 pNext로 지울 노드를 알 수 있다.
	
	USERDATA* pRemove = NULL;
	if (pPrev == NULL) {
		if (g_pHeadNode == NULL) {
			return;
		}
		else {
			pRemove = g_pHeadNode;
			g_pHeadNode = g_pHeadNode->pNext;
			printf("RemoveNode(): %s\n", pRemove -> name);
			free(pRemove);
		}
		return;
	}
	// HEAD 노드가 아니다.
	pRemove = pPrev->pNext;
	pPrev->pNext = pRemove->pNext;
	printf("RemoveNode(): %s\n", pRemove->name);
	free(pRemove);
}

void RemoveTest01() {

	AddNewNode(10, "Hoon", "010-1111-1111");
	printf("\n------------------노드 하나 삭제 검증---------------------\n");
	PrintList();
	USERDATA* pPrev = NULL; // 이전 노드 저장
	if(SearchToRemove(&pPrev, "Hoon")) RemoveNode(pPrev); // 지울 노드와 지울 노드의 앞 노드 검사
	PrintList();
	ReleaseList();
}

void RemoveTest02() {

	USERDATA* pPrev = NULL;
	printf("\n---------------------3개의 노드 중 첫 번째 노드 삭제 검증---------------------\n");
	InitDummyData();
	PrintList();
	if (SearchToRemove(&pPrev, "Hoon")) RemoveNode(pPrev);
	PrintList();
	AddNewNode(10, "Hoon", "010-1111-1111");
	ReleaseList();
}

void RemoveTest03() {

	USERDATA* pPrev = NULL;

	printf("\n---------------------3개의 노드 중 두 번째 노드 삭제 검증---------------------\n");
	InitDummyData();
	PrintList();
	if (SearchToRemove(&pPrev, "Goon")) RemoveNode(pPrev);
	PrintList();
	AddNewNode(12, "Goon", "010-1234-5678");
	ReleaseList();
}

void RemoveTest04() {

	USERDATA* pPrev = NULL;
	printf("\n---------------------3개의 노드 중 세 번째 노드 삭제 검증---------------------\n");
	InitDummyData();
	PrintList();
	if (SearchToRemove(&pPrev, "Poon")) RemoveNode(pPrev);
	PrintList();
	AddNewNode(12, "Poon", "010-9999-9999");
	ReleaseList();
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

	printf("\n노드 삭제 검증 시작\n");
	RemoveTest01();
	RemoveTest02();
	RemoveTest03();
	RemoveTest04();

	return 0;

}