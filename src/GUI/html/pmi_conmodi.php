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
	echo '<html><head><title>PMI���ʿ������ù����޸�</title></head>';
    echo '<body background="image/pmiback.gif"><form name="PMIconmodi" METHOD="POST" ACTION="pmi_conmodiok.php?opcode=2">';
    echo '<center><font face="����_GB2312"><b>';
    //echo "radioid=$RadioGroupID";
    if ($RadioGroupID<1)
    {
        echo "��ѡ��һ����������޸ģ�"."<br>";
        echo "<p></b>";
        echo "</font><a href=\"pmi_control.php?numb=$numb\">";
        echo "<img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>";
        echo "<br></center></body></html>";
        exit();
    }
    print("<table border=\"0\" cellspacing=\"1\" width=\"50%\" style=\"border-collapse: collapse\">
             <tr><td width=\"46%\"><font face=\"����_GB2312\">Ӧ�÷�������</font></td>
                 <td width=\"54%\" valign=\"top\">");

        //----------------20051216;by yy;��ȡ/usr/SSLMPS/config/app_proxy.conf�е�Ӧ�÷����б�
        $apps=GetAppSvrNameList(2);
        //$rcc=count($apps);
        $nj=$RadioGroupID-1;

        $pmirules=GetPMIRules();
        //print_r($pmirules);
        $name=$pmirules[$nj][1];
        $asname=$pmirules[$nj][3];
        $pmiorg=$pmirules[$nj][2];
        $onoff=$pmirules[$nj][4];
        //echo "$name,$asname,$pmiorg,$onoff";
        echo "<input type=\"hidden\" name=\"RuleID\" value=$RadioGroupID>";
        echo "<select name=\"appselect\" style=\"position: relative; width: 152; height: 20\">";
        foreach($apps as $apname)
        {
            if (strcmp($name,$apname)==0)
            {
                echo "<option value=\"$apname\" selected>$apname</option>";
            } else
            {
                echo "<option value=\"$apname\">$apname</option>";
            }
        }
        //GetPMI($pmiaddr,$pmiport,$pmiorg);
        //----------------20051216;by yy;

    print("               </select></td></tr>
             <tr><td><font face=\"����_GB2312\">��֯����</font></td>
                 <td><input type=\"TEXT\" name=\"orgname\" size=%20 maxlength=20 value=\"$pmiorg\" readonly=\"true\" style=\"background-color: #c0c0c0\"></td></tr>
             <tr><td><font face=\"����_GB2312\">ϵͳ����</font></td>
	             <td width=\"54%\" valign=\"top\"><input type=\"TEXT\" name=\"sysname\" size=%20 value=\"$asname\" maxlength=255></td></tr>
             <tr><td><font face=\"����_GB2312\">����</font></td>
                 <td>
            	   <select name=\"swselect\" style=\"position: relative; width: 152; height: 20\">");
        if ($onoff=="on")
        {
            echo "<option value=\"on\" selected>��</option>";
            echo "<option value=\"off\">��</option>";
        } else
        {
            echo "<option value=\"on\">��</option>";
            echo "<option value=\"off\" selected>��</option>";
        }
    print("        </select></td></tr>
             <tr><td colspan=\"2\" align=\"center\"><br>
                   <input type=\"submit\" value=\"�޸Ĺ���\" name=\"ModiRule\">
                 </td></tr>
           </table>");
    echo "<input type=\"hidden\" name=\"numb\" value=\"$numb\">";
    echo "<p></b></font><br></center></form></body></html>";
?>