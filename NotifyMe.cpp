// Observer Pattern

#include <bits/stdc++.h>
using namespace std;

class StocksObserverInterface{
public:
    virtual void update(string &messageFromObservable) = 0;
};

class StocksObservableInterface{
public:

    virtual void add(StocksObserverInterface *observer) = 0;
    virtual void remove(StocksObserverInterface *observer) = 0;
    virtual void notify() = 0;
    virtual void setStockcount(int count) = 0;
};

class StocksObserver : public StocksObserverInterface{
private:
    string email_id;
    StocksObservableInterface *observable;
public:
    StocksObserver(string email, StocksObservableInterface* observable) : email_id(email), observable(observable) {
        this->observable->add(this);
        cout<<"I am subscribed to email notifications."<<endl;
    }
    void update(string &messageFromObservable){
        cout<<"Mail sent to " + email_id + ": " + messageFromObservable<<endl;
    }
     void unsubscribe(){
        this->observable->remove(this);
     }
};



class StocksObservable : public StocksObservableInterface{
    int stockCount = 0;
    list<StocksObserverInterface*> observerList;
public:
    void add(StocksObserverInterface *observer) override{
        observerList.push_back(observer);
    }
    void remove(StocksObserverInterface *observer) override{
        observerList.remove(observer);
    }
    void notify(){
        auto it = this->observerList.begin();
        string message = "Hurry Up! The product u wishlisted is back in stock.";
        while(it!=this->observerList.end()){
            (*it)->update(message);
            it++;
        }

    }
    void setStockcount(int count){
        this->stockCount = count;
        if(this->stockCount!=0) notify();
    }
};



int main(){
    StocksObservable *iphone = new StocksObservable();
    StocksObservable *samsung = new StocksObservable();
    StocksObserver *ob1 = new StocksObserver("ob1@gmail.com", iphone);
    StocksObserver *ob2 = new StocksObserver("ob2@gmail.com", iphone);
    StocksObserver *ob3 = new StocksObserver("ob3@gmail.com", samsung);
    iphone->setStockcount(10);
    samsung->setStockcount(5);
    ob2->unsubscribe();
    iphone->setStockcount(10);
    return 0;
}