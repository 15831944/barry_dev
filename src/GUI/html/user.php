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
<title>�û�����ҳ��</title>
</head>

<body background="image/pmiback.gif">

<FORM name="usermanage" METHOD="POST" ACTION="user.php">

<table border="0" cellspacing="1" width="100%" id="AutoNumber2" height="400">
  <tr>
  <td>
 <p>
<img border="0" src="image/usereg.gif" width="283" height="57"></p>
 
  </td>
	</tr><tr>
    <td width="100%" height="300">��
    
     <table border="0" cellspacing="0" width="85%" id="AutoNumber4" height="14" style="border-collapse: collapse" bordercolor="#111111" cellpadding="0">
      <tr>
        <td width="50%" height="39">
        <p align="right"><b><font face="����_GB2312">�û�����</font></td>
        <td width="50%" height="39"><input type="text" name="usernameu" size="20"></td>
      </tr>
      <tr>
        <td width="50%" height="38">
        <p align="right"><font face="����_GB2312"><b>��&nbsp;&nbsp;&nbsp;�ţ�</b></font>
        </td>
        <td width="50%" height="38"><input type="text" name="departmentu" size="20"></td>
      </tr>
      <tr>
        <td width="50%" height="35">
        <p align="right"><font face="����_GB2312"><b>����֤�ţ�</b></font></td>
        <td width="50%" height="35"><input type="text" name="numberu" size="20"></td>
      </tr>
      <tr>
        <td width="50%" height="35">
        <p align="right"></td>
        <td width="50%" height="35"><input type="button" value="ע ��" name="B1"  onclick="Check_input()" >
        <p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="usermess.php?numb=1"><img border="0" src="image/goback.gif" width="40" height="40"></a></p>
</td>
      </tr>
      
    </table>

</td>
  </tr>
</table>
</form>
</body>
<script language="javaScript">

function Check_input(){
	var num = document.usermanage.numberu.value;
	var tlen=document.usermanage.usernameu.value;
	var plen=document.usermanage.departmentu.value;
	if(tlen.length>10)
		alert("�û���������");
	else if(plen.length>20)
		alert("������������");
	else if(document.usermanage.usernameu.value==""){
		alert("�û�������Ϊ�գ�����������!");
		return(0);
	}
	else if(document.usermanage.numberu.value==""){
		alert("����֤�Ų���Ϊ�գ�����������!");
		return(0);
	}else if(num.length>18){
		alert("����֤�������������������!");
		return(0);
	}else{
		var i=18-num.length;
		var j;
		var temp="0";
		for(j=0;j<i;j++)
		{
			document.usermanage.numberu.value=temp.concat(document.usermanage.numberu.value);
		}
		document.usermanage.action="usermess.php?numb=1";
		document.usermanage.submit();
		return (1);
	}
}

</script>

</html>
