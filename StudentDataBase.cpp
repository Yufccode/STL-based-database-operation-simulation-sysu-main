
#define _CRT_SECURE_NO_WARNINGS 1



#include"StudentDataBase.h"


//ϣ����ʦ��������ҵ֮ǰ���Լ򵥿�һ�´�����ĵ� -- README.md лл��
//���к�������������ĵ�������
/*�����Ѱ���Ҫ��ʵ������Ŀ�����й��ܣ��������������ĵ�*/


/* ----------------------------------------------- Student��CourseObj�Ĵ�ӡ ----------------------------------------------- */
//��CourseObj����һ��ͨ��ָ���ӡ���ݵ�<<
void DisplayCourseInfo(ostream& out, const CourseObj* const& ptr)
{
	out << "CourseName: " << ptr->__course_name << endl;
	out << "Credits : " << ptr->__credits << endl;
	out << "Score : " << ptr->__score << endl;
	out << endl;
}
//��Student����һ��ͨ��ָ�����<<
void DisplayStudentByPtr(ostream& out, const Student* const& ptr)
{
	out << " -------------------- Student Info Begin -------------------- " << endl;
	out << "Name: " << ptr->__name << endl;
	out << "Id: " << ptr->__id << endl;
	out << "Sex: " << (ptr->__sex == FEMALE ? "Female" : "Male") << endl;
	out << "Birthday: " << ptr->__birthday << endl;
	out << "SchoolYear: " << ptr->__school_year << endl;
	out << "BirthPlace: " << ptr->__birth_place << endl;
	out << " ========= CourseInfo Begin ========= " << endl;
	for (const auto& e : ptr->__course_list)
	{
		//e -- CourseObj*
		DisplayCourseInfo(out, e);
	}
	out << "TotalScore: " << ptr->__total_score << endl;
	out << "AvgScore: " << ptr->__avg_score << endl;
	out << "TotalCredits : " << ptr->__total_credits << endl;
	out << " ========= CourseInfo End =========== " << endl;
	out << " -------------------- Student Info End ---------------------- " << endl;
}


/* ------------------------------------------------- ���ҽ���Ľ����� ------------------------------------------------- */
set<size_t> operator|(const set<size_t>& s1, const set<size_t>& s2)
{
	vector<size_t>ret(CAP_MAX);
	set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), ret.begin());//����
	//��ʱret������ж������0 -- ѧ����id������Ϊ0
	set<size_t>ans(ret.begin(), ret.end());
	ans.erase(0);//����ֱ�ӵ���erase -- ���ȣ�ѧ��id�϶�����0������0λ�ں������root -- ����������O(1)�Ĳ���
	return ans;
}
set<size_t> operator&(const set<size_t>& s1, const set<size_t>& s2)
{
	vector<size_t>ret(CAP_MAX);
	set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), ret.begin());//����
	set<size_t>ans(ret.begin(), ret.end());
	ans.erase(0);
	return ans;
}


