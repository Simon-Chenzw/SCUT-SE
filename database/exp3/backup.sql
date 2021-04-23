-- MySQL dump 10.13  Distrib 8.0.23, for Linux (x86_64)
--
-- Host: localhost    Database: db_SPJ
-- ------------------------------------------------------
-- Server version	8.0.23

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `db_SPJ`
--

DROP DATABASE IF EXISTS `db_SPJ`;

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `db_SPJ` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;

USE `db_SPJ`;

--
-- Table structure for table `J`
--

DROP TABLE IF EXISTS `J`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `J` (
  `JNO` char(10) NOT NULL,
  `JNAME` char(10) DEFAULT '工厂',
  `CITY` char(10) DEFAULT NULL,
  PRIMARY KEY (`JNO`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `J`
--

LOCK TABLES `J` WRITE;
/*!40000 ALTER TABLE `J` DISABLE KEYS */;
INSERT INTO `J` VALUES ('J1','三建','北京'),('J2','一汽','长春'),('J3','弹簧厂','天津'),('J4','造船厂','天津'),('J5','机车厂','唐山'),('J6','无线电厂','常州'),('J7','半导体厂','南京');
/*!40000 ALTER TABLE `J` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `P`
--

DROP TABLE IF EXISTS `P`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `P` (
  `PNO` char(10) NOT NULL,
  `PNAME` char(10) DEFAULT NULL,
  `COLOR` char(10) DEFAULT NULL,
  `WEIGHT` int DEFAULT NULL,
  PRIMARY KEY (`PNO`),
  CONSTRAINT `P_chk_1` CHECK ((`WEIGHT` > 0))
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P`
--

LOCK TABLES `P` WRITE;
/*!40000 ALTER TABLE `P` DISABLE KEYS */;
INSERT INTO `P` VALUES ('P1','螺母','红',12),('P2','螺栓','绿',17),('P3','螺丝刀','蓝',14),('P4','螺丝刀','红',14),('P5','凸轮','蓝',40),('P6','齿轮','红',30);
/*!40000 ALTER TABLE `P` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `S`
--

DROP TABLE IF EXISTS `S`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `S` (
  `SNO` char(10) NOT NULL,
  `SNAME` char(10) DEFAULT NULL,
  `STATUS` int DEFAULT NULL,
  `CITY` char(10) DEFAULT NULL,
  PRIMARY KEY (`SNO`),
  UNIQUE KEY `SNAME` (`SNAME`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `S`
--

LOCK TABLES `S` WRITE;
/*!40000 ALTER TABLE `S` DISABLE KEYS */;
INSERT INTO `S` VALUES ('S1','精益',20,'天津'),('S2','盛锡',10,'北京'),('S3','东方红',30,'北京'),('S4','丰泰',20,'天津'),('S5','为民',30,'上海');
/*!40000 ALTER TABLE `S` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SPJ`
--

DROP TABLE IF EXISTS `SPJ`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `SPJ` (
  `SNO` char(10) NOT NULL DEFAULT 'S1',
  `PNO` char(10) NOT NULL DEFAULT 'P1',
  `JNO` char(10) NOT NULL DEFAULT 'J1',
  `QTY` int DEFAULT NULL,
  PRIMARY KEY (`SNO`,`PNO`,`JNO`),
  KEY `PNO` (`PNO`),
  KEY `JNO` (`JNO`),
  CONSTRAINT `SPJ_ibfk_1` FOREIGN KEY (`SNO`) REFERENCES `S` (`SNO`) on delete Cascade,
  CONSTRAINT `SPJ_ibfk_2` FOREIGN KEY (`PNO`) REFERENCES `P` (`PNO`) on delete Cascade,
  CONSTRAINT `SPJ_ibfk_3` FOREIGN KEY (`JNO`) REFERENCES `J` (`JNO`) on delete Cascade
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `SPJ`
--

LOCK TABLES `SPJ` WRITE;
/*!40000 ALTER TABLE `SPJ` DISABLE KEYS */;
INSERT INTO `SPJ` VALUES ('S1','P1','J1',200),('S1','P1','J3',100),('S1','P1','J4',700),('S1','P2','J2',100),('S2','P3','J1',400),('S2','P3','J2',200),('S2','P3','J4',500),('S2','P3','J5',400),('S2','P5','J1',400),('S2','P5','J2',100),('S3','P1','J1',200),('S3','P3','J1',200),('S4','P5','J1',100),('S4','P6','J1',100),('S4','P6','J4',200),('S5','P2','J4',100),('S5','P3','J1',200),('S5','P6','J2',200),('S5','P6','J4',500);
/*!40000 ALTER TABLE `SPJ` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-04-17 21:34:55
