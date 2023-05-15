#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

struct Points
{
	double x, y, z;
};

struct Cord_for_center
{
	double x,y,z;
	double distance;
};

double distance(vector<Points>points,int i, int j, int x = NULL, int y = NULL, int z = NULL)
{
	if (x == NULL) {
		return sqrt(pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2) + pow(points[i].z - points[j].z, 2));
	}
	else
		return sqrt(pow(points[i].x - x, 2) + pow(points[i].y - y, 2) + pow(points[i].z - z, 2));
}

void max_distance(double distance, double maxin,double& x,double& y,double& z, vector<Points>points, int i,int j)
{
 	if(distance > maxin){
		maxin = distance;
 	}
	x = max(points[i].x,points[j].x) - min(points[i].x,points[j].x);
	y = max(points[i].y,points[j].y) - min(points[i].y,points[j].y);
	z = max(points[i].z,points[j].z) - min(points[i].z,points[j].z);
}

void distance_to_point(vector<Cord_for_center>& cord_for_center, const vector<Points>& points, int i, double dist)
{
	Cord_for_center cord = { points[i].x, points[i].y, points[i].z, dist };
	cord_for_center[i] = cord;
}

void insertionSort(vector<Cord_for_center>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        Cord_for_center key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].distance > key.distance) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int n, k;
	cout << "Введите количество точек в пространстве: ";
	cin >> n;
	double x1 = 0, y1 = 0, z1 = 0;
	vector<Points> points(n);
	vector<Cord_for_center> cord_for_center(points.size());
	cout << "Введите координаты:" << "\n" <<"x y z" << "\n";
	for (int i = 0; i < n; ++i) {
		cin >> points[i].x >> points[i].y >> points[i].z;
	}

	double maxin = 0;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < points.size(); j++) {
			max_distance(distance(points, i, j), maxin, x1, y1, z1, points, i, j);
		}
	}


	int max_for_center = 0;
	double distance_cord;
	for (int i = 0; i < points.size(); i++) {
		distance_cord = distance(points, i, 0, x1, y1, z1);
		distance_to_point(cord_for_center, points, i, distance_cord);
	}
	insertionSort(cord_for_center);
	cout << "Введите количество минимальных точек которые необходимо охватить: ";
	cin >> k;
	cout << "Минимальный радиус шара охватывающий эти точки: " <<  cord_for_center[k - 1].distance;
	return 0;
}

/*
План
Найти max длину от 2 точек 
найти max длину от 1 пункта до точек
Дальше смотреть доску
Сделать список с 2 int параметрами
*/