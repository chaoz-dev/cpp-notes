/** Non-static data member layout.
 *
 * Members with the same access specifier *must* be laid out in the same
 * relative ordering. In practice, the compiler may not change the layout at
 * all, even if there is a more optimal ordering.
 *
 * $ clang --version
 *
 * Ubuntu clang version 14.0.0-1ubuntu1.1
 * Target: x86_64-pc-linux-gnu
 * Thread model: posix
 * InstalledDir: /usr/bin
 *
 * $ clang -cc1 -fdump-record-layouts data-member-layout.cc
 *
 * *** Dumping AST Record Layout
 *         0 | class A
 *         0 |   double a
 *         8 |   double b
 *        16 |   double c
 *        24 |   int d
 *        32 |   double e
 *        40 |   int f
 *        48 |   double g
 *        56 |   int h
 *        60 |   int i
 *        64 |   int j
 *           | [sizeof=72, dsize=68, align=8,
 *           |  nvsize=68, nvalign=8]
 */

class A
{
public:
    double a = 1;
    double b = 1;

private:
    double c = 1;
    int d    = 1;

public:
    double e = 1;
    int f    = 1;

private:
    double g = 1;
    int h    = 1;

public:
    int i = 1;
    int j = 1;
};

int main()
{
    A{};
}
