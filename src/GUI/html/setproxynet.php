<?php
	include ("constant.php");

//echo "opcode=".$opcode."<br>";
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '���ȵ�½��<p>';
	    echo '<a href="login.html">����</a>';
            echo '</b></body></html>';
            exit();			
	}
	echo '<html><head><title>��Ϣ����</title></head><body  background="image/pmiback.gif"><center><font face="����_GB2312"><b>' ;
	if ($opcode == 1)
	{
		if (IsIPStr($ip_eth1) != 10)
		{
			echo "�����ڵ�IP��ַ������������ϸ��飡"."<br>";
			echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
			exit();
		}
		if (IsMaskStr($mask_eth1)!=10)
		{
			echo "�����ڵ�IP��ַ����������������ϸ��飡"."<br>";
			echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
			exit();
		}
		$ret=SetIPAddr(1,$ip_eth1,$mask_eth1);
		
		//------------20060101;by yt
	  $cmd=MYSUDO.REBOOTSERV;
		exec($cmd,$a);
		$cmd=MYSUDO . "echo 'Listen 127.0.0.1:5680' \> /etc/apache2/ports.conf";
		exec($cmd);
		$cmd=MYSUDO . "echo 'Listen " . $ip_eth1 . ":5680' \>\> /etc/apache2/ports.conf";
		exec($cmd);
		write_ed();
		$cmd=MYSUDO . " /sbin/reboot -f";
		echo passthru($cmd);
		echo "�޸ĳɹ�<p>\n";
		echo "reboot ......<p>\n";
	  
	}

	if ($opcode == 2)
	{
		if (IsIPStr($ip_eth0) != 10)
		{
			echo "�����ڵ�IP��ַ������������ϸ��飡"."<br>";
			echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
			exit();
		}
		if (IsMaskStr($mask_eth0)!=10)
		{
			echo "�����ڵ�IP��ַ����������������ϸ��飡"."<br>";
			echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
			exit();
		}
		if (!isset($ensure))
		{
			GetGateway($ip_gateway,$host_name);
			if (InOneSubnet($ip_eth0,$mask_eth0,$ip_gateway,$mask_eth0))
				$ensure=true;
			else
			{
				echo "�޸�������IP��ַ<br>";
				echo "������IP��ַ".$ip_eth0."������������IP��ַ".$ip_gateway."<br>";
				echo "����ͬһ�����ڣ����ܻ�Ӱ���������������ʣ�<br>";
				echo "�������Ҫ�����޸ģ�����<a href=\"setproxynet.php?ip_eth0=$ip_eth0&mask_eth0=$mask_eth0&opcode=2&ensure=true\">ȷ��</a><br>";
				echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
				exit();
			}
		}
		if ($ensure)
			$ret=SetIPAddr(0,$ip_eth0,$mask_eth0);
			//------------20060101;by yt
		$cmd=MYSUDO."/etc/init.d/networking restart";
	  	exec($cmd,$a);
	  	$cmd=MYSUDO.REBOOTSERV;
			//echo $cmd;
			exec($cmd,$a);
			write_ed();
		echo "�޸ĳɹ�<p>\n";
	}

	if ($opcode == 3)
	{
		if (IsIPStr($ip_gateway) != 10)
		{
			echo "�����ڵ�����IP��ַ������������ϸ��飡"."<br>";
			echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
			exit();
		}
//		echo $ip_gateway,$host_name;
		if (!isset($ensure))
		{
			GetIPAddr(0,$ip_eth0,$mask_eth0);
			if (InOneSubnet($ip_eth0,$mask_eth0,$ip_gateway,$mask_eth0))
				$ensure=true;
			else
			{
				echo "�޸�����IP��ַ<br>";
				echo "������IP��ַ".$ip_eth0."������������IP��ַ".$ip_gateway."<br>";
				echo "����ͬһ�����ڣ����ܻ�Ӱ���������������ʣ�<br>";
				echo "�������Ҫ�����޸ģ�����<a href=\"setproxynet.php?ip_gateway=$ip_gateway&host_name=$host_name&opcode=3&ensure=true\">ȷ��</a><br>";
				echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
			exit();
			}
		}
		if ($ensure)
			$ret=SetGateway($ip_gateway,$host_name);
			
			//------------20060101;by yt
			//$cmd=MYSUDO."route add default gw $ip_gateway";
		$cmd=MYSUDO."/etc/init.d/networking restart";
	  	exec($cmd,$a);
		echo "�޸ĳɹ�<p>\n";
		/*
		$cmd=MYSUDO."route add default gw ". $ip_gateway;
		exec($cmd,$a);
		*/
			
	}

	echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
?>
