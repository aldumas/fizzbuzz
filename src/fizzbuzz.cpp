/**
 * FizzBuzz
 *
 * @author Adam L Dumas
 */


#include <iostream>
#include <string>
#include <sstream>

using std::string;

template <typename ValueType>
bool parseCommandLineArg(int pos, int argc, char* argv[], ValueType& out_value);
string fizzBuzz(int num);


/**
 * Extract a positive integer from the first command line argument and count up
 * to it according to the rules of FizzBuzz.
 */
int main(int argc, char* argv[])
{
    int upper_bound;
    if (!parseCommandLineArg(1, argc, argv, upper_bound) || upper_bound <= 0)
    {
        std::cerr << "Invalid argument for upper bound.\n";
        return -1;
    }

    for (int i = 1; i <= upper_bound; ++i)
        std::cout << fizzBuzz(i) << '\n';
}


/**
 * Parse a command line argument into a variable.
 *
 * @remark This function does bounds-checking of the provided position, but
 * does not check argc and argv. These two values should be passed directly
 * from main()'s arguments unless you are certain they are correct.
 *
 * @param pos 0-based position in argv of the argument to parse.
 * @param argc total number of arguments in argv.
 * @param argv array of arguments.
 * @param out_value the variable to place the result. This may be written even
 * if parsing fails, in which case the value should not be used.
 *
 * @return true if parsing succeeded, in which case out_value contains the
 * value.
 */
template <typename ValueType>
// Requires operator>>(istream&, ValueType&)
bool parseCommandLineArg(int pos, int argc, char* argv[], ValueType& out_value)
{
    if (argc < pos)
        return false;

    std::istringstream in(argv[pos]);

    return in >> out_value && in.eof();
}


/**
 * Return a string representation of the number, according to the rules of
 * FizzBuzz.
 *
 * The string returned is determined by the following rules:
 * 1. If the number is divisible by 3 but not 5, the value is "Fizz".
 * 2. If the number is divisible by 5 but not 3, the value is "Buzz".
 * 3. If the number is divisible by both 3 and 5, the value is "FizzBuzz".
 * 4. If the number is divisible by neither 3 nor 5, the value is the number,
 *    itself.
 *
 * @remark Since it is expected this function will be used in a loop, one
 * concern the author had was the repeated construction and destruction of
 * strings since a string is built and destroyed on every call to this function.
 * For that reason, he created a version which received a string reference from
 * the caller, so the caller would allocate the string once, and then the
 * fizzBuzz() function would only need to modify it, not needing to construct it
 * from scratch or destroy it. Performance testing on Release builds, however,
 * showed little difference in execution time, so he kept the initial version
 * since it has a cleaner interface.
 *
 * @param num the number to convert to a FizzBuzz string value
 *
 * @return string representation of the number, according to the rules of
 * FizzBuzz
 */
string fizzBuzz(int num)
{
    string text;

    if (num % 3 == 0)
    {
        text += "Fizz";
    }

    if (num % 5 == 0)
    {
        text += "Buzz";
    }

    if (text.empty())
    {
        text = std::to_string(num);
    }

    return text;
}
