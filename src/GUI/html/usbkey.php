<?php
	include ("constant.php");
	@session_start();
	$records_each_pages = 15;
	if($manager_ID==NULL)
	{
		echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
		echo '<p><br><br><center><font face="����_GB2312"><b>���ȵ�½��</font></b><p>';
		echo '<a href="login.html"><img border="0" src="image/goback.gif" width="40" height="40"></a>';
		echo '</center></body></html>';
		exit();			
	}	
	if($numberu)
	{
		if( !IsUsbKeyUserExist($numberu))
		{
			if(!AosAddUsbKeyUser($usernameu,$departmentu,$numberu))
			{
				echo "<html><head><title>Key�û�ע��ʧ��</title></head><body  background=\"image/pmiback.gif\"><b>";
				echo "<p><br><br><center><font face=\"����_GB2312\"><b>����֤��Ϊ '$numberu' ���û�ע��ʧ��!</font></b><p>";
				echo "<a href=\"usbkey.php?numb=$numb\">";
		        echo "<img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>";
		        echo "</center></body></html>";
		        exit();
			}
			// ���Usbkey�û���ϵͳ�ں��ڴ��У�ִ��CLI����
			$cmd=MYSUDO.MYCLI."\\\"usbkey add $numberu\\\"";
	  		exec($cmd,$a);
		}	
		else
		{
			echo "<html><head><title>Key�û�ע��ʧ��</title></head><body  background=\"image/pmiback.gif\"><b>";
			echo "<p><br><br><center><font face=\"����_GB2312\"><b>����֤��Ϊ '$numberu' ���û��Ѿ�����,<br>���ȷʵҪע����û�����ɾ��ԭ�û�!</font></b><p>";
			echo "<a href=\"usbkey.php?numb=$numb\">";
	        echo "<img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>";
	        echo "</center></body></html>";
	        exit();
		}
	}
	if($numbtemp!=NULL)
	{
		$arr = array($check0,$check1,$check2,$check3,$check4,$check5,$check6,$check7,$check8,$check9,$check10,$check11,$check12,$check13,$check14);
		$usbkey_userstemp = GetUsbkeyUserList();
    	$nr = count($usbkey_userstemp);
		$a=0;
		$b=$numbtemp*$records_each_pages;
		$c=0;
		while ($a < $nr)
		{
			$a=$a+1;
			if ($a>$b-$records_each_pages && $a<=$b )
			{
				if($arr[$c]=="ON")
				{
					$user[$c]=$usbkey_userstemp[$a-1][1];
				}
				$c=$c+1;
			}
		}
		for($i=0; $i<$c; $i++)
		{
			if($user[$i]== NULL) continue;
			if(!AosUsbkeyDelUser($user[$i]))
			{
				echo "<html><head><title>Key�û�ע��ʧ��</title></head><body  background=\"image/pmiback.gif\"><b>";
				echo "<p><br><br><center><font face=\"����_GB2312\"><b>����֤��Ϊ '$numberu' ���û�ע��ʧ��!<br>";
				echo "���û�����ѡ����û�Ҳ�޷�ע����</font></b><p>";
				echo "<a href=\"usbkey.php?numb=$numb\">";
		        echo "<img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>";
		        echo "</center></body></html>";
		        exit();
			}
			// ��ϵͳ�ں��ڴ���ɾ����ִ��CLI����
			$cmd=MYSUDO.MYCLI."\\\"usbkey remove $user[$i]\\\"";
	  		exec($cmd,$a);
		}
	}
?>
<html>

<head>
<meta name="GENERATOR" content="Microsoft FrontPage 5.0">
<meta name="ProgId" content="FrontPage.Editor.Document">
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�û���Ϣ</title>
</head>

<body bgcolor="#eef4f4">
<?php
	echo "<form name=\"usbkey\" method=\"POST\" action=\"usbkey.php?numb=1\">";
?>

