-- on crée la table étudiant

create table _trigger_student (
_id integer primary key autoincrement,
_student_id integer not null,
_firstname text not null,
_lastname text not null,
_class text not null,
_section text not null
);

-- on insère des données dans la table étudiant

insert into _trigger_student (_student_id, _firstname, _lastname, _class, _section) values
(10, 'FirstName_10', 'LastName_10', 'Class_10', 'Section_10'),
(20, 'FirstName_20', 'LastName_20', 'Class_20', 'Section_20'),
(30, 'FirstName_30', 'LastName_30', 'Class_30', 'Section_30'),
(40, 'FirstName_40', 'LastName_40', 'Class_40', 'Section_40'),
(50, 'FirstName_50', 'LastName_50', 'Class_50', 'Section_50');
