<?php
	include ("constant.php");

	@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '���ȵ�½��<p>';
	    echo '<a href="login.html">����</a>';
            echo '</b></body></html>';
            exit();
	}
	echo '<html><head><title>PMI��������</title></head><body  background="image/pmiback.gif"><center><font face="����_GB2312"><b>' ;
	
	if (IsIPStr($pmi_addr) != 10)
	{
		echo "PMIȫ�ֲ�����IP��ַ������������ϸ��飡"."<br>";
		echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
		exit();
	}
	
	/*GetIPAddr(1,$ip_eth1,$mask_eth1);
	if (!InOneSubnet($ip_eth1,$mask_eth1,$pmi_addr,$mask_eth1)))
	{
		echo "PMI������IP�����������������ڣ�"."<br>";
		echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
		exit();
	}*/
	
	if (!VarIsValid($pmi_addr,1) or !VarIsValid($pmi_port,3) or ($pmi_port>=65536) or ($pmi_port<=0))
	{
		echo "PMIȫ�ֲ�����IP��ַ��˿���������,����ϸ��飡"."<br>";
		echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
		exit();
	}
    if (!VarIsValid($pmi_org,1))
	{
		echo "PMIȫ�ֲ�������֯�����������пո�,����ϸ��飡"."<br>";
		echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
		exit();
	}
	
	if ( (IsIPStr($pmi_ca_addr) != 10) or !VarIsValid($pmi_ca_addr,1) )
	{
		echo "CA������IP��ַ��������,����ϸ��飡"."<br>";
		echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
		exit();
	}

	if ( !VarIsValid($pmi_ca_port,3) or ($pmi_ca_port>=65536) or ($pmi_ca_port<=0))
	{
		echo "CA�������Ķ˿���������,����ϸ��飡"."<br>";
		echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
		exit();
	}
	
	if ( !VarIsValid($pmi_ldap_port,3) or ($pmi_ldap_port>=65536) or ($pmi_ldap_port<=0))
	{
		echo "LDAP�������Ķ˿���������,����ϸ��飡"."<br>";
		echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
		exit();
	}
	
	$ret=AosSetPMI($pmiRadioGroup,$pmi_addr,$pmi_port,$pmi_org);
	
	SetPMICfg($pmi_ldap_port,$pmi_subtree,$pmi_addr,$pmi_port,$pmi_org,$pmi_ca_addr,$pmi_ca_port,$pmi_ca_dn);


    
    //------------20060101;by yt
    $cmd=MYSUDO.MYCLI."\\\"amm status $pmiRadioGroup\\\"";
    exec($cmd,$a);
    $cmd=MYSUDO.MYCLI."\\\"amm set addr $pmi_addr $pmi_port\\\"";
    exec($cmd,$a);  
    $cmd=MYSUDO.MYCLI."\\\"amm set org $pmi_org\\\"";
    exec($cmd,$a);   
    
    echo "PMIȫ�ֲ����޸ĳɹ���";
    echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
?>