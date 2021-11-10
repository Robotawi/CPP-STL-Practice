//This is to indicate how to have a shared pointer converted into a weak pointer and vice verse \
+ the use case of a weak ptr that access data till data is unavailable (because it has no ownership).\
This is useful when we want a function to be able to access data, till this data is available. 

#include <string>
#include <memory>
#include <iostream>

using namespace std;

class Student
{
public:
    Student();
    Student(int id, string name) : _id(id), _name(name) {}

    int &getID()
    {
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
        cout << "Deleting student: " << s->getName() << endl;
        delete s;
    }
};

void printSharedStudent(shared_ptr<Student> shr_ptr)
{
    cout << "shared_ptr reference counter is: " << shr_ptr.use_count() << endl;
    cout << "Student with name " << shr_ptr->getName() << " has and ID:" << shr_ptr->getID() << endl;
}

void printWeaktudent(weak_ptr<Student> wk_ptr)
{
    //The following line works, for only use count. If we want to access the values, we must convert the weak pointer to shared
    cout << "shared_ptr reference counter is: " << wk_ptr.use_count() << endl;
    shared_ptr<Student> tmp_shr_ptr = wk_ptr.lock();
    if (tmp_shr_ptr)
    {
        cout << "Student with name " << tmp_shr_ptr->getName() << " has and ID:" << tmp_shr_ptr->getID() << endl;
    }
    else
    {
        cout << "Shared pointer expired!" << endl;
    }
}
int main(int argc, char const *argv[])
{
    weak_ptr<Student> wk_ptr;

    {
        shared_ptr<Student> shr_ptr1;

        //Notice, if we use() initialization, we need to provide a raw pointer
        shared_ptr<Student> shr_ptr2(new Student(15, "Mohamed")); //Not recommended to pass a raw pointer

        //make shared is more recommended that above because exception safe
        shared_ptr<Student> shr_ptr3 = make_shared<Student>(20, "Raessa");

        //With a deleter function, it takes a raw pointer to type and a deleter class object to be called\
        needs further consideration. It works only if unique. It is probably related to the C++ std version.

        // Student *s_raw_ptr = new Student(25, "Mohamadeen");
        // StudentDeleter sd;
        // shared_ptr<Student, StudentDeleter> shr_ptr4(s_raw_ptr, sd);

        wk_ptr = shr_ptr3; //get a weak pointer from the shared pointer

        printWeaktudent(wk_ptr); //always prints there is 1 reference count
    }

    printWeaktudent(wk_ptr); //always prints there is 0 reference count, and shows the shared pointer expired.
    // a weak pointer will never claim ownership, even if it is assigned as wk_ptr = shr_ptr3; \
    This is the way how we get a weak pointer from a shared pointer. \
    To get a shared pointer from the weak pointer (to be able to access data, not only use count), we need the lock() function,\
    which returns a shared pointer that never forgets it was acquired from a weak parent (weak ptr). Hard, but a fact! 

    return 0;
}