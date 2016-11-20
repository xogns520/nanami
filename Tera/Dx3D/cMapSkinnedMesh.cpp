#include "StdAfx.h"
#include "cMapSkinnedMesh.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"

cMapSkinnedMesh::cMapSkinnedMesh(void)
: m_pRoot(NULL)
, m_pAnimController(NULL)
{
}


cMapSkinnedMesh::~cMapSkinnedMesh(void)
{
	cAllocateHierarchy alloc;
	D3DXFrameDestroy((LPD3DXFRAME)m_pRoot, &alloc);
	SAFE_RELEASE(m_pAnimController);
}

void cMapSkinnedMesh::Load(char* szFolder, char* szFile)
{
	std::string sFolder(szFolder);
	std::string sFile(szFile);
	std::string sFullPath = sFolder + "/" + sFile;

	cAllocateHierarchy alloc;
	alloc.SetFolder(sFolder);

	D3DXLoadMeshHierarchyFromX(
		sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&alloc,
		NULL,
		(LPD3DXFRAME*)&m_pRoot,
		&m_pAnimController);

	SetupBoneMatrixPtrs(m_pRoot);
}

void cMapSkinnedMesh::Update()
{
	//m_pAnimController->AdvanceTime(g_pTimeManager->GetDeltaTime(), NULL);
	D3DXMATRIXA16 mat;
	D3DXMatrixTranslation(&mat, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	Update2(m_pRoot, &mat);
	//Update(m_pRoot, NULL);
}

void cMapSkinnedMesh::Update(ST_BONE* pFrame, ST_BONE* pParent)
{
	pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	if (pParent)
	{
		pFrame->CombinedTransformationMatrix *=
			pParent->CombinedTransformationMatrix;
	}

	if (pFrame->pFrameFirstChild)
	{
		Update((ST_BONE*)pFrame->pFrameFirstChild, (ST_BONE*)pFrame);
	}

	if (pFrame->pFrameSibling)
	{
		Update((ST_BONE*)pFrame->pFrameSibling, (ST_BONE*)pParent);
	}
}

void cMapSkinnedMesh::Update2(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent)
{
	pCurrent->CombinedTransformationMatrix = pCurrent->TransformationMatrix;
	if (pmatParent)
	{
		pCurrent->CombinedTransformationMatrix =
			pCurrent->CombinedTransformationMatrix * (*pmatParent);
	}

	if (pCurrent->pFrameSibling)
	{
		Update2((ST_BONE*)pCurrent->pFrameSibling, pmatParent);
	}

	if (pCurrent->pFrameFirstChild)
	{
		Update2((ST_BONE*)pCurrent->pFrameFirstChild, &(pCurrent->CombinedTransformationMatrix));
	}
}

void cMapSkinnedMesh::Render()
{


	Render(m_pRoot);
}

void cMapSkinnedMesh::Render(ST_BONE* pFrame)
{

	if (pFrame)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		while (pBoneMesh)
		{
			for (size_t i = 0; i < pBoneMesh->vecMtlTex.size(); ++i)
			{
				g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtlTex[i]->GetMtl());
				g_pD3DDevice->SetTexture(0, pBoneMesh->vecMtlTex[i]->GetTexture());
				pBoneMesh->pOrgMesh->DrawSubset(i);
			}
			pBoneMesh = (ST_BONE_MESH*)pBoneMesh->pNextMeshContainer;
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		Render((ST_BONE*)pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		Render((ST_BONE*)pFrame->pFrameSibling);
	}
}

void cMapSkinnedMesh::UpdateSkinnedMesh(ST_BONE* pFrame)
{
	// pCurrentBoneMatrices 를 계산하시오
	// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 


	// 	BYTE* src = NULL;
	// 	BYTE* dest = NULL;
	// 
	// 	pBoneMesh->pOrgMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
	// 	pBoneMesh->pWrkMesh->LockVertexBuffer( 0, (void**)&dest );
	// 
	// 	//pWrkMesh을 업데이트 시켜준다.
	// 	pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
	// 		pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );
	// 
	// 	pBoneMesh->pWrkMesh->UnlockVertexBuffer();
	// 	pBoneMesh->pOrgMesh->UnlockVertexBuffer();


	//재귀적으로 모든 프레임에 대해서 실행.
}

void cMapSkinnedMesh::SetupBoneMatrixPtrs(ST_BONE* pFrame)
{
	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
	// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
	// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
	// 찾아서 월드매트릭스를 걸어줘라.

	//재귀적으로 모든 프레임에 대해서 실행.
}
