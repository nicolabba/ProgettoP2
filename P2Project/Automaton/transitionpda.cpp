#include "transitionpda.h"

TransitionPDA::TransitionPDA(StatePDA *s, char i, char h, const std::string &nh):Transition(s, i), head(h)
{
    if(nh.length() <= 2)
        newHead = nh;
}
char TransitionPDA::getHead(){
  return head;
}
std::string TransitionPDA::getNewHead(){
  return newHead;
}
