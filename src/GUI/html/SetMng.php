<?php
	include ("constant.php");
	include("mysql.lib.php");
@session_start();
	if($manager_ID==NULL)
	{
            echo '<html><head><title>��½ʧ��</title></head><body  background="image/backgroud.gif"><b>' ;
	    echo '���ȵ�½��<p>';
	    echo '<a href="login.html">����</a>';
            echo '</b></body></html>';
            exit();			
	}
	$dblink=new DB;
	$dblink->Database=C_DB_NAME;

//	echo $passwd."<br>";
	if ($passwd != $passwd2)
	{
		echo "�Բ�����������ľ���֤�Ų���ͬ�����飡";
		exit();
	}
	$slen=strlen($passwd);
	if ($slen > 18)
	{
		echo "�Բ��𣬾���֤�ų��ȳ���18�ֽڣ����飡";
		exit();
	}
	else
	{
		for ($i=0;$i<(18-$slen);$i++)
			$passwd="0".$passwd;
	}
//	echo $passwd."<br>";
	
	if ($opcode == 1)
	{
		$dblink->query("SELECT COUNT(*) FROM ".C_MNG_TBL." WHERE policenum='".addslashes($passwd)."' AND isdeleted!=1");
		list($count) = $dblink->next_record();
		$dblink->clean_results();
		if ($count != 0)
		{
			echo $count;
			echo "��ע�⣺����".$passwd."�Ѿ�����ȨΪ����Ա��";
		}
		else
		{
			$dblink->query("INSERT INTO ".C_MNG_TBL." (name,policenum,joindate,isdeleted) VALUES ('".addslashes($username)."','".addslashes($passwd)."','".time()."',0)");
			if ($dblink->Errno == 0)
				echo "����".$passwd."���ɹ���ȨΪ����Ա��";
			else
				echo "����".$passwd."��ȨΪ����Աʧ�ܣ�";
		}
	}

	if ($opcode == 2)
	{
		$dblink->query("SELECT COUNT(*) FROM ".C_MNG_TBL." WHERE policenum='".addslashes($passwd)."' AND isdeleted!=1");
		list($count) = $dblink->next_record();
		$dblink->clean_results();
		if ($count == 0)
		{
			echo "��ע�⣺����".$passwd."��û�б���ȨΪ����Ա�������޸����ϣ�";
		}
		else
		{
			$dblink->query("UPDATE ".C_MNG_TBL." SET name='".addslashes($username)."',policenum='".addslashes($passwd)."',joindate='".time()."',isdeleted=0 WHERE policenum='".addslashes($passwd)."' AND isdeleted!=1");
			if ($dblink->Errno == 0)
				echo "����".$passwd."�����ϱ��ɹ��޸ģ�";
			else
				echo "����".$passwd."�������޸Ĳ��ɹ�";
		}
	}

	if ($opcode == 3)
	{
		$dblink->query("SELECT COUNT(*) FROM ".C_MNG_TBL." WHERE isdeleted!=1");
		list($count) = $dblink->next_record();
		$dblink->clean_results();
		$act=1;
		if ($count < 2)
		{
			echo "�����ȼ���һ������Ա�����������ٱ���һ������Ա����";
			$act=0;
		}
		else
		{
			$dblink->query("DELETE FROM ".C_MNG_TBL." WHERE policenum='".addslashes($passwd)."' AND isdeleted!=1");
			if ($dblink->Errno != 0)
				$act=0;
		}
		if ($act != 0)
			echo "������".$passwd."���������Ա�б��Ѿ��ɹ���";
		else
			echo "������".$passwd."���������Ա�б�û�гɹ�";
	}
?>