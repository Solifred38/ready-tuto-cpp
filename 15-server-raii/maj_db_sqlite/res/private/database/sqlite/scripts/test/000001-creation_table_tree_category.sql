-- on crée la table catégorie

create table _tree_category (
_id integer primary key autoincrement,
_parent_id integer not null,
_name text not null
);

-- on insère des données dans la table catégorie

insert into _tree_category (_id, _parent_id, _name) values
(1, 0, 'Name_1'),
(2, 1, 'Name_1.1'),
(3, 1, 'Name_1.2'),
(4, 2, 'Name_1.2.1'),
(5, 2, 'Name_1.2.2'),
(6, 3, 'Name_1.2.1'),
(7, 3, 'Name_1.2.2');
