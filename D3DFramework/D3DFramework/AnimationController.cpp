#include "stdafx.h"
#include "AnimationController.h"

AnimationController::AnimationController(LPD3DXANIMATIONCONTROLLER pAniCtrl)
	: m_pAniCtrl(pAniCtrl)
	, m_iCurrentTrack(0)
	, m_iNewTrack(1)
	, m_fAccTime(0.f)
	, m_iOldAniIdx(99)
{
	m_pAniCtrl->AddRef();
}

AnimationController::AnimationController(const AnimationController& rhs)
	: m_iCurrentTrack(rhs.m_iCurrentTrack)
	, m_iNewTrack(rhs.m_iNewTrack)
	, m_fAccTime(rhs.m_fAccTime)
	, m_iOldAniIdx(rhs.m_iOldAniIdx)
{
	rhs.m_pAniCtrl->CloneAnimationController(rhs.m_pAniCtrl->GetMaxNumAnimationOutputs(), // 복제 시 원본 객체에서 제공되고 있는 애니메이션의 개수
		rhs.m_pAniCtrl->GetMaxNumAnimationSets(), // 구동 가능한 애니메이션의 최대 개수(대게는 1과 같음)
		rhs.m_pAniCtrl->GetMaxNumTracks(),		  // 애니메이션을 재생하기 위한 최대 트랙의 개수(대부분 한 개를 사용, 정말 많이 사용해야 두 개 사용)
		rhs.m_pAniCtrl->GetMaxNumEvents(),		  // 애니메이션 재생 시 적용되는 독특한 이벤트(우리는 사용 못함)
		&m_pAniCtrl);
}

AnimationController::~AnimationController(void)
{

}

HRESULT AnimationController::Ready_AnimationCtrl(void)
{
	return S_OK;
}

bool PKH::AnimationController::GetAnimationName(char** outName, UINT index)
{
	LPD3DXANIMATIONSET pAS = NULL;
	HRESULT res = m_pAniCtrl->GetAnimationSet(index, &pAS);
	if (res == S_OK)
	{
		*outName = (char*)pAS->GetName();
		return true;
	}

	return false;
}

bool PKH::AnimationController::GetAnimationIndex(UINT* outIndex, const char* name)
{
	LPD3DXANIMATIONSET pAS = NULL;
	UINT animCount = m_pAniCtrl->GetNumAnimationSets();
	
	HRESULT res = m_pAniCtrl->GetAnimationSetByName(name, &pAS);
	if (res == S_OK)
	{
		LPD3DXANIMATIONSET pAnim;
		for (UINT i = 0; i < animCount; i++)
		{
			m_pAniCtrl->GetAnimationSet(i, &pAnim);
			if (pAS == pAnim)
			{
				*outIndex = i;
				return true;
			}
		}
	}
	return false;
}

UINT PKH::AnimationController::GetNumAnimations()
{
	return m_pAniCtrl->GetNumAnimationSets();
}

double PKH::AnimationController::GetPeriod(const UINT& index)
{
	LPD3DXANIMATIONSET		pAS = NULL;

	m_pAniCtrl->GetAnimationSet(index, &pAS);
	return pAS->GetPeriod();
}

void AnimationController::SetAnimationSet(const UINT& iIndex)
{
	if (m_iOldAniIdx == iIndex)
		return;

	m_iNewTrack = (m_iCurrentTrack == 0 ? 1 : 0);

	LPD3DXANIMATIONSET		pAS = NULL;

	// 인덱스 값에 해당하는 애니메이션 셋을 얻어는 함수
	m_pAniCtrl->GetAnimationSet(iIndex, &pAS);
	//m_pAniCtrl->GetAnimationSetByName()

	m_dPeriod = pAS->GetPeriod(); // 애니메이션 셋의 재생 시간을 반환하는 함수


	// 0번 트랙에 애니메이션 셋 세팅
	m_pAniCtrl->SetTrackAnimationSet(m_iNewTrack, pAS);


	// 애니메이션 정보 안에 삽입되어 있는 이벤트 정보를 해제하는 함수(이벤트가 없는 것으로 처리)
	// : 우리가 이벤트를 사용할 수 없는 상황인데, 정보가 삽입되어 있는 경우 가끔 애니메이션이 보간 되지 않는 문제가 발생
	m_pAniCtrl->UnkeyAllTrackEvents(m_iCurrentTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(m_iNewTrack);

	// 현재 설정된 트랙을 재생 또는 종료 시키기 위한 함수(3인자 : 언제부터 현재 트랙을 해제할 것인가)
	m_pAniCtrl->KeyTrackEnable(m_iCurrentTrack, FALSE, m_fAccTime + 0.25);

	// 인자값으로 들어오는 트랙에 세팅된 애니메이션 셋을 어떤 속도로 움직일 것인지 설정하는 함수(속도의 상수 값은 1)
	m_pAniCtrl->KeyTrackSpeed(m_iCurrentTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	// 인자값으로 들어오는 트랙의 가중치를 설정하는 함수
	m_pAniCtrl->KeyTrackWeight(m_iCurrentTrack, 0.1f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);


	// New 트랙의 활성화를 지시하는 함수
	m_pAniCtrl->SetTrackEnable(m_iNewTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(m_iNewTrack, 1.f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(m_iNewTrack, 0.9f, m_fAccTime, 0.25, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->ResetTime(); // AdvanceTime 호출 시 내부적으로 누적되던 시간을 초기화하는 함수
	m_fAccTime = 0.f;

	// 기존의 재생 중이던 트랙에서 새로운 트랙으로 변경을 했기 때문에 재생 시점을 0초(0의 위치로 초기화)로 시작하도록 지시하는 함수
	m_pAniCtrl->SetTrackPosition(m_iNewTrack, 0.0);

	m_iOldAniIdx = iIndex;
	m_iCurrentTrack = m_iNewTrack;
}

void AnimationController::PlayAnimation(const float& fTimeDelta)
{
	m_pAniCtrl->AdvanceTime(fTimeDelta, NULL);	// 2인자 : 애니메이션 재생에 따라 사운드나, 이펙트를 구동 가능, 하지만 안씀.
	// AdvanceTime 호출 시 내부적으로 누적되는 시간 값이 있음

	m_fAccTime += fTimeDelta;
}

AnimationController* AnimationController::Create(LPD3DXANIMATIONCONTROLLER pAniCtrl)
{
	AnimationController* pInstance = new AnimationController(pAniCtrl);

	if (FAILED(pInstance->Ready_AnimationCtrl()))
		Safe_Release(&pInstance);

	return pInstance;
}

AnimationController* AnimationController::Create(const AnimationController& rhs)
{
	AnimationController* pInstance = new AnimationController(rhs);

	if (FAILED(pInstance->Ready_AnimationCtrl()))
		Safe_Release(&pInstance);

	return pInstance;
}

void AnimationController::Free(void)
{
	
	Safe_Release(&m_pAniCtrl);
}

bool AnimationController::IsAnimationSetEnd(void)
{
	D3DXTRACK_DESC		tTrackInfo;
	ZeroMemory(&tTrackInfo, sizeof(D3DXTRACK_DESC));

	m_pAniCtrl->GetTrackDesc(m_iCurrentTrack, &tTrackInfo);
	
	if (tTrackInfo.Position >= m_dPeriod - 0.1)
		return true;

	return false;
}