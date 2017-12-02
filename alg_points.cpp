#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct point {
	int x, y, polar_angle, sg_dist;
};

vector <point> points;
int number_of_points;
vector <point> border;

void get_points() {
	cout << "At first enter the count of points : " << endl;
	cin >> number_of_points;
	points.resize(number_of_points + 1);
	for (int i = 0; i < number_of_points; ++i) {
		cout << "Enter coordinates of point  " << (i+1) << ":" << endl;
		cin >> points[i].x >> points[i].y;
	}
}

//знайшли крайню ліву точку, базову із якої починається порівняння по куту
void base_point() {
	int number = 0;
	for (int i = 0; i < number_of_points; i++) {
		if (points[i].x < points[number].x || (points[i].x == points[number].x && points[i].y < points[number].y))
			number = i;
	}
	swap(points[0], points[number]);
}

int tangens(point a, point b) {
	if (a.x == b.x)
		return 1;
	else
		return (b.y - a.y) / (b.x - a.x);
}

float sq_dist(point a, point b) {
	return pow((b.x - a.x), 2) + pow((b.y - a.y), 2);
}

void multiply_of_points() {
	points[0].polar_angle = 0;
	points[0].sg_dist = 0;
	for (int i = 1; i < number_of_points; i++) {
		points[i].polar_angle = tangens(points[0], points[i]);
		points[i].sg_dist = sq_dist(points[0], points[i]);
	}
	number_of_points++;
	points[number_of_points - 1] = points[0];
}

void sort() {
	for (int i = 0; i < number_of_points - 1; i++) {
		for (int k=0;k<number_of_points - 2; k++)
			if ((points[k].polar_angle > points[k + 1].polar_angle) || ((points[k].polar_angle > points[k + 1].polar_angle) && points[k].sg_dist > points[k + 1].sg_dist)) {
				swap(points[k], points[k + 1]);
			}
	}
}

//векторний добуток координат
bool rotation(int ax, int ay, int bx, int by) {
	return (ax*by - bx*ay) > 0;
}

void answer() {
	border.resize(number_of_points);
	border[0] = points[0];
	border[1] = points[1];
	int current = 2, ptr = 2;
	while (current < number_of_points) {
		int Vector_1_x = border[ptr - 1].x - border[ptr - 2].x;
		int Vector_1_y = border[ptr - 1].y - border[ptr - 2].y;
		int Vector_2_x = points[current].x - points[ptr - 1].x;
		int Vector_2_y = points[current].y - points[ptr - 1].y;
		if (rotation(Vector_1_x, Vector_1_y, Vector_2_x, Vector_2_y)) {
			border[ptr] = points[current];
			ptr++;
		}
		else {
			border[ptr - 1] = points[current];
		}
		current++;
	}
	border.resize(ptr - 1);
}

void print() {
	cout << "Number of points " << border.size() << endl;
	for (int i = 0; i < border.size(); ++i) {
		cout << border[i].x << " " << border[i].y << endl;
	}
}

int main() {
	get_points();
	base_point();
	multiply_of_points();
	sort();
	answer();
	print();
	system("pause");
	return 0;
}