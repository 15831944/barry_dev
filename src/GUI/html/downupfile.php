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
?>
<form name=fileupdown method=post>
	FTP������IP��ַ<br>
	<input type=text name=FTPSvrIP value=192.168.1.200><br>
	FTP����˿ں�<br>
	<input type=text name=FTPSvrPort value=21><br>
	�û���<br>
	<input type=text name=UserName value=zzc><br>
	�û�����<br>
	<input type=password name=UserPasswd value=poiuyt><br>
	FTP���������ļ���<br>
	<input type=text name=SvrFileName><br>
	PWL517���ļ���<br>
	<input type=text name=LocalFName><br><br>
	<input type=submit value=�����ļ� onclick="fileupdown.action='upwjfiles.php?upload=0'">
	<input type=submit value=�ϴ��ļ� onclick="fileupdown.action='upwjfiles.php?upload=1'">
	<input type=reset value=���ò��� >
</form>
