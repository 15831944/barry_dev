<!--
**************************************************************************
                  �� PLW517���������������ϵͳWebվ�㡷
                        ��Ȩ���� (C) 2005,2006
**************************************************************************
******************************************************
��Ŀ:�� PLW517���������������ϵͳWebվ�㡷
ģ��:AppProxy�����������б����
����:
�汾:1.0.1.0
����:2006-01-08
����:Stephen
TODO:
*******************************************************
-->
<?php
	include("constant.php");
	@session_start();
	if($manager_ID==NULL)
	{
	  	echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '<p><br><br><center><font face="����_GB2312"><b>���ȵ�½��</font></b><p>';
	    echo '<a href="login.html"><img border="0" src="image/goback.gif" width="40" height="40"></a>';
	    echo '</center></body></html>';
	    exit();
	}
?>
<html>

<head>
<meta name="GENERATOR" content="Microsoft FrontPage 5.0">
<meta name="ProgId" content="FrontPage.Editor.Document">
<!--
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
-->
<title>��������������</title>
</head>

<body bgcolor="#eef4f4">
<form name="server" method="post">
<table border="0" cellspacing="1" width="100%" id="AutoNumber2" height="400">
  <tr>

    <td width="100%" height="400">
    <img border="0" src="image/revser.gif" width="283" height="57">
    <b><font face="����_GB2312"  color="#006699">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ҳ��:
