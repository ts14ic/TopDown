//
// Created by ts14ic on 12/2/17.
//

#pragma once

class Resources;

class Texture;

class Box;

class Color;

class GraphicContext {
public:
    virtual ~GraphicContext() = 0;

    virtual void refreshScreen() = 0;

    virtual void clearScreen() = 0;

    virtual void renderBox(const Box& box, const Color& color) = 0;

    virtual void render(Texture const& texture, int x, int y) = 0;

    virtual void render(Texture const& texture, int x, int y, float angle) = 0;

    virtual int getScreenWidth() = 0;

    virtual int getScreenHeight() = 0;
};