<table border="0" cellspacing="1" width="100%" id="AutoNumber2" height="400">
  <tr>

    <td width="100%" height="380">
<br><img border="0" src="image/keyusehead.gif" width="283" height="57"><br>
<?php
	echo "<input type=\"hidden\" name=\"numbtemp\" value=\"$numb\">";
?>   
<table border="2" cellspacing="1" bordercolor="#55847e" width="100%" style="border-collapse: collapse">
<tr bgcolor="#95bdbf">
<td width="5%" height="20"></td>
<td width="28%" height="20"><center><b>�û���</b></center></td>
<td width="28%" height="20"><center><b>��������</b></center></td>
<td width="39%" height="20"><center><b>����֤��</b></center></td>
</tr>
<?php
	$usbkey_users = GetUsbkeyUserList();
    $nr = count($usbkey_users);
    
	//$records_each_pages = 15;
	if( $nr%$records_each_pages == 0 )
		$tmp = floor($nr/$records_each_pages);
	else
		$tmp = floor($nr/$records_each_pages)+1;
    if ($numb <= 0) $numb = 1;

    $aaa = ($numb-1)*$records_each_pages+1;	//��ҳ�ĵ�һ����¼��rid
    if (($numb*$records_each_pages) <= $nr)
    	$bbb=$numb*$records_each_pages;      //��ҳ�����һ����¼��rid
    else
		$bbb=$nr;

    $rs=$bbb-$aaa;                   		//��ҳ��ʾ�ļ�¼��-1��
    $ri=0;
	if ($nr != 0)
	{
		$count = 0;
		while ($ri <= $rs)
		{
			$rid = $usbkey_users[$aaa-1][0];
	        $userid = $usbkey_users[$aaa-1][1];
	        $username = $usbkey_users[$aaa-1][2];
	        $department = $usbkey_users[$aaa-1][3];
			echo "<tr bgcolor=\"#eef4f4\"><th><input type=\"checkbox\" name=\"check$count\" value=\"ON\"></th><th>$username</th><th>$department</th><th>$userid</th></tr>";
			$count = $count+1;
			$aaa = $aaa+1;
		    $ri += 1;
		}
	}
	
?>

</table>
<br>
<input type="button" value="ɾ���û�" name="usbkeydelb" onclick="usbkeydel()">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

<font face="����_GB2312"  color="#006699"><b>&nbsp;&nbsp;&nbsp;ҳ��:
   <?php 
   	if($nr%15>7)	
		$tmp=round($nr/15);
	else
		$tmp=round($nr/15)+1;
 
 	print("$numb/$tmp&nbsp;&nbsp;&nbsp;ÿҳ15��&nbsp;&nbsp;&nbsp;��¼��:$nr".
 	"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font><font face=\"����_GB2312\" color=\"#C0C0C0\">");
    
   	if($numb>1)
   	{	
  		$temp=$numb-1;
	 	echo "<a href=\"usbkey.php?numb=$temp\">��һҳ</a>&nbsp;&nbsp;";
	}else{
		echo "��һҳ&nbsp;&nbsp;";
	}
	if($nr>$numb*15)
	{
  		$temp=$numb+1;
	 	echo "<a href=\"usbkey.php?numb=$temp\">��һҳ</a></font></b>";
	}else{
		echo "��һҳ</font></b>";
	}
 ?>
 
 	<p align="center"><input type="button" value="Key�û�ע��" name="usbkeyregb" onclick="usbkeyreg()"></p>
    </td>
  </tr>
</table>
</form>

</body>
<script language="javaScript">
function usbkeydel()
{
	if(window.confirm("ȷ��ɾ����ѡ���Key�û���"))
	{
		document.usbkey.action="usbkey.php?numb=1";
		document.usbkey.submit();
	}
}

function usbkeyreg()
{
	document.usbkey.action="usbkeyreg.php";
	document.usbkey.submit();
}
</script>
</html>