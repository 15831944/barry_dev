<?php
include("constant.php");
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '<p><br><br><center><font face="����_GB2312"><b>���ȵ�½��</font></b><p>';
	    echo '<a href="login.html"><img border="0" src="image/goback.gif" width="40" height="40"></a>';
            echo '</center></body></html>';
            exit();			
	}
        echo '<html><head><meta http-equiv="refresh" content="60;url=shutdown.php"><title>��������������</title></head><body  background="image/pmiback.gif">' ;	
	echo "<p><br><br><center><font face=\"����_GB2312\"><b>�����������������������".$ln;
        echo "�����ĵȴ�...</b></font>".$ln;
//	register_shutdown_function(MyReboot);
        echo '</center></body></html>';
        
        //-------------------------20060101;by yt;reboot
        exec(MYSUDO . " /sbin/reboot -f");
        //-------------------------20060101;by yt;reboot
?>
