#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include<fstream>
using namespace std;
typedef struct {
    char id[10];    //编号
    char name[10];  //姓名
    char sex[10];   //性别
    char number[10];//电话号码 
    char qq[10];    //QQ号
    char zhiwei[10];//职位
}ElemType;          //数据元素结构

//链表结构
typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode;

LNode* head = NULL;
char txtName[10];//定义txt文件名
FILE* txt;

//初始化链表
void StartList()
{
    head = (LNode*)malloc(sizeof(LNode));
    head->next = NULL;
}

//输入所有数据
void InputList()
{
    cout << "请输入添加职工人数" << endl;
    int n;
    cin >> n;
    LNode* p, * q;//构建新节点p
    for (int i = 0; i < n; i++)
    {
        p = (LNode*)malloc(sizeof(LNode));
        cout << "请输入第" << i + 1 << "个职工的编号" << endl;
        cin >> p->data.id;
        q = head->next;
        while (q != NULL)//判断职工编号是否重复
        {
            if (strcmp(q->data.id, p->data.id) == 0)
            {
                cout << "职工编号重复，请重新输入：" << endl;
                cin >> p->data.id;
                q = head->next;
                continue;
            }
            else q = q->next;
        }
        cout << "请输入第" << i + 1 << "个职工的姓名：" << endl;
        cin >> p->data.name;
        cout << "请输入第" << i + 1 << "个职工的性别：" << endl;
        cin >> p->data.sex;
        cout << "请输入第" << i + 1 << "个职工的电话号码：" << endl;
        cin >> p->data.number;
        cout << "请输入第" << i + 1 << "个职工的qq：" << endl;
        cin >> p->data.qq;
        cout << "请输入第" << i + 1 << "个职工的职位：" << endl;
        cin >> p->data.zhiwei;
        if (head->next == NULL)
        {
            p->next = NULL;
            head->next = p;
        }
        else
        {
            q = head->next;
            while (q != NULL)
            {
                if (q->next != NULL)
                {
                    if (p->data.id > q->data.id && p->data.id < q->next->data.id)
                    {
                        p->next = q->next;
                        q->next = p;
                        break;
                    }
                }
                else
                {
                    p->next = NULL;
                    q->next = p;
                    break;
                }
                q = q->next;
            }
        }
    }
}

//显示链表数据
void ShowData()
{
    LNode* p;//构建新节点p
    p = head->next;
    cout << "编号" << "\t" << "姓名" << "\t" << "性别" << "\t" << "电话" << "\t" << "QQ" << "\t" << "职位" << endl;
    if (p == NULL)
    {
        cout << "链表中无职工数据！";
        return;
    }
    while (p != NULL)
    {
        cout << p->data.id << "\t" << p->data.name << "\t" << p->data.sex << "\t" << p->data.number << "\t" << p->data.qq << "\t" << p->data.zhiwei << endl;
        p = p->next;
    }
}

//存储数据在txt文件中
void StorageData()
{
    LNode* q = head->next;
    if ((txt = fopen(txtName, "w")) == NULL)
    {
        cout << "打开文件失败！" << endl;
        return;
    }
    else
    {
        while (q != NULL)
        {
            fprintf(txt, "%s\t%s\t%s\t%s\t%s\t%s\n", q->data.id, q->data.name, q->data.sex, q->data.number, q->data.qq, q->data.zhiwei);
            q = q->next;
        }
    }
    fclose(txt);
    cout << "职工档案已存储到" << txtName << "文件中！" << endl;
}

//显示txt文件的数据
void DisplayData()
{
    cout << "请输入要查看的txt文件：" << endl;
    cin >> txtName;
    txt = fopen(txtName, "r");//以只读的形式打开txt文件
    if (txt == NULL)
    {
        cout << "不存在此txt文件！" << endl;
        return;
    }
    cout << "编号" << "\t" << "姓名" << "\t" << "性别" << "\t" << "电话" << "\t" << "QQ" << "\t" << "职位";
    ifstream ifs;//创建流对象
    ifs.open(txtName, ios::in);//打开文件
    char data[100] = { 0 };
    int i = 0;
    while (ifs >> data)
    {
        if (i % 6 == 0)
        {
            cout << endl;
        }
        cout << data << "\t";
        i++;
    }
    ifs.close();
}

//在txt中查找职工信息
void FindInTxt(char* dataID)
{
    cout << "请输入要查找的员工所在的txt文件：" << endl;
    cin >> txtName;
    txt = fopen(txtName, "r");//以只读的形式打开txt文件
    if (txt == NULL)
    {
        cout << "不存在此txt文件" << endl;
        return;
    }
    char a[100];
    cout << "请输入要查找职工的编号：" << endl;
    cin >> dataID;
    cout << "编号" << "\t" << "姓名" << "\t" << "性别" << "\t" << "电话" << "\t" << "QQ" << "\t" << "职位" << endl;
    strcpy(a, dataID);
    ifstream ifs;
    ifs.open(txtName, ios::in);
    char data[100] = { 0 };
    int i = 0;
    while (ifs >> data)
    {
        int n = strcmp(a, data);
        if (n == 0)
        {
            cout << data << "\t";
            i++;
            continue;
        }
        if (i >= 6)
        {
            return;
        }
        if (i < 6 && i >= 1)
        {
            cout << data << "\t";
            i++;
        }
    }
    ifs.close();
}

