<?php
	include("constant.php");
	include("mysql.lib.php");
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '<p><br><br><center><font face="����_GB2312"><b>���ȵ�½��</font></b><p>';
	    echo '<a href="login.html"><img border="0" src="image/goback.gif" width="40" height="40"></a>';
            echo '</center></body></html>';
            exit();			
	}
	if($numbtemp!=NULL)
	{	
		$arr = array($check0,$check1,$check2,$check3,$check4,$check5,$check6,$check7,$check8,$check9);
		$dblink1=new DB;
		$dblink1->Database=C_DB_NAME;
		$dblink1->connect();
		if ($dblink1->Errno != 0){
			echo '���ݿ�����ʧ��';
			return 0;
		} 
		$sql ="SELECT * FROM ".C_DB_ROLE;			
		$dblink1->Query($sql);
		$nr=$dblink1->num_rows();
		$a=0;
		$b=$numbtemp*10;
		$c=0;
		if ($nr != 0)
		{
			while (list($Roleid1,$Rolename1,$fatherid1,$isdeleted1)=$dblink1->next_record())
			{
				$a=$a+1;
				if ($isdeleted != 1 && $a>$b-10 && $a<=$b ){
					if($arr[$c]=="ON")
					{
					//	$Rname[$c]=$Rolename1;
						$Rid[$c]=$Roleid1;
					}
					$c=$c+1;
				}
			}
		}

		for($i=0;$i<$c;$i++)
			if($Rid[$i]!=NULL){
				$sql="delete from ".C_ROLE_CONT." where Roleid=".$Rid[$i];
				$dblink1->Query($sql);

				$sql="delete from ".C_ROLE_RULE." where Roleid=".$Rid[$i];
				$dblink1->Query($sql);
				
				$sql="delete from ".C_DB_ROLE." where Roleid=".$Rid[$i];
				$dblink1->Query($sql);
				
		//		del_user($user[$i]);
			}
		$dblink1->close();
	}?>
<html>

<head>
<meta http-equiv="Content-Language" content="zh-cn">
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>��ɫ��</title>
</head>

<body background="image/pmiback.gif" style="text-align: center">

<form name="role" method="POST">
	<!--webbot bot="SaveResults" U-File="C:\Inetpub\wwwroot\_private\form_results.csv" S-Format="TEXT/CSV" S-Label-Fields="TRUE" -->
	<table border="0" cellspacing="1" style="border-collapse: collapse" width="100%" id="table1">
		<tr>
			<td colspan="2">
			<img border="0" src="image/rolereg.gif" width="283" height="57"></td>
		</tr>
		<tr>
			<td colspan="2">
			<p align="center">��
			<table border="2" cellspacing="1" bordercolor="#55847e" width="100%" style="border-collapse: collapse">
<tr bgcolor="#95bdbf">
<td width="5%" height="20"></td>
<td width="50%" height="20"><center><b>��ɫ��</b></center></td>
<td width="45%" height="20"><center><b>��ɫ�ƶ���Ϣ</b></center></td>
</tr>
<?php
	$dblink=new DB;
	$dblink->Database=C_DB_NAME;
	$dblink->connect();
	if ($dblink->Errno != 0)
		die();
	$sql="SELECT * FROM ".C_DB_ROLE;
	$dblink->Query($sql);
	$nr=$dblink->num_rows();
	$aaa=0;
	$bbb=$numb*10;
	$count=0;
	if ($nr != 0)
	{
	while (list($Roleid,$Rolename,$fatherid,$isdeleted)=$dblink->next_record())
		{
			$aaa=$aaa+1;
			if ($aaa>$bbb-10 && $aaa<=$bbb)
			{
				echo "<tr bgcolor=\"#eef4f4\"><th><input type=\"checkbox\" name=\"check$count\" value=\"ON\"></th><th>$Rolename</th><th><a href=\"rolecont.php?roleid=$Roleid&rolename=$Rolename\">�鿴��Ϣ</a></th></tr>";
				$count=$count+1;
			}
		}
		$dblink->clean_results();
	}
?>

</table></td>
		</tr>
		<tr>
			<td colspan="2">&nbsp;&nbsp;&nbsp;&nbsp;
			<input type="button" value="ɾ����ɫ" name="B1" onclick="delrole()">
			
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;

<font face="����_GB2312"  color="#006699"><b>&nbsp;&nbsp;&nbsp;ҳ��:
   <?php 
   	echo "<input type=\"hidden\" name=\"numbtemp\" value=\"$numb\">";
   	if($nr%10>5)	
		$tmp=round($nr/10);
	else
		$tmp=round($nr/10)+1;
 
 	print("$numb/$tmp&nbsp;&nbsp;&nbsp;ÿҳ10��&nbsp;&nbsp;&nbsp;��¼��:$nr".
 	"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font><font face=\"����_GB2312\" color=\"#C0C0C0\">");
    
   	if($numb>1)
   	{	
  		$temp=$numb-1;
	 	echo "<a href=\"role.php?numb=$temp\">��һҳ</a>&nbsp;&nbsp;";
	}else{
		echo "��һҳ&nbsp;&nbsp;";
	}
	if($nr>$numb*10)
	{
  		$temp=$numb+1;
	 	echo "<a href=\"role.php?numb=$temp\">��һҳ</a></font></b>";
	}else{
		echo "��һҳ</font></b>";
	}
 ?>
 	<p align="center"><input type="button" value="�½�ɫ����" name="reg" onclick="regrole()"></p>
 	</td>
		</tr>

	</table>
<script language="javascript">

function delrole(){
	if(window.confirm("��ɾ���˽�ɫ����ý�ɫ��Ӧ�ķ��ʿ��ƹ�\n��Ҳ��һͬɾ����ȷ��ɾ���˽�ɫ��"))
	{
		document.role.action="role.php?numb=1";
		document.role.submit();
	}else{
	}
}
function regrole(){
	document.role.action="rolereg.php";
	document.role.submit();
}
</script>
</form>

</body>

</html>