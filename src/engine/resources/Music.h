//
// Created by ts14ic on 12/3/17.
//
#pragma once

class Music {
public:
    virtual ~Music() = 0;

    virtual bool isLoaded() const = 0;
};