//按编号查找数据
void FindData()
{
    char ID[10];
    cout << "请输入要查找的职工的编号：" << endl;
    cin >> ID;
    LNode* q = head->next;
    while (q != NULL)
    {
        if (strcmp(q->data.id, ID) == 0)
        {
            cout << "编号" << "\t" << "姓名" << "\t" << "性别" << "\t" << "电话" << "\t" << "QQ" << "\t" << "职位" << endl;
            cout << q->data.id << "\t" << q->data.name << "\t" << q->data.sex << "\t" << q->data.number << "\t" << q->data.qq << "\t" << q->data.zhiwei << endl;
            return;
        }
        q = q->next;
    }
}

//按编号删除数据
void DeleteData()
{
    cout << "请输入要删除职工的编号：" << endl;
    char id[10];
    cin >> id;
    LNode* q = head;
    while (q != NULL)
    {
        if (strcmp(q->next->data.id, id) == 0)
        {
            LNode* p = q->next;
            q->next = p->next;
            free(p);
            cout << "删除成功！" << endl;
            return;
        }
        q = q->next;
    }
}

//按编号修改数据
void ReviseData()
{
    cout << "请输入要修改职工的编号：" << endl;
    char ID[10];
    cin >> ID;
    int n = 0;
    LNode* q = head;
    while (q != NULL)
    {
        q = q->next;
        if (strcmp(q->data.id, ID) == 0)
        {
            break;
        }
        if (q->next == NULL)
        {
            cout << "该职工编号不存在，请重新输入：" << endl;
            cin >> ID;
            q = head->next;
            continue;
        }
    }
    LNode* ln = (LNode*)malloc(sizeof(LNode));
    ln->next = NULL;
    cout << "请输入修改后的职工编号：" << endl;
    cin >> ln->data.id;
    LNode* p = head->next;
    while (p != NULL)
    {
        if (strcmp(ln->data.id, p->data.id) == 0)
        {
            cout << "职工编号重复，请重新输入：" << endl;
            cin >> ln->data.id;
            p = head->next;
            continue;
        }
        else p = p->next;
    }
    cout << "请输入修改后的职工姓名：" << endl;
    cin >> ln->data.name;
    cout << "请输入修改后的职工性别：" << endl;
    cin >> ln->data.sex;
    cout << "请输入修改后的职工电话：" << endl;
    cin >> ln->data.number;
    cout << "请输入修改后的职工QQ：" << endl;
    cin >> ln->data.qq;
    cout << "请输入修改后的职工职位：" << endl;
    cin >> ln->data.zhiwei;
    strcpy(q->data.id, ln->data.id);
    strcpy(q->data.name, ln->data.name);
    strcpy(q->data.sex, ln->data.sex);
    strcpy(q->data.number, ln->data.number);
    strcpy(q->data.qq, ln->data.qq);
    strcpy(q->data.zhiwei, ln->data.zhiwei);
    free(ln);
}

//销毁链表
void DestroyList(LNode* head) {
    LNode* q, * p = head;//让p指向头结点
    while (p != NULL)
    {
        q = p->next;//让q指向头结点的后续结点
        free(p);//删除p
        p = q;
    }
    head = NULL;
}

//读入txt文件
void InputTxt()
{
    StartList();
    LNode* p, * q;//构建新节点p
    q = head;//q指向头节点创建链表
    while (true)//创建txt文件
    {
        cout << "请输入要读入的txt文件名(输入时请加入后缀名.txt)：" << endl;
        cin >> txtName;//输入时请加入后缀名.txt
        if ((txt = fopen(txtName, "r")) == NULL)//若该txt文件不存在
        {
            cout << "未找到该txt文件，是否创建？" << endl;
            cout << "请输入Y或N：" << endl;
            char a;
            cin >> a;
            if (a == 'Y' || a == 'y')
            {
                if ((txt = fopen(txtName, "a+")) == NULL)
                {
                    cout << "创建失败" << endl;
                }
                else break;
            }
            else continue;
        }
        else break;
    }
    while (true)
    {
        p = (LNode*)malloc(sizeof(LNode));//为节点p分配空间
        if (fscanf(txt, "%s\t%s\t%s\t%s\t%s\t%s\n", p->data.id, p->data.name, p->data.sex, p->data.number, p->data.qq, p->data.zhiwei) == EOF)//从txt文件中读入数据
        {
            free(p);//释放p节点空间
            cout << "读入成功！" << endl;
            break;
        }
        //之后利用尾插法创建链表
        p->next = NULL;
        q->next = p;
        q = q->next;
    }
    fclose(txt);//关闭文件
}

int main()
{
    char dataID[10];
    printf("***************************************************职工档案管理系统**************************************************");
    int choice = 1;
    while (choice != 0) {
        cout << endl;
        printf("*********************************************************************************************************************\n");
        printf("|                                                                                                                   |\n");
        printf("|1.添加  2.查找  3.修改  4.删除  5.显示链表数据  6.保存到txt文件  7.显示txt文件数据  8.txt中查找  9.读入txt  10.返回|\n");
        printf("|                                                                                                                   |\n");
        printf("*********************************************************************************************************************\n");
        printf("输出需要操作的选项：");
        cout << endl;
        scanf("%d", &choice);
        switch (choice) {
        case 1: InputList();//添加人员信息
            break;
        case 2: FindData();//按编号查找数据
            break;
        case 3: ReviseData();//按编号修改数据
            break;
        case 4: DeleteData();//按编号删除数据
            break;
        case 5: ShowData();//显示链表数据
            break;
        case 6: StorageData();//保存到txt文件
            break;
        case 7: DisplayData();//显示txt文件数据
            break;
        case 8: FindInTxt(dataID);//txt中查找
            break;
        case 9: InputTxt();//读入txt
            break;
        case 10: DestroyList(head);//销毁链表
            printf("退出程序。\n");
            break;
        default:
            printf("程序已退出...\n");
            break;
        }
    }
    printf("欢迎您使用本系统！\n");
    return 0;
}