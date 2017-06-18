/*
 * movie.h
 */

#ifndef MOVIE_H_
#define MOVIE_H_

#include <string>
using namespace std;

class Movie{
private:
	string title;
	string releasedate;
	bool watched;

public:
	// constructors
	Movie();
	Movie(string, string);
	Movie(string, string, bool);

	// accessor methods
	string getTitle ();
	string getReleaseDate();
	bool wasWatched();

	// mutator methods
	void setTitle(string);
	void setReleaseDate(string);
	void setWatched(bool);
};


#endif /* MOVIE_H_ */
