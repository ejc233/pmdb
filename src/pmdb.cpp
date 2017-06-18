//============================================================================
// Name        : pmdb.cpp
// Author      : Erik Chan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

//int main() {
//	cout << "Hello, World!" << endl;
//	try {
//		connection C(
//				"dbname = pmdb user = postgres hostaddr = 127.0.0.1 port = 5432");
//		if (C.is_open()) {
//			cout << "Opened database successfully: " << C.dbname() << endl;
//		} else {
//			cout << "Can't open database" << endl;
//			return 1;
//		}
//		C.disconnect();
//	} catch (const std::exception &e) {
//		cerr << e.what() << std::endl;
//		return 1;
//	}
//	return 0;
//}
