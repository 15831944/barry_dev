<?php
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/pmiback.gif"><b>' ;
	    echo '<p><br><br><center><font face="����_GB2312"><b>���ȵ�½��</font></b><p>';
	    echo '<a href="login.html"><img border="0" src="image/goback.gif" width="40" height="40"></a>';
            echo '</center></body></html>';
            exit();			
	} ?>
 <html>

<head>
<meta http-equiv="Content-Language" content="zh-cn">
<meta name="GENERATOR" content="Microsoft FrontPage 5.0">
<meta name="ProgId" content="FrontPage.Editor.Document">
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>�½���ҳ 1</title>
</head>

<body background="image/pmiback.gif">
<form name="update" enctype="multipart/form-data" action="upload.php" method="post"> 
   <input type="hidden" name="max_file_size" value="1000000000"> <br><br><br>
  <center>    <input type="button" value="�ָ���ǰ�汾" onclick="back()"></center><br><br>
<div align="center"> 

<center><font face="����_GB2312"><b>��ѡ���ļ���</b></font> 
    <input name="userfile" type="file">
    <!--������һ������ userfile,��upload.php�У����ǾͿ���ʹ����������ˣ����ǿ���ֱ��ͨ��$userfile�������ص��ļ�������������һ�������ļ��ı���������ļ����ֱ���ͨ������һ��$userfile_name����ȡ�á���������������ľ�����;�� 
$userfile:�ڽ�Ҫ��������ļ��ķ������ϵ���ʱ�ļ����֡� 
$userfile_name:�ڷ�����ϵͳ�еĳ�ʼ�ļ����� 
$userfile_size:���ֽڼ���������ļ��Ĵ�С�� 
$userfile_type:����;�����ʼ�����Э�����͵��ļ���ǰ����������ṩ������Ϣ������˵��image/gif"�� 
//--> 
<br><br>
    <input type="button" value="�������" onclick="upgrade()"> 
</center> 

</div> 
<p align="center"><a href="shutdown.php"><img border="0" src="image/goback.gif" width="40" height="40"></a></p>
</form></body>
<script language="javaScript">

function back(){
	if(window.confirm("ȷʵҪ�ָ���һ�ε�����汾��"))
	{
		document.update.action="backsoft.php";
		document.update.submit();
	}else{
	}
//	window.alert(document.control.numbtemp.value);
}
function upgrade(){
	if(window.confirm("ȷʵҪ��������汾��"))
	{
		document.update.action="upload.php";
		document.update.submit();
	}else{
	}
//	window.alert(document.control.numbtemp.value);
}
</script>
</html>
