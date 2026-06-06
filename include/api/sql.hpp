/**
 * @file sql.hpp
 * @brief Provides some wrapper functions around the MySQL connector library /
 * JDBC
 */

#ifndef _SQL
#define _SQL

#include "jdbc/cppconn/resultset.h"
#include <mysql/jdbc.h>
#include <string>
#include <vector>

namespace nathcat {
namespace sqlwrapper {

/**
 * @brief Extracts details of an SQL error, includes the provided function name
 * in the output
 *
 * @param e The exception to detail
 * @param fName The function name to include
 */
std::string error_details(sql::SQLException &e, std::string fName);
/**
 * @brief Extracts details of an SQL error, using a default function name
 *
 * @param e The exception to detail
 */
std::string error_details(sql::SQLException &e);

/**
 * @brief Transform a single row of a result set into a given type. Type
 * specific definitions of this function should be provided by the user.
 *
 * @tparam T The type to transform the row into
 * @param res The result set to get the data from
 * @return The current row of the result set interpreted as the provided type
 */
template <typename T> T fromRow(std::unique_ptr<sql::ResultSet> &res);

/**
 * @brief Transform a result set into an array of a type, with each element
 * being a single row of the set
 *
 * @tparam T The type to use for each row
 * @param res The result set
 * @return An array of the rows as the given type
 */
template <typename T>
std::vector<T> toArray(std::unique_ptr<sql::ResultSet> &res) {
  std::vector<T> v;

  while (res->next()) {
    v.push_back(fromRow<T>(res));
  }

  return v;
}

namespace util {
/**
 * @brief Check if a given user is a member of a group
 */
bool isMemberOfGroup(std::unique_ptr<sql::Connection> &db, int user, int group);
} // namespace util
} // namespace sqlwrapper
} // namespace nathcat

#endif
