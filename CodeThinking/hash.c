#include <stdbool.h>
#include<stdio.h>
#include <stdlib.h>
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

int *intersection(int *arr, int a_len, int *brr, int b_len, int *resultSize) {
    int hash[1000] = {0};
    int min_len = a_len < b_len ? a_len : b_len;
    int resultIndex = 0;
    int *result = (int *)calloc(min_len, sizeof(int));

    for (int i = 0; i < a_len; i++) {
        hash[arr[i]]++;
    }

    for (int i = 0; i < b_len; i++) {
        if (hash[brr[i]] != 0) {
            result[resultIndex++] = brr[i];
            hash[brr[i]] = 0;
        }
    }

    *resultSize = resultIndex;
    return result;
}

int main(){

    char *s1 = "abbacc";
    char *s2 = "bbaacc";
    if (isAnagram(s1, s2)) {
        printf("is anagram!\n");
    }else {
        printf("isn't anagram\n");
    }

    int arr[5] = {1, 2, 2, 4, 5};
    int brr[3] = {2, 2, 5};
    int resultIndex;
    int * intersection1 = intersection(arr, 5, brr, 3, &resultIndex);
    printf("arr and brr hava sample elements are :\n");
    for (int i = 0; i < resultIndex; i++) {
        printf("%d ", intersection1[i]);
    }
    printf("\n");
    free(intersection1);
    return 0;
}