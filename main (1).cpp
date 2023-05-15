#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// Структура для хранения координат точек в трехмерном пространстве
struct Points
{
    double x, y, z;
};

// Структура для хранения координат и расстояния до центра
struct Cord_for_center
{
    double x, y, z;
    double distance;
};

// Функция для вычисления расстояния между двумя точками или от заданной точки до точки с заданными координатами
double distance(vector<Points>points,int i, int j, int x = NULL, int y = NULL, int z = NULL)
{
    if (x == NULL) {
        return sqrt(pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2) + pow(points[i].z - points[j].z, 2));
    }
    else
        return sqrt(pow(points[i].x - x, 2) + pow(points[i].y - y, 2) + pow(points[i].z - z, 2));
}

// Функция для определения максимального расстояния между двумя точками и вычисления координат центра
void max_distance(double distance, double maxin,double& x,double& y,double& z, vector<Points>points, int i,int j)
{
    if(distance > maxin){
        maxin = distance;
    }
    x = max(points[i].x,points[j].x) - min(points[i].x,points[j].x);
    y = max(points[i].y,points[j].y) - min(points[i].y,points[j].y);
    z = max(points[i].z,points[j].z) - min(points[i].z,points[j].z);
}

// Функция для вычисления расстояния от заданной точки до центра
void distance_to_point(vector<Cord_for_center>& cord_for_center, const vector<Points>& points, int i, double dist)
{
    Cord_for_center cord = { points[i].x, points[i].y, points[i].z, dist };
    cord_for_center[i] = cord;
}

// Функция для сортировки массива по расстоянию от точки до центра
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
    cin >> n; // Ввод количества точек 
    double x1 = 0, y1 = 0, z1 = 0;// Объявление переменных для хранения координат центра
    vector<Points> points(n);
    vector<Cord_for_center> cord_for_center(points.size());
    cout << "Введите координаты:" << "\n" <<"x y z" << "\n";
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y >> points[i].z;
    }
    double maxin = 0;// Объявление переменной для хранения максимального расстояния

    // Вычисление максимального расстояния и координат центра
    for (int i = 0; i < points.size(); i++) {
        for (int j = 0; j < points.size(); j++) {
            max_distance(distance(points, i, j), maxin, x1, y1, z1, points, i, j);
        }
    }
    int max_for_center = 0;// Объявление переменной для хранения максимального расстояния до центра
    double distance_cord; // Объявление переменной для хранения расстояния до центра

    // Вычисление расстояний от точек до центра
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