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
	echo '<html><head><title>Denypage�޸�</title></head><body background="image/pmiback.gif"><center><font face="����_GB2312"><b>' ;
    //************************************************************************************
    if (!VarIsValid($denypname,1))
    {
        echo "Denypage�����в�����ո���ڣ����޸ĺ��ٲ�����<br>";
    } else if(!VarIsValid($denyppath,1))
    {
        echo "Denypage�ļ����в�����ո���ڣ����޸ĺ��ٲ�����<br>";
    } else
    {
      
      //-------------20051221;by cw;ԭ·�����ʹ��,��ȡ�����Ĺ̶�·��DENYPAGEFILEPATH
      if ($opcode==1)
      {
          //------------------------20060101;by cw;Denypage�ܸ���������256�����ڣ�
          $dcount=count(GetDenysList());
          if ($dcount>=256)
          {
              echo "����Denypage�������ƣ���256�������ʧ�ܣ�";
              echo "<p></b></font><a href=\"denypage.php?numb=$numb\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";  
              exit();
          }
          //------------------------20060101;by cw;Denypage�ܸ���������256�����ڣ�
          
           if($denypfile_size > 5000)
							{
								echo "<center><font face=\"����_GB2312\"><b>�ļ����ܴ���5K,�ϴ�ʧ�ܣ�����</b></font></center>";
								echo "<p></b></font><a href=\"denypage.php?numb=$numb\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>"; 
								exit();
							}
							
          if (!DenypageExists($denypname,$denyppath))
          {
              $Mdenyppath=DENYPAGEFILEPATH.$denyppath;              
              //echo "path=   ".$_FILES['denypfile']['tmp_name'];
              
        
              
        //add write option to the file   --by ytao
	    	$mysudo = MYSUDO;
	    	$chmodaddow = ADDOW;
	    	$cmd = 0;
	    	$cmd = $mysudo.$chmodaddow.DENYPAGEFILEPATH;
	    	/* for test --by ytao
	    	echo '<html>';
		echo '<head>';
		echo "this is the $cmd:";
	    	echo $cmd;
	    	echo '</head>';
		echo '<body>';
		echo '</body>';
		echo '</html>';
	    	*/
	    	exec($cmd);
              
              if (copy($denypfile,$Mdenyppath))
              //if (move_uploaded_file($_FILES['userfile']['tmp_name'], $uploadfile))
              //if (move_uploaded_file($_FILES['denypfile']['tmp_name'],"denyTTT.zip"))
              {
		
		    	//del write option to the file   --by ytao
		    	$mysudo = MYSUDO;
		    	$chmodaddow = DELOW;
		    	$cmd = 0;
		    	$cmd = $mysudo.$chmodaddow.DENYPAGEFILEPATH;
		    	/* for test --by ytao
		    	echo '<html>';
			echo '<head>';
			echo "this is the $cmd:";
		    	echo $cmd;
		    	echo '</head>';
			echo '<body>';
			echo '</body>';
			echo '</html>';
		    	*/    	
		    	exec($cmd);
		
                  $ret=AddDenyPage($denypname,$denyppath);
                  if ($ret)
                  {
                      echo "Denypage����ӳɹ���"."<br>";
                      //---------------20060101;by yt;���ӡ����Denypage����ӿڡ���
                      //exec the Cli.exe commands -- add by ytao
                      $cmd=MYSUDO.MYCLI."\\\"deny page import $denypname /usr/local/AOS/Config/Denypages/$denyppath\\\"";
                      //echo $cmd."<br>";
                      exec($cmd,$a);  
                      //---------------20060101;by yt;���ӡ����Denypage����ӿڡ���
                  } else
                  {
                      echo "Denypage���û�ܳɹ�����д�ļ�����ʧ�ܣ�"."<br>";
                  }
              } else
              {
                  echo "Denypage���û�ܳɹ����ϴ��ļ�ʧ�ܣ�"."<br>";
              }
          } else
          {
              echo "����Ϊ<font color=\"#0000FF\"> $denypname </font>��Denypage���ƻ��ļ��Ѿ����ڣ�<br>��������дDenypage���ƻ��ļ�����"."<br>";
          }
      } else if($opcode==2)
      {
          $df=DENYPAGEFILEPATH.$denyppath;
          //echo $df;
              
          //$cmd=MYSUDU."mv ".$denypfile." ".DENYPAGEFILEPATH.$denyppath;
          //echo $cmd;
          //exec($cmd);         
          
              if($denypfile_size > 5000)
							{
								echo "<center><font face=\"����_GB2312\"><b>�ļ����ܴ���5K,�ϴ�ʧ�ܣ�����</b></font></center>";
								echo "<p></b></font><a href=\"denypage.php?numb=$numb\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>"; 
								exit();
							}
							
        //add write option to the file   --by ytao
	    	$mysudo = MYSUDO;
	    	$chmodaddow = ADDOW;
	    	$cmd = 0;
	    	$cmd = $mysudo.$chmodaddow.DENYPAGEFILEPATH;
	    	/* for test --by ytao
	    	echo '<html>';
		echo '<head>';
		echo "this is the $cmd:";
	    	echo $cmd;
	    	echo '</head>';
		echo '<body>';
		echo '</body>';
		echo '</html>';
	    	*/
	    	exec($cmd);
          
          if (copy($denypfile,$df))
          {
              echo "Denypage�޸��ѳɹ���"."<br>";
              //---------------20060101;by yt;���ӡ��޸�Denypage����ӿڡ���
              //exec the Cli.exe commands -- add by ytao
              $cmd=MYSUDO.MYCLI."\\\"deny page import $denypname /usr/local/AOS/Config/Denypages/$denyppath\\\"";
              //echo $cmd."<br>";
              exec($cmd,$a);  
              //---------------20060101;by yt;���ӡ��޸�Denypage����ӿڡ���
              
          } else
          {
              echo "Denypage�޸�û�ܳɹ����ϴ��ļ�ʧ�ܣ�"."<br>";
          }
          
          		//del write option to the file   --by ytao
		    	$mysudo = MYSUDO;
		    	$chmodaddow = DELOW;
		    	$cmd = 0;
		    	$cmd = $mysudo.$chmodaddow.DENYPAGEFILEPATH;
		    	/* for test --by ytao
		    	echo '<html>';
			echo '<head>';
			echo "this is the $cmd:";
		    	echo $cmd;
		    	echo '</head>';
			echo '<body>';
			echo '</body>';
			echo '</html>';
		    	*/    	
		    //	exec($cmd);
          

      }
      //-------------20051221;by cw;ԭ·�����ʹ��,��ȡ�����Ĺ̶�·��DENYPAGEFILEPATH
    } 
    //************************************************************************************
    echo "<p></b></font><a href=\"denypage.php?numb=$numb\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
?>