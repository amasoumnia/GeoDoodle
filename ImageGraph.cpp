#include <sstream>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <numeric>
#include "ImageGraph.h"

using namespace std;

#define LATKM 110.567
#define LONGCOEFF 111.320
#define R_EARTH 6378.1370000
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

/**
 * @brief Constructs an ImageGraph object with given Cartesian points.
 * 
 * @param pts A vector of vectors containing Cartesian coordinates.
 */
ImageGraph::ImageGraph(vector<vector<float>> pts){
    cartesian_points = pts;
    n = cartesian_points.size();
    recenter();
    polar_points = to_polar(cartesian_points);
    max_r = 0;
    for (auto point : polar_points){max_r = max(point[0], max_r);}
}

/**
 * @brief Recenters the Cartesian points to have the centroid as the origin.
 */
void ImageGraph::recenter(){
    float x_sum = 0;
    float y_sum = 0;

    for (auto point : cartesian_points){
        x_sum += point[0];
        y_sum += point[1];
    }

    //compute centroid of image
    const float centroid_x = x_sum/n;
    const float centroid_y = y_sum/n;
    
    for (int i=0; i<n; i++){
        cartesian_points[i][0] -= centroid_x; //make x values relative to new origin
        cartesian_points[i][1] -= centroid_y; //make y values relative to new origin
    }
}

/**
 * @brief Converts Cartesian coordinates to polar coordinates.
 * 
 * @param cartesian A vector of vectors containing Cartesian coordinates.
 * @return A vector of vectors containing polar coordinates.
 */
vector<vector<float>> ImageGraph::to_polar(vector<vector<float>> cartesian){
    vector<vector<float>> polar(cartesian.size(), vector<float>(2,0));
    size_t i = 0;
    
    for (auto point : cartesian){
        float r = sqrt(pow(point[0], 2) + pow(point[1], 2));
        float theta = atan2(point[1],point[0]);
        
        polar[i] = {r, theta};
        i++;
    }

    return polar;
}

/**
 * @brief Converts polar coordinates to Cartesian coordinates.
 * 
 * @param polar A vector of vectors containing polar coordinates.
 * @return A vector of vectors containing Cartesian coordinates.
 */
vector<vector<float>> ImageGraph::to_cartesian(vector<vector<float>> polar){
    vector<vector<float>> cartesian(polar.size(), vector<float>(2,0));
    size_t i = 0;

    for (auto point : polar){
        float x = point[0]*cos(point[1]);
        float y = point[0]*sin(point[1]);
        
        cartesian[i] = {x,y};
        i++;
    }

    return cartesian;
}

/**
 * @brief Sets the radius of the polar points and updates the Cartesian points accordingly.
 * 
 * @param r The new radius to set.
 */
void ImageGraph::set_radius(float r){
    float factor = r/max_r;

    for (int i = 0; i < n; i++){
        polar_points[i][0] *= factor;
    }

    cartesian_points = to_cartesian(polar_points);
}

/**
 * @brief Helper function to double the density of GPS points by inserting midpoints.
 */
void ImageGraph::double_helper(){
    size_t i = 0;
    while (i<gps_points.size()-1) {
        double mid_x = (gps_points[i][0] + gps_points[i+1][0])/2;
        double mid_y = (gps_points[i][1] + gps_points[i+1][1])/2;
        vector<double> mid = {mid_x, mid_y};
        gps_points.insert(gps_points.begin()+i+1, mid);
        i += 2;
    }
}

/**
 * @brief Doubles the density of GPS points a specified number of times.
 * 
 * @param times The number of times to double the density.
 */
void ImageGraph::double_density(size_t times){
    while (times>0){
        double_helper();
        times--;
    }
}

/**
 * @brief Places the Cartesian points on a map based on a given location.
 * 
 * @param loc A vector containing the latitude and longitude of the location.
 */
void ImageGraph::place_on_map(vector<double> loc){
    location = loc;
    vector<vector<double>> gps(n, vector<double>(2,0));

    for (int i = 0; i<n; i++) {
        double lat_calc = location[0] + cartesian_points[i][1]/LATKM;
        double long_calc = location[1] + cartesian_points[i][0]/(LONGCOEFF*cos(lat_calc*M_PI/180.0));

        gps[i] = {lat_calc, long_calc};
    }

    gps_points = gps;
}

/**
 * @brief Generates a path string from the GPS points.
 * 
 * @return A string representing the path of GPS points.
 */
string ImageGraph::path(){
    stringstream s;
    s << fixed << setprecision(6);

    for (auto point : gps_points){
        s << "'" << point[0] << "," << point[1] << "'" << "/";
    }
    string out = s.str();
    out.pop_back();
    return out;
}

/**
 * @brief Gets the Cartesian points.
 * 
 * @return A vector of vectors containing Cartesian coordinates.
 */
vector<vector<float>> ImageGraph::get_cartesian(){
    return cartesian_points;
}

/**
 * @brief Gets the polar points.
 * 
 * @return A vector of vectors containing polar coordinates.
 */
vector<vector<float>> ImageGraph::get_polar(){
    return polar_points;
}

/**
 * @brief Gets the GPS points.
 * 
 * @return A vector of vectors containing GPS coordinates.
 */
vector<vector<double>> ImageGraph::get_gps(){
    return gps_points;
}
