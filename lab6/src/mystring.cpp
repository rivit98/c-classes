#include "mystring.h"

#include <utility>


MyString::MyString() :
        m_data_c{},
        m_data_s(),
        m_size(0){

}

MyString::MyString(const char *str) :
        m_size(std::strlen(str)) {

    if(m_size < initialBufferSize){
        std::strncpy(m_data_c, str, m_size);
        m_data_c[m_size] = '\0';
    }else{
        m_data_s.reserve(m_size);
        m_data_s = str;
    }
}

MyString::MyString(const std::string &str) :
        MyString(str.c_str()){

}

size_t MyString::size() const {
    return m_size;
}

size_t MyString::capacity() const {
    return initialBufferSize + m_data_s.capacity();
}

bool MyString::empty() const {
    return m_size == 0;
}

void MyString::clear() {
    std::memset(m_data_c, 0, initialBufferSize);
    m_data_s.clear();
    m_size = 0;
}

const char *MyString::c_str() const{
    if(m_size < initialBufferSize){
        return m_data_c;
    }
    return m_data_s.c_str();
}

const char &MyString::operator[](size_t index) const{
    if(index >= m_size){
        throw std::out_of_range("Out of range!");
    }

    if(m_size < initialBufferSize){
        return m_data_c[index];
    }
    return m_data_s[index];
}

char &MyString::operator[](size_t index){
    if(index >= m_size){
        throw std::out_of_range("Out of range!");
    }

    if(m_size < initialBufferSize){
        return m_data_c[index];
    }
    return m_data_s[index];
}

void MyString::trim() {
    ltrim();
    rtrim();
    shrink();
}

