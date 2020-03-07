#include <iostream>

int main() {

    std::ios_base::sync_with_stdio(false); //garantee that iostreams are not synchronized with stdin or stdout
    std::locale loc("zh_CN.utf8"); //set the character set to zh_CN.utf8
    std::wcin.imbue(loc); //set the locale of wcin and wcout
    std::wcout.imbue(loc);
    wchar_t *c = L"汉";
    std::wcout << c << std::endl;
    return 0;
}
