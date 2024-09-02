#define BOOST_TEST_MODULE Operations
#include <boost/test/included/unit_test.hpp>
#include "Calculations.h" 
#include <sstream>

BOOST_AUTO_TEST_CASE(OperationsTest)
{
    std::unique_ptr<Node> Num { CreateNumber(1) };
    BOOST_TEST( Num->Calculate() == 1 );

    std::unique_ptr<Node> Div{ OpDivision (CreateNumber(13),CreateNumber(9))};
    BOOST_TEST(Div->Calculate() == (13.0/9.0), boost::test_tools::tolerance(0.01));

    std::unique_ptr<Node> Mul{ OpMultiplication(CreateNumber(13),CreateNumber(9)) };
    BOOST_TEST(Mul->Calculate() == (13*9));

    std::unique_ptr<Node> Sub{ OpSubtraction(CreateNumber(13),CreateNumber(9)) };
    BOOST_TEST(Sub->Calculate() == (13-9));

    std::unique_ptr<Node> Add{ OpAddition(CreateNumber(13),CreateNumber(9)) };
    BOOST_TEST(Add->Calculate() == (13 + 9));

    std::unique_ptr<Node> Text{ OpSubtraction(OpDivision(OpAddition(CreateNumber(13),CreateNumber(9)),OpMultiplication(CreateNumber(13),CreateNumber(9))),OpDivision(OpAddition(CreateNumber(13),CreateNumber(9)),OpMultiplication(CreateNumber(13),CreateNumber(9)))) };
    std::stringstream ss;
    Text->Print(ss, 0);
    BOOST_TEST(ss.str() == "Subtraction\n  Division\n    Addition\n      Number(13.000000)\n      Number(9.000000)\n    Multiplication\n      Number(13.000000)\n      Number(9.000000)\n  Division\n    Addition\n      Number(13.000000)\n      Number(9.000000)\n    Multiplication\n      Number(13.000000)\n      Number(9.000000)\n");
    CheckMain();
    //
    //BOOST_REQUIRE(Num->Calculate()==0);
    //BOOST_CHECK(Num->Calculate() == 1); // will never reach this check
}
