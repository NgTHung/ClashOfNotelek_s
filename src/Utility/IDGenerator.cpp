#include "Utility/IDGenerator.hpp"

int ID::s_NextID = 0;

ID::ID() : m_ID(s_NextID++)
{
}

int ID::GetID() const
{
    return m_ID;
}

bool ID::operator==(const ID& Other) const
{
    return m_ID == Other.m_ID;
}

bool ID::operator!=(const ID& Other) const
{
    return !(*this == Other);
}