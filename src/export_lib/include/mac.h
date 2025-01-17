/*
 * generated by genAPI.py
 * author: bill xia<xw_cn@163.com>
 */
#ifndef AOS_RHC_MAC_API_H
#define AOS_RHC_MAC_API_H
#include "aosReturnCode.h"
enum
{
	eAosRc_MacNotChanged = 119001,
};


/*
 * clone device mac
 */
extern int aos_mac_set(char*, char*);
/*
 *  restores an interface's MAC address.
 */
extern int aos_mac_restore(char*);
/*
 *  get an interface's MAC address.
 */
extern int aos_mac_get(char* ,char*, int*);
/*
 * save current mac config
 */
extern int aos_mac_clone_save_config();
/*
 * load current mac config
 */
extern int aos_mac_clone_load_config();
/*
 * show mac  config
 */
extern int aos_mac_clone_retrieve_config(char*, int*);
/*
 * clear current mac config
 */
extern int aos_mac_clone_clear_config();
#endif
