/**
 * @file demo.cpp
 * @author Omid Moghtader (omidm.analytics@gmail.com)
 *
 * @version 1.0
 * @date 2023-12-28
 *
 * @copyright Copyright (c) 2023
 *
 * @brief bigint: a class for arbitrary-precision integers, allowing arithmetic and
 * comparison operations on integers beyond the scope of signed 64-bit integer.
 * This program tests all aspects of the bigint class, but is not needed in order to use the class.
 */

#include "bigint.hpp"

int main()
{
    try
    {
        // Constructing arbitrary-precision integers using three different constructors.
        bigint x;
        bigint y(-1234567890);
        bigint z("+12345678901234567890");

        std::cout << '\n';
        std::cout << "Implementing three different constructors:\n";
        std::cout << "\tDefault constructor : x = " << x << '\n';
        std::cout << "\tInteger constructor : y = " << y << '\n';
        std::cout << "\tString  constructor : z = " << z << '\n';

        // Introducing randomly generated arbitrary-precision integers.
        const bigint initial_a("983746594765981237");
        const bigint initial_b("293847567832190475629348");
        const bigint initial_c("+784509283746593287561982");
        const bigint initial_d("-983746594765981237");
        const bigint initial_e("-65789234509873456192");
        const bigint initial_f("-34985619823476509238457694601");

        // Initializing the corresponding arbitrary-precision integers
        bigint a = initial_a;
        bigint b = initial_b;
        bigint c = initial_c;
        bigint d = initial_d;
        bigint e = initial_e;
        bigint f = initial_f;

        std::cout << '\n';
        std::cout << "Introducing randomly generated arbitrary-precision integers:\n";
        std::cout << "\ta = " << a << '\n';
        std::cout << "\tb = " << b << '\n';
        std::cout << "\tc = " << c << '\n';
        std::cout << "\td = " << d << '\n';
        std::cout << "\te = " << e << '\n';
        std::cout << "\tf = " << f << '\n';

        std::cout << '\n';
        std::cout << "Implementing addition-assignment overloaded operator:\n";
        std::cout << "\ta += b  ;  a = " << (a += b) << '\n';
        std::cout << "\tc += d  ;  c = " << (c += d) << '\n';
        std::cout << "\te += f  ;  e = " << (e += f) << '\n';

        std::cout << '\n';
        std::cout << "Implementing subtraction-assignment overloaded operator:\n";
        std::cout << "\ta -= b  ;  a = " << (a -= b) << '\n';
        std::cout << "\tc -= d  ;  c = " << (c -= d) << '\n';
        std::cout << "\te -= f  ;  e = " << (e -= f) << '\n';

        std::cout << '\n';
        std::cout << "Implementing multiplication-assignment overloaded operator:\n";
        std::cout << "\ta *= b  ;  a = " << (a *= b) << '\n';
        std::cout << "\tc *= d  ;  c = " << (c *= d) << '\n';
        std::cout << "\te *= f  ;  e = " << (e *= f) << '\n';

        std::cout << '\n';
        std::cout << "Implementing negation overloaded operator:\n";
        std::cout << "\tb  = " << b << '\n';
        std::cout << "\t-b = " << -b << '\n';
        std::cout << "\td  = " << d << '\n';
        std::cout << "\t-d = " << -d << '\n';

        // Restoring randomly generated arbitrary-precision integers to their initial values.
        a = initial_a;
        b = initial_b;
        c = initial_c;
        d = initial_d;
        e = initial_e;
        f = initial_f;

        std::cout << '\n';
        std::cout << "Restoring randomly generated arbitrary-precision integers to their initial values:\n";
        std::cout << "\ta = " << a << '\n';
        std::cout << "\tb = " << b << '\n';
        std::cout << "\tc = " << c << '\n';
        std::cout << "\td = " << d << '\n';
        std::cout << "\te = " << e << '\n';
        std::cout << "\tf = " << f << '\n';

        std::cout << std::boolalpha << '\n';
        std::cout << "Implementing comparison overloaded operators:\n";
        std::cout << "\ta == a : " << (a == a) << '\n';
        std::cout << "\ta == d : " << (a == d) << '\n';
        std::cout << "\tb == e : " << (b == e) << '\n';
        std::cout << "\tc == f : " << (c == f) << '\n';
        std::cout << "\ta != a : " << (a != a) << '\n';
        std::cout << "\ta != d : " << (a != d) << '\n';
        std::cout << "\tb != e : " << (b != e) << '\n';
        std::cout << "\tc != f : " << (c != f) << '\n';
        std::cout << "\ta <= a : " << (a <= a) << '\n';
        std::cout << "\ta <= b : " << (a <= b) << '\n';
        std::cout << "\tc <= d : " << (c <= d) << '\n';
        std::cout << "\te <= f : " << (e <= f) << '\n';
        std::cout << "\ta < a  : " << (a < a) << '\n';
        std::cout << "\ta < b  : " << (a < b) << '\n';
        std::cout << "\tc < d  : " << (c < d) << '\n';
        std::cout << "\te < f  : " << (e < f) << '\n';
        std::cout << "\ta >= a : " << (a >= a) << '\n';
        std::cout << "\ta >= b : " << (a >= b) << '\n';
        std::cout << "\tc >= d : " << (c >= d) << '\n';
        std::cout << "\te >= f : " << (e >= f) << '\n';
        std::cout << "\ta > a  : " << (a > a) << '\n';
        std::cout << "\ta > b  : " << (a > b) << '\n';
        std::cout << "\tc > d  : " << (c > d) << '\n';
        std::cout << "\te > f  : " << (e > f) << '\n';

        // Declaring three arbitrary-precision integers using the default constructor.
        bigint u, v, w;

        // Implementing assignment overloaded operator, followed by addition, subtraction, and multiplication overloaded operators.
        std::cout << '\n';
        std::cout << "Declaring three arbitrary-precision integers using the default constructor:\n";
        std::cout << "\tu = " << u << '\n';
        std::cout << "\tv = " << v << '\n';
        std::cout << "\tw = " << w << '\n';

        std::cout << '\n';
        std::cout << "Implementing assignment, addition, subtraction, and multiplication overloaded operators:\n";
        u = a + b;
        v = c + d;
        w = e + f;
        std::cout << "\tu = a + b = " << u << '\n';
        std::cout << "\tv = c + d = " << v << '\n';
        std::cout << "\tw = e + f = " << w << '\n';
        u = a - b;
        v = c - d;
        w = e - f;
        std::cout << "\tu = a - b = " << u << '\n';
        std::cout << "\tv = c - d = " << v << '\n';
        std::cout << "\tw = e - f = " << w << '\n';
        u = a * b;
        v = c * d;
        w = e * f;
        std::cout << "\tu = a * b = " << u << '\n';
        std::cout << "\tv = c * d = " << v << '\n';
        std::cout << "\tw = e * f = " << w << '\n';

        std::cout << '\n';
        std::cout << "The insertion overloaded operator has been implemented throughout the demo, representing all the outputs.\n";

        std::cout << '\n';
        std::cout << "Implementing inputs that do not adhere to the specified neat and standard format:\n";
        std::cout << "\tbigint(00)         : " << bigint(00) << '\n';
        std::cout << "\tbigint(-0)         : " << bigint(-0) << '\n';
        std::cout << "\tbigint(+0)         : " << bigint(+0) << '\n';
        std::cout << "\tbigint(\"  +000  \") : " << bigint("  +000  ") << '\n';
        std::cout << "\tbigint(\"  -000  \") : " << bigint("  -000  ") << '\n';
        std::cout << "\tbigint(\"   000  \") : " << bigint("   000  ") << '\n';
        std::cout << "\tbigint(\"  +012  \") : " << bigint("  +012  ") << '\n';
        std::cout << "\tbigint(\"  -012  \") : " << bigint("  -012  ") << '\n';
        std::cout << "\tbigint(\"   012  \") : " << bigint("   012  ") << '\n';

        std::cout << '\n';
        std::cout << "Implementing safeguards against unnecessary workloads:\n";
        std::cout << "\tbigint(0) + bigint(5)  = " << bigint(0) + bigint(5) << '\n';
        std::cout << "\tbigint(5) + bigint(0)  = " << bigint(5) + bigint(0) << '\n';
        std::cout << "\tbigint(5) + bigint(-5) = " << bigint(5) + bigint(-5) << '\n';
        std::cout << "\tbigint(0) - bigint(5)  = " << bigint(0) - bigint(5) << '\n';
        std::cout << "\tbigint(5) - bigint(0)  = " << bigint(5) - bigint(0) << '\n';
        std::cout << "\tbigint(5) - bigint(5)  = " << bigint(5) - bigint(5) << '\n';
        std::cout << "\tbigint(0) * bigint(5)  = " << bigint(0) * bigint(5) << '\n';
        std::cout << "\tbigint(5) * bigint(0)  = " << bigint(5) * bigint(0) << '\n';
        std::cout << "\tbigint(1) * bigint(5)  = " << bigint(1) * bigint(5) << '\n';
        std::cout << "\tbigint(5) * bigint(1)  = " << bigint(5) * bigint(1) << '\n';
        std::cout << "\tbigint(-1) * bigint(5) = " << bigint(-1) * bigint(5) << '\n';
        std::cout << "\tbigint(5) * bigint(-1) = " << bigint(5) * bigint(-1) << '\n';

        // Implementing exception handling.
        std::cout << '\n';
        std::cout << "NOTE:\tTo enable exception handling feature, kindly uncomment each statement in the last \n\t11 lines of `try` code block in demo.cpp file one at a time and execute the code. \n\tIt's important to note that, for better presentation, only one exception handling \n\tstatement should be uncommented at a time to observe each exception individually. \n\tFor presentation purposes, only the first statement is uncommented, ensuring it \n\tdoesn't affect the outcomes generated earlier.\n";
        std::cout << '\n';
        std::cout << "Implementing exception handling:\n";
        std::cout << "bigint(\"\") : " << bigint("") << '\n';
        // std::cout << "bigint(\"+\") : " << bigint("+") << '\n';
        // std::cout << "bigint(\"-\") : " << bigint("-") << '\n';
        // std::cout << "bigint(\"+ 123\") : " << bigint("+ 123") << '\n';
        // std::cout << "bigint(\"- 123\") : " << bigint("- 123") << '\n';
        // std::cout << "bigint(\"-12A\") : " << bigint("-12A") << '\n';
        // std::cout << "bigint(\"+1A3\") : " << bigint("-1A3") << '\n';
        // std::cout << "bigint(\"-+123\") : " << bigint("-+123") << '\n';
        // std::cout << "bigint(\"+12-34\") : " << bigint("+12-34") << '\n';
        // std::cout << "bigint(\"A123\") : " << bigint("A123") << '\n';
        // std::cout << "bigint(\"*123\") : " << bigint("*123") << '\n';
    }
    catch (const std::exception &e)
    {
        std::cout << "\tError: " << e.what() << '\n';
    }
}
