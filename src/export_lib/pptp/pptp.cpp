/*
 * generated by genAPI.py
 * author: bill xia<xw_cn@163.com>
 */
#include "common.h"
#include "aos/aosReturnCode.h"
#include "aosApi.h"
#define MAX_BUFF_LEN 10240
/*
 * start pptp service
 */
int aos_api_pptp_start()
{
	OmnString rslt = "";
	char* tmp;
	char cmd[MAX_BUFF_LEN];

	sprintf(cmd, "pptp start ");

	OmnCliProc::getSelf()->runCliAsClient(cmd, rslt);
	tmp = rslt.getBuffer();
	tmp += rslt.find(0, false) + 1;

	return *((int*)tmp);
}

/*
 * stop pptp service
 */
int aos_api_pptp_stop()
{
	OmnString rslt = "";
	char* tmp;
	char cmd[MAX_BUFF_LEN];

	sprintf(cmd, "pptp stop ");

	OmnCliProc::getSelf()->runCliAsClient(cmd, rslt);
	tmp = rslt.getBuffer();
	tmp += rslt.find(0, false) + 1;

	return *((int*)tmp);
}

/*
 * set pptp local ip
 */
int aos_api_pptp_add_local_ip(char* str1)
{
	OmnString rslt = "";
	char* tmp;
	char cmd[MAX_BUFF_LEN];

	sprintf(cmd, "pptp local ip  %s ", str1);

	OmnCliProc::getSelf()->runCliAsClient(cmd, rslt);
	tmp = rslt.getBuffer();
	tmp += rslt.find(0, false) + 1;

	return *((int*)tmp);
}

/*
 * set pptp server ip range
 */
int aos_api_pptp_add_ip_range(char* str1, char* str2)
{
	OmnString rslt = "";
	char* tmp;
	char cmd[MAX_BUFF_LEN];

	sprintf(cmd, "pptp ip range  %s  %s ", str1, str2);

	OmnCliProc::getSelf()->runCliAsClient(cmd, rslt);
	tmp = rslt.getBuffer();
	tmp += rslt.find(0, false) + 1;

	return *((int*)tmp);
}

/*
 * add pptp account
 */
int aos_api_pptp_add_account(char* str1, char* str2, char* str3)
{
	OmnString rslt = "";
	char* tmp;
	char cmd[MAX_BUFF_LEN];

	sprintf(cmd, "pptp add user  %s  %s  %s ", str1, str2, str3);

	OmnCliProc::getSelf()->runCliAsClient(cmd, rslt);
	tmp = rslt.getBuffer();
	tmp += rslt.find(0, false) + 1;

	return *((int*)tmp);
}

/*
 * del a pptp account
 */
int aos_api_pptp_del_account(char* str1)
{
	OmnString rslt = "";
	char* tmp;
	char cmd[MAX_BUFF_LEN];

	sprintf(cmd, "pptp del user  %s ", str1);

	OmnCliProc::getSelf()->runCliAsClient(cmd, rslt);
	tmp = rslt.getBuffer();
	tmp += rslt.find(0, false) + 1;

	return *((int*)tmp);
}

/*
 * save current config
 */
int aos_api_pptp_save_config()
{
	OmnString rslt = "";
	char* tmp;
	char cmd[MAX_BUFF_LEN];

	sprintf(cmd, "pptp save config ");

	OmnCliProc::getSelf()->runCliAsClient(cmd, rslt);
	tmp = rslt.getBuffer();
	tmp += rslt.find(0, false) + 1;

	return *((int*)tmp);
}

/*
 * show current config
 */
int aos_api_pptp_retrieve_config(char* result, int* resultlen)
{
	OmnString rslt = "";
	char* tmp;
	char cmd[MAX_BUFF_LEN];
	int len;

	sprintf(cmd, "pptp show config ");

	OmnCliProc::getSelf()->runCliAsClient(cmd, rslt);
	len = strlen(rslt);
	if (len > *resultlen)
	{
		strncpy(result, rslt, *resultlen);
		return eAosRc_LenTooShort;
	}
	else
	{
		strcpy(result, rslt);
		*resultlen = len;}
	tmp = rslt.getBuffer();
	tmp += rslt.find(0, false) + 1;

	return *((int*)tmp);
}

/*
 * clear current config
 */
int aos_api_pptp_clear_config()
{
	OmnString rslt = "";
	char* tmp;
	char cmd[MAX_BUFF_LEN];

	sprintf(cmd, "pptp clear config ");

	OmnCliProc::getSelf()->runCliAsClient(cmd, rslt);
	tmp = rslt.getBuffer();
	tmp += rslt.find(0, false) + 1;

	return *((int*)tmp);
}

