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
<title>ϵͳ��־����</title>
</head>
<body  background="image/pmiback.gif">
<?php
include "constant.php";

$cmd=MYSUDO . "/etc/cron.daily/logcron";
exec($cmd);
$cmd=MYSUDO . "ln -sf /var/log/msg.gz /usr/local/AOS/GUI/html/aos.syslog";
exec($cmd);
?>
<img border="0" src="image/logdown.gif" width="283" height="57">
<p>
<center><font face="����_GB2312"><b>������,�Ƿ�����?</font></b></center>
<p>
<center><a href="aos.syslog">��  ��</a></center>
<center><a href='aos.syslog'><img border="0" src="image/goback.gif" width="40" height="40"></a>
</center>

</body>
</html>
