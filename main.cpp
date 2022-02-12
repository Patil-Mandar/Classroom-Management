#include<iostream>
#include<fstream>
#include<vector>
#include<map>
using namespace std;


class Student{
    private:
        string fName;
        string lName;
        string pass;
        int rollNum;
        static int nextRollNum;
    public:
        vector<int> classroomJoined;
        
        Student(){};
        Student(string fName,string lName,string pass);
        string getFName(){return fName;}
        string getLName(){return lName;}
        string getPass(){return pass;}
        int getRollNum(){return rollNum;}
        int getLastRollNum(){return nextRollNum;}
        static void setLastRollNum(int rollNum);
        friend ofstream& operator << (ofstream& fout, Student &student);
        friend ifstream& operator >> (ifstream& fin, Student &student);
        friend ostream& operator << (ostream& cout, Student &student);
        ~Student(){};
};
int Student::nextRollNum = 0;

class Teacher{
    private:
        string fName;
        string lName;
        string pass;
        int id;
        static int nextID;
    public:
        vector<int> classroomCreated;

        Teacher(){};
        Teacher(string fName,string lName,string pass);
        string getFName(){return fName;}
        string getLName(){return lName;}
        string getPass(){return pass;}
        int getID(){return id;}
        int getLastID(){return nextID;}
        static void setLastID(int id);
        friend ofstream& operator << (ofstream& fout, Teacher &teacher);
        friend ifstream& operator >> (ifstream& fin, Teacher &teacher);
        friend ostream& operator << (ostream& cout, Teacher &teacher);
        ~Teacher(){};
};
int Teacher::nextID = 0;

class Classroom{
    private:
        string className;
        int classCode;
        int id;             //it's teacher id
        string notice;
        static int nextClassCode;
    public:
        vector<int> studentsJoined;

        Classroom(){};
        Classroom(string className,int id,string notice); //done
        string getClassName(){return className;}
        int getClassCode(){return classCode;}
        int getID(){return id;}
        string getNotice(){return notice;}
        void setNotice(string newNotice){notice = newNotice;}
        int getLastClassCode(){return nextClassCode;}
        static void setLastClassCode(int classCode);//done
        friend ofstream& operator << (ofstream& fout, Classroom &classroom);
        friend ifstream& operator >> (ifstream& fin, Classroom &classroom);
        friend ostream& operator << (ostream& cout, Classroom &classroom);
};
int Classroom::nextClassCode = 0;

Student registerNewStudent(string fName,string lName,string pass,map<int,Student> &students);
Teacher registerNewTeacher(string fName,string lName,string pass,map<int,Teacher> &teachers);
Classroom createNewClassroom(string className,int id,map<int,Classroom> &classrooms,string n);
Classroom joinNewClassroom(int classCode,Student student,map<int,Classroom> &classrooms);
void logedInAsStudent(Student &student,map<int,Classroom> &classrooms); //TODO
void logedInAsTeacher(Teacher &teacher,map<int,Classroom> &classrooms); //TODO
void EnterClassroomAsStudent(Student &student,map<int,Classroom> &classrooms);
void EnterClassroomAsTeacher(Teacher &teacher,map<int,Classroom> &classrooms);
void SaveAllchanges(map<int,Student> &students,map<int,Teacher> &teachers,map<int,Classroom> &classrooms);

