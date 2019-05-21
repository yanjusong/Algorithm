#include "hashtable.hpp"
#include <string>
#include <cassert>

unsigned int getIntHash(const int &x)
{
    return x;
}

struct Student
{
    std::string name_;
    int calssID_;

    Student() {}
    Student(const std::string &name, int calssID) : name_(name), calssID_(calssID) {}

    bool operator==(const Student &rhs) const
    {
        return (rhs.name_ == name_) && (rhs.calssID_ == calssID_);
    }

    static unsigned int getStudentHash(const Student &x)
    {
        std::hash<std::string> h;
        return h(x.name_) + x.calssID_;
    }
};

struct StudentExtra
{
    std::string phoneNumber_;
    int score_;

    StudentExtra() {}
    StudentExtra(std::string phoneNumber, int score) : phoneNumber_(phoneNumber), score_(score) {}
};

class TestHashTable
{
public:
    void testCURD()
    {
        HashTable<int, std::string> hashTable(getIntHash);

        // 分别插入0、128、256
        // table: [0] -> (0, "testInsert") -> (128, "testInsert") -> (256, "testInsert") -> NULL
        //        [1] -> NULL
        //        [2] -> NULL
        //         .
        //         .
        //         .
        //        [127] -> NULL
        for (int i = 0, j = 0; i < 3; ++i, j += 128)
        {
            hashTable.insert(j, "testInsert");
        }

        assert(hashTable.itemNum_ == 3);
        assert(hashTable.items_[0]);
        assert(hashTable.items_[0]->key_ == 0);
        assert(hashTable.items_[0]->next_->key_ == 128);
        assert(hashTable.items_[0]->next_->next_->key_ == 256);
        assert(hashTable.items_[0]->next_->next_->next_ == NULL);
        assert(hashTable.items_[0]->val_ == "testInsert");
        assert(hashTable.items_[0]->next_->val_ == "testInsert");
        assert(hashTable.items_[0]->next_->next_->val_ == "testInsert");

        for (int i = 0, j = 0; i < 3; ++i, j += 128)
        {
            bool ok = false;
            std::string val;
            ok = hashTable.get(j, val);
            assert(ok);
            assert(val == "testInsert");
        }

        for (int i = 1; i < 128; ++i)
        {
            bool ok = false;
            std::string val;
            ok = hashTable.get(i, val);
            assert(ok == false);
            assert(val == "");
        }

        // 修改
        // table: [0] -> (0, "testInsert__0") -> (128, "testInsert__128") -> (256, "testInsert__256") -> NULL
        //        [1] -> NULL
        //        [2] -> NULL
        //         .
        //         .
        //         .
        //        [127] -> NULL
        hashTable.insert(0, "testInsert__0");
        hashTable.insert(128, "testInsert__128");
        hashTable.insert(256, "testInsert__256");

        {
            std::string val;
            bool ok = hashTable.get(0, val);
            assert(SA_ONSTACK);
            assert(val == "testInsert__0");
        }

        {
            std::string val;
            bool ok = hashTable.get(128, val);
            assert(ok);
            assert(val == "testInsert__128");
        }

        {
            std::string val;
            bool ok = hashTable.get(256, val);
            assert(ok);
            assert(val == "testInsert__256");
        }

        // 删除 0
        // table: [0] -> (128, "testInsert__128") -> (256, "testInsert__256") -> NULL
        //        [1] -> NULL
        //        [2] -> NULL
        //         .
        //         .
        //         .
        //        [127] -> NULL
        hashTable.remove(0);
        assert(hashTable.itemNum_ == 2);
        assert(hashTable.items_[0]);
        assert(hashTable.items_[0]->key_ == 128);
        assert(hashTable.items_[0]->next_->key_ == 256);
        assert(hashTable.items_[0]->next_->next_ == NULL);
        assert(hashTable.items_[0]->val_ == "testInsert__128");
        assert(hashTable.items_[0]->next_->val_ == "testInsert__256");

        // 删除 256
        // table: [0] -> (128, "testInsert__128") -> NULL
        //        [1] -> NULL
        //        [2] -> NULL
        //         .
        //         .
        //         .
        //        [127] -> NULL
        hashTable.remove(256);
        assert(hashTable.itemNum_ == 1);
        assert(hashTable.items_[0]);
        assert(hashTable.items_[0]->key_ == 128);
        assert(hashTable.items_[0]->next_ == NULL);
        assert(hashTable.items_[0]->val_ == "testInsert__128");

        // 删除 128
        // table: [0] -> NULL
        //        [1] -> NULL
        //        [2] -> NULL
        //         .
        //         .
        //         .
        //        [127] -> NULL
        hashTable.remove(128);
        assert(hashTable.itemNum_ == 0);
        assert(hashTable.items_[0] == NULL);
    }

