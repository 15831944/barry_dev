<?php
	include("mysql.lib.php");

function MakeProxyDBTables($TableName)
{
	// ��ʼ�������ݱ�
	// ###################### ����Ա #######################
	$dblink=new DB;
	$dblink->Database=C_DB_NAME;
	if ($TableName == "" || $TableName == C_MNG_TBL)
	{
		$dblink->query("SELECT managerid FROM ".C_MNG_TBL);
		if ($dblink->Errno != 0)
		{
			$dblink->query("CREATE TABLE ".C_MNG_TBL." (
				managerid SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
				name CHAR(50) NOT NULL,
				policenum CHAR(50) NOT NULL,
				joindate INT UNSIGNED NOT NULL,
				isdeleted SMALLINT NOT NULL,
				PRIMARY KEY(managerid)
				)");// IF NOT EXISTS ".C_MNG_TBL);
		}
		$dblink->clean_results();
	}
	$dblink->close();
}

function MakeProxyDB()
{
	$dblink=new DB;
	$dblink->query("CREATE DATABASE ".C_DB_NAME);
	$dblink->Database=C_DB_NAME;
        echo "<p>�����ٴ�����...</p>";
        $dblink->connect(C_DB_NAME);
        if ($dblink->Errno == 0)
        {
        	echo "<p>�ɹ��������ݿ�!</p>";
        }
        else
        {
        	echo "<p>�ٴ��������ݿ�ʧ��! ��ȷ�����ݿ�ͷ�����������ȷȻ������.</p>";
        	echo "�����  ��$dblink->Errno<br>";
        	echo "����˵����$dblink->Error<br>";
        }
        $dblink->close();
        MakeProxyDBTables("");
}

	$dblink=new DB;
	$dblink->Database=C_DB_NAME;

	$dblink->connect();
	if ($dblink->Errno != 0)
	{
		if ($dblink->Errno == $ERR_NO_MYSQL)
		{
			print("$dblink->Error");
			$dblink->close();
			die();
		}
		else
		{
			print("�������ݿ�������ڳ����ؽ�����ȴ�...");
			$dblink->close();
			MakeProxyDB();
		}
	}
	else
	{
		$dblink->close();
		MakeProxyDBTables("");
	}
?>