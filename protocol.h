/*
 * protocol.h
 *	
 *  名称：
 *  
 *  Date: 
 *  Author: 
 *  Mail: 
 *
 *  修改记录：
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "mario/mario.h"

typedef enum _CMD {
	CMD_FUNCTION_BASE = 0x6100,
	CMD_FUNCTION_LOGIN = 0x6101,
} CMD;

typedef enum _CODE_RSP {
	CODE_ACCPET = 200, CODE_DENNY = 400
} CODE_RSP;

#pragma pack(1)
/*用户登录协议*/
typedef struct _LOGIN_REQ {
	uint16_t uid;
} LOGIN_REQ;

typedef struct _LOGIN_RSP {
} LOGIN_RSP;
#pragma pack()

#endif /* PROTOCOL_H_ */
