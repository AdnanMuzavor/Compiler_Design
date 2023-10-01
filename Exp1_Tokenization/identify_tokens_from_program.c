#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<ctype.h>

int is_Keyword(char buffer[]) {
  char keywords[33][10] = {
    "auto","break","case","char","const","continue","default",
"do","double","else","enum","extern","float","for","goto",
"if","int","long","register","return","short","signed",
"sizeof","static","struct","switch","typedef","union",
"unsigned","void","volatile","while","printf"};
  int i, flag = 0;
  for (i = 0; i < 33; i++) {
    if (strcmp(keywords[i], buffer) == 0) {
      return 1;
    }
  }
  return 0;
}

int is_Delimitor(char ch){
    return (ch == ' ' || ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}');
}

int is_Operator(char ch){
    return (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='=');
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
        //If it's include statement we can skip the token as handled below
        int is_preprocessor=0;
        for(int i=0;i<strlen(token);i++){
            //Look for preprocessor
            int j=0;
            if(i==0 && token[i]=='#'){
                
                //Get the token=preprocessor directive
                char buffer1[10];
                while(i<=strlen(token) && token[i]!='<'){
                    buffer1[j++]=token[i++];
                }
                buffer1[j]='\0';
                printf(" preprocessor directive , %s \n", buffer1);
                
                //Get the token=preprocessor directive parameter
                char buffer2[10];
                j=0;
                while(i<=strlen(token) && token[i]!='>'){
                    buffer2[j++]=token[i++];
                }
                buffer2[j]='>';
                buffer2[j+1]='\0';
                printf(" preprocessor directive parameter , %s \n", buffer2);
                
                //Mark this line as preprocessor to avoid further classification
                is_preprocessor=1;
                
                break;
            }
            

        }
        if(is_preprocessor==1 ){ 
             //Move to next token && check it's not null
             token = strtok(NULL, " ");
             continue;
            
        }
   

        if(is_Delimitor(token[0])){
            printf(" delimiter , %s \n", token);
        }
        else if(is_Operator(token[0])){
            printf(" operator , %s \n", token);
        }
        else if(is_Number(token)){
            printf(" literal , %s \n", token);
        }
        else {
            if(is_Keyword(token)){
                 printf(" keyword, %s \n", token);
            }
            else{
                 printf(" identifier, %s \n", token);
            }
        }
        token = strtok(NULL, " ");
    }
}

int main() {


    char buffer[100];
    FILE *fp;
    
    fp = fopen("hello.c", "r");
    if (fp == NULL) {
        printf("Error while opening the file\n");
        exit(1); // Exit with an error code
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {

        Process_Expression(buffer);
    }

    fclose(fp);
}