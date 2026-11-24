#include <iostream>
#include <string>

using namespace std;

class Person
{
private:
    string name;
    int age;

public:
    void setName(string personName)
    {
        name = personName;
    }

    string getName()
    {
        return name;
    }

    void setAge(int personAge)
    {
        age = personAge;
    }

    int getAge()
    {
        return age;
    }

    virtual void displayInfo()
    {
        cout << "Name: " << getName() << '\n';
        cout << "Age: " << getAge() << '\n';
    }
};

class Employee : public Person
{
private:
    int employeeID;

public:
    void setEmployeeID(int id)
    {
        employeeID = id;
    }

    void displayInfo() override
    {
        Person::displayInfo();
        cout << "Employee ID: " << employeeID << '\n';
    }
};

class Student : public Person
{
private:
    int studentID;

public:
    void setStudentID(int id)
    {
        studentID = id;
    }

    void displayInfo() override
    {
        Person::displayInfo();
        cout << "Student ID: " << studentID << '\n';
    }
};

int main()
{
    Person person;
    person.setName("Alex Morgan");
    person.setAge(35);
    person.displayInfo();

    cout << '\n';

    Employee employee;
    employee.setName("Jamie Lee");
    employee.setAge(29);
    employee.setEmployeeID(1001);
    employee.displayInfo();

    cout << '\n';

    Student student;
    student.setName("Taylor Kim");
    student.setAge(20);
    student.setStudentID(2001);
    student.displayInfo();

    return 0;
}
