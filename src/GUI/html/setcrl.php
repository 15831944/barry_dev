<?php
    include("constant.php");
    @session_start();

    if($manager_ID==NULL)
	{
        echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '���ȵ�½��<p>';
	    echo '<a href="login.html">����</a>';
        echo '</b></body></html>';
        exit();
	}
    echo '<html><head><title>CRL����������</title></head><body  background="image/pmiback.gif"><center><font face="����_GB2312"><b>';
    echo "$REMOTE_ADDR";
	echo "��������CRL�������Ĳ���</b><br><br>";

    $ipss=IsIPStr($crl_addr);
    if ($ipss != 10)
	{
		echo "CRL���������õ�IP��ַ������������ϸ��飡"."<br>";
		echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
		exit();
	}

	if (!VarIsValid($crl_addr,1) or !VarIsValid($crl_port,3) or ($crl_port>=65536) or ($crl_port<=0))
	{
		echo "CRL���������õ�IP��ַ��˿���������,����ϸ��飡"."<br>";
		echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
		exit();
	}
	$ret=SetCRL($crl_onoff, $crl_addr, $crl_port, $crl_url, $crl_time);

    echo "CRL�����������޸ĳɹ���";
    
    $cmd=MYSUDO.MYCLI."\\\"crl set addr $crl_addr $crl_port\\\"";
    exec($cmd,$a);
    $cmd=MYSUDO.MYCLI."\\\"crl status $crl_onoff\\\"";
    exec($cmd,$a);    
    $cmd=MYSUDO.MYCLI."\\\"crl set url $crl_url\\\"";
    exec($cmd,$a);    
    $cmd=MYSUDO.MYCLI."\\\"crl set timeout $crl_time\\\"";
    exec($cmd,$a);    
  
	echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
?>