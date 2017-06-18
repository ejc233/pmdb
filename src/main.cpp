#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <curl/curl.h>
#include "get.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

int main(void) {
	string apikey = "06709af3621440ead23fb1f3e554ee3d";

	// Get database response
	string fullURL = "https://api.themoviedb.org/3/genre/movie/list?api_key="
			+ apikey;

	string message = get(fullURL);

	cout << message << endl;

	string strJson = message;
	json j = json::parse(message);

	for (int i = 0; i < j["genres"].size(); i++) {
		cout << j["genres"][i]["id"];
		cout << j["genres"][i]["name"] << endl;
	}

	return 0;
}
