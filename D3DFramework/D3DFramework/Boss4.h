#pragma once

namespace PKH {
	class Boss4 :
		public GameObject
	{
	public:
		Boss4();
		virtual ~Boss4();
		void Ready();
		// GameObject을(를) 통해 상속됨
		virtual void Update() override;
	public:
		int GetHp() { return BossHp; }
		void DecHp(int Att) { BossHp -= Att; }
		void OnCollision(GameObject* target);
	private:
		void BossPattern();
		void CreateBullet2(Vector3 _vec, int BulletPosZ);
		void CreateBullet3(int Code, Vector3 _vec, int BulletPosZ, Vector3 _pos);


	public:
		GameObject* TargetPlayer;
		Vector3 TargetPos;
		Vector3 dir;
		float BossBulletRegenTime;
		float BossPatternTime[5];
		int BossPatternNumber1;
		int BossPatternNumber2;
		int BossHp;
	};
}

