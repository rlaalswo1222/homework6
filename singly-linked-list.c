/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
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
	printf("[----- [�����] [2021041070] -----]\n");

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
			headnode = initialize(headnode); // ���Ḯ��Ʈ ����
			break;
		case 'p': case 'P':
			printList(headnode); // ���Ḯ��Ʈ ���
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //���Ḯ��Ʈ�� ����. ���� ���� ũ�⿡ ���� �������� ���ķ� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); // ��� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); // ���Ḯ��Ʈ�� ���� ���� ��带 ����
			break;
		case 'e': case 'E':
			deleteLast(headnode); // ���Ḯ��Ʈ�� ���� ���� ��带 ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); // ���Ḯ��Ʈ�� ���� �տ� ����
			break;
		case 't': case 'T':
			deleteFirst(headnode); // ���Ḯ��Ʈ�� ���� �� ��带 ����
			break;
		case 'r': case 'R':
			invertList(headnode); // ���Ḯ��Ʈ�� �������� ���ġ
			break;
		case 'q': case 'Q':
			freeList(headnode); //���Ḯ��Ʈ�� �Ҵ�� �޸� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //�׿� �Է��� ����
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) { //���Ḯ��Ʈ ����
 
	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // ��� �����Ҵ� ����
	temp->first = NULL; //��������Ƿ� first �� NULL
	return temp; 
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;  

	listNode* prev = NULL;
	while(p != NULL) { //����� ������ ���� �̵�
		prev = p; // ���� ���
		p = p->link; //���� ���� �̵� 
		free(prev); // ��������� �����Ҵ� ����
	}
	free(h); //����� �����Ҵ� ����
	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // ��� �����Ҵ� ����
	node->key = key; // ����� �����Ͱ��� �Է°����� ����
	node->link = NULL;

	if (h->first == NULL) //��尡 ����ִٸ�
	{
		h->first = node; // �Ǿտ� ��带 ����
		return 0;
	}

	listNode* n = h->first; //���� ���
	listNode* trail = h->first; //���� ���

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key >= key) { // ���Ե� ���� ���� ����� ������ �۰ų� ���ٸ�
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {
				h->first = node; //��� ���� ������ ��带 ����Ŵ
				node->link = n; //������ ����� ��ũ��, '���Ե��� �� �ڽ��� �ڿ� ���̰� �� ���'�� ����Ŵ
			} else { /* �߰��̰ų� �������� ��� */
				node->link = n; //������ ����� ��ũ��, '���Ե��� �� �ڽ��� �ڿ� ���̰� �� ���'�� ����Ŵ
				trail->link = node; // ���Ե��� �� �ڽ��� �տ� ���̰� �� ��� ��, ��������� trail�� ��ũ��
				//������ ��带 ����Ŵ
			}
			return 0;
		}

		trail = n; // ���� ��带 ����Ŵ
		n = n->link; //���� ���� �̵�
	}

	/* ������ ������ ã�� ���� ��� , �������� ���� */
	trail->link = node; // ���Ե��� �� �ڽ��� �տ� ���̰� �� ��� ��, ��������� trail�� ��ũ��
				//������ ��带 ����Ŵ
	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //���ο� ��� �����Ҵ� ����
	node->key = key; // ����� �����Ͱ��� �Է°����� ����
	node->link = NULL; // ������ ���� �� ���̱� ������ ��ũ�� NULL

	if (h->first == NULL) //���� ��尡 ����ִٸ�
	{
		h->first = node; //ù�ڸ��� ����
		return 0;
	}

	listNode* n = h->first; //���� ���
	while(n->link != NULL) { // ����� �������� �ɶ�����
		n = n->link; // ���� ���� �̵�
	}
	n->link = node; // ����� ������ ��ũ�� �� ��带 ����
	return 0;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // ���ο� ��� �����Ҵ����� ����
	node->key = key; // ����� �����Ͱ��� �Է°����� ����

	node->link = h->first; // ���ο� ��忡 ����� �����ּ� ����
	h->first = node; // ������ 	������ ��带 ����Ŵ

	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // ��尡 �������� �ʴ´ٸ�
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; 
	listNode* trail = NULL;

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key == key) { // ���� ���� ����� ���� ������ ����� ���� ������
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) { 
				h->first = n->link; //������ �����带 ����Ű�� ��
			} else { /* �߰��� ���ų� �������� ��� */
				trail->link = n->link; //���� ���� �����带 ����Ű�� ��
			}
			free(n); //���� �����ص� ���Ḯ��Ʈ�� ���� �۵�
			return 0;
		}

		trail = n; //trail�� ������带 ����Ŵ
		n = n->link; //���� ��� �� �̵�
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) // ��尡 ���������
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->link == NULL) {
		h->first = NULL; //����尡 ����Ű�� ���� ����
		free(n); // ������ ��� ����
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->link != NULL) {
		trail = n; // trail�� ������� ����Ŵ
		n = n->link; //�������� �̵�
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->link = NULL; //������尡 ����ų ��ũ ����
	free(n);//���� �� ��� �����ص� ���Ḯ��Ʈ �����۵�

	return 0;
}
/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) // ��尡 ����ִٸ�
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;  // ������ ��� �ּҸ� �ӽ÷� ����

	h->first = n->link; // ����� ���� ��� �ּҸ� ������ ����� ���� �ּҷ� ����
	free(n); //���� ��带 �����ص� ���Ḯ��Ʈ�� ���� �۵�

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if(h->first == NULL) { // ���Ḯ��Ʈ�� ���������
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; 
	listNode *trail = NULL;
	listNode *middle = NULL;
	//n�� ����, middle�� �׵�, tail�� �׵ڸ� ����Ű�鼭 ���� ������ �ְԵȴ�.
	while(n != NULL){
		trail = middle; //trail�� middle�� ����Ŵ
		middle = n; // middle�� n�� ����Ŵ
		n = n->link; //���� ���� �̵�
		middle->link = trail; // middle�� ��ũ�� trail�� ����Ŵ
	}
	//������ ��带 ����Ű�� ������ �������� ����Ű�� ��

	h->first = middle; // �� �ٲ������ n�� Null�̹Ƿ� �� ���� ����� middle�� ����尡 �ȴ�.



	return 0;
}


void printList(headNode* h) { // ���Ḯ��Ʈ ��� 
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p�� ����Ű�� ���� ó������ ����

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key); // ���
		p = p->link; // ���� ��ũ ����Ŵ
		i++; // ������ �ε��� ����
	}

	printf("  items = %d\n", i); 
}

