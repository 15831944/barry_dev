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
<title>setcaip</title>
</head>
<body background="image/pmiback.gif">
<?php
	print("<center><b><font face=\"����_GB2312\"><b>��ѡ��ʹ�õ�֤����֤��ʽ</b></font><br>");
	print("<form name=\"setcaip\" method=\"post\">
	        <input type=\"submit\" value=\"OCSP������֤��ʽ\" name=\"OCSP\" length=100 onclick=\"setcaip.action='setcaip_ocsp.php'\">
		<br>
		<br>
		<br>
	        <input type=\"submit\" value=\"��������֤��ʽ\" name=\"NOONLINE\" length=100 onclick=\"setcaip.action='setcaip_noonline.php'\">
		<br>
		<br>
		<br>
		<a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>
		</center></form>");
?>
</body></html>