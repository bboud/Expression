//
// Created by Brandon Boudreaux on 3/21/23.
//

#ifndef GRAPHICS_LEXER_H
#define GRAPHICS_LEXER_H

#include "imgui.h"

namespace PhyG::Editor::Lexer {
        const char * Keywords[] = {
            "and", "break", "do", "else", "elseif", "end",
                    "false", "for", "function", "goto", "if", "in",
                    "local", "nil", "not", "or", "return", "repeat",
                    "then", "true", "until", "while"
        };

        const ImVec4 KeywordColor = ImVec4(0.0, 0.0, 0.0, 1.0);

        const char * Symbols[] = {
            "+", "-", "*", "/", "%", "^", "#",
                    "&", "~", "|", "<<", ">>", "//",
                    "==", "~=", "<=", ">=", "<", ">", "=",
                    "(", ")", "{", "}", "[", "]", "::",
                    ";", ":", ",", ".", "..", "..."
        };

        const ImVec4 SymbolsColor = ImVec4(0.0, 0.0, 0.0, 1.0);

        const char * BasicFunctions[] = {
            "assert", "collectgarbage", "dofile", "error", "_G",
                    "getmetatable", "ipairs", "load", "loadfile", "next",
                    "pairs", "pcall", "print", "rawequal", "rawget",
                    "rawlen", "rawset", "select", "setmetatable", "tonumber",
                    "tostring", "type", "_VERSION", "warn", "xpcall"
        };

        const ImVec4 BFunctionsColor = ImVec4(0.0, 0.0, 0.0, 1.0);

        const char * Numbers[] = {
            "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"
        };

        const ImVec4 NumbersColor = ImVec4(0.0, 0.0, 0.0, 1.0);
}


#endif //GRAPHICS_LEXER_H
