/** Size and layout of empty classes.
 *
 * Empty classes are (at least) 1 byte.
 *
 * $ clang --version
 *
 * Ubuntu clang version 14.0.0-1ubuntu1.1
 * Target: x86_64-pc-linux-gnu
 * Thread model: posix
 * InstalledDir: /usr/bin
 *
 * $ clang -cc1 -fdump-record-layouts empty-classes.cc
 *
 * *** Dumping AST Record Layout
 *          0 | class non_empty_class::A
 *          0 |   int i
 *            | [sizeof=4, dsize=4, align=4,
 *            |  nvsize=4, nvalign=4]
 *
 * *** Dumping AST Record Layout
 *          0 | class empty_class::A (empty)
 *            | [sizeof=1, dsize=1, align=1,
 *            |  nvsize=1, nvalign=1]
 *
 * *** Dumping AST Record Layout
 *          0 | class unique_address::A
 *          0 |   class empty_class::A a (empty)
 *            | [sizeof=1, dsize=1, align=1,
 *            |  nvsize=1, nvalign=1]
 *
 * *** Dumping AST Record Layout
 *          0 | class empty_class::B (empty)
 *            | [sizeof=1, dsize=1, align=1,
 *            |  nvsize=1, nvalign=1]
 *
 * *** Dumping AST Record Layout
 *          0 | class empty_class::C (empty)
 *            | [sizeof=1, dsize=1, align=1,
 *            |  nvsize=1, nvalign=1]
 *
 * *** Dumping AST Record Layout
 *          0 | class unique_address::B
 *          0 |   class empty_class::A a (empty)
 *          1 |   class empty_class::B b (empty)
 *          2 |   class empty_class::C c (empty)
 *            | [sizeof=3, dsize=3, align=1,
 *            |  nvsize=3, nvalign=1]
 *
 * *** Dumping AST Record Layout
 *          0 | class unique_address::C
 *          0 |   class empty_class::A a (empty)
 *          1 |   class empty_class::A aa (empty)
 *          2 |   class empty_class::A aaa (empty)
 *            | [sizeof=3, dsize=3, align=1,
 *            |  nvsize=3, nvalign=1]
 *
 * *** Dumping AST Record Layout
 *          0 | class unique_address::D
 *          0 |   class empty_class::A a (empty)
 *          4 |   class non_empty_class::A a_
 *          4 |     int i
 *            | [sizeof=8, dsize=8, align=4,
 *            |  nvsize=8, nvalign=4]
 *
 * *** Dumping AST Record Layout
 *          0 | class non_unique_address::A (empty)
 *          0 |   class empty_class::A a (empty)
 *          0 |   class empty_class::B b (empty)
 *          0 |   class empty_class::C c (empty)
 *            | [sizeof=1, dsize=0, align=1,
 *            |  nvsize=1, nvalign=1]
 *
 * *** Dumping AST Record Layout
 *          0 | class non_unique_address::B (empty)
 *          0 |   class empty_class::A a (empty)
 *          1 |   class empty_class::A aa (empty)
 *          2 |   class empty_class::A aaa (empty)
 *            | [sizeof=3, dsize=0, align=1,
 *            |  nvsize=3, nvalign=1]
 *
 * *** Dumping AST Record Layout
 *          0 | class non_unique_address::C
 *          0 |   class empty_class::A a (empty)
 *          0 |   class empty_class::B b (empty)
 *          0 |   class non_empty_class::A a_
 *          0 |     int i
 *            | [sizeof=4, dsize=4, align=4,
 *            |  nvsize=4, nvalign=4]
 *
 * *** Dumping AST Record Layout
 *          0 | class non_unique_address::D
 *          0 |   class empty_class::A a (empty)
 *          1 |   class empty_class::A aa (empty)
 *          0 |   class non_empty_class::A a_
 *          0 |     int i
 *            | [sizeof=4, dsize=4, align=4,
 *            |  nvsize=4, nvalign=4]
 *
 */

namespace empty_class
{

// 1 byte.
class A
{
};

// 1 byte.
class B
{
};

// 1 byte.
class C
{
};

} // namespace empty_class

namespace non_empty_class
{

// 4 bytes.
class A
{
    int i = 1;
};

} // namespace non_empty_class

namespace unique_address
{

// 1 byte.
class A
{
    empty_class::A a{};
};

// 3 bytes.
class B
{
    empty_class::A a{};
    empty_class::B b{};
    empty_class::C c{};
};

// 3 bytes.
class C
{
    empty_class::A a{};
    empty_class::A aa{};
    empty_class::A aaa{};
};

// 8 bytes.
class D
{
    empty_class::A a{};

    non_empty_class::A a_{};
};

} // namespace unique_address

namespace non_unique_address
{

// 1 byte.
class A
{
    [[no_unique_address]] empty_class::A a{};
    [[no_unique_address]] empty_class::B b{};
    [[no_unique_address]] empty_class::C c{};
};

// 3 bytes.
class B
{
    [[no_unique_address]] empty_class::A a{};
    [[no_unique_address]] empty_class::A aa{};
    [[no_unique_address]] empty_class::A aaa{};
};

// 4 bytes.
class C
{
    [[no_unique_address]] empty_class::A a{};
    [[no_unique_address]] empty_class::B b{};

    [[no_unique_address]] non_empty_class::A a_{};
};

// 4 bytes.
class D
{
    [[no_unique_address]] empty_class::A a{};
    [[no_unique_address]] empty_class::A aa{};

    [[no_unique_address]] non_empty_class::A a_{};
};

} // namespace non_unique_address

int main()
{
    empty_class::A{};
    empty_class::B{};
    empty_class::C{};

    non_empty_class::A{};

    unique_address::A{};
    unique_address::B{};
    unique_address::C{};
    unique_address::D{};

    non_unique_address::A{};
    non_unique_address::B{};
    non_unique_address::C{};
    non_unique_address::D{};
}
