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

	include "pmi_db.php";
	if($issubmit==1)
	{
		if($amit==V1)
			$amitv=1;
		else if($amit==V2)
			$amitv=0;
 		if($userid!=NULL)
		{
			if($appid)
			{
				add_control($userid,$appid,$amitv);
			}
		}
	}else if($issubmit==0){
		if($appid!=NULL && $numbtemp!=NULL)
		{	
			$arr = array($check0,$check1,$check2,$check3,$check4,$check5,$check6,$check7,$check8,$ckeck9);
			$dblink1=new DB;
			$dblink1->Database=C_DB_NAME;
			$dblink1->connect();
			if ($dblink->Errno != 0){
				echo '���ݿ�����ʧ��';
				return 0;
			} 
			$sql ="select * from ".C_RULE_WJ_TBL." where appid=".$appid." and userid<65534000";			
			$dblink1->Query($sql);
			$nr=$dblink1->num_rows();
			$a=0;
			$b=$numbtemp*10;
			$c=0;
			if ($nr != 0)
			{
				while (list($appid1,$userid1,$rule,$joindate,$isdeleted)=$dblink1->next_record())
					{
						$a=$a+1;
						if ($isdeleted != 1 && $a>$b-10 && $a<=$b ){
							if($arr[$c]=="ON")
							{
								$user[$c]=$userid1;
							}
							$c=$c+1;
						}
					}
				}
			$sql ="select * from ".C_RULE_WJ_TBL." where appid=".$appid." and userid=65534000";
			if($nr==0)
				$a=$a+1;
			$dblink1->Query($sql);
			$nr=$dblink1->num_rows();
			if($nr != 0&& $a>$b-10 && $a<=$b && $arr[$c]=="ON")
			{
				$user[$c]=65534000;
			}	
			$dblink1->close();
			for($i=0;$i<$c+1;$i++)

				if($user[$i]!=NULL){
	//				echo "i=$i and appid=$appid and userid=$user[$i]";
					del_control($appid,$user[$i]);
				}

		}
	}
	if($appid==NULL)
	{
  	   	echo '<html><head><title>��Ϣ</title></head><body  background="image/backgroud.gif">';
		echo '��ѡ��Ӧ�÷���!';
		echo '<p>';
   	   	echo "<a href='pmi.php'>����</a>";
     	   	echo '</body></html>';
     	   	exit();
	}
?>
<html>

<head>
<meta name="GENERATOR" content="Microsoft FrontPage 5.0">
<meta name="ProgId" content="FrontPage.Editor.Document">
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�������</title>
</head>

<body bgcolor="#eef4f4">

<?php
 	echo "<form name=\"control\" method=\"POST\" action=\"pmi1.php?appid=$appid&numb=1\">" ;
 ?> 
 	 

<table border="0" cellspacing="1" width="100%" id="AutoNumber2" height="400">
 <tr>

    <td width="100%" height="400">
        <table border="0" cellspacing="0" width="100%" id="AutoNumber4" height="77" style="border-collapse: collapse" bordercolor="#111111" cellpadding="0">
      <tr>
        <td width="100%" height="26">
        <p align="left"><font face="����_GB2312"><b>��ѡ���û�:</b></font><select size="1" name="userid">
        <option value="65534000">�����û�</option>
   <?php
	$db = mysql_connect(C_DB_HOST, "root");
	mysql_select_db("wjproxy",$db);
 	$result = mysql_query("SELECT * FROM UserTable",$db);
  	if(!$result)
 	{
 		echo 'û�����������ļ�¼';
		mysql_close($db);
 		return 0;
 	}
        while($row =mysql_fetch_row($result))
        {
         	echo "<option value=$row[0]>".$row[2]." ".$row[1]."</option>";
        }
        mysql_close($db);
  //      $appid=$appid;
     ?>        
        </select>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
      <input type="radio" value="V1" checked name="amit"><font face="����_GB2312">����</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" name="amit" value="V2"><font face="����_GB2312">������</font>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <input type="submit" value="��ӹ���" name="B1" onclick="set1()">
</p>       <INPUT type=hidden value="2" name=issubmit><INPUT type=hidden value="" name=appnamex>
<INPUT type=hidden value="" name=usernamex>
</td>
      </tr>
    </table>
<img border="0" src="image/pmihead.gif" width="283" height="57"><br>
<?php
	echo "<input type=\"hidden\" name=\"numbtemp\" value=".$numb.">";
