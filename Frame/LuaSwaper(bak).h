#ifndef __LUA_SWAPER_H__
#define __LUA_SWAPER_H__
#include "Frame.h"
////得到指定键的状态
//int GetKeyState(unsigned char vk);
////得到光标相对于客户端的位置
//bool GetCursor(int* x, int* y);
int L_GameInput_GetKeyState(lua_State* L)
{
	int vk = (unsigned char)lua_tointeger(L,1);
	int ret = GetKeyState(vk);
	lua_settop(L,0);
	lua_pushinteger(L,ret);
	return 1;//这个return 表示的是在lua脚本中调用L_GameInput_GetKeyState函数
	//时，有几个返回值。
}

int L_GameInput_GetCursor(lua_State* L)
{
	int x,y=0;
	bool ret = g_GameInput->GetCursor(&x,&y);
	lua_pushboolean(L,ret);
	lua_pushinteger(L,x);
	lua_pushinteger(L,y);
	return 3;
	//lua中的调用形式：ok,x,y =L_GameInput_GetCursor()
}

static const luaL_Reg gamefuncs[]={
	{"GameInput_GetKeyState",L_GameInput_GetKeyState},
	{"GameInput_GetCursor",L_GameInput_GetCursor},
	{NULL,NULL}
};

//将数组中所有的函数注册到lua
void RegGameFuncs2Lua(lua_State* L)
{
	int i = 0;
	while (gamefuncs[i].name!=NULL)
	{
		lua_register(L,gamefuncs[i].name,gamefuncs[i].func);
		++i;
	}
}


#endif