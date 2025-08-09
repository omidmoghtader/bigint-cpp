#pragma once

/**
 * @file bigint.hpp
 * @author Omid Moghtader (omidm.analytics@gmail.com)
 *
 * @since 1.0 (2023-12-28)
 * @version 1.2
 * @date 2025-08-09
 *
 * @copyright Copyright (c) 2023
 *
 * @brief bigint: a class for arbitrary-precision integers, allowing arithmetic and comparison operations on integers beyond the scope of signed 64-bit integer.
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <cmath>

/**
 * @class bigint
 * @brief Arbitrary-precision integer class.
 *
 * This class, equipped with three constructors, supports arithmetic and comparison operations for integers beyond the usual 64-bit range.
 */
class bigint
{
public:
    /**
     * @brief Default constructor.
     *
     * Creates a bigint object with a default value, 0.
     */
    bigint()
    {
        // Assigning sign as '+'.
        sign = '+';
        // Initializing vector 'digits' to 0.
        digits.push_back(0);
    }

    /**
     * @brief Integer constructor.
     *
     * Construct a new bigint object and initializes it with the provided integer value.
     *
     * @param int_num The integer value to initialize the bigint object with.
     */
    bigint(int64_t int_num)
    {
        // Assigning sign as '-' for negative numbers and '+' for non-negative numbers.
        if (int_num < 0)
        {
            sign = '-';
            int_num = -int_num;
        }
        else
        {
            sign = '+';
        }

        // Storing the digits of the number in vector 'digits'.
        if (int_num == 0)
        {
            digits.insert(digits.begin(), 0);
        }
        else
        {
            // Extracting and storing the rightmost digit of the number in vector 'digits', then removing it from the original number.
            while (int_num != 0)
            {
                digits.insert(digits.begin(), static_cast<uint8_t>(int_num % 10));
                int_num /= 10;
            }
        }
    }

    /**
     * @brief String constructor.
     *
     * Construct a new bigint object and initializes it with the value represented by the provided string.
     *
     * @param int_str The string representation of the integer value.
     */
    bigint(const std::string &int_str)
    {
        // Verifying whether the string is empty.
        if (int_str.size() == 0)
        {
            throw empty_string();
        }

        // Marking indices 'i' and 'l' for the first and last non-white-space characters.
        uint64_t i = 0;
        uint64_t l = int_str.size() - 1;

        while (int_str[i] == ' ')
        {
            i++;
        }

        while (int_str[l] == ' ')
        {
            l--;
        }

        // The scenario where the initial non-white-space character is one of the two sign characters.
        if ((int_str[i] == '-') or (int_str[i] == '+'))
        {
            // Verifying if there is a digit immediately following the sign.
            if ((i == l) or (int_str[i + 1] == ' '))
            {
                throw no_digit();
            }
            else
            {
                sign = int_str[i];
                i++;
                // Skipping leading zeros after the sign and the first non-zero digit.
                while (int_str[i] == '0')
                {
                    // Assigning the arbitrary-precision integer to '+0' if all digits in the entry string are 0.
                    if (i == l)
                    {
                        sign = '+';
                        digits.insert(digits.begin(), 0);
                    }
                    i++;
                }

                // Storing the digits of the string in vector 'digits'.
                for (uint64_t j = i; j < l + 1; j++)
                {
                    if (!isdigit(int_str[j]))
                    {
                        throw non_digit();
                    }
                    else
                    {
                        // Converting a character representing a digit to its corresponding numeric value.
                        digits.push_back((uint8_t)(int_str[j] - '0'));
                    }
                }
            }
        }
        // The scenario where the initial non-white-space character is a digit.
        else if (isdigit(int_str[i]))
        {
            sign = '+';
            // Skipping leading zeros to the right of the other non-zero digits.
            while (int_str[i] == '0')
            {
                // Assigning the arbitrary-precision integer to '+0' if all digits in the entry string are 0.
                if (i == l)
                    digits.insert(digits.begin(), 0);
                i++;
            }

            // Storing the digits of the string in vector 'digits'.
            for (uint64_t j = i; j < l + 1; j++)
            {
                if (!isdigit(int_str[j]))
                {
                    throw non_digit();
                }
                else
                {
                    digits.push_back((uint8_t)(int_str[j] - '0'));
                }
            }
        }
        else
            throw non_digit();
    }