?>
<table border="2" cellspacing="1" bordercolor="#55847e" width="100%" style="border-collapse: collapse">
<tr bgcolor="#95bdbf">
<td width="5%" height="20"></td>
<td width="25%" height="20"><center><b>Ӧ�÷�������</b></center></td>
<td width="23%" height="20"><center><b>�û���</b></center></td>
<td width="15%" height="20"><center><b>���ƹ���</b></center></td>
<td width="32%" height="20"><center><b>����ʱ��</b></center></td>
</tr>
<?php
	$dblink=new DB;
	$dblink->Database=C_DB_NAME;
	$dblink->connect();
	if ($dblink->Errno != 0)
		die();
	$sql="SELECT ".C_APP_WJ_TBL.".appname,".C_USER_WJ_TBL.".userid,".C_USER_WJ_TBL.".username,".C_USER_WJ_TBL.".department,rule,".C_RULE_WJ_TBL.".joindate,".C_SERVER_PMI_TBL.".isdeleted FROM ".C_SERVER_PMI_TBL.",".C_APP_WJ_TBL.",".C_USER_WJ_TBL." where ".C_APP_WJ_TBL.".appid=".C_SERVER_PMI_TBL.".appid and ".C_USER_WJ_TBL.".userid=".C_SERVER_PMI_TBL.".userid and ".C_APP_WJ_TBL.".appid=$appid";
	$dblink->Query($sql);
	$nr=$dblink->num_rows();
	$aaa=0;
	$bbb=$numb*10;
	$count=0;
	if ($nr != 0)
	{
		while (list($appname,$useridx,$username,$department,$rule,$joindate,$isdeleted)=$dblink->next_record())
			{
				$aaa=$aaa+1;
				if ($isdeleted != 1 && $aaa>$bbb-10 && $aaa<=$bbb){
					if($rule==1)
						echo "<tr><th><input type=\"checkbox\" name=\"check$count\" value=\"ON\"></th><th><a href=\"appmessage.php?appnamex=$appname\">$appname</a></th><th><a href=\"usermessage.php?usernamex=$useridx&appid=$appid\">".$department." $username</a></th><th>����</th><th>".date("Y/m/d--H:i:s",$joindate)."</th></tr>";
					else
						echo "<tr><th><input type=\"checkbox\" name=\"check$count\" value=\"ON\"></th><th><a href=\"appmessage.php?appnamex=$appname\">$appname</a></th><th><a href=\"usermessage.php?usernamex=$useridx&appid=$appid\">".$department." $username</a></th><th>�ܾ�</th><th>".date("Y/m/d--H:i:s",$joindate)."</th></tr>";
					$count=$count+1;
				}
			}
		$dblink->clean_results();
	}
	$sql="SELECT ".C_APP_WJ_TBL.".appname,rule,".C_RULE_WJ_TBL.".joindate,".C_SERVER_PMI_TBL.".isdeleted FROM ".C_SERVER_PMI_TBL.",".C_APP_WJ_TBL." where ".C_APP_WJ_TBL.".appid=".C_SERVER_PMI_TBL.".appid and ".C_SERVER_PMI_TBL.".userid=65534000 and ".C_SERVER_PMI_TBL.".appid=$appid";
	$dblink->Query($sql);
	$nr1=$dblink->num_rows();
	if ($nr1 != 0)
	{
		while (list($appname,$rule,$joindate,$isdeleted)=$dblink->next_record())
			{
				$aaa=$aaa+1;
				if ($isdeleted != 1 && $aaa>$bbb-10 && $aaa<=$bbb){
					if($rule==1)
						echo "<tr><th><input type=\"checkbox\" name=\"check$count\" value=\"ON\"></th><th><a href=\"appmessage.php?appnamex=$appname\">$appname</a></th><th>�����û�</th><th>����</th><th>".date("Y/m/d--H:i:s",$joindate)."</th></tr>";
					else
						echo "<tr><th><input type=\"checkbox\" name=\"check$count\" value=\"ON\"></th><th><a href=\"appmessage.php?appnamex=$appname\">$appname</a></th><th>�����û�</th><th>�ܾ�</th><th>".date("Y/m/d--H:i:s",$joindate)."</th></tr>";
					$count=$count+1;
				}
			}
		$dblink->clean_results();
	}
	echo "<tr><th><input type=\"hidden\" name=\"counttemp\" value=\"$count\"></th></tr>";
?>

</table><br>
<input type="button" value="ɾ������" name="B1" onclick="set()">
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 <font face="����_GB2312"  color="#006699"><b>&nbsp;&nbsp;&nbsp;ҳ��:

   <?php  
   	if(($nr+$nr1)%10>4)	
		$tmp=round(($nr+$nr1)/10);
	else
		$tmp=round(($nr+$nr1)/10)+1;
	$tmp1=$nr+$nr1;
 
 	print("$numb/$tmp&nbsp;&nbsp;&nbsp;ÿҳ10��&nbsp;&nbsp;&nbsp;��¼��:$tmp1".
 	"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font><font face=\"����_GB2312\">");
   	if($numb>1)
   	{	
  		$temp=$numb-1;
	 	echo "<a href=\"pmi1.php?appid=$appid&numb=$temp\">��һҳ</a>&nbsp;&nbsp;";
	}else{
		echo "��һҳ&nbsp;&nbsp;";
	}
	if($nr+$nr1>$numb*10)
	{
  		$temp=$numb+1;
	 	echo "<a href=\"pmi1.php?appid=$appid&numb=$temp\">��һҳ</a></font></b>";
	}else{
		echo "��һҳ</font></b>";
	}
 ?>

 </td>
  </tr>
  
</table>
</form>
</body>

<script language="javaScript">

function set(){
	if(window.confirm("ȷ��ɾ���˹�����"))
	{
		document.control.issubmit.value=0;
		document.control.submit();
	}else{
	}
//	window.alert(document.control.numbtemp.value);
}

function set1(){
	document.control.issubmit.value=1;	
}

</script>
</html>
