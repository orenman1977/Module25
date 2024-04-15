#
cmake_minimum_required (VERSION 3.16)
project ("ChatServer" DESCRIPTION "Backend чата по материалам Skillfactory" LANGUAGES C CXX)

# цели
add_executable(${PROJECT_NAME} "main.cpp"  "ConnectionTCPserver.h" "ConnectionTCPserver.cpp" "WorkDB.h" "WorkDB.cpp" "SocketStream.h" "SocketStream.cpp" "Server.h" "Server.cpp" 
	"../share/opcodes.h" "../share/User.h" "../share/User.cpp" "../share/Message.h" "../share/Message.cpp" 
	"../share/IHasher.h" "../share/sha1.h" "../share/sha1.cpp" "../share/IConnection.h" "../share/IStream.h")

if(UNIX)
	target_include_directories(${PROJECT_NAME} PUBLIC /usr/include/mysql ../share)
	target_link_libraries(${PROJECT_NAME} PUBLIC -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lzstd -lssl -lcrypto -lresolv -lm)
elseif(WIN32)
	message("Нужен Линукс")
endif()