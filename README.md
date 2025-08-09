By Omid Moghtader\
Email: <omidm.analytics@gmail.com>\
GitHub: <https://github.com/omidmoghtader>

# Class `bigint`

A `C++` class for handling arbitrary-precision integers using object-oriented programming.

## Introduction

`bigint` is a C++ class designed for arbitrary-precision integers, extending the capabilities of typical signed C++ integer types to accommodate extremely large or extremely small integers beyond the range of standard 64-bit signed integers.

With this class, users can perform comparisons and various arithmetic operations on integers exceeding 20 digits, a task not feasible with standard C++ data types. `bigint` class includes operator overloads for addition `+`, subtraction `-`, and multiplication `*`, along with their assignment counterparts `+=`, `-=`, and `*=`. It also supports negation `-`, comparison (`==`, `!=`, `<`, `<=`, `>`, `>=`), assignment `=`, and insertion `<<` operations.

The `bigint` class features three constructors: default, integer, and string. The default constructor returns a `bigint` object initialized to the value `0`. The second constructor accepts a signed 64-bit integer and returns its corresponding `bigint` equivalent. Lastly, the third constructor processes a string of digits, with an optional sign character on the leftmost side, transforming it into a `bigint` object.

The sign is stored in a `char` variable, and the digits are stored in a `uint8_t` vector. Subsequently, I've implemented overloaded operators to perform operations on these components.

## Methodology

In choosing an approach for this class, I opted to store the number as a vector of 8-bit unsigned integers, each representing a single decimal digit in the range of 0 to 9. This choice facilitates easier manipulation compared to using strings in C++. 

The `bigint` class comprises two private member variables:
1. `sign`: This variable retains the sign information for the associated `bigint` object. It indicates whether the integer is positive (including zero), or negative.
2. `digits`: Representing the digits of an arbitrary-precision integer value, this vector contains individual digits of the `bigint` object. Each element in the vector corresponds to a decimal digit of the integer.

## Constructors

As previously noted, this class is equipped with three constructors:
- **Default Constructor:** Creates a `bigint` object with the default value of `0`. 
- **Integer Constructor:** Constructs a new `bigint` object and initializes it with the given integer value.
  - If the integer value is less than zero, the `-` character is assigned to the `sign` member variable; otherwise, it is set to `+`.
  - Subsequently, using the `%` operator, the rightmost digit of the given integer is identified and inserted as the first element of the `digits` vector. Truncating the stored digit from the initial number with integer division by 10 allows access to the second rightmost digit of the given number. This process is repeated until all digits of the given number are converted and stored in the `digits` vector.
- **String Constructor:** Constructs a new `bigint` object and initializes it with the numeric value represented by the provided string.
    - This constructor ensures the integrity of the input string, throwing exceptions in case of undesirable entries. The validation process includes:
      1. Verification of whether the string is empty.
      2. Removal of leading and trailing white spaces.
      3. Checking if the initial non-white-space character is one of the two sign characters, followed by an expected digit.
      4. Skipping leading zeros after the sign and the first non-zero digit. If all digits after the sign are '0', the arbitrary-precision integer is assigned to `+0`.
      5. Checking for any non-digit characters (excluding the sign) to identify invalid entries.
    - If a '-' character is found on the right of the trimmed string, it is stored in the `sign` member variable. If the character is either '+' or a digit, `+` is stored in `sign`. 
    - Subsequently, each character from the string is read, and its corresponding numeric value is saved in the `digits` vector.

## Operator overloads

As mentioned earlier, this class boasts multiple operator overloads, which I will detail below:

- **`<<` Insertion:** This binary output stream operator facilitates the printing of `bigint` objects to an output stream. It begins by printing the `sign` character followed by the elements of the `digits` vector, creating the representation of the arbitrary-precision integer.

- **`=` Assignment:** This binary operator assigns the value of a `bigint` object on the right-hand side to the one on the left-hand side. 
  - It starts by assigning the `sign`, then resizes the `digits` vector to match the size of the `digits` vector of the `bigint` object on the right. 
  - Subsequently, it stores each element of the latter vector in the corresponding position of `digits` vector of the `bigint` object on the left. 
  - The implementation includes a safeguard against self-assignment to prevent unnecessary computation.