    void testRehash()
    {
        HashTable<int, std::string> hashTable(getIntHash);
        assert(hashTable.items_.size() == 128);
        assert(static_cast<int>(hashTable.items_.size() * hashTable.factor_) == 96);

        for (int i = 0; i < 128; ++i)
        {
            assert(hashTable.items_[i] == NULL);
        }

        for (int i = 0; i < 128; ++i)
        {
            hashTable.insert(i, "testRehash");

            if (i <= 95)
            {
                assert(hashTable.items_.size() == 128);
            }
            else
            {
                assert(hashTable.items_.size() == 192);
            }
        }
    }

    void testOperatorOverloading()
    {
        HashTable<int, std::string> hashTable(getIntHash);

        // 分别插入0、128、256
        // table: [0] -> (0, "testInsert") -> (128, "testInsert") -> (256, "testInsert") -> NULL
        //        [1] -> NULL
        //        [2] -> NULL
        //         .
        //         .
        //         .
        //        [127] -> NULL
        for (int i = 0, j = 0; i < 3; ++i, j += 128)
        {
            hashTable[j] = "testInsert";
        }

        assert(hashTable.itemNum_ == 3);
        assert(hashTable.items_[0]);
        assert(hashTable.items_[0]->key_ == 0);
        assert(hashTable.items_[0]->next_->key_ == 128);
        assert(hashTable.items_[0]->next_->next_->key_ == 256);
        assert(hashTable.items_[0]->next_->next_->next_ == NULL);
        assert(hashTable.items_[0]->val_ == "testInsert");
        assert(hashTable.items_[0]->next_->val_ == "testInsert");
        assert(hashTable.items_[0]->next_->next_->val_ == "testInsert");

        assert(hashTable.itemNum_ == 3);
        for (int i = 0, j = 0; i < 3; ++i, j += 128)
        {
            bool ok = false;
            std::string val;
            ok = hashTable.get(j, val);
            assert(ok);
            assert(val == "testInsert");
        }

        // 修改
        hashTable[0] = "testInsert__0";
        assert(hashTable.itemNum_ == 3);

        hashTable[128] = "testInsert__128";
        assert(hashTable.itemNum_ == 3);

        hashTable[256] = "testInsert__256";
        assert(hashTable.itemNum_ == 3);

        assert(hashTable.items_[0]);
        assert(hashTable.items_[0]->key_ == 0);
        assert(hashTable.items_[0]->next_->key_ == 128);
        assert(hashTable.items_[0]->next_->next_->key_ == 256);
        assert(hashTable.items_[0]->next_->next_->next_ == NULL);
        assert(hashTable.items_[0]->val_ == "testInsert__0");
        assert(hashTable.items_[0]->next_->val_ == "testInsert__128");
        assert(hashTable.items_[0]->next_->next_->val_ == "testInsert__256");

        {
            std::string val;
            bool ok = hashTable.get(0, val);
            assert(SA_ONSTACK);
            assert(val == "testInsert__0");
        }

        {
            std::string val;
            bool ok = hashTable.get(128, val);
            assert(ok);
            assert(val == "testInsert__128");
        }

        {
            std::string val;
            bool ok = hashTable.get(256, val);
            assert(ok);
            assert(val == "testInsert__256");
        }
    }

    void testCostomStruct()
    {
        HashTable<Student, StudentExtra> hashTable(Student::getStudentHash);
        hashTable[Student("jason", 1)] = StudentExtra("1xx xxxx xxxx", 90);
        assert(hashTable.itemNum_ == 1);

        hashTable[Student("jeff", 2)] = StudentExtra("2xx xxxx xxxx", 100);
        assert(hashTable.itemNum_ == 2);

        {
            StudentExtra jasonExtra;
            bool ok = hashTable.get(Student("jason", 1), jasonExtra);
            assert(ok);
            assert(jasonExtra.phoneNumber_ == "1xx xxxx xxxx");
            assert(jasonExtra.score_ == 90);
        }

        {
            StudentExtra jasonExtra;
            bool ok = hashTable.get(Student("jason", 2), jasonExtra);
            assert(ok == false);
        }

        {
            StudentExtra jeffExtra;
            bool ok = hashTable.get(Student("jeff", 2), jeffExtra);
            assert(ok);
            assert(jeffExtra.phoneNumber_ == "2xx xxxx xxxx");
            assert(jeffExtra.score_ == 100);
        }

        hashTable.remove(Student("jason", 1));
        assert(hashTable.itemNum_ == 1);
        hashTable.remove(Student("jeff", 2));
        assert(hashTable.itemNum_ == 0);

        {
            StudentExtra jasonExtra;
            bool ok = hashTable.get(Student("jason", 1), jasonExtra);
            assert(ok == false);
        }

        {
            StudentExtra jeffExtra;
            bool ok = hashTable.get(Student("jeff", 2), jeffExtra);
            assert(ok == false);
        }
    }
};

// g++ -std=c++11 test__all.cpp -o a && ./a
int main()
{
    TestHashTable t;

    // 测试insert/remove
    t.testCURD();

    // 测试rehash
    t.testRehash();

    // 测试operator[]
    t.testOperatorOverloading();

    // 测试自定义数据结构插入到哈希表
    t.testCostomStruct();

    return 0;
}
