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

<title>Ӧ�ô���</title>
</head>

<body bgcolor="#eef4f4">

<form name="mapplication_proxy" METHOD="POST" ACTION="">
	<img border="0" src="image/mapphead.gif" width="283" height="57">
<?php
include ("constant.php");

	echo '<br>';
	$a="";
	$cmd=MYSUDO.MYCLI."\\\"app proxy show\\\"";
	$buffer=exec($cmd,$a);
	//print_r($a);
	//echo $a;
	    if($a=="")
	    {
	    	echo "û���ҵ�Ӧ�ô������";
	    }
	    else
	    {	
	    	foreach($a as $buffer)
		    {
		        $lines=htmlspecialchars("$buffer",ENT_QUOTES);
		        $lines=str_replace(" ","&nbsp;",$lines);
		        echo "$lines".'<br>';
		    }
	    }
	    
	    
?>
</form>
</body>
</html>
