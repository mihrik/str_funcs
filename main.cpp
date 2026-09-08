#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

unsigned int my_strlen(const char *data);
int my_puts(const char *data);
char *my_strcpy(char *dest, const char *src);
char *my_strcat(char *dest, const char *src);
int my_strcmp(const char *str1, const char *str2);
char *my_strdup(const char *str);
int my_atoi(const char *str);
double my_atof(const char *str);
size_t my_strnlen(const char *str, size_t maxlen);
char * my_strchr(const char *str, int ch);
char * my_strrchr(const char *str, int ch);
char * my_strstr(const char *haystack, const char *needle);
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);
const char *word = "Phystech";

const int SIZE_OF_BUF = 500;

int main(void)
{
    // test my_strlen
    printf("my_strlen(\"%s\") = %u\n", word, my_strlen(word));

    // test my_puts
    my_puts(word);

    // test my_strcpy
    char str[10] = {};
    my_strcpy(str, word);
    my_puts(str);

    // test my_strcat
    char phrase[] = "I love ";
    char *ptr = phrase;
    my_strcat(ptr, word);
    my_puts(ptr);

    // test my_strcmp
    printf("my_strcmp result is %d\n", my_strcmp("Phystech", "Phystec"));

    // test my_strdup
    ptr = NULL;
    ptr = my_strdup(word);
    my_puts(ptr);
    free(ptr);

    // test my_atoi
    int n = 0;
    n = atoi("-15672.8ojjnk");
    printf("%d\n", n);

    // test my_atof
    double m = 0;
    m = atof("+15672.8ojjnk");
    printf("%g\n", m);

    // test my_strnlen
    printf("%lu\n", my_strnlen(word, 3));

    // test my_strchr
    printf("%s\n", my_strchr(word, 'h'));

    // test my_strrchr
    printf("%s\n", my_strrchr(word, 'h'));

    // test my_strstr
    printf("%s\n", my_strstr(word, "hys"));

    // test my_getline
    ptr = (char *) calloc(2, sizeof(int));
    my_getline(&ptr, (size_t *)&n, stdin);
    my_puts(ptr);
    free(ptr);

    return 0;
}

unsigned int my_strlen(const char *data)
{
    unsigned int len = 0;
    const char *ptr = data;

    while (*ptr)
    {
        len++;
        ptr++;
    }

    return len;
}

int my_puts(const char *data)
{
    const char *ptr = data;

    while (*ptr)
    {
        if (putchar(*ptr) == EOF)
        {
            return EOF;
        }

        ptr++;
    }

    return putchar('\n');
}

char *my_strcpy(char *dest, const char *src)
{
    for (int i = 0; i < my_strlen(src) + 1; i++)
    {
        *(dest+i) = *(src+i);
    }

    return dest;
}

char *my_strcat(char *dest, const char *src)
{
    char *ptr = dest;

    while (*ptr)
    {
        ptr++;
    }

    for (int i = 0; i < my_strlen(src) + 1; i++)
    {
        *(ptr + i) = *(src + i);
    }

    return dest;
}

int my_strcmp(const char *str1, const char *str2)
{
    const char *ptr1 = str1;
    const char *ptr2 = str2;

    while (*ptr1 && *ptr2 && *ptr1 == *ptr2)
    {
        ptr1++;
        ptr2++;
    }

    return *ptr1 - *ptr2;
}

char *my_strdup(const char *str)
{
    char *data = (char *) calloc(my_strlen(str) + 1, sizeof(char));

    return my_strcpy(data, str);
}

int my_atoi(const char *str)
{
    int is_negative = 0;
    int num = 0;
    const char *ptr = str;

    if (*ptr == '-')
    {
        is_negative = 1;
        ptr++;
    }
    else if (*ptr == '+')
    {
        ptr++;
    }
    while (isdigit(*ptr))
    {
        num *= 10;
        num += *ptr - '0';
        ptr++;
    }

    if (is_negative)
    {
        num *= -1;
    }

    return num;
}

double my_atof(const char *str)
{
    double num = 0;
    const char *ptr = str;
    int is_negative = 0;

    if (*ptr == '-')
    {
        is_negative = 1;
        ptr++;
    }
    else if (*ptr == '+')
    {
        ptr++;
    }
    while (isdigit(*str))
    {
        num *= 10;
        num += *ptr - '0';
        ptr++;
    }

    if (*ptr == '.')
    {
        ptr++;
        double exp = 1;

        while (isdigit(*ptr))
        {
            exp *= 10;
            num += (*ptr - '0') / exp;
        }
    }

    if (is_negative)
    {
        num *= -1;
    }

    return num;
}

size_t my_strnlen(const char *str, size_t maxlen)
{
    unsigned int len = 0;
    const char *ptr = str;

    while (*ptr)
    {
        len++;
        ptr++;
    }

    if (len < maxlen)
    {
        return len;
    }
    return maxlen;
}

char * my_strchr(const char *str, int ch)
{
    const char *ptr = str;

    while (*ptr)
    {
        if (*ptr == ch)
        {
            return (char *)ptr;
        }

        ptr++;
    }

    return NULL;
}

char * my_strrchr(const char *str, int ch)
{
    const char *ptr = str;
    char *answer = NULL;

    while (*ptr)
    {
        if (*ptr == ch)
        {
            answer = (char *)ptr;
        }

        ptr++;
    }

    return answer;
}

char * my_strstr(const char *haystack, const char *needle)
{
    const char *ptr_hay = haystack;
    const char *ptr_ndl = needle;
    int in_str = 0;

    while (*ptr_hay)
    {
        if (*ptr_hay == *ptr_ndl)
        {
            ptr_ndl++;
        }
        else
        {
            ptr_ndl = needle;
        }

        if (*ptr_ndl == '\0')
        {
            in_str = 1;
            break;
        }

        ptr_hay++;
    }


    if (in_str)
    {
        return (char *)ptr_hay - my_strlen(needle) + 1;
    }

    return NULL;
}

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
    int counter = 0;
    int start_size = 2;
    int ch = '\0';
    int read = 0;

    char *arr = (char *)calloc(start_size, sizeof(char));
    if (*lineptr != NULL)
    {
        free(*lineptr);
    }

    while (!read)
    {
        start_size *= start_size;
        arr = (char *)realloc(arr, start_size * sizeof(int));

        while (counter < start_size)
        {
            ch = getc(stream);
            if (ch != EOF)
            {
                arr[counter] = ch;
                counter++;
                if (ch =='\n')
                {
                    read = 1;
                    break;
                }
            }
            else
            {
                read = 1;
                break;
            }
        }

        if (ch == EOF || ch == '\n')
        {
            *n = counter;
            *lineptr = arr;
            return *n;
           }
    }
    return -1;
}