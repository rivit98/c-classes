#pragma once
#include <iostream>
#include <cstring>
#include <istream>
#include <ostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <regex>
#include <random>

class MyString{
public:
    static constexpr size_t initialBufferSize = 20;
    static std::string generateRandomWord(size_t word_length);

private:
    char m_data_c[MyString::initialBufferSize + 1]{}; //just for sure
    std::string m_data_s;
    size_t m_size;

public:
    ~MyString() = default;
    MyString();
    MyString(const char *str);
    MyString(const std::string& str);


    [[nodiscard]] size_t size() const;
    [[nodiscard]] size_t capacity() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] const char *c_str() const;
    void clear();
    void trim();
    void ltrim();
    void rtrim();
    void shrink();
    [[nodiscard]] char *begin();
    [[nodiscard]] char *end();
    [[nodiscard]] const char *begin() const;
    [[nodiscard]] const char *end() const;
    [[nodiscard]] std::vector<std::string> split(const std::string& delimiters) const;
    [[nodiscard]] std::set<MyString> getUniqueWords() const;
    [[nodiscard]] std::map<MyString, size_t> countWordsUsage() const;
    void toLower();
    [[nodiscard]] bool startsWith(const std::string& part) const;
    [[nodiscard]] bool endsWith(const std::string& part) const;
    [[nodiscard]] MyString join(const std::vector<MyString>& words) const;
    [[nodiscard]] bool all_of(std::function<int(int c)> predicate) const;

    const char &operator[](size_t index) const;
    char &operator[](size_t index);
    MyString& operator+=(const char data[]);
    MyString& operator+=(char c);
    bool operator<(const MyString& str) const;
    bool operator==(const MyString& str) const;
    bool operator!=(const MyString& str) const;

    friend std::istream& operator>>(std::istream& os, MyString& mystr);
};

std::ostream& operator<<(std::ostream& os, const MyString& mystr);