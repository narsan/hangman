#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

int main() {

    char hangman[14] = {'_', ' ', '_', ' ', '_', ' ', '_', ' ', '_', ' ', '_', ' ', '_'};
    char word_line[200];

    FILE *fp = fopen("dictionary.txt", "r");
    int lines = 0;

    while (!feof(fp)) {
        char string[100];
        fgets(string, 100, fp);
        lines++;
    }
    fclose(fp);

    fp = fopen("dictionary.txt", "r");
    srand(time(NULL));
    int random = rand() % lines;
    lines = 0;
    char my_word[100];
    while (!feof(fp)) {
        char string[100];
        fgets(string, 100, fp);
        if (lines == random) {
            strcpy(my_word, string);
            break;
        }
        lines++;
    }
    int word_len = strlen(my_word) - 1;
    int hangman_len = strlen(hangman);
    printf("the word len is %d\n", word_len);
    for (int i = 0; i < 2 * word_len; i += 2) {
        word_line[i] = '_';
        word_line[i + 1] = ' ';
    }
    word_line[2 * word_len] = 0;
    puts(word_line);
    puts(my_word);


    char letter;
    while (hangman_len > 0 && word_len > 0) {
        printf("Guess your next letter >>");
        scanf(" %c", &letter);
        char *index = strchr(my_word, letter);
        if (index == NULL) {
            Beep(800, 900);
            switch (hangman_len) {
                case 13:
                    hangman[0] = 'H';
                    break;
                case 11:
                    hangman[2] = 'A';
                    break;
                case 9:
                    hangman[4] = 'N';
                    break;
                case 7:
                    hangman[6] = 'G';
                    break;
                case 5:
                    hangman[8] = 'M';
                    break;
                case 3:
                    hangman[10] = 'A';
                    break;
                case 1:
                    hangman[12] = 'N';
                    break;
            }
            hangman_len -= 2;
        } else {
            do {
                index -= my_word;
                word_line[(int) index * 2] = my_word[(int) index];
                my_word[(int) index] = 127;
                index = strchr(my_word, letter);
                word_len--;
            } while (index != NULL);
        }
        puts(word_line);
        puts(hangman);
    }

    return 0;
}