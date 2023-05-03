-- MySQL Script generated by MySQL Workbench
-- Wed Nov 16 18:00:15 2022
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema group_2
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema group_2
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `group_2` DEFAULT CHARACTER SET utf8mb3 ;
USE `group_2` ;

-- -----------------------------------------------------
-- Table `group_2`.`owner`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `group_2`.`owner` (
  `id_owner` INT NOT NULL AUTO_INCREMENT,
  `fname` VARCHAR(50) NULL DEFAULT NULL,
  `lname` VARCHAR(50) NULL DEFAULT NULL,
  `address` VARCHAR(50) NULL DEFAULT NULL,
  `phonenumber` VARCHAR(50) NULL DEFAULT NULL,
  `email` VARCHAR(50) NULL DEFAULT NULL,
  PRIMARY KEY (`id_owner`))
ENGINE = InnoDB
AUTO_INCREMENT = 10
DEFAULT CHARACTER SET = utf8mb3;


-- -----------------------------------------------------
-- Table `group_2`.`card`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `group_2`.`card` (
  `id_card` INT NOT NULL AUTO_INCREMENT,
  `cardnumber` VARCHAR(16) NOT NULL,
  `password` VARCHAR(255) NOT NULL,
  `credit` INT NULL DEFAULT NULL,
  `id_owner` INT NULL DEFAULT NULL,
  PRIMARY KEY (`id_card`),
  INDEX `owner_card_idx` (`id_owner` ASC) VISIBLE,
  CONSTRAINT `owner_card`
    FOREIGN KEY (`id_owner`)
    REFERENCES `group_2`.`owner` (`id_owner`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE)
ENGINE = InnoDB
AUTO_INCREMENT = 15
DEFAULT CHARACTER SET = utf8mb3;


-- -----------------------------------------------------
-- Table `group_2`.`account`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `group_2`.`account` (
  `id_account` INT NOT NULL AUTO_INCREMENT,
  `account_balance` INT NULL DEFAULT NULL,
  `credit_balance` INT NULL DEFAULT NULL,
  `id_card` INT NULL DEFAULT NULL,
  `creditlimit` INT NULL DEFAULT NULL,
  `savingsmode` INT NULL DEFAULT '0',
  PRIMARY KEY (`id_account`),
  INDEX `user_card_idx` (`id_card` ASC) VISIBLE,
  CONSTRAINT `account_card`
    FOREIGN KEY (`id_card`)
    REFERENCES `group_2`.`card` (`id_card`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE)
ENGINE = InnoDB
AUTO_INCREMENT = 30
DEFAULT CHARACTER SET = utf8mb3;


-- -----------------------------------------------------
-- Table `group_2`.`logs`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `group_2`.`logs` (
  `id_logs` INT NOT NULL AUTO_INCREMENT,
  `id_account` INT NULL DEFAULT NULL,
  `log` VARCHAR(45) NULL DEFAULT NULL,
  `log_time` TIMESTAMP NULL DEFAULT NULL,
  `amount` INT NULL DEFAULT NULL,
  PRIMARY KEY (`id_logs`),
  INDEX `account_logs_idx` (`id_account` ASC) VISIBLE,
  CONSTRAINT `account_logs`
    FOREIGN KEY (`id_account`)
    REFERENCES `group_2`.`account` (`id_account`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE)
ENGINE = InnoDB
AUTO_INCREMENT = 26
DEFAULT CHARACTER SET = utf8mb3;

USE `group_2` ;

-- -----------------------------------------------------
-- procedure credit_withdraw
-- -----------------------------------------------------

DELIMITER $$
USE `group_2`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `credit_withdraw`(in idcard INT, in amount INT)
BEGIN
Declare creditcheck INT DEFAULT 0;
start transaction;
UPDATE account SET credit_balance = credit_balance-amount WHERE id_card=idcard AND credit_balance-amount>=0;
Set creditcheck = row_count();
if (creditcheck > 0) THEN
commit;
INSERT INTO logs (id_account,log,log_time,amount) VALUES ((select id_account FROM account where id_card = idcard),"Credit withdraw",NOW(),amount);
ELSE ROLLBACK;
END IF;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure debit_withdraw
-- -----------------------------------------------------

DELIMITER $$
USE `group_2`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `debit_withdraw`(in cardid INT, in summa INT)
BEGIN
Declare balancetest INT DEFAULT 0;
declare savings INT default 0;
START TRANSACTION;
UPDATE account SET account_balance = account_balance-summa WHERE id_card=cardid AND account_balance-summa>=0;
SET balancetest=row_count();
IF (balancetest>0) THEN 
COMMIT;
INSERT INTO logs (id_account,log,log_time,amount) VALUES ((select id_account FROM account where id_card = cardid),"Debit withdraw",NOW(),summa);
END IF;
IF ((select savingsmode from account where id_account=(select id_account from account where id_card = cardid))>0) AND (balancetest>0) THEN
set savings =(summa/100)*(select savingsmode from account where id_card=cardid);
Update account set account_balance = account_balance-savings where id_card=cardid;
Insert into logs (id_account,log,log_time,amount) VALUES ((select id_account from account where id_card = cardid),"Savingmode on, sent to designated savings acc",NOW(),savings);
ELSE ROLLBACK;
END IF;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure deposit
-- -----------------------------------------------------

DELIMITER $$
USE `group_2`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `deposit`(in cardid INT, in amount INT)
BEGIN
UPDATE account SET account_balance = account_balance+amount where id_card=cardid;
INSERT INTO logs (id_account,log,log_time,amount) VALUES ((select id_account FROM account where id_card = cardid),"Debit deposit",NOW(),amount);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure get_balance
-- -----------------------------------------------------

DELIMITER $$
USE `group_2`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `get_balance`(in idcard INT)
BEGIN
IF ((select creditlimit from account where id_card = idcard) > 0) THEN
SELECT account_balance, credit_balance from account where id_card = idcard;
ELSE 
select account_balance from account where id_card = idcard;
END IF;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure get_logs
-- -----------------------------------------------------

DELIMITER $$
USE `group_2`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `get_logs`(in idcard INT)
BEGIN
SELECT * from logs where id_account =(select id_account from account where id_card = idcard);
end$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure make_card_account
-- -----------------------------------------------------

DELIMITER $$
USE `group_2`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `make_card_account`(in idcard INT)
BEGIN
IF EXISTS(select * from card where id_card = idcard) THEN
INSERT INTO account (account_balance, id_card, creditlimit,credit_balance) VALUES (0,idcard,(select credit from card where id_card = idcard),(select credit from card where id_card = idcard));
END IF;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure new_card
-- -----------------------------------------------------

DELIMITER $$
USE `group_2`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `new_card`(IN ownerid INT, IN cardnum VARCHAR(50),
IN passu VARCHAR(50), IN cred INT)
BEGIN
IF EXISTS(select * from owner where id_owner = ownerid)  THEN
COMMIT;
INSERT INTO card (cardnumber,password,credit,id_owner) VALUES (cardnum,passu,cred,ownerid);
END IF;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure update_savingsmode
-- -----------------------------------------------------

DELIMITER $$
USE `group_2`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `update_savingsmode`(in idcard INT,in savings INT)
BEGIN
UPDATE account set savingsmode = savings where id_card = idcard;
Insert into logs (id_account,log,log_time,amount) VALUES ((select id_account from account where id_card = idcard),"Updated savingsmode",NOW(),0);
END$$

DELIMITER ;

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

-- Create a new user
INSERT INTO `group_2`.`owner` (`fname`, `lname`) VALUES ('Debit', 'Demo');
INSERT INTO `group_2`.`owner` (`fname`, `lname`) VALUES ('Crebit', 'Demo');

-- Call the `new_card` 
CALL `group_2`.`new_card`((SELECT `id_owner` FROM `group_2`.`owner` WHERE `fname` = 'Debit' AND `lname` = 'Demo'), '0000', '0000', 0);
CALL `group_2`.`new_card`((SELECT `id_owner` FROM `group_2`.`owner` WHERE `fname` = 'Crebit' AND `lname` = 'Demo'), '1111', '1111', 5000);

-- Call `make_card_account`
CALL `group_2`.`make_card_account`((SELECT `id_card` FROM `group_2`.`card` WHERE `id_owner` = (SELECT `id_owner` FROM `group_2`.`owner` WHERE `fname` = 'Debit' AND `lname` = 'Demo')));
CALL `group_2`.`make_card_account`((SELECT `id_card` FROM `group_2`.`card` WHERE `id_owner` = (SELECT `id_owner` FROM `group_2`.`owner` WHERE `fname` = 'Crebit' AND `lname` = 'Demo')));
