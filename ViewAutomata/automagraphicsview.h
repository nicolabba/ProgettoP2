#ifndef AUTOMAGRAPHICSVIEW_H
#define AUTOMAGRAPHICSVIEW_H

#include <QGraphicsView>
#include "abstractautoma.h"
#include "statographicsitem.h"
#include "transizionegraphicsitem.h"
#include <QVector>
#include <list>

class AutomaGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    enum AutomaType
    {
        DFA,
        NFA,
        PDA
    };
    AutomaGraphicsView(QWidget * = nullptr, AutomaType = NFA);
    AutomaType getCurrentType() const;
    bool check(const std::string&) const;
    void changeType(AutomaType);
    void addStato(const std::string&, bool = false, bool = false, int = 0, int = 0);
    void addTransizione(const std::string&, const std::string&, const char&, const char& = '\0', const std::string& = " \0");
    void removeStato(const std::string&);
    void removeTransizione(const std::string&, const std::string&, const char&, const char& = '\0', const std::string& = " \0");
    void setAlfabetoDFA(const std::string&);
    void update();
    bool doesStatoExist(const std::string&) const;
    bool doesTransizioneExist(const std::string&, const std::string&) const;
    void setStartingState(const std::string&);
    void setFinal(const std::string&, bool);
    std::list<std::string> *getStatesName() const;
    std::string getAlphabet() const;
    char getEpsilon() const;
    void setEpsilon(char) const;
    void reset(AutomaType = NFA, std::string = "", char = '\0');
private:
    AutomaType currentType;
    AbstractAutoma* automa;
    QGraphicsScene* scene;
    QVector<StatoGraphicsItem*> stati;
    QVector<TransizioneGraphicsItem*> transizioni;
    void mouseMoveEvent(QMouseEvent*);
    void resizeEvent(QResizeEvent*);
    void removeTransizioni(const std::string&, const std::string&);

public slots:
    void editAutoma();
    void removeSelected();
    void editSelected();
};

#endif // AUTOMAGRAPHICSVIEW_H
