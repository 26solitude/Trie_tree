#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define Alpha_Size 26

typedef struct Trie {
	struct Trie* children[Alpha_Size];		// Trie가 가질 수 있는 자식 노드의 수 = 26개(알파벳 숫자)
	int word_end;		// 단어가 끝나는지 판별할 수 있는 변수
}Trie;

Trie* Get_node()
{
	Trie* node = (Trie*)malloc(sizeof(Trie));		// 동적할당
	node->word_end = 0;		// word_end의 초기값을 0으로 설정해준다.
	for (int i = 0; i < Alpha_Size - 1; i++)
	{
		node->children[i] = NULL;		// ndoe->children의 26개 칸을 모두 null로 초기화한다.
	}
	return node;		// 초기화된 노드를 반환한다.
}

void Word_insert(Trie* root, char* word)
{
	Trie* curr = root;
	int i = 0;
	while (word[i])
	{
		int idx = word[i] - 'a';
		if (curr->children[idx] == NULL) {
			curr->children[idx] = Get_node();
		}
		curr = curr->children[idx];
		i++;
	}
	curr->word_end = 1;
}

int Word_search(Trie* root, char* word)
{
	if (root == NULL) return 0;
	Trie* curr = root;
	int i = 0;
	while (word[i])
	{
		int idx = word[i] - 'a';
		curr = curr->children[idx];
		if (curr == NULL) return 0;
		i++;
	}
	return curr->word_end;
}

void Search_print(int word_end)		// word_end를 판별해 결과를 출력해주는 함수
{
	if (word_end == 1)
		printf("존재하는 단어입니다.\n");
	else
		printf("존재하지 않는 단어입니다.\n");
}

int nochildren(Trie* curr)		// 자식이 있으면 1, 자식이 없으면 0을 반환하는 함수
{
	for (int i = 0; i < Alpha_Size; i++)
	{
		if (curr->children[i] != NULL) return 0;
	}
	return 1;
}

Trie* Word_delete(Trie* curr, char* word, int depth)
{
	if (curr == NULL) return NULL;
	if (depth == strlen(word)) {
		if (curr->word_end == 1) curr->word_end = 0;
		if (nochildren(curr) == 1) {
			free(curr);
			curr = NULL;
		}
		return curr;
	}
	int idx = word[depth] - 'a';
	curr->children[idx] = Word_delete(curr->children[idx], word, depth + 1);
	if (nochildren(curr) == 1 && curr->word_end == 0)
	{
		free(curr);
		curr = NULL;
	}
	return curr;
}


void main()
{
	Trie* p1 = Get_node();	// 루트노드 생성

	char* arr[8] = { "bit","bite","stuff","study","student","the","them","there"};		// 포인터 배열로 초기 단어들을 묶어준다

	for (int i = 0; i < 8; i++)
	{
		Word_insert(p1, arr[i]);		// 포인터 배열과 for문을 이용해 초기 단어들을 한번에 트라이 트리를 구성한다.
	}
	Search_print(Word_search(p1, "messi"));		// 집합에 포함되지 않은 단어 출력
	Search_print(Word_search(p1, "ronaldo"));
	printf("\n");

	Search_print(Word_search(p1, "stuff"));		// 집합에 포함된 단어 출력
	Search_print(Word_search(p1, "bite"));
	Search_print(Word_search(p1, "study"));
	Search_print(Word_search(p1, "them"));
	Search_print(Word_search(p1, "the"));
	printf("\n");

	Word_delete(p1, "bit", 0);		// 삭제 수행
	Word_delete(p1, "the", 0);
	Word_delete(p1, "there", 0);

	Search_print(Word_search(p1, "bit"));	// 삭제된 단어 출력
	Search_print(Word_search(p1, "the"));
	Search_print(Word_search(p1, "there"));
	printf("\n");

	Search_print(Word_search(p1, "bite"));	// 삭제되지 않은 단어 출력
	Search_print(Word_search(p1, "study"));

}