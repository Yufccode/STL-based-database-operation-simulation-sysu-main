
��ʦҪ����ofstream����Ľ���� result.txt ��
����ӿڵĲ��ֲ��Խ���� result_test.txt �� ��ͬ��Ҳ��ʹ��ofstream����ģ����в��ֽ������ֶ�����ģ�

## 21312780 �����
## ��ĿҪ���ڴ����л��ĵ�������������
1. ʹ��stl�洢���ű����Ϣ -- �� ǰ�ڽṹ׼��
2. Ҫ��Ч�ʸ� -- ά����ú���� -- ��֤����Ч�� -- �� ǰ�ڽṹ׼��
3. ��������Ŀ��Ĭ����id��˳�� -- �����з���set<~size_t~>���ͣ�key��id�� -- Ĭ�ϰ���id�ź���
4. ����ÿ���ֶν������� -- Student�е�ÿ���ֶζ�ά�������򷽷� -- �����룬����SortByKey�ӿ�ά���˶��������ô���SortKey����
5. ֧�ַ�Χ��ѯ -- �� ���ҹ��� �еĵ�4��
6. ֧�ָ����ֶν���ɾ�� -- ��ϲ���ʹ�øýӿ� -- ����֧�ָ����ֶΣ�ɾ��ͨ�����ò��ҵĽ������ɾ��
7. ֧�ֽ���Ľ��� -- ��&��|������
8. �����Ѿ����������ܰѲ�ѯ��Ч��ά����O(logn)��


## StudentDataBase��ʵ��˼·��������
### ǰ�ڽṹ׼��
1. ����ͨ��enumö���Ա� -- ��ǿ����Ŀɶ��� enum Sex;

2. ͨ������struct CourseObj; ��struct Student;�洢Studentÿһ��ѧ������Ϣ
	����Ŀ�ṩ������txt�ļ���ȡ��֮������ȫ��ͳһ��struct Student�ṹ���д洢
	
3. ����ѧ������Ϣͳһ�洢��һ��**��ϣ��**��
	���й�ϣ���еĽṹΪ unordered_map<~size_t, Student*~>__hash_map;
	keyΪѧ����id
	valueΪָ��ѧ����Ϣ��ָ��
	�ڱ������ݿ�ṹ�� -- ȫ��Χ��ѧ����Id���в���
	**ͨ����ϣ��洢ѧ����Ϣ������id��Ϊkey -- ��������ͨ��key�ҵ�ѧ����Ϣ�ĸ��Ӷ�ΪO(1)**

4. ��ĿҪ��ͨ������ֶβ���ѧ��������Ҫ��Ч��
	�������ά�����multimap��ͬʱ�洢ѧ������Ϣ -- �Ա㱣֤��ѯ������Ч�ʿ��ԴﵽO(logn)
	���У�ÿ��multimap��keyΪ���Ӧ���ֶΣ�value��Ӧ��ѧ����id -- (���id����O(1)�ҵ�ѧ����ָ�룬������ɸ�Ч�Ĳ�ѯ)
	����һ��ά����8��multimap(����multimap,ͨ���º���greater<~double~>)
	��8��multimap������һ����ϣ���װ��
	unordered_map<~string, multimap<~double, size_t, greater<~double~>~>*~>__inner_maps;
	�����ϣ���key��Ϊ8��multimap����Ӧ�ı�ǩ���ֱ�Ϊ��
	"C Programming Language" ,"Advanced math", "College English",
		"Control Theory","Python","total_score", "avg_score","birthday"
	ͨ���ù�ϣ���е�key ���ǿ����ҵ���Ӧ��multimap

### ����txt�ļ����ݵ�¼��
1. ���ݵ�¼��ͨ���ڲ�__init_hash_map()�ӿں�__init_maps()���
	�������ӿ��������һЩ���߽ӿڣ�����װ�����ڲ���struct init_tools;��

2. __init_hash_map()�ӿ�ͨ����ȡ����txt�ļ���ÿһ�У����ַ���������new��Student���󣬲����뵽��ϣ����

