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
	tm releasedate;
	bool watched;

public:
	// constructors
	Movie();
	Movie(string, tm);
	Movie(string, tm, bool);

	// accessor methods
	string getTitle ();
	tm getReleaseDate();
	string getRating();
	bool wasWatched();

	// mutator methods
	void setTitle(string);
	void setReleaseDate(tm);
	void setWatched(bool);
};


#endif /* MOVIE_H_ */
