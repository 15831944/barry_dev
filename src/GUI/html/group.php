<?php
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
<!--
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
-->
<title>�½���ҳ 2</title>
</head>

<body background="image/pmiback.gif">
<form name="group" METHOD="post">
 <table border="0" cellspacing="0" width="100%" id="AutoNumber2" height="44" bgcolor="#eef4f4">
  <tr>
  <td width="20%"></td>
<td width ="80%">
��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <fieldset style="width: 160px; height: 175px; border-style: groove; border-width: 1px; padding: 0; background-color: #eef4f4">
<legend><font face="��������" size="4">���</font></legend>
<p align="center">
<input type="radio" value="V1" checked name="R1"  onclick="checkitem()"><font face="���Ŀ���" size="4"> ����1</font><p align="center">
<input type="radio" value="V2" name="R1"  onclick="checkitem()"><font size="4" face="���Ŀ���"> ����2</font></p>
<p align="center"><input type="radio" value="V3" name="R1"  onclick="checkitem()"><font face="���Ŀ���" size="4"> ����3</font></p>
</fieldset><p><font face="���Ŀ���" size="4">&nbsp;&nbsp;&nbsp; ѡ��������1���飺</font><select size="1" name="D1" disabled="true">
</select></p>
<p><font face="���Ŀ���" size="4">&nbsp;&nbsp;&nbsp; ѡ��������2���飺</font><select size="1" name="D2" disabled="true">
</select></p>
<p>&nbsp;&nbsp; <font face="���Ŀ���" size="4">������</font><input type="text" name="T1" size="20"></p>
<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<input type="button" value="ע ��" name="B1"></p>
</td></tr></table>
<script language="javascript">
function checkitem(){
	if(document.group.R1[0].checked==true)
	{
		document.group.D1.disabled=true;
		document.group.D2.disabled=true;
	}
	if(document.group.R1[1].checked==true)
	{
		document.group.D1.disabled=false;
		document.group.D2.disabled=true;
	}
	if(document.group.R1[2].checked==true)
	{
		document.group.D1.disabled=false;
		document.group.D2.disabled=false;
	}
}</script>
</form>
</body>
</html>