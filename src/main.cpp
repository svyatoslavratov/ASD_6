#include <iostream>

#include <include/TText.h>

using namespace std;


int main()
{
    TText text;
    
    text.push_back_current_level("A");
    text.push_back_current_level("B");
    text.push_back_current_level("C");
    text.push_back_next_level("D");
    text.push_back_next_level("E");
    text.Next();
    text.push_back_next_level("F");
    text.Next();
    text.push_back_next_level("G");
    text.Down();
    text.push_back_current_level("H");
    text.print();

    system("pause");
    return 0;
}