<?php
	$apptype = "backward";
 	$proxyservs=GetAppSvrList($apptype);
	$nr=count($proxyservs);
	if($nr%10==0)
		$tmp=floor($nr/10);
	else
		$tmp=floor($nr/10)+1;
  	if ($numb<=0)
    	$numb=1;
 	print("$numb/$tmp&nbsp;&nbsp;&nbsp;ÿҳ�����ʾ10��&nbsp;&nbsp;&nbsp;��¼��:$nr</font></b>");
	print("<table border=\"2\" cellspacing=\"1\" bordercolor=\"#55847e\" width=\"100%\" style=\"border-collapse: collapse\">".
			"<tr bgcolor=\"#95bdbf\">\n".
			"<th width=\"2%\"></th>\n".
			"<th width=\"28%\"><center>�������<br>��������</center></th>\n".
  			"<th width=\"6%\"><center>Э��<br>����</center></th>\n".
  			"<th width=\"7%\"><center>����<br>�˿�</center></th>\n".
   			"<th width=\"17%\"><center>�Է�PWL517<br>���IP</center></th>\n".
  			"<th width=\"9%\"><center>��̨����<br>�˿ں�</center></th>\n".
      		"<th width=\"6%\"><center>����<br>״̬</center></th>\n".
  			"<th width=\"24%\"><center>����ʱ��</center></th>\n".
			"</tr>\n<font size=\"1\">");

  	$aaa=($numb-1)*10+1;             //��ҳ�ĵ�һ����¼��rid
  	if (($numb*10)<=$nr)
    	$bbb=$numb*10;                   //��ҳ�����һ����¼��rid
  	else
  		$bbb=$nr;
  	$rs=$bbb-$aaa;                       //��ҳ��ʾ�ļ�¼��-1��
  	$ri=0;

	if ($nr != 0)
	{
		while ($ri<=$rs)
		{
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
	 
	        if($prtype != $apptype)	continue;
	 
	        if ($modienable==1)
	          echo "<tr><th><input type=\"radio\" name=\"RadioGroupID\" value=$rid></th>\n";
	        else
	         	echo "<tr><th> </th>\n";
	        echo "<th>$prname</th>";
              
	        if (($svrtype=="tcp") or ($svrtype=="TCP"))
	          echo "<th>����</th><th>$svrport</th>\n";
	        else
	          echo "<th>$svrtype</th><th>$svrport</th>\n";
	      
	       	if ($seraddr=="-")
	          echo "<th></th>";
	        else
	          echo "<th>$seraddr</th>";
 
	        if ($serport=="-")
	          echo "<th></th>";
					else
	          echo "<th>$serport</th>\n";
	 
	        if (($opensw=="on") or ($opensw=="ON"))
	          echo "<th>��</th>";
	        else
	          echo "<th>��</th>";
	        echo "<th>$addtime</th>";
	       	echo "\n</tr>";             
	        $aaa=$aaa+1;
			  $ri+=1;
		}
	}
    $temp=$numb;

	print("</font></table><br>");
	echo "<input type=\"hidden\" name=\"numb\" value=\"$numb\">";
 	print("<input type=\"button\" value=\"ɾ������\" name=\"del\" onclick=\"set()\">");        
 	print("&nbsp;&nbsp;&nbsp;");
	print("<input type=\"submit\" value=\"�޸ķ���\" name=\"edit\" onclick=\"modi()\">");
	print("&nbsp;&nbsp;&nbsp;");
	print("<input type=\"button\" value=\"ȫ��ɾ��\" name=\"deleall\" onclick=\"delall()\">");

	print("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
	print("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
	print("<font face=\"����_GB2312\" color=\"#C0C0C0\"><b>");
 	
 	if($numb>1)
 	{
 		$temp=$numb-1;
	 	echo "<a href=\"revserver.php?numb=$temp&apptype=$apptype\">��һҳ</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
	}
	else
	{
		echo "��һҳ&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
	}
	
	if($nr>$numb*10)
	{
  		$temp=$numb+1;
	 	echo "<a href=\"revserver.php?numb=$temp&apptype=$apptype\">��һҳ</a>";
	}
	else
	{
		echo "��һҳ";
	}

	print("</font><br><br><center>");
  	print("<table border=\"0\" cellspacing=\"1\" width=\"50%\" style=\"border-collapse: collapse\">
        	<tr><td><font face=\"����_GB2312\">��������������</font></td>
	      		<td width=\"54%\" valign=\"top\">
        			<input type=\"TEXT\" name=\"proxyname\" size=%20 maxlength=32>
  						<input name=\"proxytype\" style=\"Display:none\" value = $apptype>
  				</td>
  			</tr>");

	print("  <tr id=\"SvrTxtSel\" style=\"DISPLAY:\"><td><font face=\"����_GB2312\">Э������</font></td>
             <td>
        	   	<select name=\"svrstypef\" style=\"position: relative; width: 152; height: 20\" onchange=\"changedenyp()\" onclick=\"changedenyp()\">
                 <option value=\"http\" selected>http</option>
                 <option value=\"ftp\">ftp</option>
                 <option value=\"smtp\">smtp</option>
                 <option value=\"pop3\">pop3</option>
                 <option value=\"yzw\">yzw</option>
                 <option value=\"dhttp\">dhttp</option>
                 <option value=\"tcp\">����</option>
              </select>
             </td>
            </tr>");
    
    print("  <tr><td><font face=\"����_GB2312\">����˿�</font></td>
                 <td><input type=\"TEXT\" name=\"svrsport\" size=%20 maxlength=5>
                 			<input type=\"hidden\" name=\"secstag\" value=\" \">
                 </td>
             </tr>");
         
    print("<tr><td><font face=\"����_GB2312\">�Է�PWL517���IP</font></td>
               <td><input type=\"TEXT\" name=\"asaddr\" size=%20 maxlength=20></td></tr>
           <tr><td><font face=\"����_GB2312\">��̨����˿ں�</font></td>
               <td><input type=\"TEXT\" name=\"asport\" size=%20 maxlength=5></td></tr>
           <tr><td><font face=\"����_GB2312\">����״̬</font></td>
               <td>
          	   <select name=\"openstat\"  style=\"position: relative; width: 152; height: 20\">
                   <option value=\"on\">��</option>
                   <option value=\"off\">��</option>
                 </select></td></tr>");
    
    print("<tr><td colspan=\"2\" align=\"center\"><br>
           			<input type=\"button\" value=\"��ӷ���\" name=\"addSvrs\" onClick=\"check()\">
               </td>
           </tr>
          </table>");
    echo "<input type=\"hidden\" name=\"svrstype\" value=\"http\">";
?>
</td>
  </tr>
</table>
</form>
</body>
<script language="javaScript">
function set()
{
	if(window.confirm("��ȷ��ɾ���˷���Ӧ�÷�����"))
	{
		document.server.action="revserver_del.php?delall=0";
		document.server.submit();
	}
}

function delall()
{
	if(window.confirm("��ȷ��ɾ��ȫ������Ӧ�÷�����"))
	{
		document.server.action="revserver_del.php?delall=1";
		document.server.submit();
	}
}

function modi()
{
	document.server.action="revserver_modi.php?";
	document.server.submit();
}

function check()
{
	var appnamelen=document.server.proxyname.value;
	if(appnamelen.length>32)
		alert("�������ƹ�����");
	else if(appnamelen=="")
		alert("�������Ʋ���Ϊ�գ�");
  /*
    else if(pronamelen.length>20)
		alert("����Э�����ƹ�����");
		else if(pronamelen=="")
		alert("����Э�����Ʋ���Ϊ�գ�");
  */
  else if(document.server.svrsport.value>65535)
		alert("����˿ڹ���");
	else if(document.server.svrsport.value==0)
		alert("����˿ڲ���Ϊ����");
	else if(document.server.asport.value>65535)
		alert("ʵ�ʷ���˿ںŹ���");
	else if((document.server.asport.value<=0) && (document.server.svrstype.value!="dhttp") && (document.server.svrstype.value!="yzw"))
		alert("ʵ�ʷ���˿ںŲ���Ϊ���գ�");
	else if((document.server.asaddr.value=="") && (document.server.svrstype.value!="dhttp") && (document.server.svrstype.value!="yzw"))
		alert("ʵ�ʷ�����IP��ַ����Ϊ�գ�");
	else{
		document.server.action="server_modiok.php?opcode=1";
		document.server.submit();
	}
}

function changedenyp() 
{
	document.server.svrstype.value=document.server.svrstypef.value;
}

</script>
</html>