- **`-` Negation:** This unary operator negates the current `bigint` object by creating a new one with the opposite `sign`, achieved simply by swapping the sign of the arbitrary-precision integer.

- **`+=` Addition-Assignment:** This binary operator performs addition on two operands and modifies the left-hand operand with the result. 
  - To optimize efficiency, I've implemented safeguards to handle cases where one of the operands is `0` or involves an additive inverse, preventing unnecessary computations.
  - In instances where both `bigint` objects share the same sign, `sign` identification becomes unnecessary as it remains consistent between the two. In such cases, I employ a straightforward elementary school arithmetic algorithm for addition. This involves utilizing a carry-over digit, systematically adding it to the appropriate digit of the left-hand operand, while the other operand remains `const`ant.
  - In scenarios where arbitrary-precision integers exhibit opposite signs, I utilized subtraction arithmetic logic. This involves considering the sign of the `bigint` object with the greater absolute value, which is also the `sign` returned by the operation. During this process, I subtracted the operand with the smaller absolute value from the other. To prevent negative results during individual digit subtraction, I implemented borrowing logic. However, due to the definition of the `digits` vector which only has elements of type `uint8_t`, I opted to increase the corresponding digit of the subtrahend by 1 instead of decreasing digits in the minuend during the borrowing process.
  - Towards the end of this operator overload, I simplified the result by removing any leading `0` digits on the left side, ensuring the resulting `bigint` object maintains a concise and accurate representation.

- **`-=` Subtraction-Assignment:** This binary operator subtracts the values of another bigint object from the current object and modifies the current object accordingly. 
  - The implementation applies the negation and addition-assignment operator overloads. 
  - Additionally, it is guarded against subtracting `0`, subtracting from `0`, and self-subtraction to ensure accurate and efficient computation.

- **`*=` Multiplication-Assignment:** This binary operator multiplies the `bigint` object on the left by another `bigint` object on the right, modifying the left-hand object with the result.
  - To optimize efficiency, I've implemented safeguards to handle cases where one of the operands is `-1`, `0`, or `1`, preventing unnecessary computations.
  - Following that, by considering the `sign`s of both operands, I determine the `sign` of the result and apply it to the `bigint` object on the left.
  - For the multiplication algorithm, I introduce an intermediate vector named `partial_products` with a size equal to the sum of the sizes of `digits` vectors of both operand. 
  - Additionally, I employ a temporary variable `temp` for individual digit-by-digit multiplication and a variable `c` to manage the current digit and any carried-over digits.
  - Afterward, I perform individual digit mult iplication, accumulating the results in the `partial_products` vector in the appropriate order.
  - By utilizing modulo `%` and integer division `/` operators, I accumulate values in the `partial_products` vector. I ensure to carry over whenever an element in the intermediate vector reaches or exceeds `10`.
  - Then, I simplified the result by removing any leading `0` digits on the left side, ensuring the resulting `bigint` object maintains a concise and accurate representation.
  - Towards the end of this operator overload, I rewrite the `digits` vector of this arbitrary-precision integer with the values from the `partial_products` vector.

- **`+` Addition:** This binary operator, defined outside the class, adds two `bigint` objects and returns a new `bigint` object with the result. It uses the addition-assignment `+=` operator to provide the user with the result.

- **`-` Subtraction:** This binary operator, defined outside the class, subtracts the `bigint` object on the right from the one on the left, yielding a new `bigint` object with the result. It employs the subtraction-assignment `-=` operator to provide the user with the outcome.

- **`*` Multiplication:** This binary operator, defined outside the class, multiplies two `bigint` objects and returns a new `bigint` object with the result. It uses the multiplication-assignment `*=` operator to provide the user with the result.

- **`==` Equality:** This binary operator checks for equality between two `bigint` objects. It initially attempts to determine inequality, and upon failure, it confirms their equality. The comparison begins by ensuring their signs are the same, followed by a check of the sizes of their `digits` vectors. If these conditions are met, it proceeds to compare the actual contents of the `digits` vectors. If any of the three comparisons yields false, it returns `false`; otherwise, it confirms the equality of the two `bigint` objects by returning `true`.

