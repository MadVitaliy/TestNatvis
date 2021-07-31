// TestNatvis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>



class CName
{
private:
    std::string m_first;
    std::string m_last;
public:
    CName(const std::string& first, const std::string& last) : m_first(first), m_last(last) {}
    void Print()
    {
        std::cout << m_first << " " << m_last << std::endl;
    }
};

class CNameList
{
private:
    std::vector<CName*> m_list;
public:
    CNameList() noexcept
    {}
    ~CNameList() noexcept
    {
        for (int i = 0; i < m_list.size(); i++)
        {
            delete m_list[i];
        }
        m_list.clear();
    }
    void AddName(const std::string& first, const std::string& last)
    {
        m_list.push_back(new CName(first, last));
    }
};

class CircularList
{
private:
    struct Node
    {
        int m_value;
        Node* m_pNext;
    };
    Node* m_pFirst;
    Node* GetTail() noexcept
    {
        if (!m_pFirst)
            return nullptr;

        Node* pNode = m_pFirst;
        while (pNode->m_pNext != m_pFirst)
            pNode = pNode->m_pNext;
        return pNode;
    }
public:
    CircularList() noexcept : m_pFirst(nullptr)
    {}
    ~CircularList() noexcept
    {
        Node* pNode = m_pFirst;
        while (pNode != m_pFirst)
        {
            Node* pNext = pNode->m_pNext;
            delete pNode;
            pNode = pNext;
        }
    }
    void AddTail(int i)
    {
        Node* pNewNode = new Node();
        if (m_pFirst)
            GetTail()->m_pNext = pNewNode;
        else
            m_pFirst = pNewNode;
        pNewNode->m_value = i;
        pNewNode->m_pNext = m_pFirst;
    }
};

int main()
{
    CNameList presidents;
    presidents.AddName("George", "Washington");
    presidents.AddName("John", "Adams");
    presidents.AddName("Thomas", "Jefferson");
    presidents.AddName("Abraham", "Lincoln");

    CircularList circularList;
    circularList.AddTail(1);
    circularList.AddTail(2);
    circularList.AddTail(3);

    std::vector<int> vector = { 5, 10, 12, 13, 1, 4, 3 };
    std::set<int> set = { 5, 10, 12, 13, 1, 4, 3 };
    std::pair<int, float> pair = std::make_pair(5, 6.f);

    std::cout << "Vector: ";
    for(auto elem : vector)
        std::cout << elem << ", ";
    std::cout << std::endl;

    std::cout << "Set: ";
    for (auto elem : set)
        std::cout << elem << ", ";
    std::cout << std::endl;


    return 0;
}
