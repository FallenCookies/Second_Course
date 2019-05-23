#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;
class Person{
public:
    Person(const string& name,const string& type_):Name(name),Type(type_){
    }
    const string Get_person() const {
        return Type+": "+Name;
    }
    virtual void Walk(const string& destination) const =0;


public:
     const string Name;
     const string Type;
};

class Student: public Person {
public:
    Student(const string& name, const string& favouriteSong):Person(name,"Student"),FavouriteSong(favouriteSong) {
    }

    void Learn() {
        cout << Get_person() << " learns" << endl;
    }

    void Walk(const string& destination)const override {
        cout << Get_person() << " walks to: " << destination << endl;
        SingSong();
    }
    void SingSong() const{
        cout <<Get_person() << " sings a song: " << FavouriteSong << endl;
    }
private:
    const string FavouriteSong;
};


class Teacher: public Person {
public:
    Teacher(const string& name, const string& subject):Person(name,"Teacher"),Subject(subject){
    }

    void Teach() {
        cout <<Get_person()<< " teaches: " << Subject << endl;
    }

    void Walk(const string& destination)const override {
        cout <<Get_person()<< " walks to: " << destination << endl;
    }

private:
    const string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name):Person(name,"Policeman") {
    }
    void Check(const Person& p) {
        cout<<Get_person()<< " checks Teacher. Teacher's name is: " << p.Name << endl;
    }
    void Walk(const string& destination)const override {
        cout <<Get_person()<< " walks to: " << destination << endl;
    }

};


void VisitPlaces(const Person& person, vector<string> places) {
    for (auto p : places) {
        person.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");
    t.Teach();
    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
