#define MAX_LEN 255
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String {
    char string[MAX_LEN];
    int length;
}String;


String *init_string(char *string) {
    String *new_string = (String *)malloc(sizeof(String));
    int len = strlen(string);
    strncpy(new_string->string, string, len);
    new_string->length = len;
    return new_string;
}

String *init_1_string(char *string) {
    String *new_string = (String *)malloc(sizeof(String));
    int len = strlen(string);
    new_string->string[0] = '#';
    for (int i = 0; i < len; i++) {
        new_string->string[i + 1] = string[i];
    }
    new_string->string[len + 1] = '\0';
    new_string->length = len;
    return new_string;
}

/**
 *
 * @param main_string 主串（从0开始）
 * @param sub_string 模式串
 * @return 模式串出现的位置
 */
int violent_match_string(String *main_string, String *sub_string) {
    if (main_string->length < sub_string->length) {
        printf("the sub_string bigger than the main_string!\n");
        exit(1);
    }
    int main_index = 0;
    int sub_index = 0;
    while (main_index < main_string->length && sub_index < sub_string->length) {
        if (main_string->string[main_index] == sub_string->string[sub_index]) {
            main_index++;
            sub_index++;
        }else {
            main_index = main_index - sub_index + 1;
            sub_index = 0;
        }
    }
    if (sub_index >= sub_string->length) {
        return main_index - sub_string->length;
    }
    return -1;
}


int index_main_string(String *main_string, String *sub_string) {
    int i = 1;
    int j = 1;
    while (i <= main_string->length && j <= sub_string->length) {
        if (main_string->string[i] == sub_string->string[j]) {
            i++;
            j++;
        }else {
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > sub_string->length)
        return i - sub_string->length;
    return 0;
}

/**
 * @description 获取string的next数组（KMP算法的核心所在）
 * @param string 串
 * @param next next数组
 */
void get_string_next(String *string, int *next) {
    int i = 1;
    int j = 0;
    next[0] = -1;
    next[i] = 0;
    while (i < string->length) {
        if (j == 0 || string->string[i] == string->string[j]) {
            ++i;
            ++j;
            next[i] = j;
        }else {
            j = next[j];
        }
    }
}

int kmp_string(String *main_string, String *sub_string) {
    int *next = (int *)malloc(sizeof(int) * (main_string->length + 1));
    int i = 1;
    int j = 1;
    get_string_next(sub_string, next);
    while (i <= main_string->length && j <= sub_string->length) {
        if (j == 0 || main_string->string[i] == sub_string->string[j]) {
            ++i;
            ++j;
        }else {
            j = next[j];
        }
    }
    free(next);
    if (j > sub_string->length) {
        return i - sub_string->length;
    }
    return 0;
}


int main(){
    // String * main_s = init_string("adgbsdfgqweg");
    // String * sub_s = init_string("fgq");
    // printf("%d \n", violent_match_string(main_s, sub_s));
    // printf("%d \n", sub_s->length);
    // String * string = init_1_string("hello world");
    // printf("%d %c\n", string->length, string->string[0]);
    // printf("%s \n", string->string);
    // String * init_1_string1 = init_1_string("wor");
    // printf("%d \n", index_main_string(string, init_1_string1));
    String * string = init_1_string("agbnwlwejg");
    String * string1 = init_1_string("wlwe");
    int next[string1->length + 1];
    get_string_next(string1, next);
    printf("the string1's next is:\n");
    for (int i = 1; i < string1->length + 1; i++) {
        printf("%d ", next[i]);
    }
    printf("\n");
    printf("%d\n", kmp_string(string, string1));
    return 0;
}