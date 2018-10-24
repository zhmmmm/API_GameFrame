#ifndef __LUA_SWAPER_H__
#define __LUA_SWAPER_H__
#include "Frame.h"
////�õ�ָ������״̬
//int GetKeyState(unsigned char vk);
////�õ��������ڿͻ��˵�λ��
//bool GetCursor(int* x, int* y);
int L_GameInput_GetKeyState(lua_State* L)
{
	int vk = (unsigned char)lua_tointeger(L,1);
	int ret = GetKeyState(vk);
	lua_settop(L,0);
	lua_pushinteger(L,ret);
	return 1;//���return ��ʾ������lua�ű��е���L_GameInput_GetKeyState����
	//ʱ���м�������ֵ��
}

int L_GameInput_GetCursor(lua_State* L)
{
	int x,y=0;
	bool ret = g_GameInput->GetCursor(&x,&y);
	lua_pushboolean(L,ret);
	lua_pushinteger(L,x);
	lua_pushinteger(L,y);
	return 3;
	//lua�еĵ�����ʽ��ok,x,y =L_GameInput_GetCursor()
}

static const luaL_Reg gamefuncs[]={
	{"GameInput_GetKeyState",L_GameInput_GetKeyState},
	{"GameInput_GetCursor",L_GameInput_GetCursor},
	{NULL,NULL}
};

//�����������еĺ���ע�ᵽlua
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