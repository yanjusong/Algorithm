#include "../Generator.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cerrno>
using namespace std;

void BAD_ERROR(const char *str, int line)
{
    int errnum = errno;
    fprintf(stderr, "line:%d, info:%s, errno:%d, sysinfo:%s\n", line, str, errnum, strerror(errnum));
    exit(errnum);
}

#define badError(str) BAD_ERROR(str, __LINE__)

void close(vector<FILE *> &fps)
{
    int len = fps.size();
    for (int i = 0; i < len; ++i)
    {
        if (fps[i])
        {
            fclose(fps[i]);
            fps[i] = NULL;
        }
    }
}

void distributed(string originFile, int tmpFileNum, string nameTag, vector<string> &tmpFileNames)
{
    vector<FILE *> fps(tmpFileNum, NULL);
    int ret = 0;
    FILE *originFp = NULL;
    int curNum = 0;
    int i = 0;

    originFp = fopen(originFile.c_str(), "r");
    if (!originFp)
        badError("open origin file error");

    for (i = 0; i < tmpFileNum; ++i)
    {
        char tmpFile[256];
        sprintf(tmpFile, "./%s_%d.txt", nameTag.c_str(), i);
        tmpFileNames[i] = tmpFile;
        fps[i] = fopen(tmpFileNames[i].c_str(), "w+");
        if (!fps[i])
            badError("open tmp file error");
    }

    while (fscanf(originFp, "%d", &curNum) != EOF)
    {
        if (fprintf(fps[i++ % tmpFileNum], "%d\n", curNum) < 0)
            badError("read tmp file error");
    }

    if (originFp)
        fclose(originFp);
    close(fps);
}

void sortedTmpFiles(const vector<string> &tmpFileNames)
{
    if (tmpFileNames.size() == 0)
        badError("error size");

    for (int i = 0; i < tmpFileNames.size(); ++i)
    {
        FILE *tmpFp = fopen(tmpFileNames[i].c_str(), "r");
        if (!tmpFp)
            badError("open tmp file error");

        vector<int> nums;
        int num = 0;
        while (fscanf(tmpFp, "%d", &num) != EOF)
        {
            nums.push_back(num);
        }
        fclose(tmpFp);
        sort(nums.begin(), nums.end());

        tmpFp = fopen(tmpFileNames[i].c_str(), "w+");
        if (!tmpFp)
            badError("open tmp file error");

        for (int &x : nums)
        {
            if (fprintf(tmpFp, "%d\n", x) < 0)
            {
                fclose(tmpFp);
                badError("rewrite tmp file error");
            }
        }

        fclose(tmpFp);
    }
}

struct FileBuffer
{
    FileBuffer(string fileName, int cap) : cap_(cap), cur_(0), total_(0)
    {
        assert(cap_ > 0);

        fp_ = fopen(fileName.c_str(), "r");
        if (!fp_)
            badError("open tmp file error");

        buffer_ = vector<int>(cap_, 0);
        load();
    }

    ~FileBuffer()
    {
        if (fp_)
            fclose(fp_);
    }

    bool isEmpty()
    {
        if (cur_ < total_)
            return false;

        if (fp_)
        {
            load();
            return isEmpty();
        }
        else
        {
            return true;
        }
    }

    int get()
    {
        return buffer_[cur_++];
    }

    static bool com_self(FileBuffer *lhs, FileBuffer *rhs)
    {
        if (lhs->cur_ >= lhs->total_)
            return false;
        if (rhs->cur_ >= rhs->total_)
            return true;
        return lhs->buffer_[lhs->cur_] >= rhs->buffer_[rhs->cur_];
    }

private:
    void load()
    {
        int curNum = 0;
        cur_ = total_ = 0;
        for (int i = 0; i < cap_; ++i, ++total_)
        {
            if (fscanf(fp_, "%d", &curNum) == EOF)
            {
                fclose(fp_);
                fp_ = NULL;
                break;
            }

            buffer_[i] = curNum;
        }
    }

    FILE *fp_;
    int cap_;
    int total_;
    int cur_;
    vector<int> buffer_;
};

void mergeTmpFiles(const vector<string> &tmpFileNames, string &sortedFile, int maxMemSize)
{
    FILE *sortedFp = fopen(sortedFile.c_str(), "w+");
    if (!sortedFp)
        badError("open sorted file error");

    int tmpFileSize = tmpFileNames.size();
    if (tmpFileNames.size() == 0)
        badError("there are no tmp file");

    vector<FileBuffer *> bufs;
    for (int i = 0; i < tmpFileSize; ++i)
    {
        bufs.push_back(new FileBuffer(tmpFileNames[i], maxMemSize / 10 / 4));
    }

    make_heap(bufs.begin(), bufs.end(), &FileBuffer::com_self);

    while (bufs.size() > 0)
    {
        pop_heap(bufs.begin(), bufs.end(), &FileBuffer::com_self);
        int curNum = bufs.back()->get();
        if (fprintf(sortedFp, "%d\n", curNum) < 0)
        {
            fclose(sortedFp);
            badError("write sorted file error");
        }

        if (bufs.back()->isEmpty())
        {
            delete bufs.back();
            bufs.pop_back();
        }
        else 
        {
            push_heap(bufs.begin(), bufs.end(), &FileBuffer::com_self);
        }
    }

    fclose(sortedFp);
}

void test(int total, int tmpFileNum, int maxMemSize, string nameTag = "output")
{
    // 生成测试数据
    Generator gen;
    string originFile = nameTag + ".txt";
    gen.genIntegers(originFile.c_str(), total);
    
    vector<string> tmpFileNames(tmpFileNum, "");
    string sortedFile = nameTag + "_sorted.txt";

    // 将数据分配到不同的tmp文件中
    distributed(originFile, tmpFileNum, nameTag, tmpFileNames);

    // 将不同tmp文件中的数据排序
    sortedTmpFiles(tmpFileNames);

    // 多路归并tmp文件
    mergeTmpFiles(tmpFileNames, sortedFile, maxMemSize);
}

// g++ -std=c++11 test__sort.cpp ../Generator.cpp -o a && ./a
int main()
{
    test(10000000, 10, 10 * 1024 * 1024, "output");

    return 0;
}
