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

//echo $userfile1;

$cmd=MYSUDO . "mv -f " . $userfile1 . " /tmp/upfile.tar.gz";
exec($cmd);
$cmd=MYSUDO . "/usr/local/AOS/Bin/tar-conf-to-ed /tmp/upfile.tar.gz";
exec($cmd);
$cmd=MYSUDO . "rm -f /tmp/upfile.tar.gz";
exec($cmd);
//echo "Please reboot"

/*
//-------------------------20060101;by yt;�����ļ�����
$cmd=MYSUDO."mkdir /tmp/upfile";
exec($cmd,$a);
$cmd=MYSUDO."chmod 777 /tmp/upfile";
exec($cmd,$a);
copy($userfile1,"/tmp/upfile.tgz");
$cmd=MYSUDO."tar xfz /tmp/upfile.tgz -C /";
exec($cmd,$a);
//$cmd=MYSUDO."unzip ".WWWDOCDIR."upfile.zip -d /tmp/upfile";
//exec($cmd,$a);
$cmd=MYSUDO."mv /tmp/download/ifcfg-eth0 /etc/sysconfig/network-scripts/ifcfg-eth0";
exec($cmd,$a);
$cmd=MYSUDO."chown root:root /etc/sysconfig/network-scripts/ifcfg-eth0";
exec($cmd,$a);
$cmd=MYSUDO."mv /tmp/download/ifcfg-eth1 /etc/sysconfig/network-scripts/ifcfg-eth1";
exec($cmd,$a);
$cmd=MYSUDO."chown root:root /etc/sysconfig/network-scripts/ifcfg-eth1";
exec($cmd,$a);
$cmd=MYSUDO."mv /tmp/download/network /etc/sysconfig/network";
exec($cmd,$a);
$cmd=MYSUDO."chown root:root /etc/sysconfig/network";
exec($cmd,$a);
$cmd=MYSUDO."mv /tmp/download/crontab /etc/crontab";
exec($cmd,$a);
$cmd=MYSUDO."chown root:root /etc/crontab";
exec($cmd,$a);
$cmd=MYSUDO."cp /tmp/download/*.* ".CFGFILEPATH;
exec($cmd,$a);
$cmd=MYSUDO."cp /tmp/download/Denypages/* ".DENYPAGEFILEPATH;
exec($cmd,$a);
$cmd=MYSUDO."rm -rf /tmp/download";
exec($cmd,$a);
$cmd=MYSUDO."rm -f /tmp/upfile.tgz";
exec($cmd,$a);
*/

//-------------------------20060101;by yt;�����ļ�����


//$cmd=MYSUDO."find /tmp/upfile -type f > /tmp/upfile/filelist.txt";
//exec($cmd,$a);
/*
$fd = fopen("/tmp/upfile/filelist.txt", "r");
//$dirlen=fgets($fd,250);
//$dirlen=strlen($dirlen);
$dirlen=12;
while ($buffer = fgets($fd, 250))
{
	$len=strlen($buffer);
	$buffer=substr($buffer,0,$len-1);
	$oldbuffer=substr($buffer,$dirlen,$len-1-$dirlen);

	//����������
 	$cmd=MYSUDO."mount /dev/hda2 /mnt/data";
  //	echo $cmd;
	exec($cmd,$a);

	//���������д�°汾
//	if($oldbuffer=="db_origin.tgz")
	if ($oldbuffer=="wjproxy_backup.sql.tgz")
	{
  		$cmd=MYSUDO."cp  ".$buffer."  /mnt/data/Manage/".$oldbuffer;
  //		echo $cmd;
		exec($cmd,$a);
	}else if($oldbuffer=="ifcfg-eth0")
	{
		$cmd=MYSUDO."cp  ".$buffer."  /mnt/data/SSLMPS/Config/".$oldbuffer;
  //		echo $cmd;
		exec($cmd,$a);
	}else if($oldbuffer=="ifcfg-eth1")
	{
		$cmd=MYSUDO."cp  ".$buffer."  /mnt/data/SSLMPS/Config/".$oldbuffer;
  //		echo $cmd;
		exec($cmd,$a);
	}else if($oldbuffer=="network")
	{
		$cmd=MYSUDO."cp  ".$buffer."  /mnt/data/SSLMPS/Config/".$oldbuffer;
  //		echo $cmd;
		exec($cmd,$a);
	}else if($oldbuffer=="Protocol.conf")
	{
		$cmd=MYSUDO."cp  ".$buffer."  /mnt/data/SSLMPS/Config/".$oldbuffer;
  //		echo $cmd;
		exec($cmd,$a);
	}else if($oldbuffer=="root")
	{
		$cmd=MYSUDO."cp  ".$buffer."  /mnt/data/SSLMPS/Config/cron".$oldbuffer;
  //		echo $cmd;
		exec($cmd,$a);
	}else if($oldbuffer=="SetCA.cfg")
	{
		$cmd=MYSUDO."cp  ".$buffer."  /mnt/data/SSLMPS/".$oldbuffer;
  //		echo $cmd;
		exec($cmd,$a);
	}

	//ж�ص�����
	$cmd=MYSUDO."umount /mnt/data";
  //	echo $cmd;
	exec($cmd,$a);
}


ʹ����һ������copy()�����ص���ʱĿ¼�µ��ļ�������һ���ض���Ŀ¼��
����������Ϊ"newfile",������򵥵�һ�ַ�����
*/
/*
ֵ��ע������ļ�upload.html�б�ѡ�� MAX_FILE_SIZE ������ֵ��ͨ������
��Value(ֵ)�������������ļ��Ĵ�С��

echo $userfile."-�û��ϴ����������ϵ��ļ���ʱ��ŵ�����<br>";
echo $userfile_name."-���û������ϸ��ļ���ԭʼ����<br>";
echo $userfile_size."-�ϴ��ļ���ʵ���ֽ���<br>";
echo $userfile_type."-����û���������ṩ�������Ϣ�Ļ�������ʾmime�����͡�����image/gif<br>";
*/
?>
<p>
<center><font face="����_GB2312"><b>�ļ��ϴ����!</font></b></center>
<p>
<center><a href='confile.php'><img border="0" src="image/goback.gif" width="40" height="40"></a>
</center>

</body>
</html>
