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
<meta name="GENERATOR" content="Microsoft FrontPage 5.0">
<meta name="ProgId" content="FrontPage.Editor.Document">
<!--
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
-->
<title>����Ա����</title>
</head>

<body bgcolor="#eef4f4">

<FORM name="manamanage" METHOD="POST" ACTION="check_manager.php">

<table border="0" cellspacing="1" width="100%" id="AutoNumber1" height="480">
  <tr>

    <td width="100%" height="480">��

 <table border="0" cellspacing="0" width="100%" id="AutoNumber2" height="44" bgcolor="#eef4f4">
  <tr>
    <td width="50%" height="39">
    <img border="0" src="image/mareg1.gif" width="283" height="57"><br>&nbsp;
    <font face="����_GB2312">����Ա������</font><input type="text" name="mananame1" style="position: relative; width: 120; height: 20">&nbsp;
    <br>&nbsp;<font face="����_GB2312"> ��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    �룺</font><input type="password" name="password1" style="position: relative; width: 120; height: 20"><br>&nbsp;
    <font face="����_GB2312">ȷ �� ���룺</font><input type="password" name="password2" style="position: relative; width: 120; height: 20">
    <p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <input type="button" value="�� ��" name="B1"  onclick="set()" ></td>
    <td width="50%" height="39">
    <img border="0" src="image/mareg2.gif" width="283" height="57"><br>
    <font face="����_GB2312">��ѡ��ע������Ա����</font>
    <select size="1" name="mananame2"  style="position: relative; width: 120; height: 20">
      <?php
        include "pmi_db.php";
        //----------------20051210;by yy;�û�ע�᷽ʽ�����ݿ��Ϊ�ļ���ȡ
        /*
        $db = mysql_connect(C_DB_HOST, "root");
      	mysql_select_db(C_DB_NAME,$db);
     	$result = mysql_query("SELECT * FROM ManagerTable",$db);
     	if(!$result)
     	{
     		echo 'û�����������ļ�¼';
    		mysql_close($db);
 	    	return 0;
 	    }
        while($row =mysql_fetch_row($result))
        {
          	echo "<option value=$row[0]>$row[0]</option>";
        }
        mysql_close($db);
        */
        //----------------20051210;by yy;�û�ע�᷽ʽ�����ݿ��Ϊ�ļ���ȡ

        //----------------20051213;by yy;�����û��ļ�ע�᷽ʽ��
        $users=GetManagerList();
        foreach ($users as $name) {

            echo "<option value=$name>$name</option>";
        }
        //----------------20051213;by yy;�����û��ļ�ע�᷽ʽ��
     ?>
        </select><p>
        <font face="����_GB2312">�� &nbsp;&nbsp; ��&nbsp;&nbsp;  ��&nbsp;&nbsp;  �룺 </font>
        <input type="password" name="password3"  style="position: relative; width: 120; height: 20">
        <p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        <input type="button" value="ɾ ��" name="logout"  onclick="set1()" >
        </td>
  </tr>
</table>
<br><br>
<table border="0" cellspacing="0" width="100%" id="AutoNumber3">
  <tr>
    <td width="100%">
    <p align="center">
    <img border="0" src="image/mareg3.gif" width="283" height="57">
    <br><font face="����_GB2312">��ѡ���޸ĵĹ���Ա����
	</font>

        <select size="1" name="mananame3"  style="position: relative; width: 120; height: 20">
          <?php
            //----------------20051210;by yy;�û�ע�᷽ʽ�����ݿ��Ϊ�ļ���ȡ
            /*
            $db = mysql_connect(C_DB_HOST, "root");
         	mysql_select_db(C_DB_NAME,$db);
        	$result = mysql_query("SELECT * FROM ManagerTable",$db);
        	if(!$result)
 	        {
 	        	echo 'û�����������ļ�¼';
	        	mysql_close($db);
 	        	return 0;
 	        }
            while($row =mysql_fetch_row($result))
            {
              	echo "<option value=$row[0]>$row[0]</option>";
            }
            mysql_close($db);
            */
            //----------------20051210;by yy;�û�ע�᷽ʽ�����ݿ��Ϊ�ļ���ȡ

            //----------------20051213;by yy;�����û��ļ�ע�᷽ʽ��
            $users=GetManagerList();
            foreach ($users as $name)
            {
                echo "<option value=$name>$name</option>";
            }
            //----------------20051213;by yy;�����û��ļ�ע�᷽ʽ��
          ?>
        </select>
        <br><font face="����_GB2312">�� �� �� �� �룺&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font><input type="password" name="password4"  style="position: relative; width: 120; height: 20">
        <br><font face="����_GB2312">�� �� �� �� �룺&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font><input type="password" name="password5"  style="position: relative; width: 120; height: 20">
        <br><font face="����_GB2312">ȷ �� �� �� �룺&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</font><input type="password" name="password6"  style="position: relative; width: 120; height: 20">
        <br><br>
        <input type="button" value="�� ��" name="change"  onclick="set2()" >
        <INPUT type=hidden value="0" name=islogin><br></td>
  </tr>
</table>

    </td>
  </tr>
</table>
</form>
</body>

<script language="javaScript">

function set(){

    var tlen;
	tlen=document.manamanage.mananame1.value;
	p1len=document.manamanage.password1.value;
	p2len=document.manamanage.password2.value;

	if (tlen.length<1 || p1len.length<1)
        alert("����Ա���������벻��Ϊ�գ�");
    else if (tlen.indexOf(" ")!= -1)
        alert("����Ա�����в����пո�");
    else if(tlen.length>20)
		alert("����Ա����������");
	else if(p1len.length>15)
		alert("���������");
	else if(p2len.length>15)
		alert("���������");
	else if(p1len!=p2len)
		alert("�����벻����");
    else if (p1len.indexOf(" ")!= -1)
        alert("�����в����пո�");
	else
	{
		document.manamanage.islogin.value=0;
		document.manamanage.action="check_manager.php";
		document.manamanage.submit();
	}
}

function set1(){
	var tlen;
	p1len=document.manamanage.password3.value;
	if(p1len.length>15)
		alert("���������");
    else if(p1len.length<1)
		alert("���벻��Ϊ�գ�");
    else if (p1len.indexOf(" ")!= -1)
        alert("�����в����пո�");
	else
	{
		document.manamanage.islogin.value=1;
		document.manamanage.action="check_manager.php";
		document.manamanage.submit();
	}
}

function set2(){
	var tlen;
	p3len=document.manamanage.password6.value;
	p1len=document.manamanage.password4.value;
	p2len=document.manamanage.password5.value;
	if(p1len.length>15)
		alert("�����������");
    else if(p1len.length<1)
		alert("���벻��Ϊ�գ�");
	else if(p2len.length>15)
		alert("�����������");
	else if(p2len.length<1)
		alert("�����벻��Ϊ�գ�");
	else if(p2len!=p3len)
		alert("���������벻����");
    else if (p2len.indexOf(" ")!= -1)
        alert("�����в����пո�");
    else
	{
		document.manamanage.islogin.value=2;
		document.manamanage.action="check_manager.php";
		document.manamanage.submit();
	}
	}

</script>
</html>