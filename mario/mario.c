/*
 * MarioTCP:  Multi Libvent TCP Server  一个高性能的TCP服务器
 *
 * mario.h
 *  名称：mario接口模块
 *  功能：mario高效网络处理功能的接口
 *
 *  Created on: 
 *      Author: 
 *        Mail: 
 *
 *  修改记录：
 */

#include "mario.h"

inline void regist_akg_func(uint16 id, FUNC_PTR func)
{
	AKG_FUNC[id] = func;
}

inline void regist_connected_func(FUNC_PTR func) 
{
	AKG_FUNC[g_akg_connected_id] = func;
}

inline void regist_disconnected_func(FUNC_PTR func) 
{
	AKG_FUNC[g_akg_timeout_id] = func;
	AKG_FUNC[g_akg_closed_id] = func;
	AKG_FUNC[g_akg_error_id] = func;
}

inline void regist_timeout_func(FUNC_PTR func) 
{
	AKG_FUNC[g_akg_timeout_id] = func;
}

inline void regist_closed_func(FUNC_PTR func) 
{
	AKG_FUNC[g_akg_closed_id] = func;
}

inline void regist_error_func(FUNC_PTR func) 
{
	AKG_FUNC[g_akg_error_id] = func;
}

inline void regist_stx(uint32 stx)
{
	g_stx = stx;
}
