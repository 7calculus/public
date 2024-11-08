#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cfloat>

using namespace std;

float dist(const vector<float>& point1, const vector<float>& point2){// missed the reference and const again...
    float distance = sqrt(pow(point1[0] - point2[0], 2) + pow(point1[1] - point2[1], 2));
    return distance;
}

void merge(const vector<vector<float>>& part1, const vector<vector<float>>& part2, vector<vector<float>>& points, int d){
    int i = 0, j = 0;
    points.clear();/*made a mistake by not clearing the vector before pushing into it... if you don't do this u'll be adding the points alongside already
    existing set of points... if you don't wanna include points.clear() then use a separate index for points vector, then you'll be overwriting on top
    of the existing points*/
    while(i < part1.size() && j < part2.size()){
        if(part1[i][d] < part2[j][d]){
            points.push_back(part1[i]);
            i++;
        } else {
            points.push_back(part2[j]);
            j++;
        }
    }
    while(i < part1.size()){
        points.push_back(part1[i]);
        i++;
    }
    while(j < part2.size()){
        points.push_back(part2[j]);
        j++;
    }
}

void mergeSort(vector<vector<float>>& points, int d){//made a mistake by not taking points as reference but instead took it by value
    int size = points.size();
    int half_size = size/2;
    if(size < 2) return;
    vector<vector<float>> part1(points.begin(), points.begin() + half_size);
    vector<vector<float>> part2(points.begin() + half_size, points.end());
    mergeSort(part1, d);
    mergeSort(part2, d);
    merge(part1, part2, points, d);
}
//made a mistake by placing both the merge and mergeSort function inside sortP function
vector<vector<float>> sortP(vector<vector<float>>& points, int d){
    mergeSort(points, d);
    return points;
}

float minimumDist_split(vector<vector<float>>& pointsX, vector<vector<float>>& pointsY, float delta, int half_n){ //made delta int first
    vector<vector<float>> ys_in_strip;
    for(auto points : pointsY){
        if(points[0] < pointsX[half_n][0] + delta && points[0] > pointsX[half_n][0] - delta){
            ys_in_strip.push_back(points);
        }
    }
    float minimum = FLT_MAX;/*initially wrote: float minimum = dist(ys_in_strip[0], ys_in_strip[1]) this can cause runtime errors
    if there are only one point in the ys_in_strip......FLT_MAX requires the header cfloat*/
    for(int i = 0; i < ys_in_strip.size(); i++){// made a mistake here by taking i <= ys_in_strip
        for(int j = i + 1; j < ys_in_strip.size() && j <= i + 7 && dist(ys_in_strip[j], ys_in_strip[i]) < delta; j++){
            /* made a mistake by writing j <= 7 rather than j <= i + 7, it has to check 7 neighers*/
            /* And I added dist(ys_in_strip[j], ys_in_strip[i]) < delta this will prevent it do distance calculation if the point
            is farther than delta inside the strip*/
            /* btw the first point will have the lowest y coordinate and overall ys_in_strip is sorted by y, so only the above stat-
            ement works...*/
            minimum = min(dist(ys_in_strip[i], ys_in_strip[j]), minimum);
        }
    }
    return minimum;
}

float minimumDist(vector<vector<float>>& pointsX, vector<vector<float>>& pointsY){
    int n = pointsX.size();
    int half_n = n/2;
    if(n == 2) return dist(pointsX[0], pointsX[1]);
    else if(n == 3) return min({dist(pointsX[0], pointsX[1]), dist(pointsX[1], pointsX[2]), dist(pointsX[2], pointsX[0])});
    vector<vector<float>> pointsXL(pointsX.begin(), pointsX.begin() + half_n);
    vector<vector<float>> pointsXR(pointsX.begin() + half_n, pointsX.end());
    float min1 = minimumDist(pointsXL, pointsY);
    float min2 = minimumDist(pointsXR, pointsY);
    float delta = min(min1, min2);
    float min3 = minimumDist_split(pointsX, pointsY, delta, half_n);

    return min(delta, min3);

}

int main(){
    freopen("closest_pair_points.txt", "r", stdin);
    int number_of_points = 100;
    vector<vector<float>> points(number_of_points), pointsX, pointsY;
    // made mistake by not initialising the number of things in number_of_points    
    
    float xs, ys;
    for(int i = 0; i < number_of_points; i++){
        cin>>xs>>ys;
        //points[i].insert(points[i].begin(), {xs, ys});//points[i] wouldn't make sense without "points(number_of_points)", me => just points
        points[i] = {xs, ys};

    }
    pointsX = sortP(points, 0);
    pointsY = sortP(points, 1);
    cout<<minimumDist(pointsX, pointsY);

    return 0;
}