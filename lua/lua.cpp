extern "C" {
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}

#include <iostream>
#include <string>
using namespace std;

int main()
{
    lua_State* lua = lua_open();
    luaL_openlibs(lua);

    luaL_dofile(lua, "hello.lua");

    lua_close(lua);

    return 0;
}
