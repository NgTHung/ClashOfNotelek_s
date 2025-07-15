#pragma once

class ID {
private:
    static int s_NextID;
    const int m_ID;
public:
    ID();
    ID(const ID&) = delete;
    ID& operator=(const ID&) = delete;
    ID(ID&&) = delete;
    ID& operator=(ID&&) = delete;
    ~ID() = default;

    int GetID() const;
    bool operator==(const ID& Other) const;
    bool operator!=(const ID& Other) const;
};