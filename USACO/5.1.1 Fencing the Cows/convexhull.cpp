//
//  original Graham's scan.
//  from "CMSC 754, Computational Geometry1, David M. Mount"
//
//  This code was tested by a data-set of USACO 5.1.1 "Fencing the cows"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;
typedef pair<double, double> point;

int n;
vector<point> points;
vector<point> hull;

void input()
{
    ifstream in("in.txt");
    in >> n;
    
    for (auto i = 0; i < n; ++ i)
    {
        decltype(point::first) tmpa;
        decltype(point::second) tmpb;
        
        in >> tmpa >> tmpb;
        points.push_back(point(tmpa,tmpb));
    }
    
    sort(points.begin(), points.end(),
         [](point&a, point&b)
         {
             return (a.first == b.first)? a.second < b.second : a.first < b.first;
         });
    
    hull.resize(n*2);
}

decltype(point::first) cross(const point& o, const point& a, const point& b)
{
    return (a.first - o.first) * (b.second - o.second) - (a.second - o.second) * (b.first - o.first);
}

decltype(points) find_convexhull(const vector<point>& points)
{
    int stc = 0; //stack count;
    
    for (auto i = 0; i < n; ++ i)
    {
        while (stc >= 2 && cross(hull[stc-2], hull[stc-1], points[i]) <= 0) -- stc;
        hull[stc ++] = points[i];
    }
    
    for (int i = (int)points.size() - 2, upper_size = stc; i >= 0; -- i)
    {
        while (stc > upper_size && cross(hull[stc-2], hull[stc-1], points[i]) <= 0) -- stc;
        hull[stc ++] = points[i];
    }
    
    hull.resize(stc);
    return hull;
}

double length(const point& a, const point& b)
{
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

void output(const vector<point>& hull)
{
    double len = 0;
    for (int i = 1; i < hull.size(); ++ i)
    {
        len += length(hull[i-1], hull[i]);
    }
    cout << fixed << setprecision(2) << len << endl;
}

int main()
{
    input();
    output(find_convexhull(points));
    return 0;
}