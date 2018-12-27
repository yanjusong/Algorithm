#ifndef BINARY_SERACH_TREE_H_20181227
#define BINARY_SERACH_TREE_H_20181227

#include "tree.h"

/*
 * @brief: �ҵ�������������ֵ��С�Ľ��
 * @params:
 *    Tree *t: �����
 * @return:
 *    NULL: �����ΪNULL
 *    else: ֵ��С�Ľ��ָ��
 */
Tree *find_min(Tree *t);

/*
 * @brief: �ҵ�������������ֵ���Ľ��
 * @params:
 *    Tree *t: �����
 * @return:
 *    NULL: �����ΪNULL
 *    else: ֵ���Ľ��ָ��
 */
Tree *find_max(Tree *t);

/*
 * @brief: �ҵ�������������ֵΪ�ض�ֵ�Ľ��
 * @params:
 *    int value: ָ���ļ�ֵ
 *    Tree *t:   �����
 * @return:
 *    NULL: �����ΪNULL���߲����ڸ�ֵ�Ľ��
 *    else: ������������ֵΪelem�Ľ��ָ��
 */
Tree *find(int value, Tree *t);

/*
 * @brief: �ڶ����������в����ض�ֵ�Ľ��
 * @params:
 *    int value: ָ����ֵ
 *    Tree *t:   �����
 * @return: �����½���ĸ����
 */
Tree *insert(int value, Tree *t);

/*
 * @brief: ɾ��������������ֵΪ�ض�ֵ�Ľ��
 * @params:
 *    int value: ָ���ļ�ֵ
 *    Tree *t:   �����
 * @return: ����ɾ���Ľ���ĸ����
 */
Tree *del(int value, Tree *t);

#endif // !BINARY_SERACH_TREE_H_20181227