void MyString::ltrim() {
    if(m_size < initialBufferSize){
        std::copy_if(std::begin(m_data_c), std::end(m_data_c), std::begin(m_data_c), [](char c){
            return !std::isspace(c);
        });
        m_size = std::strlen(m_data_c);
    }else{
        m_data_s.erase(m_data_s.begin(), std::find_if(m_data_s.begin(), m_data_s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
        m_size = m_data_s.size();
        shrink();
    }
}

void MyString::rtrim() {
    if(m_size < initialBufferSize){
        char* back = m_data_c + m_size;
        while(isspace(*--back));
        *(back+1) = '\0';
        m_size = std::strlen(m_data_c);
    }else{
        m_data_s.erase(std::find_if(m_data_s.rbegin(), m_data_s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), m_data_s.end());
        m_size = m_data_s.size();
        shrink();
    }
}

void MyString::shrink() {
    if(m_size >= initialBufferSize){
        return;
    }
    std::strncpy(m_data_c, m_data_s.c_str(), m_size);
    m_data_c[m_size] = '\0';
    m_data_s.clear();
}

MyString& MyString::operator+=(const char data[]){
    size_t size = std::strlen(data);
    if(m_size + size < initialBufferSize){ //if it fits to static buffer
        std::strncpy(m_data_c + m_size, data, size);
//        std::copy(std::begin(m_data_c) + m_size, std::end(m_data_c), &data[0]);
        m_data_c[m_size] = '\0';
        m_size = std::strlen(m_data_c);
    }else if(m_size >= initialBufferSize){
        m_data_s += data;
        m_size = m_data_s.size();
    }else{ //we need to copy static buffer to string and also append data to string
        m_data_s.clear();
        m_data_s = m_data_c;
        m_data_s += data;
        m_size = m_data_s.size();
    }

    return *this;
}

MyString& MyString::operator+=(char c){
    if(m_size + 1 < initialBufferSize){ //if it fits to static buffer
        m_data_c[m_size] = c;
        m_data_c[++m_size] = '\0';
    }else if(m_size >= initialBufferSize){
        m_data_s += c;
        m_size++;
    }else{ //we need to copy static buffer to string and also append data to string
        m_data_s.clear();
        m_data_s = m_data_c;
        m_data_s += c;
        m_size++;
    }

    return *this;
}

char *MyString::begin() {
    if(m_size < initialBufferSize){
        return m_data_c;
    }

    return m_data_s.data();
}

char *MyString::end(){
    return begin() + m_size;
}

const char *MyString::begin() const {
    if(m_size < initialBufferSize){
        return m_data_c;
    }

    return m_data_s.data();
}

const char *MyString::end() const{
    return begin() + m_size;
}

std::vector<std::string> MyString::split(const std::string& delimiters) const {
    std::vector<std::string> elems;

    std::string ss;
    ss.reserve(m_size);
    ss = ((m_size < initialBufferSize) ? m_data_c : m_data_s);

    std::regex re("[" + delimiters + "]");
    std::sregex_token_iterator first{ss.begin(), ss.end(), re, -1};
    std::sregex_token_iterator end;

    std::string item;
    while(first != end){
        item = *first;
        first++;

        item.erase(std::remove_if(item.begin(), item.end(), [](const char c){
            return !std::isalnum(c);
        }), item.end());

        if(!item.empty()){
            elems.push_back(item);
        }
    }

    return elems;
}

std::set<MyString> MyString::getUniqueWords() const {
    std::vector<std::string> tokens = split(" .,");
    std::transform(tokens.begin(), tokens.end(), tokens.begin(), [](std::string& s) {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
        return s;
    });
    //std::set(tokens.begin(), tokens.end());

    std::set<MyString> uniq;
    for(const std::string& s : tokens){
        uniq.insert(MyString(s));
    }

    return uniq;
}

std::map<MyString, size_t> MyString::countWordsUsage() const {
    std::vector<std::string> tokens = split(" .,");

    std::map<MyString, size_t> words;
    for(const std::string& s : tokens){
        ++words[MyString(s)];
    }

    return words;
}

bool MyString::operator<(const MyString& str) const {
    return std::strcmp(c_str(), str.c_str()) < 0;
}

bool MyString::operator==(const MyString &str) const {
    return std::strcmp(c_str(), str.c_str()) == 0;
}

bool MyString::operator!=(const MyString &str) const {
    return !operator==(str);
}

void MyString::toLower() {
    if(m_size < initialBufferSize){
        char *p = m_data_c;
        for (;*p ; ++p){
            *p = std::tolower(*p);
        }
    }else{
        std::transform(m_data_s.begin(), m_data_s.end(), m_data_s.begin(), ::tolower);
    }
}

std::ostream& operator<<(std::ostream& os, const MyString& mystr){
    os << mystr.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, MyString& mystr){
    is.seekg(0, std::istream::end);
    size_t size = is.tellg();
    is.seekg(0, std::istream::beg);

    if(size < MyString::initialBufferSize){
        is.read(mystr.m_data_c, size);
    }else{
        mystr.m_data_s.reserve(size);
        mystr.m_data_s = std::string(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>());
    }
    mystr.m_size = size;

    return is;
}

bool MyString::startsWith(const std::string &part) const {
    size_t size = part.size();
    if(size > m_size){
        return false;
    }

    if(m_size < initialBufferSize){
        return std::search(begin(), end(), part.begin(), part.end()) != end();
    }
    const auto& end = m_data_s.begin() + size;
    return std::search(m_data_s.begin(), end, part.begin(), part.end()) != end;

//    if(m_size < initialBufferSize){
//        if(m_size < size){
//            return false;
//        }
//
//        const char *prefix = part.c_str();
//        const char *check = m_data_c;
//        while(*prefix){
//            if(*prefix++ != *check++){
//                return false;
//            }
//        }
//        return true;
//    }
//
//    return m_data_s.rfind(part, 0) == 0;
}

bool MyString::endsWith(const std::string &part) const {
    size_t size = part.size();
    if(size > m_size){
        return false;
    }

    if(m_size < initialBufferSize){
        const auto& end = std::rbegin(m_data_c) + m_size;
        return std::search(std::rbegin(m_data_c), end, part.rbegin(), part.rend()) != end;
    }
    const auto& end = m_data_s.rbegin() + m_size;
    return std::search(m_data_s.rbegin(), end, part.rbegin(), part.rend()) != end;
}

std::string MyString::generateRandomWord(size_t word_length) {
    std::string result;
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dis(0, 25);
    std::generate_n(std::back_inserter(result), word_length, [&dis, &g](){
        return 'a' + dis(g);
    });

    return result;
}

MyString MyString::join(const std::vector<MyString> &words) const {
    std::string output;
    auto vec_begin = words.begin();
    MyString s;

    if(vec_begin != words.end()){
        s = *vec_begin;
        std::copy(s.begin(), s.begin() + s.m_size, std::back_inserter(output));
        vec_begin++;
    }

    while(vec_begin != words.end()){
        s = *vec_begin;
        vec_begin++;
        std::copy(begin(), begin() + m_size, std::back_inserter(output));
        std::copy(s.begin(), s.begin() + s.m_size, std::back_inserter(output));
    }

    return MyString(output);
}

bool MyString::all_of(std::function<int(int)> predicate) const {
    return std::find_if_not(begin(), end(), predicate) == end();
}