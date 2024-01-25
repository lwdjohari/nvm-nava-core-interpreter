#ifndef NAVA_CORE_INTERPRETERS_SQL_V2_ISQLDIALECT_H
#define NAVA_CORE_INTERPRETERS_SQL_V2_ISQLDIALECT_H

#include <memory>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "nava/core/interpreters/sql/expression.h"

namespace nava {
namespace core {
namespace interpreters {
namespace sql {

class ISqlDialect {
 private:
 protected:
  virtual void InitializeDialect() = 0;
  virtual Expression CreateUnaryExpression(const std::string& op,
                                           const Expression& expr) = 0;
  virtual Expression CreateBinaryExpression(const std::string& op,
                                            const Expression& left,
                                            const Expression& right) = 0;
  virtual Expression CreateBinaryExressionChain(
      const Expression& head, std::vector<Expression>& tails) = 0;

 public:
  virtual ~ISqlDialect(){};

  virtual std::shared_ptr<absl::flat_hash_map<std::string, bool>>
  ReservedWords() const = 0;
  virtual std::shared_ptr<absl::flat_hash_map<std::string, bool>> PrefixMap()
      const = 0;

}

} // namespace sql
} // namespace interpreters
} // namespace core
} // namespace nava

#endif // NAVA_CORE_INTERPRETERS_SQL_V2_ISQLDIALECT_H
