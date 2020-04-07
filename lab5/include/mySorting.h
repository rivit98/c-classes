#pragma once
#include <algorithm>
#include <iterator>

template <class T>
void selection_sort(T begin, T end){
    for (T i = begin; i != end; ++i)
        std::iter_swap(i, std::min_element(i, end));
}

template<class T>
void mySort(T& container){
    selection_sort(std::begin(container), std::end(container));
}

void swap_str(char str1[], char str2[]) {
    std::size_t MAX_SIZE = std::max(strlen(str1), strlen(str2));
    char *temp_buffer = new char[MAX_SIZE+1];

    strcpy(temp_buffer, str1);
    strcpy(str1, str2);
    strcpy(str2, temp_buffer);

    delete[] temp_buffer;
}

int stricmp (const char *p1, const char *p2){
    auto *s1 = (unsigned char *) p1;
    auto *s2 = (unsigned char *) p2;
    unsigned char c1, c2;

    do
    {
        c1 = (unsigned char) toupper((int)*s1++);
        c2 = (unsigned char) toupper((int)*s2++);
        if (c1 == '\0'){
            return c1 - c2;
        }
    }
    while (c1 == c2);

    return c1 - c2;
}

template<std::size_t N, std::size_t M>
void mySort(char (&arr)[N][M]){
    int i = 0;
    int j = 0;
    while (i < N) {
        j = 0;
        while (j < N) {
            if (stricmp(arr[i], arr[j]) < 0) {
                swap_str(arr[i], arr[j]);
            }
            j++;
        }
        i++;
    }
}