/* --------------------------------------------- ���ݿ��ڲ��ӿڶ���protected: --------------------------------------------- */
struct StudentDataBase::init_tools
{
	size_t __clean_the_str(string& str)
	{
		string ret;
		for (auto& e : str)
		{
			if (isdigit(e))
			{
				ret.push_back(e);
			}
		}
		return stoi(ret);
	}
	void __deal_the_sen(Student* ptr, string str)
	{
		vector<string>words;
		istringstream line(str);
		string word;
		while (line >> word)
		{
			words.push_back(word);
		}
		ptr->__id = stoi(words[0]);
		ptr->__name = words[1];
		ptr->__sex = (words[2] == "Female" ? FEMALE : MALE);
		ptr->__birthday = __clean_the_str(words[3]);
		ptr->__school_year = stoi(words[4]);
		ptr->__birth_place = words[5];
	}
	size_t get_line_id(string& str)
	{
		istringstream line(str);
		string word;
		line >> word;
		return stoi(word);
	}
	void __init_course_list(string& str, vector<CourseObj*>& v)
	{
		//�Ȱ����е�����ȡ����
		istringstream line(str);
		vector<string>words;
		string word;
		while (line >> word)
		{
			words.push_back(word);
		}
		//���words����[0]λ�õ�Ԫ�ز����ã���Ϊ�����Ѿ�ȷ�����ڶ��ĸ�vector���в�����
		string course_name;
		//�ѿγ������ҵ�
		size_t i = 0;
		for (i = 1;; i++)
		{
			if (isdigit(words[i][0]))break;
			course_name += words[i];
			course_name += ' ';
		}
		//��ʱ��course_name���һ���ո�
		course_name.pop_back();
		double cre = stod(words[i++]);
		double s = stod(words[i]);
		CourseObj* pobj = new CourseObj(course_name, cre, s);
		v.push_back(pobj);
	}
	template<class iterator>
	iterator my_find_if(iterator start, iterator end, const string& name)
	{
		while (start != end)
		{
			if ((*start)->__course_name == name)return start;
			start++;
		}
		return end;
	}
};
struct StudentDataBase::Cmp_SortByName
{
	bool operator()(Student* ptr1, Student* ptr2)
	{
		return ptr1->__name < ptr2->__name;
	}
};
struct StudentDataBase::Cmp_SortBySex
{
	bool operator()(Student* ptr1, Student* ptr2)
	{
		return ptr1->__sex < ptr2->__sex;
	}
};
struct StudentDataBase::Cmp_SortBySchoolYear
{
	bool operator()(Student* ptr1, Student* ptr2)
	{
		return ptr1->__school_year < ptr2->__school_year;
	}
};
struct StudentDataBase::Cmp_SortByBirthPlace
{
	bool operator()(Student* ptr1, Student* ptr2)
	{
		return ptr1->__birth_place < ptr2->__birth_place;
	}
};
struct StudentDataBase::Cmp_SortByTotalCredits
{
	bool operator()(Student* ptr1, Student* ptr2)
	{
		return ptr1->__total_credits < ptr2->__total_credits;
	}
};
void StudentDataBase::__init_hash_map(ifstream& file1, ifstream& file2)
{
	//����Щ��Ϣ�浽��ϣ����
	string cur_sen;
	size_t line_number = 0;
	//�����һ���ļ�
	while (getline(file1, cur_sen))
	{
		line_number++;
		if (line_number == 1)continue;//������һ��
		Student* newStudentPtr = new Student;
		init_tools().__deal_the_sen(newStudentPtr, cur_sen);
		__hash_map.insert({ newStudentPtr->__id,newStudentPtr });
	}
	//����ڶ����ļ�
	line_number = 0;
	while (getline(file2, cur_sen))
	{
		line_number++;
		if (line_number == 1)continue;//������һ��
		//�Ȱ�ÿһ�е�id�ҵ� -- Ȼ��ͨ�����id�ڹ�ϣ�����ҵ��Ѿ�new�õ�Student�����ָ��
		size_t cur_id = init_tools().get_line_id(cur_sen);
		Student* cur_student_ptr = __hash_map[cur_id];
		//�����ָ�������__course_list���в���
		init_tools().__init_course_list(cur_sen, cur_student_ptr->__course_list);
	}
	//�ߵ��������ѧ������Ϣ�Ѿ������
	//�����ֻܷ�û�д���� -- ����һ���ܷ֣������ܵ�ѧ��
	for (auto& e : __hash_map)
	{
		e.second->__total_score = 0;
		e.second->__total_credits = 0;
		for (auto& ee : e.second->__course_list)
		{
			e.second->__total_score += ee->__score; //û����ֱ����0����
			e.second->__total_credits += ee->__credits;
		}
		e.second->__avg_score = e.second->__total_score /
			((double)e.second->__course_list.size());
	}
}
void StudentDataBase::__init_maps()
{
	//��Ϊ�γ������ǹ̶��� -- ����д��map�Ĺ��� -- ά��8��map��ÿ��map��Ӧ���Ӧ���ֶ�
	__inner_maps.insert({ "total_score",new multimap<double, size_t,greater<double>> });
	__inner_maps.insert({ "avg_score",new multimap<double, size_t,greater<double>> });
	for (const auto& e : __CourseNames)
	{
		__inner_maps.insert({ e,new multimap<double, size_t,greater<double>> });
	}
	__inner_maps.insert({ "birthday",new multimap<double, size_t,greater<double>> });
	//0-total_score 1-cprog 2-Advanced math 3-College English
	//4-Control Theory 5-Python 6-birthday 8-avg_score
	cout << endl;
	for (const auto& e : __hash_map)
	{
		//e -- {id,ptr}
		Student* cur_ptr = e.second;
		auto& v = cur_ptr->__course_list;
		//��ÿһ�Ƶĳɼ��ҵ�
		for (const auto& ee : __CourseNames)
		{
			string name = ee;
			size_t id = e.first;
			auto it = init_tools().my_find_if(v.begin(), v.end(), name);
			if (it == v.end())
			{
				//�Ҳ������ſε���Ϣ
				continue;
			}
			//�ҵ��� -- �����ſεķ������뵽map����ȥ
			double score = (*it)->__score;
			__inner_maps[name]->insert({ score,id });
		}
		//�����Ѿ��������5��map �������ֺܷ�ƽ���ֺ�birthday��
		__inner_maps["birthday"]->insert({ cur_ptr->__birthday,e.first });
		__inner_maps["total_score"]->insert({ cur_ptr->__total_score,e.first });
		__inner_maps["avg_score"]->insert({ cur_ptr->__avg_score,e.first });
	}
}
tuple<size_t, size_t, size_t> StudentDataBase::__get_date(const Student* ptr)
{
	size_t year;
	size_t month;
	size_t day;
	string str = to_string(ptr->__birthday);
	assert(str.size() == 8);//�ַ����ĳ���Ӧ����8
	year = stoi(str.substr(0, 4));
	month = stoi(str.substr(4, 2));
	day = stoi(str.substr(6, 2));
	return make_tuple(year, month, day);
}

