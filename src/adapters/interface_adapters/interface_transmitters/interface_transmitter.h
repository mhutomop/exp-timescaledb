
/*
 =================================================================================================================
 Name        : interface_transmitter.h
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 09/06/2025
 Description : Interface for transmitter
 =================================================================================================================
*/

#pragma once
#include <cstddef>
#include <string>

class InterfaceTransmitter
{
public:
    virtual ~InterfaceTransmitter() = default;

    /**
     * Interface method to send message
     */
    virtual void send_message() = 0;
};
