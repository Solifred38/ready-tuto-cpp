-- on crée un trigger avant chaque insertion dans la table étudiant
-- on vérifie que le prénom et le nom sont alaphabétiques
-- sinon, on lève une exception

create trigger _trigger_student_before
before insert on _trigger_student
begin
    select case
        when new._firstname is not null and new._lastname is not null
        and (new._firstname glob '*[^a-za-z]*' and new._lastname glob '*[^a-za-z]*') then
        raise(abort, 'erreur : le prénom et le nom doivent être alphabétiques.')
    end;
end;
