#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <memory>
#include <vector>
#include <cmath>
using namespace std;
class Figure{
public:
    Figure(){
        name="figure";
        Perim=0;
        area=0;
    }
    virtual string Name()const =0;
    virtual double Perimeter()const =0;
    virtual double Area()const =0;

protected:
    string name;
    double Perim;
    double area;
};
class Triangle: public Figure{
public:
    Triangle(int a,int b,int c):Figure(){
        name="TRIANGLE";
        Perim=a+b+c;
        double p=Perim/2;
        area=sqrt(p*(p-a)*(p-b)*(p-c));
    }
    string Name()const override{
        return name;
    }
    double Perimeter()const override{
        return Perim;
    }
    double Area()const override{
        return area;
    }
};

class Rect : public Figure{
public:
    Rect (int a,int b):Figure(){
        name="RECT";
        Perim=(a+b)*2;
        area=a*b;
    }
    string Name()const override {
        return name;
    }
    double Perimeter()const override{
        return Perim;
    }
    double Area()const override{
        return area;
    }
};

class Circle: public Figure{
public:
    Circle(int r):Figure(){
        name="CIRCLE";
        Perim=r*2*3.14;
        area=3.14*r*r;
    }
    string Name()const override{
        return name;
    }
    double Perimeter()const override{
        return Perim;
    }
    double Area()const override{
        return area;
    }
};
shared_ptr<Figure> CreateFigure(istringstream& s){
    string figure;
    s>>figure;
    if (figure=="RECT"){
        int a,b;
        s>>a>>b;
        Rect  r(a,b);

        return make_shared<Rect >(r);
    }
    if (figure=="CIRCLE"){
        int r;
        s>>r;
        Circle c(r);

        return make_shared<Circle>(c);
    }
    if (figure=="TRIANGLE"){
        int a,b,c;
        s>>a>>b>>c;
        Triangle t(a,b,c);
        return make_shared<Triangle>(t);
    }
}
int main() {
    vector<shared_ptr<Figure>> figures;

    for (string line; getline(cin, line); ) {
        istringstream is(line);
        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}