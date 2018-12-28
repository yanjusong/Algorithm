#ifndef BINARY_SERACH_TREE_H_20181227
#define BINARY_SERACH_TREE_H_20181227

#include "tree.h"

/*
 * @brief: �ҵ�������������ֵ��С�Ľ��
 * @params:
 *    BTree *t: �����
 * @return:
 *    NULL: �����ΪNULL
 *    else: ֵ��С�Ľ��ָ��
 */
BTree *find_min(BTree *t);

/*
 * @brief: �ҵ�������������ֵ���Ľ��
 * @params:
 *    BTree *t: �����
 * @return:
 *    NULL: �����ΪNULL
 *    else: ֵ���Ľ��ָ��
 */
BTree *find_max(BTree *t);

/*
 * @brief: �ҵ�������������ֵΪ�ض�ֵ�Ľ��
 * @params:
 *    int value: ָ���ļ�ֵ
 *    BTree *t:  �����
 * @return:
 *    NULL: �����ΪNULL���߲����ڸ�ֵ�Ľ��
 *    else: ������������ֵΪelem�Ľ��ָ��
 */
BTree *find(int value, BTree *t);

/*
 * @brief: �ڶ����������в����ض�ֵ�Ľ��
 * @params:
 *    int value: ָ����ֵ
 *    BTree *t:  �����
 * @return: �����½���ĸ����
 */
BTree *bst_insert(int value, BTree *t);

/*
 * @brief: ɾ��������������ֵΪ�ض�ֵ�Ľ��
 * @params:
 *    int value: ָ���ļ�ֵ
 *    BTree *t:  �����
 * @return: ����ɾ���Ľ���ĸ����
 */
BTree *bst_delete(int value, BTree *t);

#endif // !BINARY_SERACH_TREE_H_20181227
