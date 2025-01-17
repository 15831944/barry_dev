create table user (
	objid 		varchar(255) not null primary key,
	username	varchar(255),
	passwd		varchar(32),
	engname		varchar(64),
	firstname	varchar(64),
	lastname	varchar(64),
	email		varchar(255),
	workemail	varchar(255),
	otheremail	varchar(255),
	cell		varchar(32),
	homephone	varchar(32),
	workphone	varchar(32),
	address		varchar(255),
	country		varchar(64),
	state		varchar(64),
	city		varchar(64),
	zip			varchar(64),
	qq			varchar(32),
	msn			varchar(128),
	nickname	varchar(128),
	profession	varchar(64),
	sex			char,
	birthday	date,
	description	varchar(255),
	status 		char,
	xml			text
);
