#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define Alpha_Size 26

typedef struct Trie {
	struct Trie* children[Alpha_Size];		// Trie�� ���� �� �ִ� �ڽ� ����� �� = 26��(���ĺ� ����)
	int word_end;		// �ܾ �������� �Ǻ��� �� �ִ� ����
}Trie;

Trie* Get_node()
{
	Trie* node = (Trie*)malloc(sizeof(Trie));		// �����Ҵ�
	node->word_end = 0;		// word_end�� �ʱⰪ�� 0���� �������ش�.
	for (int i = 0; i < Alpha_Size - 1; i++)
	{
		node->children[i] = NULL;		// ndoe->children�� 26�� ĭ�� ��� null�� �ʱ�ȭ�Ѵ�.
	}
	return node;		// �ʱ�ȭ�� ��带 ��ȯ�Ѵ�.
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

void Search_print(int word_end)		// word_end�� �Ǻ��� ����� ������ִ� �Լ�
{
	if (word_end == 1)
		printf("�����ϴ� �ܾ��Դϴ�.\n");
	else
		printf("�������� �ʴ� �ܾ��Դϴ�.\n");
}

int nochildren(Trie* curr)		// �ڽ��� ������ 1, �ڽ��� ������ 0�� ��ȯ�ϴ� �Լ�
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
	Trie* p1 = Get_node();	// ��Ʈ��� ����

	char* arr[8] = { "bit","bite","stuff","study","student","the","them","there"};		// ������ �迭�� �ʱ� �ܾ���� �����ش�

	for (int i = 0; i < 8; i++)
	{
		Word_insert(p1, arr[i]);		// ������ �迭�� for���� �̿��� �ʱ� �ܾ���� �ѹ��� Ʈ���� Ʈ���� �����Ѵ�.
	}
	Search_print(Word_search(p1, "messi"));		// ���տ� ���Ե��� ���� �ܾ� ���
	Search_print(Word_search(p1, "ronaldo"));
	printf("\n");

	Search_print(Word_search(p1, "stuff"));		// ���տ� ���Ե� �ܾ� ���
	Search_print(Word_search(p1, "bite"));
	Search_print(Word_search(p1, "study"));
	Search_print(Word_search(p1, "them"));
	Search_print(Word_search(p1, "the"));
	printf("\n");

	Word_delete(p1, "bit", 0);		// ���� ����
	Word_delete(p1, "the", 0);
	Word_delete(p1, "there", 0);

	Search_print(Word_search(p1, "bit"));	// ������ �ܾ� ���
	Search_print(Word_search(p1, "the"));
	Search_print(Word_search(p1, "there"));
	printf("\n");

	Search_print(Word_search(p1, "bite"));	// �������� ���� �ܾ� ���
	Search_print(Word_search(p1, "study"));

}