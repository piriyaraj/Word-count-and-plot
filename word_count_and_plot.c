#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*
    programme for count the word and character in the file or files and print the percentage graph
*/
//==========================for character
typedef struct _{          //structure for character store
    char letter;
    int no_letter;

    struct _ *next;
} counterc;
counterc *headc,*currentc,*currentsc=NULL,*headsc=NULL;

int del_c();                // delete character from structure
int sort_c();               // sort the character in structure according to char count
int countc();               // count the char counts
int find_newc();            // check a char is new for structure
int outputc();              // print the output chart in terminal

//==========================for word
typedef struct __{          // structure for word store
    char letter[100];
    int no_letter;

    struct __ *next;
} counterw;

counterw *headw,*currentw,*currentsw=NULL,*headsw=NULL;

int del_w();                // delete a word from the structure
int sort_w();               // sort the words according to the word counts
int countw();               // count the words counts
int find_neww();            // check a word is new for structure
int outputw();              // print the output chart in terminal

//=================================
int wordc=0,charc=0,len=10,active=0,maxwlen=0;
int change();               // function for change to alphanumeric
char *type="-w";
char ch1[1000],line[1000];
int main(int argc,char **argv){
    char *typec,*typew,*te,*te1,s[2]=".",file[30],*occ;
    occ=NULL;
    FILE *pfile;
    headc=NULL;
    currentc=NULL;
    headw=NULL;
    currentw=NULL;
    if(argc<2){                        // programme run without argument print error
        printf("No input files were given\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
        return 0;
    }

    for(int k=0;k<argc;k++){           // loop for find wrong flag and print the error message
            if(!strcmp("-l",argv[k])){

                if(argv[k+1]==NULL){       // have -l flag without value then print the error
                    printf("Not enough options for [-l]\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                    return 0;
                }
                int p=0;
                if(argv[k+1][p]=='-'){
                    p++;
                }
                if(argv[k+1][p]-48>=0&&argv[k+1][p]-48<=9){   // there are any number after the -l flag

                    len=0;

                    for(int m=p;m<strlen(argv[k+1]);m++){
                        int t=1;
                        if(!(argv[k+1][m]-48>=0&&argv[k+1][m]-48<=9)){
                            printf("Invalid options for [-l]\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);   // have -l flag without value then print the error
                            return 0;
                        }

                        for(int n=0;n<strlen(argv[k+1])-1-m;n++){
                            t*=10;
                        }
                        len=len+(argv[k+1][m]-48)*t;              // assign the length form argument
                    }
                    if(len==0){
                        return 0;
                    }
                    if(len>0&&p==1){
                        printf("Invalid option(negative) for [-l]\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                        return 0;
                    }
                }

                else{
                    printf("Invalid options for [-l]\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);   // have -l flag without value then print the error
                    return 0;
                }


        }
        if(argv[k][0]=='-'){

            if(!(!strcmp(argv[k],"-c")||!strcmp(argv[k],"-w")||!strcmp(argv[k],"-l")||!strcmp(argv[k],"--scaled"))){
                printf("Invalid option [%s]\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[k],argv[0]); // print error when wrong flag enterd
                return 0;
            }
        }
    }
    for(int k=0;k<argc;k++){

        if(!strcmp("-c",argv[k])){        // if argument is -c then assign some value
            type="-c";
            typec="-c";
        }
        if(!strcmp("-w",argv[k])){        // if argument is -w then assign some value

            typew="-w";
        }
        if(typec=="-c"&&typew=="-w"){     // if have both -c and -w print the error message
            printf("[-c] and [-w] cannot use together\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
            return 0;
        }
        if(!strcmp("--scaled",argv[k])){   // check there are scaled argument
            active=1;
        }




    }
    for(int k=0;k<argc;k++){                                 // loop for read files and count the word or characters
        if(argv[k][0]=='-'){
            if((!strcmp(argv[k],"-c")||!strcmp(argv[k],"-w")||!strcmp(argv[k],"-l")||!strcmp(argv[k],"--scaled"))){   // ignore the flags
                continue;
            }
        }
        if(k==0||!strcmp("-l",argv[k-1])){   // ignore the first and -l flag and value
            continue;
        }
        strcpy(file,argv[k]);                // copy the text file name
        te=strtok(file,s);                   // split the file name using "."
        te=strtok(NULL, s);                  // get file extention

        if(te!=NULL){                        // check the extention is not null
            occ=te;               // check any file name are found or not


            pfile=fopen(argv[k],"r");         // open the file
            if(pfile==NULL){                  // check the file occur
                printf("Cannot open one or more given files\n");
                return 0;
            }
            else{

                if(!(strcmp(type,"-c"))){        // if the flag is -c then find the count
                    while (fgets(line, sizeof(line), pfile)) {     // read the file line by line

                        if(!(strcmp(line,"\n"))){                  // there is empty line then continue the loop
                            continue;
                        }

                        change(line,ch1);                          // change line to alphanumeric and assign to ch1 array
                        countc(ch1);                               // count the each character  in the line
                    }
                    if(charc==0){                                  // when file is empty then print the message
                        printf("No data to process\n");
                        return 0;
                    }
                }
                else{                                              // the flag is -w
                    while (fgets(line, sizeof(line), pfile)) {     // read the file line by line

                        if(!(strcmp(line,"\n"))){                  // there is empty line then continue the loop
                            continue;
                        }

                        change(line,ch1);                          // change line to alphanumeric and assign to ch1 array

                        countw(ch1);                               // count the each words in line

                }
                    if(wordc==0){                                  // when file is empty then print the message
                        printf("No data to process\n");
                        return 0;
                    }
                }

            }
            fclose(pfile);                                        // close the open file

        }
        else{                                                     // when the file is not appear in folder
            printf("Cannot open one or more given files\n");
            return 0;
        }
    }
    if(occ==NULL){                                                // programme run without txt file
        printf("No input files were given\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
        return 0;
    }
    if(!strcmp(type,"-c")){                                       // if flag is -c print the output
        sort_c();                                                 // sort the character
        outputc();                                                // print the graph in terminal
    }
    else {                                                        // if flag is -w print the output
        sort_w();                                                 // sort the words
        outputw();                                                // print the graph in terminal
    }



    return 0;
}

//================================for char
int countc(char *ch1){                                            // count the character in a sentence

    counterc *new1;
    for(int k=0;ch1[k]!='\0';k++){                                // loop for get all character
        if(ch1[k]==' '){                                          // ignore the spaces
            continue;
        }
        charc++;                                                  // find the character count
        new1=(counterc*)malloc(sizeof(counterc));                 // allocate memory
        if(find_newc(ch1[k])){                                    // check is it a new character
            new1->letter=ch1[k];                                  // assign the new char in stuture
            new1->no_letter=1;                                    // start a count for new char
            new1->next=NULL;
            if(headc==NULL){
                headc=new1;                                       // if it is first char

            }
            else{

                currentc->next=new1;                              // if it isnt first char

            }
            currentc=new1;                                        // assign the last char to count
        }

    }
    return 0;
}
int find_newc(int ch3){                                           // check the char is new or not
    counterc *cn;
    cn=headc;

    while(cn!=NULL){                                              // check the char is occur in the structure
        if(cn->letter==ch3){
            cn->no_letter++;                                      // if occur the char in structure then increase the count
            return 0;
        }
        cn=cn->next;                                              // switch to next memory
    }
    return 1;
}
int del_c(counterc *todel){                                       // delete the date after store new structure

    counterc *check,*tem;

    tem=NULL;
    check=headc;
    if(headc==NULL){                                              // stop the function when the all date delete

        return 0;
    }
    while(check!=todel){                                          // loop while find the want to delete data

        tem=check;
        check=check->next;
        if(check==NULL){                                          // stop after loop all data with out find
            break;
        }
    }

        if(check!=NULL){                                          // if date was found

            if(tem!=NULL){
                tem->next=check->next;                            // ignore the date
            }
            else{
                headc=check->next;                                // ignore the head data
            }

            check=NULL;

            return 0;
        }


    return 0;
}
int sort_c(){                                                     // sort the character according to count
    counterc *new2,*che,*che1;
    int max;
    new2=headc;

    che=(counterc*)malloc(sizeof(counterc));
    che1=(counterc*)malloc(sizeof(counterc));

    for(int k=0;k<len;k++){                                        // add to new data according to user input or default
        new2=headc;
        max=0;
        if(new2==NULL){                                            // if head is null then stop the process
            break;
        }
        while(new2!=NULL){                                         // loop for find the max count letter

            if(new2->no_letter>max){                               // find the max value count
                max=new2->no_letter;
                che=new2;                                          // store  the max count data to che
                che1=new2;

            }
            new2=new2->next;
        }

        if(headsc==NULL){                                         // add the max data to new structure
            headsc=che;

        }
        else{
            currentsc->next=che;                                  // add other dates
        }
        currentsc=che;
        del_c(che1);                                              // delete date after add to new structure

    }
    currentsc->next=NULL;
    return 0;
}
int outputc(){                                                    // print the output in the terminal
    counterc *temp1;
    temp1=headsc;
   /* for(int p=0;p<80;p++){
        printf(" ");
    }
    */
    printf("\n");
    while(temp1!=NULL){                                           // loop while the structure is empty
        int t=((temp1->no_letter/(float)charc)*70);
        if(active==1){                                            // if the scaled flag is occur
            float x=(temp1->no_letter);
            float y=(headsc->no_letter);
            t=(x/y)*70;                                           // scaled length of the line
        }

        if(temp1->no_letter==charc){                              // if only one letter in the file
            t=t-1;
        }
        for(int l=0;l<4;l++){                                     // loop for the output of the every char
            if(l==0){                                             // this is for first line
                printf("   ");
                printf("\u2502");

                for(int m=0;m<t;m++){                             // print the pattern
                    printf("\u2591");
                }

                printf("\n");
            }
            else if(l==1){                                        // this for 2nd line
                printf(" %c ",temp1->letter);                     // print the char
                printf("\u2502");                                 // vertical line

                for(int m=0;m<t;m++){                             // print the pattern
                    printf("\u2591");
                }
                printf("%.2f%%\n",(temp1->no_letter/(float)charc)*100);   // print the percentage value
            }
            else if(l==2){                                        // for 3rd line
                printf("   ");
                printf("\u2502");

                for(int m=0;m<t;m++){                             // print the pattern
                    printf("\u2591");
                }

                printf("\n");
            }
            else{                                                 // for 4th line
                printf("   ");
                printf("\u2502");                                 // print the vertical line
              /*  for(int p=0;p<76;p++){
                    printf(" ");
                }
             */
                printf("\n");
                break;
            }
        }
        temp1=temp1->next;
    }
    printf("   \u2514");                                          // print the conner symbol
    for(int k=0;k<76;k++){                                        // print the horizontal line
        printf("\u2500");
    }
    printf("\n");
    return 0;

}

//================================for word
int countw(char *ch1){                                            // count the word
    const char s[2] = " ";
    char *token;
    counterw *new1;
    token = strtok(ch1, s);
    while(token!= NULL ) {                                        // loop while the all word pass
        wordc++;

        if(find_neww(token)){                                     // check its a new word
            new1=(counterw*)malloc(sizeof(counterw));             // allocate the memory

            strcpy(new1->letter,token);                           // copy the new word

            new1->no_letter=1;                                    // start the count
            new1->next=NULL;
            if(headw==NULL){
                headw=new1;                                       // add new word in head

            }
            else{
                currentw->next=new1;                              // add the words

            }
            currentw=new1;                                        // assign new word to current
        }

        token = strtok(NULL, s);                                  // change the next word

    }
    return 0;
}
int find_neww(char *ch3){                                         // check the word new or not

    counterw *cn;
    cn=headw;

    while(cn!=NULL){                                              // loop all date in structure
        if(!strcmp(cn->letter,ch3)){                              // check the same word or not
            cn->no_letter++;                                      // if same increase the count
            return 0;
        }
        cn=cn->next;
    }
    return 1;                                                     // if match return 1;
}
int del_w(counterw *todel){                                       // delete the sorted data

    counterw *check,*tem;

    tem=NULL;
    check=headw;
    if(headw==NULL){

        return 0;
    }
    while(check!=todel){                                          // loop while the word is same

        tem=check;
        check=check->next;
        if(check==NULL){                                          // break after all date checked
            break;
        }
    }

        if(check!=NULL){                                          // if the word found

            if(tem!=NULL){
                tem->next=check->next;                            // ignore head the word when the sent word is head
            }
            else{
                headw=check->next;                                // ignore the word
            }

            check=NULL;

            return 0;
        }


    return 0;
}
int sort_w(){                                                     // function for the sort the word according to count
    counterw *new2,*che,*che1;
    int max;
    new2=headw;

    che=(counterw*)malloc(sizeof(counterw));
    che1=(counterw*)malloc(sizeof(counterw));

    for(int k=0;k<len;k++){                                       // sort the value given length
        new2=headw;
        max=0;
        if(new2==NULL){                                           // break if the head is null
            break;
        }
        while(new2!=NULL){                                        // loop while the date is null

            if(new2->no_letter>max){                              // find the max count
                max=new2->no_letter;
                che=new2;
                che1=new2;

            }
            new2=new2->next;
        }
        if(maxwlen<strlen(che1->letter)){                         // check the max word length
            maxwlen=strlen(che1->letter);
        }

        if(headsw==NULL){                                         // add max count in new head
            headsw=che;

        }
        else{
            currentsw->next=che;                                  // add the sored value in the structure
        }
        currentsw=che;
        del_w(che1);                                              // delete after sorted

    }
    currentsw->next=NULL;
    return 0;
}
int outputw(){                                                    // function for print the graph in terminal
    counterw *temp2;
    temp2=headsw;
   /* for(int p=0;p<80;p++){
        printf(" ");
    }
    */
    printf("\n");
    while(temp2!=NULL){
        int t=((temp2->no_letter/(float)wordc)*(72-maxwlen));    // find the length of the line
        if(active==1){

            t=((float)temp2->no_letter/headsw->no_letter)*(72-maxwlen);     // find the scaled length line
        }
        if(temp2->no_letter==wordc){                                        // if file have only one word
            t=t-1;
        }

        for(int l=0;l<4;l++){                                   // each word line output

            if(l==0){                                           // for 1st line
                for(int p=0;p<maxwlen-1;p++){
                    printf(" ");                                // print the space before vertical line
                }
                printf("   ");
                printf("\u2502");                               // print the vertical line


                for(int m=0;m<t;m++){                           // print the pattern
                    printf("\u2591");
                }

                printf("\n");
            }
            else if(l==1){                                      // for 2nd line
                printf(" %s ",temp2->letter);                   // print the word
                for(int p=0;p<maxwlen-strlen(temp2->letter);p++){   // print the space
                    printf(" ");
                }
                printf("\u2502");                               // print the vertical line

                for(int p=0;p<t;p++){
                    printf("\u2591");                           // print the pattern
                }
                printf("%.2f%%\n",(temp2->no_letter/(float)wordc)*100);   // print the percentage
            }
            else if(l==2){                                      // for 3rd line
                for(int p=0;p<maxwlen-1;p++){
                    printf(" ");                                // print the space before vertical line
                }
                printf("   ");
                printf("\u2502");                               // print the vertical line

                for(int m=0;m<t;m++){
                    printf("\u2591");                           // print the pattern
                }

                printf("\n");
            }
            else if(l=3){                                       // for 4th line
                for(int p=0;p<maxwlen-1;p++){                   // print the space
                    printf(" ");
                }
                printf("   ");
                printf("\u2502");                               // print the vertical line
               /* for(int p=0;p<77-maxwlen;p++){
                    printf(" ");
                }
               */
                printf("\n");
                break;
            }
            else{
                break;
            }
        }
        temp2=temp2->next;
    }
    for(int p=0;p<maxwlen-1;p++){                               // print the space
        printf(" ");
    }
    printf("   \u2514");                                        // print the conner symbol
    for(int p=0;p<77-maxwlen;p++){
        printf("\u2500");                                       // print the horizontal line
    }

    printf("\n");

    return(0);

}

//================================for common
int change(char *ch,char *ch1){

    int t=0;
    for(int k=0;ch[k]!='\0';k++){
        if(ch[k]<='Z'&&ch[k]>='A'){          // change capital letter to small
           ch[k]=ch[k]+32;
        }
        if(!((ch[k]<='z'&&ch[k]>='a')||(ch[k]<='Z'&&ch[k]>='A')||(ch[k]<='9'&&ch[k]>='0')||ch[k]==' ')){     //ignore the non alphanumeric
           continue;
        }


        else{
            ch1[t]=ch[k];                   //  add the char to ch1 array
            t++;
        }

    }
    ch1[t]='\0';                           // assign last char as empty
    return 0;
}
