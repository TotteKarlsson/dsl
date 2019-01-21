#include <sstream>
#include <limits>
#include <complex>

//ResolveUnresolvedExternals resstd.cpp

using namespace std;
void UnresolvedSTDExternals()
{

ostringstream output;
output.precision(1);
std::ostream st;
st.exceptions(2);
st.setf( std::ios::showbase,  std::ios::showbase);

st.eof();
st.bad();
st.operator void *();
st.operator !();

char_traits<char>::compare("The Hell Boy", "rer", 'a');
char_traits<char>::find("The Hell Boy", 1, 'a');
char_traits<char>::length("The Hell Boy");
char_traits<char>::move("The Hell Boy", "tet", 1);
locale loc;
st<<use_facet <codecvt<wchar_t, char, mbstate_t> >(loc).max_length();

char_traits<wchar_t>::char_type str1[25] = L"The Hell Boy";
char_traits<wchar_t>::char_type str2[25] = L"Something To ponder";
char_traits<wchar_t>::char_type *result1;
char_traits<wchar_t>::length(str1);
result1 = char_traits<wchar_t>::move(str2, str1, 10);
result1 = char_traits<wchar_t>::copy(str1, str2, 2);
char_traits<wchar_t>::assign(*str1, *str2);
char_traits<wchar_t>::assign(str1, 2, *str2);

//ios_base::precision(2);
double test = std::numeric_limits<unsigned int>::quiet_NaN();
test = std::numeric_limits<int>::quiet_NaN();
test = std::numeric_limits<unsigned int>::quiet_NaN();
test = std::numeric_limits<int>::quiet_NaN();
test = std::numeric_limits<double>::quiet_NaN();
test = std::numeric_limits<float>::quiet_NaN();
test = std::numeric_limits<float>::infinity();
test = std::numeric_limits<double>::infinity();
test = std::numeric_limits<int>::max();

complex<double> testComplex(1,2);
testComplex = 1.2;
short v = 1;
char w = 'a';

std::ctype<char> *dfd;
dfd->is(v,w);

}
void Unlocksyslock()
{}

