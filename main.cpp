
#define _CRT_SECURE_NO_WARNINGS 1

//ϣ����ʦ��������ҵ֮ǰ���Լ򵥿�һ�´�����ĵ� -- README.md лл��
/*�����Ѱ���Ҫ��ʵ������Ŀ�����й��ܣ��������������ĵ�*/

using namespace std;


#if 1
#include"StudentDataBase.h"
/*
	std::array<string, 5> __CourseNames = { "C Programming Language" ,"Advanced math", "College English",
		"Control Theory","Python" };
*/
#define pinf_double 999.99 //����������С��
#define ninf_double -999.99 //���帺����С��
#define pinf_uint 99999 //��������������
#define ninf_uint 0 //���帺��������
void Run(ifstream& file1, ifstream& file2)
{
	StudentDataBase database(file1, file2);
	ofstream ofs("result_test.txt");//�Ѳ��Խ�������������
	ofs << "ϣ����ʦ��������ҵ֮ǰ���Լ򵥿�һ�´�����ĵ� -- README.md лл��" << endl << endl;
	ofs << " --------------------- ��������Ĺ��� --------------------- " << endl;
	ofs << "����������" << endl;
	database.SortByName(ofs); ofs << endl << endl;
	ofs << "��Python�ĳɼ�����" << endl;
	database.SortByKey(ofs, "Python"); //����key -- ��Ϊ����Ĺؼ���
	/*
	�ؼ�����:
	"C Programming Language" ,"Advanced math", "College English",
	"Control Theory","Python",
	"total_score","avg_score"
	*/
	ofs << endl << endl;
	ofs << " --------------------- ���Բ��ҵĹ��� --------------------- " << endl << endl;
	/*
		����key֮�⴫һ������ -- ��ʾ��ֵ����
		�������key������������ -- �����������
		���磺
			(key,30,pinf_double) �������30��
			(key,ninf_double,30) ����С��30��
		��ϸʹ�÷������������ĵ���лл
	*/
	ofs << "����C���Դ���70��С��80�ֵ�ͬѧ" << endl;
	set<size_t>ret1 = database.FindByScoreWithKey("C Programming Language", 70, 80);//����C���Դ���70��С��80�ֵ�ͬѧ
	database.OutputByIdSet(ret1, ofs);
	ofs << endl << endl;

	//���Խ�����
	ofs << "ɾ��ѧ���� Ůͬѧ��C���Բ���70�֣�����ѧ��Ϊ2021����ͬѧ" << endl;
	set<size_t>ret2 = (database.FindBySex(FEMALE)
		& database.FindByScoreWithKey("C Programming Language", ninf_double, 70))
		| database.FindBySchoolYear(2021);
	//ɾ��ѧ���� Ůͬѧ��C���Բ���70�֣�����ѧ��Ϊ2021����ͬѧ
	database.EraseInfoByIdSet(ret2);
	database.SortByName(ofs);
}
void Test(ifstream& file1, ifstream& file2)
{
	ofstream ofs("result.txt");
	ofs << "ϣ����ʦ��������ҵ֮ǰ���Լ򵥿�һ�´�����ĵ� -- README.md лл��" << endl << endl;
	StudentDataBase database(file1, file2);
	ofs << " ---------------------------------------- ��ӡ2020��ѡ��C�����ҳɼ�С��60�ֵ�ѧ�� ---------------------------------------- " << endl;
	database.OutputByIdSet(database.FindByScoreWithKey("C Programming Language", ninf_double, 60), ofs);
	ofs << endl << endl;
	ofs << " ---------------------------------------- ͳ�ƿγ�ƽ���ִ���80��ѧ��������Ϣ����� ---------------------------------------- " << endl;
	database.OutputByIdSet(database.FindByScoreWithKey("avg_score", 80, pinf_double), ofs);
	ofs << endl << endl;
	ofs << " ----------------------------------------------- ��ѯÿ��ѧ���Ƿ�����20ѧ�� ---------------------------------------------- " << endl;
	set<size_t>valid = database.CheckCredits(20);
	set<size_t>all = database.ReturnAllStudents();
	ofs << " ------ ����ѧ��������20��ѧ�� ------ " << endl;
	for (const auto& e : valid)
	{
		ofs << e << endl;
	}
	ofs << " ------ ����ѧ��û������20��ѧ�� ------ " << endl;
	vector<size_t>ans(CAP_MAX);
	set_difference(all.begin(), all.end(), valid.begin(), valid.end(), ans.begin());//��
	set<size_t>ret(ans.begin(), ans.end()); ret.erase(0);
	for (const auto& e : ret)
	{
		ofs << e << endl;
	}
}
int main()
{
	ifstream file1("StudentInfo.txt");
	ifstream file2("StudentCourse.txt");
	Run(file1, file2);
	//Test(file1, file2);
	return 0;
}
#endif