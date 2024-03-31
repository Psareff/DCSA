#include "Routers.hpp"
#include "User.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector<std::string> split(std::string s, std::string delimiter) 
{
    size_t pos_start = 0, 
		   pos_end, 
		   delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) 
	{
		token = s.substr (pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back (token);
    }

	res.push_back (s.substr (pos_start));
	return res;
}

void route::RegisterResources(hv::HttpService &router)
{
    static std::vector<user> users = {};
    
	router.GET("/user/{user_name}", [](HttpRequest *req, HttpResponse *resp)
    {
		int ret = 200;

		std::vector<std::string> splitted_path = split(req->path, "/");

		nlohmann::json response;

		for(auto user : users)
			if(user.get_name() == splitted_path.back())
			{
				ret = 400;
				response = 
				{
					{"id", user.get_uid()},
					{"info", user.get_info()},
					{"name", user.get_name()}
				};
			} 

		if(ret == 200) response["error"] = "JSON parsing error";
		
		resp->SetBody(response.dump());
		resp->content_type = APPLICATION_JSON;

		return ret;
    });

    router.GET("/users", [](HttpRequest *req, HttpResponse *resp)
    {
		nlohmann::json response;
		int ret = 200;
		if(!users.size())
		{
			resp->SetBody("Didn't find any user");
			resp->content_type = APPLICATION_JSON;
			return ret;
		}
		for( auto user : users )
			response["user " + user.get_uid()] = 
			    "name=" + user.get_name() +
			    " info=" + user.get_info(); 

		resp->SetBody(response.dump());
		resp->content_type = APPLICATION_JSON;

		return ret;
    });

   router.Delete("/user/{userId}", [](HttpRequest *req, HttpResponse *resp)
    {
		std::vector<std::string> splitted_path = split(req->path, "/");
		nlohmann::json response;
		users.erase(std::remove_if(users.begin(), users.end(), [splitted_path](user usr) 
					{ 
						return usr.get_name() == splitted_path.back(); 
					}), users.end());

		resp->SetBody("User deleted");
		resp->content_type = APPLICATION_JSON;

		return 200;

    });

    router.POST("/user", [](HttpRequest *req, HttpResponse *resp)
    {
		nlohmann::json request;
		nlohmann::json response;
		try
		{
		    request = nlohmann::json::parse(req->body);
		}
		catch(const std::exception& e)
		{
			response["error"] = "Invalid JSON";
			resp->SetBody(response.dump());
			resp->content_type = APPLICATION_JSON;
			return 400;
		}

		 std::string name = request["name"];
		 std::string info_string = request["info"];
		 std::string id_string = request["id"];

		 user user(id_string, name, info_string);
		 users.push_back(user);

		resp->SetBody("User Added");
		resp->content_type = APPLICATION_JSON;
		return 200;
	});
}
