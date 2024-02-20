#ifndef QUANTITY_H_
#define QUANTITY_H_

namespace quantity
{

template<int M, int L, int T>
class Quantity
{
public:
    explicit constexpr Quantity(double x = 0.0): value(x) {}
    constexpr Quantity(const Quantity& rhs): value(rhs.value) {}
    constexpr Quantity& operator+=(const Quantity& rhs) { value += rhs.value; return *this; }
    constexpr Quantity& operator-=(const Quantity& rhs) { value -= rhs.value; return *this; }
    constexpr Quantity& operator*=(double x) { value *= x; return *this; }
    constexpr Quantity& operator/=(double x) { value /= x; return *this; }
    constexpr Quantity operator+(const Quantity& rhs) const { return Quantity(value + rhs.value); }
    constexpr Quantity operator-(const Quantity& rhs) const { return Quantity(value - rhs.value); }
    constexpr bool operator>(const Quantity& rhs) const { return value > rhs.value; }
    constexpr bool operator>=(const Quantity& rhs) const { return value >= rhs.value; }
    constexpr bool operator<(const Quantity& rhs) const { return value < rhs.value; }
    constexpr bool operator<=(const Quantity& rhs) const { return value <= rhs.value; }
    constexpr bool operator==(const Quantity& rhs) const { return value == rhs.value; }
    constexpr bool operator!=(const Quantity& rhs) const { return value != rhs.value; }
    constexpr double Convert(const Quantity& rhs) const { return value / rhs.value; }
    constexpr Quantity operator*(double x) const { return Quantity(value * x); }
    constexpr Quantity operator/(double x) const { return Quantity(value / x); }
    constexpr double GetValue() const { return value; }
private:
    double value;
};

template <int M1, int L1, int T1, int M2, int L2, int T2>
constexpr Quantity<M1 + M2, L1 + L2, T1 + T2> operator*(const Quantity<M1, L1, T1>& lhs, const Quantity<M2, L2, T2>& rhs)
{
    return Quantity<M1 + M2, L1 + L2, T1 + T2>(lhs.GetValue() * rhs.GetValue());
}

template <int M1, int L1, int T1, int M2, int L2, int T2>
constexpr Quantity<M1 - M2, L1 - L2, T1 - T2> operator/(const Quantity<M1, L1, T1>& lhs, const Quantity<M2, L2, T2>& rhs)
{
    return Quantity<M1 - M2, L1 - L2, T1 - T2>(lhs.GetValue() / rhs.GetValue());
}

template <int M, int L, int T>
constexpr Quantity<M, L, T> operator*(double lhs, const Quantity<M, L, T>& rhs)
{
    return Quantity<M, L, T>(lhs * rhs.GetValue());
}

template <int M, int L, int T>
constexpr Quantity<-M, -L, -T> operator/(double x, const Quantity<M, L, T>& rhs)
{
    return Quantity<-M, -L, -T>(x / rhs.GetValue());
}

typedef Quantity<1, 0, 0> Mass;
typedef Quantity<0, 1, 0> Length;
typedef Quantity<0, 0, 1> Time;
typedef Quantity<0, 2, 0> Area;
typedef Quantity<0, 3, 0> Volume;
typedef Quantity<0, 1, -1> Speed;
typedef Quantity<0, 1, -2> Acceleration;
typedef Quantity<0, 0, -1> Frequency;
typedef Quantity<1, 1, -2> Force;
typedef Quantity<1, -1, -2> Pressure;
typedef Quantity<1, 2, -2> Torque;
typedef Quantity<1, 2, -2> Work;
typedef Quantity<1, 2, -3> Power;
typedef Quantity<0, 2, 0> Consumption;
typedef Quantity<0, -2, 0> Economy;

constexpr Length metre(1.0);
constexpr Length decimetre = metre / 10;
constexpr Length centimetre = metre / 100;
constexpr Length millimetre = metre / 1000;
constexpr Length kilometre = 1000 * metre;
constexpr Length inch = 2.54 * centimetre;
constexpr Length foot = 12 * inch;
constexpr Length yard = 3 * foot;
constexpr Length mile = 1760 * yard;
constexpr Length nautical_mile = 1852 * metre;
constexpr Frequency hertz(1.0);

constexpr Area kilometre2 = kilometre * kilometre;
constexpr Area metre2 = metre * metre;
constexpr Area decimetre2 = decimetre * decimetre;
constexpr Area centimetre2 = centimetre * centimetre;
constexpr Area millimetre2 = millimetre * millimetre;
constexpr Area inch2 = inch * inch;
constexpr Area foot2 = foot * foot;
constexpr Area mile2 = mile * mile;

constexpr Volume kilometre3 = kilometre2 * kilometre;
constexpr Volume metre3 = metre2 * metre;
constexpr Volume decimetre3 = decimetre2 * decimetre;
constexpr Volume litre = decimetre3;
constexpr Volume centimetre3 = centimetre2 * centimetre;
constexpr Volume millimetre3 = millimetre2 * millimetre;
constexpr Volume inch3 = inch2 * inch;
constexpr Volume foot3 = foot2 * foot;
constexpr Volume mile3 = mile2 * mile;
constexpr Volume us_gallon = 3.785412 * litre;
constexpr Volume imp_gallon = 4.546090 * litre;

constexpr Time second(1.0);
constexpr Time minute = 60 * second;
constexpr Time hour = 60 * minute;
constexpr Time day = 24 * hour;

constexpr Mass kg(1.0);
constexpr Mass gramme = 0.001 * kg;
constexpr Mass tonne = 1000 * kg;
constexpr Mass ounce = 0.028349523125 * kg;
constexpr Mass pound = 16 * ounce;
constexpr Mass stone = 14 * pound;

constexpr Speed mps = metre / second;
constexpr Speed kmph = kilometre / hour;
constexpr Speed miph = mile / hour;

constexpr Acceleration mps2 = metre / (second * second);
constexpr Force newton(1.0);
constexpr Pressure q_pascal = newton / metre2;
constexpr Work joule(1.0);
constexpr Power watt = joule / second;
constexpr Torque Nm = newton * metre;
constexpr Consumption lp100km = litre / (100 * kilometre);
constexpr Economy mpg = mile / us_gallon;

constexpr Mass operator"" _kg(long double x)  { return Mass(x); }
constexpr Length operator"" _mm(long double x) { return x * millimetre; }
constexpr Length operator"" _cm(long double x)  { return x * centimetre; }
constexpr Length operator"" _m(long double x)  { return x * metre; }
constexpr Length operator"" _km(long double x)  { return x * kilometre; }
constexpr Volume operator"" _l(long double x) { return x * litre; }
constexpr Speed operator"" _mps(long double x)  { return Speed(x); }
constexpr Speed operator"" _miph(long double x) { return x * mile / hour; }
constexpr Speed operator"" _kmph(long double x) { return x * kilometre / hour; }
constexpr Force operator"" _N(long double x) { return Force(x); }
constexpr Pressure operator"" _Pa(long double x) { return Pressure(x); }
constexpr Work operator"" _J(long double x) { return Work(x); }
constexpr Power operator"" _W(long double x) { return Power(x); }
constexpr Torque operator"" _Nm(long double x) { return x * Nm; }
constexpr Consumption operator"" _lp100km(long double x) { return x * lp100km; }
constexpr Economy operator"" _mpg(long double x) { return x * mpg; }
}

#endif /* QUANTITY_H_ */
