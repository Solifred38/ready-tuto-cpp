-- action_1 : sans trigger
-- on a essayé d'ajouter une ligne de données où le prenom est un nombre
-- la ligne de données a été ajouté

insert into _trigger_student (_student_id, _firstname, _lastname, _class, _section) values
(60, 6001, 'LastName_60', 'Class_60', 'Section_60');

select * from _trigger_student;

-- action_2 : avec trigger
-- on a essayé d'ajouter une ligne de données où le prenom est un nombre
-- la ligne de données n'a pas été ajouté
-- une exception a été levée

insert into _trigger_student (_student_id, _firstname, _lastname, _class, _section) values
(70, 7001, 'LastName_70', 'Class_70', 'Section_70');

select * from _trigger_student;