    /**
     * @brief Default constexpr copy constructor for bigint class.
     *
     * This constexpr copy constructor creates a new bigint object by copying the values from another bigint object.
     *
     * @param other The bigint object to be copied.
     */
    constexpr bigint(const bigint &other) = default;

    /**
     * @brief Overloaded insertion operator for bigint class.
     *
     * This binary output stream operator allows printing bigint objects to an output stream.
     *
     * @param out The output stream.
     * @param num_bigint The bigint object to be printed.
     * @return The modified output stream.
     */
    friend std::ostream &operator<<(std::ostream &out, const bigint &num_bigint)
    {
        out << num_bigint.sign;
        for (uint64_t i = 0; i < num_bigint.digits.size(); i++)
        {
            out << num_bigint.digits[i] - 0;
        }
        return out;
    }

    /**
     * @brief Overloaded assignment operator for bigint class.
     *
     * This binary operator assigns the value of another bigint object to the current object.
     *
     * @param other The bigint object whose value will be assigned.
     * @return A reference to the modified current object.
     */
    bigint &operator=(const bigint &other)
    {
        // Guard against self-assignment.
        if (this == &other)
        {
            return *this;
        }

        sign = other.sign;
        digits.resize(other.digits.size());
        for (uint64_t i = 0; i < other.digits.size(); i++)
        {
            digits[i] = other.digits[i];
        }
        return *this;
    }

    /**
     * @brief Overloaded negation operator for bigint class.
     *
     * This unary operator negates the value of the current bigint object, creating a new bigint object with the opposite sign.
     *
     * @return A new bigint object representing the negated value.
     */
    bigint operator-() const
    {
        bigint other = *this;
        // Swapping the sign of an arbitrary-precision integer.
        if (sign == '+')
            other.sign = '-';
        else
            other.sign = '+';
        return other;
    }

