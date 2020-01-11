#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NUM_LETTERS 26
#define CONVERT 97


//Trie node struct
typedef struct node {
char letter;
long unsigned int count;
struct node* children[NUM_LETTERS];
bool isEndOfWord;

} node;

//Initailize the first trie node to be null
node* root = NULL;

//Constructor for TRIE nodes
void create(node** add,char c){
 node* t = (node*)malloc(sizeof(node));

for(int i=0;i<NUM_LETTERS;i++){//Initalized first 26 sons to be null 
    t->children[i] = NULL;
}
t->letter = c;
t->count = 1;
t->isEndOfWord = false;
(*add) = t;

}

void add_to_trie(node** root,char* str){//This function adds the node we got to the TRIE 
    int level; 
    int length = strlen(str); 
	node* trienode = (*root);
	 for (level = 0; level < length; level++) 
    	 {        
                if(*(str+level)>='a'  && *(str+level)<='z'){//Check to see that the word is small letter
		if(trienode->children[*(str+level)-CONVERT]==NULL){ 
			create(&(trienode->children[*(str+level)-CONVERT]),*(str+level));//If none exsist create the node
		}
        else{
            trienode->children[*(str+level)-CONVERT]->count++;//If does exsist make the counter grow in 1
        }
		trienode = trienode->children[*(str+level)-CONVERT];
}

	}
    
	trienode->isEndOfWord = true;  //End of word
    return;
}

void free_trie(node* root){//This function frees the tree by recursive call to each node
    for(int i=0;i<NUM_LETTERS;i++){
        if(root->children[i]!=NULL){
            free_trie(root->children[i]);
        }
    }
    free(root);
}

void to_lower_case(char* str){//Converts upper case letters to lower case ones
    int len = strlen(str);
    for(int i=0;i<len;i++){
        if(str[i]>='A' && str[i]<='Z'){
            str[i] = tolower(str[i]);
        }
    }

}


void preorder(node* root,char* hold,int s){//Printing the words of the TRIE in by increasing lexicorgpic order
    int i=0;
    if(root==NULL){
        return;
    }
    if(root->isEndOfWord == true){
        hold[s]=0;
        printf("%s %ld\n",hold,root->count);//End of the word if does print it and his appearance 
    }
      for(i = 0; i < 26; i++){
           hold[s] = 'a'+i;
           preorder(root->children[i], hold, s + 1);
 }
}

void postorder(node* root,char* hold,int s){//Printing the words of the TRIE in by decreasing lexicorgpic order
    int i=0;
    if(root==NULL){
        return;
    }
    if(root->isEndOfWord == true){
        hold[s]=0;
        printf("%s %ld\n",hold,root->count);//End of the word if does print it and his appearance 
    }
      for(i = 25; i >= 0; i--){
           hold[s] = 'a'+i;
           postorder(root->children[i], hold, s + 1);
 }
}


int main(int argc,char *argv[]){


 char* hold;
 hold = (char *)malloc(sizeof(char));

    node* root = (node*)malloc(sizeof(node));//First element(root)
    root->letter= ' ';
    root->count = 0;
    root->isEndOfWord = false;

for(int i=0;i<NUM_LETTERS;i++){//Initalized first 26 sons 
    root->children[i] =NULL;
}

int i=0;
char* add =(char *)malloc(sizeof(char));//Allocate new memory to the strings that will join the tree
char buffer=getchar();//Get argument from stdin
*(add+i) = buffer;
while(buffer!=-1){//If not end of word then keep getting words from the user

    while( buffer !=' ' && buffer!='\n' && buffer!=-1 ){
    buffer=getchar();
    i++;
    *(add+i) = buffer;
    add = (char*)realloc(add,(i+1)*sizeof(char));
}
*(add+i+1)=0;

to_lower_case(add);
add_to_trie(&root,add);
free(add);//Freeing our allocation
i=0;
add =(char *)malloc(sizeof(char));
buffer=getchar();
if(buffer==-1){//If we get the end of the file then we break the loop
    break;
}
*(add+i) = buffer;
}

free(add);//freeing the string varible

if(argc==1){//if ./frequancy that preorder
preorder(root,hold,0);
}
else if(argv[1][0]=='r'){//else postorder
    postorder(root,hold,0);
}
free(hold);//freeing the allocation we made for hold
free_trie(root);//freeing the TRIE


    return 0;

}