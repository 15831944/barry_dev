<?php
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '���ȵ�½��<p>';
	    echo '<a href="login.html">����</a>';
            echo '</b></body></html>';
            exit();			
	}
?>
<html>
<head>
<title>setcaip_noonline</title>
</head>
<body background="image/pmiback.gif"><?php
include("constant.php");
//include("func_setca.php");

//	print("$REMOTE_ADDR");
/*
	print("������OCSP��������IP��ַ�ͷ���˿�<br>");
	$a=filesize($CAIPCFGFILE);
	if ($a < 28)//!= 36)
	{
		print("OCSP�����ļ����Ȳ��ԣ��ļ����ȣ�".$a);
//		print("	<a href=\"index.php\">������ҳ</a>");
//		return;
	}
	else
	{
		system($apachesudo.CATXTCOM." r",$a);
		system($apachesudo."chmod "."666 ".CATXTFILE,$b);
//		print("$a<br>");
		if ($a != 0 || $b != 0)
		{
			print("����OCSP�����ļ�ʧ�ܣ�");
//			print("	<a href=\"index.php\">������ҳ</a>");
//			return;
		}
		else
		{
			$fcont=file(CATXTFILE);
			list($key_pro,$catxtstr) = each($fcont);
			
			GetCaTxt(&$ca_pol,
				&$ca_ldapgap,
				&$ca_ldapport,
				&$ca_ocspport,
				&$ca_ocsponldapsuc,
				&$ca_ldapipstr,
				&$ca_ocspipstr,
				&$ca_ldapport2,
				&$ca_ldapipstr2);
		}
	}*/

	print("<form name=\"setcaip_noonline\" method=\"post\">
		<font face=\"����_GB2312\"><b>ע�⣺<br><center>
		ʹ�÷�������֤��ʽ���ڰ�ȫ�ϵ�������
		��ȷ��ʹ�÷�������֤��ʽ��<br>�������������������������ҳ�桱��</b></font><p>
	        <input type=\"submit\" value=\"ȷ��\" name=\"NOONLINE\" length=20 onclick=\"setcaip_noonline.action='setcaip_noonline_ok.php'\">
		<br>
		<br>
		<br>
		<a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>
		</center></form>");
?>
</body></html>