int main(){
    int choice;
    Student student;  //temp student obj
    Teacher teacher;  //temp teacher obj
    Classroom classroom; //temp classroom obj
    map<int,Student>students;
    map<int,Teacher>teachers;
    map<int,Classroom>classrooms;
    ofstream fout;
    ifstream fin;
    string fname,lname,pass;
    int rollNum,id;

    //This block will copy all the student's data in roll+Student pair in "students" map
    fin.open("Students.data");
    // if(!fin.is_open()){throw 101;}
    while(!fin.eof()){
        fin>>student;
        students.insert(pair<int,Student>(student.getRollNum(),student));
    }
    fin.close();

    //simlarly for teachers
    fin.open("Teachers.data");
    // if(!fin.is_open()){throw 101;}
    while(!fin.eof()){
        fin>>teacher;
        teachers.insert(pair<int,Teacher>(teacher.getID(),teacher));
    }
    fin.close();
    
    //simlarly for classrooms
    fin.open("Classrooms.data");
    // if(!fin.is_open()){throw 101;}
    while(!fin.eof()){
        fin>>classroom;
        classrooms.insert(pair<int,Classroom>(classroom.getClassCode(),classroom));
    }
    fin.close();

    Student::setLastRollNum(student.getRollNum());       //sets the next rollNum to last rollNum of Students.data list
    Teacher::setLastID(teacher.getID());                 //if the data file is empty rollnum n ud are taken garbage value
    Classroom::setLastClassCode(classroom.getClassCode());     //Solution : have a psedo profile at beginning

    try{while(1){
        cout<<"**********Welcome to VIT Classroom**********\n\n";
        cout<<"\t1.\tLogin as Student\n";
        cout<<"\t2.\tLogin as Teacher\n";
        cout<<"\t3.\tRegister as new Student\n";
        cout<<"\t4.\tRegister as new Teacher\n";
        cout<<"\t5.\tQuit\n\n";
        cout<<"\t*Choose from above: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"\n\t***Login***\n";
            cout<<"Enter your Roll Number: ";
            cin>>rollNum;
            cout<<"Enter the password: ";
            cin>>pass;
            if((students[rollNum]).getPass()==pass){      
                logedInAsStudent(students[rollNum],classrooms);
            }
            else{
                cout<<"\n\t!Wrong Roll Number or Password!\n";
            }
            SaveAllchanges(students,teachers,classrooms);
            break;

        case 2:
            cout<<"\n\t***Login***\n";
            cout<<"Enter your ID: ";
            cin>>id;
            cout<<"Enter the password: ";
            cin>>pass;
            if((teachers[id]).getPass()==pass){     
                logedInAsTeacher(teachers[id],classrooms);
            }
            else{
                cout<<"\n\t!Wrong ID or Password!\n";
            }
            SaveAllchanges(students,teachers,classrooms);
            break;
        
        case 3:
            cout<<"\n\t***Registeration***\n";
            cout<<"Enter your first name: ";
            cin>>fname;
            cout<<"Enter yout last name: ";
            cin>>lname;
            do{
                cout<<"Create a *strong* password: ";
                cin>>pass;
            }while(pass.length()<5);
            student = registerNewStudent(fname,lname,pass,students);
            break;

        case 4:
            cout<<"\n\t***Registeration***\n";
            cout<<"Enter your first name: ";
            cin>>fname;
            cout<<"Enter yout last name: ";
            cin>>lname;
            do{
                cout<<"Create a *strong* password: ";
                cin>>pass;
            }while(pass.length()<5);
            teacher = registerNewTeacher(fname,lname,pass,teachers);
            break;

        case 5:
            cout<<"\n\tThanks you for using our software!!!\n\tYour data is safe with us\n";
            return 0;

        default:
            cout<<"Looks like you made a mistake. Please try again\n\n";
        }
        SaveAllchanges(students,teachers,classrooms);
    }}
    catch(int e){
        if(e==101){
            cout<<"\t!!!File Error!!! "<<e;
        }
    }
    catch(...){
        cout<<"\t!!!Somthing Went wrong!!!";
    }

    //Saving all changes in file
    SaveAllchanges(students,teachers,classrooms);
    return 0;
}

//Student
Student::Student(string fName,string lName,string pass){
    this->fName=fName;
    this->lName=lName;
    this->pass=pass;
    this->rollNum = ++nextRollNum;
}

void Student::setLastRollNum(int rollNum){
    nextRollNum=rollNum;
}

//Teachers
Teacher::Teacher(string fName,string lName,string pass){
    this->fName=fName;
    this->lName=lName;
    this->pass=pass;
    this->id = ++nextID;
}

void Teacher::setLastID(int id){
    nextID=id;
}

//Classroom
Classroom::Classroom(string className,int id,string notice){
    this->className = className;
    this->id=id;
    this->notice=notice;
    this->classCode = ++nextClassCode;
}

void Classroom::setLastClassCode(int classCode){
    nextClassCode=classCode;
}

//friend
ofstream& operator << (ofstream& fout, Student &student){
    fout<<student.rollNum<<endl;
    fout<<student.fName<<endl;
    fout<<student.lName<<endl;
    fout<<student.pass<<endl;
    return fout;
}

ifstream& operator >> (ifstream& fin, Student &student){
    fin>>student.rollNum;
    fin>>student.fName;
    fin>>student.lName;
    fin>>student.pass;
    return fin;
}

ostream& operator << (ostream& cout, Student &student){
    cout<<"\tRoll Number.: "<<student.rollNum<<endl;
    cout<<"\tName.: "<<student.fName<<" "<<student.lName<<endl;
    return cout;
}


ofstream& operator << (ofstream& fout, Teacher &teacher){
    fout<<teacher.id<<endl;
    fout<<teacher.fName<<endl;
    fout<<teacher.lName<<endl;
    fout<<teacher.pass<<endl;
    return fout;
}

ifstream& operator >> (ifstream& fin, Teacher &teacher){
    fin>>teacher.id;
    fin>>teacher.fName;
    fin>>teacher.lName;
    fin>>teacher.pass;
    return fin;
}

