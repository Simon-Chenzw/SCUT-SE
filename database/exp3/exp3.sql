--  1	找出所有供应商的姓名和所在城市。
select SNAME, CITY from S;
--  2	找出所有零件的名称、颜色和重量。
select PNAME, COLOR, WEIGHT from P;
--  3	找出使用了供应商S1所供应的零件的工程号码。
select JNO from SPJ where SNO='S1';
--  4	找出工程J2使用的各种零件的名称和数量。
select PNAME, QTY 
from 
    SPJ natural join P
where JNO='J2';
--  5	找出上海供应商供应的所有零件的零件号码。
select distinct PNO 
from 
    SPJ 
    natural join S
where CITY='上海'; 
--  6	找出使用了上海供应商供应的零件的工程名称。
select distinct JNAME 
from 
    SPJ 
    inner join S
        on SPJ.SNO=S.SNO
    inner join J
        on SPJ.JNO=J.JNO
where S.CITY='上海';
--  7	找出供应工程J1零件的供应商号SNO。
select distinct SNO from SPJ where JNO='J1';
--  8	找出供应工程J1零件P1的供应商号SNO。
select distinct SNO from SPJ where JNO='J1' and PNO='P1';
--  9	找出供应工程J1红色零件的供应商号SNO。
select distinct SNO
from 
    SPJ
    natural join P
where JNO='J1' and COLOR='红';
-- 10	找出没有使用天津供应商生产的红色零件的工程号JNO。
select JNO from J where JNO not in (
    select distinct JNO
    from 
        SPJ
        inner join S 
            on SPJ.SNO=S.SNO
        inner join P
            on SPJ.PNO=P.PNO
    where S.CITY='天津' and P.COLOR='红'
);
-- 11	求所有有关project 的信息。
select * from J;
-- 12	求在北京的所有project 的信息。
select * from J where CITY='北京';
-- 13	求为project（工程）J1 提供part（零件）的supplier（供应商）的号码。
select distinct SNO from SPJ where JNO='J1';
-- 14	求数量在300 到750 之间的发货。
select * from SPJ where QTY>=300 and QTY<=750;
-- 15	求所有的零件颜色 / 城市对。注意：这里及以后所说的“所有”特指在数据库中。
select distinct P.COLOR, S.CITY, J.CITY
from 
    SPJ
    inner join S 
        on SPJ.SNO=S.SNO
    inner join P
        on SPJ.PNO=P.PNO
    inner join J
        on SPJ.JNO=J.JNO
;
-- 16	求所有的supplier-number / part-number / project-number 对。其中所指的供应商和工程在同一个城市。
select distinct S.SNO, SPJ.PNO, J.JNO
from 
    SPJ
    inner join S 
        on SPJ.SNO=S.SNO
    inner join J
        on SPJ.JNO=J.JNO
where S.CITY=J.CITY;
-- 17	求所有的supplier-number / part-number / project-number 对。其中所指的供应商和工程不在同一个城市。
select distinct S.SNO, SPJ.PNO, J.JNO
from 
    SPJ
    inner join S 
        on SPJ.SNO=S.SNO
    inner join J
        on SPJ.JNO=J.JNO
where S.CITY!=J.CITY;
-- 18	求由北京供应商提供的零件的信息。
select distinct P.* 
from 
    SPJ 
    natural join S 
    natural join P
where S.CITY='北京';
-- 19	求由北京供应商为北京工程供应的零件号。
select distinct PNO
from 
    SPJ
    inner join S 
        on SPJ.SNO=S.SNO
    inner join J
        on SPJ.JNO=J.JNO
where S.CITY='北京' and J.CITY='北京';
-- 20	求满足下面要求的城市对，要求在第一个城市的供应商为第二个城市的工程供应零件。
select distinct S.CITY, J.CITY
from 
    SPJ
    inner join S 
        on SPJ.SNO=S.SNO
    inner join J
        on SPJ.JNO=J.JNO
