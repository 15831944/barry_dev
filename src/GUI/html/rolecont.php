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
	$dblink=new DB;
	$dblink->Database=C_DB_NAME;
	$dblink->connect();
	if ($dblink->Errno != 0)
		die();
	$sql="select * from ".C_ROLE_CONT." where Roleid=".$roleid;
	$dblink->Query($sql);
	$nr=$dblink->num_rows();
	if ($nr != 0)
	{
		$arr=array('֤�����кţ�','�û�����','����֤�ţ�','�û���1��','�û���2��','�û���3��','��֯��','���ţ�','ְ��','Ȩ�ޣ�');
		echo '<html><head><title>��ɫ��Ϣ</title></head><body  background="image/pmiback.gif">' ;
		echo "<p align=\"center\"><font face=\"����_GB2312\">��ɫ����</font><font face=\"����_GB2312\" color=#ff0000>$rolename</font></p>";
		echo "<p align=\"center\"><font face=\"����_GB2312\" color=\"#333399\"><b>��ɫƥ����Ϣ</b></font></p>";

		echo '<table border="0" cellspacing="1" style="border-collapse: collapse" width="70%" id="table1"><tr><td width="55%">��</td><td>';

		echo '<table border="2" cellspacing="1" style="border-collapse: collapse" width="297" bordercolorlight="#008080" bordercolor="#008080" id="table2">';
		echo '<tr>';
		echo '<td bgcolor="#0066CC" width="50%"><p align="center"><b><font color="#FFFF00" face="����_GB2312">';
		echo '֤����</font></b></td><td bgcolor="#0066CC" align="center" width="50%">';
		echo '<p align="center"><b><font color="#FFFF00" face="����_GB2312">ƥ��ֵ</font></b></td></tr>';
				
		while(list($Roleid,$certitemid,$cont)=$dblink->next_record())
		{
			$tmp=$certitemid-1;
			echo "<tr><td><p align=\"center\"><font face=\"����_GB2312\">$arr[$tmp]</font></p></td><td><p align=\"center\"><font face=\"����_GB2312\" color=#0000ff>$cont</font></p></td></tr>";
		}
		echo '</table></td></table>';
		echo "<p align=\"center\"><a href=\"role.php?numb=1\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a></p>";
            echo '</body></html>';
        }
        $dblink->close();
?>