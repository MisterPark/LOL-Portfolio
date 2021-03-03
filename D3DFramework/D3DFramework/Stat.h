#pragma once
#include "Buff.h"
class Stat
{
public:
    Stat();
    Stat(const Stat& rhs);
    Stat(float val);
    virtual ~Stat();


    Stat& operator=(const float& val);
    Stat& operator+=(const float& modi);
    Stat& operator+(const float& modi);
    Stat& operator-=(const float& modi);
    Stat& operator-(const float& modi);
    Stat& operator*=(const float& modi);
    Stat& operator*(const float& modi);
    Stat& operator/=(const float& modi);
    Stat& operator/(const float& modi);

    Stat& operator=(const Stat& rhs);
    Stat& operator+(const Stat& rhs);
    Stat& operator+=(const Stat& rhs);
    Stat& operator-(const Stat& rhs);
    Stat& operator-=(const Stat& rhs);
    Stat& operator*(const Stat& rhs);
    Stat& operator*=(const Stat& rhs);
    Stat& operator/(const Stat& rhs);
    Stat& operator/=(const Stat& rhs);


    bool operator==(const Stat& rhs);
    bool operator!=(const Stat& rhs);
    bool operator>=(const Stat& rhs);
    bool operator<=(const Stat& rhs);
    bool operator>(const Stat& rhs);
    bool operator<(const Stat& rhs);

    void AddModifier(float _modifier);
    void RemoveModifier(float _modifier);

    float GetValue();
    float GetBaseValue();
public:
    float baseValue = 0.f;
private:
    list<float> modifiers;
};

