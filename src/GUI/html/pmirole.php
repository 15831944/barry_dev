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
		if($mod!=NULL && $grad!=NULL)
		{
			move_role_control($appid,$rd,$mod,$grad);
		}
	}else if($issubmit==4){
		if($amitr==V3)
			$amitv=1;
		else if($amitr==V4)
			$amitv=0;
 		if($roleid!=NULL)
		{
			if($appid)
			{
				add_role_control($roleid,$appid,$amitv);
			}
		}
		
	}else if($issubmit==3){
		if($grad!=NULL)
		{
			delete_role_control($appid,$grad);
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
 	echo "<form name=\"control\" method=\"POST\" action=\"pmirole.php?appid=$appid&rolenumb=1\">" ;
 ?> 
 	 

<table border="0" cellspacing="1" width="100%" id="AutoNumber2" height="300">
 <tr>

    <td width="100%" height="300">
        <table border="0" cellspacing="0" width="100%" id="AutoNumber4" height="77" style="border-collapse: collapse" bordercolor="#111111" cellpadding="0">
      <tr>
        <td width="100%" height="26">
        
         <p align="left"><font face="����_GB2312"><b>��ѡ���ɫ:</b></font><select size="1" name="roleid">
   <?php
	$db = mysql_connect(C_DB_HOST, "root");
	mysql_select_db("wjproxy",$db);
 	$result = mysql_query("SELECT * FROM RoleTable",$db);
  	if(!$result)
 	{
 		echo 'û�����������ļ�¼';
		mysql_close($db);
 		return 0;
 	}
        while($row =mysql_fetch_row($result))
        {
         	echo "<option value=$row[0]>".$row[1]."</option>";
        }
        mysql_close($db);
  //      $appid=$appid;
     ?>        
        </select>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
      <input type="radio" value="V3" checked name="amitr"><font face="����_GB2312">����</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="radio" name="amitr" value="V4"><font face="����_GB2312">������</font>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <input type="submit" value="��ӽ�ɫ����" name="roleB1" onclick="setrole()">
</p>       
   <img border="0" src="image/pmirolehead.gif" width="283" height="57"><br>
<?php
	echo "<input type=\"hidden\" name=\"rolenumbtemp\" value=".$rolenumb.">";
?>
 <table border="2" cellspacing="1" bordercolor="#55847e" width="100%" style="border-collapse: collapse">
<tr bgcolor="#95bdbf">
<td width="5%" height="20"></td>
<td width="17%" height="20"><center><b>Ӧ�÷�������</b></center></td>
<td width="23%" height="20"><center><b>��ɫ��</b></center></td>
<td width="10%" height="20"><center><b>���ƹ���</b></center></td>
<td width="35%" height="20"><center><b>����ʱ��</b></center></td>
<td width="10%" height="20"></td>
</tr>
<?php
	$dblink=new DB;
	$dblink->Database=C_DB_NAME;
	$dblink->connect();
	if ($dblink->Errno != 0)
		die();
	$sql="SELECT ".C_APP_WJ_TBL.".appname,".C_DB_ROLE.".Roleid,".C_DB_ROLE.".Rolename,rule,".C_ROLE_RULE.".grade,".C_ROLE_RULE.".joindate,".C_ROLE_RULE.".isdeleted FROM ".C_ROLE_RULE.",".C_APP_WJ_TBL.",".C_DB_ROLE." where ".C_APP_WJ_TBL.".appid=".C_ROLE_RULE.".appid and ".C_DB_ROLE.".Roleid=".C_ROLE_RULE.".Roleid and ".C_APP_WJ_TBL.".appid=$appid order by ".C_ROLE_RULE.".grade";
	$dblink->Query($sql);
	$nr=$dblink->num_rows();
	$aaa=0;
	$bbb=$rolenumb*10;
	$count=0;
	if ($nr != 0)
	{
		while (list($appname,$roleidx,$rolename,$rule,$grade,$joindate,$isdeleted)=$dblink->next_record())
			{
				$aaa=$aaa+1;
				if ($isdeleted != 1 && $aaa>$bbb-10 && $aaa<=$bbb){
					if($rule==1)
					{
						echo "<tr><th><img border=\"0\" src=\"image/del.gif\" width=\"15\" height=\"15\" onclick=\"del($grade)\"></th><th><a href=\"roleappmessage.php?appnamex=$appname\">$appname</a></th>";
						echo "<th><a href=\"rolemessage.php?roleid=$roleidx&rolename=$rolename&appid=$appid\">$rolename</a></th><th>����</th><th>".date("Y/m/d--H:i:s",$joindate)."</th>";
						echo "<th><img border=\"0\" src=\"image/up.gif\" width=\"20\" height=\"20\" onclick=\"move(0,$grade,$roleidx)\">";
						echo "<img border=\"0\" src=\"image/down.gif\" width=\"20\" height=\"20\" onclick=\"move(1,$grade,$roleidx)\"></th></tr>";
					}else{
						echo "<tr><th><img border=\"0\" src=\"image/del.gif\" width=\"15\" height=\"15\" onclick=\"del($grade)\"></th><th><a href=\"roleappmessage.php?appnamex=$appname\">$appname</a></th>";
						echo "<th><a href=\"rolemessage.php?roleid=$roleidx&rolename=$rolename&appid=$appid\">$rolename</a></th><th>�ܾ�</th><th>".date("Y/m/d--H:i:s",$joindate)."</th>";
						echo "<th><img border=\"0\" src=\"image/up.gif\" width=\"20\" height=\"20\" onclick=\"move(0,$grade,$roleidx)\">";
						echo "<img border=\"0\" src=\"image/down.gif\" width=\"20\" height=\"20\" onclick=\"move(1,$grade,$roleidx)\"></th></tr>";
					}
					$count=$count+1;
				}
			}
		$dblink->clean_results();
	}
	echo "<tr><th><input type=\"hidden\" name=\"rolecounttemp\" value=\"$count\"></th></tr>";
?>

</table>  
<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 <font face="����_GB2312"  color="#006699"><b>&nbsp;&nbsp;&nbsp;ҳ��:

   <?php  
   	if(($nr)%10>4)	
		$tmp=round(($nr+$nr1)/10);
	else
		$tmp=round(($nr+$nr1)/10)+1;
 
 	print("$rolenumb/$tmp&nbsp;&nbsp;&nbsp;ÿҳ10��&nbsp;&nbsp;&nbsp;��¼��:$nr".
 	"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font><font face=\"����_GB2312\">");
   	if($rolenumb>1)
   	{	
  		$temp=$rolenumb-1;
	 	echo "<a href=\"pmirole.php?appid=$appid&rolenumb=$temp\">��һҳ</a>&nbsp;&nbsp;";
	}else{
		echo "��һҳ&nbsp;&nbsp;";
	}
	if($nr>$rolenumb*10)
	{
  		$temp=$rolenumb+1;
	 	echo "<a href=\"pmirole.php?appid=$appid&rolenumb=$temp\">��һҳ</a></font></b>";
	}else{
		echo "��һҳ</font></b>";
	}
 ?>

</td>
      </tr>
    </table></tr><tr><td>
<?php
	echo "<input type=\"hidden\" name=\"numbtemp\" value=".$numb.">";
?>
<p><b><font size="2" face="����_GB2312" color="#FF0000">ע����ɫ���ƹ����ж������϶���ִ�еģ�����ͨ�����</font></b>
<br><b><font face="����_GB2312" size="2" color="#FF0000">&nbsp;&nbsp;&nbsp; &quot;����&quot;<img border="0" src="image/up.gif" width="20" height="20"> 
��&quot;����&quot; <img border="0" src="image/down.gif" width="20" height="20"> ��ť���������˳��<br>
&nbsp;&nbsp;&nbsp;����ͨ�����<img border="0" src="image/del.gif" width="15" height="15">ɾ������ </font></b></p>
       <INPUT type=hidden value="2" name=issubmit><INPUT type=hidden value="" name=appnamex>
<INPUT type=hidden value="" name=usernamex><INPUT type=hidden value="" name=grad>
<INPUT type=hidden value="" name=mod><INPUT type=hidden value="" name=rd>

</td></tr></table>
</form>
</body>

<script language="javaScript">


function del(gra){
	if(window.confirm("ȷ��ɾ���˹�����"))
	{
		document.control.issubmit.value=3;
		document.control.grad.value=gra;
		document.control.submit();
	}else{
	}
//	window.alert(document.control.numbtemp.value);
}

function setrole(){
	document.control.issubmit.value=4;	

}
function move(mode,num,rid){
	document.control.issubmit.value=1;
	document.control.grad.value=num;
	document.control.mod.value=mode;
	document.control.rd.value=rid;
	document.control.submit();
}
</script>
</html>
