/*
 * collect.h
 *  Date: 
 *  Author: 
 *  Mail:
 *
*/

#ifndef STATS_COLLECT_H_
#define STATS_COLLECT_H_

#include "config.h"


#define NUM_START_TYPE (5)

typedef struct _REPORT {
	uint64 online;
} REPORT;

extern REPORT *report;

/**
 * ³õÊ¼»¯È«¾Öcollect
 */
sint32 init_collect();

sint32 start_collect_thread();

#endif /* STATS_COLLECT_H_ */
