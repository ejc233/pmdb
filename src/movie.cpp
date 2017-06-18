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

Movie::Movie(string t, string rd) {
	title = t;
	releasedate = rd;
	watched = false;
}

Movie::Movie(string t, string rd, bool w) {
	title = t;
	releasedate = rd;
	watched = w;
}

// accessor methods
string Movie::getTitle() {
	return title;
}
string Movie::getReleaseDate() {
	return releasedate;
}
bool Movie::wasWatched() {
	return watched;
}

// mutator methods
void Movie::setTitle(string t) {
	title = t;
}
void Movie::setReleaseDate(string rd) {
	releasedate = rd;
}
void Movie::setWatched(bool w) {
	watched = w;
}
