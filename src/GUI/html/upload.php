<?php
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '<p><br><br><center><font face="����_GB2312"><b>���ȵ�½��</font></b><p>';
	    echo '<a href="login.html"><img border="0" src="image/goback.gif" width="40" height="40"></a>';
            echo '</center></body></html>';
            exit();			
	} 
?>
<html> 
<head> 
<title>���������ļ�</title> 
</head> 
<body background="image/pmiback.gif"> 
<? 
include "constant.php";

 
if ($_FILES[userfile] == "")
{ 
	die("û��ָ�����ص��ļ�");
}

echo "���سɹ�<p>\n";
echo "��ʱ�ļ���:" . $_FILES[userfile][tmp_name] . "<p>\n";
echo "�ļ���:" . $_FILES[userfile][name] . "<p>\n";
echo "�ļ���С:" . $_FILES[userfile][size] . "<p>\n";

$realfile=$_FILES[userfile][tmp_name] . "-" . $_FILES[userfile][name] ;
echo "����Ϊ:" . $realfile . "<p>\n";
$cmd=MYSUDO . "mv -f " . $_FILES[userfile][tmp_name] . " " . $realfile;
echo passthru($cmd);


echo "upgrade ... <p>\n";
$cmd=MYSUDO . "/usr/local/AOS/Bin/upgrade-ed " . $realfile;
echo passthru($cmd, $a);
if($a==0)
{
	echo "�����ɹ�<p>\n";
}
else
{
	echo "����ʧ��<p>\n";
}

echo "delete old files <p>\n";
$cmd=MYSUDO . "rm -f " . $realfile;
echo passthru($cmd);
?> 
</body> 
</html> 


