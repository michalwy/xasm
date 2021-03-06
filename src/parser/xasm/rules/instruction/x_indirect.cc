#include "x_indirect.hh"

#include "../../ast_adapted/instruction.hh"
#include "../../config.hh"
#include "../token.hh"
#include "operand.hh"

#include <boost/spirit/home/x3.hpp>

namespace xasm {
namespace parser {
namespace xasm {
namespace rules {
namespace instruction {
namespace x_indirect {

namespace x3 = boost::spirit::x3;

static struct mos6502_mnemonic_ : public x3::symbols<ast::instruction::opcode_t> {
	mos6502_mnemonic_() {
		add("ORA", 0x01)("AND", 0x21)("EOR", 0x41)("ADC", 0x61)("SBC", 0xE1)("CMP", 0xC1)(
		    "LDA", 0xA1)("STA", 0x81);
	}
} mos6502_mnemonic;

static x3::rule<class mnemonic, ast::instruction::opcode_t> const mnemonic = "mnemonic";
static auto const mnemonic_def = x3::no_case[mos6502_mnemonic];
BOOST_SPIRIT_DEFINE(mnemonic);

static x3::rule<class argument, std::uint8_t> const argument = "argument";
static auto const argument_def = x3::lit("(") >> byte >> x3::no_case[x3::lit(",X)")] >> &x3::space;
BOOST_SPIRIT_DEFINE(argument);

static auto const statement_def
    = x3::attr(ast::instruction::x_indirect) >> mnemonic >> token_sep >> argument;
BOOST_SPIRIT_DEFINE(statement);
BOOST_SPIRIT_INSTANTIATE(statement_type, config::iterator_type, config::context_type);

} // namespace x_indirect
} // namespace instruction
} // namespace rules
} // namespace xasm
} // namespace parser
} // namespace xasm
