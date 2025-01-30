#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void getWord(char** wordAddr);
int main() {
    printf("Write a word and press enter to see if there is a \"cat\" in it.\nWrite '\\q' to exit the program.\n");
    regex_t hasCatRegexp;
    regmatch_t catMatch[1];
    if (regcomp(&hasCatRegexp, "cat", REG_ICASE | REG_NOSUB))
    {
        fprintf(stderr, "Couldn't compile regexp.\n");
        return 1;
    }
    char* word = NULL;
    do {
        printf("Write a word: ");
        getWord(&word);
        if (word == NULL) break;
        if (word[0] == '\\' && word[1] == 'q') break;
        if (regexec(&hasCatRegexp, word, 1, catMatch, 0) == REG_NOMATCH)
            printf("The word \"%s\" does not have \"cat\" in it.\n", word);
        else
            printf("The word \"%s\" has \"cat\" in it.\n", word);
    } while (!feof(stdin));
    if (word != NULL) free(word);
    printf("Bye-bye...\n");
    return 0;
}

void getWord(char** wordAddr) {
    //add debug messages
    if (*wordAddr != NULL) { free(*wordAddr); *wordAddr = NULL; }

    fpos_t filePos;
    int __debug_spacesSkipped = 0;
    int nextCharacter;
    fgetpos(stdin, &filePos);

    do {
        nextCharacter = getchar();
        if (!isspace(nextCharacter)) {
            break;
        }
        fgetpos(stdin, &filePos);
        __debug_spacesSkipped++;
    } while (nextCharacter != EOF);
    fprintf(stderr, "Skipped %d space characters.\n", __debug_spacesSkipped);
    if (nextCharacter == EOF) { fprintf(stderr, "Reached end of file before a word was found.\n"); return; }
    int strlen = 0;
    while (nextCharacter != EOF && !isspace(nextCharacter)) {
        strlen += 1;
        nextCharacter = getchar();
    }
    fprintf(stderr, "Read %d non-space characters.\n", strlen);
    if (nextCharacter == EOF) { fprintf(stderr, "Reached end of file while reading a word.\n"); }
    //TRY mallocing before assigning

    char* tmp_p = malloc(sizeof(char) * (1 + strlen));
    if (tmp_p == NULL)
    {
        fprintf(stderr, "Big bad malloc error. Bailing out.\n");
        exit(-1);
    }

    *wordAddr = tmp_p;
    fsetpos(stdin, &filePos);
    //maybe i should just change this to scanf, lol.
    memset(*wordAddr, '\0', strlen + 1);
    for (int i = 0; i < strlen;i++) (*wordAddr)[i] = getchar();
    fprintf(stderr, "Read word: \"%s\"\n", tmp_p);
    return;
}

