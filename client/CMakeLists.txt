#
cmake_minimum_required (VERSION 3.16)
project ("ChatClient" DESCRIPTION "Клиент чата по материалам Skillfactory" LANGUAGES C CXX)

# цели
add_executable (${PROJECT_NAME} "main.cpp" "ConnectionTCPclient.h" "ConnectionTCPclient.cpp" "StreamTCP.h" "StreamTCP.cpp"  "Chat.h" "Chat.cpp"  
	"../share/opcodes.h" "../share/User.h" "../share/User.cpp" "../share/Message.h" "../share/Message.cpp" 
	"../share/IHasher.h" "../share/sha1.h" "../share/sha1.cpp" "../share/IConnection.h" "../share/IStream.h")

if(UNIX)
	message("Это Линукс")
elseif(WIN32)
	message("Это Windows! Нужен Линукс")
endif()