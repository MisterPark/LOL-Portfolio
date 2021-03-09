#include "stdafx.h"
#include "Buff_GarenQAttack.h"
#include "Unit.h"

Buff_GarenQAttack::Buff_GarenQAttack(Unit* _host, float _duration, float _basicDamage, float _weightDamage) :Buff_OnHit(_host, _duration, _basicDamage, _weightDamage)
{
}

Buff_GarenQAttack::~Buff_GarenQAttack()
{
	host->attackState = State::ATTACK1;
}

void Buff_GarenQAttack::Update()
{
	host->attackState = State::Q;
	//1.평타추가데미지 버프들 만을 찾을수있어야함 //Buff를 dynamic_cast로 찾는건 노가다. 같은타입 다른버프들을 다같이 찾을수 있을만한.
	//2.기본수치데미지를 저장하고있어야함.
	//3.계수데미지를 저장하고있어함.
	/* {가렌Q버프 잭스W 이즈Q 레오나Q }
	 Buff -> Buff_OnHit -> Buff_GarenQAttack
						->Buff_JaxQAttack*/
}
