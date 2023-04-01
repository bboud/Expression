//
// Created by Brandon Boudreaux on 3/25/23.
//

#ifndef GRAPHICS_CONSOLE_H
#define GRAPHICS_CONSOLE_H

#include "../Window.h"

namespace Expression {

    class Console : public Window{
    public:
        Console(bool *o);
        ~Console();
    };

} // Expression

#endif //GRAPHICS_CONSOLE_H
