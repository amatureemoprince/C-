#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * 题目描述
 * 回文，英文palindrome，指一个顺着读和反过来读都一样的字符串，比如madam、我爱我，这样的短句在智力性、
 * 趣味性和艺术性上都颇有特色，中国历史上还有很多有趣的回文诗。
 * 那么，我们的第一个问题就是：判断一个字串是否是回文？
 */


/***
 * @param string 需要判断的字符串
 * @return 是否为回文数
 */
bool palindrome(const char *string) {
  if (string == NULL) {
    return false;
  }
  int end = (int) strlen(string) - 1;
  int start = 0;
  while (start < end) {
    if (string[start] != string[end]) {
      return false;
    }
    start++;
    end--;
  }
  return true;
}
int main(){
  const char arr[1000];
  printf("please input a string :");
  // &取地址符
  scanf("%s", &arr);
  if (palindrome(arr)) {
    printf("is a palindrome");
  }else {
    printf("isn't a palindrome");
  }
  return 0;
}