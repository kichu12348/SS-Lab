

#include<stdio.h>
#include<string.h>

void main(){
    FILE *obj=fopen("objectCode.txt","r");

    char recordType;
    char name[10];
    int strAddr,progLen,newAdr;

    printf("enter new Addr: ");
    scanf("%x",&newAdr);

    int diff=newAdr-strAddr;

    fscanf(obj,"%c^%[^'^']%x^%x\n",&recordType,name,&strAddr,&progLen);

    printf("program: %s\n starting addr: %04X\nprogram length: %04X\nnew start: %04X\n",name,strAddr,progLen,newAdr);

    int currAdr,textLen;
    char textData[500];

    while(fscanf(obj,"%c",&recordType)!= EOF){
        if(recordType=='T'){
            fscanf(obj,"^%x^%x^%s\n",&currAdr,&textLen,textData);
            currAdr+=diff;
            printf("Text Record Starts at: %04X\n Length: %02X\n",currAdr,textLen);

            for(int i=0;i<strlen(textData);i+=2){
                char byteStr[3];
                strncpy(byteStr,&textData[i],2);
                byteStr[2]='\0';
                printf("%04X\t%s\n",currAdr,byteStr);
                currAdr++;
            }
            printf("\n");
        }
        else if(recordType=='E'){
            int execAddr;
            fscanf(obj,"^%x\n",&execAddr);
            execAddr+=diff;
            printf("Program Execution starts at: %04X\n",execAddr);
            break;
        }
    }
    fclose(obj);
}