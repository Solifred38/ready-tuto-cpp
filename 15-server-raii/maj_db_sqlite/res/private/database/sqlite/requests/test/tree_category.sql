-- on sélection les données de la table catégorie
-- on utilise une table récursive
-- on utilise la méthode union all
-- les données sont lues correctement

with recursive _tree_category_cte as (
select _id, _parent_id, _name
from _tree_category
where _parent_id = 0
union all
select t1._id, t1._parent_id, t1._name
from _tree_category t1
join _tree_category_cte t2 on t1._parent_id = t2._id
) select * from _tree_category_cte;

-- on sélection les données de la table catégorie
-- on utilise une table récursive
-- on utilise la méthode join level
-- les données sont lues correctement

with recursive _tree_category_cte as (
select _id, _parent_id, _name, 0 as _level
from _tree_category
where _parent_id = 0
union all
select t1._id, t1._parent_id, t1._name, t2._level + 1
from _tree_category t1
join _tree_category_cte t2 on t1._parent_id = t2._id
) select * from _tree_category_cte;

-- on sélection les données de la table catégorie
-- on utilise une table récursive
-- on utilise la méthode concaténantion de chemin
-- les données sont lues correctement

with recursive _tree_category_cte as (
select _id, _parent_id, _name, cast(_id as text) as _path
from _tree_category
where _parent_id = 0
union all
select t1._id, t1._parent_id, t1._name, t2._path || '->' || t1._id
from _tree_category t1
join _tree_category_cte t2 on t1._parent_id = t2._id
) select * from _tree_category_cte;

select * from _tree_category;

