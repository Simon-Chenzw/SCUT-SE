-- craete table
source ../exp3/backup.sql

-- 2.1 授权与回收
-- a) 建立多个用户，给他们赋予不同的权限，然后查看是否真正拥有被授予的权限了。
-- [1] 建立用户U1、U2、U3、U4、U5、U6、U7，选择其数据库角色全部允许为public。
create user U1;
create user U2;
create user U3;
create user U4;
create user U5;
create user U6;
create user U7;
select user from mysql.user;

-- [2] 在DBA与七个用户之间进行授权
show grants for U1;
grant all privileges on * to U1;
show grants for U1;

-- [3] 尝试用U1为别的用户授权，检验with grant option的作用
grant all privileges on * to U1 with grant option;
grant all on db_SPJ.S to U2;

-- [4] 在授权之后验证用户是否拥有了相应的权限，注意系统提示。
select * from db_SPJ.S;

-- b) 回收权限。将[1]授予的权限部分收回，检查回收后，该用户是否真正丧失了对数据的相应权限。
-- [1] 用revoke收回权限。
revoke all on * from U1;

-- [2] 在回收权限之后验证用户是否真正丧失了该权限。
-- 思考：revoke语句有没有类似于“with grant option”的功能，即级联把该用户授出的权限收回？
-- 答：没有

-- 2.2 数据库角色
-- a) 角色的创建与授权。
-- [1] 首先创建一个角色 R1
create role R1;

-- [2] 然后使用GRANT语句，使角色R1拥有S表的SELECT、UPDATE、INSERT，看看系统的提示有何不同。
grant select, update, insert on S to R1;

-- [3] 将这个角色授予U1,U3,U7。使他们具有角色R1所包含的全部权限。
grant R1 to U1, U3, U7;
show grants for U1;

-- [4] 对角色R1的权限进行修改，增加对S表的DELETE权限，并回收对S表的INSERT权限。
grant delete on S to R1;
revoke insert on S from R1;

-- [5] 删除角色R1。
drop role R1;

-- 2.3 触发器
-- a) 创建一个作用在P表上的触发器P_Ins，确保用户在插入或更新数据时所提供的WEIGHT值是非负和非零的，
-- 否则给出错误提示并回滚此操作。请测试该触发器。测试方法自定。
DELIMITER $$
create trigger P_Ins before insert
on P for each row 
if NEW.WEIGHT<=0 then 
    signal sqlstate '45001' set message_text = 'WEIGHT must be positive';
end if$$
create trigger P_Upd before update
on P for each row 
if NEW.WEIGHT<=0 then 
    signal sqlstate '45001' set message_text = 'WEIGHT must be positive';
end if$$
DELIMITER ;
    /* test Statements */
insert into P values ('P7', 'Name', 'clr', 0);
update P Set WEIGHT=0 where PNO = 'P1';

-- b) 利用触发器为供应情况表SPJ定义完整性规则“供应量不得低于100，如果低于100，自动改为100”。
DELIMITER $$
create trigger qty_check
    before insert
    -- before update
    on SPJ 
for each row 
if NEW.qty<100 then 
    set NEW.qty = 100;
end if$$
DELIMITER ;
insert into SPJ values ('S1', 'P1', 'J1', 1);

-- c) 查看P表上的触发器。
select trigger_name from information_schema.triggers where event_object_table = 'P';

-- d) 删除以上建的触发器。
drop trigger P_Ins;
drop trigger P_Upd;
drop trigger qty_check;

-- 考核内容
-- 1、创建U8，赋予U8在P表上的SELECT权限
create user U8;
grant select on db_SPJ.P to U8;

-- 2、创建U9，赋予U9在SPJ表上qty的UPDATE权限
create user U9;
grant update(qty) on db_SPJ.SPJ to U9;

-- 3、回收U9的所有权限
revoke all privileges on *.* from U9;

-- 4、创建角色R2，使之拥有P表上的的SELECT和INSERT
create role R2;
grant select, insert on db_SPJ.P to R2;

-- 5、将R2授予U3和U8，使他们具有角色R2所包含的全部权限
create user U3;
grant R2 to U3, U8;

-- 6、增加R2对P表的DELETE权限，并验证U8是否具有了这个权限？
grant delete on db_SPJ.P to R2;
    /* relogin as U8 */
set role all;
select current_role();
delete from db_SPJ.P where PNO = "P1";

-- 7、创建一个作用在SPJ表上的触发器，确保无论在什么时候，qty均应大于零，否则给出错误提示并回滚此操作。请测试该触发器
DELIMITER $$
create trigger qty_check
    before insert
    -- before update
    on SPJ 
for each row 
if NEW.qty<=0 then 
    signal sqlstate '45001' set message_text = 'QTY must be positive';
end if$$
DELIMITER ;
    /* test Statements */
insert into SPJ values ('S1', 'P1', 'J1', 0);
update SPJ Set QTY=0 where SNO = 'S1';

-- 8、查看SPJ上的触发器
show triggers;

-- 9、删除SPJ上的触发器
drop trigger qty_check;

-- clean
drop user if exists U1;
drop user if exists U2;
drop user if exists U3;
drop user if exists U4;
drop user if exists U5;
drop user if exists U6;
drop user if exists U7;
drop user if exists U8;
drop user if exists U9;
drop role if exists R1;
drop role if exists R2;
