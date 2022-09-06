#ifndef KMEANS_H
#define KMEANS_H
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Point
{
private:
    int pointId, clusterId;
    int dimensions;
    vector<double> values;

public:
    Point(int id, string line);
    int getDimensions();
    int getCluster();
    int getID();
    void setCluster(int val);
    double getVal(int pos);
};

class Cluster
{
private:
    int clusterId;
    vector<double> centroid;
    vector<Point> points;
public:
    Cluster(int clusterId, Point centroid);
    void addPoint(Point p);
    bool removePoint(int pointId);
    int getId();
    Point getPoint(int pos);
    int getSize();
    double getCentroidByPos(int pos);
    void setCentroidByPos(int pos, double val);

};

class Kmeans
{
private:
    vector<int> m_used_pointIds;
public:
    int K, iters, dimensions, total_points;
    vector<Cluster> clusters;
    int getNearestClusterId(Point point);
    vector<int> getCenterPoint();

public:
    Kmeans(int K, int iterations);
    void run(vector<Point>& all_points);
};

#endif // KMEANS_H
