#include "jdbc/cppconn/exception.h"
#include "jdbc/cppconn/prepared_statement.h"
#include "jdbc/cppconn/resultset.h"
#include <api/api.hpp>
#include <api/sql.hpp>
#include <regex>

bool nathcat::sqlwrapper::util::isMemberOfGroup(
    std::unique_ptr<sql::Connection> &db, int user, int group) {
  std::unique_ptr<sql::PreparedStatement> stmt{db->prepareStatement(
      "select count(*) as 'count' from DataCat.Group_Members where `group` = ? "
      "and `user` = ?")};

  stmt->setInt(1, group);
  stmt->setInt(2, user);

  std::unique_ptr<sql::ResultSet> res{stmt->executeQuery()};

  if (!res->next()) {
    throw sql::SQLException();
  }

  int count = res->getInt("count");

  return count > 0;
}

std::string nathcat::api::get_cookie(const httplib::Request &req,
                                     std::string name) {
  if (!req.has_header("Cookie"))
    return "";

  std::string cookies = req.get_header_value("Cookie");

  std::regex r(name.append("=([^;]*);?"));

  std::smatch match;
  if (std::regex_match(cookies, match, r)) {
    return match[1].str();
  } else {
    return "";
  }
}