;
-- 21	求供应商为工程供应的零件的号码，要求供应商和工程在同一城市。
select distinct PNO
from 
    SPJ
    inner join S 
        on SPJ.SNO=S.SNO
    inner join J
        on SPJ.JNO=J.JNO
where S.CITY=J.CITY;
-- 22	求至少被一个不在同一城市的供应商供应零件的工程号。
select distinct J.JNO
from 
    SPJ
    inner join S 
        on SPJ.SNO=S.SNO
    inner join J
        on SPJ.JNO=J.JNO
where S.CITY!=J.CITY;
-- 23	求由同一个供应商供应的零件号的对。
with SP as ( select distinct SNO, PNO from SPJ )
select distinct SP1.PNO, SP2.PNO
from
    SP SP1
    inner join SP SP2
    on SP1.SNO=SP2.SNO
where SP1.PNO<SP2.PNO;
-- 24	求所有由供应商S1 供应的工程号。
select distinct PNO from SPJ where SNO='S1';
-- 25	求供应商S1 供应的零件P1 的总量。
select sum(QTY) from SPJ where SNO='S1' and PNO='P1';
-- 26	对每个供应给工程的零件，求零件号、工程号和相应的总量。
select PNO, JNO, sum(QTY) from SPJ group by PNO, JNO;
-- 27	求为单个工程供应的零件数量超过350 的零件号。
select distinct PNO from SPJ where QTY>350;
-- 28	求由S1 供应的工程名称。
select distinct JNO from SPJ where SNO='S1';
-- 29	求由S1 供应的零件颜色。
select distinct COLOR
from
    SPJ natural join P
where SNO='S1';
-- 30	求供应给北京工程的零件号。
select distinct PNO
from 
    SPJ natural join J
where CITY='北京';
-- 31	求使用了S1 供应的零件的工程号。
select distinct JNO from SPJ where SNO='S1';
-- 32	求status 比S1 低的供应商号码。
select SNO from S where status<( select status from S where SNO='S1' );
-- 33	求所在城市按字母排序为第一的工程号。
select JNO from J order by CITY limit 1;
-- 34	求被供应零件P1 的平均数量大于供应给工程J1 的任意零件的最大数量的工程号。
select JNO from SPJ where PNO='P1' group by JNO having avg(QTY)>(
    select max(QTY) from SPJ where JNO='J1'
);
-- 35	求满足下面要求的供应商号码，该供应商供应给某个工程零件P1 的数量大于这个工程被供应的零件P1 的平均数量。
select SNO 
from 
    SPJ
    inner join ( 
            select JNO, avg(QTY) as aver from SPJ where PNO='p1' group by JNO 
        )as average
        on SPJ.PNO='P1' and SPJ.JNO=average.JNO
where QTY > aver;
-- 36	求没有被北京供应商供应过红色零件的工程号码。
select JNO from J where JNO not in (
    select distinct JNO
    from 
        SPJ
        inner join S 
            on SPJ.SNO=S.SNO
        inner join P
            on SPJ.PNO=P.PNO
    where S.CITY='北京' and P.COLOR='红'
);
-- 37	求所用零件全被S1 供应的工程号码。
select JNO from SPJ where JNO not in (
    select distinct JNO from SPJ where SNO!='S1'
);
-- 38	求所有北京工程都使用的零件号码。
select PNO from 
    SPJ natural join J 
where CITY='北京'
group by PNO 
having count(distinct JNO)=(
    select count(*) from J where CITY='北京'
);
-- 39	求对所有工程都提供了同一零件的供应商号码。
select SNO from SPJ group by SNO having count(distinct PNO)=1;
-- 40	求使用了S1 提供的所有零件的工程号码。
select JNO from SPJ where SNO='S1' group by JNO having count(distinct PNO)=(
    select count(distinct PNO) from SPJ where SNO='S1'
);
-- 41	求至少有一个供应商、零件或工程所在的城市。
select CITY from S union select CITY from J;
-- 42	求被北京供应商供应或被北京工程使用的零件号码。
select distinct PNO from 
    SPJ
    inner join S 
        on SPJ.SNO=S.SNO
    inner join J
        on SPJ.JNO=J.JNO
