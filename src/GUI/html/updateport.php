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
		for($i=0;$i<10;$i++)
			if($arr[$i]=="ON")
				break;
        /*
        $dblink1=new DB;
		$dblink1->Database=C_DB_NAME;
		$dblink1->connect();
		if ($dblink->Errno != 0){
			echo '���ݿ�����ʧ��';
			return 0;
		}
		$sql ="SELECT * FROM ".C_APP_WJ_TBL;
		$dblink1->Query($sql);
		$nr=$dblink1->num_rows();
		*/
        $a=0;
		$b=$numbtemp*10;
		$c=0;
		if ($nr != 0)
		{
			//while (list($appid1,$appname1,$listenip1,$protocolname1,$listenport1,$verifymode1,$serverip1,$serverport1,$joindate1,$isdeleted1)=$dblink1->next_record())
			{
				$a=$a+1;
				if ($isdeleted != 1 && $a>$b-10 && $a<=$b )
				{
					if($i==$c)
						break;
					$c=$c+1;
				}
			}
		}
		$temp=$serverip1-0x80000000;
		if($temp<0){
			$B4=($serverip1&0xff);
			$B3=(($serverip1>>8)&0xff);
			$B2=(($serverip1>>16)&0xff);
			$B1=(($serverip1>>24)&0xff);
		}else{
			$B4=($temp&0xff);
			$B3=(($temp>>8)&0xff);
			$B2=(($temp>>16)&0xff);
			$B1=(($temp>>24)&0xff)+0x80;
		}
		$ip_str=$B4.".".$B3.".".$B2.".".$B1;

		print("<html><head><title>�޸ķ�����Ϣ</title></head><body  background=\"image/pmiback.gif\">");
		print("<form name=\"update\" method=\"post\">");
		print("<center>	<br><br><font face=\"����_GB2312\"><b>Ӧ�÷�������&nbsp;&nbsp;&nbsp;
		<input type=\"TEXT\" name=\"appname\" value=$appname1 size=%20 maxlength=20><br>
	����Э������&nbsp;&nbsp;&nbsp; <input type=\"TEXT\" name=\"svname\" value=$protocolname1 size=%20 maxlength=20><br>
	����˿�&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
	<input type=\"TEXT\" name=\"svport\" value=$listenport1 size=%20 maxlength=20><br>
	��̨������IP��ַ<input type=\"TEXT\" name=\"svrip\" value=$ip_str size=%20 maxlength=20><br>
	��̨����˿ں�&nbsp;&nbsp;<input type=\"TEXT\" name=\"svrport\" value=$serverport1 size=%20 maxlength=20><br>
		        <br></b></font><input type=\"submit\" value=\"�޸ķ���\" name=\"add\" onclick=\"update.action='setport1.php?opcode=2'\">
		        &nbsp;&nbsp;&nbsp;&nbsp;<input type=\"submit\" value=\"ȡ���޸�\" name=\"add\" onclick=\"update.action='server.php?numb=1'\">
			</center></form>");
		print("</body></html>");
	}
?>