- **`!=` Inequality:** This binary operator checks for inequality between two `bigint` objects, returning the inverse outcome of the equality operator, as a `bool`ean.

- **`<=` Less-Than-Or-Equal-To:** This binary operator evaluates whether the value of the `bigint` object on the left-hand side is less than or equal to the value of the other `bigint` object. 
  - It begins by applying logic for comparing opposite `sign`s. 
  - For operands with the same sign, it considers the size of the `digits` vector, taking the `sign` into account. 
  - In the event of having the same size, it employs lexicographical comparison for vectors in `C++`. The final `bool`ean result is then returned.

- **`<` Less-Than:** This binary operator determines whether the value of the `bigint` object on the left-hand side is less than the value of the other `bigint` object. It checks for inequality `!=` and ensures that the one on the left is less than or equal to `<=` the one on the right. The final result is then returned as a `bool`ean.

- **`>=` Greater-Than-Or-Equal-To:** This binary operator assesses whether the value of the `bigint` object on the left-hand side is greater than or equal to the value of the other `bigint` object. It achieves this by simply returning the `bool`ean opposite of the result obtained from the less-than `<` operator.

- **`>` Greater-Than:** This binary operator determines whether the value of the `bigint` object on the left-hand side is greater than the value of the other `bigint` object. It achieves this by simply returning the `bool`ean opposite of the result obtained from the less-than-or-equal-to `<=` operator.

## Exception handling

The `bigint` class is equipped with three distinct exceptions, each serving a specific purpose, to manage scenarios during the validation of integer entry from strings.
- **empty_string():** throws an exception if an empty string is supplied to the `bigint` constructor.
- **no_digit():** Raises an exception when, in a string provided to the relevant constructor, no digit is encountered after the `sign` character. This contradicts the `bigint` class design, where there should be no white-space between the `sign` and the nearest digit on its right.
- **non_digit():** Throws an exception if a non-digit character is found in the entry string (excluding the `sign`), leading to the invalidation of the string.








## Warning and error handling

While coding this class, I encountered a few warnings and errors in the outcomes that initially confused me. After looking into it, I found some good solutions for these problems:

- For addressing type casting warnings, particularly the usage of  `static_cast<uint8_t>`, I implemented it wherever a warning on type casting arose. This helped ensure proper casting among different variable types.

- To convert a character representing a digit to its corresponding numeric value, I successfully used the following statement, which provided the desired outcome.:
```
digits.push_back((uint8_t)(int_str[j] - '0'));
```
- Additionally, I faced warnings related to out-of-class definitions when attempting to assign the right-hand side operand to the other. The warning message indicated:
```
implicitly-declared 'constexpr bigint::bigint(const bigint&)' is deprecated [-Wdeprecated-copy]gcc
``` 
- Unable to initially resolve this, I turned to online resources and found a suggested solution that involved using specific line of code to address this warning as you can see beneath. For further details and the source of this solution, click [here](https://stackoverflow.com/questions/51863588/warning-definition-of-implicit-copy-constructor-is-deprecated). The line of code is represented: 

```
constexpr bigint(const bigint &other) = default;
```

## References and Resources

For my whole `C` and `C++` knowledge: [Lecture Notes for CSE 701: Foundations of Modern Scientific Programming](https://baraksh.com/CSE701/notes.php)

For definition of the assignment operator overloads: [geeksforgeeks](https://www.geeksforgeeks.org/cpp-assignment-operator-overloading/)

For additional extension understanding on `C++` and how operator overloads work: [cppreference](https://en.cppreference.com/w/cpp/language/operators)

For addressing above mentioned warning: [stackoverflow](https://stackoverflow.com/questions/51863588/warning-definition-of-implicit-copy-constructor-is-deprecated)

For Doxygen, commenting, and documentation: [Barak Shoshany's Github Page](https://github.com/bshoshany)
- [thread-pool](https://github.com/bshoshany/thread-pool)