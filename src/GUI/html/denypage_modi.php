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
	echo '<html><head><title>Denypage�����޸�</title></head>';
    echo '<body background="image/pmiback.gif"><form name="Denypagemodi" METHOD="POST" ACTION="denypage_modiok.php?opcode=2" enctype="multipart/form-data">';
    echo '<center><font face="����_GB2312"><b>';
    if ($RadioGroupID<1)
    {
        echo "��ѡ��һ��Denypage�����޸ģ�"."<br>";
        echo "<p></b>";
        echo "</font><a href=\"denypage.php?numb=$numb\">";
        echo "<img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>";
        echo "<br></center></body></html>";
        exit();
    }
    //----------------20051218;by cw;��ȡ/usr/SSLMPS/config/app_proxy.conf�е�Ӧ�÷����б�
        $denyps=GetDenypagesList();
        //$rcc=count($apps);
        $nj=$RadioGroupID-1;

        $dpname=$denyps[$nj][1];
        $dppath=$denyps[$nj][2];
    //----------------20051218;by cw;��ȡ/usr/SSLMPS/config/denypages.conf�е�Denypage�б�
    print("<table border=\"0\" cellspacing=\"1\" width=\"50%\" style=\"border-collapse: collapse\">
             <tr><td width=\"35%\"><font face=\"����_GB2312\">Denypage����</font></td>
                 <td width=\"65%\" valign=\"top\">
                   <input type=\"TEXT\" name=\"denypname\" size=%30 maxlength=15 value=\"$dpname\" readonly=\"true\" style=\"background-color: #c0c0c0\">
                 </td></tr>
             <tr><td><font face=\"����_GB2312\">Denypage�ļ���</font></td>
	             <td width=\"54%\" valign=\"top\">
                   <input type=\"TEXT\" name=\"denyppath\" size=%30 maxlength=200 value=\"$dppath\" readonly=\"true\">
                   </td></tr>
             <tr><td><font face=\"����_GB2312\">DenypageԴ�ļ�</font></td>
                 <td><input name=\"denypfile\" type=\"file\" size=%32 maxlength=250></td></tr>
             <tr><td colspan=\"2\" align=\"center\"><br>
                   <input type=\"button\" value=\"�޸�Denypage\" name=\"Modidenypage\" onClick=\"modidp()\">
                 </td></tr>
           </table>");
    //----------------20051218;by cw;��ȡ/usr/SSLMPS/config/denypages.conf�е�Denypage�б�
    echo "<input type=\"hidden\" name=\"numb\" value=\"$numb\">";
	echo "<p></b></font><br></center></form></body>";

?>

<script language="javaScript">
function modidp()
{
    var filelen=document.Denypagemodi.denypfile.value;

    if (filelen=="")
		alert("DenypageԴ�ļ�����Ϊ�գ�");
    else if(filelen.length>250)
		alert("DenypageԴ�ļ���������");
    else
    {
        document.Denypagemodi.action="denypage_modiok.php?opcode=2";
        document.Denypagemodi.submit();
    }
}
</script>
</html>
