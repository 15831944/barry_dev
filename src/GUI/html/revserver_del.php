<!--
**************************************************************************
                  �� PLW517���������������ϵͳWebվ�㡷
                        ��Ȩ���� (C) 2005,2006
**************************************************************************
******************************************************
��Ŀ:�� PLW517���������������ϵͳWebվ�㡷
ģ��:AppProxy�������ɾ������ҳ��
����:
�汾:1.0.1.0
����:2006-1-8
����:Stephen
TODO:
*******************************************************
-->
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
	
	echo '<html><head><title>����Ӧ�÷�������ɾ��</title></head><body background="image/pmiback.gif"><center><font face="����_GB2312"><b>' ;
	$apptype = "backward";
	$proxyservsarray=GetAppSvrList($apptype);
  $nr=count($proxyservsarray);
  $selproxyname=$proxyservsarray[$RadioGroupID-1][2];
  if ($delall==1)
  {    	  
      $ret=ModiServs($RadioGroupID,"",$apptype,"","","","","","","","",9);
      if ($ret)
      {
          echo "����Ӧ�÷����ѳɹ�ȫ��ɾ����"."<br><br>";              
          //exec the Cli.exe commands -- add by ytao
          for($lineapp=0;$lineapp<$nr;$lineapp++)
          {
          		$appnametmp=$proxyservsarray[$lineapp][2];
          		//echo "Now del ".$appnametmp."<br>";
          	  $cmd=MYSUDO.MYCLI."\\\"app proxy set status $appnametmp off\\\"";
              //echo $cmd."<br>";
              exec($cmd,$a);                
              $cmd=MYSUDO.MYCLI."\\\"app proxy remove $appnametmp\\\"";
              //echo $cmd."<br>";
              exec($cmd,$a);            	
          }        
      } else
      {
          echo "����Ӧ�÷���ɾ��û�ܳɹ�����д�ļ�����ʧ�ܣ�"."<br>";
      }
  }
  if (($RadioGroupID<1) && ($delall==0))
  {
      echo "��ѡ��һ������Ӧ�÷������ɾ����"."<br>";
  } 
  else if($delall==0)
  {
    $ret=ModiServs($RadioGroupID,$selproxyname,"","","","","","","","","",2);
    if ($ret)
    {
    	echo "�� $RadioGroupID ������Ӧ�÷����ѳɹ�ɾ����"."<br><br>";                
      
      //exec the Cli.exe commands -- add by ytao
      
      $cmd=MYSUDO.MYCLI."\\\"app proxy set status $selproxyname off\\\"";
      //echo $cmd."<br>";
      exec($cmd,$a);                
      $cmd=MYSUDO.MYCLI."\\\"app proxy remove $selproxyname\\\"";
      //echo $cmd."<br>";
      exec($cmd,$a);
    } 
    else
       echo "����Ӧ�÷���ɾ��û�ܳɹ�����д�ļ�����ʧ�ܣ�"."<br>";
  }
	echo "<p></b></font><a href=\"revserver.php?numb=&numb&apptype=$apptype\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
?>