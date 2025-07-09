
/*
 =================================================================================================================
 Name        : interface_observable.h
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 09/06/2025
 Description : Interface for observable
 =================================================================================================================
*/

#pragma once
#include "../../../handlers/observer/observer.h"

class InterfaceObservable
{
public:
    virtual ~InterfaceObservable() = default;

    /**
     * Interface method to add observer
     * @param observer observer to be added as pointer Observer
     */
    virtual void add_observer(Observer* observer) = 0;
    /**
     * Interface method to remove observer
     * @param observer observer to be removed as pointer Observer
     */
    virtual void remove_observer(Observer* observer) = 0;
};
