<?php
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '<p><br><br><center><font face="����_GB2312"><b>���ȵ�½��</font></b><p>';
	    echo '<a href="login.html"><img border="0" src="image/goback.gif" width="40" height="40"></a>';
            echo '</center></body></html>';
            exit();
	}
?>
<html>

<head>
<meta name="GENERATOR" content="Microsoft FrontPage 5.0">
<meta name="ProgId" content="FrontPage.Editor.Document">

<meta http-equiv="Content-Type" content="text/html; charset=gb2312">

<title>License����</title>
</head>

<body bgcolor="#eef4f4">

<form name="mserver_resource" METHOD="POST" ACTION="">

<?php
include ("constant.php");

	echo '<br>';
	echo '<font face="����_GB2312"><b>����Ҫ�ύ�������ִ�Ϊ��</font></b>';
	echo '<hr>';
	$a="";
	$cmd=MYSUDO.LICENSE_GETHDINFO;
	$buffer=exec($cmd,$a);
	//print_r($a);
	//echo $a;

	    	foreach($a as $buffer)
	    	{
		        $lines=htmlspecialchars("$buffer",ENT_QUOTES);
		        $lines=str_replace(" ","&nbsp;",$lines);
		        echo "$lines".'<br>';
		}

	    
	echo '<hr>';
	echo '<br>';
	echo '<font face="����_GB2312"><b>����ϵͳ��ǰ�汾Ϊ��</font></b>';
	echo '<hr>';
	$a="";
	$cmd=MYSUDO.MYCLIVERSION;
	$buffer=exec($cmd,$a);
	//echo $a;
	    	foreach($a as $buffer)
	    	{
		        $lines=htmlspecialchars("$buffer",ENT_QUOTES);
		        $lines=str_replace(" ","&nbsp;",$lines);
		        echo "$lines".'<br>';
		}
	echo '<hr>';
?><p>
<center><a href='license.php'><img border="0" src="image/goback.gif" width="40" height="40"></a>
</center>
</form>
</body>
</html>
