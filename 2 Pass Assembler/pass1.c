#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct SymtabEntry{
    char label[10];
    int address;
};

struct SymtabEntry SYMTAB[50];
int symtabIndex=0;


int searchOpTab(char val[]){
    FILE *optab;
    optab = fopen("optab.txt","r");
    char opcode[10],addr[10];
    int found=0;
    while(fscanf(optab,"%s %s",opcode,addr)!=EOF)
        if(strcmp(opcode,val)==0) found=1;
    fclose(optab);    
    return found;
}

void main(){

    FILE *inputFile,*intFile,*symTab;

    char label[10],opcode[10],operand[10];

    int startingAddr,locctr;

    inputFile = fopen("input.txt","r");
    intFile = fopen("intFile.txt","w");
    symTab = fopen("symtab.txt","w");

    fscanf(inputFile,"%s %s %s",label,opcode,operand);

    if(strcmp(opcode,"START")==0){
        startingAddr=locctr=(int)strtol(operand,NULL,16);
        fprintf(intFile,"%X\t%s\t%s\t%s\n",startingAddr,label,opcode,operand);
        fscanf(inputFile,"%s %s %s",label,opcode,operand);
    }

    while(strcmp(opcode,"END")!=0){ // while not END

        fprintf(intFile,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand);

        if (strcmp(label,"**")!=0){ // check if label is present
            strcpy(SYMTAB[symtabIndex].label,label);
            SYMTAB[symtabIndex].address=locctr;
            symtabIndex++;
        }

        if(searchOpTab(opcode))
            locctr+=3;
        
        else if(strcmp(opcode,"WORD")==0)
            locctr+=3;
        
        else if(strcmp(opcode,"RESW")==0)
            locctr+=(3*atoi(operand));
        
        else if(strcmp(opcode,"RESB")==0)
            locctr+=atoi(operand);

        else if(strcmp(opcode,"BYTE")==0){
            if(operand[0]=='C'){
                locctr+=strlen(operand)-3;
            }
            else if(operand[0]=='X'){
                locctr+=(strlen(operand)-3)/2;
            }
        }
            
        

        fscanf(inputFile,"%s %s %s",label,opcode,operand);
    }

    fprintf(intFile,"\t\t%s\t%s\t%s\n",label,opcode,operand);

    
    

    for(int i=0;i<symtabIndex;i++){
        fprintf(symTab,"%s\t%X\n",SYMTAB[i].label,SYMTAB[i].address);
    }

    printf("Program Length: %X\n",(locctr-startingAddr));

    fclose(intFile);
    fclose(symTab);
    fclose(inputFile);
    return;
}