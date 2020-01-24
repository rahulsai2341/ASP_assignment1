#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {char *subject_name; int subject_score} Tuple;

int update_subject_score(Tuple **tuples, char *subject_name, int subject_score, int length)
{
    for(int i = 0; i < length; i++)
    {
        if(strcmp(tuples[i]->subject_name, subject_name) == 0)
        {
            tuples[i]->subject_score = tuples[i]->subject_score + subject_score;
            return length;
        }
    }
    Tuple *top = malloc(sizeof(Tuple));
    top->subject_name = malloc(sizeof(subject_name));
    strcpy(top->subject_name, subject_name);
    top->subject_score = subject_score;
    tuples[length++] = top;

    return length;
}

void main(int argc, char *argv[])
{
    char buffer[30];
    char *previous_user_id = NULL;
    Tuple *tuples[1000];
    int count = 0;
    char *delim = "(),";

    //Loop until there are tuples in STDIN
    while(fgets(buffer, 30, stdin) != NULL)
    {    
        // Check for temination condition
        if (strcmp("\n", buffer) == 0){
            break;
        }    
        //Seperate each element in the tuple
        char *user = strtok(buffer, delim);
        char *subject_name = strtok(NULL, delim);
        int subject_score = atoi(strtok(NULL, delim));

        //Starting condition
        if(previous_user_id == NULL)
        {
            previous_user_id = malloc(sizeof(user));
            strcpy(previous_user_id, user);

            Tuple *top = malloc(sizeof(Tuple));
            top->subject_name = malloc(sizeof(subject_name));
            strcpy(top->subject_name, subject_name);

            top->subject_score = subject_score;

            tuples[count++] = top;
        }
        //If the user is still the same
        else if(strcmp(previous_user_id, user) == 0)
        {
            // Check for the subject_name and update the subject_score
            count = update_subject_score(&tuples, subject_name, subject_score, count);
        }
        // If the user changed
        else
        {
            for(int i=0; i < count; i++)
            {
                printf("(%s,%s,%d)\n", previous_user_id, tuples[i]->subject_name, tuples[i]->subject_score);
                free(tuples[i]);
            }

            previous_user_id = strcpy(previous_user_id, user);
            count = 0;
            // Now that the user is changed, create a new Tuple struct and re-initialize the count
            Tuple *top = malloc(sizeof(Tuple));
            top->subject_name = malloc(sizeof(subject_name));
            strcpy(top->subject_name, subject_name);

            top->subject_score = subject_score;

            tuples[count++] = top;
        }
        
    }
    for(int i=0; i < count; i++)
    {
        printf("(%s,%s,%d)\n", previous_user_id, tuples[i]->subject_name, tuples[i]->subject_score);
        free(tuples[i]);
    }
    return;
}