    /**
     * @brief Overloaded addition-assignment operator for bigint class.
     *
     * This binary operator adds the values of another bigint object to the current object and modifies the current object.
     *
     * @param other The bigint object whose values will be added to the current object.
     * @return A reference to the modified current object.
     */
    bigint &operator+=(const bigint &other)
    {
        // Guard against adding 0 to the value.
        if (digits[0] == 0)
        {
            *this = other;
            return *this;
        }

        if (other.digits[0] == 0)
        {
            return *this;
        }

        // Guard against additive inverse of this arbitrary-precision integer.
        if (*this == -other)
        {
            sign = '+';
            digits = {0};
            return *this;
        }

        // The scenario where both arbitrary-precision integers have the same sign.
        if (sign == other.sign)
        {
            // Declaring and initializing a temporary variable 'temp' to store current digits and carry (or carried-over digit) 'c'.
            uint8_t c = 0;
            uint8_t temp = 0;

            // Determining the size of the arbitrary-precision integer with fewer digits.
            uint64_t min_size = std::min(digits.size(), other.digits.size());

            // Applying addition-assignment so all digits of the number with fewer digits are added to the corresponding digits of number with more digits.
            for (uint64_t i = 0; i < min_size; i++)
            {
                temp = static_cast<uint8_t>(digits[digits.size() - 1 - i] + other.digits[other.digits.size() - 1 - i] + c);
                digits[digits.size() - 1 - i] = temp % 10;
                c = temp / 10;
            }

            // Applying addition-assignment to the remaining digits.
            if (digits.size() > other.digits.size())
            {
                for (uint64_t i = min_size; i < digits.size(); i++)
                {
                    temp = static_cast<uint8_t>(digits[digits.size() - 1 - i] + c);
                    digits[digits.size() - 1 - i] = temp % 10;
                    c = temp / 10;
                }
            }
            else if (digits.size() < other.digits.size())
            {
                for (uint64_t i = min_size; i < other.digits.size(); i++)
                {
                    temp = static_cast<uint8_t>(other.digits[other.digits.size() - 1 - i] + c);
                    digits.insert(digits.begin(), temp % 10);
                    c = temp / 10;
                }
            }

            // Integrating the last carried-over digit into the leftmost position of the digits.
            if (c != 0)
            {
                digits.insert(digits.begin(), c);
            }
        }
        // Employing subtraction arithmetic logic for addition-assignment of arbitrary-precision integers with opposite signs.
        else
        {
            // Handling the case where this arbitrary-precision integer has a greater absolute value than the other.
            if ((digits.size() > other.digits.size()) or ((digits.size() == other.digits.size()) and (digits > other.digits)))
            {
                // Declaring and initializing a temporary 'temp' variable which returns current digits, and borrowed digit 'b'.
                uint8_t b = 0;
                int8_t temp = 0;

                for (uint64_t i = 0; i < other.digits.size(); i++)
                {
                    temp = static_cast<int8_t>(digits[digits.size() - 1 - i] - other.digits[other.digits.size() - 1 - i] - b);
                    if (temp < 0)
                    {
                        digits[digits.size() - 1 - i] = static_cast<uint8_t>(temp + 10);
                        b = 1;
                    }
                    else
                    {
                        digits[digits.size() - 1 - i] = static_cast<uint8_t>(temp);
                        b = 0;
                    }
                }

                uint64_t i = other.digits.size();
                while (b != 0)
                {
                    temp = static_cast<int8_t>(digits[digits.size() - 1 - i] - b);
                    if (temp < 0)
                    {
                        digits[digits.size() - 1 - i] = static_cast<uint8_t>(temp + 10);
                        b = 1;
                    }
                    else
                    {
                        digits[digits.size() - 1 - i] = static_cast<uint8_t>(temp);
                        b = 0;
                    }
                    i++;
                }
            }
            // Handling the case where this arbitrary-precision integer has a lesser absolute value than the other.
            else
            {
                sign = other.sign;

                // Declaring and initializing a temporary 'temp' variable which returns current digits, and borrowed digit 'b'.
                uint8_t b = 0;
                int8_t temp = 0;

                for (uint64_t i = 0; i < digits.size(); i++)
                {
                    temp = static_cast<int8_t>(other.digits[other.digits.size() - 1 - i] - digits[digits.size() - 1 - i] - b);
                    if (temp < 0)
                    {
                        digits[digits.size() - 1 - i] = static_cast<uint8_t>(temp + 10);
                        b = 1;
                    }
                    else
                    {
                        digits[digits.size() - 1 - i] = static_cast<uint8_t>(temp);
                        b = 0;
                    }
                }

                for (uint64_t i = digits.size(); i < other.digits.size(); i++)
                {
                    temp = static_cast<int8_t>(other.digits[other.digits.size() - 1 - i] - b);
                    if (temp < 0)
                    {
                        digits.insert(digits.begin(), static_cast<uint8_t>(temp + 10));
                        b = 1;
                    }
                    else
                    {
                        digits.insert(digits.begin(), static_cast<uint8_t>(temp));
                        b = 0;
                    }
                }
            }
        }

        // Eliminating leading zero digits on the leftmost side.
        while ((digits.size() > 1) and (digits[0] == 0))
        {
            digits.erase(digits.begin());
        }

        return *this;
    }

    /**
     * @brief Overloaded subtraction-assignment operator for bigint class.
     *
     * This binary operator subtracts the values of another bigint object from the current object and modifies the current object.
     *
     * @param other The bigint object whose values will be subtracted from the current object.
     * @return A reference to the modified current object.
     */
    bigint &operator-=(const bigint &other)
    {
        // Guard against subtracting 0, subtracting from 0, and self-subtraction.
        if (digits[0] == 0)
        {
            *this = -other;
            return *this;
        }

        if (other.digits[0] == 0)
        {
            return *this;
        }

        if (*this == other)
        {
            sign = '+';
            digits = {0};
            return *this;
        }

        // Utilizing negation and addition-assignment operator overloads to implement the subtraction-assignment operator.
        *this += -other;
        return *this;
    }

