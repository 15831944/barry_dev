<?php
include "constant.php";
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
<meta http-equiv="Content-Language" content="zh-cn">
<meta name="GENERATOR" content="Microsoft FrontPage 5.0">
<meta name="ProgId" content="FrontPage.Editor.Document">
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�½���ҳ 1</title>
</head>

<body  background="image/pmiback.gif">

<form name="license" method="POST" action=verifylicense.php>
<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" width="811" id="AutoNumber1" height="250">
  <tr>
    <td width="50%" height="37">
    <p align="center">
<img border="0" src="image/snrequest.gif" width="283" height="57">
<p align="center"><br>

  <p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  <input type="button" value="���������ִ�" name="B1" onclick=gen()>
  <br>
   </td>  
 
  <td width="50%" height="37">
  
 <p align="left">
 <img border="0" src="image/snregister.gif" width="283" height="57"> 
    <p align="left">
	<br><font face=\"����_GB2312\">����ע���ִ���</font>
	<input name=verifystring type=text size=48 maxlength=48>
	<br>
	<p align="center">
	<input type=submit name=verifylicense value=ע��>
	<br>  
   </td>
   
  </tr>  
</table>
</form>

</body>

<script language="javaScript">

function gen(){
	document.license.action="generatelicensereq.php";
	document.license.submit();	
}
</script>
</html>
