#ifndef TTEXT_h
#define TTEXT_h
#include <string>
#include <algorithm>



class TText
{
protected:
    class Iterator;
    struct Node;
    Node* first;
    Node* end;
    Node* curr;
public:
    TText();
    ~TText();
    void Next();
    void Down();
    void push_back_current_level (std::string data);
    void push_back_next_level (std::string data);
    std::pair<int, std::string> pop();
    Iterator begin();
    Iterator last();
    void print();
    friend Iterator;
};

class TText::Iterator
{
public:
    Iterator next();

    // Вправо до последнего элемента
    Iterator endNext();
    Iterator nextLevel();

    // Вниз на уровень и вправо до последнего элемента
    Iterator endNextLevel();

    // Добавляет новый узел Node в next
    void insNext(std::string data);

    // Добавляет новый узел Node в down
    void insDown(std::string data);

    void Next();
    void Down();
    int current_level();
    std::string current_data();
    std::pair<int,std::string> current();

    Node *it;
    
    Node& operator*();
    Node* operator->();
    bool operator==(const Iterator& iterator);
    bool operator!=(const Iterator& iterator);
};

struct TText::Node {
    std::string data;
    Node* next;
    Node* down;
    int level;
};
#endif // TTEXT_h
