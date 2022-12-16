# workerManagerSystem
c++职工档案管理系统  
若使用功能1-5，运行时请先运行功能9，否则可能会报错。  
功能9：创建txt文件，若该txt文件已存在将会将txt数据读入到链表数据中进行增删改查。  
功能8：在任意已存在的txt文件中按编号查询想要的职工信息，省去了读入链表在查询的步骤。  
功能7：输出指定txt文件中存储的内容。  
功能6：将链表中的数据保存在自己创建的txt文件中。  
功能5：输出链表中的数据。  
功能1-4：链表的增删改查。  
增删改查后的链表数据要通过功能8才能保存在txt文件中。  
新增排序功能函数：  
void ListData()
{
    LNode* q;
    q = head->next;
    int length = 0;//链表长度
    while (q != NULL)
    {
        length++;
        q = q->next;
    }
    //接下来我们用冒泡排序
    LNode* m, * n;
    for (int i = 0; i < length; i++)
    {
        q = head->next;
        for (int j = 0; j < length - i - 1; j++)
        {
            m = q;
            n = q->next;
            if (strcmp(m->data.id, n->data.id) > 0)
            {
                ElemType elem = m->data;
                m->data = n->data;
                n->data = elem;
            }
            q = q->next;
        }
    }
    cout << "排序完成,请查看！" << endl;
    ShowData();
}
