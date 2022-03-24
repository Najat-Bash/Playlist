#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int isBlank (char const * line)
{
    char * ch;
    int is_blank = -1;

    // Iterate through each character.
    for (ch = line; *ch != '\0'; ++ch)
    {
        if (!isspace(*ch))
        {
            // Found a non-whitespace character.
            is_blank = 0;
            break;
        }
    }

    return is_blank;
}

int main(int argc, char const *argv[])
{
    FILE * fp;

    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int end_song_name; // end index of song name
    int start_song_duration; // start index of duration
    char artist_name[100];
    char song_name[100]; // variable to store song name
    char duration[100]; // variable to store duration
    char last_line[200];

    fp = fopen("songs.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {

        char * asterix="***";
        last_line[0]='\0';
        if(isBlank(line)== -1) // checking blank, if blank skip this iteration
            continue;

        line[strcspn(line, "\n")] = 0; // deleting new line character

        char *ptr;
        if(ptr=strstr(line,asterix)==NULL)  // if no asterix inside the string then its artist name
        {
            strcpy(artist_name,line);
            continue;
        }

        // Song parsing section

        int asterix_index = strcspn(line, asterix); // getting asterix index by strcspn
        int duration_start = asterix_index+3;   // duration starts 3 index after first asterix

        for(int i = 0; i < asterix_index; i++)
        {
            song_name[i]=line[i]; // copying line to the song_name till the asterix
        }
        song_name[asterix_index]='\0'; // adding null terminator


        // Duration parsing section

        int j=0;
        for(int i = duration_start; i<strlen(line); i++)
        {
            duration[j] = line[i];
            j++;
        }
        duration[j]='\0';

        printf("%s %s %s \n", artist_name, song_name, duration);

    }


    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);

    return 0;
}


