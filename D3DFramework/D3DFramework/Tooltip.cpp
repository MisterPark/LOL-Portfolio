#include "stdafx.h"
#include "Tooltip.h"
// Control
#include "Form.h"
#include "Label.h"

Tooltip::Tooltip(const std::wstring& _desc)
{
    form = AddChild<Form>(L"background", new Form(Vector2(0, 0), Vector2(0, 0)));

    auto desc = AddChild<Label>(L"desc", new Label(20));
    desc->SetColor(255, 240, 230, 210);
    desc->SetLocation(11, 14);
    desc->SetWidthLimit(648);
    desc->SetText(_desc);
    desc->shadow = false;

    // 사이즈 맞춤
    int formWidth;
    int formHeight;
    if (desc->IsLineAlignment()) { // 개행한 경우
        formWidth = 648 + 14;
        formHeight = desc->GetDrawTextHeight() + 20;
    }
    else { // 개행하지 않은 경우
        formWidth = desc->GetDrawTextWidth() + 14;
        formHeight = desc->GetDrawTextHeight() + 20;
    }

    form->SetSize(Vector2(formWidth, formHeight));

    visible = false;
}

Tooltip::Tooltip(const std::wstring& _title, const std::wstring& _subtitle, const std::wstring& _desc)
{
    form = AddChild<Form>(L"background", new Form(Vector2(0, 0), Vector2(0, 0)));
    
    auto title = AddChild<Label>(L"title", new Label(20));
    title->SetColor(255, 240, 230, 210);
    title->SetLocation(10, 16);
    title->SetText(_title);
    title->shadow = false;
    
    auto subtitle = AddChild<Label>(L"subtitle", new Label(17));
    subtitle->SetColor(255, 240, 230, 210);
    subtitle->SetLocation(10, 47);
    subtitle->SetText(_subtitle);
    subtitle->shadow = false;

    auto desc = AddChild<Label>(L"desc", new Label(17));
    desc->SetColor(255, 160, 155, 140);
    desc->SetLocation(10, 90);
    desc->SetWidthLimit(648);
    desc->SetText(_desc);
    desc->shadow = false;

    // 사이즈 맞춤
    int formWidth;
    int formHeight;
    // 윗테두리선~2번째칸 글자 시작까지 공백 90
    // 글자~밑테두리선까지 공백 10
    if (desc->IsLineAlignment()) { // 개행한 경우
        formWidth = 648 + 12;
        formHeight = desc->GetDrawTextHeight() + 100;
    }
    else { // 개행하지 않은 경우
        formWidth = desc->GetDrawTextWidth() + 12;
        formHeight = desc->GetDrawTextHeight() + 100;
    }

    form->SetSize(Vector2(formWidth, formHeight));

    auto line = AddChild<UI>(L"line", new UI(L"tooltipatlas_line_c", Vector2(10, 74)));
    line->transform->scale = { (float)(formWidth - 10) / line->GetSize().x, 1.f, 1.f };
}

Tooltip::Tooltip(Item* item)
{
    form = AddChild<Form>(L"background", new Form(Vector2(0, 0), Vector2(0, 0)));

    auto icon = AddChild<UI>(L"icon", new UI(item->GetIcon(), Vector2(10, 10)));
    icon->transform->scale = { 0.8437f, 0.8437f, 1.f };

    auto title = AddChild<Label>(L"title", new Label(20));
    title->SetColor(255, 240, 230, 210);
    title->SetLocation(75, 16);
    title->SetText(item->GetName());
    title->shadow = false;
    int titleWidth = title->GetTextWidth();

    auto goldicon = AddChild<UI>(L"goldicon", new UI(L"icon_gold", Vector2(75, 47)));

    auto gold = AddChild<Label>(L"gold", new Label(17));
    gold->SetColor(255, 216, 174, 75);
    gold->SetLocation(94, 47);
    gold->SetText(item->GetPrice());
    gold->shadow = false;

    auto desc = AddChild<Label>(L"desc", new Label(17));
    desc->SetColor(255, 160, 155, 140);
    desc->SetLocation(10, 90);
    desc->SetWidthLimit(648);
    desc->SetText(item->GetDesc());

    // 사이즈 맞춤
    int formWidth;
    int formHeight;
    if (desc->IsLineAlignment()) { // 개행한 경우
        formWidth = 648 + 12;
        formHeight = desc->GetDrawTextHeight() + 100;
    }
    else { // 개행하지 않은 경우
        int descWidth = desc->GetDrawTextWidth();
        if ((titleWidth + 65) > descWidth) {
            formWidth = titleWidth
                + 65 // 아이콘 시작부분부터 글자 시작 부분까지
                + 12; // 양쪽 공백
        } else {
            formWidth = desc->GetDrawTextWidth() + 12;
        }
        
        formHeight = desc->GetDrawTextHeight() + 100;
    }

    form->SetSize(Vector2(formWidth, formHeight));

    auto line = AddChild<UI>(L"line", new UI(L"tooltipatlas_line_c", Vector2(10, 74)));
    line->transform->scale = { (float)(formWidth - 10) / line->GetSize().x, 1.f, 1.f };
}

Tooltip::~Tooltip()
{
}

void Tooltip::Update()
{
    UI::Update();
}

void Tooltip::SetLocation(int x, int y)
{
    pos = Vector2(x, y);
    UI::SetLocation(x, y);
}

void Tooltip::SetLocation(float x, float y)
{
    pos = Vector2(x, y);
    UI::SetLocation(x, y);
}

void Tooltip::SetLocation(Vector2 _pos)
{
    pos = _pos;
    UI::SetLocation(pos);
}

void Tooltip::SetAlign(Tooltip::Align _align, Tooltip::VAlign _valign)
{
    float x = pos.x;
    float y = pos.y;
    Vector2 size = form->GetSize();

    switch (_align)
    {
    case Tooltip::Align::Left:
        break;

    case Tooltip::Align::Center:
        x -= size.x * 0.5f;
        break;

    case Tooltip::Align::Right:
        x -= size.x;
        break;
    }
    
    switch (_valign)
    {
    case Tooltip::VAlign::Top:
        break;

    case Tooltip::VAlign::Middle:
        y -= size.y * 0.5f;
        break;

    case Tooltip::VAlign::Bottom:
        y -= size.y;
        break;
    }

    SetLocation(x, y);
}
