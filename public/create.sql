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
    last_update BIGINT NOT NULL DEFAULT 0
);
INSERT INTO url (url, name) values ('https://danjuanapp.com/strategy/CSI1033','danjuan');
INSERT INTO url (url, name) values ('https://danjuanapp.com/strategy/CSI1032','danjuan');
INSERT INTO url (url, name) values ('https://danjuanapp.com/strategy/CSI1038','danjuan');
INSERT INTO url (url, name) values ('https://danjuanapp.com/strategy/CSI1029','danjuan');
INSERT INTO url (url, name) values ('https://danjuanapp.com/strategy/CSI1006','danjuan');
INSERT INTO url (url, name) values ('https://danjuanapp.com/strategy/CSI1065','danjuan');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH001798','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH012926','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH039471','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH010246','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH006498','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH000193','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH009664','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH030684','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH017252','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH007973','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH037807','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH007974','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH017409','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH035411','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH043108','qieman');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH043126','qieman');
-- fund
CREATE TABLE fund (
    url varchar(300) references url(url) on delete cascade on update cascade,
    date BIGINT NOT NULL,
    value DOUBLE NOT NULL
);