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

        echo '<html><head><meta http-equiv="refresh" content="30;url=shutdown.php"><title>���������������</title></head><body  background="image/pmiback.gif">' ;	
	echo "<p><br><br><center><font face=\"����_GB2312\"><b>���������������������".$ln;
        echo "�����ĵȴ�...</b></font></center>".$ln;
        
	echo "ִ�н����".'<hr>';
	$a="";
	echo "<p><pre>\n";
	$cmd=MYSUDO."/etc/init.d/aos-script stop";
	echo passthru($cmd,$a);
	$cmd=MYSUDO."/etc/init.d/aos-script start";
	echo passthru($cmd,$a);
	echo "\n";
	echo "</pre>";
	
    echo '</body></html>';
?>
