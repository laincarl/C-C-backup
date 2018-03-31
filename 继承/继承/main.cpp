#include<fstream>
#include<strstream>
#include<sstream>
#include"Person.h"
#include"Pupil.h"
#include"Student.h"
int main()
{
	/*Person wkq("Wang", 'M', Date(1995, 12, 07), "HeNan","2014173720141737");
	Pupil wkq0("Wang", 'M', Date(1995, 12, 07), "HeNan", "2014173720141737", "s school",
		20141737, 80);
	Student wkq1("Wang", 'M', Date(1995, 12, 07), "HeNan", "2014173720141737","CQU",
		20141737, 80, "Sofeware Engineering");*/
	/*Person wkq;
	Pupil wkq0;
	Student wkq1;*/
	ifstream fin("d:\\Student.txt");
	vector<Person*>listPerson;

	string strObjType;
	Person*p = 0;
	
	while (fin >> strObjType)
	{
		
		if (strObjType == "#Person#")
		p=new Person;
		else if (strObjType == "#Pupil#")
		p = new Pupil;
		else if (strObjType == "#Student#")
		p = new Student;
		if (p)
			p->Load(fin);
		listPerson.push_back(p);

	}
	for each(auto p in listPerson)
	{
		p->Display();
	}

	/*fin >> wkq >> wkq0;// >> wkq1;
	cout << wkq << endl;
	cout << wkq0 << endl;
	cout << wkq1 << endl;*/
	/*wkq.Display();
	cout << endl;
	wkq0.Display();
	cout << endl;
	wkq1.Display();*/
	/*ofstream fout("d:\\Student.txt");
	fout << wkq << endl;
	fout << wkq0 << endl;
	fout << wkq1 << endl;

	ostringstream oss;//ostrstream 封装的是字符指针（数组）ostringstream封装的是字符串
	oss << wkq << endl;
	oss << wkq0 << endl;
	oss << wkq1 << endl;
	//oss << ends;

	cout << oss.str();
	//c.name = "Program"
	//wkq1.AddCourse(c);*/
	return 0;
}