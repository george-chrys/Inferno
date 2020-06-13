-- phpMyAdmin SQL Dump
-- version 5.0.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 13, 2020 at 04:27 PM
-- Server version: 10.4.11-MariaDB
-- PHP Version: 7.4.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `infernodb`
--

-- --------------------------------------------------------

--
-- Table structure for table `friendreq`
--

CREATE TABLE `friendreq` (
  `reqsender` int(11) NOT NULL,
  `reqreceiver` int(11) NOT NULL,
  `reqstatus` enum('accepted','rejected','pending') NOT NULL DEFAULT 'pending',
  `requestid` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `friendreq`
--

INSERT INTO `friendreq` (`reqsender`, `reqreceiver`, `reqstatus`, `requestid`) VALUES
(1, 12, 'accepted', 1),
(9, 10, 'rejected', 3),
(10, 14, 'rejected', 6),
(15, 16, 'accepted', 8),
(15, 10, 'accepted', 9),
(5, 3, 'pending', 11),
(5, 4, 'pending', 12),
(5, 9, 'accepted', 13),
(9, 4, 'pending', 14),
(9, 8, 'accepted', 15),
(9, 11, 'pending', 16),
(1, 15, 'pending', 17),
(1, 8, 'accepted', 19),
(17, 14, 'pending', 21),
(17, 15, 'pending', 22),
(17, 8, 'pending', 23),
(17, 7, 'pending', 24),
(16, 17, 'accepted', 25),
(16, 14, 'pending', 26),
(16, 11, 'pending', 27),
(16, 4, 'pending', 28),
(15, 14, 'pending', 29),
(15, 12, 'accepted', 31),
(15, 3, 'pending', 32),
(15, 13, 'pending', 33),
(15, 7, 'pending', 34),
(14, 16, 'accepted', 35),
(14, 17, 'accepted', 36),
(14, 5, 'accepted', 37),
(14, 10, 'accepted', 38),
(14, 13, 'pending', 39),
(11, 3, 'pending', 40),
(11, 5, 'accepted', 41),
(11, 8, 'accepted', 42),
(11, 10, 'pending', 43),
(11, 12, 'pending', 44),
(11, 15, 'pending', 45),
(8, 4, 'pending', 46),
(8, 7, 'pending', 47),
(8, 9, 'accepted', 48),
(8, 13, 'pending', 49),
(8, 14, 'pending', 50),
(8, 17, 'pending', 51),
(13, 4, 'pending', 52),
(13, 5, 'accepted', 53),
(13, 11, 'pending', 54),
(13, 12, 'accepted', 55),
(13, 16, 'accepted', 56),
(13, 7, 'pending', 57),
(13, 9, 'pending', 58),
(15, 7, 'pending', 59),
(1, 10, 'accepted', 77),
(472, 1, 'accepted', 78);

-- --------------------------------------------------------

--
-- Table structure for table `posts`
--

CREATE TABLE `posts` (
  `wallid` int(11) NOT NULL,
  `postid` int(11) NOT NULL,
  `writer` varchar(255) NOT NULL,
  `message` varchar(255) NOT NULL,
  `likes` int(11) DEFAULT 0,
  `postdate` date DEFAULT curdate()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `posts`
--

INSERT INTO `posts` (`wallid`, `postid`, `writer`, `message`, `likes`, `postdate`) VALUES
(1, 38, 'a a', 'this is not happening', 0, '2020-06-11'),
(8, 40, 'a a', 'hey lydia! I solved the proble with getline(). Call me when you see this', 1, '2020-06-11'),
(12, 41, 'Lily Rose', 'goodmorning everyone!', 0, '2020-06-11'),
(14, 42, 'Reggina Bull', 'happy birthday travis', 0, '2020-06-13');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `firstName` varchar(20) NOT NULL,
  `lastName` varchar(20) NOT NULL,
  `password` int(10) NOT NULL,
  `status` tinyint(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `firstName`, `lastName`, `password`, `status`) VALUES
(1, 'a', 'a', 0, 0),
(3, 'Josh ', 'Dewars', 32145, 0),
(4, 'Evelyn', 'Tullamore', 3456, 0),
(5, 'Peter', 'Grouse', 6724, 0),
(7, 'Arthur', 'Haig', 3535, 0),
(8, 'Lydia ', 'Vat', 7356, 0),
(9, 'Patrick', 'Jameson', 1235, 0),
(10, 'Robert', 'Bushmills', 7903, 0),
(11, 'Agatha', 'Teachers', 12347, 0),
(12, 'Lily', 'Rose', 7824, 0),
(13, 'Charlie', 'Daniels', 23468, 0),
(14, 'Travis', 'Gordon', 1245, 0),
(15, 'Brenda', 'Hendricks', 3579, 0),
(16, 'Reggina', 'Bull', 2353, 0),
(17, 'Aaron', 'Beefeater', 5615, 0);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `friendreq`
--
ALTER TABLE `friendreq`
  ADD PRIMARY KEY (`requestid`);

--
-- Indexes for table `posts`
--
ALTER TABLE `posts`
  ADD PRIMARY KEY (`postid`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `friendreq`
--
ALTER TABLE `friendreq`
  MODIFY `requestid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=79;

--
-- AUTO_INCREMENT for table `posts`
--
ALTER TABLE `posts`
  MODIFY `postid` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=43;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=473;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
