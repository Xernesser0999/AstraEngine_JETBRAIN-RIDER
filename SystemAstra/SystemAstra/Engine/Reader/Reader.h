#pragma once

class Reader {
public:
    virtual ~Reader() = default;
    virtual void read() = 0;
};
