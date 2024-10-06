#pragma once
#include <algorithm>
#include <vector>
using std::vector;

class Observer{ //ferestrele
public:
    virtual void update()=0;
}; // clasa pur abstracta

class Observable{ //service -> este observabil ; de aici isi iau date observers, adica ferestrele
    vector<Observer*> interesati;
protected:
    void notify()
    {
        for(auto obs:interesati)
            obs->update();
    }
public:
    void add_observer(Observer *o)
    {
        interesati.push_back(o);
    }

};

// model -> observabil / service
// view -> observer / ferestre