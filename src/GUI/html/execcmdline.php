<?php
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/backgroud.gif"><b>' ;
	    echo '���ȵ�½��<p>';
	    echo '<a href="login.html">����</a>';
            echo '</b></body></html>';
            exit();			
	}
		print("<form name=\"execcmd\" method=\"post\">
		��������Ҫִ�е�������<br>
		<input type=\"TEXT\" name=\"cmdline\" value=\"\" size=100 maxlength=400>
		<br>
	        <input type=\"submit\" value=\"ִ��ȷ��\" name=\"OK\" onclick=\"execcmd.action='eusercmd.php'\">
	        <input type=\"submit\" value=\"���ص�¼ҳ\" name=\"log\" onclick=\"execcmd.action='login.html'\">
		</form>");
?>
