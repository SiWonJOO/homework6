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

typedef struct Node { //typedef 형태로 구조체 선언
	int key;
	struct Node* link; //구조체를 가르키는 포인터 변수 선언
} listNode;

typedef struct Head { //typedef 형태로 구조체 선언
	struct Node* first; // Node 구조체 형태로 first 구조체 선언
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
	headNode* headnode=NULL; // 처음 헤드노드를 NULL값으로 초기화해준다.

    printf("[----- [SIWON JOO] [2018038045] -----]");
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
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h); // 노트 h의 할당된 메모리를 모두 해제한다.

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // headNode 사이즈 만큼 메모리를 할당해준다.
	temp->first = NULL; // first 에 Null 값을 넣어준다.
	return temp; // 할당된 메모리를 리턴해준다.
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; // 노드 h에 first 값의 주소를 리스트 노드 구조체 p에 할당해준다.

	listNode* prev = NULL; // 리스트노드 구조체 prev 를 만들어주고 초기화한다.
	while(p != NULL) { // p가 NULL 값일때까지 반복한다 즉 노드의 FIRST 와 LINK 전부 메모리 해제가 된다.
		prev = p; // 처음에 h -> first의 메모리 해제를 위해 prev 에 넣어준다.
		p = p->link; // 두번째 반복할때 link 의 메모리를 해제해야하기 된다. 첫 반복때 p에는 h-> first의 메모리를 해제 해주기때문에 p 에 link 주소를 넣어준다. 
		free(prev); // 처음은 h -> first 메모리를 해제해주고 두번째 반복할때는 link 의 메모리를 해제한다.
	}
	free(h); // headnode 의 메모리를 해제해준다.
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) { 

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 리스트노드 구조체 node 의 메모리를 할당해준다.
	node->key = key; // 노드구조체 key에는 입력받은 key 값을 넣어주고
	node->link = NULL; // node의 link 에는 NULL 값을 넣어준다.

	if (h->first == NULL) // 만약 구조체 h가 비어있다면
	{
		h->first = node; // 입력받아서 만든 node를 h->first 에 넣어준다.
		return 0;
	}

	listNode* n = h->first; // first 가 n노드를 가르키고
	listNode* trail = h->first; // first 가 trail노드를 가르킨다.

	/* key를 기준으로 삽입할 위치를 찾는다 */ // 정렬과 같다.
	while(n != NULL) { // n이 비어있을때까지 반복
		if(n->key >= key) { //입력받은 키의 값이 노드h의 처음 값보다 클경우 앞에 삽입한다. 
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //노드 처음값과 n 이 같다면
				h->first = node; // 만든 node에 주소를 first에 넣어주고
				node->link = n; // h 노드의 link를 n과 연결해준다. 그러면 입력받은 노드가 헤드노드로 바뀜.
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n; // 입력받은 노드를 뒤에 붙여준다.
				trail->link = node;
			}
			return 0;
		}

		trail = n; // 노드를 한칸 씩 이동하면서 노드를 붙일 곳을 찾는다.
		n = n->link;
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 리스트노드 구조체 node에 메모리를 할당한다.
	node->key = key; // 노드구조체 key에는 입력받은 key 값을 넣어주고
	node->link = NULL; // node의 link 에는 NULL 값을 넣어준다.

	if (h->first == NULL) // 노드 h 가 비어있다면 처음에 바로 값을 넣어준다.
	{
		h->first = node; // 노드의 주소를 노드 h 처음에 대입한다.
		return 0;
	}

	listNode* n = h->first; // h노드를 n 노드를 만들어 주소를 대입한다.
	while(n->link != NULL) { //노드가 마지막일 때까지
		n = n->link; // link 를 하나씩 움직인다.
	}
	n->link = node; // 마지막 노드에 도달하면 마지막 노드 link 가 입력받은 노드를 가르키게 한다.
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) { 

	listNode* node = (listNode*)malloc(sizeof(listNode)); //리스트노드 구조체 node에 메모리를 동적 할당한다.
	node->key = key; // 입력받은 key 값을 구조체 node key 값에 대입한다.

	node->link = h->first; // h노드의 처음 주소가 입력받은 node 의 link 를 가르키게 한다.
	h->first = node; // node의 주소를 first 에 넣어 헤드노드(처음시작노드)를 바꾼다.

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n"); // 노드가 비어있다면 오류메세지를 출력한다.
		return 0;
	}

	listNode* n = h->first; // h노드의 처음 주소를 n에 대입해준다.
	listNode* trail = NULL; // 리스트노드 구조체 trail 을 만들어 NULL 값으로 초기화한다.


	while(n != NULL)
	 {
		if(n->key == key) { // 입력받은 값과 노드에있는 값이 같을때 
			/* 첫 노드 앞쪽에 삭제해야할 경우 인지 검사 */
			if(n == h->first) { // 젤처음 노드가 삭제해야할 값이라면 
				h->first = n->link; // 다음 노드의 주소를 처음 주소에 대입해준다. 처음값을 삭제해야하므로 해주는 것.
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link; // 다음 노드의 주소를 trail 주소에 대입해준다. 삭제하고 삭제할 노드의 이전노드와 이어주어야 하기때문임. 
			}
			free(n); // 할당된 메모리를 해제시킨다.
			return 0; // 삭제하면 반복문을 빠져나간다.
		}
			//노드를 다음칸으로 움직인다.
		trail = n;
		n = n->link;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) // 노드가 비어있다면
	{
		printf("nothing to delete.\n"); // 오류메세지 출력
		return 0;
	}

	listNode* n = h->first; // h노드의 처음 주소를 n에 대입해준다.
	listNode* trail = NULL; // 리스트노드 구조체 trail 을 만들어 NULL 값으로 초기화한다.

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) // 처음 노드가 다음노드를 가르키고 있지 않다면
	 {
		h->first = NULL; // 처음 노드를 NULL 값으로 초기화 한 후
		free(n); // 메모리 할당을 해제해준다.
		return 0; // 함수를 빠져나간다.
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) { // 마지막 노드의 도달할때까지 반복한다.
		trail = n; // 노드를 한칸씩 이동한다.
		n = n->link;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL; // 마지막노드로 이동했으면 이전 노드가 현재 가르키는 위치의 노드 주소를 초기화 시켜준다.
	free(n); // 마지막 노드의 메모리 할당을 해제한다.

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) // 노드가 비어있다면 
	{
		printf("nothing to delete.\n"); // 오류메세지 출력
		return 0;
	}
	listNode* n = h->first; // 처음 노드의 주소를 가진 구조체 n 을 만들어준다

	h->first = n->link; // 다음 노드의 주소를 담고있는 링크의 값을 처음 주소에 대입해준 후
	free(n); // 가장앞에 노드 초기화 한다

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) { 


	if(h->first == NULL) { // 노드가 비어있다면 
		printf("nothing to invert...\n"); // 오류메세지 출력
		return 0;
	}
	listNode *n = h->first; // 처음 주소를 가진 구조체 n 을 선언한다.
	listNode *trail = NULL; // 이전 주소를 가진 trail 구조체를 선언 한 후 NULL 값으로 초기화 한다.
	listNode *middle = NULL; // 역순으로 만들기위해 middle 구조체를 선언 한후 NULL값으로 초기화 한다.

	while(n != NULL){ // 마지막 노드에 도달할때까지 반복한다.
		trail = middle; //taril 의 middle 을 대입해준다.
		middle = n; // 구조체 n 을 구조체 middle 에 대입해준다.
		n = n->link; // n이 그 다음 노드를 가르키게한다.
		middle->link = trail; // middle 의 다음 노드가 가르키는 것을 trail 노드로 한다.
	}
	h->first = middle; // 처음 주소가 middle 을 가르키게한다.
	return 0;
}

void printList(headNode* h) // 노드 전체를 출력하는 함수이다
 {
	int i = 0;
	listNode* p; //노드를 하나씩 출력하기위해 구조체 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) { // 노드가 비어있다면 
		printf("Nothing to print....\n"); // 오류메세지 출력
		return;
	}
	p = h->first; // 처음 주소의 값을 p 에 넣어준다
	while(p != NULL) { // 마지막 노드에 도달할때까지 반복
		printf("[ [%d]=%d ] ", i, p->key); // 노드의 인덱스와 해당 인덱스의 값 출력 
		p = p->link; // 다음 노드로 옮긴다. 
		i++; // 인덱스 값 출력하기위해 i를 1씩 더해준다.
	}

	printf("  items = %d\n", i); // 몇개의 노드를 가지고 있는지 출력해준다.
}

