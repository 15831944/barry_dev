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
    //echo "apn:$apname";
    if($mcode==1)
	{
        /*
        if (!$iparaformat1>"")
        {
             $iparaformat1="-";
        }
        */
        $ret=AddAssignFile($iappname,$iassignfile,
                 $iparatype1,$iparaname1,$icertitem1,$iparaformat1,
                 $iparatype2,$iparaname2,$icertitem2,$iparaformat2,
                 $iparatype3,$iparaname3,$icertitem3,$iparaformat3);
		$apname=$iappname;
	}
    if($mcode==2)
	{
        /*
        if (!$iparaformat>"")
        {
             $iparaformat="-";
        }
        */
        $ret=ModiAssignFiles($iassid,$iappname,$iassignfile,
                 $iparatype1,$iparaname1,$icertitem1,$iparaformat1,
                 $iparatype2,$iparaname2,$icertitem2,$iparaformat2,
                 $iparatype3,$iparaname3,$icertitem3,$iparaformat3,1);
		$apname=$iappname;
	}
    if($mcode==3)
	{
		$ret=ModiAssignFiles($iassid,$iappname,$iassignfile,
                 $iparatype1,$iparaname1,$icertitem1,$iparaformat1,
                 $iparatype2,$iparaname2,$icertitem2,$iparaformat2,
                 $iparatype3,$iparaname3,$icertitem3,$iparaformat3,0);
		$apname=$iappname;
	}
    //  echo "apn:$apname";
	echo '<html><head><title>��������޸�</title></head>';
    echo '<body background="image/pmiback.gif">';
    echo '<form name="SvrsAssign" METHOD="POST" ACTION="svrparamodi.php?opcode=1">';
    echo '<center><font face="����_GB2312"><b>';
    //----------------20051218;by cw;��ȡ/usr/SSLMPS/config/Assign.conf�еĹ����ļ��б�
        if (!isset($apname) or ($apname==""))
        {
            echo "����ѡ��Ӧ�ô�������ִ�й������ã�<br><br>";
            echo "<a href=\"server.php?numb=$numb\"><img border=\"0\" src=\"image/goback.gif\" width=\"40\" height=\"40\"></a><br>";
            echo "<p></b></font><br></center></form></body></html>";
            exit();
        }
        $Proxyname=$apname;           //�����������
        $assigns=GetAssignsList();
        $rcc=count($assigns);
        //echo "appname=$apname";
        $modied=0;
        if ($assigns[0][0]>" ")
        {
            //echo ">0erro";
            for($ri=0;$ri<$rcc;$ri++)
            {
                $appsname=$assigns[$ri][1];
                if(strcmp($Proxyname,$appsname)==0)
                {
                    $modied=1;
                    $assignid=$assigns[$ri][0];
                    $assignfile=$assigns[$ri][2];

                    $paratype1=$assigns[$ri][3];
                    $paraname1=$assigns[$ri][4];
                    $certitem1=$assigns[$ri][5];
                    $paraformat1=$assigns[$ri][6];

                    $paratype2=$assigns[$ri][7];
                    $paraname2=$assigns[$ri][8];
                    $certitem2=$assigns[$ri][9];
                    $paraformat2=$assigns[$ri][10];

                    $paratype3=$assigns[$ri][11];
                    $paraname3=$assigns[$ri][12];
                    $certitem3=$assigns[$ri][13];
                    $paraformat3=$assigns[$ri][14];
                    break;
                }
            }
        }
        if ($modied==0)
        {
            $assignid=0;
            $assignfile="";

            $paratype1="";
            $paraname1="";
            $certitem1="-";
            $paraformat1="";

            $paratype2="-";
            $paraname2="";
            $certitem2="-";
            $paraformat2="";

            $paratype3="-";
            $paraname3="";
            $certitem3="-";
            $paraformat3="";
        }
        echo "<input type=\"hidden\" name=\"iassid\" value=$assignid>";
    //----------------20051218;by cw;��ȡ/usr/SSLMPS/config/Assign.conf�еĹ����ļ��б�

    print("<table border=\"0\" cellspacing=\"1\" width=\"50%\" style=\"border-collapse: collapse\">
             <tr><td width=\"35%\"><font face=\"����_GB2312\">��������</font></td>
                 <td width=\"65%\" valign=\"top\">
                   <input type=\"TEXT\" name=\"iappname\" size=%30 maxlength=20 value=\"$Proxyname\" readonly=\"true\">
                 </td></tr>
             <tr><td><font face=\"����_GB2312\">�����ļ�</font></td>
	             <td width=\"54%\" valign=\"top\">
                   <input type=\"TEXT\" name=\"iassignfile\" size=%30 maxlength=200 value=\"$assignfile\">
                   </td></tr>
           </table><br>");
    //**************************************����1�������
    print("<table border=\"0\" cellspacing=\"1\" width=\"50%\" style=\"border-collapse: collapse\">
             <tr><td colspan=\"2\" align=\"left\">");
        if (($paratype1=="-") or ($paratype1==""))
        {
            echo "<input type=\"checkbox\" name=\"checkbox1\" value=\"checks1\" onchange=\"setparas()\">";
        } else
        {
            echo "<input type=\"checkbox\" name=\"checkbox1\" value=\"checks1\" checked onchange=\"setparas()\">";
        }
    print("       ��������һ</td></tr>
             <tr><td width=\"35%\"><font face=\"����_GB2312\">��������</font></td>
                 <td width=\"65%\" valign=\"top\">
            	   <select name=\"iparatype1\" style=\"position: relative; width: 152; height: 20\">");
            if (($paratype1=="-") or ($paratype1==""))
            {
                echo "<option value=\"-\">��</option>";
                echo "<option value=1>֤����ز���</option>";
                echo "<option value=0>��������</option>";
            } else if ($paratype1==1)
            {
                echo "<option value=\"-\">��</option>";
                echo "<option value=1 selected>֤����ز���</option>";
                echo "<option value=0>��������</option>";
            } else if ($paratype1==0)
            {
                echo "<option value=\"-\">��</option>";
                echo "<option value=1>֤����ز���</option>";
                echo "<option value=0 selected>��������</option>";
            }

    print("        </select></td></tr>
             <tr><td><font face=\"����_GB2312\">������</font></td>
                 <td><input name=\"iparaname1\" type=\"TEXT\" size=%30 maxlength=50 value=\"$paraname1\"></td></tr>
             <tr><td><font face=\"����_GB2312\">֤����</font></td>
                 <td>
            	   <select name=\"icertitem1\" style=\"position: relative; width: 152; height: 20\">");
            echo "<option value=\"-\">��</option>";
            if ($certitem1==1)
            {
                echo "<option value=1 selected>֤�����к�</option>";
            } else
            {
                echo "<option value=1>֤�����к�</option>";
            }
            if ($certitem1==8)
            {
                echo "<option value=8 selected>�û���</option>";
            } else
            {
                echo "<option value=8>�û���</option>";
            }
            if ($certitem1==15)
            {
                echo "<option value=15 selected>����֤��</option>";
            } else
            {
                echo "<option value=15>����֤��</option>";
            }
            if ($certitem1==121)
            {
                echo "<option value=121 selected>�û���1</option>";
            } else
            {
                echo "<option value=121>�û���1</option>";
            }
            if ($certitem1==122)
            {
                echo "<option value=122 selected>�û���2</option>";
            } else
            {
                echo "<option value=122>�û���2</option>";
            }
            if ($certitem1==123)
            {
                echo "<option value=123 selected>�û���3</option>";
            } else
            {
                echo "<option value=123>�û���3</option>";
            }
            if ($certitem1==6)
            {
                echo "<option value=6 selected>��֯</option>";
            } else
            {
                echo "<option value=6>��֯</option>";
            }
            if ($certitem1==7)
            {
                echo "<option value=7 selected>����</option>";
            } else
            {
                echo "<option value=7>����</option>";
            }
            if ($certitem1==13)
            {
                echo "<option value=13 selected>ְ��</option>";
            } else
            {
                echo "<option value=13>ְ��</option>";
            }
            if ($certitem1==11)
            {
                echo "<option value=11 selected>Ȩ��</option>";
            } else
            {
                echo "<option value=11>Ȩ��</option>";
            }

    print("        </select></td></tr>
             <tr><td><font face=\"����_GB2312\">������ʽ</font></td>
                 <td><input name=\"iparaformat1\" type=\"TEXT\" size=%30 maxlength=50 value=\"$paraformat1\"></td></tr>
             <tr><td colspan=\"2\" align=\"center\">");
    print("</table>");
    //********************** 20051222;by cw;���������������
    //**************************************����2�������
    print("<table border=\"0\" cellspacing=\"1\" width=\"50%\" style=\"border-collapse: collapse\">
             <tr><td colspan=\"2\" align=\"left\">");
        if (($paratype2=="-") or ($paratype2==""))
        {
            echo "<input type=\"checkbox\" name=\"checkbox2\" value=\"checks2\" onchange=\"setparas()\">";
        } else {
            echo "<input type=\"checkbox\" name=\"checkbox2\" value=\"checks2\" checked onchange=\"setparas()\">";
        }
    print("       �������ö�</td></tr>
             <tr><td width=\"35%\"><font face=\"����_GB2312\">��������</font></td>
                 <td width=\"65%\" valign=\"top\">
            	   <select name=\"iparatype2\" style=\"position: relative; width: 152; height: 20\">");
            if (($paratype2=="-") or ($paratype2==""))
            {
                echo "<option value=\"-\">��</option>";
                echo "<option value=1>֤����ز���</option>";
                echo "<option value=0>��������</option>";
            } else if ($paratype2==1)
            {
                echo "<option value=\"-\">��</option>";
                echo "<option value=1 selected>֤����ز���</option>";
                echo "<option value=0>��������</option>";
            } else if ($paratype2==0)
            {
                echo "<option value=\"-\">��</option>";
                echo "<option value=1>֤����ز���</option>";
                echo "<option value=0 selected>��������</option>";
            }
    print("        </select></td></tr>
             <tr><td><font face=\"����_GB2312\">������</font></td>
                 <td><input name=\"iparaname2\" type=\"TEXT\" size=%30 maxlength=50 value=\"$paraname2\"></td></tr>
             <tr><td><font face=\"����_GB2312\">֤����</font></td>
                 <td>
            	   <select name=\"icertitem2\" style=\"position: relative; width: 152; height: 20\">");
            echo "<option value=\"-\">��</option>";
            if ($certitem2==1)
            {
                echo "<option value=1 selected>֤�����к�</option>";
            } else
            {
                echo "<option value=1>֤�����к�</option>";
            }
            if ($certitem2==8)
            {
                echo "<option value=8 selected>�û���</option>";
            } else
            {
                echo "<option value=8>�û���</option>";
            }
            if ($certitem2==15)
            {
                echo "<option value=15 selected>����֤��</option>";
            } else
            {
                echo "<option value=15>����֤��</option>";
            }
            if ($certitem2==121)
            {
                echo "<option value=121 selected>�û���1</option>";
            } else
            {
                echo "<option value=121>�û���1</option>";
            }
            if ($certitem2==122)
            {
                echo "<option value=122 selected>�û���2</option>";
            } else
            {
                echo "<option value=122>�û���2</option>";
            }
            if ($certitem2==123)
            {
                echo "<option value=123 selected>�û���3</option>";
            } else
            {
                echo "<option value=123>�û���3</option>";
            }
            if ($certitem2==6)
            {
                echo "<option value=6 selected>��֯</option>";
            } else
            {
                echo "<option value=6>��֯</option>";
            }
            if ($certitem2==7)
            {
                echo "<option value=7 selected>����</option>";
            } else
            {
                echo "<option value=7>����</option>";
            }
            if ($certitem2==13)
            {
                echo "<option value=13 selected>ְ��</option>";
            } else
            {
                echo "<option value=13>ְ��</option>";
            }
            if ($certitem2==11)
            {
                echo "<option value=11 selected>Ȩ��</option>";
            } else
            {
                echo "<option value=11>Ȩ��</option>";
            }

    print("        </select></td></tr>
             <tr><td><font face=\"����_GB2312\">������ʽ</font></td>
                 <td><input name=\"iparaformat2\" type=\"TEXT\" size=%30 maxlength=50 value=\"$paraformat2\"></td></tr>
             <tr><td colspan=\"2\" align=\"center\">");
    print("</table>");
    //**************************************����3�������
    print("<table border=\"0\" cellspacing=\"1\" width=\"50%\" style=\"border-collapse: collapse\">
             <tr><td colspan=\"2\" align=\"left\">");
        if (($paratype3=="-") or ($paratype3==""))
        {
           echo "<input type=\"checkbox\" name=\"checkbox3\" value=\"checks3\" onchange=\"setparas()\">";
        } else {
           echo "<input type=\"checkbox\" name=\"checkbox3\" value=\"checks3\" checked onchange=\"setparas()\">";
        }
    print("      ����������</td></tr>
             <tr><td width=\"35%\"><font face=\"����_GB2312\">��������</font></td>
                 <td width=\"65%\" valign=\"top\">
            	   <select name=\"iparatype3\" style=\"position: relative; width: 152; height: 20\">");
            if (($paratype3=="-") or ($paratype3==""))
            {
                echo "<option value=\"-\">��</option>";
                echo "<option value=1>֤����ز���</option>";
                echo "<option value=0>��������</option>";
            } else if ($paratype3==1)
            {
                echo "<option value=\"-\">��</option>";
                echo "<option value=1 selected>֤����ز���</option>";
                echo "<option value=0>��������</option>";
            } else if ($paratype3==0)
            {
                echo "<option value=\"-\">��</option>";
                echo "<option value=1>֤����ز���</option>";
                echo "<option value=0 selected>��������</option>";
            }
    print("        </select></td></tr>
             <tr><td><font face=\"����_GB2312\">������</font></td>
                 <td><input name=\"iparaname3\" type=\"TEXT\" size=%30 maxlength=50 value=\"$paraname3\"></td></tr>
             <tr><td><font face=\"����_GB2312\">֤����</font></td>
                 <td>
            	   <select name=\"icertitem3\" style=\"position: relative; width: 152; height: 20\">");
            echo "<option value=\"-\">��</option>";
            if ($certitem3==1)
            {
                echo "<option value=1 selected>֤�����к�</option>";
            } else
            {
                echo "<option value=1>֤�����к�</option>";
            }
            if ($certitem3==8)
            {
                echo "<option value=8 selected>�û���</option>";
            } else
            {
                echo "<option value=8>�û���</option>";
            }
            if ($certitem3==15)
            {
                echo "<option value=15 selected>����֤��</option>";
            } else
            {
                echo "<option value=15>����֤��</option>";
            }
            if ($certitem3==121)
            {
                echo "<option value=121 selected>�û���1</option>";
            } else
            {
                echo "<option value=121>�û���1</option>";
            }
            if ($certitem3==122)
            {
                echo "<option value=122 selected>�û���2</option>";
            } else
            {
                echo "<option value=122>�û���2</option>";
            }
            if ($certitem3==123)
            {
                echo "<option value=123 selected>�û���3</option>";
            } else
            {
                echo "<option value=123>�û���3</option>";
            }
            if ($certitem3==6)
            {
                echo "<option value=6 selected>��֯</option>";
            } else
            {
                echo "<option value=6>��֯</option>";
            }
            if ($certitem3==7)
            {
                echo "<option value=7 selected>����</option>";
            } else
            {
                echo "<option value=7>����</option>";
            }
            if ($certitem3==13)
            {
                echo "<option value=13 selected>ְ��</option>";
            } else
            {
                echo "<option value=13>ְ��</option>";
            }
            if ($certitem3==11)
            {
                echo "<option value=11 selected>Ȩ��</option>";
            } else
            {
                echo "<option value=11>Ȩ��</option>";
            }

    print("        </select></td></tr>
             <tr><td><font face=\"����_GB2312\">������ʽ</font></td>
                 <td><input name=\"iparaformat3\" type=\"TEXT\" size=%30 maxlength=50 value=\"$paraformat3\"></td></tr>
             <tr><td colspan=\"2\" align=\"center\"><br>");
    //********************** 20051222;by cw;���������������
    if ($modied==0)
    {
         echo "  <input type=\"button\" value=\"��ӹ���\" name=\"addAssign\" onClick=\"addass()\">";
    } else
    {
         echo "  <input type=\"button\" value=\"ɾ������\" name=\"DelAssign\" onClick=\"delass()\">";
         echo "&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"button\" value=\"�޸Ĺ���\" name=\"ModiAssign\" onClick=\"modiass()\">";
    }
    print("      </td></tr>
           </table>");
    //----------------20051218;by cw;��ȡ/usr/SSLMPS/config/denypages.conf�е�Denypage�б�
    //echo "<input type=\"hidden\" name=\"numb\" value=\"$numb\">";
	echo "<p></b></font><br></center></form></body>";

?>

<script language="javaScript">
function setparas()
{
    if (!document.SvrsAssign.checkbox1.checked) {
        document.SvrsAssign.iparatype1.value="-";
        document.SvrsAssign.iparaname1.value="";
        document.SvrsAssign.icertitem1.value="-";
        document.SvrsAssign.iparaformat1.value="";
    }
    if (!document.SvrsAssign.checkbox2.checked) {
        document.SvrsAssign.iparatype2.value="-";
        document.SvrsAssign.iparaname2.value="";
        document.SvrsAssign.icertitem2.value="-";
        document.SvrsAssign.iparaformat2.value="";
    }
    if (!document.SvrsAssign.checkbox3.checked) {
        document.SvrsAssign.iparatype3.value="-";
        document.SvrsAssign.iparaname3.value="";
        document.SvrsAssign.icertitem3.value="-";
        document.SvrsAssign.iparaformat3.value="";
    }
}

function addass()
{
  var filelen=document.SvrsAssign.iassignfile.value;
  var namelen,ptype,citem,formatlen;
  var checkOK=1;

  setparas();

  if(window.confirm("ȷ����� ��Ӧ�ô��������� ��"))
  {
    if ((document.SvrsAssign.checkbox1.checked) && (checkOK==1)) {
        namelen=document.SvrsAssign.iparaname1.value;
        ptype=document.SvrsAssign.iparatype1.value;
        citem=document.SvrsAssign.icertitem1.value;
        formatlen=document.SvrsAssign.iparaformat1.value;
        checkOK=0;
        if (filelen=="")
	        alert(" ��������һ:�����ļ�����Ϊ�գ�");
        else if(filelen.length>200)
	        alert(" ��������һ:�����ļ���������");
        else if (filelen.indexOf(" ")!= -1)
            alert(" ��������һ:�����ļ����в��ܴ��ڿո�");
        else if(namelen=="")
	        alert(" ��������һ:����������Ϊ�գ�");
        else if(namelen.length>50)
	        alert(" ��������һ:������������");
        else if (namelen.indexOf(" ")!= -1)
            alert(" ��������һ:�������в��ܴ��ڿո�");
    	else if((ptype==1) && (citem==15) && (formatlen==""))
	        alert(" ��������һ:��֤����Ϊ������֤�š�ʱ��������ʽ����Ϊ�գ�");
        else if (formatlen.indexOf(" ")!= -1)
            alert(" ��������һ:������ʽ�в��ܴ��ڿո�");
        else {
            checkOK=1;
        }
    }
    if ((document.SvrsAssign.checkbox2.checked) && (checkOK==1)) {
        namelen=document.SvrsAssign.iparaname2.value;
        ptype=document.SvrsAssign.iparatype2.value;
        citem=document.SvrsAssign.icertitem2.value;
        formatlen=document.SvrsAssign.iparaformat2.value;
        checkOK=0;
        if (filelen=="")
	    	alert(" �������ö�:�����ļ�����Ϊ�գ�");
        else if(filelen.length>200)
	    	alert(" �������ö�:�����ļ���������");
        else if (filelen.indexOf(" ")!= -1)
            alert(" �������ö�:�����ļ����в��ܴ��ڿո�");
        else if(namelen=="")
	    	alert(" �������ö�:����������Ϊ�գ�");
        else if(namelen.length>50)
	    	alert(" �������ö�:������������");
        else if (namelen.indexOf(" ")!= -1)
            alert(" �������ö�:�������в��ܴ��ڿո�");
    	else if((ptype==1) && (citem==15) && (formatlen==""))
	    	alert(" �������ö�:��֤����Ϊ������֤�š�ʱ��������ʽ����Ϊ�գ�");
        else if (formatlen.indexOf(" ")!= -1)
            alert(" �������ö�:������ʽ�в��ܴ��ڿո�");
        else {
            checkOK=1;
        }
    }
    if ((document.SvrsAssign.checkbox3.checked) && (checkOK==1)) {
        namelen=document.SvrsAssign.iparaname3.value;
        ptype=document.SvrsAssign.iparatype3.value;
        citem=document.SvrsAssign.icertitem3.value;
        formatlen=document.SvrsAssign.iparaformat3.value;
        checkOK=0;
        if (filelen=="")
	    	alert(" ����������:�����ļ�����Ϊ�գ�");
        else if(filelen.length>200)
	    	alert(" ����������:�����ļ���������");
        else if (filelen.indexOf(" ")!= -1)
            alert(" ����������:�����ļ����в��ܴ��ڿո�");
        else if(namelen=="")
	    	alert(" ����������:����������Ϊ�գ�");
        else if(namelen.length>50)
	    	alert(" ����������:������������");
        else if (namelen.indexOf(" ")!= -1)
            alert(" ����������:�������в��ܴ��ڿո�");
    	else if((ptype==1) && (citem==15) && (formatlen==""))
	    	alert(" ����������:��֤����Ϊ������֤�š�ʱ��������ʽ����Ϊ�գ�");
        else if (formatlen.indexOf(" ")!= -1)
            alert(" ����������:������ʽ�в��ܴ��ڿո�");
        else {
            checkOK=1;
        }
    }
    if (checkOK==1)
    {
        document.SvrsAssign.action="set_svrpara.php?mcode=1";
        document.SvrsAssign.submit();
    }
  }
}

function modiass()
{
  var filelen=document.SvrsAssign.iassignfile.value;
  var namelen,ptype,citem,formatlen;
  var checkOK=1;

  setparas();

  if(window.confirm("ȷ���޸Ĵ�Ӧ�ô�����������"))
  {
    if ((document.SvrsAssign.checkbox1.checked) && (checkOK==1)) {
        namelen=document.SvrsAssign.iparaname1.value;
        ptype=document.SvrsAssign.iparatype1.value;
        citem=document.SvrsAssign.icertitem1.value;
        formatlen=document.SvrsAssign.iparaformat1.value;
        checkOK=0;
        if (filelen=="")
	        alert(" ��������һ:�����ļ�����Ϊ�գ�");
        else if(filelen.length>200)
	        alert(" ��������һ:�����ļ���������");
        else if (filelen.indexOf(" ")!= -1)
            alert(" ��������һ:�����ļ����в��ܴ��ڿո�");
        else if(namelen=="")
	        alert(" ��������һ:����������Ϊ�գ�");
        else if(namelen.length>50)
	        alert(" ��������һ:������������");
        else if (namelen.indexOf(" ")!= -1)
            alert(" ��������һ:�������в��ܴ��ڿո�");
    	else if((ptype==1) && (citem==15) && (formatlen==""))
	        alert(" ��������һ:��֤����Ϊ������֤�š�ʱ��������ʽ����Ϊ�գ�");
        else if (formatlen.indexOf(" ")!= -1)
            alert(" ��������һ:������ʽ�в��ܴ��ڿո�");
        else {
            checkOK=1;
        }
    }
    if ((document.SvrsAssign.checkbox2.checked) && (checkOK==1)) {
        namelen=document.SvrsAssign.iparaname2.value;
        ptype=document.SvrsAssign.iparatype2.value;
        citem=document.SvrsAssign.icertitem2.value;
        formatlen=document.SvrsAssign.iparaformat2.value;
        checkOK=0;
        if (filelen=="")
	    	alert(" �������ö�:�����ļ�����Ϊ�գ�");
        else if(filelen.length>200)
	    	alert(" �������ö�:�����ļ���������");
        else if (filelen.indexOf(" ")!= -1)
            alert(" �������ö�:�����ļ����в��ܴ��ڿո�");
        else if(namelen=="")
	    	alert(" �������ö�:����������Ϊ�գ�");
        else if(namelen.length>50)
	    	alert(" �������ö�:������������");
        else if (namelen.indexOf(" ")!= -1)
            alert(" �������ö�:�������в��ܴ��ڿո�");
    	else if((ptype==1) && (citem==15) && (formatlen==""))
	    	alert(" �������ö�:��֤����Ϊ������֤�š�ʱ��������ʽ����Ϊ�գ�");
        else if (formatlen.indexOf(" ")!= -1)
            alert(" �������ö�:������ʽ�в��ܴ��ڿո�");
        else {
            checkOK=1;
        }
    }
    if ((document.SvrsAssign.checkbox3.checked) && (checkOK==1)) {
        namelen=document.SvrsAssign.iparaname3.value;
        ptype=document.SvrsAssign.iparatype3.value;
        citem=document.SvrsAssign.icertitem3.value;
        formatlen=document.SvrsAssign.iparaformat3.value;
        checkOK=0;
        if (filelen=="")
	    	alert(" ����������:�����ļ�����Ϊ�գ�");
        else if(filelen.length>200)
	    	alert(" ����������:�����ļ���������");
        else if (filelen.indexOf(" ")!= -1)
            alert(" ����������:�����ļ����в��ܴ��ڿո�");
        else if(namelen=="")
	    	alert(" ����������:����������Ϊ�գ�");
        else if(namelen.length>50)
	    	alert(" ����������:������������");
        else if (namelen.indexOf(" ")!= -1)
            alert(" ����������:�������в��ܴ��ڿո�");
    	else if((ptype==1) && (citem==15) && (formatlen==""))
	    	alert(" ����������:��֤����Ϊ������֤�š�ʱ��������ʽ����Ϊ�գ�");
        else if (formatlen.indexOf(" ")!= -1)
            alert(" ����������:������ʽ�в��ܴ��ڿո�");
        else {
            checkOK=1;
        }
    }
    if (checkOK==1)
    {
        document.SvrsAssign.action="set_svrpara.php?mcode=2";
        document.SvrsAssign.submit();
    }
  }
}

function delass()
{
  setparas();
  if(window.confirm("ȷ��ɾ�� ��Ӧ�ô��������� ��"))
  {
    document.SvrsAssign.action="set_svrpara.php?mcode=3";
    document.SvrsAssign.submit();
  }
}
</script>
</html>