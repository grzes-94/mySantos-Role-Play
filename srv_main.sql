-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Czas generowania: 14 Kwi 2017, 13:14
-- Wersja serwera: 5.5.54-0+deb8u1
-- Wersja PHP: 5.6.30-0+deb8u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Baza danych: `srv_main`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `panel_admins_online`
--

CREATE TABLE IF NOT EXISTS `panel_admins_online` (
`id` mediumint(8) unsigned NOT NULL,
  `player_uid` mediumint(9) NOT NULL,
  `global_id` mediumint(9) NOT NULL,
  `online` mediumint(8) unsigned NOT NULL,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB AUTO_INCREMENT=596 DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `panel_admin_log`
--

CREATE TABLE IF NOT EXISTS `panel_admin_log` (
`uid` int(11) NOT NULL,
  `owner` int(11) NOT NULL,
  `log` text NOT NULL,
  `date` int(11) NOT NULL,
  `char` int(11) NOT NULL
) ENGINE=MyISAM AUTO_INCREMENT=2633 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `panel_panel_log`
--

CREATE TABLE IF NOT EXISTS `panel_panel_log` (
`uid` int(11) NOT NULL,
  `owner` int(11) NOT NULL,
  `log` text NOT NULL,
  `date` int(11) NOT NULL,
  `char` int(11) NOT NULL
) ENGINE=MyISAM AUTO_INCREMENT=25 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `panel_premium_codes`
--

CREATE TABLE IF NOT EXISTS `panel_premium_codes` (
`code_uid` mediumint(8) unsigned NOT NULL,
  `code` varchar(12) CHARACTER SET latin1 NOT NULL,
  `days` tinyint(3) unsigned NOT NULL,
  `created_by` smallint(5) unsigned NOT NULL,
  `used_by` smallint(5) unsigned NOT NULL,
  `activation_time` int(10) unsigned NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=143 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `panel_premium_logs`
--

CREATE TABLE IF NOT EXISTS `panel_premium_logs` (
`code_uid` int(11) NOT NULL,
  `code_title` varchar(10) NOT NULL,
  `code_owner` int(11) NOT NULL,
  `code_date` int(11) NOT NULL,
  `typ` int(3) NOT NULL DEFAULT '0'
) ENGINE=MyISAM AUTO_INCREMENT=451 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_3dtext`
--

CREATE TABLE IF NOT EXISTS `srv_3dtext` (
  `uid` tinyint(3) unsigned NOT NULL,
  `text` tinytext CHARACTER SET latin1 NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `interior` tinyint(4) NOT NULL,
  `vw` smallint(6) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_anims`
--

CREATE TABLE IF NOT EXISTS `srv_anims` (
`uid` smallint(5) unsigned NOT NULL,
  `cmd` varchar(12) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `lib` varchar(16) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `name` varchar(24) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `speed` float NOT NULL,
  `loop/sa` tinyint(4) NOT NULL,
  `lockx` tinyint(4) NOT NULL,
  `locky` tinyint(4) NOT NULL,
  `freeze` tinyint(4) NOT NULL,
  `time` smallint(4) NOT NULL,
  `action` tinyint(3) unsigned NOT NULL DEFAULT '1'
) ENGINE=InnoDB AUTO_INCREMENT=169 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_attached`
--

CREATE TABLE IF NOT EXISTS `srv_attached` (
  `UID` int(10) unsigned NOT NULL,
  `ind` tinyint(3) unsigned NOT NULL,
  `model` mediumint(8) unsigned NOT NULL,
  `bone` tinyint(3) unsigned NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `rx` float NOT NULL,
  `ry` float NOT NULL,
  `rz` float NOT NULL,
  `sx` float NOT NULL,
  `sy` float NOT NULL,
  `sz` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_bans`
--

CREATE TABLE IF NOT EXISTS `srv_bans` (
`ban_id` int(11) NOT NULL,
  `ip` varchar(32) NOT NULL,
  `player_global_id` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=587 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_bus`
--

CREATE TABLE IF NOT EXISTS `srv_bus` (
  `uid` int(11) NOT NULL,
  `name` varchar(32) CHARACTER SET latin1 NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `angle` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_cash_logs`
--

CREATE TABLE IF NOT EXISTS `srv_cash_logs` (
  `from_uid` int(11) NOT NULL,
  `from_gid` int(11) NOT NULL,
  `to_uid` int(11) NOT NULL,
  `to_gid` int(11) NOT NULL,
  `value` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_characters`
--

CREATE TABLE IF NOT EXISTS `srv_characters` (
`player_uid` int(11) NOT NULL,
  `global_id` int(11) NOT NULL,
  `nickname` varchar(32) NOT NULL,
  `age` int(11) NOT NULL,
  `sex` int(11) NOT NULL,
  `skin` int(11) NOT NULL,
  `cash` int(11) NOT NULL DEFAULT '3000',
  `hours` int(11) NOT NULL,
  `minutes` int(11) NOT NULL,
  `hp` float NOT NULL DEFAULT '100',
  `admin` int(11) NOT NULL,
  `hide` int(11) NOT NULL,
  `credit` int(11) NOT NULL,
  `bw` int(11) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `vw` int(11) NOT NULL,
  `interior` int(11) NOT NULL,
  `tog` int(11) NOT NULL,
  `block` int(11) NOT NULL DEFAULT '0',
  `glod` int(11) NOT NULL DEFAULT '100',
  `spawnopt` int(11) NOT NULL,
  `spawnhouseopt` int(11) NOT NULL,
  `nogun` int(11) NOT NULL,
  `nocar` int(11) NOT NULL,
  `noooc` int(11) NOT NULL,
  `norun` int(11) NOT NULL,
  `jail` int(11) NOT NULL,
  `jail_time` int(11) NOT NULL,
  `logged` int(11) NOT NULL,
  `last_online` int(11) NOT NULL,
  `online_today` int(11) NOT NULL,
  `job` int(11) NOT NULL,
  `job_count` int(11) NOT NULL,
  `docs` int(11) NOT NULL,
  `phone_uid` int(11) NOT NULL,
  `radio_channel` int(11) NOT NULL,
  `hotel` int(11) NOT NULL,
  `penaltypoints` int(11) NOT NULL,
  `strength` int(11) NOT NULL,
  `strength_today` int(11) NOT NULL,
  `driverpenalty` int(11) NOT NULL,
  `celebrity` int(11) NOT NULL,
  `fightstyle` int(11) NOT NULL,
  `suplement` int(11) NOT NULL,
  `lastdmg` float NOT NULL,
  `lasthb` int(11) NOT NULL,
  `lastweap` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=4400 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_christmasshop`
--

CREATE TABLE IF NOT EXISTS `srv_christmasshop` (
`uid` tinyint(4) NOT NULL,
  `name` varchar(32) NOT NULL,
  `type` tinyint(4) NOT NULL,
  `value1` int(11) NOT NULL,
  `value2` int(11) NOT NULL,
  `price` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_corners`
--

CREATE TABLE IF NOT EXISTS `srv_corners` (
  `uid` int(11) NOT NULL,
  `name` varchar(32) CHARACTER SET latin1 NOT NULL,
  `owner` int(11) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_corpse`
--

CREATE TABLE IF NOT EXISTS `srv_corpse` (
`uid` int(11) NOT NULL,
  `player_uid` int(11) NOT NULL,
  `player_name` varchar(128) NOT NULL,
  `reason` varchar(256) NOT NULL,
  `gun` varchar(32) NOT NULL,
  `gun_val` int(11) NOT NULL,
  `date` varchar(16) NOT NULL,
  `money` int(6) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `int` int(11) NOT NULL,
  `vw` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=383 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_descriptions`
--

CREATE TABLE IF NOT EXISTS `srv_descriptions` (
  `UID` int(11) NOT NULL,
  `owneruid` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_descriptions_text`
--

CREATE TABLE IF NOT EXISTS `srv_descriptions_text` (
  `UID` int(11) NOT NULL,
  `text` varchar(128) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_doors`
--

CREATE TABLE IF NOT EXISTS `srv_doors` (
  `UID` int(11) NOT NULL,
  `name` varchar(32) NOT NULL,
  `ownertyp` int(11) NOT NULL,
  `owner` int(11) NOT NULL,
  `enterx` float NOT NULL,
  `entery` float NOT NULL,
  `enterz` float NOT NULL,
  `enterangle` int(11) NOT NULL,
  `enterint` int(11) NOT NULL,
  `entervw` int(11) NOT NULL,
  `exitx` float NOT NULL,
  `exity` float NOT NULL,
  `exitz` float NOT NULL,
  `exitangle` int(11) NOT NULL,
  `exitint` int(11) NOT NULL,
  `exitvw` int(11) NOT NULL,
  `lock` int(11) NOT NULL,
  `pickupid` int(11) NOT NULL,
  `garage` int(11) NOT NULL,
  `radio_url` varchar(128) NOT NULL,
  `icon_id` int(11) NOT NULL,
  `priceforentry` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `weather` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_doors_members`
--

CREATE TABLE IF NOT EXISTS `srv_doors_members` (
  `UID` int(11) NOT NULL,
  `player_uid` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_falied_logins`
--

CREATE TABLE IF NOT EXISTS `srv_falied_logins` (
`uid` int(11) NOT NULL,
  `player_uid` mediumint(9) NOT NULL,
  `player_gid` mediumint(9) NOT NULL,
  `ip` varchar(64) NOT NULL,
  `time` int(11) NOT NULL,
  `reason` varchar(32) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=287 DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_fuel_orders`
--

CREATE TABLE IF NOT EXISTS `srv_fuel_orders` (
`uid` int(11) NOT NULL,
  `station_id` int(11) NOT NULL,
  `value` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `driver` int(11) NOT NULL,
  `status` tinyint(1) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=228 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_fuel_stations`
--

CREATE TABLE IF NOT EXISTS `srv_fuel_stations` (
  `uid` int(11) NOT NULL,
  `owner` int(11) NOT NULL,
  `fuel` int(11) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `fuelcost` int(11) NOT NULL DEFAULT '8'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_groups`
--

CREATE TABLE IF NOT EXISTS `srv_groups` (
  `UID` int(11) NOT NULL,
  `name` varchar(32) NOT NULL,
  `tag` varchar(32) NOT NULL,
  `type` int(11) NOT NULL,
  `cash` int(11) NOT NULL,
  `flags` int(11) NOT NULL,
  `leader` int(11) NOT NULL,
  `spawn_x` float NOT NULL,
  `spawn_y` float NOT NULL,
  `spawn_z` float NOT NULL,
  `spawn_angle` float NOT NULL,
  `spawn_int` int(11) NOT NULL,
  `spawn_vw` int(11) NOT NULL,
  `color` int(11) NOT NULL DEFAULT '-1',
  `notice` varchar(64) NOT NULL,
  `registered` int(11) NOT NULL,
  `grant` int(11) NOT NULL,
  `salary_account` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_groups_members`
--

CREATE TABLE IF NOT EXISTS `srv_groups_members` (
`id` int(11) NOT NULL,
  `group_uid` int(11) NOT NULL,
  `player_uid` int(11) NOT NULL,
  `rank_name` varchar(32) NOT NULL,
  `rank` int(11) NOT NULL,
  `permission` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `skin` int(11) NOT NULL,
  `salary` int(11) NOT NULL,
  `payment` int(11) NOT NULL,
  `commission` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=6718 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_group_offer_logs`
--

CREATE TABLE IF NOT EXISTS `srv_group_offer_logs` (
`id` int(11) NOT NULL,
  `groupid` int(11) NOT NULL,
  `player_uid` int(11) NOT NULL,
  `player_gid` int(11) NOT NULL,
  `customer_uid` int(11) NOT NULL,
  `type` varchar(32) CHARACTER SET latin1 NOT NULL,
  `cash` int(11) NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=45418 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_group_offer_prices`
--

CREATE TABLE IF NOT EXISTS `srv_group_offer_prices` (
  `groupid` int(11) NOT NULL,
  `price1` int(11) NOT NULL,
  `price2` int(11) NOT NULL,
  `price3` int(11) NOT NULL,
  `price4` int(11) NOT NULL,
  `price5` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_gym_pass`
--

CREATE TABLE IF NOT EXISTS `srv_gym_pass` (
`id` int(11) NOT NULL,
  `player_uid` int(11) NOT NULL,
  `groupid` int(11) NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=870 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_hotel`
--

CREATE TABLE IF NOT EXISTS `srv_hotel` (
`uid` int(11) NOT NULL,
  `player_uid` int(11) NOT NULL,
  `hotel_id` int(11) NOT NULL,
  `locked` int(11) NOT NULL,
  `expire` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_items`
--

CREATE TABLE IF NOT EXISTS `srv_items` (
  `UID` int(11) NOT NULL,
  `name` varchar(32) NOT NULL,
  `type` int(11) NOT NULL,
  `value1` int(11) NOT NULL,
  `value2` int(11) NOT NULL,
  `used` int(11) NOT NULL,
  `ownertyp` int(11) NOT NULL,
  `owner` int(11) NOT NULL,
  `ilosc` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `posx` float NOT NULL,
  `posy` float NOT NULL,
  `posz` float NOT NULL,
  `world` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_items_logs`
--

CREATE TABLE IF NOT EXISTS `srv_items_logs` (
`id` int(11) NOT NULL,
  `from_uid` mediumint(8) unsigned NOT NULL,
  `from_gid` mediumint(8) unsigned NOT NULL,
  `to_uid` mediumint(8) unsigned NOT NULL,
  `to_gid` mediumint(8) unsigned NOT NULL,
  `itemid` mediumint(8) unsigned NOT NULL,
  `price` int(10) unsigned NOT NULL,
  `time` int(10) unsigned NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=6623 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_jail_logs`
--

CREATE TABLE IF NOT EXISTS `srv_jail_logs` (
`logid` mediumint(8) unsigned NOT NULL,
  `to_uid` mediumint(8) unsigned NOT NULL,
  `to_gid` mediumint(8) unsigned NOT NULL,
  `from_uid` mediumint(8) unsigned NOT NULL,
  `from_gid` mediumint(8) unsigned NOT NULL,
  `groupid` tinyint(3) unsigned NOT NULL,
  `value` smallint(5) unsigned NOT NULL,
  `type` tinyint(4) NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=1013 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_kartoteki`
--

CREATE TABLE IF NOT EXISTS `srv_kartoteki` (
`uid` int(11) NOT NULL,
  `player_uid` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=407 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_kartoteki_records`
--

CREATE TABLE IF NOT EXISTS `srv_kartoteki_records` (
`ID` int(11) NOT NULL,
  `UID` int(11) NOT NULL,
  `date` varchar(16) NOT NULL,
  `record` varchar(32) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=740 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_legal_weapons`
--

CREATE TABLE IF NOT EXISTS `srv_legal_weapons` (
  `weapuid` int(11) NOT NULL,
  `player_uid` mediumint(8) unsigned NOT NULL,
  `player_gid` mediumint(8) unsigned NOT NULL,
  `seller_uid` mediumint(8) unsigned NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_login_logs`
--

CREATE TABLE IF NOT EXISTS `srv_login_logs` (
  `gid` int(11) NOT NULL,
  `character_id` int(11) NOT NULL,
  `ip` varchar(16) CHARACTER SET latin1 NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_mmat_text`
--

CREATE TABLE IF NOT EXISTS `srv_mmat_text` (
  `object_id` int(11) NOT NULL,
  `index` int(11) NOT NULL,
  `matsize` int(11) NOT NULL,
  `fontsize` int(11) NOT NULL,
  `bold` int(11) NOT NULL,
  `fontcolor` text NOT NULL,
  `backcolor` text NOT NULL,
  `align` text NOT NULL,
  `fontface` text NOT NULL,
  `text` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_mmat_texture`
--

CREATE TABLE IF NOT EXISTS `srv_mmat_texture` (
  `object_id` int(11) NOT NULL,
  `index` int(11) NOT NULL,
  `materialcolor` text NOT NULL,
  `modelid` int(11) NOT NULL,
  `txdname` text NOT NULL,
  `texturename` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_mostwanted`
--

CREATE TABLE IF NOT EXISTS `srv_mostwanted` (
`ID` int(11) NOT NULL,
  `player_uid` int(11) NOT NULL,
  `reason` varchar(32) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=81 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_objects`
--

CREATE TABLE IF NOT EXISTS `srv_objects` (
  `uid` int(11) NOT NULL,
  `model` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `rx` float NOT NULL,
  `ry` float NOT NULL,
  `rz` float NOT NULL,
  `vw` int(11) NOT NULL,
  `int` int(11) NOT NULL,
  `owner` int(11) NOT NULL,
  `ownertype` int(11) NOT NULL,
  `gate` int(11) NOT NULL,
  `gate_x` float NOT NULL,
  `gate_y` float NOT NULL,
  `gate_z` float NOT NULL,
  `gate_rx` float NOT NULL,
  `gate_ry` float NOT NULL,
  `gate_rz` float NOT NULL,
  `mmat` int(11) NOT NULL,
  `creator_uid` int(11) NOT NULL,
  `lastedit_uid` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_orders`
--

CREATE TABLE IF NOT EXISTS `srv_orders` (
`uid` int(11) NOT NULL,
  `door_uid` int(11) NOT NULL,
  `value1` int(11) NOT NULL,
  `value2` int(11) NOT NULL,
  `kind` int(11) NOT NULL,
  `count` int(11) NOT NULL,
  `name` varchar(64) NOT NULL,
  `shippment_cost` int(11) NOT NULL,
  `driver` int(11) NOT NULL,
  `status` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=2211 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_order_products`
--

CREATE TABLE IF NOT EXISTS `srv_order_products` (
`uid` int(11) NOT NULL,
  `grouptype` int(11) NOT NULL,
  `category` int(11) NOT NULL,
  `name` varchar(128) NOT NULL,
  `price` int(11) NOT NULL,
  `value1` int(11) NOT NULL,
  `value2` int(11) NOT NULL,
  `type` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=341 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_penalty`
--

CREATE TABLE IF NOT EXISTS `srv_penalty` (
`penalty_id` int(11) NOT NULL,
  `player_uid` int(11) NOT NULL,
  `player_gid` int(11) NOT NULL,
  `admin_gid` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `value` int(11) NOT NULL,
  `reason` varchar(128) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=6356 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_plants`
--

CREATE TABLE IF NOT EXISTS `srv_plants` (
  `uid` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `owner` int(11) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `vw` int(11) NOT NULL,
  `int` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_safekeeps`
--

CREATE TABLE IF NOT EXISTS `srv_safekeeps` (
  `UID` int(11) NOT NULL,
  `inactive` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_salon_vehicles`
--

CREATE TABLE IF NOT EXISTS `srv_salon_vehicles` (
  `category` int(11) NOT NULL,
  `model` int(11) NOT NULL,
  `name` varchar(32) NOT NULL,
  `price` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_settings`
--

CREATE TABLE IF NOT EXISTS `srv_settings` (
  `status` int(11) NOT NULL,
  `spawnx` float NOT NULL,
  `spawny` float NOT NULL,
  `spawnz` float NOT NULL,
  `spawn_angle` float NOT NULL,
  `magazinex` float NOT NULL,
  `magaziney` float NOT NULL,
  `magazinez` float NOT NULL,
  `premiumeventdays` int(11) NOT NULL,
  `lsnprice` int(11) NOT NULL,
  `doc_id` int(11) NOT NULL,
  `doc_driver` int(11) NOT NULL,
  `doc_pilot` int(11) NOT NULL,
  `fuel_cost` int(11) NOT NULL,
  `hotelPrice` int(11) NOT NULL,
  `insurance` int(11) NOT NULL,
  `taxes` int(11) NOT NULL,
  `platecharge` int(11) NOT NULL,
  `registercharge` int(11) NOT NULL,
  `doc_weapon` smallint(6) NOT NULL,
  `doc_med` smallint(6) NOT NULL,
  `HealPrice` int(11) NOT NULL,
  `sannpay` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_tuning`
--

CREATE TABLE IF NOT EXISTS `srv_tuning` (
`id` int(11) NOT NULL,
  `vehicle` int(11) NOT NULL,
  `component_id` int(11) NOT NULL,
  `name` varchar(32) CHARACTER SET latin1 NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=454 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_vcards`
--

CREATE TABLE IF NOT EXISTS `srv_vcards` (
`uid` int(11) NOT NULL,
  `phone_uid` int(11) NOT NULL,
  `number` int(11) NOT NULL,
  `name` varchar(25) CHARACTER SET latin1 NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=6964 DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_vehicles`
--

CREATE TABLE IF NOT EXISTS `srv_vehicles` (
  `UID` int(11) NOT NULL,
  `model` int(11) NOT NULL,
  `hp` float NOT NULL,
  `visual` varchar(32) NOT NULL,
  `color1` int(11) NOT NULL,
  `color2` int(11) NOT NULL,
  `ownertyp` int(11) NOT NULL,
  `owner` int(11) NOT NULL,
  `posx` float NOT NULL,
  `posy` float NOT NULL,
  `posz` float NOT NULL,
  `angle` int(11) NOT NULL,
  `vw` int(11) NOT NULL,
  `interior` int(11) NOT NULL,
  `fuel` float NOT NULL,
  `distance` float NOT NULL,
  `register` varchar(32) NOT NULL,
  `radio_url` varchar(256) NOT NULL,
  `block` int(11) NOT NULL,
  `rank` int(11) NOT NULL,
  `description` varchar(128) NOT NULL,
  `tuning` int(11) NOT NULL,
  `registered` int(11) NOT NULL,
  `glass` int(11) NOT NULL,
  `last_driver` mediumint(8) unsigned NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_veh_logs`
--

CREATE TABLE IF NOT EXISTS `srv_veh_logs` (
  `from_uid` mediumint(8) unsigned NOT NULL,
  `from_gid` mediumint(8) unsigned NOT NULL,
  `to_uid` mediumint(8) unsigned NOT NULL,
  `to_gid` mediumint(8) unsigned NOT NULL,
  `value` int(11) NOT NULL,
  `veh_uid` smallint(5) unsigned NOT NULL,
  `model` smallint(5) unsigned NOT NULL,
  `type` tinyint(3) unsigned NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_walkie_channels`
--

CREATE TABLE IF NOT EXISTS `srv_walkie_channels` (
  `channel` smallint(6) NOT NULL,
  `creator` mediumint(9) NOT NULL,
  `password` text CHARACTER SET latin1 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `srv_weapons_magazine`
--

CREATE TABLE IF NOT EXISTS `srv_weapons_magazine` (
`uid` int(11) NOT NULL,
  `category` tinyint(4) NOT NULL,
  `name` varchar(32) NOT NULL,
  `type` tinyint(4) NOT NULL,
  `value1` tinyint(4) NOT NULL,
  `value2` smallint(6) NOT NULL,
  `price` mediumint(9) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=utf8;

--
-- Indeksy dla zrzutów tabel
--

--
-- Indexes for table `panel_admins_online`
--
ALTER TABLE `panel_admins_online`
 ADD PRIMARY KEY (`id`);

--
-- Indexes for table `panel_admin_log`
--
ALTER TABLE `panel_admin_log`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `panel_panel_log`
--
ALTER TABLE `panel_panel_log`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `panel_premium_codes`
--
ALTER TABLE `panel_premium_codes`
 ADD PRIMARY KEY (`code_uid`), ADD UNIQUE KEY `code` (`code`);

--
-- Indexes for table `panel_premium_logs`
--
ALTER TABLE `panel_premium_logs`
 ADD PRIMARY KEY (`code_uid`);

--
-- Indexes for table `srv_3dtext`
--
ALTER TABLE `srv_3dtext`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `srv_anims`
--
ALTER TABLE `srv_anims`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `srv_attached`
--
ALTER TABLE `srv_attached`
 ADD PRIMARY KEY (`UID`);

--
-- Indexes for table `srv_bans`
--
ALTER TABLE `srv_bans`
 ADD PRIMARY KEY (`ban_id`);

--
-- Indexes for table `srv_bus`
--
ALTER TABLE `srv_bus`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `srv_characters`
--
ALTER TABLE `srv_characters`
 ADD PRIMARY KEY (`player_uid`), ADD UNIQUE KEY `nickname` (`nickname`);

--
-- Indexes for table `srv_christmasshop`
--
ALTER TABLE `srv_christmasshop`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `srv_corners`
--
ALTER TABLE `srv_corners`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `srv_corpse`
--
ALTER TABLE `srv_corpse`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `srv_descriptions`
--
ALTER TABLE `srv_descriptions`
 ADD PRIMARY KEY (`UID`), ADD KEY `owneruid` (`owneruid`);

--
-- Indexes for table `srv_descriptions_text`
--
ALTER TABLE `srv_descriptions_text`
 ADD PRIMARY KEY (`UID`);

--
-- Indexes for table `srv_doors`
--
ALTER TABLE `srv_doors`
 ADD PRIMARY KEY (`UID`);

--
-- Indexes for table `srv_doors_members`
--
ALTER TABLE `srv_doors_members`
 ADD PRIMARY KEY (`UID`,`player_uid`), ADD KEY `player_uid` (`player_uid`);

--
-- Indexes for table `srv_falied_logins`
--
ALTER TABLE `srv_falied_logins`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `srv_fuel_orders`
--
ALTER TABLE `srv_fuel_orders`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `srv_fuel_stations`
--
ALTER TABLE `srv_fuel_stations`
 ADD PRIMARY KEY (`uid`), ADD KEY `owner` (`owner`);

--
-- Indexes for table `srv_groups`
--
ALTER TABLE `srv_groups`
 ADD PRIMARY KEY (`UID`);

--
-- Indexes for table `srv_groups_members`
--
ALTER TABLE `srv_groups_members`
 ADD PRIMARY KEY (`id`), ADD KEY `group_uid` (`group_uid`), ADD KEY `player_uid` (`player_uid`);

--
-- Indexes for table `srv_group_offer_logs`
--
ALTER TABLE `srv_group_offer_logs`
 ADD PRIMARY KEY (`id`), ADD KEY `groupid` (`groupid`);

--
-- Indexes for table `srv_group_offer_prices`
--
ALTER TABLE `srv_group_offer_prices`
 ADD PRIMARY KEY (`groupid`);

--
-- Indexes for table `srv_gym_pass`
--
ALTER TABLE `srv_gym_pass`
 ADD PRIMARY KEY (`id`);

--
-- Indexes for table `srv_hotel`
--
ALTER TABLE `srv_hotel`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `srv_items`
--
ALTER TABLE `srv_items`
 ADD PRIMARY KEY (`UID`);

--
-- Indexes for table `srv_items_logs`
--
ALTER TABLE `srv_items_logs`
 ADD PRIMARY KEY (`id`);

--
-- Indexes for table `srv_jail_logs`
--
ALTER TABLE `srv_jail_logs`
 ADD PRIMARY KEY (`logid`);

--
-- Indexes for table `srv_kartoteki`
--
ALTER TABLE `srv_kartoteki`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `srv_kartoteki_records`
--
ALTER TABLE `srv_kartoteki_records`
 ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `srv_legal_weapons`
--
ALTER TABLE `srv_legal_weapons`
 ADD PRIMARY KEY (`weapuid`);

--
-- Indexes for table `srv_mmat_text`
--
ALTER TABLE `srv_mmat_text`
 ADD PRIMARY KEY (`object_id`,`index`);

--
-- Indexes for table `srv_mostwanted`
--
ALTER TABLE `srv_mostwanted`
 ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `srv_objects`
--
ALTER TABLE `srv_objects`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `srv_orders`
--
ALTER TABLE `srv_orders`
 ADD PRIMARY KEY (`uid`), ADD KEY `door_uid` (`door_uid`);

--
-- Indexes for table `srv_order_products`
--
ALTER TABLE `srv_order_products`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `srv_penalty`
--
ALTER TABLE `srv_penalty`
 ADD PRIMARY KEY (`penalty_id`);

--
-- Indexes for table `srv_plants`
--
ALTER TABLE `srv_plants`
 ADD PRIMARY KEY (`uid`);

--
-- Indexes for table `srv_safekeeps`
--
ALTER TABLE `srv_safekeeps`
 ADD PRIMARY KEY (`UID`);

--
-- Indexes for table `srv_salon_vehicles`
--
ALTER TABLE `srv_salon_vehicles`
 ADD PRIMARY KEY (`model`);

--
-- Indexes for table `srv_settings`
--
ALTER TABLE `srv_settings`
 ADD PRIMARY KEY (`status`);

--
-- Indexes for table `srv_tuning`
--
ALTER TABLE `srv_tuning`
 ADD PRIMARY KEY (`id`), ADD KEY `vehicle` (`vehicle`);

--
-- Indexes for table `srv_vcards`
--
ALTER TABLE `srv_vcards`
 ADD PRIMARY KEY (`uid`), ADD KEY `phone_uid` (`phone_uid`);

--
-- Indexes for table `srv_vehicles`
--
ALTER TABLE `srv_vehicles`
 ADD PRIMARY KEY (`UID`);

--
-- Indexes for table `srv_walkie_channels`
--
ALTER TABLE `srv_walkie_channels`
 ADD PRIMARY KEY (`channel`);

--
-- Indexes for table `srv_weapons_magazine`
--
ALTER TABLE `srv_weapons_magazine`
 ADD PRIMARY KEY (`uid`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT dla tabeli `panel_admins_online`
--
ALTER TABLE `panel_admins_online`
MODIFY `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `panel_admin_log`
--
ALTER TABLE `panel_admin_log`
MODIFY `uid` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `panel_panel_log`
--
ALTER TABLE `panel_panel_log`
MODIFY `uid` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `panel_premium_codes`
--
ALTER TABLE `panel_premium_codes`
MODIFY `code_uid` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `panel_premium_logs`
--
ALTER TABLE `panel_premium_logs`
MODIFY `code_uid` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_anims`
--
ALTER TABLE `srv_anims`
MODIFY `uid` smallint(5) unsigned NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_bans`
--
ALTER TABLE `srv_bans`
MODIFY `ban_id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_characters`
--
ALTER TABLE `srv_characters`
MODIFY `player_uid` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_christmasshop`
--
ALTER TABLE `srv_christmasshop`
MODIFY `uid` tinyint(4) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_corpse`
--
ALTER TABLE `srv_corpse`
MODIFY `uid` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_falied_logins`
--
ALTER TABLE `srv_falied_logins`
MODIFY `uid` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_fuel_orders`
--
ALTER TABLE `srv_fuel_orders`
MODIFY `uid` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_groups_members`
--
ALTER TABLE `srv_groups_members`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_group_offer_logs`
--
ALTER TABLE `srv_group_offer_logs`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_gym_pass`
--
ALTER TABLE `srv_gym_pass`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_hotel`
--
ALTER TABLE `srv_hotel`
MODIFY `uid` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT dla tabeli `srv_items_logs`
--
ALTER TABLE `srv_items_logs`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_jail_logs`
--
ALTER TABLE `srv_jail_logs`
MODIFY `logid` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_kartoteki`
--
ALTER TABLE `srv_kartoteki`
MODIFY `uid` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_kartoteki_records`
--
ALTER TABLE `srv_kartoteki_records`
MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_mostwanted`
--
ALTER TABLE `srv_mostwanted`
MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_orders`
--
ALTER TABLE `srv_orders`
MODIFY `uid` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_order_products`
--
ALTER TABLE `srv_order_products`
MODIFY `uid` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_penalty`
--
ALTER TABLE `srv_penalty`
MODIFY `penalty_id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_tuning`
--
ALTER TABLE `srv_tuning`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_vcards`
--
ALTER TABLE `srv_vcards`
MODIFY `uid` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT dla tabeli `srv_weapons_magazine`
--
ALTER TABLE `srv_weapons_magazine`
MODIFY `uid` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=1;
--
-- Ograniczenia dla zrzutów tabel
--

--
-- Zrzut danych tabeli `srv_anims`
--

INSERT INTO `srv_anims` (`uid`, `cmd`, `lib`, `name`, `speed`, `loop/sa`, `lockx`, `locky`, `freeze`, `time`, `action`) VALUES
(1, 'idz1', 'PED', 'WALK_gang1', 4.1, 1, 1, 1, 1, 1, 1),
(2, 'idz2', 'PED', 'WALK_gang2', 4.1, 1, 1, 1, 1, 1, 1),
(3, 'idz3', 'PED', 'WOMAN_walksexy', 4, 1, 1, 1, 1, 1, 1),
(4, 'idz4', 'PED', 'WOMAN_walkfatold', 4, 1, 1, 1, 1, 1, 1),
(5, 'idz5', 'PED', 'Walk_Wuzi', 4, 1, 1, 1, 1, 1, 1),
(6, 'idz6', 'PED', 'WALK_player', 6, 1, 1, 1, 1, 1, 1),
(7, 'stopani', 'CARRY', 'crry_prtial', 4, 0, 0, 0, 0, 0, 0),
(8, 'pa', 'KISSING', 'gfwave2', 6, 0, 0, 0, 0, 0, 0),
(9, 'zmeczony', 'PED', 'IDLE_tired', 4, 1, 0, 0, 0, 0, 1),
(10, 'umyjrece', 'INT_HOUSE', 'wash_up', 4, 0, 0, 0, 0, 0, 0),
(11, 'medyk', 'MEDIC', 'CPR', 4, 0, 0, 0, 0, 0, 0),
(12, 'ranny', 'SWEET', 'Sweet_injuredloop', 4, 1, 0, 0, 1, 1, 1),
(13, 'salutuj', 'ON_LOOKERS', 'lkup_in', 4, 0, 1, 1, 1, 0, 1),
(14, 'wtf', 'RIOT', 'RIOT_ANGRY', 4, 0, 1, 1, 1, 1, 1),
(15, 'spoko', 'GANGS', 'prtial_gngtlkD', 4, 0, 0, 0, 0, 0, 0),
(16, 'napad', 'SHOP', 'ROB_Loop_Threat', 4, 1, 0, 0, 1, 1, 1),
(17, 'krzeslo', 'ped', 'SEAT_idle', 5, 1, 0, 0, 1, 1, 1),
(18, 'szukaj', 'COP_AMBIENT', 'Copbrowse_loop', 4, 1, 0, 0, 0, 0, 1),
(19, 'lornetka', 'ON_LOOKERS', 'shout_loop', 4, 1, 0, 0, 0, 0, 1),
(20, 'oh', 'MISC', 'plyr_shkhead', 4, 0, 0, 0, 0, 0, 0),
(21, 'oh2', 'OTB', 'wtchrace_lose', 4, 0, 1, 1, 0, 0, 0),
(22, 'wyciagnij', 'FOOD', 'SHP_Tray_Lift', 4, 0, 0, 0, 0, 0, 0),
(23, 'zdziwiony', 'PED', 'facsurp', 4, 0, 1, 1, 1, 1, 1),
(24, 'recemaska', 'POLICE', 'crm_drgbst_01', 6, 1, 0, 0, 1, 0, 1),
(25, 'krzeslojem', 'FOOD', 'FF_Sit_Eat1', 4, 1, 0, 0, 0, 0, 1),
(26, 'gogo', 'RIOT', 'RIOT_CHANT', 4, 1, 1, 1, 1, 0, 1),
(27, 'czekam', 'GRAVEYARD', 'prst_loopa', 4, 1, 0, 0, 1, 1, 1),
(28, 'garda', 'FIGHT_D', 'FightD_IDLE', 4, 1, 1, 1, 1, 0, 1),
(29, 'barman2', 'BAR', 'BARman_idle', 4, 0, 0, 0, 0, 0, 0),
(30, 'fotel', 'INT_HOUSE', 'LOU_Loop', 4, 1, 0, 0, 1, 1, 1),
(31, 'napraw', 'CAR', 'Fixn_Car_Loop', 4, 1, 0, 0, 1, 1, 1),
(32, 'barman', 'BAR', 'Barserve_loop', 4, 1, 0, 0, 0, 0, 1),
(33, 'opieraj', 'GANGS', 'leanIDLE', 4, 1, 0, 0, 1, 1, 1),
(34, 'bar.nalej', 'BAR', 'Barserve_glass', 4, 0, 0, 0, 0, 0, 0),
(35, 'ramiona', 'COP_AMBIENT', 'Coplook_loop', 4, 1, 0, 0, 1, 0, 1),
(36, 'bar.wez', 'BAR', 'Barserve_bottle', 4, 0, 0, 0, 0, 0, 0),
(37, 'chowaj', 'ped', 'cower', 3, 1, 0, 0, 0, 0, 1),
(38, 'wez', 'BAR', 'Barserve_give', 4, 0, 0, 0, 0, 0, 0),
(39, 'fuck', 'ped', 'fucku', 4, 0, 0, 0, 0, 0, 0),
(40, 'klepnij', 'SWEET', 'sweet_ass_slap', 6, 0, 0, 0, 0, 0, 0),
(41, 'cmon', 'RYDER', 'RYD_Beckon_01', 4, 0, 1, 1, 0, 0, 1),
(42, 'daj', 'DEALER', 'DEALER_DEAL', 8, 0, 0, 0, 0, 0, 0),
(43, 'pij', 'VENDING', 'VEND_Drink2_P', 4, 1, 1, 1, 1, 0, 1),
(44, 'start', 'CAR', 'flag_drop', 4, 0, 0, 0, 0, 0, 0),
(45, 'karta', 'HEIST9', 'Use_SwipeCard', 4, 0, 0, 0, 0, 0, 0),
(46, 'spray', 'GRAFFITI', 'spraycan_fire', 4, 1, 0, 0, 0, 0, 1),
(47, 'odejdz', 'POLICE', 'CopTraf_Left', 4, 0, 0, 0, 0, 0, 0),
(48, 'fotelk', 'JST_BUISNESS', 'girl_02', 4, 1, 0, 0, 1, 1, 1),
(49, 'chodz', 'POLICE', 'CopTraf_Come', 4, 0, 0, 0, 0, 0, 0),
(50, 'stop', 'POLICE', 'CopTraf_Stop', 4, 0, 0, 0, 0, 0, 0),
(51, 'drapjaja', 'MISC', 'Scratchballs_01', 4, 1, 0, 0, 0, 0, 1),
(52, 'opieraj2', 'MISC', 'Plyrlean_loop', 4, 1, 0, 0, 0, 0, 1),
(53, 'walekonia', 'PAULNMAC', 'wank_loop', 4, 1, 0, 0, 0, 0, 1),
(54, 'popchnij', 'GANGS', 'shake_cara', 4, 0, 0, 0, 0, 0, 0),
(55, 'rzuc', 'GRENADE', 'WEAPON_throwu', 3, 0, 0, 0, 0, 0, 0),
(56, 'rap1', 'RAPPING', 'RAP_A_Loop', 4, 1, 0, 0, 0, 0, 1),
(57, 'rap2', 'RAPPING', 'RAP_C_Loop', 4, 1, 0, 0, 0, 0, 1),
(58, 'rap3', 'RAPPING', 'RAP_B_Loop', 4, 1, 0, 0, 0, 0, 1),
(59, 'rap4', 'GANGS', 'prtial_gngtlkH', 4, 1, 0, 0, 1, 1, 1),
(60, 'glowka', 'WAYFARER', 'WF_Fwd', 4, 0, 0, 0, 0, 0, 0),
(61, 'skop', 'FIGHT_D', 'FightD_G', 4, 0, 0, 0, 0, 0, 0),
(62, 'siad', 'BEACH', 'ParkSit_M_loop', 4, 1, 0, 0, 0, 0, 1),
(63, 'krzeslo2', 'FOOD', 'FF_Sit_Loop', 4, 1, 0, 0, 0, 0, 1),
(64, 'krzeslo3', 'INT_OFFICE', 'OFF_Sit_Idle_Loop', 4, 1, 0, 0, 0, 0, 1),
(65, 'krzeslo4', 'INT_OFFICE', 'OFF_Sit_Bored_Loop', 4, 1, 0, 0, 0, 0, 1),
(66, 'krzeslo5', 'INT_OFFICE', 'OFF_Sit_Type_Loop', 4, 1, 0, 0, 0, 0, 1),
(67, 'padnij', 'PED', 'KO_shot_front', 4, 0, 1, 1, 1, 0, 1),
(68, 'padaczka', 'PED', 'FLOOR_hit_f', 4, 1, 0, 0, 0, 0, 1),
(69, 'unik', 'PED', 'EV_dive', 4, 0, 1, 1, 1, 0, 1),
(70, 'ranny3', 'CRACK', 'crckdeth2', 4, 1, 0, 0, 0, 0, 1),
(71, 'bomb', 'BOMBER', 'BOM_Plant', 4, 0, 0, 0, 0, 0, 1),
(72, 'cpaj', 'SHOP', 'ROB_Shifty', 4, 0, 0, 0, 0, 0, 1),
(73, 'rece', 'ROB_BANK', 'SHP_HandsUp_Scr', 4, 0, 1, 1, 1, 1, 1),
(74, 'tancz1', '-', '-', 0, 5, 0, 0, 0, 0, 2),
(75, 'tancz2', '-', '-', 0, 6, 0, 0, 0, 0, 2),
(76, 'tancz3', '-', '-', 0, 7, 0, 0, 0, 0, 2),
(77, 'tancz4', '-', '-', 0, 8, 0, 0, 0, 0, 2),
(78, 'tancz5', 'STRIP', 'STR_Loop_A', 2, 1, 0, 0, 0, 0, 1),
(79, 'pijak', 'PED', 'WALK_DRUNK', 4, 1, 1, 1, 1, 1, 1),
(80, 'nie', 'GANGS', 'Invite_No', 4, 0, 0, 0, 0, 0, 0),
(81, 'lokiec', 'CAR', 'Sit_relaxed', 4, 1, 1, 1, 1, 0, 1),
(82, 'go', 'RIOT', 'RIOT_PUNCHES', 4, 0, 0, 0, 0, 0, 0),
(83, 'stack1', 'GHANDS', 'gsign2LH', 4, 0, 0, 0, 0, 0, 0),
(84, 'lez3', 'BEACH', 'ParkSit_W_loop', 4, 1, 0, 0, 0, 0, 1),
(85, 'lez1', 'BEACH', 'bather', 4, 1, 0, 0, 0, 0, 1),
(86, 'lez2', 'BEACH', 'Lay_Bac_Loop', 4, 1, 0, 0, 0, 0, 1),
(87, 'padnij2', 'PED', 'KO_skid_front', 4, 0, 1, 1, 1, 0, 1),
(88, 'bat', 'CRACK', 'Bbalbat_Idle_01', 4, 1, 1, 1, 1, 1, 1),
(89, 'bat2', 'CRACK', 'Bbalbat_Idle_02', 4, 0, 1, 1, 1, 1, 1),
(90, 'stack2', 'GHANDS', 'gsign2', 4, 0, 1, 1, 1, 1, 1),
(91, 'stack3', 'GHANDS', 'gsign4', 4, 0, 1, 1, 1, 1, 1),
(92, 'taichi', 'PARK', 'Tai_Chi_Loop', 4, 1, 0, 0, 0, 0, 1),
(93, 'kosz1', 'BSKTBALL', 'BBALL_idleloop', 4, 1, 0, 0, 0, 0, 1),
(94, 'kosz2', 'BSKTBALL', 'BBALL_Jump_Shot', 4, 0, 0, 0, 0, 0, 1),
(95, 'kosz3', 'BSKTBALL', 'BBALL_pickup', 4, 0, 0, 0, 0, 0, 1),
(96, 'kosz4', 'BSKTBALL', 'BBALL_def_loop', 4, 1, 0, 0, 0, 0, 1),
(97, 'kosz5', 'BSKTBALL', 'BBALL_Dnk', 4, 0, 0, 0, 0, 0, 1),
(98, 'papieros', 'SMOKING', 'M_smklean_loop', 4, 1, 0, 0, 0, 0, 1),
(99, 'wymiotuj', 'FOOD', 'EAT_Vomit_P', 3, 0, 0, 0, 0, 0, 1),
(100, 'fuck2', 'RIOT', 'RIOT_FUKU', 4, 0, 0, 0, 0, 0, 0),
(101, 'koks', 'PED', 'IDLE_HBHB', 4, 1, 0, 0, 1, 0, 1),
(102, 'idz7', 'PED', 'WOMAN_walkshop', 4, 1, 1, 1, 1, 1, 1),
(103, 'cry', 'GRAVEYARD', 'mrnF_loop', 4, 1, 0, 0, 1, 0, 1),
(104, 'rozciagaj', 'PLAYIDLES', 'stretch', 4, 0, 0, 0, 0, 0, 1),
(105, 'cellin', '-', '-', 0, 11, 0, 0, 0, 0, 2),
(106, 'cellout', '-', '-', 0, 13, 0, 0, 0, 0, 2),
(107, 'bagaznik', 'POOL', 'POOL_Place_White', 4, 0, 0, 0, 1, 0, 1),
(108, 'wywaz', 'GANGS', 'shake_carK', 4, 0, 0, 0, 0, 0, 0),
(109, 'skradajsie', 'PED', 'Player_Sneak', 6, 1, 1, 1, 1, 1, 1),
(110, 'przycisk', 'CRIB', 'CRIB_use_switch', 4, 0, 0, 0, 0, 0, 1),
(111, 'tancz6', 'DANCING', 'DAN_down_A', 4, 1, 0, 0, 0, 0, 1),
(112, 'tancz7', 'DANCING', 'DAN_left_A', 4, 1, 0, 0, 0, 0, 1),
(113, 'idz8', 'PED', 'walk_shuffle', 4, 1, 1, 1, 1, 1, 1),
(114, 'stack4', 'LOWRIDER', 'prtial_gngtlkB', 4, 0, 0, 0, 0, 0, 1),
(115, 'stack5', 'LOWRIDER', 'prtial_gngtlkC', 4, 0, 1, 1, 1, 1, 1),
(116, 'stack6', 'lowrider', 'prtial_gngtlkD', 4, 0, 0, 0, 0, 0, 0),
(117, 'stack7', 'lowrider', 'prtial_gngtlkE', 4, 0, 0, 0, 0, 0, 1),
(118, 'stack8', 'lowrider', 'prtial_gngtlkF', 4, 0, 0, 0, 0, 0, 1),
(119, 'stack9', 'lowrider', 'prtial_gngtlkG', 4, 0, 0, 0, 0, 0, 1),
(120, 'stack10', 'lowrider', 'prtial_gngtlkH', 4, 0, 1, 1, 1, 1, 1),
(121, 'tancz8', 'DANCING', 'dnce_m_d', 4, 1, 0, 0, 0, 0, 1),
(122, 'kasjer', 'INT_SHOP', 'shop_cashier', 4, 0, 0, 0, 0, 0, 1),
(123, 'idz9', 'wuzi', 'wuzi_walk', 4, 1, 1, 1, 1, 1, 1),
(124, 'taxi', 'misc', 'hiker_pose', 4, 0, 0, 0, 1, 0, 1),
(125, 'wskaz', 'on_lookers', 'pointup_loop', 4, 0, 0, 0, 1, 0, 1),
(126, 'wskaz2', 'on_lookers', 'point_loop', 4, 0, 0, 0, 1, 0, 1),
(127, 'podpisz', 'otb', 'betslp_loop', 4, 0, 0, 0, 0, 0, 1),
(132, 'jedz', 'FOOD', 'EAT_Burger', 4.1, 0, 0, 0, 0, 0, 1),
(133, 'dealer', 'DEALER', 'DEALER_IDLE', 4.1, 1, 1, 1, 1, 0, 1),
(134, 'dealer2', 'DEALER', 'DEALER_IDLE_01', 4.1, 1, 1, 1, 0, 0, 1),
(135, 'dealer3', 'DEALER', 'DEALER_IDLE_02', 4.1, 1, 1, 1, 0, 0, 1),
(136, 'dealer4', 'DEALER', 'DEALER_IDLE_03', 4.1, 1, 1, 1, 0, 0, 1),
(137, 'siad2', 'ATTRACTORS', 'Stepsit_loop', 4.1, 1, 1, 1, 0, 0, 1),
(138, 'lokiec2', 'CAR', 'Tap_hand', 4.1, 1, 1, 1, 0, 0, 1),
(139, 'preload', 'COLT45', 'colt45_reload', 4.1, 0, 0, 0, 0, 1000, 1),
(140, 'mysl', 'COP_AMBIENT', 'Coplook_think', 4.1, 1, 1, 1, 0, 0, 1),
(141, 'zegarek', 'COP_AMBIENT', 'Coplook_watch', 4.1, 0, 0, 0, 0, 1000, 1),
(142, 'crack2', 'CRACK', 'crckidle1', 4.1, 1, 1, 1, 1, 0, 1),
(143, 'crack3', 'CRACK', 'crckidle2', 4.1, 1, 1, 1, 1, 0, 1),
(144, 'crack4', 'CRACK', 'crckidle3', 4.1, 1, 1, 1, 1, 0, 1),
(145, 'crack5', 'CRACK', 'crckidle4', 4.1, 1, 1, 1, 1, 0, 1),
(146, 'gang1', 'GANGS', 'prtial_gngtlkA', 4.1, 1, 1, 1, 1, 0, 1),
(147, 'gang2', 'GANGS', 'prtial_gngtlkB', 4.1, 1, 1, 1, 1, 0, 1),
(148, 'gang3', 'GANGS', 'prtial_gngtlkC', 4.1, 1, 1, 1, 1, 0, 1),
(149, 'gang4', 'GANGS', 'prtial_gngtlkD', 4.1, 1, 1, 1, 1, 0, 1),
(150, 'gang5', 'GANGS', 'prtial_gngtlkE', 4.1, 1, 1, 1, 1, 0, 1),
(151, 'gang6', 'GANGS', 'prtial_gngtlkF', 4.1, 1, 1, 1, 1, 0, 1),
(152, 'gang7', 'GANGS', 'prtial_gngtlkG', 4.1, 1, 1, 1, 1, 0, 1),
(153, 'gang8', 'GANGS', 'prtial_gngtlkH', 4.1, 1, 1, 1, 1, 0, 1),
(154, 'czekaj2', 'GRAVEYARD', 'mrnM_loop', 4.1, 1, 1, 1, 1, 0, 1),
(155, 'hide', 'PED', 'cower', 4.1, 1, 1, 1, 0, 0, 1),
(156, 'papieros2', 'LOWRIDER', 'F_smklean_loop', 4.1, 1, 1, 1, 0, 0, 1),
(157, 'kreload', 'RIFLE', 'RIFLE_load', 4.1, 0, 0, 0, 0, 1000, 1),
(158, 'stack11', 'GHANDS', 'gsign1', 4, 0, 0, 0, 0, 0, 0),
(159, 'stack12', 'GHANDS', 'gsign1LH', 4, 0, 0, 0, 0, 0, 0),
(160, 'stack13', 'GHANDS', 'gsign3', 4, 0, 0, 0, 0, 0, 0),
(161, 'stack14', 'GHANDS', 'gsign5', 4, 0, 0, 0, 0, 0, 0),
(162, 'stack15', 'GHANDS', 'gsign5LH', 4, 0, 0, 0, 0, 0, 0),
(163, 'ranny2', 'CRACK', 'crckdeth1', 4, 1, 0, 0, 0, 0, 1),
(166, 'ranny4', 'CRACK', 'crckidle3', 4, 1, 0, 0, 0, 0, 1),
(167, 'ranny5', 'CRACK', 'crckidle4', 4, 1, 0, 0, 0, 0, 1),
(168, '.bronidz', 'POLICE', 'Cop_move_FWD', 6, 1, 0, 0, 0, 0, 1);

--
-- Zrzut danych tabeli `srv_bus`
--

INSERT INTO `srv_bus` (`uid`, `name`, `pos_x`, `pos_y`, `pos_z`, `angle`) VALUES
(1, 'Rodeo', 427.758, -1598.96, 25.8167, 357.074),
(2, 'Pershing Square - Centrum', 1521.68, -1695.58, 13.5469, 270.311),
(3, 'Market', 1227.14, -1387.36, 13.4056, 177.773),
(4, 'Santa Maria Beach', 336.625, -1767.78, 5.24465, 270.668),
(5, 'Unity Station', 1795.1, -1862.12, 13.5767, 3.72856),
(6, 'Downtown', 1567.8, -1286.53, 17.4311, 184.066),
(7, 'Idlewood', 1965.05, -1745.09, 13.5469, 182.095),
(8, 'Lotnisko Los Santos', 1667.88, -2326.07, 13.5469, 353.856),
(9, 'Doki - Magazyn paczek', 2606.19, -2389.83, 13.6216, 142.146),
(10, 'Ganton', 2324.73, -1652.51, 13.8304, 181.385),
(11, 'Jefferson', 2195.93, -1133.52, 25.5283, 339.838),
(12, 'Dillmore', 661.751, -610.475, 16.3359, 358.594),
(13, 'Pizzeria Idlewood', 2087.85, -1831.37, 13.5469, 94.9409),
(14, 'Rodeo - salon pojazdow', 531.485, -1269.57, 16.4242, 39.5406),
(15, 'Palomino Creek', 2478.18, 32.9319, 26.4844, 358.693),
(16, 'Ganton', 2171.07, -1739.12, 13.5487, 277.697),
(17, 'Angel Pine', -2192.28, -2270.36, 30.625, 142.568),
(18, 'East Beach', 2864.78, -1907.06, 11.1094, 93.4742),
(19, 'Montgomery', 1257.74, 256.27, 19.5547, 337.586),
(20, 'Blueberry', 158.913, -135.393, 1.57812, 171.228),
(21, 'Bayside', -2534.02, 2270.7, 4.98438, 337.876),
(22, 'Lotnisko San Fierro', -1737.9, -569.926, 16.4844, 182.438),
(23, 'Lotnisko Las Venturas', 1707.81, 1450.38, 10.8176, 253.902),
(24, 'Rodeo - Apartamentowiec', 305.612, -1633.28, 33.3294, 172.889),
(25, 'Pilon Street - Lombard', 2436.85, -1535.48, 24, 85.0579),
(26, 'Test', 1552.85, -1739.61, 13.5469, 358.645),
(27, 'Test2', 1536.47, -1724.34, 13.5469, 60.6852);

--
-- Zrzut danych tabeli `srv_order_products`
--

INSERT INTO `srv_order_products` (`uid`, `grouptype`, `category`, `name`, `price`, `value1`, `value2`, `type`) VALUES
(1, 2, 0, 'Palka Teleskopowa [LSPD]', 500, 3, 1, 1),
(2, 2, 0, 'Granat Dymny [LSPD]', 1500, 17, 3, 1),
(3, 2, 0, 'Desert Eagle [LSPD]', 2500, 24, 100, 1),
(4, 2, 0, 'Less Lethal Shotgun [LSPD]', 2500, 33, 100, 1),
(5, 2, 0, 'Shotgun [LSPD]', 5000, 25, 100, 1),
(6, 2, 0, 'MP5 [LSPD]', 7500, 29, 250, 1),
(7, 2, 0, 'AK-47 [LSPD]', 10000, 30, 250, 1),
(8, 2, 0, 'M4 [LSPD]', 12500, 31, 250, 1),
(9, 2, 0, 'Snajperka [LSPD]', 20000, 34, 15, 1),
(10, 2, 1, 'Ammo [LessLethal][LSPD]', 350, 33, 100, 22),
(11, 2, 1, 'Ammo [DE][LSPD]', 500, 24, 100, 22),
(12, 2, 1, 'Ammo [Shotgun][LSPD]', 750, 25, 100, 22),
(13, 2, 1, 'Ammo [MP5][LSPD]', 1000, 29, 250, 22),
(14, 2, 1, 'Ammo [AK-47][LSPD]', 1500, 30, 250, 22),
(15, 2, 1, 'Ammo [M4][LSPD]', 1750, 31, 250, 22),
(16, 2, 1, 'Ammo [Snajperka][LSPD]', 10000, 34, 10, 22),
(17, 2, 2, 'Krotkofalowka', 15, 1, 1, 18),
(18, 2, 2, 'Megafon [LSPD]', 200, 0, 0, 19),
(19, 2, 2, 'Kominiarka', 50, 0, 0, 3),
(20, 2, 2, 'Lekka Kamizelka [LSPD]', 550, 50, 0, 8),
(21, 2, 2, 'Ciezka Kamizelka [LSPD]', 5000, 100, 0, 8),
(22, 3, 0, 'Megafon', 300, 0, 0, 19),
(23, 4, 0, 'Megafon', 300, 0, 0, 19),
(24, 4, 1, 'Aparat', 200, 43, 200, 1),
(25, 5, 0, 'Palka Teleskopowa [FBI]', 500, 3, 1, 1),
(26, 5, 0, 'Granat Dymny [FBI]', 1500, 17, 3, 1),
(27, 5, 0, 'Desert Eagle [FBI]', 2500, 24, 100, 1),
(28, 5, 0, 'Shotgun [FBI]', 5000, 25, 100, 1),
(29, 5, 0, 'MP5 [FBI]', 7500, 29, 250, 1),
(30, 5, 0, 'AK-47 [FBI]', 10000, 30, 250, 1),
(31, 5, 0, 'M4 [FBI]', 12500, 31, 250, 1),
(32, 5, 0, 'Snajperka [FBI]', 20000, 34, 15, 1),
(33, 5, 1, 'Ammo [DE][FBI]', 500, 24, 100, 22),
(34, 5, 1, 'Ammo [Shotgun][FBI]', 750, 25, 100, 22),
(35, 5, 1, 'Ammo [MP5][FBI]', 1000, 29, 250, 22),
(36, 5, 1, 'Ammo [AK-47][FBI]', 1500, 30, 250, 22),
(37, 5, 1, 'Ammo [M4][FBI]', 1750, 31, 250, 22),
(38, 5, 1, 'Ammo [Snajperka][FBI]', 10000, 34, 10, 22),
(39, 5, 2, 'Krotkofalowka', 15, 1, 1, 18),
(40, 5, 2, 'Kominiarka', 50, 0, 0, 3),
(41, 5, 2, 'Megafon [FBI]', 200, 0, 0, 19),
(42, 5, 2, 'Lekka Kamizelka [FBI]', 550, 50, 0, 8),
(43, 5, 2, 'Ciezka Kamizelka [FBI]', 5000, 100, 0, 8),
(45, 7, 0, 'Nasionko marihuany', 100, 1, 1, 13),
(47, 7, 0, 'Baseball', 50, 5, 1, 1),
(54, 9, 0, 'Nitro x2', 20000, 1009, 0, 23),
(55, 9, 0, 'Nitro x5', 50000, 1008, 0, 23),
(56, 9, 0, 'Nitro x10', 100000, 1010, 0, 23),
(57, 10, 0, 'Kostki do gry', 10, 0, 0, 5),
(58, 10, 0, 'Karty', 10, 0, 0, 6),
(59, 10, 0, 'Piwo', 20, 0, 0, 12),
(61, 10, 0, 'Papierosy', 30, 20, 1, 11),
(63, 10, 0, 'Krotkofalowka', 30, 1, 1, 18),
(64, 10, 0, 'Telefon', 50, 1, 1, 2),
(65, 10, 0, 'Zegarek', 50, 0, 0, 9),
(66, 10, 0, 'Boombox', 200, 0, 0, 21),
(67, 10, 0, 'Aparat', 200, 43, 0, 1),
(68, 11, 0, 'Access', 1500, 1098, 0, 23),
(69, 11, 0, 'Rimshine', 2000, 1075, 0, 23),
(70, 11, 0, 'Ahab', 2000, 1096, 0, 23),
(71, 11, 0, 'Wires', 3000, 1076, 0, 23),
(72, 11, 0, 'Grove', 3000, 1081, 0, 23),
(73, 11, 0, 'Trance', 3000, 1084, 0, 23),
(74, 11, 0, 'Atomic', 3000, 1085, 0, 23),
(75, 11, 0, 'Virtual', 3000, 1097, 0, 23),
(76, 11, 0, 'Shadow', 4000, 1073, 0, 23),
(77, 11, 0, 'Mega', 4000, 1074, 0, 23),
(78, 11, 0, 'Cutter', 4000, 1079, 0, 23),
(79, 11, 0, 'Import', 4000, 1082, 0, 23),
(80, 11, 0, 'Classic', 5000, 1077, 0, 23),
(81, 11, 0, 'Switch', 5000, 1080, 0, 23),
(82, 11, 0, 'Twist', 5000, 1078, 0, 23),
(83, 11, 0, 'Dollar', 5000, 1083, 0, 23),
(84, 11, 1, 'Hydraulika', 8000, 1087, 0, 23),
(85, 11, 2, 'WydechAlien [Sultan]', 2000, 1028, 0, 23),
(86, 11, 2, 'WydechX-Flow [Sultan]', 2000, 1029, 0, 23),
(87, 11, 2, 'ProgiAlien [Sultan]', 3000, 1026, 0, 23),
(88, 11, 2, 'ProgiX-Flow [Sultan]', 3000, 1030, 0, 23),
(89, 11, 2, 'ZderzakPAlien [Sultan]', 4000, 1169, 0, 23),
(90, 11, 2, 'ZderzakPX-Flow [Sultan]', 4000, 1170, 0, 23),
(91, 11, 2, 'ZderzakTAlien [Sultan]', 4000, 1141, 0, 23),
(92, 11, 2, 'ZderzakTX-Flow [Sultan]', 4000, 1140, 0, 23),
(93, 11, 2, 'WlotyAlien [Sultan]', 4000, 1032, 0, 23),
(94, 11, 2, 'WlotyX-Flow [Sultan]', 4000, 1033, 0, 23),
(95, 11, 2, 'SpoilerAlien [Sultan]', 4000, 1138, 0, 23),
(96, 11, 2, 'SpoilerX-Flow [Sultan]', 4000, 1139, 0, 23),
(97, 11, 3, 'WydechAlien [Jester]', 2000, 1065, 0, 23),
(98, 11, 3, 'WydechX-Flow [Jester]', 2000, 1066, 0, 23),
(99, 11, 3, 'ProgiAlien [Jester]', 3000, 1071, 0, 23),
(100, 11, 3, 'ProgiX-Flow [Jester]', 3000, 1072, 0, 23),
(101, 11, 3, 'ZderzakPAlien [Jester]', 4000, 1160, 0, 23),
(102, 11, 3, 'ZderzakPX-Flow [Jester]', 4000, 1173, 0, 23),
(103, 11, 3, 'ZderzakTAlien [Jester]', 4000, 1159, 0, 23),
(104, 11, 3, 'ZderzakTX-Flow [Jester]', 4000, 1161, 0, 23),
(105, 11, 3, 'WlotyAlien [Jester]', 4000, 1067, 0, 23),
(106, 11, 3, 'WlotyX-Flow [Jester]', 4000, 1068, 0, 23),
(107, 11, 3, 'SpoilerAlien [Jester]', 4000, 1162, 0, 23),
(108, 11, 3, 'SpoilerX-Flow [Jester]', 4000, 1158, 0, 23),
(109, 11, 4, 'WydechAlien [Elegy]', 2000, 1034, 0, 23),
(110, 11, 4, 'WydechX-Flow [Elegy]', 2000, 1037, 0, 23),
(111, 11, 4, 'ProgiAlien [Elegy]', 3000, 1040, 0, 23),
(112, 11, 4, 'ProgiX-Flow [Elegy]', 3000, 1039, 0, 23),
(113, 11, 4, 'ZderzakPAlien [Elegy]', 4000, 1171, 0, 23),
(114, 11, 4, 'ZderzakPX-Flow [Elegy]', 4000, 1172, 0, 23),
(115, 11, 4, 'ZderzakTAlien [Elegy]', 4000, 1149, 0, 23),
(116, 11, 4, 'ZderzakTX-Flow [Elegy]', 4000, 1148, 0, 23),
(117, 11, 4, 'WlotyAlien [Elegy]', 4000, 1038, 0, 23),
(118, 11, 4, 'WlotyX-Flow [Elegy]', 4000, 1035, 0, 23),
(119, 11, 4, 'SpoilerAlien [Elegy]', 4000, 1147, 0, 23),
(120, 11, 4, 'SpoilerX-Flow [Elegy]', 4000, 1146, 0, 23),
(121, 11, 5, 'WydechAlien [Flash]', 2000, 1046, 0, 23),
(122, 11, 5, 'WydechX-Flow [Flash]', 2000, 1045, 0, 23),
(123, 11, 5, 'ProgiAlien [Flash]', 3000, 1051, 0, 23),
(124, 11, 5, 'ProgiX-Flow [Flash]', 3000, 1052, 0, 23),
(125, 11, 5, 'ZderzakPAlien [Flash]', 4000, 1153, 0, 23),
(126, 11, 5, 'ZderzakPX-Flow [Flash]', 4000, 1152, 0, 23),
(127, 11, 5, 'ZderzakTAlien [Flash]', 4000, 1150, 0, 23),
(128, 11, 5, 'ZderzakTX-Flow [Flash]', 4000, 1151, 0, 23),
(129, 11, 5, 'WlotyAlien [Flash]', 4000, 1054, 0, 23),
(130, 11, 5, 'WlotyX-Flow [Flash]', 4000, 1053, 0, 23),
(131, 11, 5, 'SpoilerAlien [Flash]', 4000, 1049, 0, 23),
(132, 11, 5, 'SpoilerX-Flow [Flash]', 4000, 1050, 0, 23),
(133, 11, 6, 'Wydech [Upswept]', 2000, 1018, 0, 23),
(134, 11, 6, 'Wydech [Twin]', 2000, 1019, 0, 23),
(135, 11, 6, 'Wydech [Large]', 2000, 1020, 0, 23),
(136, 11, 6, 'Wydech [Medium]', 2000, 1021, 0, 23),
(137, 11, 6, 'Wydech [Small]', 2000, 1022, 0, 23),
(138, 11, 7, 'Spoiler [Pro]', 4000, 1000, 0, 23),
(139, 11, 7, 'Spoiler [Win]', 4000, 1001, 0, 23),
(140, 11, 7, 'Spoiler [Drag]', 4000, 1002, 0, 23),
(141, 11, 7, 'Spoiler [Alpha]', 4000, 1003, 0, 23),
(142, 11, 7, 'Spoiler [Champ]', 4000, 1014, 0, 23),
(143, 11, 7, 'Spoiler [Race]', 4000, 1015, 0, 23),
(144, 11, 7, 'Spoiler [Worx]', 4000, 1016, 0, 23),
(145, 11, 7, 'Spoiler [Fury]', 4000, 1023, 0, 23),
(146, 13, 0, 'Palka Teleskopowa', 500, 3, 1, 1),
(147, 13, 0, '9mm', 1500, 22, 100, 1),
(148, 13, 1, 'Cywilna kamizelka', 1000, 25, 0, 8),
(149, 13, 1, 'Ammo [9mm]', 500, 22, 100, 22),
(167, 19, 0, 'Papierosy', 30, 20, 0, 11),
(168, 19, 0, 'Kanister [5L]', 50, 5, 0, 10),
(169, 19, 0, 'Kanister [10L]', 90, 10, 0, 10),
(172, 19, 0, 'Zestaw naprawczy', 1000, 200, 0, 27),
(176, 1, 0, 'Palka Teleskopowa [USSS]', 500, 3, 1, 1),
(177, 1, 0, 'Granat Dymny [USSS]', 1500, 17, 3, 1),
(178, 1, 0, 'Desert Eagle [USSS]', 2500, 24, 100, 1),
(179, 1, 0, 'Shotgun [USSS]', 5000, 25, 100, 1),
(180, 1, 0, 'MP5 [USSS]', 7500, 29, 250, 1),
(181, 1, 0, 'AK-47 [USSS]', 10000, 30, 250, 1),
(182, 1, 0, 'M4 [USSS]', 12500, 31, 250, 1),
(183, 1, 0, 'Snajperka [USSS]', 20000, 34, 15, 1),
(184, 1, 0, 'Ammo [DE][USSS]', 500, 24, 100, 22),
(185, 1, 0, 'Ammo [Shotgun][USSS]', 750, 25, 100, 22),
(186, 1, 0, 'Ammo [MP5][USSS]', 1000, 29, 250, 22),
(187, 1, 0, 'Ammo [AK-47][USSS]', 1500, 30, 250, 22),
(188, 1, 0, 'Ammo [M4][USSS]', 1750, 31, 250, 22),
(189, 1, 0, 'Ammo [Snajperka][USSS]', 10000, 34, 10, 22),
(190, 1, 0, 'Krotkofalowka', 15, 1, 1, 18),
(191, 1, 0, 'Kominiarka', 50, 0, 0, 3),
(192, 1, 0, 'Megafon [USSS]', 200, 0, 0, 19),
(193, 1, 0, 'Lekka Kamizelka [USSS]', 550, 50, 0, 8),
(194, 1, 0, 'Ciezka Kamizelka [USSS]', 5000, 100, 0, 8),
(195, 3, 0, 'Krotkofalowka', 15, 1, 1, 18),
(197, 2, 2, 'Aparat', 200, 43, 200, 1),
(198, 22, 0, 'Kokaina', 90, 1, 1, 15),
(199, 22, 0, 'Heroina', 40, 1, 1, 16),
(200, 22, 0, 'LSD', 200, 1, 1, 17),
(201, 11, 1, 'Przyciemniane szyby', 8000, 1, 1, 29),
(202, 7, 0, 'Kastet', 50, 1, 1, 1),
(205, 8, 0, 'Baseball', 50, 5, 1, 1),
(206, 8, 0, 'Kastet', 50, 1, 1, 1),
(207, 8, 0, 'Noz', 100, 4, 1, 1),
(210, 9, 0, 'Kastet', 50, 1, 1, 1),
(211, 9, 0, 'Baseball', 50, 5, 1, 1),
(214, 22, 0, 'Kominiarka', 50, 0, 0, 3),
(215, 22, 0, 'Baseball', 50, 5, 1, 1),
(218, 22, 0, 'Noz', 100, 4, 1, 1),
(219, 22, 0, 'Kastet', 50, 1, 1, 1),
(222, 17, 0, 'Suplement typu A', 250, 1, 1, 20),
(223, 17, 0, 'Suplement typu B', 200, 2, 1, 20),
(224, 17, 0, 'Suplement typu C', 50, 3, 1, 20),
(225, 3, 0, 'Gasnica', 300, 42, 10000, 1),
(226, 18, 2, 'Papierosy', 10, 1, 20, 11),
(227, 18, 0, 'Jedzenie (10)', 10, 10, 1, 4),
(228, 18, 0, 'Jedzenie (20)', 20, 20, 1, 4),
(229, 18, 0, 'Jedzenie (30)', 30, 30, 1, 4),
(230, 18, 0, 'Jedzenie (50)', 50, 50, 1, 4),
(231, 18, 1, 'Alkohol', 10, 1, 1, 12),
(232, 18, 1, 'Napoj', 5, 0, 1, 4),
(233, 2, 2, 'Tarcza policyjna [LSPD]', 20, 18637, 6, 26),
(234, 2, 2, 'Kask policyjny [LSPD]', 20, 19141, 2, 26),
(235, 2, 2, 'Czapka policyjna (1) [LSPD]', 20, 19161, 2, 26),
(236, 2, 2, 'Czapka policyjna (2) [LSPD]', 20, 19162, 2, 26),
(237, 2, 2, 'Czapka policyjna (3) [LSPD]', 20, 18636, 2, 26),
(238, 2, 2, 'Kapelusz policyjny (1) [LSPD]', 20, 19099, 2, 26),
(239, 2, 2, 'Kapelusz policyjny (2) [LSPD]', 20, 19100, 2, 26),
(240, 23, 0, 'Alkohol', 10, 1, 1, 12),
(241, 23, 0, 'Napoj', 5, 0, 1, 4),
(242, 11, 0, 'Offroad', 3000, 1025, 0, 23),
(243, 11, 8, 'WydechChrome [Savanna]', 2000, 1129, 0, 23),
(244, 11, 8, 'DachHardTop [Savanna]', 3000, 1130, 0, 23),
(245, 11, 8, 'DachSoftTop [Savanna]', 3000, 1131, 0, 23),
(246, 11, 8, 'WydechSlamin [Savanna]', 2000, 1132, 0, 23),
(247, 11, 8, 'ProgiChromeStrip [Savanna]', 2000, 1102, 0, 23),
(248, 11, 8, 'ZderzakPSlamin [Savanna]', 2000, 1188, 0, 23),
(249, 11, 8, 'ZderzakTSlamin [Savanna]', 2000, 1186, 0, 23),
(250, 11, 8, 'ZderzakTChrome [Savanna]', 2000, 1187, 0, 23),
(251, 11, 8, 'ZderzakPChrome [Savanna]', 2000, 1189, 0, 23),
(252, 11, 9, 'DachConvertible [Blade]', 3000, 1103, 0, 23),
(253, 11, 9, 'WydechChrome [Blade]', 2000, 1104, 0, 23),
(254, 11, 9, 'WydechSlamin [Blade]', 2000, 1105, 0, 23),
(255, 11, 9, 'ProgiChromeStrip [Blade]', 2000, 1107, 0, 23),
(256, 11, 9, 'DachVinylHardTop [Blade]', 3000, 1128, 0, 23),
(257, 11, 9, 'ZderzakPSlamin [Blade]', 2000, 1181, 0, 23),
(258, 11, 9, 'ZderzakPChrome [Blade]', 2000, 1182, 0, 23),
(259, 11, 9, 'ZderzakTChrome [Blade]', 2000, 1184, 0, 23),
(260, 11, 9, 'ZderzakTSlamin [Blade]', 2000, 1183, 0, 23),
(261, 11, 10, 'WlotyAlien [Stratum]', 3000, 1055, 0, 23),
(262, 11, 10, 'SpoilerAlien [Stratum]', 2000, 1058, 0, 23),
(263, 11, 10, 'WydechX-Flow [Stratum]', 2000, 1059, 0, 23),
(264, 11, 10, 'SpoilerX-Flow [Stratum]', 2000, 1060, 0, 23),
(265, 11, 10, 'WlotyX-Flow [Stratum]', 3000, 1061, 0, 23),
(266, 11, 10, 'ProgiAlien [Stratum]', 2000, 1062, 0, 23),
(267, 11, 10, 'ProgiX-Flow [Stratum]', 2000, 1063, 0, 23),
(268, 11, 10, 'WydechAlien [Stratum]', 2000, 1064, 0, 23),
(269, 11, 10, 'ZderzakPAlien [Stratum]', 2000, 1155, 0, 23),
(270, 11, 10, 'ZderzakTAlien [Stratum]', 2000, 1154, 0, 23),
(271, 11, 10, 'ZderzakTX-Flow [Stratum]', 2000, 1156, 0, 23),
(272, 11, 10, 'ZderzakPX-Flow [Stratum]', 2000, 1157, 0, 23),
(273, 11, 11, 'WlotyAlien [Uranus]', 4000, 1088, 0, 23),
(274, 11, 11, 'WydechX-Flow [Uranus]', 3000, 1089, 0, 23),
(275, 11, 11, 'ProgiX-Flow [Uranus]', 3000, 1063, 0, 23),
(276, 11, 11, 'WlotyX-Flow [Uranus]', 4000, 1091, 0, 23),
(277, 11, 11, 'WydechAlien [Uranus]', 3000, 1092, 0, 23),
(278, 11, 11, 'ProgiAlien [Uranus]', 3000, 1094, 0, 23),
(279, 11, 11, 'SpoilerX-Flow [Uranus]', 3000, 1163, 0, 23),
(280, 11, 11, 'SpoilerAlien [Uranus]', 3000, 1164, 0, 23),
(281, 11, 11, 'ZderzakPX-Flow [Uranus]', 3000, 1165, 0, 23),
(282, 11, 11, 'ZderzakPAlien [Uranus]', 3000, 1166, 0, 23),
(283, 11, 11, 'ZderzakTX-Flow [Uranus]', 3000, 1167, 0, 23),
(284, 11, 11, 'ZderzakTAlien [Uranus]', 3000, 1168, 0, 23),
(285, 11, 12, 'BullbarsTChrome [Slamvan]', 3000, 1109, 0, 23),
(286, 11, 12, 'BullbarsTSlamin [Slamvan]', 3000, 1110, 0, 23),
(287, 11, 12, 'WydechChrome [Slamvan]', 2000, 1113, 0, 23),
(288, 11, 12, 'WydechSlamin [Slamvan]', 2000, 1114, 0, 23),
(289, 11, 12, 'BullbarsPChrome [Slamvan]', 3000, 1115, 0, 23),
(290, 11, 12, 'BullbarsPSlamin [Slamvan]', 3000, 1116, 0, 23),
(291, 11, 12, 'ZderzakPChrome [Slamvan]', 2000, 1117, 0, 23),
(292, 11, 12, 'ProgiChromeTrim [Slamvan]', 2000, 1120, 0, 23),
(293, 11, 12, 'ProgiWheelCovers [Slamvan]', 2000, 1121, 0, 23),
(294, 11, 13, 'BullbarsChromeBars [Remington]', 3000, 1123, 0, 23),
(295, 11, 13, 'ProgiChromeArches [Remington]', 2000, 1124, 0, 23),
(296, 11, 13, 'BullbarsChromeLights [Remington]', 3000, 1125, 0, 23),
(297, 11, 13, 'WydechChrome [Remington]', 2000, 1126, 0, 23),
(298, 11, 13, 'WydechSlamin [Remington]', 2000, 1127, 0, 23),
(299, 11, 13, 'ZderzakTSlamin [Remington]', 2000, 1178, 0, 23),
(300, 11, 13, 'ZderzakPChrome [Remington]', 2000, 1179, 0, 23),
(301, 11, 13, 'ZderzakTChrome [Remington]', 2000, 1180, 0, 23),
(302, 11, 13, 'ZderzakPSlamin [Remington]', 2000, 1185, 0, 23),
(303, 11, 13, 'BullbarsChromeGrill [Remington]', 3000, 1100, 0, 23),
(304, 11, 13, 'ProgiChromeFlames [Remington]', 2000, 1101, 0, 23),
(305, 11, 14, 'WydechSlamin [Tornado]', 2000, 1135, 0, 23),
(306, 11, 14, 'WydechChrome [Tornado]', 2000, 1136, 0, 23),
(307, 11, 14, 'ProgiChromeStrip [Tornado]', 2000, 1137, 0, 23),
(308, 11, 14, 'ZderzakPSlamin [Tornado]', 2000, 1190, 0, 23),
(309, 11, 14, 'ZderzakPChrome [Tornado]', 2000, 1191, 0, 23),
(310, 11, 14, 'ZderzakTChrome [Tornado]', 2000, 1192, 0, 23),
(311, 11, 14, 'ZderzakTSlamin [Tornado]', 2000, 1193, 0, 23),
(312, 11, 15, 'WydechSlamin [Broadway]', 2000, 1043, 0, 23),
(313, 11, 15, 'WydechChrome [Broadway]', 2000, 1044, 0, 23),
(314, 11, 15, 'ProgiChrome [Broadway]', 2000, 1099, 0, 23),
(315, 11, 15, 'ZderzakPChrome [Broadway]', 2000, 1174, 0, 23),
(316, 11, 15, 'ZderzakPSlamin [Broadway]', 2000, 1175, 0, 23),
(317, 11, 15, 'ZderzakTChrome [Broadway]', 2000, 1176, 0, 23),
(318, 11, 15, 'ZderzakTSlamin [Broadway]', 2000, 1177, 0, 23),
(319, 7, 0, 'Noz', 100, 4, 1, 1),
(320, 9, 0, 'Noz', 100, 4, 1, 1),
(321, 24, 0, 'Cywilna kamizelka [L]', 1000, 25, 1, 8),
(322, 24, 0, 'Baseball [L]', 200, 5, 1, 1),
(323, 24, 0, 'Gaz pieprzowy [L]', 200, 41, 200, 1),
(324, 24, 0, '9mm [L]', 2000, 22, 50, 1),
(325, 24, 0, 'Desert Eagle [L]', 4800, 24, 50, 1),
(326, 24, 0, 'Shotgun [L]', 6800, 25, 30, 1),
(327, 24, 0, 'Sawnoff [L]', 6500, 26, 30, 1),
(328, 24, 0, 'Tlumik [9mm][L]', 2000, 0, 0, 24),
(329, 24, 0, 'Ammo [9mm][L]', 200, 22, 50, 22),
(330, 24, 0, 'Ammo [DE][L]', 300, 24, 50, 22),
(331, 24, 0, 'Ammo [Shotgun][L]', 400, 25, 30, 22),
(332, 24, 0, 'Ammo [Sawnoff][L]', 350, 26, 30, 22),
(333, 8, 0, '9mm', 2000, 22, 50, 1),
(334, 8, 0, 'Shotgun', 7000, 25, 20, 1),
(335, 8, 0, 'TEC9', 3500, 32, 60, 1),
(336, 8, 0, 'Micro SMG', 3500, 28, 60, 1),
(337, 8, 0, 'Ammo 9mm', 300, 22, 50, 22),
(338, 8, 0, 'Ammo Shotgun', 500, 25, 30, 22),
(339, 8, 0, 'Ammo SMG', 300, 28, 75, 22),
(340, 8, 0, 'Ammo TEC9', 300, 32, 75, 22);

--
-- Zrzut danych tabeli `srv_salon_vehicles`
--

INSERT INTO `srv_salon_vehicles` (`category`, `model`, `name`, `price`) VALUES
(3, 400, 'Landstalker', 30000),
(1, 401, 'Bravura', 7200),
(5, 402, 'Buffalo', 102300),
(2, 404, 'Perenniel', 11700),
(2, 405, 'Sentinel', 46200),
(1, 410, 'Manana', 5800),
(5, 411, 'Infernus', 360000),
(1, 412, 'Voodoo', 7800),
(4, 413, 'Pony', 19200),
(5, 415, 'Cheetah', 246000),
(2, 418, 'Moonbeam', 21000),
(1, 419, 'Esperanto', 13200),
(2, 421, 'Washington', 42000),
(4, 422, 'Bobcat', 12000),
(2, 426, 'Premier', 31200),
(5, 429, 'Banshee', 228000),
(1, 436, 'Previon', 8600),
(1, 439, 'Stallion', 36000),
(4, 440, 'Rumpo', 14400),
(2, 445, 'Admiral', 10000),
(5, 451, 'Turismo', 300000),
(2, 458, 'Solair', 9600),
(0, 461, 'PCJ-600', 16800),
(0, 462, 'Faggio', 1800),
(0, 463, 'Freeway', 12000),
(2, 466, 'Glendale', 9600),
(2, 467, 'Oceanic', 8400),
(0, 468, 'Sanchez', 10800),
(3, 471, 'Quad', 18000),
(1, 474, 'Hermes', 19200),
(1, 475, 'Sabre', 40800),
(5, 477, 'ZR-350', 98700),
(4, 478, 'Walton', 9600),
(2, 479, 'Regina', 11400),
(5, 480, 'Comet', 117600),
(0, 481, 'BMX', 360),
(4, 482, 'Burrito', 24000),
(2, 483, 'Camper', 47400),
(3, 489, 'Rancher', 33600),
(1, 491, 'Virgo', 17200),
(2, 492, 'Greenwood', 6400),
(1, 496, 'Blista Compact', 16200),
(4, 498, 'Boxville', 28500),
(4, 499, 'Benson', 31700),
(3, 500, 'Mesa', 26400),
(5, 506, 'Super GT', 112400),
(2, 507, 'Elegant', 33000),
(3, 508, 'Journey', 26400),
(0, 509, 'Bike', 420),
(0, 510, 'Mountain Bike', 480),
(2, 516, 'Nebula', 14400),
(1, 517, 'Majestic', 6300),
(1, 518, 'Buccaner', 13200),
(0, 521, 'FCR-900', 28800),
(1, 526, 'Fortune', 8500),
(1, 527, 'Cadrona', 9900),
(2, 529, 'Willard', 21600),
(1, 533, 'Feltzer', 45200),
(1, 534, 'Remington', 25200),
(1, 535, 'Slamvan', 38400),
(1, 536, 'Blade', 25200),
(2, 540, 'Vincent', 24000),
(5, 541, 'Bullet', 276000),
(1, 542, 'Clover', 4500),
(4, 543, 'Sadler', 16800),
(2, 546, 'Intruder', 12600),
(2, 547, 'Primo', 10800),
(1, 549, 'Tampa', 4800),
(2, 550, 'Sunrise', 15000),
(2, 551, 'Merit', 46700),
(3, 554, 'Yosemite', 50400),
(5, 555, 'Windsor', 38400),
(5, 558, 'Uranus', 54000),
(5, 559, 'Jester', 81600),
(5, 560, 'Sultan', 132000),
(2, 561, 'Stratum', 20400),
(5, 562, 'Elegy', 125700),
(5, 565, 'Flash', 46800),
(2, 566, 'Tahoma', 13200),
(2, 567, 'Savanna', 14400),
(1, 575, 'Broadway', 20400),
(1, 576, 'Tornado', 8400),
(3, 579, 'Huntley', 38400),
(2, 580, 'Stafford', 50400),
(0, 581, 'BF-400', 21600),
(2, 585, 'Emperor', 19800),
(0, 586, 'Wayfarer', 7200),
(5, 587, 'Euros', 42600),
(1, 589, 'Club', 14800),
(1, 600, 'Picador', 14400),
(5, 602, 'Alpha', 45000),
(5, 603, 'Phoenix', 39600);

--
-- Zrzut danych tabeli `srv_weapons_magazine`
--

INSERT INTO `srv_weapons_magazine` (`uid`, `category`, `name`, `type`, `value1`, `value2`, `price`) VALUES
(1, 0, '9mm', 1, 22, 50, 1500),
(2, 1, 'Ammo [9mm]', 22, 22, 50, 200),
(3, 0, 'Desert Eagle', 1, 24, 50, 2500),
(4, 1, 'Ammo [DE]', 22, 24, 50, 300),
(5, 0, 'Shotgun', 1, 25, 30, 5500),
(6, 1, 'Ammo [Shotgun]', 22, 25, 30, 400),
(7, 0, 'Sawnoff', 1, 26, 30, 5000),
(8, 1, 'Ammo [Sawnoff]', 22, 26, 30, 350),
(9, 0, 'Micro SMG', 1, 28, 150, 3000),
(10, 1, 'Ammo [Micro SMG]', 22, 28, 75, 200),
(11, 0, 'MP5', 1, 29, 150, 7500),
(12, 1, 'Ammo [MP5]', 22, 29, 75, 400),
(13, 0, 'AK-47', 1, 30, 250, 10000),
(14, 1, 'Ammo [AK-47]', 22, 30, 125, 500),
(15, 0, 'M4', 1, 31, 250, 12000),
(16, 1, 'Ammo [M4]', 22, 31, 125, 500),
(17, 0, 'TEC9', 1, 32, 150, 2000),
(18, 1, 'Ammo [TEC9]', 22, 32, 75, 200),
(19, 0, 'Snajperka', 1, 34, 20, 35000),
(20, 1, 'Ammo [Snajperka]', 22, 34, 10, 700),
(21, 0, 'Granat Dymny', 1, 17, 3, 500),
(22, 0, 'Noz', 1, 4, 1, 100),
(23, 0, 'Baseball', 1, 5, 1, 50),
(25, 1, 'Kominiarka', 3, 0, 0, 50),
(26, 1, 'Cywilna kamizelka', 8, 25, 0, 1000),
(27, 0, 'Katana', 1, 8, 1, 400),
(28, 0, 'Kastet', 1, 1, 1, 50),
(29, 0, 'Tlumik [9mm]', 24, 0, 0, 2000),
(30, 1, 'Lekka kamizelka', 8, 50, 0, 3000);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;


--
-- Ograniczenia dla tabeli `srv_descriptions`
--
ALTER TABLE `srv_descriptions`
ADD CONSTRAINT `srv_descriptions_ibfk_1` FOREIGN KEY (`owneruid`) REFERENCES `srv_characters` (`player_uid`) ON DELETE CASCADE ON UPDATE NO ACTION;

--
-- Ograniczenia dla tabeli `srv_descriptions_text`
--
ALTER TABLE `srv_descriptions_text`
ADD CONSTRAINT `srv_descriptions_text_ibfk_1` FOREIGN KEY (`UID`) REFERENCES `srv_descriptions` (`UID`) ON DELETE CASCADE ON UPDATE NO ACTION;

--
-- Ograniczenia dla tabeli `srv_doors_members`
--
ALTER TABLE `srv_doors_members`
ADD CONSTRAINT `srv_doors_members_ibfk_1` FOREIGN KEY (`UID`) REFERENCES `srv_doors` (`UID`) ON DELETE CASCADE ON UPDATE NO ACTION,
ADD CONSTRAINT `srv_doors_members_ibfk_2` FOREIGN KEY (`player_uid`) REFERENCES `srv_characters` (`player_uid`) ON DELETE CASCADE ON UPDATE NO ACTION;

--
-- Ograniczenia dla tabeli `srv_fuel_stations`
--
ALTER TABLE `srv_fuel_stations`
ADD CONSTRAINT `srv_fuel_stations_ibfk_1` FOREIGN KEY (`owner`) REFERENCES `srv_groups` (`UID`) ON DELETE CASCADE ON UPDATE NO ACTION;

--
-- Ograniczenia dla tabeli `srv_groups_members`
--
ALTER TABLE `srv_groups_members`
ADD CONSTRAINT `srv_groups_members_ibfk_1` FOREIGN KEY (`group_uid`) REFERENCES `srv_groups` (`UID`) ON DELETE CASCADE ON UPDATE NO ACTION,
ADD CONSTRAINT `srv_groups_members_ibfk_2` FOREIGN KEY (`player_uid`) REFERENCES `srv_characters` (`player_uid`) ON DELETE CASCADE ON UPDATE NO ACTION;

--
-- Ograniczenia dla tabeli `srv_group_offer_logs`
--
ALTER TABLE `srv_group_offer_logs`
ADD CONSTRAINT `srv_group_offer_logs_ibfk_1` FOREIGN KEY (`groupid`) REFERENCES `srv_groups` (`UID`) ON DELETE CASCADE ON UPDATE NO ACTION;

--
-- Ograniczenia dla tabeli `srv_legal_weapons`
--
ALTER TABLE `srv_legal_weapons`
ADD CONSTRAINT `srv_legal_weapons_ibfk_1` FOREIGN KEY (`weapuid`) REFERENCES `srv_items` (`UID`) ON DELETE CASCADE ON UPDATE NO ACTION;

--
-- Ograniczenia dla tabeli `srv_mmat_text`
--
ALTER TABLE `srv_mmat_text`
ADD CONSTRAINT `srv_mmat_text_ibfk_1` FOREIGN KEY (`object_id`) REFERENCES `srv_objects` (`uid`) ON DELETE CASCADE ON UPDATE NO ACTION;

--
-- Ograniczenia dla tabeli `srv_orders`
--
ALTER TABLE `srv_orders`
ADD CONSTRAINT `srv_orders_ibfk_1` FOREIGN KEY (`door_uid`) REFERENCES `srv_doors` (`UID`) ON DELETE CASCADE ON UPDATE NO ACTION;

--
-- Ograniczenia dla tabeli `srv_tuning`
--
ALTER TABLE `srv_tuning`
ADD CONSTRAINT `srv_tuning_ibfk_1` FOREIGN KEY (`vehicle`) REFERENCES `srv_vehicles` (`UID`) ON DELETE CASCADE ON UPDATE NO ACTION;

--
-- Ograniczenia dla tabeli `srv_vcards`
--
ALTER TABLE `srv_vcards`
ADD CONSTRAINT `srv_vcards_ibfk_1` FOREIGN KEY (`phone_uid`) REFERENCES `srv_items` (`UID`) ON DELETE CASCADE ON UPDATE NO ACTION;

INSERT INTO `srv_settings` (`status`, `spawnx`, `spawny`, `spawnz`, `spawn_angle`, `magazinex`, `magaziney`, `magazinez`, `premiumeventdays`, `lsnprice`, `doc_id`, `doc_driver`, `doc_pilot`, `fuel_cost`, `hotelPrice`, `insurance`, `taxes`, `platecharge`, `registercharge`, `doc_weapon`, `doc_med`, `HealPrice`, `sannpay`) VALUES
(1, 1479.42, -1676.7, 14.0469, 180, 2271.55, -2343.38, 13.5469, 0, 1111, 1000, 5000, 2, 1000, 40, 5, 100, 2000, 10000, 100, 100, 150, 2999);

ALTER TABLE `members` ADD `score` INT NOT NULL ,
ADD `premium` INT NOT NULL ,
ADD `warn` TINYINT NOT NULL ,
ADD `curse` INT NOT NULL ,
ADD `aj` INT NOT NULL ,
ADD `panel_perm` INT NOT NULL ;

DELETE FROM `groups` WHERE 1;
ALTER TABLE `groups` AUTO_INCREMENT=1;
INSERT INTO `groups` (`g_id`, `g_view_board`, `g_mem_info`, `g_other_topics`, `g_use_search`, `g_edit_profile`, `g_post_new_topics`, `g_reply_own_topics`, `g_reply_other_topics`, `g_edit_posts`, `g_delete_own_posts`, `g_open_close_posts`, `g_delete_own_topics`, `g_post_polls`, `g_vote_polls`, `g_use_pm`, `g_is_supmod`, `g_access_cp`, `g_title`, `g_append_edit`, `g_access_offline`, `g_avoid_q`, `g_avoid_flood`, `g_icon`, `g_attach_max`, `prefix`, `suffix`, `g_max_messages`, `g_max_mass_pm`, `g_search_flood`, `g_edit_cutoff`, `g_promotion`, `g_hide_from_list`, `g_post_closed`, `g_perm_id`, `g_photo_max_vars`, `g_dohtml`, `g_edit_topic`, `g_bypass_badwords`, `g_can_msg_attach`, `g_attach_per_post`, `g_topic_rate_setting`, `g_dname_changes`, `g_dname_date`, `g_mod_preview`, `g_rep_max_positive`, `g_rep_max_negative`, `g_signature_limits`, `g_can_add_friends`, `g_hide_online_list`, `g_bitoptions`, `g_pm_perday`, `g_mod_post_unit`, `g_ppd_limit`, `g_ppd_unit`, `g_displayname_unit`, `g_sig_unit`, `g_pm_flood_mins`, `g_max_notifications`, `g_max_bgimg_upload`) VALUES
(NULL, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'OczekujÄ™ na aktywacjÄ™', 1, 0, 0, 0, '', 0, '<span style=''color:#3E4F73''>', '</span>', 50, 0, 20, 0, '-1&-1', 0, 0, '1', '50:150:150', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '0:1::::', 0, 0, 66977824, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(NULL, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'GoÅ›Ä‡', 0, 0, 0, 0, '', -1, '', '', 50, 0, 20, 0, '-1&-1', 0, 0, '2', '50:150:150', 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, '0:::::', 1, 0, 33423360, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(NULL, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 'UÅ¼ytkownik', 0, 0, 0, 0, '', 1000, '<span style=''color:#3E4F73''>', '</span>', 50, 5, 0, 0, '-1&-1', 0, 0, '3', '500:400:400', 0, 1, 0, 0, 0, 1, 1, 30, 0, 20, 0, '0:1::::', 1, 0, 27197568, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(NULL, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 'Administrator GÅ‚Ã³wny', 1, 1, 1, 1, '', 0, '<span style=''color:red;''>', '</span>', 0, 50, 0, 5, '-1&-1', 0, 1, '4', '500:170:240', 1, 1, 1, 1, 0, 2, 0, 30, 0, 100, 100, '0:::::', 1, 0, 27197568, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(NULL, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 'Zbanowany', 0, 0, 0, 0, '', 0, '<s>', '</s>', 50, 0, 20, 0, '-1&-1', 1, 0, '5', '50:150:150', 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, '1:::::', 0, 0, 32505888, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(NULL, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 'Moderator', 1, 1, 1, 1, '', 1000, '<span style=''color:green;''>', '</span>', 50, 5, 0, 0, '-1&-1', 0, 1, '6', '100:150:150', 1, 1, 1, 0, 0, 2, 3, 30, 0, 100, 10, '0:1::::', 1, 0, 27197568, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(NULL, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 'Administrator', 1, 1, 1, 1, '', 0, '<span style=''color:#C90000;''>', '</span>', 0, 50, 0, 5, '-1&-1', 0, 1, '4', '100:170:240', 1, 1, 1, 1, 0, 2, 3, 30, 0, 100, 100, '0:::::', 1, 0, 27197568, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(NULL, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 'GameMaster', 1, 1, 1, 1, '', 1000, '<span style=''color:purple''>', '</span>', 0, 20, 0, 0, '-1&-1', 0, 1, '7', '100:150:150', 0, 1, 1, 0, 0, 2, 0, 30, 0, 10, 1, '0:1::::', 1, 0, 27197568, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(NULL, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 'Premium', 0, 0, 0, 0, '', 1000, '<span style=''color:#3E4F73''><img src="http://i.imgur.com/qHJj3Tl.png" width="12px" style="margin:-5px 2px 0px 0px">', '</span>', 200, 30, 0, 0, '-1&-1', 0, 0, '8', '2048:800:800', 0, 1, 0, 0, 0, 1, 3, 30, 0, 20, 0, '0:1::::', 1, 0, 27197568, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(NULL, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 'ZasÅ‚uÅ¼ony', 0, 0, 0, 1, '', 1000, '<span style=''color:#18946A''>', '</span>', 500, 20, 0, 0, '-1&-1', 0, 0, '3', '100:150:150', 0, 1, 0, 0, 0, 1, 3, 30, 0, 10, 1, '0:1::::', 1, 0, 27197568, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(NULL, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 'Opiekun Org. PrzestÄ™pczych', 1, 1, 1, 1, '', 1000, '<span style=''color:#E67A00''>', '</span>', 0, 20, 0, 0, '-1&-1', 0, 1, '9,3,12', '100:150:150', 1, 1, 0, 0, 0, 1, 3, 30, 0, 10, 1, '0:1::::', 1, 0, 27197568, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(NULL, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 'Tester', 1, 1, 0, 0, '', 1000, '<span style=''color:#3E4F73''>', '</span>', 50, 5, 0, 0, '-1&-1', 0, 0, '10', '500:400:400', 0, 1, 0, 0, 0, 1, 3, 30, 0, 10, 1, '0:1::::', 1, 0, 27197440, 0, 0, 0, 0, 0, 0, 0, 0, 0);


/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

CREATE TABLE `srv_actors` (
  `uid` int(11) NOT NULL,
  `name` varchar(32) NOT NULL,
  `skin` smallint(5) unsigned NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `vw` smallint(5) unsigned NOT NULL,
  `angle` float NOT NULL,
  `anim` smallint(6) NOT NULL,
  PRIMARY KEY (`uid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `srv_skins` (
`ID` int(11) NOT NULL,
`type` int(11) NOT NULL,
`uid` int(11) NOT NULL,
`model` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `srv_skins`
ADD PRIMARY KEY (`ID`);

ALTER TABLE `srv_skins`
MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;
