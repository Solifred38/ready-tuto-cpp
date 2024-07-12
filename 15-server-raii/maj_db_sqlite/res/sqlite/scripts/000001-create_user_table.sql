create table _user (
_id integer primary key autoincrement
, _pseudo varchar(255) not null
, _password varchar(255) not null
);

insert into _user (_pseudo, _password)
values ("gkesse", "123456");
