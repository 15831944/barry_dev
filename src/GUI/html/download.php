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
<body  background="image/pmiback.gif">
<?php
include "constant.php";


$cmd=MYSUDO . "/usr/local/AOS/Bin/tar-conf-ed /usr/local/AOS/GUI/html/confile.tar.gz";
exec($cmd);
?>
<p>
<center><font face="����_GB2312"><b>�ļ�������,�Ƿ�����?</font></b></center>
<p>
<center><a href="confile.tar.gz">��  ��</a></center>
<center><a href='confile.php'><img border="0" src="image/goback.gif" width="40" height="40"></a>
</center>

</body>
</html>
