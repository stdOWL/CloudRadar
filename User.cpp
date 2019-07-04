#include "User.h"
#include "LocalListener.h"
std::map<std::string, User*>	User::users;

User::User(char * id)
{
	userid = id;
}

User * User::AddOrCreateUser(std::string id)
{

}

User::~User()
{
}
