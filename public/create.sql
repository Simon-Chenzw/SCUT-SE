-- website
CREATE TABLE website (
   name varchar(100) PRIMARY KEY,
   hostname varchar(300) NOT NULL UNIQUE
);
INSERT INTO website values ('danjuan', 'danjuanapp.com');
INSERT INTO website values ('qieman', 'qieman.com');
-- url
CREATE TABLE url (
    url varchar(300) PRIMARY KEY,
    hostname varchar(100) NOT NULL,
    last_update BIGINT NOT NULL DEFAULT 0
);
INSERT INTO url (url, name) values ('https://danjuanapp.com/strategy/CSI1033','danjuanapp.com');
INSERT INTO url (url, name) values ('https://danjuanapp.com/strategy/CSI1032','danjuanapp.com');
INSERT INTO url (url, name) values ('https://danjuanapp.com/strategy/CSI1038','danjuanapp.com');
INSERT INTO url (url, name) values ('https://danjuanapp.com/strategy/CSI1029','danjuanapp.com');
INSERT INTO url (url, name) values ('https://danjuanapp.com/strategy/CSI1006','danjuanapp.com');
INSERT INTO url (url, name) values ('https://danjuanapp.com/strategy/CSI1065','danjuanapp.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH001798','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH012926','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH039471','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH010246','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH006498','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH000193','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH009664','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH030684','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH017252','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH007973','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH037807','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH007974','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH017409','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH035411','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH043108','qieman.com');
INSERT INTO url (url, name) values ('https://qieman.com/portfolios/ZH043126','qieman.com');
-- fun
CREATE TABLE fund (
    url varchar(300) references url(url) on delete cascade on update cascade,
    date BIGINT NOT NULL,
    value DOUBLE NOT NULL
);