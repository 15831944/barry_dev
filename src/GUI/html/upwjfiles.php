<?php

/* use http upload files
<form enctype="multipart/form-data" action=result_up.php method=post>
	<input type=hidden name=MAX_FILE_SIZE value=1000>
	<input type=file name=upfilebox>
	<input type=submit value=upload>
</form>

	$FTPSvrIP="192.168.1.200";
	$FTPSvrPort=21;
	$UserName="zzc";
	$UserPasswd="poiuyt";
	$upload=0;
	$LocalFName="/tmp/tmpfile";
	$SvrFileName="/boot.ini";
*/
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/backgroud.gif"><b>' ;
	    echo '���ȵ�½��<p>';
	    echo '<a href="login.html">����</a>';
            echo '</b></body></html>';
            exit();			
	}
	$FTPStream=ftp_connect($FTPSvrIP,$FTPSvrPort);
	if ($FTPStream)
		echo "����FTP�������ɹ�<br>";
	else
	{
		echo "����FTP������ʧ��<br>";
		exit(-1);
	}
	$LoginSucc=ftp_login($FTPStream,$UserName,$UserPasswd);
	if ($LoginSucc)
	{
		echo "��¼FTP�������ɹ�<br>";
		if ($upload == 0)
		{
			echo "��ʼ�����ļ�<br>";
			$LocalFP=fopen($LocalFName,"wb+");
			$Ret=ftp_fget($FTPStream,$LocalFP,$SvrFileName,FTP_BINARY);
			if ($Ret)
				echo "�ļ����سɹ�".$Ret."<br>";
			else
				echo "�ļ�����ʧ��".$Ret."<br>";
			fclose($LocalFP);
		}
		else
		{
			echo "��ʼ�ļ��ϴ�<br>";
			$LocalFP=fopen($LocalFName,"rb+");
			$Ret=ftp_fput($FTPStream,$SvrFileName,$LocalFP,FTP_BINARY);
			if ($Ret)
				echo "�ļ��ϴ��ɹ�".$Ret."<br>";
			else
				echo "�ļ��ϴ�ʧ��".$Ret."<br>";
			fclose($LocalFP);
		}
	}
	else
	{
		echo "��¼FTP������ʧ��<br>";
		$LogoutSucc=ftp_quit($FTPStream);
	}

/*	echo $fname."<br>".$LocalFName;
	$fp=fopen($fname,"rb");
	$flen=filesize($fname);
	$flen=34;
	echo $flen;
	$fcont=fread($fp,$flen);
	$LocalFP=fopen($LocalFName,"wb");
	$ret=fwrite($LocalFP,$fcont,$flen);
	fclose($fp);
	fclose($LocalFP);*/
?>
