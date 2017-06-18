//============================================================================
// Name        : pmdb.cpp
// Author      : Erik Chan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <pqxx/pqxx>
#include "get.h"
#include "json.hpp"
#include <sstream>

using json = nlohmann::json;
using namespace std;
using namespace pqxx;

#include <sstream>
#include <chrono>
#include <thread>

template<typename T>
string toString(T Number) {
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

string escape(std::string const &s) {
	std::size_t n = s.length();
	std::string escaped;
	escaped.reserve(n * 2);        // pessimistic preallocation

	for (std::size_t i = 0; i < n; ++i) {
		if (s[i] == '\'')
			escaped += '\'';
		escaped += s[i];
	}
	return escaped;
}

void populateGenres() {
	string apikey = "06709af3621440ead23fb1f3e554ee3d";

	// Get database response
	string fullURL = "https://api.themoviedb.org/3/genre/movie/list?api_key="
			+ apikey;

	json genreJson = json::parse(get(fullURL));

	try {
		string sql;

		connection C(
				"dbname = pmdb user = postgres password = postgres hostaddr = 127.0.0.1 port = 5432");
		if (C.is_open()) {
			cout << "Opened database successfully: " << C.dbname() << endl;
		} else {
			cout << "Can't open database" << endl;
		}

		/* Create a transactional object. */
		work W(C);

		sql = string("DROP TABLE IF EXISTS genre");
		W.exec(sql);

		sql = string("CREATE TABLE genre(") + "id INT PRIMARY KEY NOT NULL,"
				+ "name CHAR(15));";
		W.exec(sql);

		for (int i = 0; i < genreJson["genres"].size(); i++) {
			string id = toString(genreJson["genres"][i]["id"]);
			string name = escape(genreJson["genres"][i]["name"]);
			sql = string("INSERT INTO genre (id, name) ") + "VALUES (" + id
					+ ", '" + name + "'); ";
			W.exec(sql);
		}

		W.commit();
		cout << "Table created successfully" << endl;
		C.disconnect();

	} catch (const exception &e) {
		cerr << e.what() << endl;
	}
}

void populateMovies() {
	string apikey = "06709af3621440ead23fb1f3e554ee3d";

	// Get database response
	string url = "https://api.themoviedb.org/3/";
	string latest = url + "movie/latest?api_key=" + apikey;

	json latestJson = json::parse(get(latest));

	try {
		string sql;

		connection C(
				"dbname = pmdb user = postgres password = postgres hostaddr = 127.0.0.1 port = 5432");
		if (C.is_open()) {
			cout << "Opened database successfully: " << C.dbname() << endl;
		} else {
			cout << "Can't open database" << endl;
		}

		/* Create a transactional object. */
		work W(C);

		// sql = string("DROP TABLE IF EXISTS movie;");
		// W.exec(sql);

		sql = string("CREATE TABLE IF NOT EXISTS movie(")
				+ "id INT PRIMARY KEY NOT NULL,"
				+ "title CHAR(50), releasedate CHAR(10), watched BOOL);";
		W.exec(sql);

		string current = url + "list/28?api_key=" + apikey;
		json winnerJson = json::parse(get(current));

		// int latestId = latestJson["id"];
		for (int i = 0; i < winnerJson["items"].size(); i++) {
			string id = toString(winnerJson["items"][i]["id"]);
			string title = escape(winnerJson["items"][i]["title"]);
			string releasedate = escape(winnerJson["items"][i]["release_date"]);
			sql = string("INSERT INTO movie (id, title, releasedate) ")
					+ "VALUES (" + id + ", '" + title + "', '" + releasedate
					+ "') ON CONFLICT DO NOTHING;";
			W.exec(sql);
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
		sql = string("DELETE FROM movie WHERE title = 'Finding Nemo';");
		W.exec(sql);

		W.commit();
		cout << "Table created successfully" << endl;
		C.disconnect();

	} catch (const exception &e) {
		cerr << e.what() << endl;
	}
}

int main() {
	populateGenres();
	populateMovies();
	return 0;
}
