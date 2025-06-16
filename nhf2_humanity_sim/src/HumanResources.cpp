#include "HumanResources.h"
//TO hr
void HumanResources::add_resources(const std::string& what, int amount){
	resources[what]+=amount;
}

void HumanResources::remove_resources(const std::string& what, int amount){
	resources[what]-=amount;
}
bool HumanResources::is_there_enough_resource(const std::string& from_what, int needed_amount) const{
	auto it = resources.find(from_what);
    return it != resources.end() && it->second >= needed_amount;
}
void HumanResources::set_resources(const std::string& what,int amount){
	resources[what]=amount;
}

int HumanResources::get_count_from(const std::string& what) const{
	auto it = resources.find(what);
    return (it != resources.end()) ? it->second : 0;
}