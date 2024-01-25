#ifndef NAVA_CORE_INTERPRETERS_V2_PARSER_H
#define NAVA_CORE_INTERPRETERS_V2_PARSER_H

namespace nava {
namespace core {
namespace interpreters {

class IParser
{
private:
    
public:
    virtual ~IParser(){};
};



class ParserBase:public IParser
{
private:
    
public:
    ParserBase(){};
    virtual ~ParserBase() override;
};



} // namespace interpreters
} // namespace core
} // namespace nava

#endif // NAVA_CORE_INTERPRETERS_V2_PARSER_H
