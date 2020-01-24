#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

typedef struct { char *action; int score; } Scores;
Scores scores[5] = {{"P",50}, {"L",20}, {"D",-10}, {"C",30}, {"S",40}};


int is_empty(const char *s){
    while(*s != '\0'){
        if (!isspace((unsigned char)*s))
        return 0;
        s++;
    }
    return 1;
}

void main(int argc, char *argv[]){
    char *filename = argv[1];
    //printf("%s\n", argv[0]);

    FILE *fp;
    int x = 0;  
    size_t n = 0;
    char *line = NULL;
    ssize_t chars_read;
    

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Cannot open the input/ file not found");
    }

    
    //char *line1 = (char*) malloc(1+sizeof(line));
    //line1 = strcpy(line1, line); 
    //printf("the size of line is %ld", sizeof(line1));
    //printf("the size of old line is %ld", sizeof(line));

    while(chars_read = getline(&line, &n, fp) != -1){

        char *split_tokens = strtok(line,",()");
        int c = 0;
        char *tuple[3];
        
        while (split_tokens != NULL){
            //printf("the token is:%s\n", split_tokens);
            if (!is_empty(split_tokens)){
                tuple[c++] = split_tokens;
            }
            if (c==3){
                int s =0;
                for (int i=0;i<5;i++){
                    // printf("scores is: %d\n", scores[i].action);
                    if (strcmp(scores[i].action, tuple[1])==0){
                        s = scores[i].score;
                    }
                }
                c = 0;
                printf("(%s,%s,%d)\n", tuple[0], tuple[2], s);
            }
            split_tokens = strtok(NULL,",()");
        }
    }
    printf("\n");
    return;
}