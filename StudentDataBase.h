#pragma once


//ϣ����ʦ��������ҵ֮ǰ���Լ򵥿�һ�´�����ĵ� -- README.md лл��
/*�����Ѱ���Ҫ��ʵ������Ŀ�����й��ܣ��������������ĵ�*/



#include<set>
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<unordered_map>
#include <sstream>
#include<array>
#include<algorithm>
#include<climits>
#include<tuple>
#include<assert.h>
using namespace std;


#define pinf_double 999.99 //����������С��
#define ninf_double -999.99 //���帺����С��
#define pinf_uint 99999 //��������������
#define ninf_uint 0 //���帺��������
enum Sex
{
	MALE,FEMALE
};
//�γ�
struct CourseObj
{
public:
	string __course_name;
	double __credits;
	double __score;
public:
	CourseObj(string name, double cre, double s)
		:__course_name(name), __credits(cre), __score(s) {}
};
//��CourseObj����һ��ͨ��ָ���ӡ���ݵ�<<
void DisplayCourseInfo(ostream& out, const CourseObj* const& ptr);
struct Student
{
public:
	size_t __id;
	string __name;
	Sex __sex;
	size_t __birthday;
	size_t __school_year; //�ڼ�ѧ��
	string __birth_place;
	vector<CourseObj*>__course_list;
	double __total_score;
	double __avg_score;
	double __total_credits;
public:
	~Student()
	{
		for (auto& e : __course_list)
		{
			delete e;
		}
	}
};
//��Student����һ��ͨ��ָ�����<<
void DisplayStudentByPtr(ostream& out, const Student* const& ptr);


struct StudentDataBase
{
protected:
	//��Ϊ��ĿҪ����Ҫ��ؼ��ֲ�ѯ -- ����ҪЧ�ʸ� -- ֻ��ά����ú����
	//��ú�����ù�ϣ���
	unordered_map<string, multimap<double, size_t, greater<double>>*>__inner_maps;//��Ϊ���Ƿ��������Խ���
	unordered_map<size_t, Student*>__hash_map; //��һ����ϣ������е�ѧ����Ϣ -- key��id
	std::array<string, 5> __CourseNames = { "C Programming Language" ,"Advanced math", "College English",
		"Control Theory","Python" }; //�γ�����
protected:
	struct init_tools;//��װ��ʼ����ϣ���map����Ҫ��һЩ���߽ṹ
	tuple<size_t, size_t, size_t> __get_date(const Student* ptr);
protected:
	//һЩ����Ҫ�õ��ķº���
	struct Cmp_SortByName;
	struct Cmp_SortBySex;
	struct Cmp_SortBySchoolYear;
	struct Cmp_SortByBirthPlace;
	struct Cmp_SortByTotalCredits;
protected:
	//��ʼ��
	void __init_hash_map(ifstream& file1, ifstream& file2);
	void __init_maps();
public:
	StudentDataBase(ifstream& file1, ifstream& file2);//���캯��
	~StudentDataBase();//��������
	StudentDataBase(const StudentDataBase&) = delete;//���ݿⲻ������п�������
	StudentDataBase& operator=(const StudentDataBase&) = delete;//������ֵ��Ϊ
public:
	//������
	void SortByName(ostream& output = cout);//������������
	void SortByTotalScore(ostream& output = cout);//�����ܷ�����
	void SortByKey(ostream& output = cout, string sortKey = "C Programming Language"); // �����治ֹһ������
	/* ���ո��ַ������򣨰������գ�
	* SortByScoreWithKey()�ӿ������ṩ��8���ֶε����� -- ��sortKey��������
	* ��ϸ��ʹ�÷����� README.md�ĵ�
	*/
	void SortBySex(ostream& output = cout);//�����Ա�����
	void SortBySchoolYear(ostream& output = cout);//����ѧ������
	void SortByBirthPlace(ostream& output = cout);//���ճ���������
	void SortByTotalCredits(ostream& output = cout);//������ѧ������ 
	//�����Ѿ��ṩ��Student���������ֶε�����
	// 
	
	//���ݸ����ֶν��в���
	set<size_t> FindById(size_t id);//����id����
	set<size_t> FindByName(const string& name);//�������ֲ���
	set<size_t> FindByBirthday(const tuple<size_t, size_t, size_t>& lower_limit,
		const tuple<size_t, size_t, size_t>& upper_limit = tuple<size_t, size_t, size_t>());//�������ղ���(֧������)
	set<size_t> FindBySchoolYear(const size_t& sy);//����ѧ�����
	set<size_t> FindByScoreWithKey(string key, double lower_limit, double upper_limit = INT_MAX);
	//���շ������� --- �����治ֹһ�ֲ���
	//֧��8�ֹؼ��ֲ��� -- ��key����
	//ͬʱҲ֧�ַ�Χ����
	//����ʹ�÷����� README.md�ĵ�
	set<size_t> FindBySex(const Sex& sex);//�����Ա����
	set<size_t> CheckCredits(const double& cre);//�ж�ѧ���Ƿ���cre��
	set<size_t> ReturnAllStudents();//��������ѧ����id����
	//����id����ɾ��
	void EraseInfoByIdSet(const set<size_t>& s);
	//����id���ϴ�ӡ
	void OutputByIdSet(const set<size_t>s, ostream& out = cout);
};
//���ҽ���Ľ���
#define CAP_MAX 999 //�������ݿ���������С
set<size_t> operator|(const set<size_t>& s1, const set<size_t>& s2);
set<size_t> operator&(const set<size_t>& s1, const set<size_t>& s2);