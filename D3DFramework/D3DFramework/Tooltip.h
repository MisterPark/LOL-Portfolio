#pragma once
#include "Panel.h"

class Form;
class Item;
class Skill;

class Tooltip :
    public Panel
{
public:
    enum class TooltipType {
        Simple,
        Item,
        Skill,
        End
    };

    enum class Align {
        Left,
        Center,
        Right,
        End
    };

    enum class VAlign {
        Top,
        Middle,
        Bottom,
        End
    };

public:
    explicit Tooltip() {};
    Tooltip(const std::wstring& _desc); // Simple, Untitle
    Tooltip(const std::wstring& _title, const std::wstring& _subtitle, const std::wstring& _desc); // Simple
    Tooltip(Item* item);// Item
    //Tooltip(Skill* skill);// Skill
    virtual ~Tooltip();

    virtual void Update();
    virtual void SetLocation(int x, int y) override;
    virtual void SetLocation(float x, float y) override;
    virtual void SetLocation(Vector2 _pos) override;
    
    void SetAlign(Tooltip::Align _align, Tooltip::VAlign _valign); // Set Location 이후에 호출

private:
    Form* form;
    Vector2 pos;
};