ostream& operator << (ostream& cout, Teacher &teacher){
    cout<<"\tID Number.: "<<teacher.id<<endl;
    cout<<"\tName.: "<<teacher.fName<<" "<<teacher.lName<<endl;
    return cout;
}

ofstream& operator << (ofstream& fout, Classroom &classroom){
    fout<<classroom.classCode<<endl;
    fout<<classroom.className<<endl;
    fout<<classroom.id<<endl;
    fout<<classroom.notice<<endl;
    fout<<classroom.studentsJoined.size()<<endl;
    for(int i=0;i<classroom.studentsJoined.size();i++){
        fout<<classroom.studentsJoined[i]<<endl;
    }
    return fout;
}

ifstream& operator >> (ifstream& fin, Classroom &classroom){
    int tempID,n;
    fin>>classroom.classCode;
    fin>>classroom.className;
    fin>>classroom.id;
    fin>>classroom.notice;
    fin>>n;
    for(int i=0;i<n;i++){
        fin>>tempID;
        classroom.studentsJoined.push_back(tempID);
    }
    return fin;
}

ostream& operator << (ostream& cout, Classroom &classroom){
    cout<<"Classroom name is "<<classroom.className<<endl;
    cout<<"Classroom code: "<<classroom.classCode<<endl;
    cout<<"Classroom's teacher id: "<<classroom.id<<endl;
    cout<<"Student roll Number who have joined:\n";
    for(int i=0;i<classroom.studentsJoined.size();i++){
        cout<<classroom.studentsJoined[i]<<endl;
    }
    return cout;
}

//separate
Student registerNewStudent(string fName,string lName,string pass,map<int,Student> &students){
    Student student(fName,lName,pass);
    students.insert(pair<int,Student>(student.getRollNum(),student));
    ofstream fout;
    fout.open("Students.data",ios::app);
    if(!fout.is_open()){throw 101;}
    fout<<student;
    fout.close();
    cout<<"\n\t***Account Successfully Created***\n";
    cout<<"Here is your information\n";
    cout<<student;
    fout.close();
    return student;
}

Teacher registerNewTeacher(string fName,string lName,string pass,map<int,Teacher> &teachers){
    Teacher teacher(fName,lName,pass);
    teachers.insert(pair<int,Teacher>(teacher.getID(),teacher));
    ofstream fout;
    fout.open("Teachers.data",ios::app);
    if(!fout.is_open()){throw 101;}
    fout<<teacher;
    fout.close();
    cout<<"\n\t***Account Successfully Created***\n";
    cout<<"Here is your information\n";
    cout<<teacher;
    return teacher;
}

Classroom createNewClassroom(string className,int id,map<int,Classroom> &classrooms,string notice){
    Classroom classroom(className,id,notice);
    classrooms.insert(pair<int,Classroom>(classroom.getClassCode(),classroom));
    ofstream fout;
    fout.open("Classrooms.data",ios::app);
    if(!fout.is_open()){throw 101;}
    fout<<classroom;
    fout.close();
    cout<<"\n\t***New Classroom Successfully Created***\n";
    cout<<"Here is the classroom information\n";
    cout<<classroom;
    return classroom;
}

Classroom joinNewClassroom(int classCode,Student student,map<int,Classroom> &classrooms){
    Classroom classroom = classrooms[classCode];
    classroom.studentsJoined.push_back(student.getRollNum());
    classrooms[classCode] = classroom;
    return classroom;
}

void logedInAsTeacher(Teacher &teacher,map<int,Classroom> &classrooms){
    int choose,classCode;
    string className,fname,lname,notice;
    Classroom classroom;
    map<int,Classroom>::iterator itr3;
    cout<<"\n\t***Loged In Successfully***\n";
    cout<<"Welcome, "<<teacher.getFName()<<"\n";
    while(1){
        cout<<"1.\tView my profile\n";
        cout<<"2.\tView all Classrooms\n";
        cout<<"3.\tEnter in classroom\n";
        cout<<"4.\tCreate new classroom\n";
        cout<<"5.\tLog Out\n";
        cout<<"Choose from above: ";
        cin>>choose;
        switch (choose)
        {
        case 1:
            cout<<teacher;
            break;
        case 2:
            cout<<"Displaying all the classroom created: \n";
            for(itr3=classrooms.begin();itr3!=classrooms.end();itr3++)
            {
                if ((itr3->second).getID() == teacher.getID()){
                    cout<<(itr3->first)<<"  "<<(itr3->second).getClassName()<<endl;
                }
            }
            cout<<endl;
            break;
        case 3:
            EnterClassroomAsTeacher(teacher,classrooms);
            break;
        case 4:
            cout<<"Enter the name of new Classroom: ";
            cin>>className;
            cout<<"Enter the notice: ";
            cin>>notice;
            classroom=createNewClassroom(className,teacher.getID(),classrooms,notice);
            break;
        case 5:
            cout<<"Loging Out\n";
            return;
        default:
            cout<<"Looks like you made a mistake. Please try again\n\n";
        }
    }
}

