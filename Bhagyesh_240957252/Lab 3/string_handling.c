
#include <stdio.h>

int string_length(char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void string_concatenate(char str1[], char str2[], char result[]) {
    int i = 0, j = 0;

    while (str1[i] != '\0') {
        result[i] = str1[i];
        i++;
    }

    while (str2[j] != '\0') {
        result[i] = str2[j];
        i++;
        j++;
    }

    result[i] = '\0';
}

int string_compare(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0; // not equal
        }
        i++;
    }

    return (str1[i] == '\0' && str2[i] == '\0');
}

void insert_substring(char str[], char sub[], int pos, char result[]) {
    int i = 0, j = 0, k = 0;

    while (i < pos && str[i] != '\0') {
        result[k++] = str[i++];
    }

    while (sub[j] != '\0') {
        result[k++] = sub[j++];
    }

    while (str[i] != '\0') {
        result[k++] = str[i++];
    }

    result[k] = '\0';
}

void delete_substring(char str[], int pos, int len, char result[]) {
    int i = 0, k = 0;

    while (i < pos && str[i] != '\0') {
        result[k++] = str[i++];
    }

    i += len;

    while (str[i] != '\0') {
        result[k++] = str[i++];
    }

    result[k] = '\0';
}

int main() {
    char str1[100], str2[100], result[200];
    int pos, len;

    printf("Enter a string to find its length: ");
    gets(str1);
    printf("Length = %d\n", string_length(str1));

    printf("\nEnter first string: ");
    gets(str1);
    printf("Enter second string: ");
    gets(str2);
    string_concatenate(str1, str2, result);
    printf("Concatenated string: %s\n", result);

    printf("\nEnter first string to compare: ");
    gets(str1);
    printf("Enter second string to compare: ");
    gets(str2);
    if (string_compare(str1, str2)) {
        printf("Strings are equal.\n");
    } else {
        printf("Strings are not equal.\n");
    }

    printf("\nEnter main string: ");
    gets(str1);
    printf("Enter substring to insert: ");
    gets(str2);
    printf("Enter position to insert at: ");
    scanf("%d", &pos);
    getchar(); // clear newline
    insert_substring(str1, str2, pos, result);
    printf("String after insertion: %s\n", result);

    printf("\nEnter string: ");
    gets(str1);
    printf("Enter position to delete from: ");
    scanf("%d", &pos);
    printf("Enter length of substring to delete: ");
    scanf("%d", &len);
    delete_substring(str1, pos, len, result);
    printf("String after deletion: %s\n", result);

    return 0;
}
