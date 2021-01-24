#pragma once


typedef struct D3DXFRAME_DERIVED : public D3DXFRAME
{
	Matrix			CombinedTransformationMatrix;

}D3DXFRAME_DERIVED;

typedef struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9* ppTexture;

	LPD3DXMESH				pOriMesh;	// x파일을 로드했을 때 최초의 상태를 가지고 있는 컴 객체(불변)

	ULONG					dwNumBones;	// 뼈의 개수를 보관하는 변수


	Matrix* pFrameOffsetMatrix;	// 애니메이션을 포함한 최초의 뼈 상태
	Matrix** ppFrameCombinedMatrix;	// frame 마다 가지고 있는 CombinedTransformationMatrix의 주소값들을 보관하기 위한 포인터
	Matrix* pRenderingMatrix;	//pFrameOffsetMatrix * (*ppFrameCombinedMatrix) 결과값으로 최종적으로 렌더링을 하기 위한 행렬


}D3DXMESHCONTAINER_DERIVED;

enum class ChampionType : char
{
	Garen,Darius,Diana,Leona,Leesin,Missfortune,Blitzcrank,Ahri,Jax,Jinx
};

enum class SpellType : char
{
	Barrier,Boost,Exhaust,Flash,Haste,Heal,Ignite,Mana,Smite,Teleport
};