<?
include "pmi_db.php";
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '<p><br><br><center><font face="����_GB2312"><b>���ȵ�½��</font></b><p>';
	    echo '<a href="login.html"><img border="0" src="image/goback.gif" width="40" height="40"></a>';
            echo '</center></body></html>';
            exit();			
	}
	write_ed();
	session_unregister("manager_ID");
?>
<html>
<head>
<meta http-equiv="refresh" content="1;url=login.html">
</head>
<body>
</body>
</html>
