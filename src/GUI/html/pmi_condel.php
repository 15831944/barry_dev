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
	echo '<html><head><title>PMI���ʿ������ù���ɾ��</title></head><body background="image/pmiback.gif"><center><font face="����_GB2312"><b>' ;
    if ($RadioGroupID<1)
    {
        echo "��ѡ��һ���������ɾ����"."<br>";
    } else
    {
        $pminames=GetPMIRules();
        $appname=$pminames[$RadioGroupID-1][1];
        $ret=ModiPMIRules($RadioGroupID,"","","","",0);
        if ($ret)
        {
            echo "�� $RadioGroupID �������ѳɹ�ɾ����"."<br>";
            //---------------20060101;by yt;���ӡ�ɾ������ӿڡ���
            //exec the Cli.exe commands -- add by ytao 
            $cmd=MYSUDO.MYCLI."\\\"app proxy set pmi $appname off\\\"";
            //echo $cmd."<br>";
            exec($cmd,$a);
            //---------------20060101;by yt;���ӡ�ɾ������ӿڡ���
        } else
        {
            echo "����ɾ��û�ܳɹ�����д�ļ�ʧ�ܣ�"."<br>";
        }
    }
    //echo "<p></b></font><a href=\"parameter.php\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";


	echo "<p></b></font><a href=\"pmi_control.php?numb=$numb\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br></center></body></html>";
?>