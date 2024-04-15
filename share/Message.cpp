/*
    Класс сообщение
*/
#include "Message.h"
#include "opcodes.h"
#include <iostream>

namespace mychat {
    Message::Message
    (
        const std::string& message_date,
        const std::string& message_from,
        const std::string& message_to,
        const std::string& message
    ) : message_{ message_date, message_from, message_to, message }
    {
        messageRaw();
    }

    Message::Message(char* messageData)
    {
        while (*messageData != messageSeparator) {
            message_.message_date.push_back(*messageData);
            messageData += 1;
        }
        messageData += 1;
        while (*messageData != messageSeparator) {
            message_.message_from.push_back(*messageData);
            messageData += 1;
        }
        messageData += 1;
        while (*messageData != messageSeparator) {
            message_.message_to.push_back(*messageData);
            messageData += 1;
        }
        messageData += 1;
        while (*messageData != messageSeparator) {
            message_.message.push_back(*messageData);
            messageData += 1;
        }
        messageRaw();
    }

    Message::~Message()
    {
        //std::cout << "~Message()\n";
    }

    std::string* Message::getFrom()
    {
        return &message_.message_from;
    }
    std::string* Message::getTo()
    {
        return &message_.message_to;
    }
    std::string* Message::getMessage()
    {
        return &message_.message;
    }
    std::string* Message::getDate()
    {
        return &message_.message_date;
    }

    std::string* Message::getRawData() {
        return &rawData_;
    }

    void Message::setFrom(std::string& str)
    {
        message_.message_from = str;
    }
    void Message::setTo(std::string& str)
    {
        message_.message_to = str;
    }
    void Message::setMessage(std::string& str)
    {
        message_.message = str;
    }
    void Message::setDate(std::string& str)
    {
        message_.message_date = str;
    }
    void Message::messageShow()
    {
        std::cout << "date: " << message_.message_date << "\nfrom: " << message_.message_from << "\nto: " << message_.message_to << "\nmessage: " << message_.message << '\n';
    }
    void Message::messageRaw()
    {
        rawData_ = message_.message_date + messageSeparator + message_.message_from + messageSeparator + message_.message_to + messageSeparator + message_.message + messageSeparator;
    }
}

