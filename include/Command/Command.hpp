#pragma once
class BaseCommand
{
public:
    virtual ~BaseCommand() = default;
    virtual void execute() = 0;
};