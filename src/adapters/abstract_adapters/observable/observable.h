
/*
 =================================================================================================================
 Name        : observable.h
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 09/06/2025
 Description : Observable
 =================================================================================================================
*/

#pragma once
#include <list>
#include <thread>
#include "interface_observable.h"
#include "../../../handlers/observer/observer.h"

class Observable : public InterfaceObservable
{
public:
    /**
     * Method to notify all observers
     */
    void notify_observers();
    /**
     * Method to synchronize all observer threads
     */
    void sync_threads();
    
    void add_observer(Observer* observer) override;
    void remove_observer(Observer* observer) override;
private:
    std::list<Observer*> observers_;
    std::list<std::thread> threads_;
};
