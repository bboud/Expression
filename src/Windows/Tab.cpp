//
// Created by Brandon Boudreaux on 3/21/23.
//

#include "Tab.h"

static void stackDump (lua_State *L) {
    int i;
    int top = lua_gettop(L);  /* depth of the stack */
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING: {  /* strings */
                printf("'%s'", lua_tostring(L, i));
                break;
            }
            case LUA_TBOOLEAN: {  /* Booleans */
                printf(lua_toboolean(L, i) ? "true" : "false");
                break; }
            case LUA_TNUMBER: {  /* numbers */
                printf("%g", lua_tonumber(L, i));
                break;
            }
            default: {  /* other values */
                printf("%s", lua_typename(L, t));
                break; }
        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}

namespace PhyG{

    void Tab::LoadTextIn() {
        std::ifstream is(path.string());

        if (is) {
            // get length of file:
            is.seekg(0, is.end);
            int length = is.tellg();
            is.seekg(0, is.beg);

            buffer = new char[buffer_size];

            // read data as a block:
            is.read(buffer, length);

            is.close();

            std::cout << buffer << std::endl;
        }
    }

    Tab::Tab(std::filesystem::path p, lua_State * L) {
        lua = L;
        tab_title = p.filename().string();
        path = p;

        LoadTextIn();

    }

    Tab::~Tab() {
        delete[] buffer;
    }

    void Tab::Render() {
        if(!opened){
            return;
        }
        if(ImGui::BeginTabItem(tab_title.c_str(), &opened, 0)){
            ImVec2 text_size = ImGui::GetContentRegionAvail();
            ImGui::InputTextMultiline("##code", buffer, buffer_size, ImVec2(text_size.x, text_size.y-30));

            if(ImGui::GetIO().KeySuper && ImGui::IsKeyPressed(ImGuiKey_S)){
                std::cout << "Saving " << tab_title << std::endl;

                std::ofstream ofs(path.string());

                ofs.write(buffer, buffer_size);

                ofs.close();

                LoadTextIn();
            }

            ImGui::Separator();

            if(ImGui::Button("Run!")){
                int lua_error = luaL_loadstring(lua, buffer) || lua_pcall(lua, 0, 0, 0);

                if(lua_error){
                    std::cerr << lua_tostring(lua, -1) << std::endl;
                    lua_pop(lua, 1);
                }
            }

            ImGui::EndTabItem();
        }
    }

    std::string Tab::GetName() {
        return tab_title;
    }
}

// PhyG