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
	echo '<html><head><title>PMI���ʿ������ù����޸�</title></head><body background="image/pmiback.gif"><center><font face="����_GB2312"><b>' ;
    if (VarIsValid($sysname,1))
    {
      if ($opcode==1)
      {
          if (!PMIRuleExists($appselect,0,3))
          {
              $ret=AddPMIRules($appselect,$orgname,$sysname,$swselect);
              if ($ret)
              {
                  echo "��������ӳɹ���"."<br>";
                  
                  //---------------20060101;by yt;���ӡ����PMI���򡱣�
                  //exec the Cli.exe commands -- add by ytao
                  $cmd=MYSUDO.MYCLI."\\\"app proxy pmi sysname $appselect $sysname\\\"";
                  //echo $cmd."<br>";
                  exec($cmd,$a);
                  
                  //if (($swselect=="on") or ($swselect=="ON"))
                  //{
                  	$cmd=MYSUDO.MYCLI."\\\"app proxy set pmi $appselect $swselect\\\"";
                  	//echo $cmd."<br>";
                  	exec($cmd,$a);
                  //}

                  //---------------20060101;by yt;���ӡ����PMI���򡱣�
              } else
              {
                  echo "�������û�ܳɹ�����д�ļ�����ʧ�ܣ�"."<br>";
              }
          } else
          {
              echo "Ӧ�÷�������Ϊ<font color=\"#0000FF\"> $appselect </font>��PMI�����Ѿ����ڣ�";
              echo "<br>������ѡ��Ӧ�÷������ƣ�"."<br>";
          }
      } else if($opcode==2)
      {
          if (!PMIRuleExists($appselect,$RuleID,3))
          {
              //echo "$appselect,$sysname,$orgname,$swselect";
              $ret=ModiPMIRules($RuleID,$appselect,$orgname,$sysname,$swselect,1);
              if ($ret)
              {
              	 
                  echo "�� $RuleID ���������޸ĳɹ���"."<br>";
                  //---------------20060101;by yt;���ӡ��޸�PMI���򡱣�
                  //exec the Cli.exe commands -- add by ytao
                  $cmd=MYSUDO.MYCLI."\\\"app proxy pmi sysname $appselect $sysname\\\"";
                  //echo $cmd."<br>";
                  exec($cmd,$a);
                  
                  //if (($swselect=="on") or ($swselect=="ON"))
                  //{
                  	$cmd=MYSUDO.MYCLI."\\\"app proxy set pmi $appselect $swselect\\\"";
                  	//echo $cmd."<br>";
                  	exec($cmd,$a);
                  //}                  
                  
                  //---------------20060101;by yt;���ӡ��޸�PMI���򡱣�
              } else
              {
                  echo "�����޸�û�ܳɹ�����д�ļ�����ʧ�ܣ�"."<br>";
              }
          } else
          {
              echo "Ӧ�÷�������Ϊ<font color=\"#0000FF\"> $appselect </font>�������Ѿ�����PMI��������ͻ��";
              echo "<br>������ѡ��Ӧ�÷������ƣ�"."<br>";
          }
      }
    }
    else
    {
      echo "Ӧ��ϵͳ���Ʋ�����ո���ڣ����޸ĺ��ٲ�����";
    }
    //echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";


	echo "<p></b></font><a href=\"pmi_control.php?numb=$numb\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
?>