#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class String {
protected:
    char* str;
    int length;

public:
    String() {
        length = 0;
        str = new char[1];
        str[0] = '\0';
    }

    String(const char* s) {
        length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
    }

    String(const String& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    virtual ~String() {
        delete[] str;
    }

    int getLength() const {
        return length;
    }

    void clear() {
        delete[] str;
        length = 0;
        str = new char[1];
        str[0] = '\0';
    }

    String operator+(const String& other) const {
        String result;
        result.length = length + other.length;
        delete[] result.str;
        result.str = new char[result.length + 1];
        strcpy(result.str, str);
        strcat(result.str, other.str);
        return result;
    }

    String& operator+=(const String& other) {
        char* temp = new char[length + other.length + 1];
        strcpy(temp, str);
        strcat(temp, other.str);
        delete[] str;
        str = temp;
        length += other.length;
        return *this;
    }

    String& operator+=(char c) {
        char* temp = new char[length + 2];
        strcpy(temp, str);
        temp[length] = c;
        temp[length + 1] = '\0';
        delete[] str;
        str = temp;
        length++;
        return *this;
    }

    bool operator==(const String& other) const {
        return strcmp(str, other.str) == 0;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    const char* getStr() const {
        return str;
    }

    virtual void changeSign() {}
};

class BitString : public String {
public:
    BitString() : String() {}

    BitString(const char* s) {
        length = 0;
        str = new char[1];
        str[0] = '\0';
        for (int i = 0; s[i] != '\0'; ++i) {
            if (s[i] == '0' || s[i] == '1') {
                *this += s[i];
            }
            else {
                clear();
                break;
            }
        }
    }

    BitString(const BitString& other) : String(other) {}

    BitString& operator=(const BitString& other) {
        String::operator=(other);
        return *this;
    }

    ~BitString() {}

    void changeSign() override {
        const char* temp = getStr();
        for (int i = 0; i < length; ++i) {
            if (temp[i] == '0')
                str[i] = '1';
            else if (temp[i] == '1')
                str[i] = '0';
        }
    }
};

int main() {
    String str1("Hello");
    String str2("World");

    String concatenated = str1 + str2;
    cout << "Concatenated string: " << concatenated.getStr() << endl;

    str1 += str2;
    cout << "Concatenated string (using +=): " << str1.getStr() << endl;

    if (str1 == concatenated)
        cout << "Strings are equal." << endl;
    else
        cout << "Strings are not equal." << endl;

    if (str1 != str2)
        cout << "Strings are not equal." << endl;
    else
        cout << "Strings are equal." << endl;

    cout << "Length of concatenated string: " << concatenated.getLength() << endl;

    concatenated.clear();
    cout << "Cleared concatenated string: " << concatenated.getStr() << endl;

    BitString bs("10101");

    bs.changeSign();
    cout << "Changed BitString: " << bs.getStr() << endl;

    BitString bs2("111");
    bs += bs2;
    cout << "Concatenated BitStrings: " << bs.getStr() << endl;

    if (bs == bs2)
        cout << "BitStrings are equal." << endl;
    else
        cout << "BitStrings are not equal." << endl;

    if (bs != bs2)
        cout << "BitStrings are not equal." << endl;
    else
        cout << "BitStrings are equal." << endl;

    return 0;
}

