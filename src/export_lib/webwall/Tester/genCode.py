#!/usr/bin/python
import xml.dom.minidom
import sys

xmlPath = "API.xml"
xmlDoc = xml.dom.minidom.parse(xmlPath)
dstPath = "main.cpp"
f = open(dstPath, "w")
'''
parse api section
'''
allLines = "/*generated by gencode.py\n *author: bill xia\n */\n#include \"webwall.h\"\n#include <stdio.h>\n#include \"ParentCtrl/webwall_common.h\" \nint main()\n{"
allLines = allLines + "\n    char result[10240];\n    int ret;\n    int total_case;\n    int fail_case;\n"
apis = xmlDoc.getElementsByTagName("api");

for api in apis:
    '''
    build contents iteratively
    sp1: function name
    '''
    api_name = api.childNodes[1]
    prefix = ""
    prefix = "\n    ret = " + api_name.firstChild.data + '('
    
    testcases = api.getElementsByTagName("testcase")
    
    for testcase in testcases:
        expected = testcase.childNodes[3].firstChild.data
        caseId = testcase.childNodes[1].firstChild.data
        params = testcase.getElementsByTagName("param")
        counter = 0
        line = ""
        for param in params:
            if counter == 0:
                line = line + param.firstChild.data
            else:
                line = line + ", " + param.firstChild.data
            counter = counter + 1
        line = line + ");\n"
        
        allLines = allLines + prefix + line
        allLines = allLines + "    if (ret != " + expected + ") {\n        printf(\"caseId:" + caseId + "\tret = %d\tError\\n\", ret);\n        fail_case++;\n    }\n"
	allLines = allLines + "    total_case++;\n\n";

allLines = allLines + "    printf(\"total case: %d\\n fail case:%d\", total_case, fail_case);\n"
allLines = allLines + "    return 0;\n}\n"
f.write(allLines)
f.close()
        
