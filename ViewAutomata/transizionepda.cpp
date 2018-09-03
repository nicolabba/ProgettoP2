#include "transizionepda.h"

TransizionePDA::TransizionePDA(StatoPDA *s, char i, char h, const std::string &nh):Transizione(s, i), head(h)
{
    if(nh.length() <= 2)
        newHead = nh;
}
char TransizionePDA::getHead(){
  return head;
}
std::string TransizionePDA::getNewHead(){
  return newHead;
}
