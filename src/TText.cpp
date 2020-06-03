#include <vector>
#include <iostream>

#include <include/TText.h>

TText::TText()
{
  first = end = curr = nullptr;
}

TText::~TText()
{
  if (end != nullptr) 
  {
    while (end != nullptr) 
    {
      // Очищаем память
      pop();
    }
  }
}

void TText::Next()
{
  if (curr->next == nullptr)
  {
    throw "Next is null";
  }
  curr = curr->next;
}

void TText::Down()
{
  if (curr->down == nullptr) 
  {
    throw "Down is null";
  }
  curr = curr->down;
}

/* 
  С помощью итератора проходим до конца уровня и вставляем новый узел Node
*/
void TText::push_back_current_level(std::string data)
{
  if (first == nullptr)
  {
    first = new Node();
    first->level = 0;
    first->data = data;
    first->next = nullptr;
    first->down = nullptr;
    curr = end = first;
  }
  else 
  {
    Iterator iter;
    iter.it = curr;
    iter = iter.endNext();
    iter.insNext(data);
    if (iter.current_level()==0 || iter.current_data() == end->data) 
    {
      end = end->next;
    }
  }
}

/* 
  С помощью итератора опускаемся на уровень вниз, проходим до конца уровня
  и вставляем новый узел Node
*/
void TText::push_back_next_level(std::string data)
{
  if (first == nullptr)
  {
    first = new Node();
    first->level = 0;
    first->data = "";
    first->next = nullptr;
    first->down = new Node();
    first->down->data = data;
    first->down->level = 1;
    first->down->next = nullptr;
    first->down->down = nullptr;
    curr = end= first->down;
  }
  Iterator iter;
  iter.it = curr;
  if (end->data == iter.endNextLevel().it->data)
  {
    iter.insDown(data);
    end = end->down;
  }
  else 
  {
    iter.insDown(data);
    if (curr == end)
    {
      end = end->down;
    }
  }
}


/*
  Удаляем Node, заменив указатели на указатели выше и ниже стоящих
*/
std::pair<int, std::string> TText::pop()
{
  if (first == end)
  {
    std::cout << end->level << " " << end->data << "\n";
    delete end;
    first = end = curr = nullptr;
    return std::pair<int, std::string>(0, "");
  }

  Iterator iter;
  std::pair<int, std::string> tmp;
  iter.it = first;
  std::vector<Node*> vec;

  while (iter.it->next != nullptr)
  {
    vec.push_back(iter.it);
    if (iter.it->down != nullptr)
    {
      Iterator localIter;
      localIter.it = iter.it->down;
      while (localIter.it->next != nullptr)
      {
        vec.push_back(localIter.it);
        localIter.Next();
      }
      vec.push_back(localIter.it);
    }

    Node* t = iter.it->next;
    if (iter.it->next == end)
    {
      iter.it->next = nullptr;
    }
    iter.it = t;
  }

  vec.push_back(iter.it);
  if (iter.it->down != nullptr)
  {
    Iterator localIter;
    localIter.it = iter.it->down;

    while (localIter.it->next != nullptr)
    {
      vec.push_back(localIter.it);
      localIter.Next();
    }

    vec.push_back(localIter.it);
  }

  tmp = { 
    vec[vec.size() - 1]->level,
    vec[vec.size() - 1]->data 
  };

  vec.pop_back();
  if (curr == end)
  {
    curr = vec[vec.size()-1];
  }
  delete end;
  end = vec[vec.size() - 1];
  end->next = nullptr;
  end->down = nullptr;
  std::cout << tmp.first << " " << tmp.second << "\n";
  return tmp;
}

TText::Iterator TText::begin()
{
  Iterator iter;
  iter.it = first;
  return iter;
}

TText::Iterator TText::last()
{
  Iterator iter;
  iter.it = end;
  return iter;
}

/* 
  Проходит по тексту и печатает, начиная с начала.
  Разделяет текст на абзцац и строки.

*/
void TText::print()
{
  if (first == nullptr) 
  {
    return;
  }

	Iterator iter;
	iter.it = first;

	do
  {
    std::cout << iter.it->data << std::endl;
    if (iter.it->down != nullptr) 
    {
      Iterator localIter;
      localIter.it = iter.it->down;

      while (localIter.it->next != nullptr)
      {
        std::cout << localIter.it->data << std::endl;
        localIter.Next();
      } 
      std::cout << localIter.it->data << std::endl;
    }
    iter.Next();

  } while (iter.it->next != nullptr);

  std::cout << iter.it->data << std::endl;
  if (iter.it->down != nullptr)
  {
    Iterator localIter;
    localIter.it = iter.it->down;

    while (localIter.it->next != nullptr)
    {
      std::cout << localIter.it->data << std::endl;
      localIter.Next();
    }

    std::cout << localIter.it->data << std::endl;
  }
}

TText::Node& TText::Iterator::operator*()
{
    return *it;
}

TText::Node* TText::Iterator::operator->()
{
    return it;
}

TText::Iterator TText::Iterator::next()
{
    Iterator iter;
    iter.it=it->next;
    return iter;
}

TText::Iterator TText::Iterator::endNext()
{
    Iterator iter;
    iter.it = it;
    while (iter.it->next != nullptr)
    {
        iter.it=iter.it->next;
    }
    return iter;
}

TText::Iterator TText::Iterator::nextLevel()
{
    Iterator iter;
    iter.it=it->down;
    return iter;
}

TText::Iterator TText::Iterator::endNextLevel()
{
    Iterator iter;
    if (it->down == nullptr) 
    {
      return *this;
    }

    iter.it=it->down;
    while (iter.it->next)
    {
        iter.it=iter.it->next;
    }
    return iter;
}

/*
  Вставить после текущей позиции справа
*/
void TText::Iterator::insNext(std::string data)
{
  Iterator iter;
  iter.it = it;
  Node* tmp = new Node();
  tmp->data = data;
  tmp->down = nullptr;
  tmp->level = it->level;
  tmp->next = it->next;
  it->next = tmp;
}


/*
  Вставить вниз со смещением
*/
void TText::Iterator::insDown(std::string data)
{
  Iterator iter;
  iter.it = it;
  if (it->level == 1)
  {
    throw "Can't create a level lower";
  }

  if (it->down == nullptr)
  {
    Node* tmp = new Node();
    tmp->data = data;
    tmp->down = nullptr;
    tmp->level = it->level + 1;
    tmp->next = nullptr;
    it->down = tmp;
  }
  else 
  {
    iter = iter.nextLevel();
    iter = iter.endNext();
    Node* tmp = new Node();
    tmp->data = data;
    tmp->down = nullptr;
    tmp->level = it->level + 1;
    tmp->next = nullptr;
    iter.it->next = tmp;
  }
}

void TText::Iterator::Next()
{
  if (it->next == nullptr)
  {
    return;
  }

  it = it->next;
}

void TText::Iterator::Down()
{
  if (it->down == nullptr)
  {
    return;
  }

  it = it->down;
}

int TText::Iterator::current_level()
{
    return it->level;
}

std::string TText::Iterator::current_data()
{
    return it->data;
}

std::pair<int, std::string> TText::Iterator::current()
{
    return {
      it->level,
      it->data
    };
}

bool TText::Iterator::operator==(const Iterator &iterator)
{
  return it->data == iterator.it->data;
}

bool TText::Iterator::operator!=(const Iterator &iterator)
{
  return it->data != iterator.it->data;
}