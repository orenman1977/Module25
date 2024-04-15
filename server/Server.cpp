#include "Server.h"
#include "../share/opcodes.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace mychat {
    Server::Server() : db_(new WorkDB()), gateway_(new SocketStream())
    {}

    Server::Server(WorkDB* db, SocketStream* ss) : db_(db), gateway_(ss)
    {}

    Server::~Server()
    {
        delete db_;
        delete gateway_;
        std::cout << "~Server()\n";
    }

    // ждЄт прихода данных и по коду операции вызывает нужный метод Ѕƒ
    int Server::start()
    {
        int status = 0;
        User* user{ nullptr };
        Message* message{ nullptr };
        std::time_t t{ 0 };
        std::tm* tm{ nullptr };
        std::ostringstream osstr;

        //÷икл сервера
        while (1) {
            if (gateway_->receiving()) continue;      // указатель на массив char
            char* packageData = gateway_->getResponse();
            size_t packageLenght = gateway_->getResponseLenght();

            std::cout << "ResponseLenght = " << packageLenght << '\n';
            std::cout << "ResponseData = ";
            std::cout.write(packageData, packageLenght) << '\n';

            // выбор по коду операции
            switch (packageData[0])
            {
            case login:
                // запрос клиента <код:char><user_name:string><messageSeparator:char><hashLenght:int32_t><hash:string>
                user = new User(&packageData[1]);
                status = db_->userLogin(user);
                if (status == 0) {
                    gateway_->sending(&good, 1);
                    // истори€ сообщений чата без учЄта личные\общие
                    std::vector<std::string>* mh = db_->messageHistory(user);
                    for (auto& it : *mh) {
                        std::cout << it << '\n';
                        message = new Message(it.data());                           // заполн€ю Message через конструктор Message(char*)
                        message->messageShow(); std::cout << '\n';
                        gateway_->sending(message->getRawData()->data(), message->getRawData()->size());                        
                        delete message;
                        gateway_->receiving();                        
                    }                    
                    gateway_->sending(&end_of_data_transmission, 1);
                }
                if (status == 1) gateway_->sending(&bad, 1);
                break;

            case registration:
                user = new User(&packageData[1]);
                status = db_->userRegister(user);
                switch (status)
                {
                case 0:
                    gateway_->sending(&good, 1);
                    break;
                case 1:
                    gateway_->sending(&bad, 1);
                    break;
                case 2:
                    gateway_->sending(&user_exists, 1);
                    break;
                default:
                    std::cout << "Unhandle argument \n";
                    break;
                }
                break;

                // <код><name_from><messageSeparator><space><messageSeparator><message><messageSeparator>
            case shareMessage:
                t = std::time(nullptr);
                tm = std::localtime(&t);
                osstr << std::put_time(tm, "%d-%m-%Y") << ' ' << std::put_time(tm, "%H.%M") << messageSeparator << std::string(&packageData[1], packageLenght - 1);
                message = new Message(osstr.str().data());
                if (*message->getMessage() == "server exit") return 0;
                db_->storeMessage(message);
                osstr.str("");
                delete message;
                break;

                // <код><name_from><messageSeparator><name_to><messageSeparator><message><messageSeparator>
            case privatMessage:
                t = std::time(nullptr);
                tm = std::localtime(&t);
                osstr << std::put_time(tm, "%d-%m-%Y") << ' ' << std::put_time(tm, "%H.%M") << messageSeparator << std::string(&packageData[1], packageLenght - 1);
                message = new Message(osstr.str().data());
                if (*message->getMessage() == "server exit") return 0;
                db_->storeMessage(message);
                osstr.str("");
                delete message;
                break;

            default:
                std::cout << "Unhandle argument \n";
                break;
            }
        }
        return 0;
    }
}

