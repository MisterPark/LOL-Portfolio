#pragma once

namespace Engine
{
	class AnimationController : public BaseObject
	{
	private:
		explicit AnimationController(LPD3DXANIMATIONCONTROLLER pAniCtrl);
		explicit AnimationController(const AnimationController& rhs);
		virtual ~AnimationController(void);

	public:
		LPD3DXANIMATIONCONTROLLER		Get_AnimationCtrl(void) { return m_pAniCtrl; }
		bool							IsAnimationSetEnd(void);

	public:
		HRESULT			Ready_AnimationCtrl(void);

		bool			GetAnimationName(char** outName, UINT index);
		bool			GetAnimationIndex(UINT* outIndex, const char* name);
		UINT			GetNumAnimations();
		double			GetPeriod(const UINT& index);
		void			SetAnimationSet(const UINT& iIndex);

		void			PlayAnimation(const float& fTimeDelta);

	private:
		LPD3DXANIMATIONCONTROLLER			m_pAniCtrl;

		UINT								m_iCurrentTrack;
		UINT								m_iNewTrack;

		float								m_fAccTime;
		UINT								m_iOldAniIdx;

		double								m_dPeriod = 0.0;

	public:
		static AnimationController* Create(LPD3DXANIMATIONCONTROLLER pAniCtrl);
		static AnimationController* Create(const AnimationController& rhs);
		virtual void				Free(void);

	};

}

