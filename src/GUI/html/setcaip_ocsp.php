<?php
    include("constant.php");
    @session_start();

    //echo "ocspser";
    if($manager_ID==NULL)
	{
        echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '���ȵ�½��<p>';
	    echo '<a href="login.html">����</a>';
        echo '</b></body></html>';
        exit();
	}
    echo '<html><head><title>OCSP����������</title></head><body  background="image/pmiback.gif"><center><font face="����_GB2312"><b>';
    echo "$REMOTE_ADDR";
	echo "��������OCSP��������IP��ַ�ͷ���˿�</b><br><br>";

    $ipss=IsIPStr($ocsp_addr);
    //echo "$ipss";
    if ($ipss != 10)
	{
		echo "OCSP���������õ�IP��ַ������������ϸ��飡"."<br>";
		echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
		exit();
	}

	if (!VarIsValid($ocsp_addr,1) or !VarIsValid($ocsp_port,3) or ($ocsp_port>=65536) or ($ocsp_port<=0))
	{
		echo "OCSP���������õ�IP��ַ��˿���������,����ϸ��飡"."<br>";
		echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
		exit();
	}
	$ret=SetOCSP($ocspRadioGroup,$ocsp_addr,$ocsp_port);

    echo "OCSP�����������޸ĳɹ���";
    
    //------------20060101;by yt
    $cmd=MYSUDO.MYCLI."\\\"ocsp set addr $ocsp_addr $ocsp_port\\\"";
    exec($cmd,$a);
    $cmd=MYSUDO.MYCLI."\\\"ocsp status $ocspRadioGroup\\\"";
    exec($cmd,$a);    
  
	echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
?>