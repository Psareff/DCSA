#pragma once
#include <iostream>

class user
{
public:
	user(std::string uid, 
	     std::string name, 
	     std::string user_info);
	std::string get_uid();
	std::string get_info();
	std::string get_name();
private:
	std::string _uid;
	std::string _name;
	std::string _user_info;
};
inline std::string user::get_uid()
{
	return this->_uid;
}
inline std::string user::get_info()
{
	return this->_user_info;
}
inline std::string  user::get_name()
{
	return this->_name;
}
