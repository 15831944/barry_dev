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
    include "constant.php";
?>
<html>

<head>
<meta name="GENERATOR" content="Microsoft FrontPage 5.0">
<meta name="ProgId" content="FrontPage.Editor.Document">
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">

<title>DenyPage�б�����</title>
</head>

<body bgcolor="#eef4f4">

<FORM name="Denypages" METHOD="POST" action="--WEBBOT-SELF--" enctype="multipart/form-data">
<table border="0" cellspacing="1" width="100%" id="AutoNumber2" height="480">
  <tr>

    <td width="100%" height="480">
     <img border="0" src="image/denyhead.gif" width="283" height="57">
     <b><font face="����_GB2312" color="#006699">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ҳ��
    <?php
    //��ʱʹ��
    //$nr=99;
    //$aaa=floor($nr/10);
    //echo $aaa;

    $denyps=GetDenypagesList();
    $nr=count($denyps);
    //print_r( $pmiservs);
	if($nr%10==0)
		$tmp=floor($nr/10);
	else
		$tmp=floor($nr/10)+1;
    if ($numb<=0)
        $numb=1;
 	print(":$numb/$tmp&nbsp;&nbsp;&nbsp;ÿҳ�����ʾ10��&nbsp;&nbsp;&nbsp;��¼��:$nr</font></b>");

	print("<table border=\"2\" cellspacing=\"1\" bordercolor=\"#55847e\" width=\"100%\" style=\"border-collapse: collapse\">".
			"<tr bgcolor=\"#95bdbf\">\n".
			"<th width=5%></th>\n".
			"<th width=%15><center>Denypage����</center></th>\n".
  			"<th width=%80><center>Denypage�ļ���</center></th>\n".
  	//		"<th width=%8><center>��λ����</center></th>\n".
  	//		"<th width=%15>֤����֤����</th>\n".
  	//		"<th width=%35><center>����</center></th>\n".
 			"</tr>\n");
		$aaa=($numb-1)*10+1;             //��ҳ�ĵ�һ����¼��rid
        if (($numb*10)<=$nr)
        {
            $bbb=$numb*10;                   //��ҳ�����һ����¼��rid
        } else
        {
            $bbb=$nr;
        }
        $rs=$bbb-$aaa;                       //��ҳ��ʾ�ļ�¼��-1��
        //$count=0;
        $ri=0;

		if ($nr != 0)
		{
            while ($ri<=$rs)
			{
                $rid=$denyps[$aaa-1][0];
                $denyname=$denyps[$aaa-1][1];
                //---------------20060101;by cw;ֻ��ʾ�ļ���
                //$denypath=DENYPAGEFILEPATH.$denyps[$aaa-1][2];
                $denypath=$denyps[$aaa-1][2];
                //$orgname=$denyps[$aaa-1][3];
                //$onoff=$denyps[$aaa-1][4];
                echo "<tr><th><input type=\"radio\" name=\"RadioGroupID\" value=$rid></th>\n";
                //echo "<input type=\"hidden\" name=\"RuleID\" value=$rid>";
                echo "<th>$denyname</th><th>$denypath</th>\n";
                /*
                if ($onoff=="on")
                {
                    echo "<th><label>����<input type=\"radio\" name=\"RGSW$rid\" value=\"on\" checked></label>\n";
                    echo "&nbsp;&nbsp;&nbsp;<label>�ر�<input type=\"radio\" name=\"RGSW$rid\" value=\"off\"></label></th></tr>\n";
                } else
                {
                    echo "<th><label>����<input type=\"radio\" name=\"RGSW$rid\" value=\"on\"></label>\n";
                    echo "&nbsp;&nbsp;&nbsp;<label>�ر�<input type=\"radio\" name=\"RGSW$rid\" value=\"off\" checked></label></th></tr>\n";
                }

                if ($onoff=="on")
                {
                    echo "<th>����</th></tr>\n";
                } else
                {
                    echo "<th>�ر�</th></tr>\n";
                }
                */
                echo "</tr>\n";
                $aaa=$aaa+1;
			    $ri+=1;
			}

		}
		//$dblink->close();
        $temp=$numb;

		print("</table><br>");
        //echo "radioid=".$RadioGroupID;
        echo "<input type=\"hidden\" name=\"numb\" value=\"$numb\">";
		 // action=\"setprot.php?opcode=$opcode\">;

        echo "<input type=\"button\" value=\"ɾ��Denypage\" name=\"delrule\" onclick=\"del()\">";
        print("&nbsp;&nbsp;&nbsp;");
        echo "<input type=\"button\" value=\"�޸�Denypage\" name=\"editrule\" onclick=\"modify()\">";

	print("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
	print("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\n");
	print("<font face=\"����_GB2312\" color=\"#C0C0C0\"><b>");

    if($numb>1)
   	{
  		$temp=$numb-1;
	 	echo "<a href=\"denypage.php?numb=$temp\">��һҳ</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
	}else{
		echo "��һҳ&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
	}
	if($nr>$numb*10)
	{
  		$temp=$numb+1;
	 	echo "<a href=\"denypage.php?numb=$temp\">��һҳ</a>";
	}else{
		echo "��һҳ";
	}

	print("</font><br><br><center>");

    print("<table border=\"0\" cellspacing=\"1\" width=\"50%\" style=\"border-collapse: collapse\">
             <tr><td width=\"35%\"><font face=\"����_GB2312\">Denypage����</font></td>
                 <td width=\"65%\" valign=\"top\">
                   <input type=\"TEXT\" name=\"denypname\" size=%30 maxlength=15>
                 </td></tr>
             <tr><td><font face=\"����_GB2312\">Denypage�ļ���</font></td>
	             <td width=\"54%\" valign=\"top\"><input type=\"TEXT\" name=\"denyppath\" size=%30 maxlength=200></td></tr>
             <tr><td><font face=\"����_GB2312\">ѡ��DenypageԴ�ļ�</font></td>
                 <td><input name=\"denypfile\" type=\"file\" size=%32 maxlength=250></td></tr>
             <tr><td colspan=\"2\" align=\"center\"><br>
                   <input type=\"button\" value=\"���Denypage\" name=\"addRule\" onClick=\"check()\">
                 </td></tr>
           </table>");
    ?>
     </center>
     </td>
  </tr>

</table>
</form>
</body>

<script language="javaScript">
/*
function set(){
	if(document.control.R1[0].checked)
	{
		document.control.action="pmirole.php?numb=1&rolenumb=1";
		document.control.submit();
	}else if(document.control.R1[1].checked)
	{
		document.control.action="pmi1.php?numb=1&rolenumb=1";
		document.control.submit();
	}else if(document.control.R1[2].checked)
	{
		document.control.action="pmi_all.php?numb=1&rolenumb=1";
		document.control.submit();
	}
}
*/

function del()
{   //var arra=document.PMIcontrol.RadioGroupID.value;
    //arra=2;
    {   //alert(arra);
        if(window.confirm("��ɾ����Denypage�����Denypage��Ӧ����\n��������Denypage�����Ϊ�ޣ�\n\n\nȷ��ɾ����"))
	    {
            document.Denypages.action="denypage_del.php";
     	    document.Denypages.submit();
        }
     }
}

function modify()
{
    document.Denypages.action="denypage_modi.php";
    document.Denypages.submit();

}

function check(){

    var namelen=document.Denypages.denypname.value;
	var pathlen=document.Denypages.denyppath.value;
    var filelen=document.Denypages.denypfile.value;
    //var fso;
    //fso = new ActiveXObject("Scripting.FileSystemObject");
	
	if(namelen.length>20)
		alert("Denypage���ƹ�����");
	else if(namelen=="")
		alert("Denypage���Ʋ���Ϊ�գ�");
	else if(pathlen.length>200)
		alert("Denypage�ļ���������");
	else if(pathlen=="")
		alert("Denypage�ļ�������Ϊ�գ�");
    else if(filelen=="")
		alert("DenypageԴ�ļ�����Ϊ�գ�");
    else if(filelen.length>250)
		alert("DenypageԴ�ļ���������");
   //else if(!htmlcheck(pathlen))
   //		alert("Denypage�ļ���������.html/.htmΪ��׺��");
		else
    {
        //if (fso.FileExists(filelen)) {
	        document.Denypages.action="denypage_modiok.php?opcode=1";
	        document.Denypages.submit();
        //} else {
        //    alert("Denypage�ļ������ڣ�");
        //}
    }
}

function htmlcheck(strlen)
{
		var strpos=strlen.lastIndexOf(".");
		var extstr;
		if (strpos>0) {
		    extstr=strlen.substr(strpos+1);
	  } else {
		    extstr="";
	  }
	  if ((extstr=="htm") || (extstr=="html"))
	  {
	    return(true);
	  } else {
	  	return(false);
	  }
}

</script>
</html>
