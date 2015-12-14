/*generated by gencode.py
 *author: bill xia
 */
#include "webwall.h"
#include <stdio.h>
int main()
{
    char result[10240];
    int ret;
    int total_case = 0;
    int fail_case = 0;
    int len = 10240;

    ret = aos_ww_api_set_proxy_addr("172.22.0.1", 3128);
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:1	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_proxy_addr("172.22.0.345", 3128);
    if (ret != -eAosRc_WWIPFormat) {
        printf("caseId:2	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_proxy_addr("172.22.0.345", -1);
    if (ret != -eAosRc_WWPortFormat) {
        printf("caseId:3	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_proxy_action("start");
    if (ret != -eAosRc_WWFailAction) {
        printf("caseId:4	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_proxy_action("on");
    if (ret != -eAosRc_WWUnsupportActionType) {
        printf("caseId:5	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;

    len = 10240;
    ret = aos_ww_api_proxy_retrieve_config(result, &len);
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:6	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_access_denied_addr("http://172.22.0.1/denypage.html");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:6	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_cli_set_language("danish");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:8	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_cli_set_language("mylanguage");
    if (ret != -eAosRc_WWUnsupportLanguageType) {
        printf("caseId:9	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_log_level(2);
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:10	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_log_level(9);
    if (ret != -eAosRc_WWInvalidLogLevel) {
        printf("caseId:11	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_log_exception_hits("on");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:11	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_log_exception_hits("open");
    if (ret != -eAosRc_WWInvalidSwitch) {
        printf("caseId:12	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_log_file_format(2);
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:13	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_log_file_format(100);
    if (ret != -eAosRc_WWInvalidLogFileFormat) {
        printf("caseId:14	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_max_log_item_len(200);
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:15	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_max_log_item_len(-1000);
    if (ret != -eAosRc_WWInvalidLogItemLength) {
        printf("caseId:16	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_anonymous_log("on");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:17	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_anonymous_log("open");
    if (ret != -eAosRc_WWInvalidSwitch) {
        printf("caseId:18	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_ip_and_port_of_webwall("172.22.0.1", 8080);
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:19	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_ip_and_port_of_webwall("12.4324.23.242", 8080);
    if (ret != -eAosRc_WWIPFormat) {
        printf("caseId:20	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_reporting_level(1);
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:21	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_reporting_level(100);
    if (ret != -eAosRc_WWInvalidReportingLevel) {
        printf("caseId:22	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_filter_group_len(5);
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:23	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_filter_group_len(11);
    if (ret != -eAosRc_WWInvalidGroupLength) {
        printf("caseId:24	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_show_weighted_found("on");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:25	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_show_weighted_found("open");
    if (ret != -eAosRc_WWInvalidSwitch) {
        printf("caseId:26	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_weighted_phrase_mode(1);
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:27	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_weighted_phrase_mode(5);
    if (ret != -eAosRc_WWInvalidWeightedPhraseMode) {
        printf("caseId:28	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_auth_plugins("ip");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:29	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_auth_plugins("myip");
    if (ret != -eAosRc_WWInvalidPlugin) {
        printf("caseId:30	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_auth_plugin("ip");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:31	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_auth_plugin("myip");
    if (ret != -eAosRc_WWInvalidPlugin) {
        printf("caseId:32	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_reverse_addr_lookups("on");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:33	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_reverse_addr_lookups("open");
    if (ret != -eAosRc_WWInvalidSwitch) {
        printf("caseId:34	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_reverse_client_hostname("on");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:35	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_reverse_client_hostname("open");
    if (ret != -eAosRc_WWInvalidSwitch) {
        printf("caseId:36	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_reverse_clientip_lookups("on");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:37	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_reverse_clientip_lookups("open");
    if (ret != -eAosRc_WWInvalidSwitch) {
        printf("caseId:38	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_named_user("group1", "jim");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:39	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_named_user("group100", "jim");
    if (ret != -eAosRc_WWInvalidGroupID) {
        printf("caseId:40	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_named_user("group1", "jim");
    if (ret != -eAosRc_WWExistNamedUser) {
        printf("caseId:41	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_named_user("group1", "jim");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:42	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_named_user("group100", "jim");
    if (ret != -eAosRc_WWInvalidGroupID) {
        printf("caseId:43	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_named_user("group1", "jim");
    if (ret != -eAosRc_WWNoexistNamedUser) {
        printf("caseId:44	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;

    len = 10240;
    ret = aos_ww_api_retrieve_named_user("group1", result, &len);
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:45	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_all_named_users("group1");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:46	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_all_named_users("group100");
    if (ret != -eAosRc_WWInvalidGroupID) {
        printf("caseId:47	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_ip_user("group1", "172.22.0.1");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:48	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_ip_user("group100", "172.22.0.1");
    if (ret != -eAosRc_WWInvalidGroupID) {
        printf("caseId:49	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_ip_user("group1", "172.22.0.1");
    if (ret != -eAosRc_WWExistIPUser) {
        printf("caseId:50	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_ip_user("group1", "172.22.0.1");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:51	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_ip_user("group100", "172.22.0.1");
    if (ret != -eAosRc_WWInvalidGroupID) {
        printf("caseId:52	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_ip_user("group1", "172.22.0.1");
    if (ret != -eAosRc_WWNoexistIPUser) {
        printf("caseId:53	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;

    len = 10240;
    ret = aos_ww_api_retrieve_ip_user("group1", result, &len);
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:54	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_all_ip_users("group1");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:54	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_all_ip_users("group100");
    if (ret != -eAosRc_WWInvalidGroupID) {
        printf("caseId:55	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_filter_group_mode("group1", "banned");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:56	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_filter_group_mode("group100", "banned");
    if (ret != -eAosRc_WWInvalidGroupID) {
        printf("caseId:57	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_filter_group_mode("group1", "mybanned");
    if (ret != -eAosRc_WWUnsupportGroupModeType) {
        printf("caseId:58	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_filter_group_name("group1", "test");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:59	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_filter_group_name("group100", "test");
    if (ret != -eAosRc_WWInvalidGroupID) {
        printf("caseId:60	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;

    len = 10240;
    ret = aos_ww_api_retrieve_category_list_of_filter_group("group1", result, &len);
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:61	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_group("group2");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:62	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_group("group100");
    if (ret != -eAosRc_WWInvalidGroupID) {
        printf("caseId:63	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_group("group2");
    if (ret != -eAosRc_WWExistGroup) {
        printf("caseId:64	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_group("group2");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:65	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_group("group100");
    if (ret != -eAosRc_WWInvalidGroupID) {
        printf("caseId:66	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_group("group2");
    if (ret != -eAosRc_WWNoexistGroup) {
        printf("caseId:67	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_category_list("bannedsitelist", "test");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:68	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_category_list("bannedsitelist", "newlist");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:68	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_category_list("mybannedsitelist", "test");
    if (ret != -eAosRc_WWUnsupportListType) {
        printf("caseId:69	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_category_list("bannedsitelist", "test");
    if (ret != -eAosRc_WWExistListName) {
        printf("caseId:70	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_category_list("test");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:71	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_category_list("test");
    if (ret != -eAosRc_WWNoexistListName) {
        printf("caseId:72	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_category_list("bannedsitelist");
    if (ret != -eAosRc_WWInUse) {
        printf("caseId:73	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_category_list("exceptionvirusurllist");
    if (ret != -eAosRc_WWCanNotRemove) {
        printf("caseId:74	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_time("newlist", "12:45", "18:20", "0123");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:75	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_time("test1", "12:45", "18:20", "0123");
    if (ret != -eAosRc_WWNoexistListName) {
        printf("caseId:76	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_set_time("newlist", "12:450", "18:280", "0123");
    if (ret != -eAosRc_WWTimeFormat) {
        printf("caseId:77	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_time("newlist");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:78	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_time("test");
    if (ret != -eAosRc_WWNoexistListName) {
        printf("caseId:79	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_alias("newlist", "alias");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:80	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_alias("test", "alias");
    if (ret != -eAosRc_WWNoexistListName) {
        printf("caseId:81	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_alias("newlist");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:82	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_alias("test");
    if (ret != -eAosRc_WWNoexistListName) {
        printf("caseId:83	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_alias("newlist");
    if (ret != -eAosRc_WWNoexistAaliasName) {
        printf("caseId:84	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_single_entry("newlist", "sina.com.cn");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:85	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_single_entry("test", "sina.com.cn");
    if (ret != -eAosRc_WWNoexistListName) {
        printf("caseId:86	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_single_entry("newlist", "sina.com.cn");
    if (ret != -eAosRc_WWExistEntry) {
        printf("caseId:87	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_single_entry("newlist", "sina.com.cn");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:88	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_single_entry("test", "sina.com.cn");
    if (ret != -eAosRc_WWNoexistListName) {
        printf("caseId:89	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_single_entry("newlist", "baidu.com.cn");
    if (ret != -eAosRc_WWNoexistEntry) {
        printf("caseId:90	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_include_entry_file("newlist", "normal", "mylist");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:91	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_include_entry_file("test", "normal", "mylist");
    if (ret != -eAosRc_WWNoexistListName) {
        printf("caseId:92	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_include_entry_file("newlist", "normaltest", "mylist");
    if (ret != -eAosRc_WWUnsupportEntryType) {
        printf("caseId:93	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_create_include_entry_file("newlist", "normal", "mylist");
    if (ret != -eAosRc_WWExistIncludeEntryFile) {
        printf("caseId:94	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_include_entry_file("newlist", "mylist");
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:95	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_include_entry_file("test", "mylist");
    if (ret != -eAosRc_WWNoexistListName) {
        printf("caseId:96	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;


    ret = aos_ww_api_remove_include_entry_file("newlist", "mylisttest");
    if (ret != -eAosRc_WWNoexistIncludeEntryFile) {
        printf("caseId:97	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;

    len = 10240;
    ret = aos_ww_api_retrieve_category_list("newlist", result, &len);
    if (ret != eAosRc_WWSuccess) {
        printf("caseId:98	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;

    len = 10240;
    ret = aos_ww_api_retrieve_category_list("test", result, &len);
    if (ret != -eAosRc_WWNoexistListName) {
        printf("caseId:99	ret = %d	Error\n", ret);
        fail_case++;
    }
    total_case++;

    printf("total case: %d\n fail case:%d", total_case, fail_case);
    return 0;
}