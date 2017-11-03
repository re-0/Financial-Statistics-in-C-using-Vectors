/******
*******
*
* This script computes mean, variance, st.dev, etc using vectors
* 
******
******/
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
#include <numeric>
#include <algorithm>

// Prepare data output
template<typename A, typename B, typename C, typename D, typename E, typename F, typename G> void list(A a, B b, C c, D d, E e, F f, G g){
std::cout << a << "\t" << b << "\t" << c << "\t" << d << "\t" << e << "\t" << f << "\t" << g << std::endl;
}

double xrp_close[] = {
0.1737, 0.1757, 0.1744, 0.1735,
0.1736, 0.1745, 0.1746, 0.1734, 0.1734,
0.1739, 0.1735, 0.1735, 0.1735, 0.174, 0.174,
0.1744, 0.1736, 0.1752, 0.1736, 0.1735, 0.1747,
0.1735, 0.1729, 0.173, 0.1734, 0.1727, 0.1721,
0.1724, 0.1719, 0.1716, 0.1723, 0.1729, 0.1723,
0.171, 0.1698, 0.1703, 0.17, 0.169, 0.1692,
0.1701, 0.1703, 0.1714, 0.1709, 0.1714, 0.1714,
0.1694, 0.1675, 0.168, 0.1695, 0.1699, 0.1696,
0.1686, 0.1677, 0.1685, 0.1682, 0.1678, 0.1655,
0.1644, 0.1645, 0.163, 0.1618, 0.1626, 0.1614,
0.1629, 0.1617, 0.1586, 0.1594, 0.158, 0.157,
0.155, 0.166, 0.1633, 0.1621, 0.1677, 0.1644,
0.1656, 0.1643, 0.1664, 0.1659, 0.1638, 0.1638,
0.166, 0.1666
}; // prices in EUR

int main (){
std::vector<double> vec_xrp (xrp_close, xrp_close + sizeof(xrp_close) / sizeof(double)); // Create a vector containing the market data

// Get the min and max values
double min = *std::min_element(std::begin(vec_xrp), std::end(vec_xrp));
double max = *std::max_element(std::begin(vec_xrp), std::end(vec_xrp));

double vec_sum = std::accumulate(vec_xrp.begin(), vec_xrp.end(), 0.0); // sum of the vector
double mean = vec_sum / vec_xrp.size(); // mean of the vector

std::vector<double> vec_diff(vec_xrp.size()); // new vector to store (data point - mean)
std::transform(vec_xrp.begin(), vec_xrp.end(), vec_diff.begin(), [mean](double x){return x - mean;}); // computes and stores (data point - mean) in vec_diff

double squared_sum = std::inner_product(vec_diff.begin(), vec_diff.end(), vec_diff.begin(), 0.0); // computes (data point - mean)^2 for all the data and then the total sum
double variance = squared_sum / (vec_xrp.size() - 1);
double stdev = std::sqrt(variance);

// Do some interval stuff
double lower = mean - stdev;
double upper = mean + stdev;
std::string interval = "["+ std::to_string( lower ) +":"+ std::to_string( upper ) +"]";

char line[100] = "\t\t\t\t#####################################################";
std::cout << line << std::endl << "\t\t\t\t##" << std::setw(109) 
<< "Written by re-0                ##\n\t\t\t\t## mean, min, max, sum^2, var(x), st.dev(x), range ##" << std::endl << line << "\n\n\n";


list("mean", "\tmin", "max", "sum^2", "\tvar(x)", "\tst.dev(x)", "range");
list(mean, min, max, squared_sum, variance, stdev, interval);


std::cout << "\nThere are " << double(vec_xrp.size()) << " values present in the vector.";
return 0;
}
