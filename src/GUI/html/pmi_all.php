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
	
?>

<html>
<?php
echo "appid=$appid";
?>
<form name="pmi_all_set" method="post"><br>
<font face="����_GB2312">��λ����&nbsp;&nbsp;&nbsp&nbsp;&nbsp;&nbsp&nbsp;</font> 
<?php
if (file_exists("/usr/SSLMPS/Config/".$appid.".DepName"))
{
	$fp=fopen("/usr/SSLMPS/Config/".$appid.".DepName","r");
	if ($fp)
		$dname=fread($fp,256);
	else
		$dname="δ����";
}
else
	$dname="δ����";
echo "<input type=\"TEXT\" name=\"depname\" value=\"$dname\" size=%80><br>"
?>
<font face="����_GB2312">Ӧ��ϵͳ����&nbsp;&nbsp;&nbsp;</font>
<?php
if (file_exists("/usr/SSLMPS/Config/".$appid.".AppName"))
{
	$fp=fopen("/usr/SSLMPS/Config/".$appid.".AppName","r");
	if ($fp)
		$aname=fread($fp,256);
	else
		$aname="δ����";
}
else
	$aname="δ����";
echo "<input type=\"TEXT\" name=\"appname\" value=\"$aname\" size=%80><br>";
echo "&nbsp;&nbsp;&nbsp&nbsp;&nbsp;&nbsp";
echo "<input type=\"submit\" value=\"����\" name=\"add\" onclick=\"pmi_all_set.action='pmi_all_set.php?appid=$appid&op=0'\">";
echo "&nbsp;&nbsp;&nbsp&nbsp;&nbsp;&nbsp";
echo "<input type=\"submit\" value=\"����\" name=\"del\" onclick=\"pmi_all_set.action='pmi_all_set.php?appid=$appid&op=1'\">";
?>
</form>

</html>
