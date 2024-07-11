create table _maj (
_id integer primary key autoincrement,
, _code varchar(255) not null,
, _name varchar(255) not null,
);

create table _user (
_id integer primary key autoincrement,
, _pseudo varchar(255) not null,
, _password varchar(255) not null,
);
