<?php
include ("pmi_db.php");
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
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>��ɫ����ҳ��</title>
</head>

<body background="image/pmiback.gif">

<FORM name="role" METHOD="POST">

<table border="0" cellspacing="1" width="100%" id="AutoNumber2" height="400">
  <tr>
  <td>
 <p>
<img border="0" src="image/rolereg.gif" width="283" height="57"></p>
 
  </td>
	</tr>		<tr>
			<td colspan="2" height="41">

			<p align="center"><b><font face="����_GB2312">��ɫ����<input type="text" name="rolename" size="20"></font></b></td>
		</tr>
		<tr>
			<td width="32%">
			</td>
			<td width="67%">
			<br><b><font face="����_GB2312" size="4" color="#0033CC">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
			��ɫƥ����Ϣ��</font></b>
			<table border="2" cellspacing="1" style="border-collapse: collapse" width="297" bordercolorlight="#008080" bordercolor="#008080" id="table2">
				<tr>
					<td bgcolor="#0066CC" width="28">��</td>
					<td bgcolor="#0066CC" width="101">
					<p align="center"><b><font color="#FFFF00" face="����_GB2312">
					֤����</font></b></td>
					<td bgcolor="#0066CC" align="center">
					<p align="center"><b><font color="#FFFF00" face="����_GB2312">
					ƥ��ֵ</font></b></td>
				</tr>
				<tr>
					<td width="28" style="border: 0.5px inset #C0C0C0">
					<p align="center">
					<input type="checkbox" name="C1" value="ON" onclick="checkitem1()"></td>
					<td width="101" style="border: 0.5px inset #C0C0C0">
					<p align="center"><b><font face="����_GB2312">֤�����к�</font></b></td>
					<td style="border: 0.5px inset #C0C0C0" align="center">
					<input type="text" name="certnum" size="20" disabled="true"></td>
				</tr>
				<tr>
					<td width="28" style="border: 0.5px inset #C0C0C0">
					<p align="center">
					<input type="checkbox" name="C2" value="ON" onclick="checkitem2()"></td>
					<td width="101" style="border: 0.5px inset #C0C0C0">
					<p align="center"><font face="����_GB2312"><b>�û���</b></font></td>
					<td style="border: 0.5px inset #C0C0C0" align="center">
					<input type="text" name="username" size="20" disabled="true"></td>
				</tr>
				<tr>
					<td width="28" style="border: 0.5px inset #C0C0C0">
					<p align="center">
					<input type="checkbox" name="C3" value="ON" onclick="checkitem3()"></td>
					<td width="101" style="border: 0.5px inset #C0C0C0">
					<p align="center"><b><font face="����_GB2312">����֤��</font></b></td>
					<td style="border: 0.5px inset #C0C0C0" align="center">
					<input type="text" name="plicenum" size="20" disabled="true"></td>
				</tr>
				<tr>
					<td width="28" style="border: 0.5px inset #C0C0C0">
					<p align="center">
					<input type="checkbox" name="C4" value="ON" onclick="checkitem4()"></td>
					<td width="101" style="border: 0.5px inset #C0C0C0">
					<p align="center"><b><font face="����_GB2312">�û���1</font></b></td>
					<td style="border: 0.5px inset #C0C0C0" align="center">
					<input type="text" name="group1" size="20" disabled="true"></td>
				</tr>
				<tr>
					<td width="28" style="border: 0.5px inset #C0C0C0">
					<p align="center">
					<input type="checkbox" name="C5" value="ON" onclick="checkitem5()"></td>
					<td width="101" style="border: 0.5px inset #C0C0C0">
					<p align="center"><font face="����_GB2312"><b>�û���2</b></font></td>
					<td style="border: 0.5px inset #C0C0C0" align="center">
					<input type="text" name="group2" size="20" disabled="true"></td>
				</tr>
				<tr>
					<td width="28" style="border: 0.5px inset #C0C0C0">
					<p align="center">
					<input type="checkbox" name="C6" value="ON" onclick="checkitem6()"></td>
					<td width="101" style="border: 0.5px inset #C0C0C0">
					<p align="center"><b><font face="����_GB2312">�û���3</font></b></td>
					<td style="border: 0.5px inset #C0C0C0" align="center">
					<input type="text" name="group3" size="20" disabled="true"></td>
				</tr>
				<tr>
					<td width="28" style="border: 0.5px inset #C0C0C0">
					<p align="center">
					<input type="checkbox" name="C7" value="ON" onclick="checkitem7()"></td>
					<td width="101" style="border: 0.5px inset #C0C0C0">
					<p align="center"><b><font face="����_GB2312">��֯</font></b></td>
					<td style="border: 0.5px inset #C0C0C0" align="center">
					<input type="text" name="organise" size="20" disabled="true"></td>
				</tr>
				<tr>
					<td width="28" style="border: 0.5px inset #C0C0C0">
					<p align="center">
					<input type="checkbox" name="C8" value="ON" onclick="checkitem8()"></td>
					<td width="101" style="border: 0.5px inset #C0C0C0">
					<p align="center"><font face="����_GB2312"><b>����</b></font></td>
					<td style="border: 0.5px inset #C0C0C0" align="center">
					<input type="text" name="depart" size="20" disabled="true"></td>
				</tr>
				<tr>
					<td width="28" style="border: 0.5px inset #C0C0C0">
					<p align="center">
					<input type="checkbox" name="C9" value="ON" onclick="checkitem9()"></td>
					<td width="101" style="border: 0.5px inset #C0C0C0">
					<p align="center"><b><font face="����_GB2312">ְ��</font></b></td>
					<td style="border: 0.5px inset #C0C0C0" align="center">
					<input type="text" name="dute" size="20" disabled="true"></td>
				</tr>
				<tr>
					<td width="28" style="border: 0.5px inset #C0C0C0">
					<p align="center">
					<input type="checkbox" name="C10" value="ON" onclick="checkitem10()"></p></td>
					<td width="101" style="border: 0.5px inset #C0C0C0">
					<p align="center"><b><font face="����_GB2312">Ȩ��</font></b></td>
					<td style="border: 0.5px inset #C0C0C0" align="center">
					<input type="text" name="priv" size="20" disabled="true"></td>
				</tr>
			</table>
			</td>
		</tr>
		<tr>
			<td width="32%">
			<p align="center"><b><font face="����ϸ��" size="4" color="#0033CC">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			</font></b></p>
			</td>
			<td width="67%">
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			<input type="button" value="��ӽ�ɫ" name="B2" onclick="check()">
			<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
			<a href="role.php?numb=1"><img border="0" src="image/goback.gif" width="40" height="40"></a></p></td>
		</tr>     
    </table>

