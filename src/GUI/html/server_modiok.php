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
	echo '<html><head><title>Ӧ�÷��������޸�</title></head><body background="image/pmiback.gif"><center><font face="����_GB2312"><b>' ;
	GetIPAddr(1,$ip_eth1,$mask_eth1);
    if (!VarIsValid($proxyname,1))
    {
        echo "���������в�����ո���ڣ����޸ĺ��ٲ�����";
    } 
    else if(!VarIsValid($svrsport,3))
    {
        echo "����˿��в�����ո������ִ��ڣ����޸ĺ��ٲ�����";
    } 
    else if(($asport!="") && (!VarIsValid($asport,3)))
    {
        echo "��̨����˿��в�����ո������ִ��ڣ����޸ĺ��ٲ�����";
    } 
    else if(($asaddr!="") && ((!VarIsValid($asaddr,1)) or (IsIPStr($asaddr)!=10)))
    {
    	if ($proxytype == "forward")
        	echo "��̨��������ַ��ʽ����ȷ���пո���ڣ����޸ĺ��ٲ�����";
        else 
        	echo "�Է�PWL517���IP��ַ��ʽ����ȷ���пո���ڣ����޸ĺ��ٲ�����";
    } 
    else if(($proxytype == "forward") && 
    		(!isset($ensure)) && 
    		(!InOneSubnet($ip_eth1,$mask_eth1,$asaddr,$mask_eth1)))
    {
    
		//����ͬһ����
		echo '<html><head><title>������Ϣ</title></head><body  background="image/pmiback.gif"><center>';
		echo "<font face=\"����_GB2312\" size=4 color=\"#0a8484\"><b>���ô������</b></font><br>";
		echo "�������õĺ�̨������IP��ַ".$asaddr."��������IP��ַ".$ip_eth1."<br>";
		echo "����ͬһ�����ڣ���������������޷��ṩ�������<br>";
		echo "�������Ҫ�������ã�����";
		echo "<a href=\"server_modiok.php?proxyname=$proxyname&proxytype=$proxytype&svrstype=$svrstype&svrsport=$svrsport&Msecstag=$Msecstag&asaddr=$asaddr&asport=$asport&openstat=$openstat&denypage1=$denypage1&opcode=$opcode&ensure=true&RuleID=$RuleID&adtime=$adtime\">ȷ��</a><br>";
		echo "��������������Ļ��˽����޸Ļ���<a href=\"server.php?numb=1\">���ô������</a><br></center>";
		echo '</body></html>';
		exit();
	}
    else
    {
    	if ($asport=="") $asport="-";
    	if ($asaddr=="") $asaddr="-";
		if ($opcode==1)
		{
        	if (!AppSvrsExists($proxytype,$proxyname,$svrsport,0,6))
          	{
            	$addtime=date('Y/m/d--H:i:s');
              
              	if (($proxytype=="forward") or ($proxytype=="Forward"))
              	{
              		$Msecstag="ssl";
              	} else
              	{
                	$Msecstag="plain";
              	}
              	$ret=AddServs($proxyname,$proxytype,$svrstype,$svrsport,$Msecstag,$asaddr,$asport,$openstat,$addtime,$denypage1);
              	if ($ret)
              	{
              		if (($proxytype=="forward") or ($proxytype=="Forward"))
						echo "�����������ӳɹ���"."<br>\n";
                  	else
                  		echo "��������������ӳɹ���"."<br>\n";
                  	//------------20060101;by yt;���ӡ����Ӧ�÷�������ء���
                  	AosProxyAddCli($proxyname,$proxytype,$svrstype,$svrsport,$Msecstag,$asaddr,$asport,$openstat,$addtime,$denypage1);
              	} 
              	else
              	{
                	echo "����������û�ܳɹ�����д�ļ�����ʧ�ܣ�"."<br>\n";
              	}
          	} 
          	else
          	{
            	echo "��������Ϊ<font color=\"#0000FF\"> $proxyname </font><br> �� <br>\n";
              
              	if (($proxytype=="forward") or ($proxytype=="Forward"))
              	{
                	echo "<font color=\"#0000FF\"><����></font>���������У�\n";
              	}
              	if (($proxytype=="backward") or ($proxytype=="Backward"))
              	{
                	echo "<font color=\"#0000FF\"><����></font>���������У�\n";
              	}
              	echo "����˿�Ϊ<font color=\"#0000FF\"> $svrsport </font><br>�Ĵ�������Ѿ����ڣ�\n";
              	echo "<br>��������д�������ƻ����˿ڣ�"."<br>\n";
          	}
      	} 
      	else if($opcode==2)
      	{
        	if (!AppSvrsExists($proxytype,$proxyname,$svrsport,$RuleID,2))
        	{
            	if (($proxytype=="forward") or ($proxytype=="Forward"))
            	{
               		$Msecstag="ssl";
            	} else
            	{
               		$Msecstag="plain";
            	}
            	//$addtime=date('Y/m/d--H:i:s');
            	//ModiServs($PRID,$PProxyname,$PProxytype,$PSvrtype,$PSvrport,$PSecutag,$PSname,$PSport,$POpensw,$PAddtime,$Pdenypages,$MType)
            	$ret=ModiServs($RuleID,$proxyname,$proxytype,$svrstype,$svrsport,$Msecstag,$asaddr,$asport,$openstat,$adtime,$denypage1,1);
            	if ($ret)
            	{
            		if (($proxytype=="forward") or ($proxytype=="Forward"))
              			echo "�� $RuleID ������������޸ĳɹ���"."<br>";
              		else
                		echo "�� $RuleID ���������������޸ĳɹ���"."<br>";
                
              		//exec the Cli.exe commands -- add by ytao
              		$cmd=MYSUDO.MYCLI."\\\"app proxy set status $proxyname off\\\"";
              		exec($cmd,$a);
              
              		$cmd=MYSUDO.MYCLI."\\\"app proxy remove $proxyname\\\"";
              		exec($cmd,$a);
                
                  	//------------20060101;by yt;���ӡ����Ӧ�÷�������ء���
                  	AosProxyAddCli($proxyname,$proxytype,$svrstype,$svrsport,$Msecstag,$asaddr,$asport,$openstat,$addtime,$denypage1);

            	} else
            	{
            		if (($proxytype=="forward") or ($proxytype=="Forward"))
                		echo "��������޸�û�ܳɹ�����д�ļ�����ʧ�ܣ�"."<br>";
             		else
             			echo "�����������޸�û�ܳɹ�����д�ļ�����ʧ�ܣ�"."<br>";
            	}
        	} else
        	{
            	if (($proxytype=="forward") or ($proxytype=="Forward"))
            	{
                	echo "<font color=\"#0000FF\"><����></font>���������У�";
            	}
            	if (($proxytype=="backward") or ($proxytype=="Backward"))
            	{
                	echo "<font color=\"#0000FF\"><����></font>���������У�";
            	}
            	echo "����˿�<font color=\"#0000FF\"> $svrsport </font>�Ѿ����ڣ�";
            	echo "<br>��������д����˿ڣ�"."<br>";
        	}
      	}
    }

	if (($proxytype=="forward") or ($proxytype=="Forward"))
		echo "<p></b></font><a href=\"server.php?numb=$numb&apptype=$proxytype\">";
	else
		echo "<p></b></font><a href=\"revserver.php?numb=$numb&apptype=$proxytype\">";
	echo "<img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\">";
	echo "</a><br></center></body></html>";
?>