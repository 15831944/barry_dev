<?php
	include ("constant.php");
    	//header('Cache-control: private, must-revalidate');
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
	echo '<html><head>';
    echo '<title>Denypage����ɾ��</title></head><body background="image/pmiback.gif">';
    echo '<form name="DenypageDel" method="post"><center><font face="����_GB2312"><b>';
    //echo '<table><tr><td>';
    if ($RadioGroupID<1)
    {
        echo "��ѡ��һ��Denypage����ɾ����"."<br>";
    } else
    {
        if (!isset($deldp))
        {
            //echo "<input type=\"hidden\" name=\"RadioGroupID\" value=$RadioGroupID><br>";
            //echo "<input type=\"hidden\" name=\"numb\" value=$numb><br>";
            //echo "<input type=\"hidden\" name=\"denypname\" value=$denypname><br>";
            echo "ɾ����Denypage��������Ӧ�÷����Denypage����&nbsp;&nbsp;&nbsp;&nbsp;";
            echo "<a href=\"denypage_del.php?RadioGroupID=$RadioGroupID&numb=$numb&deldp=0\">ɾ������</a><br><br>";
            echo "����<br><br>ֻɾ����Denypage����ɾ��Ӧ�÷����ӦDenypage�&nbsp;&nbsp;";
            echo "<a href=\"denypage_del.php?RadioGroupID=$RadioGroupID&numb=$numb&deldp=1\">��ɾ������</a><br><br><br>";
        } else
        {   
        		$denynames=GetDenysList();
	    			$denypname=$denynames[$RadioGroupID-1];
	    			
            $denytable=GetDenypagesList();
	    			$denyfile=DENYPAGEFILEPATH.$denytable[$RadioGroupID-1][2];
	    			//echo $denyfile."<br>";
	    			
            if ($deldp==0)
            {
                $ret=ModiDenyPages($RadioGroupID,"","",2);
                /*
                if ($ret)
                {
                    $ret=ModiServsPara($denypname,"-",0);
                    echo $denypname;
                }
                */
            } else
            {
                $ret=ModiDenyPages($RadioGroupID,"","",0);
            }
            
            if ($ret)
            {
                echo "�� $RadioGroupID ��Ӧ�÷����ѳɹ�ɾ����"."<br><br>";  
                //---------------20060101;by yt;���ӡ�ɾ��Denypage����ӿڡ���
                //exec the Cli.exe commands -- add by ytao
                $cmd=MYSUDO.MYCLI."\\\"deny page remove $denypname\\\"";
                 //echo $cmd."<br>";
                 exec($cmd,$a);  
                $cmd=MYSUDO."rm -f $denyfile";
                 //echo $cmd."<br>";
                 exec($cmd,$a);   
                 //---------------20060101;by yt;���ӡ�ɾ��Denypage����ӿڡ���            

            } else
            {
                echo "Ӧ�÷���ɾ��û�ܳɹ�����д�ļ�����ʧ�ܣ�"."<br>";
            }
        }
    }
    //echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";

    //echo '</td></tr></table>';
	echo "<p></b></font><a href=\"denypage.php?numb=$numb\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></form></body></html>";
?>