</td>
  </tr>
</table>
</form>
</body>
<script language="javaScript">

function checkitem1(){
	if(document.role.C1.checked==true)
	{
		document.role.certnum.disabled=false;
	}else{
		document.role.certnum.disabled=true;
	}
}
function checkitem2(){
	if(document.role.C2.checked==true)
	{
		document.role.username.disabled=false;
	}else{
		document.role.username.disabled=true;
	}
}
function checkitem3(){
	if(document.role.C3.checked==true)
	{
		document.role.plicenum.disabled=false;
	}else{
		document.role.plicenum.disabled=true;
	}
}
function checkitem4(){
	if(document.role.C4.checked==true)
	{
		document.role.group1.disabled=false;
	}else{
		document.role.group1.disabled=true;
	}
}
function checkitem5(){
	if(document.role.C5.checked==true)
	{
		document.role.group2.disabled=false;
	}else{
		document.role.group2.disabled=true;
	}
}
function checkitem6(){
	if(document.role.C6.checked==true)
	{
		document.role.group3.disabled=false;
	}else{
		document.role.group3.disabled=true;
	}
}
function checkitem7(){
	if(document.role.C7.checked==true)
	{
		document.role.organise.disabled=false;
	}else{
		document.role.organise.disabled=true;
	}
}
function checkitem8(){
	if(document.role.C8.checked==true)
	{
		document.role.depart.disabled=false;
	}else{
		document.role.depart.disabled=true;
	}
}
function checkitem9(){
	if(document.role.C9.checked==true)
	{
		document.role.dute.disabled=false;
	}else{
		document.role.dute.disabled=true;
	}
}
function checkitem10(){
	if(document.role.C10.checked==true)
	{
		document.role.priv.disabled=false;
	}else{
		document.role.priv.disabled=true;
	}
}
function check(){
	var certnumtmp=document.role.certnum.value;
	var usernametmp=document.role.username.value;
	var plicenumtmp=document.role.plicenum.value;
	var group1tmp=document.role.group1.value;
	var group2tmp=document.role.group2.value;
	var group3tmp=document.role.group3.value;
	var organisetmp=document.role.organise.value;
	var departtmp=document.role.depart.value;
	var dutetmp=document.role.dute.value;
	var privtmp=document.role.priv.value;
	
	if(document.role.C1.checked==true && certnumtmp.length>20)
		alert("֤�����кŹ�����");
	else if(document.role.C2.checked==true && usernametmp.length>20)
		alert("�û���������");
	else if(document.role.C3.checked==true && plicenumtmp.length>18)
		alert("����֤���������");
	else if(document.role.C4.checked==true && group1tmp.length>50)
		alert("�û���1��Ϣ������");
	else if(document.role.C5.checked==true && group2tmp.length>50)
		alert("�û���2��Ϣ������");
	else if(document.role.C6.checked==true && group3tmp.length>50)
		alert("�û���3��Ϣ������");
	else if(document.role.C7.checked==true && organisetmp.length>50)
		alert("��֯��Ϣ������");
	else if(document.role.C8.checked==true && departtmp.length>50)
		alert("������Ϣ������");
	else if(document.role.C9.checked==true && dutetmp.length>50)
		alert("ְ����Ϣ������");
	else if(document.role.C10.checked==true && privtmp.length>50)
		alert("Ȩ����Ϣ������");
	else if(document.role.C1.checked==false &&document.role.C2.checked==false &&document.role.C3.checked==false &&document.role.C4.checked==false &&document.role.C5.checked==false &&document.role.C6.checked==false &&document.role.C7.checked==false &&document.role.C8.checked==false &&document.role.C9.checked==false &&document.role.C10.checked==false)
		alert("��ɫ����Ӧ��һ���ɫ��Ϣ");
	else{
		if(document.role.C3.checked==true)
		{
			var i=18-plicenumtmp.length;
			var j;
			var temp="0";
			for(j=0;j<i;j++)
			{
				document.role.plicenum.value=temp.concat(document.role.plicenum.value);
			}

		}
		document.role.action="addrole.php";
		document.role.submit();	
	}
}

</script>

</html>
