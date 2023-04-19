#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie {
    int flag;
    struct Trie *next[26];
}Trie;

void insert(struct Trie **ppTrie, char *word)
{
    if (*ppTrie == NULL)
        return;
    
    int length = strlen(word);

    Trie *temp = *ppTrie;

    for (int i = 0; i < length; i++)
    {
        int index = word[i] - 'a';

        if (temp->next[index] == NULL)
            temp->next[index] = (Trie *)calloc(1, sizeof(Trie));

        temp = temp->next[index];
    }
    temp->flag++;
}

int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int length = strlen(word);

    Trie *temp = pTrie;

    for (int i = 0; i < length; i++)
    {
        int index = word[i] - 'a';
        temp = temp->next[index];
    }
    return temp->flag;
}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
        return pTrie;

    for (int i = 0; i < 26; i++)
    {
        if (pTrie->next[i] != NULL)
            deallocateTrie(pTrie->next[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void)
{
    Trie *trie = (Trie *)calloc(1, sizeof(Trie));

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i=0;i<5;i++)
    {
        insert(&trie, pWords[i]);
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;
}