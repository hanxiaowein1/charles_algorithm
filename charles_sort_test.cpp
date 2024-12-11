#include "unit_test.h"
#include "charles_sort.h"
#include <algorithm>

TEST(GlobalTest, sort_sorted_vec_with_one_changed)
{
    class HalfEdge
    {
    public:
        int value;
        std::shared_ptr<HalfEdge> opposite;
    public:
        HalfEdge(int in_value)
        {
            this->value = in_value;
        }
    };

    class HalfEdgeComparator
    {
    public:
        bool operator()(const std::shared_ptr<HalfEdge>& a, const std::shared_ptr<HalfEdge>& b) const
        {
            return a->value < b->value;
        }
    };

    std::shared_ptr<HalfEdge> e1 = std::make_shared<HalfEdge>(1);
    std::shared_ptr<HalfEdge> e2 = std::make_shared<HalfEdge>(2);
    std::shared_ptr<HalfEdge> e3 = std::make_shared<HalfEdge>(3);
    std::shared_ptr<HalfEdge> e4 = std::make_shared<HalfEdge>(4);
    std::shared_ptr<HalfEdge> e5 = std::make_shared<HalfEdge>(5);

    std::vector<std::shared_ptr<HalfEdge>> vec{e1, e2, e3, e4, e5};

    std::sort(vec.begin(), vec.end(), HalfEdgeComparator());

    e2->value = 7;
    sort_sorted_vec_with_one_changed(vec, e2, HalfEdgeComparator());
    ASSERT_EQ(7, vec[vec.size() - 1]->value);

    e5->value = -1;
    sort_sorted_vec_with_one_changed(vec, e5, HalfEdgeComparator());
    ASSERT_EQ(-1, vec[0]->value);

    e2->value = 8;
    sort_sorted_vec_with_one_changed(vec, e5, HalfEdgeComparator());
    ASSERT_EQ(8, vec[vec.size() - 1]->value);

    e5->value = -2;
    sort_sorted_vec_with_one_changed(vec, e5, HalfEdgeComparator());
    ASSERT_EQ(-2, vec[0]->value);


    e3->value = -2;
    sort_sorted_vec_with_one_changed(vec, e3, HalfEdgeComparator());
    ASSERT_EQ(-2, vec[0]->value);
}