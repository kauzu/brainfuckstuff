#include <string.h>
#include <stdio.h>
#define WORLD_SIZE 0xffff

/*
int validBF(char* code){
    char *stack = malloc(strlen(code));
    int size = strlen(code);
    int pos = 0;
    while(pos < size){
    	switch(code[pos]){
    	    case '[': strcat(stack, code[pos]);
                      break;
    	    case ']': strlen(stack)>0?stack[strlen(stack)-1]=(char)0x00:"";
                      break;
        }
    } 
    if(strlen(stack)==0){
        return 1;
    }
    return 0;
}
*/


void main(int argc, const char* argv[]){
    if(argc < 2 || argc > 999 ) {
	    printf("please give some code\n");
    }
	FILE *fp;
    fp = fopen(argv[1], "r"); // read mode
    if (fp == NULL)
    {
      perror("Error while opening the file\n");
      return 0;
    }

    char* code = NULL;
    long length;    
    if (fp)
    {
      fseek (fp, 0, SEEK_END);
      length = ftell (fp);
      fseek (fp, 0, SEEK_SET);
      code = malloc (length);
      if (code)
      {
        fread (code, 1, length, fp);
      }
      fclose (fp);
    }

    if(code == NULL){
       return 0;
    }
    /*if(validBF(code)==1){printf("Thats not Brainfuck\n");return 1;}*/
    int ppos = 0;
    int mpos = 0;
    char memory[WORLD_SIZE];
    memset(memory, 0x0, sizeof(char)*WORLD_SIZE);
    while(code[ppos] != '\0'){
        switch(code[ppos]){
            case '+':memory[mpos]++; break;
            case '-':memory[mpos]--; break;
            case '<':mpos==0?mpos=WORLD_SIZE:mpos--;break;
            case '>':mpos==WORLD_SIZE?mpos=0:mpos++;break;
            case '.':printf("%c",memory[mpos]);break;
            case ',':memory[mpos] = getchar();break;
            case '[':
            {
                if(memory[mpos] == 0x00){
                    int open = 1;
                    while(open){
			            if(ppos == strlen(code)){/*printf("FAIL");*/return 1;}//also no bf
                        ppos++;
                        if(code[ppos] == '['){open++;}
                        if(code[ppos] == ']'){open--;}
                    }
                }    
            } 
            break;
            case ']':
            {
                if(memory[mpos] != 0x00){
                    int closings = 1;
                    while(closings){
			            if(ppos==0){/*printf("FAIL");*/return 1;} //yeah thats no valid bf
                        ppos--;
                        if(code[ppos] == '['){closings--;}
                        if(code[ppos] == ']'){closings++;}
                    }
                }
            } 
            break;
        }
        ppos++;
    }
printf("\n");
}
