#include "jdbc/cppconn/statement.h"
#include <api/sql.hpp>
using namespace nathcat::sqlwrapper;

std::string nathcat::sqlwrapper::error_details(sql::SQLException &e,
                                               std::string fName) {
  std::string s = "";

  s = s.append("# ERR: SQLException in ")
          .append(__FILE__)
          .append("(")
          .append(fName)
          .append(") on line ")
          .append(std::to_string(__LINE__))
          .append("\n")
          .append("# ERR: ")
          .append(e.what())
          .append(" (MySQL error code: ")
          .append(std::to_string(e.getErrorCode()))
          .append(", SQLState: ")
          .append(e.getSQLState())
          .append(" )")
          .append("\n");

  return s;
}

std::string nathcat::sqlwrapper::error_details(sql::SQLException &e) {
  return error_details(e, "No function name provided");
}

void nathcat::sqlwrapper::start_transaction(
    std::unique_ptr<sql::Connection> &db) {
  std::unique_ptr<sql::Statement> stmt{db->createStatement()};
  stmt->executeUpdate("START TRANSACTION");
  stmt->close();
}

void nathcat::sqlwrapper::commit_transaction(
    std::unique_ptr<sql::Connection> &db) {
  std::unique_ptr<sql::Statement> stmt{db->createStatement()};
  stmt->executeUpdate("COMMIT");
  stmt->close();
}

void nathcat::sqlwrapper::rollback_transaction(
    std::unique_ptr<sql::Connection> &db) {
  std::unique_ptr<sql::Statement> stmt{db->createStatement()};
  stmt->executeUpdate("ROLLBACK");
  stmt->close();
}
