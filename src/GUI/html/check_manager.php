<?
include "pmi_db.php";
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '<p><br><br><center><font face="����_GB2312"><b>���ȵ�½��</font></b><p>';
	    echo '<a href="login.html"><img border="0" src="image/goback.gif" width="40" height="40"></a>';
            echo '</center></body></html>';
            exit();
	}
	switch($islogin)
	{
		case '0':
                //---------------20051213;by yy;�޸�ԭ���ݿ��дע��Ϊ�ļ���ʽ
                if (GetManagerExist($mananame1)===false)
                {
                    AddManager($mananame1,$password1);
                    echo '<center><font face="����_GB2312"><b><br>ע��ɹ���</b></font></center>';
	            } else
                {
		            echo '<center><font face="����_GB2312"><b><br>�ù���Ա��ע�����</b></font></center>';
                }
                //---------------20051213;by yy;�޸�ԭ���ݿ��дע��Ϊ�ļ���ʽ

				echo '<html><head><title>����Աע��</title></head><body  background="image/pmiback.gif">';
				echo '<p>';
   	   			echo "<center><a href='manager.php'><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>";
     	   			echo '</center></body></html>';
     	   			exit();

		case '1':

                //del_manager($mananame2,$password3);
                //---------------20051213;by yy;�޸�ԭ���ݿ��дע��Ϊ�ļ���ʽ
                $usercount=GetManagerList();

                $CC=count($usercount);
                if ($CC < 2)
                {
                    echo '<center><font face="����_GB2312"><b><br>����ɾ�����һ������Ա</b></font></center>';
                }
                else if ((GetManagerLgin($mananame2,$password3)) && (ModiManager($mananame2,$password3,0)===true))
                {
                    echo '<center><font face="����_GB2312"><b><br>ע���ɹ�</b></font></center>';
             	} else
                {
            		echo '<center><font face="����_GB2312"><b><br>����Ա�������򱣴����</b></font></center>';
            	}
                //---------------20051213;by yy;�޸�ԭ���ݿ��дע��Ϊ�ļ���ʽ

     	   		echo '<html><head><title>ɾ������Ա</title></head><body  background="image/pmiback.gif">';
				echo '<p>';
   	   			echo "<center><a href='manager.php'><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>";
     	   			echo '</center></body></html>';
     	   			exit();

		case '2':
     	   	    //update_manager($mananame3,$password4,$password5);
                //---------------20051213;by yy;�޸�ԭ���ݿ��дע��Ϊ�ļ���ʽ
                if (GetManagerLgin($mananame3,$password4))
                {
                    if (ModiManager($mananame3,$password5,1)===true)
                    {
                        echo '<center><font face="����_GB2312"><b><br>�޸�����ɹ�</b></font></center>';
                    } else
                    {
                 	      echo '<center><font face="����_<font color="#000000"></font>GB2312"><b><br>����Ա�������򱣴����</b></font></center>';
                    }
                } else
                {
                    echo '<center><font face="����_GB2312"><b><br>����Ա�������</b></font></center>';	
                }
                //---------------20051213;by yy;�޸�ԭ���ݿ��дע��Ϊ�ļ���ʽ

                echo '<html><head><title>�޸Ĺ���Ա����</title></head><body  background="image/pmiback.gif">';
				echo '<p>';
   	   			echo "<center><a href='manager.php'><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>";
     	   			echo '</center></body></html>';
     	   			exit();

	}
?>