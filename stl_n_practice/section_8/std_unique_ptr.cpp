//This is to indicate how to use unique pointer with a deleter\
it is useful when dealing with legacy C objects that have free functions or require additional cleaning

#include <string>
#include <memory>
#include <iostream>

using namespace std;

class Student
{
public:
    Student();
    Student(int id, string name) : _id(id), _name(name) {}

    int& getID(){
        return _id; 
    }

    string &getName()
    {
        return _name;
    }

private:
    int _id;
    string _name;
};

//Deleter class is implements the operator() \
making it a callable 
class StudentDeleter
{
public:
    void operator()(Student *s)
    {
        cout << "Deleting student: "<< s->getName() << endl;
        delete s; 
    }
};

int main(int argc, char const *argv[])
{
    //Normal unique pointer initialization

    unique_ptr<Student> s_ptr1();

    //Notice, if we use this way with () operator, we need to provide a raw pointer
    unique_ptr<Student> s_ptr2(new Student(10, "Mohamed1"));
    unique_ptr<Student> s_ptr3(new Student(35, "Raessa1"));

    //make unique is more recommended that above because exception safe
    unique_ptr<Student> s_ptr4 = make_unique<Student>(10, "Mohamed2");
    unique_ptr<Student> s_ptr5 = make_unique<Student>(35, "Raessa2");

    //With a deleter function, it takes a raw pointer to type and a deleter class object to be called
    Student* s_raw_ptr = new Student(10, "Mohamed3"); 
    StudentDeleter s_del; 
    unique_ptr<Student, StudentDeleter> s_ptr6(s_raw_ptr, s_del);
    cout << "Student: " << s_ptr6->getName() << " has an ID: " << s_ptr6->getID() << endl; 
    return 0;
}
