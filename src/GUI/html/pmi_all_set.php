<?php

@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/backgroud.gif"><b>' ;
	    echo '���ȵ�½��<p>';
	    echo '<a href="login.html">����</a>';
            echo '</b></body></html>';
            exit();			
	}

include("constant.php");

if ($op == 0)
{
	$fp=fopen("/tmp/".$appid.".DepName","w");
	if ($fp)
	{
		fwrite($fp,$depname,strlen($depname));
		fclose($fp);
	}
	$fp=fopen("/tmp/".$appid.".AppName","w");
	if ($fp)
	{
		fwrite($fp,$appname,strlen($appname));
		fclose($fp);
	}
	$cmd=SUDO.MOUNT_CMD;
	$ret=system($cmd,$a);

	$cmd=SUDO."cp "."/tmp/".$appid.".DepName"." ".MOUNT_PATH."SSLMPS/Config/".$appid.".DepName";
	$ret=system($cmd,$a);
	$cmd=SUDO."cp "."/tmp/".$appid.".AppName"." ".MOUNT_PATH."SSLMPS/Config/".$appid.".AppName";
	$ret=system($cmd,$a);

	$cmd=SUDO.UMOUNT_CMD;
	$ret=system($cmd,$a);
	
	$cmd=SUDO."cp "."/tmp/".$appid.".DepName"." /usr/SSLMPS/Config/".$appid.".DepName";
	$ret=system($cmd,$a);
	$cmd=SUDO."cp "."/tmp/".$appid.".AppName"." /usr/SSLMPS/Config/".$appid.".AppName";
	$ret=system($cmd,$a);

	echo "����PMIͳһ��Ȩ���ʿ��ƣ����ɹ�<br>";
	echo "��λ���ƣ�$depname<br>";
	echo "Ӧ��ϵͳ���ƣ�$appname<br>";
}
else if ($op == 1)
{
	$cmd=SUDO."rm -f /usr/SSLMPS/Config/".$appid.".DepName";
	$ret=system($cmd);
	$cmd=SUDO."rm -f /usr/SSLMPS/Config/".$appid.".AppName";
	$ret=system($cmd);

	$cmd=SUDO.MOUNT_CMD;
	$ret=system($cmd,$a);

	$cmd=SUDO."rm -f ".MOUNT_PATH."SSLMPS/Config/".$appid.".DepName";
	$ret=system($cmd,$a);
	$cmd=SUDO."rm -f ".MOUNT_PATH."SSLMPS/Config/".$appid.".AppName";
	$ret=system($cmd,$a);

	$cmd=SUDO.UMOUNT_CMD;
	$ret=system($cmd,$a);
	echo "����PMIͳһ��Ȩ���ʿ��ƣ����ɹ�";
}
?>