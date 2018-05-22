#include "pda.h"


PDA::PDA()
{

}


override void PDA::addStato(std::string nome)
{
  if(!getStato(nome))
  {
    stati.push_back(StatoPDA(s));
  }
}

override void PDA::removeStato(std::string nome)
{
  bool eliminato = false;
  for(std::list<Stato>::iterator i = stati.begin();  i != stati.end() && !eliminato; i++)
  {
      if(i->getNome() == s)
      {
          if(partenza->getNome() == s)
              partenza = nullptr;
          stati.erase(i);
          eliminato = true;
      }
  }
}

override bool start(std::string)
{

}