where S.CITY='北京' or J.CITY='北京';
-- 43	求所有supplier-number / part-number 对，其中指定的供应商不供应指定的零件。
select SNO, PNO from S,P where (SNO, PNO) not in (select distinct SNO, PNO from SPJ);
-- 44	向p表追加如下记录（P0,PN0,蓝）。
insert into P (PNO, PNAME, COLOR) values('P0', 'PN0', '蓝');
-- 45	把零件重量在15到20之间的零件信息追加到新的表p1中。
create table p1 select * from P where WEIGHT>=15 and WEIGHT<=20;
-- 46	向s表追加记录（s1, n2, ’上海’）能成功吗?为什么？
/* 不能，SNO是主键，有主键约束，不能重复。 */
-- 47	把s、p、j三个表中的s#,p#,j#列进行交叉联接，把结果追加到spj1表中（如果只考虑下面表格中的原始数据，应该在spj1表中追加多少条记录？你是如何计算记录条数的？）。
/* 5*6*7=210 */
create table spj1 select SNO, PNO, JNO from S, P, J;
-- 48	向spj表追加（s6,p1,j6,1000）本操作能正确执行吗？为什么？如果追加(s4,p1,j6,-10) 行吗？如果现在想强制追加这两条记录该怎么办？
/* 不能，SNO是外键并且S表没有SNO='S6'的值。 */
/* 可以，QTY没有施加CHECK约束。 */
SET FOREIGN_KEY_CHECKS=0;
insert into SPJ values('s6', 'p1', 'j6', 1000);
SET FOREIGN_KEY_CHECKS=1;
-- 49	把s1供应商供应的零件为p1的所有项目对应的数量qty改为500。
update SPJ set QTY=500 where SNO='S1' and PNO='P1';
-- 50	把qty值大于等于1000的所有供应商城市更改为‘北京’ 。
update S set CITY='北京' where SNO in (
    select SNO from SPJ where QTY>=1000
);
-- 51	把j1更改成j7，本操作能正确执行吗？为什么？如果改成j0呢？spj表中记录有何变化？为什么？
/* 不能，主键约束 */
/* 不能，SPJ表的外键约束 */
/* 无变化 */
-- 52	把零件重量低于15的增加3，高于15的增加2。
update P set weight=
case 
    when 
        weight>15 then weight+2
    when 
        weight<15 then weight+3 
    else 
        weight 
end;
-- 53	删除为j7工程供应零件的所有供应商信息（如果建立外键时没有带级联删除选项，本操作能正确执行吗？为什么？）
/* 建立外键时没有带级联删除选项，本操作不能正确执行 */
delete from S where SNO in (
    select distinct SNO from SPJ where JNO='J7'
);
-- 54	删除p1表中所有记录。
delete from p1;
-- 55	删除供应商和工程在同一个城市的供应商信息。
delete from S where SNO in (
    select SNO from (
        select distinct S.SNO from 
            SPJ
            inner join S 
                on S.SNO=SPJ.SNO
            inner join J
                on J.JNO=SPJ.JNO
        where S.CITY=J.CITY
    ) as a
);

-- b)	请为三建工程项目建立一个供应情况的视图，包括供应商代码（SNO）、零件代码（PNO）、供应数量（QTY）。针对该视图完成下列查询：
create view SanJian as (
    select SNO, PNO, QTY 
    from 
        SPJ 
        natural join J 
    where JNAME='三建'
);

-- 1 找出三建工程项目使用的各种零件代码及其数量；
select PNO, sum(QTY) 
from SanJian 
group by PNO 
order by PNO;

-- 2 找出供应商S1的供应情况；
select * from SanJian where SNO='S1';

-- 尝试更改该视图的每个字段，看看会发生什么？