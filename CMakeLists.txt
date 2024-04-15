cmake_minimum_required (VERSION 3.16)

project ("Itog" DESCRIPTION "Чат по материалам Skillfactory" LANGUAGES C CXX)

# Включите подпроекты.
add_subdirectory ("client")
add_subdirectory("server")
