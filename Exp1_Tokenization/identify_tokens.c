#include<stdio.h>
#include<string.h>

int is_Delimitor(char ch){
    return (ch == ' ' || ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}');
}

int is_Operator(char ch){
    return (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='=');
}

int is_Keyword(char* token){
    char * keywords[]= {"int", "float", "char", "if", "else", "while", "for"};
    for(int i=0;i<7;i++){
        if(strcmp(token,keywords[i])==0) return 1;
    }
    return 0;
}

int is_Number(char *token){
    //printf("\nprocessing : %s",token);
    for(int i=0;i<strlen(token);i++){
        if(!(token[i]>='0' && token[i]<='9')) return 0;
    }
    return 1;
}

void Process_Expression(char *str){
    char* token=strtok(str," "); //get token
    while(token!=NULL){
        
        if(is_Delimitor(token[0])){
            printf("( delimiter , %s )\n", token);
        }
        else if(is_Operator(token[0])){
            printf("( operator , %s )\n", token);
        }
        else if(is_Number(token)){
            printf("( literal , %s )\n", token);
        }
        else {
            if(is_Keyword(token)){
                 printf("( keyword, %s )\n", token);
            }
            else{
                 printf("( identifier, %s )\n", token);
            }
        }
        //Move to next token
         token = strtok(NULL, " ");
    }
}
int main(){
  char str[100];
  printf("Enter a C expression: ");
  fgets(str,sizeof(str),stdin);
  printf("Tokenization of %s \n",str);
  Process_Expression(str);
}