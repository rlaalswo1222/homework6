/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[----- [김민재] [2021041070] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode); // 연결리스트 생성
			break;
		case 'p': case 'P':
			printList(headnode); // 연결리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //연결리스트에 삽입. 넣은 값의 크기에 따라 오름차순 정렬로 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); // 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); // 연결리스트의 가장 끝에 노드를 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode); // 연결리스트의 가장 끝의 노드를 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); // 연결리스트의 가장 앞에 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode); // 연결리스트의 가장 앞 노드를 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); // 연결리스트를 역순으로 재배치
			break;
		case 'q': case 'Q':
			freeList(headnode); //연결리스트에 할당단 메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //그외 입력은 오류
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) { //연결리스트 생성
 
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // 노드 동적할당 생성
	temp->first = NULL; //비어있으므로 first 는 NULL
	return temp; 
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;  

	listNode* prev = NULL;
	while(p != NULL) { //노드의 마지막 까지 이동
		prev = p; // 이전 노드
		p = p->link; //다음 노드로 이동 
		free(prev); // 이전노드의 동적할당 해제
	}
	free(h); //헤드노드 동적할당 해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 노드 동적할당 생성
	node->key = key; // 노드의 데이터값을 입력값으로 지정
	node->link = NULL;

	if (h->first == NULL) //노드가 비어있다면
	{
		h->first = node; // 맨앞에 노드를 삽입
		return 0;
	}

	listNode* n = h->first; //현재 노드
	listNode* trail = h->first; //이전 노드

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) { // 삽입될 값이 현재 노드의 값보다 작거나 같다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = node; //헤드 노드는 삽입할 노드를 가리킴
				node->link = n; //삽입할 노드의 링크는, '삽입됐을 시 자신의 뒤에 놓이게 될 노드'를 가리킴
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n; //삽입할 노드의 링크는, '삽입됐을 시 자신의 뒤에 놓이게 될 노드'를 가리킴
				trail->link = node; // 삽입됐을 시 자신의 앞에 놓이게 될 노드 즉, 이전노드인 trail의 링크는
				//삽입할 노드를 가리킴
			}
			return 0;
		}

		trail = n; // 이전 노드를 가리킴
		n = n->link; //다음 노드로 이동
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node; // 삽입됐을 시 자신의 앞에 놓이게 될 노드 즉, 이전노드인 trail의 링크는
				//삽입할 노드를 가리킴
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 동적할당 생성
	node->key = key; // 노드의 데이터값을 입력값으로 지정
	node->link = NULL; // 마지막 노드로 들어갈 것이기 때문에 링크는 NULL

	if (h->first == NULL) //기존 노드가 비어있다면
	{
		h->first = node; //첫자리에 넣음
		return 0;
	}

	listNode* n = h->first; //현재 노드
	while(n->link != NULL) { // 노드의 마지막이 될때까지
		n = n->link; // 다음 노드로 이동
	}
	n->link = node; // 노드의 마지막 링크에 새 노드를 삽입
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적할당으로 생성
	node->key = key; // 노드의 데이터값을 입력값으로 지정

	node->link = h->first; // 새로운 노드에 헤드의 다음주소 저장
	h->first = node; // 헤드노드는 	삽입할 노드를 가리킴

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // 노드가 존재하지 않는다면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; 
	listNode* trail = NULL;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) { // 만약 현재 노드의 값과 삭제할 노드의 값이 같으면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { 
				h->first = n->link; //헤드노드는 현재노드를 가리키게 함
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link; //이전 노드는 현재노드를 가리키게 함
			}
			free(n); //이제 해제해도 연결리스트는 정상 작동
			return 0;
		}

		trail = n; //trail은 이전노드를 가리킴
		n = n->link; //다음 노드 로 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) // 노드가 비어있으면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {
		h->first = NULL; //헤드노드가 가리키는 곳을 없앰
		free(n); // 삭제할 노드 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {
		trail = n; // trail은 이전노드 가리킴
		n = n->link; //다음노드로 이동
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL; //이전노드가 가리킬 링크 없앰
	free(n);//이제 끝 노드 삭제해도 연결리스트 정상작동

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) // 노드가 비어있다면
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;  // 삭제할 노드 주소를 임시로 저장

	h->first = n->link; // 헤드의 다음 노드 주소를 삭제할 노드의 다음 주소로 저장
	free(n); //이제 노드를 삭제해도 연결리스트는 정상 작동

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { // 연결리스트가 비어있으면
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; 
	listNode *trail = NULL;
	listNode *middle = NULL;
	//n이 현재, middle이 그뒤, tail이 그뒤를 가르키면서 값을 가지고 있게된다.
	while(n != NULL){
		trail = middle; //trail은 middle을 가리킴
		middle = n; // middle은 n을 가리킴
		n = n->link; //다음 노드로 이동
		middle->link = trail; // middle의 링크는 trail을 가리킴
	}
	//끝나면 노드를 가리키는 방향이 역순으로 가리키게 됌

	h->first = middle; // 다 바뀌었으면 n은 Null이므로 그 다음 노드인 middle이 헤드노드가 된다.



	return 0;
}


void printList(headNode* h) { // 연결리스트 출력 
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p가 가리키는 곳을 처음으로 설정

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key); // 출력
		p = p->link; // 다음 링크 가리킴
		i++; // 아이템 인덱스 증가
	}

	printf("  items = %d\n", i); 
}

