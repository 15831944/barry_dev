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
<body> 
<? 
include "constant.php";
/*
//����������
 	$cmd=SUDO."mount /dev/hda2 /mnt/data";
  //	echo $cmd;
	system($cmd,$a);

$cmd=SUDO."mkdir /tmp/upgrade";
system($cmd,$a);
$cmd=SUDO."chmod 777 /tmp/upgrade";
system($cmd,$a);




if(!file_exists("/mnt/data/backup/oldversion.tgz"))
{
            echo '<html><head><title>�ָ�ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '<p><br><br><center><font face="����_GB2312"><b>û�пɸ��µİ汾</font></b><p>';
	    echo '<a href="uploadfile.php"><img border="0" src="image/goback.gif" width="40" height="40"></a>';
            echo '</center></body></html>';
            exit();			
	
}

$cmd=SUDO."tar xvfz /mnt/data/backup/oldversion.tgz -C /tmp/upgrade";
system($cmd,$a);
$cmd=SUDO."mv /tmp/upgrade/tmp/backup/* /tmp/upgrade";
system($cmd,$a);
$cmd=SUDO."find /tmp/upgrade -type f > /tmp/upgrade/filelist.txt";
system($cmd,$a);
$fd = fopen("/tmp/upgrade/filelist.txt", "r");
//$dirlen=fgets($fd,250);
//$dirlen=strlen($dirlen);
$dirlen=13;
while ($buffer = fgets($fd, 250)) 
{
	$len=strlen($buffer);
	$buffer=substr($buffer,0,$len-1);
	$oldbuffer=substr($buffer,$dirlen,$len-1-$dirlen);
	
	//����������
 	$cmd=SUDO."mount /dev/hda2 /mnt/data";
  //	echo $cmd;
	system($cmd,$a);
	
	
	//���������д�ϰ汾
	if($oldbuffer!="filelist.txt")
	{
  		$cmd=SUDO."cp  ".$buffer."  /mnt/data/".$oldbuffer;
  //		echo $cmd;
		system($cmd,$a);
	}
}
	
	//�����ʱ�ļ�
	$cmd=SUDO."rm -rf /tmp/upgrade";
  //	echo $cmd;
	system($cmd,$a);

	
	//ж�ص�����
	$cmd=SUDO."umount /mnt/data";
  //	echo $cmd;
	system($cmd,$a);
	

fclose($fd);
*/


$cmd=MYSUDO."/usr/local/AOS/Bin/downgrade-ed";
echo passthru($cmd,&$a);

if($a==0)
{
	echo "<p>\n";
	echo "�ָ����ɰ汾�ɹ����������������Ա�ʹ�þͰ汾 <p>\n";
}
else
{
	echo "<p>\n";
	echo "�ָ����ɰ汾ʧ��<p>\n";
}

?> 
</body> 
</html> 
