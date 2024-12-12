#ifndef __CHARLES_SORT_H__
#define __CHARLES_SORT_H__

#include <vector>

template<typename T, typename Comparator>
void sort_sorted_vec_with_one_changed(std::vector<T>& vec, int changed_index, Comparator comparator)
{
    int destination_index = -1;
    if(changed_index == 0)
    {
        auto it = std::upper_bound(
            vec.begin() + 1,
            vec.end(),
            vec[changed_index],
            comparator
        );
        destination_index = std::distance(vec.begin(), it);
    }
    else if(changed_index == vec.size())
    {
        auto it = std::upper_bound(
            vec.begin(),
            vec.end() - 1,
            vec[changed_index],
            comparator
        );
        destination_index = std::distance(vec.begin(), it);
    }
    else if(comparator(vec[changed_index], vec[changed_index - 1]))
    {
        // find in the left
        auto it = std::upper_bound(
            vec.begin(),
            vec.begin() + changed_index,
            vec[changed_index],
            comparator
        );
        destination_index = std::distance(vec.begin(), it);
    }
    else
    {
        // find in the right
        auto it = std::upper_bound(
            vec.begin() + changed_index,
            vec.end(),
            vec[changed_index],
            comparator
        );
        destination_index = std::distance(vec.begin(), it);
    }
    if (destination_index >= vec.size())
    {
        destination_index = vec.size() - 1;
    }
    if(changed_index == destination_index)
    {
        // do nothing
    }
    else if(destination_index < changed_index)
    {
        auto temp = vec[changed_index];
        for(int i = changed_index; i > destination_index; i--)
        {
            vec[i] = vec[i - 1];
        }
        vec[destination_index] = temp;
    }
    else
    {
        auto temp = vec[changed_index];
        for (int i = changed_index; i < destination_index; i++)
        {
            vec[i] = vec[i + 1];
        }
        vec[destination_index] = temp;
    }
}

template<typename T, typename Comparator>
void sort_sorted_vec_with_one_changed(std::vector<T>& vec, T changed_element, Comparator comparator)
{
    int changed_index = -1;
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i] == changed_element)
        {
            changed_index = i;
            break;
        }
    }
    sort_sorted_vec_with_one_changed(vec, changed_index, comparator);
}

#endif