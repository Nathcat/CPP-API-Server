#ifndef _SQL
#define _SQL

#include "jdbc/cppconn/resultset.h"
#include <mysql/jdbc.h>
#include <string>
#include <vector>

namespace nathcat {
namespace sqlwrapper {

std::string error_details(sql::SQLException &e, std::string fName);
std::string error_details(sql::SQLException &e);

template <typename T> T fromRow(std::unique_ptr<sql::ResultSet> &res);

template <typename T>
std::vector<T> toArray(std::unique_ptr<sql::ResultSet> &res);

} // namespace sqlwrapper
} // namespace nathcat

#endif
