<?
include "pmi_db.php";
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  bgcolor="#eef4f4"><b>' ;
	    echo '���ȵ�½��<p>';
	    echo '<a href="login.html">����</a>';
            echo '</b></body></html>';
            exit();			
	}
	$dblink=new DB;
	$dblink->Database=C_DB_NAME;
	$dblink->connect();
	if ($dblink->Errno != 0)
		die();
	$sql="select * from ".C_APP_WJ_TBL." where appname='".$appnamex."'";
	$dblink->Query($sql);
	$nr=$dblink->num_rows();
	if ($nr != 0)
	{
		list($appid,$appname,$listenip,$protocolname,$listenport,$verifymode,$serverip,$serverport,$joindate,$isdeleted)=$dblink->next_record();
		$temp=$serverip-0x80000000;
		if($temp<0){
			$B4=($serverip&0xff);
			$B3=(($serverip>>8)&0xff);
			$B2=(($serverip>>16)&0xff);
			$B1=(($serverip>>24)&0xff);
		}else{
			$B4=($temp&0xff);
			$B3=(($temp>>8)&0xff);
			$B2=(($temp>>16)&0xff);
			$B1=(($temp>>24)&0xff)+0x80;
		}
		$ip_str=$B4.".".$B3.".".$B2.".".$B1;

		echo '<html><head><title>Ӧ�÷�����Ϣ</title></head><body  background="image/pmiback.gif">' ;
		echo "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font face=\"����_GB2312\">Ӧ�÷���ID��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font><font face=\"����_GB2312\" color=#0000ff>$appid</font></p>";
		echo "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font face=\"����_GB2312\">Ӧ�÷������ƣ�&nbsp;&nbsp;&nbsp;&nbsp;</font><font face=\"����_GB2312\" color=#0000ff>$appname</font></p>";
		echo "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font face=\"����_GB2312\">����IP��ַ��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font><font face=\"����_GB2312\" color=#0000ff>$listenip</font></p>";
		echo "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font face=\"����_GB2312\">����Э�����ƣ�&nbsp;&nbsp;&nbsp;&nbsp;</font><font face=\"����_GB2312\" color=#0000ff>$protocolname</font></p>";
		echo "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font face=\"����_GB2312\">�����˿ڣ�&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font><font face=\"����_GB2312\" color=#0000ff>$listenport</font></p>";
		echo "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font face=\"����_GB2312\">֤����֤���ã�&nbsp;&nbsp;&nbsp;&nbsp;</font><font face=\"����_GB2312\" color=#0000ff>$verifymode</font></p>";
		echo "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font face=\"����_GB2312\">��̨������IP��ַ��</font><font face=\"����_GB2312\" color=#0000ff>$ip_str</font></p>";
		echo "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font face=\"����_GB2312\">��̨����˿ڣ�&nbsp;&nbsp;&nbsp;&nbsp;</font><font face=\"����_GB2312\" color=#0000ff>$serverport</font></p>";
		echo "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font face=\"����_GB2312\">����ʱ�䣺&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font><font face=\"����_GB2312\" color=#0000ff>".date("Y/m/d--H:i:s",$joindate)."</font></p>";
		if($isdeleted==0)
			echo "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font face=\"����_GB2312\">ɾ����&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font><font face=\"����_GB2312\" color=#0000ff>��</font></p>";
		echo "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"pmirole.php?appid=$appid&rolenumb=1\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a></p>";
            echo '</body></html>';
        }
	$dblink->close();
?>
		
