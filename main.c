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
    int nextCharacter;
    fgetpos(stdin, &filePos);

    do {
        nextCharacter = getchar();
        if (!isspace(nextCharacter)) {
            break;
        }
        fgetpos(stdin, &filePos);
    } while (nextCharacter != EOF);
    if (nextCharacter == EOF) return;
    int strlen = 0;
    while (nextCharacter != EOF && !isspace(nextCharacter)) {
        strlen += 1;
        nextCharacter = getchar();
    }

    //TRY mallocing before assigning

    char* tmp_p = malloc(sizeof(char) * (1 + strlen));
    if (tmp_p == NULL)
    {
        fprintf(stderr, "Big bad malloc error. Bailing out.\n");
        exit(-1);
    }

    *wordAddr = tmp_p;
    memset(*wordAddr, '\0', strlen + 1);
    fsetpos(stdin, &filePos);
    for (int i = 0; i < strlen;i++) (*wordAddr)[i] = getchar();
    return;
}

