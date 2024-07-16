-- on crée la table tree_html

create table _tree_html (
_id integer primary key autoincrement
, _parent_id int not null
, _name varchar(255) not null
, _order integer not null default 0
);

-- on insère des données dans la table tree_html

insert into _tree_html (_id, _parent_id, _name) values
(1, 0, 'Element_1'),
(2, 0, 'Element_2'),
(3, 0, 'Element_3');

insert into _tree_html (_id, _parent_id, _name) values
(9, 6, 'Element_1.3.1'),
(10, 6, 'Element_1.3.2'),
(11, 6, 'Element_1.3.3'),
(12, 6, 'Element_1.3.4'),
(13, 6, 'Element_1.3.5');

insert into _tree_html (_id, _parent_id, _name) values
(4, 1, 'Element_1.1'),
(5, 1, 'Element_1.2'),
(6, 1, 'Element_1.3'),
(7, 1, 'Element_1.4'),
(8, 1, 'Element_1.5');

insert into _tree_html (_id, _parent_id, _name) values
(14, 11, 'Element_1.3.3.1'),
(15, 11, 'Element_1.3.3.2'),
(16, 11, 'Element_1.3.3.3'),
(17, 11, 'Element_1.3.3.4'),
(18, 11, 'Element_1.3.3.5');
