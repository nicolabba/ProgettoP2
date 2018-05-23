#include "transizionepda.h"

TransizionePDA::TransizionePDA(StatoPDA *s, char i, char h, char nh[]):Transizione(s, i), head(h)
{
    newHead[0] = nh[0];
    newHead[1] = nh[1];
}
char TransizionePDA::getHead(){
  return head;
}
char* TransizionePDA::getNewHead(){
  return newHead;
}
