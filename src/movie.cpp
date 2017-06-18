/*
 * movie.cpp
 */

#include <iostream>
#include "movie.h"
using namespace std;

// constructors
Movie::Movie() {
	title = "";
	watched = false;
}

Movie::Movie(string t, tm rd) {
	title = t;
	releasedate = rd;
	watched = false;
}

Movie::Movie(string t, tm rd, bool w) {
	title = t;
	releasedate = rd;
	watched = w;
}

// accessor methods
string Movie::getTitle() {
	return title;
}
tm Movie::getReleaseDate() {
	return releasedate;
}
bool Movie::wasWatched() {
	return watched;
}

// mutator methods
void Movie::setTitle(string t) {
	title = t;
}
void Movie::setReleaseDate(tm rd) {
	releasedate = rd;
}
void Movie::setWatched(bool w) {
	watched = w;
}
