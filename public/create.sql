-- script
CREATE TABLE script (
   name varchar(100) PRIMARY KEY,
   hostname varchar(300) NOT NULL UNIQUE
);
INSERT INTO script values ('danjuan', 'danjuanapp.com');
INSERT INTO script values ('qieman', 'qieman.com');
-- url
CREATE TABLE url (
    url varchar(300) PRIMARY KEY,
    name varchar(100) NOT NULL references script(name) on delete cascade on update cascade,
    tag varchar(100) NOT NULL 
);
INSERT INTO url values ('https://danjuanapp.com/strategy/CSI1033','danjuan','CSI1033');
INSERT INTO url values ('https://danjuanapp.com/strategy/CSI1032','danjuan','CSI1032');
INSERT INTO url values ('https://danjuanapp.com/strategy/CSI1038','danjuan','CSI1038');
INSERT INTO url values ('https://danjuanapp.com/strategy/CSI1029','danjuan','CSI1029');
INSERT INTO url values ('https://danjuanapp.com/strategy/CSI1006','danjuan','CSI1006');
INSERT INTO url values ('https://danjuanapp.com/strategy/CSI1065','danjuan','CSI1065');
INSERT INTO url values ('https://qieman.com/portfolios/ZH001798','qieman','ZH001798');
INSERT INTO url values ('https://qieman.com/portfolios/ZH012926','qieman','ZH012926');
INSERT INTO url values ('https://qieman.com/portfolios/ZH039471','qieman','ZH039471');
INSERT INTO url values ('https://qieman.com/portfolios/ZH010246','qieman','ZH010246');
INSERT INTO url values ('https://qieman.com/portfolios/ZH006498','qieman','ZH006498');
INSERT INTO url values ('https://qieman.com/portfolios/ZH000193','qieman','ZH000193');
INSERT INTO url values ('https://qieman.com/portfolios/ZH009664','qieman','ZH009664');
INSERT INTO url values ('https://qieman.com/portfolios/ZH030684','qieman','ZH030684');
INSERT INTO url values ('https://qieman.com/portfolios/ZH017252','qieman','ZH017252');
INSERT INTO url values ('https://qieman.com/portfolios/ZH007973','qieman','ZH007973');
INSERT INTO url values ('https://qieman.com/portfolios/ZH037807','qieman','ZH037807');
INSERT INTO url values ('https://qieman.com/portfolios/ZH007974','qieman','ZH007974');
INSERT INTO url values ('https://qieman.com/portfolios/ZH017409','qieman','ZH017409');
INSERT INTO url values ('https://qieman.com/portfolios/ZH035411','qieman','ZH035411');
INSERT INTO url values ('https://qieman.com/portfolios/ZH043108','qieman','ZH043108');
INSERT INTO url values ('https://qieman.com/portfolios/ZH043126','qieman','ZH043126');
-- fund
CREATE TABLE fund (
    url varchar(300) references url(url) on delete cascade on update cascade,
    date BIGINT NOT NULL,
    value DOUBLE
);