/* --------------------------------------------- ���ݿ��ڲ��ӿڶ���public: --------------------------------------------- */
StudentDataBase::StudentDataBase(ifstream& file1, ifstream& file2)
{
	__init_hash_map(file1, file2);
	__init_maps();
}
StudentDataBase::~StudentDataBase()
{
	//ѭ���ͷ�8��multimap��ָ��
	for (const auto& e : __inner_maps)
	{
		//e -- {string,multimap*}
		delete e.second;
	}
	//ѭ���ͷ�8��Student*
	for (const auto& e : __hash_map)
	{
		delete e.second;
	}
}
//������
void StudentDataBase::SortByName(ostream& output)
{
	//��Ϊ��������û��ά��map������ֻ��ȡ������������
	vector<Student*>arr;
	for (const auto& e : __hash_map)
	{
		arr.push_back(e.second);
	}
	sort(arr.begin(), arr.end(), Cmp_SortByName());
	for (const auto& e : arr)
	{
		DisplayStudentByPtr(output, e);
	}
}
void StudentDataBase::SortByTotalScore(ostream& output)
{
	//�����ܷ����򲢴�ӡ
	//�ܷ���������ά��map�� -- ����ֱ�Ӵ�ӡ������
	//���map�Ĺؼ����� "total_score" 
	auto& usingMapPtr = __inner_maps["total_score"];
	//�������map
	for (const auto& e : (*usingMapPtr))
	{
		size_t cur_id = e.second;
		Student* cur_stu_ptr = __hash_map[cur_id];
		DisplayStudentByPtr(output, cur_stu_ptr);
	}
}
void StudentDataBase::SortByKey(ostream& output, string sortKey)
{
	//�������ͨ�ش���ؼ��������� -- ���߳�����Ҫ��һ�ŵĳɼ�������
	auto& usingMapPtr = __inner_maps[sortKey];
	//�������map
	for (const auto& e : (*usingMapPtr))
	{
		size_t cur_id = e.second;
		Student* cur_stu_ptr = __hash_map[cur_id];
		DisplayStudentByPtr(output, cur_stu_ptr);
	}
}
void StudentDataBase::SortBySex(ostream& output)
{
	vector<Student*>arr;
	for (const auto& e : __hash_map)
	{
		arr.push_back(e.second);
	}
	sort(arr.begin(), arr.end(), Cmp_SortBySex());
	for (const auto& e : arr)
	{
		DisplayStudentByPtr(output, e);
	}
}
void StudentDataBase::SortBySchoolYear(ostream& output)
{
	vector<Student*>arr;
	for (const auto& e : __hash_map)
	{
		arr.push_back(e.second);
	}
	sort(arr.begin(), arr.end(), Cmp_SortBySchoolYear());
	for (const auto& e : arr)
	{
		DisplayStudentByPtr(output, e);
	}
}
void StudentDataBase::SortByBirthPlace(ostream& output)
{
	vector<Student*>arr;
	for (const auto& e : __hash_map)
	{
		arr.push_back(e.second);
	}
	sort(arr.begin(), arr.end(), Cmp_SortByBirthPlace());
	for (const auto& e : arr)
	{
		DisplayStudentByPtr(output, e);
	}
}
void StudentDataBase::SortByTotalCredits(ostream& output)
{
	vector<Student*>arr;
	for (const auto& e : __hash_map)
	{
		arr.push_back(e.second);
	}
	sort(arr.begin(), arr.end(), Cmp_SortByTotalCredits());
	for (const auto& e : arr)
	{
		DisplayStudentByPtr(output, e);
	}
}
//���ݸ����ֶν��в���
set<size_t> StudentDataBase::FindById(size_t id)
{
	set<size_t>s;
	s.insert(id);
	return s;
}
set<size_t> StudentDataBase::FindByName(const string& name)
{
	//O(n)���Բ���
	set<size_t>s;
	for (const auto& e : __hash_map)
	{
		if (e.second->__name == name)
		{
			s.insert(e.first);
		}
	}
	return s;
}
set<size_t> StudentDataBase::FindByBirthday(const tuple<size_t, size_t, size_t>& lower_limit,
	const tuple<size_t, size_t, size_t>& upper_limit)
{
	set<size_t>s;
	//��FindByScoreWithKeyһ�� -- ����ͨ��������������ж��ǵ������һ��Ƿ�Χ����
	if (get<0>(upper_limit) == 0 && get<1>(upper_limit) == 0 && get<2>(upper_limit) == 0)
	{
		//˵��ֻ������һ��tuple  -- ����������
		size_t year = get<0>(lower_limit);
		size_t month = get<1>(lower_limit);
		size_t day = get<2>(lower_limit);
		for (const auto& e : __hash_map)
		{
			tuple<size_t, size_t, size_t>cur_date = __get_date(e.second);
			//�ж�cur_date����������Ҫ���ҵ��Ƿ����
			size_t cur_year = get<0>(cur_date);
			size_t cur_month = get<1>(cur_date);
			size_t cur_day = get<2>(cur_date);
			if ((cur_year == year || year == pinf_uint)
				&& (cur_month == month || month == pinf_uint)
				&& (cur_day == day || day == pinf_uint))
			{
				s.insert(e.first);
			}
		}
	}
	else
	{
		//��Χ����
		//���lower_limitȫ������pinf��˵�����ҷ�Χֻ�����ֵ
		//���upper_limitȫ������pinf��˵�����ҷ�Χֻ����Сֵ
		//���ҷ�Χ���� -- ����tuple��Ҫ����

		//Ŀǰ��ֻ֧����ݵķ�Χ����
		size_t lower_limit_year = get<0>(lower_limit);
		size_t upper_limit_year = get<0>(upper_limit);
		for (const auto& e : __hash_map)
		{
			tuple<size_t, size_t, size_t>cur_date = __get_date(e.second);
			//�ж�cur_date����������Ҫ���ҵ��Ƿ����
			size_t cur_year = get<0>(cur_date);
			if (cur_year < upper_limit_year && cur_year >= lower_limit_year)
			{
				s.insert(e.first);
			}
		}
	}
	return s;
}
set<size_t> StudentDataBase::FindBySchoolYear(const size_t& sy)
{
	set<size_t>s;
	for (const auto& e : __hash_map)
	{
		if (e.second->__school_year == sy)
		{
			s.insert(e.first);
		}
	}
	return s;
}
set<size_t> StudentDataBase::FindByScoreWithKey(string key, double lower_limit, double upper_limit)
{
	/// ��������ѧ��id�ļ��ϼ���
	/*
	�ؼ�����:
	"C Programming Language" ,"Advanced math", "College English",
	"Control Theory","Python",
	"total_score","avg_score"
	*/
	//key��lower_limit�Ǳ��봫�� -- ���ֻ����lower_limit��ʱ�򣬴��������ң��������Χ����
	set<size_t>ans;
	if (upper_limit == DBL_MAX)
	{
		//��������
		auto& usingMap = *(__inner_maps[key]);
		//��multimap��equal_rangeȥ�������з���������stu
		//�������ҵ�Ч����logn -- Ч�ʷǳ���
		auto retPair = usingMap.equal_range(lower_limit);
		auto start = retPair.first;
		auto end = retPair.second;
		while (start != end)
		{
			ans.insert(start->second);
			start++;
		}
	}
	else
	{
		//�������
		auto& usingMap = *(__inner_maps[key]);
		//�������������Ч�ʾ���logn -- Ч�ʷǳ��ߣ�
		auto start = usingMap.upper_bound(upper_limit);//��������
		auto end = usingMap.lower_bound(lower_limit);//��������
		//start++;//��Ϊlower_bound��upper_bound�ҵ����Ǳ�����
		while (start != end && start != usingMap.end())
		{
			ans.insert(start->second);
			start++;
		}
	}
	return ans;
}
set<size_t> StudentDataBase::FindBySex(const Sex& sex)
{
	//����O(n)����
	set<size_t>s;
	for (const auto& e : __hash_map)
	{
		if (e.second->__sex == sex)
		{
			s.insert(e.first);
		}
	}
	return s;
}
set<size_t> StudentDataBase::CheckCredits(const double& cre)
{
	set<size_t>s;
	for (const auto& e : __hash_map)
	{
		if (e.second->__total_credits >= cre)
		{
			s.insert(e.first);
		}
	}
	return s;
}
set<size_t> StudentDataBase::ReturnAllStudents()
{
	set<size_t>s;
	for (const auto& e : __hash_map)
	{
		s.insert(e.first);
	}
	return s;
}
//����id����ɾ��
void StudentDataBase::EraseInfoByIdSet(const set<size_t>& s)
{
	//���ڹ�ϣ����ɾ�� -- ����8��multimap��ɾ�� -- �ܸ��Ӷ�ΪO(n*s.size())
	for (const auto& key : s)
	{
		__hash_map.erase(key);
	}
	//��multimap��ɾ��
	for (const auto& key : s)
	{
		for (const auto& mapsPtr : __inner_maps) //���ѭ����8��
		{
			for (const auto& e : *(mapsPtr.second))
			{
				if (e.second == key)
				{
					mapsPtr.second->erase(e.first);
					break;//��Ϊһ��mapֻ��Ҫ��һ��ɾ�� -- ����ֱ��break
				}
			}
		}
	}
}
//����set��ӡ
void StudentDataBase::OutputByIdSet(const set<size_t>s, ostream& out)
{
	for (const auto& key : s)
	{
		DisplayStudentByPtr(out, __hash_map[key]);
	}
}