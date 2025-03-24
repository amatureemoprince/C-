#include <stdbool.h>
#include<stdio.h>
#include <string.h>

bool isAnagram(char *s1, char *s2) {
    int hash[26] = {0};
    int len_s1 = strlen(s1);
    int len_s2 = strlen(s2);
    if (len_s1 != len_s2) {
        return false;
    }
    for (int i = 0; i < len_s1; i++) {
        hash[s1[i] - 'a']++;
    }
    for (int i = 0; i < len_s2; i++) {
        hash[s2[i] - 'a']--;
    }
    for (int i = 0; i < len_s1; i++) {
        if (hash[i] != 0) {
            return false;
        }
    }
    return true;
}


int main(){
    char *s1 = "abbacc";
    char *s2 = "bbaacc";
    if (isAnagram(s1, s2)) {
        printf("is anagram!\n");
    }else {
        printf("isn't anagram\n");
    }

    return 0;
}