3. __init_maps()�ӿڣ�ͨ����ȡ����txt�ļ��е�ÿһ�У��ҵ���Ӧ��id����__hash_map���ҵ���Ӧ���Ѿ�new�õ�Student���󣬽������ݵ�¼��

### ������
1. ����������ӿ��� -- ���Ҫ������ֶ��Ѿ�ά����һ�ú����
	��ֱ�ӱ����������ӡ
	���Ӷ�:O(n)
2. ����������ӿ��� -- ���Ҫ������ֶ�û�б�ά�������
	��ȡ���� -- ������ӡ
	�ڴ�ͬʱ����Ҫ�ṩsort�ķº��������磺Cmp_SortByName
	���Ӷ�:O(nlogn)

### ���ҹ��� 
1. ���ҹ���ͳһ����set<~size_t~>���ͣ�Ϊ����������id�ļ��� --- �ô��������Ǵ�ӡ�����Ŀʱ�� -- ��Ϊset�����ԣ��Զ�����id�ź�����
	�����������ƣ����㽻������ 
	ͨ��id�ҵ�ѧ����ϢЧ�ʺܸ� -- ΪO(1)
2. �����ҵ��ֶ��Ѿ�ά���˺���� -- ֱ�Ӳ���multimap���ڲ��ӿڽ��в��ң���multimap::upper_bound,multimap::equal_range
3. �����ҵ��ֶ�û��ά������� -- ���������

4. ֧�ַ�Χ���ҵĽӿ��� FindByBirthday() -- ͨ�����ղ���
					  FindByScoreWithKey() -- ͨ����������
	���У�FindByBirthday()�ӿڣ�
		FindByBirthday()�ӿڴ�������Ԫ���������ݽṹ (tuple<~size_t,size_t,size_t~>)
		set<~size_t~> FindByBirthday(const tuple<~size_t, size_t, size_t~>& lower_limit,
			const tuple<~size_t, size_t, size_t>& upper_limit = tuple<~size_t, size_t, size_t~>())
		���У��ڶ���Ԫ���ṩȱʡ����
	ʹ�÷�����
		���ڶ�������������ʱ�򣬼�FindByBirthday()ֻ����һ��tuple -- ��ʾ����������ѯ
		����ѯ���շ��ϵ�һ��Ԫ���ѧ��
		����������������ʱ�򣺷�Ϊ���������
			1. ���lower_limitΪ(ninf_uint,ninf_uint,ninf_uint) -- ��ʾ�����޲��� -- ��ʾֻҪ������upper_limit֮ǰ�Ķ���������
			2. ���upper_limitΪ(pinf_uint,pinf_uint,pinf_uint) -- ��ʾ�����޲���
			3. lower_limit,upper_limit�ж����������� -- ��ʾ�������

	����FindByScoreWithKey()�ӿڣ�
		set<~size_t~> FindByScoreWithKey(string key, double lower_limit, double upper_limit = INT_MAX)
		ͨ��key�Ĵ����ʾҪ���ҵ��ֶΣ�key��ѡ���У�
		"C Programming Language" ,"Advanced math", "College English",
		"Control Theory","Python","total_score", "avg_score"
	ʹ�÷�����
		��FindByBirthday()�ӿ�һ��
		ͨ�����ִ������������ֵ���ֱ��ʾ ��ֵ���ң������޲��ң������޲��Һ��������

### ɾ������
	ͨ�������set<~size_t~> -- ��ѧ����id���Ͻ��в���
	������ϣ��O(1)����8��map (O(n))��ָ��id��ѧ������ɾ������
	�ܵĸ��Ӷȣ�O(n)

### ��������
	���Ե���stl��set_union�Ⱥ�����set��ɽ������ܣ������������ע��

### ����
	ѭ���ͷŹ�ϣ���8��multimap��ָ��
	���У�Student��Ҫ�ֶ�ʵ��������������CourseObj*

### �����ӿڵĹ���
	ͨ��ע�͵���ʽչʾ