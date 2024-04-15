-- chat.user_messages определение

CREATE TABLE `user_messages` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `message_date` date DEFAULT NULL,
  `message_from` varchar(100) NOT NULL,
  `message_to` varchar(100) DEFAULT NULL,
  `message` varchar(1024) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;