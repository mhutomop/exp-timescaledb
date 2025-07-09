
/*
 =================================================================================================================
 Name        : observer.h
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 09/06/2025
 Description : Observer
 =================================================================================================================
*/

#pragma once

class Observer
{
public:
    virtual ~Observer() = default;

    /**
    * Interface method to process updated data
    */
    virtual void update_data() = 0;
};
