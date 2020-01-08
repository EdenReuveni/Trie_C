#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define NUM_LETTERS 26
#define CONVERT 97

typedef struct node {
char letter;
long unsigned int count;
struct node* children[NUM_LETTERS];
bool isEndOfWord;

} node;

node* root = NULL;

void create(node** add,char c){
 node* t = (node*)malloc(sizeof(node));

for(int i=0;i<NUM_LETTERS;i++){//initalized first 26 sons 
    t->children[i] = NULL;
}
t->letter = c;
t->count = 1;
t->isEndOfWord = false;
(*add) = t;

}

void add_to_trie(node** root,char* str){//maybe chenge to boolean
   	int level; 
    int length = strlen(str); 
    int index; 
	node* trienode = (*root);
        //aab
	 for (level = 0; level < length; level++) 
    {
		if(trienode->children[*(str+level)-CONVERT]==NULL){ 
			create(&(trienode->children[*(str+level)-CONVERT]),*(str+level));
		}
        else{
            trienode->children[*(str+level)-CONVERT]->count++;
        }
		trienode = trienode->children[*(str+level)-CONVERT];

	}
    
	trienode->isEndOfWord = true;
    return;
}

bool search(node** root,char* str){

    int level; 
    int length = strlen(str); 
    int index; 
	node* trienode = (*root);
	 for (level = 0; level < length; level++) 
    { 
		if (!trienode->children[*(str+level)-CONVERT]) 
            return false; 
		trienode = trienode->children[*(str+level)-CONVERT];

	}
	//aab
	return (trienode !=NULL && trienode->isEndOfWord);
}

void postorder(node* root,char* hold,int s){
    int i=0;
    if(root==NULL){
        return;
    }
    if(root->isEndOfWord == true){
        hold[s]=0;
        printf("%s %d\n",hold,root->count);
    }
      for(i = 25; i >= 0; i--){
           hold[s] = 'a'+i;
           hold = (char*)realloc(hold,((s+2)*sizeof(char)));
           postorder(root->children[i], hold, s + 1);
 }
}


int main(){

 char* str4 = "ab";
 char* str2 = "ab";
 char* str3 = "bbcd";
 char* str5 = "basaddsbasdasdasdsadasdasdasdasdsadsadsadsadsadcd";
 char* str22="zjjks";
  char* str21="nsnsjkjjs";
    char* str20="nsnsjkjjs";


 char* hold;
 hold = (char *)malloc(sizeof(char));

    node* root = (node*)malloc(sizeof(node));//first element(root)
    root->letter= ' ';
    root->count = 0;
    root->isEndOfWord = false;

for(int i=0;i<NUM_LETTERS;i++){//initalized first 26 sons 
    root->children[i] =NULL;
}

add_to_trie(&root,str4);
add_to_trie(&root,str2);
add_to_trie(&root,str3);
add_to_trie(&root,str5);
add_to_trie(&root,str20);
add_to_trie(&root,str21);
add_to_trie(&root,str22);


//preorder(root,hold,0);
free(hold);

//printf("The word %s is found  : %d", str3,search(&root,str3));




    return 0;

}
