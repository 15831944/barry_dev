<?php
include "constant.php";
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '<p><br><br><center><font face="����_GB2312"><b>���ȵ�½��</font></b><p>';
	    echo '<a href="login.html"><img border="0" src="image/goback.gif" width="40" height="40"></a>';
            echo '</center></body></html>';
            exit();			
	}
	
	//echo '<meta http-equiv="refresh" content="1;url=settime.php">';
	
	if($opnumb==1)
	{
		$tempstr=$roolminu." ".$roolhour." * * * root /sbin/reboot -f";
		$cmd=MYSUDO."echo \"'".$tempstr."'\" \>".CRONTAB;
		exec($cmd);
		//write_ed();
	}
	if($opnumb==2)
	{
		$cmd=MYSUDO."echo \"'#a'\" \>".CRONTAB;
		exec($cmd);
		//write_ed();
	}

	echo '<html>';
	echo '<head>';
	echo '<meta http-equiv="refresh" content="1;url=settime.php">';
	echo '</head>';
	echo '<body>';
	echo '</body>';
	echo '</html>';
	
?>
