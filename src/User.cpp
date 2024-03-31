#include "User.hpp"

user::user(std::string uid, 
           std::string name, 
           std::string user_info)
{
	_uid = uid;
	_user_info = user_info;
	_name = name;
}
