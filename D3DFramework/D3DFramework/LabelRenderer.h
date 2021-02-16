#pragma once
#include "UIRenderer.h"

class Label;

class LabelRenderer :
    public UIRenderer
{
public:
    explicit LabelRenderer(GameObject* owner);
    virtual void Render() override;

    void SetLabel(Label* label);

private:
    Label* label = nullptr;
};

