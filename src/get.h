/*
 * get.h
 */

#ifndef GET_H_
#define GET_H_

#include <curl/curl.h>
#include <sstream>

using namespace std;

static size_t writer(void *contents, size_t size, size_t nmemb, void *userp) {
	((std::string*) userp)->append((char*) contents, size * nmemb);
	return size * nmemb;
}

string get(const string url) {
	CURL *curl;
	CURLcode res;
	struct curl_slist *headers = NULL;
	string readBuffer;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "charsets: utf-8");

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		// Perform the request, res will get the return code
		res = curl_easy_perform(curl);

		if (CURLE_OK == res) {
			char *ct;
			res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
			curl_easy_cleanup(curl);
			if ((CURLE_OK == res) && ct) {
				return readBuffer;
			}
		} else {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
			curl_easy_cleanup(curl);
		}
	}
	return "";
}

#endif /* GET_H_ */