    /**
     * @brief Overloaded multiplication-assignment operator for bigint class.
     *
     * This binary operator multiplies the current bigint object by another bigint object and modifies the current object.
     *
     * @param other The bigint object to be multiplied with the current object.
     * @return A reference to the modified current object.
     */
    bigint &operator*=(const bigint &other)
    {
        // Guard against multiplication by 0.
        if ((digits[0] == 0) or other.digits[0] == 0)
        {
            sign = '+';
            digits = {0};
            return *this;
        }

        // Guard against multiplication by 1.
        if ((sign == '+') and (digits[0] == 1) and (digits.size() == 1))
        {
            *this = other;
            return *this;
        }

        if ((other.sign == '+') and (other.digits[0] == 1) and (other.digits.size() == 1))
        {
            return *this;
        }

        // Guard against multiplication by -1.
        if ((sign == '-') and (digits[0] == 1) and (digits.size() == 1))
        {
            *this = -other;
            return *this;
        }

        if ((other.sign == '-') and (other.digits[0] == 1) and (other.digits.size() == 1))
        {
            if (sign == '-')
            {
                sign = '+';
            }
            else
            {
                sign = '-';
            }
            return *this;
        }

        // Determining the sign of the multiplication result.
        if (sign == other.sign)
            sign = '+';
        else
            sign = '-';

        // Declare and initialize vector 'partial_products' with the appropriate size, and a temporary variable 'temp' for individual digit by digit multiplication, and variable 'c' to handle the current digit and carry or carried-over digit.
        std::vector<uint8_t> partial_products(digits.size() + other.digits.size(), 0);
        uint8_t temp = 0;
        uint8_t c;

        // Multiply digits individually and accumulate the results in the vector 'partial_products'.
        for (uint64_t i = 0; i < digits.size(); i++)
        {
            c = 0;
            for (uint64_t j = 0; j < other.digits.size(); j++)
            {
                temp = static_cast<uint8_t>((digits[digits.size() - 1 - i] * other.digits[other.digits.size() - 1 - j]) + c);
                partial_products[partial_products.size() - 1 - i - j] += temp % 10;
                c = temp / 10 + partial_products[partial_products.size() - 1 - i - j] / 10;
                partial_products[partial_products.size() - 1 - i - j] %= 10;
            }
            partial_products[digits.size() - 1 - i] = c;
        }

        // Eliminating leading zero digits on the leftmost side.
        while (partial_products[0] == 0)
        {
            partial_products.erase(partial_products.begin());
        }

        // Rewriting the vector 'digits' of this arbitrary-precision integer with the 'partial_products' vector.
        digits.resize(partial_products.size());
        for (uint64_t i = 0; i < digits.size(); i++)
        {
            digits[i] = partial_products[i];
        }
        return *this;
    }