void logedInAsStudent(Student &student,map<int,Classroom> &classrooms){
    int choose,classCode;
    string fname,lname;
    Classroom classroom;
    map<int,Classroom>::iterator itr3;
    cout<<"\n\t***Loged In Successfully***\n";
    cout<<"Welcome, "<<student.getFName()<<"\n";
    while(1){
        cout<<"1.\tView my profile\n";
        cout<<"2.\tView all joined Classrooms\n";
        cout<<"3.\tEnter in classroom\n";
        cout<<"4.\tJoin new classroom\n";
        cout<<"5.\tLog Out\n";
        cout<<"Choose from above: ";
        cin>>choose;
        switch (choose)
        {
        case 1:
            cout<<student;
            break;
        case 2:
            cout<<"Displaying all the classroom joined:\n";
            for(itr3=classrooms.begin();itr3!=classrooms.end();itr3++)
            {
                for(int i=0;i<(itr3->second).studentsJoined.size();i++){
                    if ((itr3->second).studentsJoined[i] == student.getRollNum()){
                        cout<<(itr3->first)<<"  "<<(itr3->second).getClassName()<<endl;
                    }
                }
            }
            cout<<endl;
            break;
        case 3:
            EnterClassroomAsStudent(student,classrooms);
            break;
        case 4:
            cout<<"Enter the Class Code of new classroom: ";
            cin>>classCode;
            if(classrooms.find(classCode) == classrooms.end()){
                cout<<"Classroom not present\n";
            }
            else{
                classroom = joinNewClassroom(classCode,student,classrooms);
                student.classroomJoined.push_back(classroom.getClassCode());
                cout<<"You have joined the classroom succeddfully\n";
                cout<<"Here is the info of this classroom:\n";
                cout<<classroom;
            }
            break;
        case 5:
            cout<<"Loging Out\n";
            return;
        default:
            cout<<"Looks like you made a mistake. Please try again\n\n";
        }
    }
}

void EnterClassroomAsStudent(Student &student,map<int,Classroom> &classrooms){
    int classCode,flag=0;
    cout<<"Enter the code of classroom you want to enter\n";
    cin>>classCode;
    if(classrooms.find(classCode) == classrooms.end()){
        cout<<"Classroom not present\n";
        return;
    }
    vector<int> studentsJoined = (classrooms[classCode]).studentsJoined;
    for(int i=0;i<studentsJoined.size();i++){
        if(studentsJoined[i] == student.getRollNum()){
            flag=1;break;
        }
    }
    if(flag==0){
        cout<<"You haven't joined it this classroom yet\n";
        return;
    }
    cout<<"Here is your classroom: \n";
    cout<<classrooms[classCode];
    cout<<"\nAnd the current notice is:\n";
    cout<<classrooms[classCode].getNotice();
}

void EnterClassroomAsTeacher(Teacher &teacher,map<int,Classroom> &classrooms){
    int classCode;
    char choice;
    string newNotice;
    cout<<"Enter the code of classroom you want to enter\n";
    cin>>classCode;
    if(classrooms.find(classCode) == classrooms.end()){
        cout<<"Classroom not present\n";
        return;
    }
    if(classrooms[classCode].getID() != teacher.getID()){
        cout<<"You are not authorized to enter this classroom\n";
        return;
    }
    cout<<"Here is your classroom: \n";
    cout<<classrooms[classCode];
    cout<<"\nAnd the current notice is:\n";
    cout<<classrooms[classCode].getNotice();
    cout<<"\nDo you want to edit it? (Yes -> Y): ";
    cin>>choice;
    if(choice == 'Y'){
        cout<<"Enter the new notice\n";
        cin>>newNotice;
        classrooms[classCode].setNotice(newNotice);
        cout<<"Notice Updated\n";
    }
}

void SaveAllchanges(map<int,Student> &students,map<int,Teacher> &teachers,map<int,Classroom> &classrooms){
    ofstream fout;
    fout.open("Students.data", ios::trunc);
    map<int,Student>::iterator itr1;
    for(itr1=students.begin();itr1!=students.end();itr1++)
    {
      fout<<itr1->second;
    }
    fout.close();
    fout.open("Teachers.data", ios::trunc);
    map<int,Teacher>::iterator itr2;
    for(itr2=teachers.begin();itr2!=teachers.end();itr2++)
    {
      fout<<itr2->second;
    }
    fout.close();
    fout.open("Classrooms.data", ios::trunc);
    map<int,Classroom>::iterator itr3;
    for(itr3=classrooms.begin();itr3!=classrooms.end();itr3++)
    {
      fout<<itr3->second;
    }
    fout.close();
}