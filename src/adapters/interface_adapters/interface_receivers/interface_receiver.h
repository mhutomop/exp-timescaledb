
/*
 =================================================================================================================
 Name        : interface_receiver.h
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 09/06/2025
 Description : Interface for receiver
 =================================================================================================================
*/

#pragma once

class InterfaceReceiver
{
public:
    virtual ~InterfaceReceiver() = default;

    /**
     * Interface method to start receiver
     */
    virtual void start() = 0;
    /**
     * Interface method to stop receiver
     */
    virtual void stop() = 0;
};