    /**
     * @brief Overloaded equality operator for bigint class.
     *
     * This binary operator checks if the current bigint object is equal to another bigint object.
     *
     * @param other The bigint object to compare with.
     * @return `true` if the objects are equal, `false` otherwise.
     */
    bool operator==(const bigint &other) const
    {
        if (sign != other.sign)
        {
            return false;
        }
        else if (digits.size() != other.digits.size())
        {
            return false;
        }
        else
        {
            if (digits != other.digits)
            {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Overloaded inequality operator for bigint class.
     *
     * This binary operator checks if the current bigint object is not equal to another bigint object.
     *
     * @param other The bigint object to compare with.
     * @return `true` if the two bigint objects are not equal, `false` otherwise.
     */
    bool operator!=(const bigint &other) const
    {
        // Utilizing equal-to operator overload to implement the not-equal-to operator.
        return !(*this == other);
    }

    /**
     * @brief Overloaded less-than-or-equal-to operator for bigint class.
     *
     * This binary operator checks if the value of the current bigint object is less than or equal to the value of another bigint object.
     *
     * @param other The bigint object to compare with.
     * @return `true` if the current value is less than or equal to the value of other, `false` otherwise.
     */
    bool operator<=(const bigint &other) const
    {
        if (sign != other.sign)
        {
            if (sign == '+')
            {
                return false;
            }
        }
        else
        {
            if (sign == '+')
            {
                if (digits.size() > other.digits.size())
                {
                    return false;
                }
                else if ((digits.size() == other.digits.size()) and (digits > other.digits))
                {
                    return false;
                }
            }
            else
            {
                if (digits.size() < other.digits.size())
                {
                    return false;
                }
                else if ((digits.size() == other.digits.size()) and (digits < other.digits))
                {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * @brief Overloaded less-than operator for bigint class.
     *
     * This binary operator checks if the value of the current bigint object is less than the value of another bigint object.
     *
     * @param other The bigint object to compare with.
     * @return `true` if the current value is less than the value of other, `false` otherwise.
     */
    bool operator<(const bigint &other) const
    {
        // Utilizing less-than-or-equal-to and not-equal-to operator overloads to implement the equal-to operator.
        return ((*this <= other) and (*this != other));
    }

    /**
     * @brief Overloaded greater-than-or-equal-to operator for bigint class.
     *
     * This binary operator checks if the value of the current bigint object is greater than or equal to the value of another bigint object.
     *
     * @param other The bigint object to compare with.
     * @return `true` if the current value is greater than or equal to the value of other, `false` otherwise.
     */
    bool operator>=(const bigint &other) const
    {
        // Utilizing less-than operator overload to implement the greater-than-or-equal-to operator.
        return !(*this < other);
    }

    /**
     * @brief Overloaded greater-than operator for bigint class.
     *
     * This binary operator checks if the value of the current bigint object is greater than the value of another bigint object.
     *
     * @param other The bigint object to compare with.
     * @return `true` if the current value is greater than the value of other, `false` otherwise.
     */
    bool operator>(const bigint &other) const
    {
        // Utilizing less-than-or-equal-to operator overload to implement the greater-than operator.
        return !(*this <= other);
    }

    /**
     * @brief Exception thrown by `empty_string()` if an empty string is passed to the bigint class.
     *
     */
    class empty_string : public std::invalid_argument
    {
    public:
        empty_string() : std::invalid_argument("Invalid integer string: Empty string detected!\n"){};
    };

    /**
     * @brief Exception thrown by `no_digit()` if no digit is found following the sign in the input string.
     *
     */
    class no_digit : public std::invalid_argument
    {
    public:
        no_digit() : std::invalid_argument("Invalid integer string: No digit found following the sign!\n"){};
    };

    /**
     * @brief Exception thrown by `non_digit()` if a non-digit character (excluding the sign) is found in the input string.
     *
     */
    class non_digit : public std::invalid_argument
    {
    public:
        non_digit() : std::invalid_argument("Invalid integer string: Non-digit character found (excluding the sign)!\n"){};
    };

private:
    /**
     * @brief Private member variable storing the sign of an arbitrary-precision integer value.
     *
     * The `sign` member variable retains the sign information for the associated bigint object.
     */
    char sign;
    /**
     * @brief Private member variable representing the digits of an arbitrary-precision integer value.
     *
     * The `digits` member variable is a vector containing the individual digits of the bigint object.
     */
    std::vector<uint8_t> digits;
};

/**
 * @brief Overloaded addition operator for bigint class.
 *
 * This binary operator adds two bigint objects and returns a new bigint object with the result.
 *
 * @param lhs The left-hand side bigint operand.
 * @param rhs The right-hand side bigint operand.
 * @return A new bigint object representing the sum of lhs and rhs.
 */
bigint operator+(bigint lhs, const bigint &rhs)
{
    lhs += rhs;
    return lhs;
}

/**
 * @brief Overloaded subtraction operator for bigint class.
 *
 * This binary operator subtracts the right-hand side bigint object from the left-hand side and returns a new bigint object with the result.
 *
 * @param lhs The left-hand side bigint operand.
 * @param rhs The right-hand side bigint operand.
 * @return A new bigint object representing the result of lhs - rhs.
 */
bigint operator-(bigint lhs, const bigint &rhs)
{
    lhs -= rhs;
    return lhs;
}

/**
 * @brief Overloaded multiplication operator for bigint class.
 *
 * This binary operator multiplies two bigint objects and returns a new bigint object with the result.
 *
 * @param lhs The left-hand side bigint operand.
 * @param rhs The right-hand side bigint operand.
 * @return A new bigint object representing the product of lhs and rhs.
 */
bigint operator*(bigint lhs, const bigint &rhs)
{
    lhs *= rhs;
    return lhs;
}
