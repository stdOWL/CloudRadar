#pragma once
class User
{
public:
	User(char * id);
	~User();
public:

	std::string userid;

	static std::map<std::string, User*>	users;
	static User *AddOrCreateUser(std::string id);
};

