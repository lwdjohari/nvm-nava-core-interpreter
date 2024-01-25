#ifndef NAVA_CORE_INTERPRETERS_SQL_V2_PQSQL_DIALECT_H
#define NAVA_CORE_INTERPRETERS_SQL_V2_PQSQL_DIALECT_H

#include <memory>

#include "absl/container/flat_hash_map.h"
#include "nava/core/interpreters/sql/isqldialect.h"
#include "nava/core/interpreters/sql/expression.h"

namespace nava {
namespace core {
namespace interpreters {
namespace sql {

class PqsqlDialect : public ISqlDialect {
 public:
  PqsqlDialect()
      : ISqlDialect(),
        reserved_words_(PopulateReservedWords()),
        prefix_map_(std::make_shared<absl::flat_hash_map<std::string, bool>>()){

        };

  ~PqsqlDialect() override{

  };

  std::shared_ptr<absl::flat_hash_map<std::string, bool>> ReservedWords()
      const override {
    return reserved_words_;
  };

  std::shared_ptr<absl::flat_hash_map<std::string, bool>> PrefixMap()
      const override {
    return prefix_map_;
  };

 protected:
  std::shared_ptr<absl::flat_hash_map<std::string, bool>> reserved_words_;
  std::shared_ptr<absl::flat_hash_map<std::string, bool>> prefix_map_;

  virtual void InitializeDialect() override{

  };

  virtual Expression CreateUnaryExpression(const std::string& op,
                                           const Expression& expr) override {
    return Expression();
  };

  virtual Expression CreateBinaryExpression(const std::string& op,
                                            const Expression& left,
                                            const Expression& right) override {
    return Expression();
  };

  virtual Expression CreateBinaryExressionChain(
      const Expression& head, std::vector<Expression>& tails) override {
    return Expression();
  };

 private:
  std::shared_ptr<absl::flat_hash_map<std::string, bool>> PopulatePrefixMap() {
    return std::make_shared<absl::flat_hash_map<std::string, bool>>(
        {{"+", true},
         {"-", true},
         {"*", true},
         {"/", true},
         {"%", true},
         {"&", true},
         {"|", true},
         {"^", true},
         {"~", true},
         {"<<", true},
         {">>", true},
         {"=", true},
         {"<", true},
         {">", true},
         {"<=", true},
         {">=", true},
         {"<>", true},
         {"!=", true},
         {"!~", true},
         {"!~*", true},
         {"~*", true},
         {"IS", true},
         {"IS NOT", true},
         {"ISNULL", true},
         {"NOTNULL", true},
         {"NOT", true},
         {"AND", true},
         {"OR", true},
         {"IN", true},
         {"NOT IN", true},
         {"BETWEEN", true},
         {"NOT BETWEEN", true},
         {"LIKE", true},
         {"ILIKE", true},
         {"SIMILAR TO", true},
         {"NOT LIKE", true},
         {"NOT ILIKE", true},
         {"NOT SIMILAR TO", true},
         {"ESCAPE", true},
         {"OVERLAPS", true},
         {"NOT OVERLAPS", true},
         {"ANY", true},
         {"ALL", true},
         {"SOME", true},
         {"IN", true},
         {"NOT IN", true},
         {"EXISTS", true},
         {"NOT EXISTS", true},
         {"UNIQUE", true},
         {"IS DISTINCT FROM", true},
         {"IS NOT DISTINCT FROM", true},
         {"<=>", true},
         {"||", true},
         {"AS", true},
         {"COLLATE", true},
         {"ASC", true},
         {"DESC", true},
         {"NULLS FIRST", true},
         {"NULLS LAST", true},
         {"USING", true},
         {"ROW", true},
         {"ROWS", true},
         {"EXTRACT", true},
         {"FROM", true},
         {"WITH TIME ZONE", true},
         {"WITHOUT TIME ZONE", true},
         {"AT TIME ZONE", true}});
  }

  std::shared_ptr<absl::flat_hash_map<std::string, bool>>
  PopulateReservedWords() {
    return std::make_shared<absl::flat_hash_map<std::string, bool>>(
        {{"ALTER", true},
         {"ALL", true},
         {"ADD", true},
         {"AND", true},
         {"AS", true},
         {"ASC", true},
         {"BETWEEN", true},
         {"BY", true},
         {"CALL", true},
         {"CASE", true},
         {"CREATE", true},
         {"CONTAINS", true},
         {"CURRENT_DATE", true},
         {"CURRENT_TIME", true},
         {"CURRENT_TIMESTAMP", true},
         {"CURRENT_USER", true},
         {"DELETE", true},
         {"DESC", true},
         {"DISTINCT", true},
         {"DROP", true},
         {"ELSE", true},
         {"END", true},
         {"EXISTS", true},
         {"EXPLAIN", true},
         {"FALSE", true},
         {"FROM", true},
         {"FULL", true},
         {"GROUP", true},
         {"HAVING", true},
         {"IN", true},
         {"INNER", true},
         {"INSERT", true},
         {"INTO", true},
         {"IS", true},
         {"JOIN", true},
         {"JSON", true},
         {"LEFT", true},
         {"LIKE", true},
         {"LIMIT", true},
         {"NOT", true},
         {"NULL", true},
         {"NULLS", true},
         {"OFFSET", true},
         {"ON", true},
         {"OR", true},
         {"ORDER", true},
         {"OUTER", true},
         {"RECURSIVE", true},
         {"RENAME", true},
         {"RIGHT", true},
         {"SELECT", true},
         {"SESSION_USER", true},
         {"SET", true},
         {"SHOW", true},
         {"SYSTEM_USER", true},
         {"TABLE", true},
         {"THEN", true},
         {"TRUE", true},
         {"TRUNCATE", true},
         {"UNION", true},
         {"UPDATE", true},
         {"USING", true},
         {"WITH", true},
         {"WHEN", true},
         {"WHERE", true},
         {"WINDOW", true},
         {"GLOBAL", true},
         {"SESSION", true},
         {"LOCAL", true},
         {"PERSIST", true},
         {"PERSIST_ONLY", true}});
  };
}

}  // namespace sql
}  // namespace interpreters
}  // namespace core
}  // namespace nava

#endif  // NAVA_CORE_INTERPRETERS_SQL_V2_PQSQL_DIALECT_H
