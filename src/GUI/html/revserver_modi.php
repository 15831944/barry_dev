<!--
**************************************************************************
                  �� PLW517���������������ϵͳWebվ�㡷
                        ��Ȩ���� (C) 2005,2006
**************************************************************************
******************************************************
��Ŀ:�� PLW517���������������ϵͳWebվ�㡷
ģ��:AppProxy��������޸�ҳ��
����:
�汾:1.0.1.0
����:2006-1-9
����:Stephen
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
	echo '<html><head><title>���������������޸�</title></head>';
  	echo '<body background="image/pmiback.gif"><form name="servermodi" METHOD="POST" ACTION="server_modiok.php?opcode=2">';
	echo '<center><font face="����_GB2312"><b>';
	if ($RadioGroupID<1)
	{
	    echo "��ѡ��һ����������������޸ģ�"."<br>";
	    echo "<p></b>";
	    echo "</font><a href=\"revserver.php?numb=$numb&apptype=$apptype\">";
	    echo "<img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a>";
	    echo "<br></center></body></html>";
	    exit();
	}
	$apptype = "backward";
	$aaa=$RadioGroupID;
	$proxyservs=GetAppSvrList($apptype);
	
	$rid=$proxyservs[$aaa-1][0];
	$modienable=$proxyservs[$aaa-1][1];
	$prname=$proxyservs[$aaa-1][2];
	$prtype=$proxyservs[$aaa-1][3];
	$svrtype=$proxyservs[$aaa-1][4];
	$svrport=$proxyservs[$aaa-1][5];
	$secutag=$proxyservs[$aaa-1][6];
	$seraddr=$proxyservs[$aaa-1][7];
	$serport=$proxyservs[$aaa-1][8];
	$opensw=$proxyservs[$aaa-1][9];
	$addtime=$proxyservs[$aaa-1][10];
	$denypage=$proxyservs[$aaa-1][11];

	echo "<input type=\"hidden\" name=\"RuleID\" value=$RadioGroupID>";
	
	print("<table border=\"0\" cellspacing=\"1\" width=\"50%\" style=\"border-collapse: collapse\">
	     	<tr><td><font face=\"����_GB2312\">��������������</font></td>
	            <td width=\"54%\" valign=\"top\">
	          	<input type=\"TEXT\" name=\"proxyname\" size=%20 maxlength=32 value=\"$prname\" readonly=\"true\" style=\"background-color: #c0c0c0\">
	      			<input type=\"hidden\" name=\"proxytype\" value=\"$prtype\">
	      		</td>
	      </tr>");
	
	print(" <tr id=\"SvrTxtSel\" style=\"DISPLAY:\">");
	print("     <td><font face=\"����_GB2312\">Э������</font></td>
              <td>
            	   <select name=\"svrstypef\" style=\"position: relative; width: 152; height: 20\" onchange=\"changesvrstype()\" onclick=\"changesvrstype()\">");
	if (($svrtype=="HTTP") or ($svrtype=="http")) {
	   echo "<option value=\"http\" selected>http</option>";
	} else {
	   echo "<option value=\"http\">http</option>";
	}
	if (($svrtype=="FTP") or ($svrtype=="ftp")) {
	   echo "<option value=\"ftp\" selected>ftp</option>";
	} else {
	   echo "<option value=\"ftp\">ftp</option>";
	}
	if (($svrtype=="SMTP") or ($svrtype=="smtp")) {
	   echo "<option value=\"smtp\" selected>smtp</option>";
	} else {
	   echo "<option value=\"smtp\">smtp</option>";
	}
	if (($svrtype=="POP3") or ($svrtype=="pop3")) {
	   echo "<option value=\"pop3\" selected>pop3</option>";
	} else {
	   echo "<option value=\"pop3\">pop3</option>";
	}
	if (($svrtype=="YZW") or ($svrtype=="yzw")) {
	   echo "<option value=\"yzw\" selected>yzw</option>";
	} else {
	   echo "<option value=\"yzw\">yzw</option>";
	}
	if (($svrtype=="DHTTP") or ($svrtype=="dhttp")) {
	   echo "<option value=\"dhttp\" selected>dhttp</option>";
	} else {
	   echo "<option value=\"dhttp\">dhttp</option>";
	}
	
	if (($svrtype=="TCP") or ($svrtype=="tcp")) {
	   echo "<option value=\"tcp\" selected>����</option>";
	} else {
	   echo "<option value=\"tcp\">����</option>";
	}
	print("       </select></td></tr>");
	
	print(" <tr><td><font face=\"����_GB2312\">����˿�</font></td>
	           <td><input type=\"TEXT\" name=\"svrsport\" size=%20 maxlength=5 value=\"$svrport\">
	           		 <input type=\"hidden\" name=\"secstag\" value=\" \"></td></tr>");
	             
	if ($seraddr=="-") $seraddr="";
	if ($serport=="-") $serport="";
	print(" <tr><td><font face=\"����_GB2312\">�Է�PWL517���IP</font></td>
	             <td><input type=\"TEXT\" name=\"asaddr\" size=%20 maxlength=20 value=\"$seraddr\"></td></tr>
	         <tr><td><font face=\"����_GB2312\">��̨����˿ں�</font></td>
	             <td><input type=\"TEXT\" name=\"asport\" size=%20 maxlength=5 value=\"$serport\"></td></tr>
	         <tr><td><font face=\"����_GB2312\">����״̬</font></td>
	             <td>
	        	   <select name=\"openstat\"  style=\"position: relative; width: 152; height: 20\">");
	         if (($opensw=="on") or ($opensw=="ON"))
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
	               <input type=\"button\" value=\"�޸ķ���\" name=\"modiSvrs\" onClick=\"modiserv()\">
	             </td></tr>
	       </table>");
	echo "<input type=\"hidden\" name=\"numb\" value=\"$numb\">";
	echo "<input type=\"hidden\" name=\"adtime\" value=\"$addtime\">";
	
	echo "<input type=\"hidden\" name=\"svrstype\" value=\"$svrtype\">";
	echo "<p></b></font><br></center></form></body>";

?>

<script language="javaScript">
function modiserv(){
    var appnamelen=document.servermodi.proxyname.value;
    if(appnamelen.length>32)
		alert("�������ƹ�����");
	else if(appnamelen=="")
		alert("�������Ʋ���Ϊ�գ�");
    else if(document.servermodi.svrsport.value>65535)
		alert("����˿ڹ���");
	else if(document.servermodi.svrsport.value==0)
		alert("����˿ڲ���Ϊ��");
	else if(document.servermodi.asport.value>65535)
		alert("ʵ�ʷ���˿ںŹ���");
	else if((document.servermodi.asport.value<=0) && (document.servermodi.svrstype.value!="dhttp") && (document.servermodi.svrstype.value!="yzw"))
		alert("ʵ�ʷ���˿ںŲ���Ϊ�գ�");
	else if((document.servermodi.asaddr.value=="") && (document.servermodi.svrstype.value!="dhttp") && (document.servermodi.svrstype.value!="yzw"))
		alert("ʵ�ʷ�����IP��ַ����Ϊ�գ�");
	else{
		/*
		if ((document.servermodi.svrstype.value=="dhttp") || (document.servermodi.svrstype.value=="yzw"))
		{
		    document.servermodi.asaddr.value="";
		    document.servermodi.asport.value="";
		} 
		*/  
		document.servermodi.action="server_modiok.php?opcode=2";
		document.servermodi.submit();
	}
}

function changesvrstype() 
{
	document.servermodi.svrstype.value=document.servermodi.svrstypef.value;
}
</script>
</html>