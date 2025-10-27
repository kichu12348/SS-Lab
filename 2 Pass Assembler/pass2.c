
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

void main(){
    FILE *intrFile,*opTab,*symTab,*obj,*listing;

    intrFile=fopen("intFile.txt","r");
    obj=fopen("objectCode.txt","w");
    listing=fopen("listing.txt","w");


    char label[10],opcode[10],operand[10],progName[10];
    int address,startingAdr=0,progLength=12;

    fscanf(intrFile,"%X %s %s %s",&address,label,opcode,operand);

    if(strcmp(opcode,"START")==0){
        startingAdr=(int)strtol(operand,NULL,16);
        strcpy(progName,label);
        fprintf(obj,"H^%s^%06X\n",progName,startingAdr);
        fprintf(listing,"%X\t%s\t%s\t%s\n",address,label,opcode,operand);
        fscanf(intrFile,"%X %s %s %s",&address,label,opcode,operand);
    }

    char textRecord[500]="";
    int textAdrr=address,textLen=0;

    while(strcmp(opcode,"END")!=0){
        char objCode[20]="";

        opTab=fopen("optab.txt","r");
        char op[10],code[10];
        int found=0;
        while(fscanf(opTab,"%s %s",op,code)!=EOF){
            if(strcmp(op,opcode)==0){
                symTab=fopen("symtab.txt","r");
                char sym[10];
                int addr;

                while(fscanf(symTab,"%s %X",sym,&addr)!=EOF){
                    if(strcmp(sym,operand)==0){
                        sprintf(objCode,"%s%04X",code,addr);
                        break;
                    }
                }
                fclose(symTab);
                if(strlen(objCode)==0){
                    sprintf(objCode,"%s0000",code);
                }
                found=1;
                break;
            }
        }
        fclose(opTab);

        if(strcmp(opcode,"WORD")==0){
            sprintf(objCode,"%06X",atoi(operand));
        }
        else if(strcmp(opcode,"BYTE")==0){
            if(operand[0]=='C'){
                char tmp[20]="";
                for(int i=2;i<strlen(operand)-1;i++){
                    char hex[3];
                    sprintf(hex,"%02X",operand[i]);
                    strcat(tmp,hex);
                }
                strcpy(objCode,tmp);
            }
            else if(operand[0]=='X'){
                strncpy(objCode,operand+2,strlen(operand)-3);
                objCode[strlen(operand)-3]='\0';
            }
        }


        if(strlen(objCode)>0){
            if(textLen+strlen(objCode)/2>30){
                fprintf(obj,"T^%06X^%02X^%s\n",textAdrr,textLen,textRecord);
                strcpy(textRecord,"");
                textLen=0;
                textAdrr=address;
            }
            strcat(textRecord,objCode);
            textLen+=strlen(objCode)/2;
        }

        fprintf(listing,"%X\t%s\t%s\t%s\n",address,label,opcode,operand);
        fscanf(intrFile,"%X %s %s %s",&address,label,opcode,operand);
    }

    if(strlen(textRecord)>0){
            fprintf(obj,"T^%06X^%02X^%s\n",textAdrr,textLen,textRecord);
    }

    fprintf(obj,"E^%06X\n",startingAdr);
    fprintf(listing,"%X\t%s\t%s\t%s\n",address,label,opcode,operand);

    fclose(intrFile);
    fclose(obj);
    fclose(listing);
}