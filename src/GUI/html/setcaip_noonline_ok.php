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
<title>setcaip_noonline_ok</title>
</head>
<body background="image/pmiback.gif"><?php
include("constant.php");
//include("func_setca.php");

//	print("OCSP������IP��ַ��$ocsp_ip<br>OCSP����˿ںţ�$ocsp_port");
	GetCaTxt(&$ca_pol,
		&$ca_ldapgap,
		&$ca_ldapport,
		&$ca_ocspport,
		&$ca_ocsponldapsuc,
		&$ca_ldapipstr,
		&$ca_ocspipstr,
		&$ca_ldapport2,
		&$ca_ldapipstr2);
		
	$ca_pol=3;
//	$ca_ocspport=$ocsp_port;
//	$ca_ocspipstr=$ocsp_ip;

	$ret=SetCaTxt($ca_pol,
		$ca_ldapgap,
		$ca_ldapport,
		$ca_ocspport,
		$ca_ocsponldapsuc,
		$ca_ldapipstr,
		$ca_ocspipstr,
		$ca_ldapport2,
		$ca_ldapipstr2);

	if ($ret != FALSE)
	{		
		system($apachesudo.CATXTCOM." w",$a);
		CopyFileToElecDisk(SETCAFILE,SETCAFILE_DZP);
		if ($a != 0)
		{
			print("<center><font face=\"����_GB2312\">����OCSP�����ļ�ʧ�ܣ�</font>");
		}else{
			print("<center><font face=\"����_GB2312\">����OCSP�����ļ��ɹ���</font>");
		}
	}
?>

	<p>
	<a href=parameter.php><img border="0" src="image/goback.gif" width="40" height="40"></a>
</center></body></html>