<?php
	include("pmi_db.php");
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '<p><br><br><center><font face="����_GB2312"><b>���ȵ�½��</font></b><p>';
	    echo '<a href="login.html"><img border="0" src="image/goback.gif" width="40" height="40"></a>';
            echo '</center></body></html>';
            exit();			
	}
	$dblink1=new DB;
	$dblink1->Database=C_DB_NAME;
	$dblink1->connect();
	if ($dblink1->Errno != 0){
		echo '���ݿ�����ʧ��';
		return 0;
	} 
	$sql ="SELECT * FROM ".C_DB_ROLE." where Rolename='".$rolename."'";			
	$dblink1->Query($sql);
	$nr=$dblink1->num_rows();
	if($nr>0)
	{
		$dblink1->close();
		echo '<html><head><title>������Ϣ</title></head><body  background="image/pmiback.gif">';
		echo "<p align=\"center\">";
		echo "<b><font face=\"����_GB2312\">�˽�ɫ�Ѵ���,��ʹ���µ��û�����</font></b><br>";
		echo '<p align="center">';
	   	echo "<a href='rolereg.php'><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>";
	     	echo '</body></html>';
		exit();
	}else{
		$sql="insert into ".C_DB_ROLE."(Rolename,fatherid,isdeleted) values('".$rolename."',0,0)";
		$dblink1->Query($sql);
		$sql="select * from ".C_DB_ROLE." where Rolename='".$rolename."'";
		$dblink1->Query($sql);
		$nr1=$dblink1->num_rows();
		if($nr1==1)
		{
			while (list($Roleid,$Rolename,$fatherid,$isdeleted)=$dblink1->next_record())
			{
				$arr = array($C1,$C2,$C3,$C4,$C5,$C6,$C7,$C8,$C9,$C10);
				$arr1 = array($certnum,$username,$plicenum,$group1,$group2,$group3,$organise,$depart,$dute,$priv);
				$dblink2=new DB;
				$dblink2->Database=C_DB_NAME;
				$dblink2->connect();
				if ($dblink2->Errno != 0){
					echo '���ݿ�����ʧ��';
					return 0;
				} 

				for($i=0;$i<10;$i++)
				{
					if($arr[$i]=="ON")
					{
						$tmp=$i+1;
						$sql="insert into ".C_ROLE_CONT." values(".$Roleid.",".$tmp.",'".$arr1[$i]."')";
						$dblink2->Query($sql);
					}
				}
				$dblink2->close();
			}
		}else{
			$dblink1->close();
			echo '<html><head><title>������Ϣ</title></head><body  background="image/pmiback.gif">';
			echo '<p align="center">';
			echo '<b><font face="����_GB2312">��ӽ�ɫʧ�ܣ�</font></b><br>';
			echo '<p align="center">';
		   	echo "<a href='rolereg.php'><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>";
		     	echo '</body></html>';
			exit();		
		}
		$dblink1->close();
		echo '<html><head><title>������Ϣ</title></head><body  background="image/pmiback.gif">';
		echo '<p align="center">';
		echo '<b><font face="����_GB2312">��ӽ�ɫ�ɹ���</font></b><br>';
		echo '<p align="center">';
		echo "<a href='role.php?numb=1'><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>";
		echo '</body></html>';
		exit();		
		
	}

?>