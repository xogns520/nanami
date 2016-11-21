#include "StdAfx.h"
#include "cMapSkinnedMesh.h"
#include "cMapAllocateHierarchy.h"
#include "cMtlTex.h"

cMapSkinnedMesh::cMapSkinnedMesh(void)
: m_pRoot(NULL)
, m_pAnimController(NULL)
{
}


cMapSkinnedMesh::~cMapSkinnedMesh(void)
{
	cMapAllocateHierarchy alloc;
	D3DXFrameDestroy((LPD3DXFRAME)m_pRoot, &alloc);
	SAFE_RELEASE(m_pAnimController);
}

void cMapSkinnedMesh::Load(char* szFolder, char* szFile)
{
	std::string sFolder(szFolder);
	std::string sFile(szFile);
	std::string sFullPath = sFolder + "/" + sFile;

	cMapAllocateHierarchy alloc;
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

void cMapSkinnedMesh::Update(MAP_ST_BONE* pFrame, MAP_ST_BONE* pParent)
{
	pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	if (pParent)
	{
		pFrame->CombinedTransformationMatrix *=
			pParent->CombinedTransformationMatrix;
	}

	if (pFrame->pFrameFirstChild)
	{
		Update((MAP_ST_BONE*)pFrame->pFrameFirstChild, (MAP_ST_BONE*)pFrame);
	}

	if (pFrame->pFrameSibling)
	{
		Update((MAP_ST_BONE*)pFrame->pFrameSibling, (MAP_ST_BONE*)pParent);
	}
}

void cMapSkinnedMesh::Update2(MAP_ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent)
{
	pCurrent->CombinedTransformationMatrix = pCurrent->TransformationMatrix;
	if (pmatParent)
	{
		pCurrent->CombinedTransformationMatrix =
			pCurrent->CombinedTransformationMatrix * (*pmatParent);
	}

	if (pCurrent->pFrameSibling)
	{
		Update2((MAP_ST_BONE*)pCurrent->pFrameSibling, pmatParent);
	}

	if (pCurrent->pFrameFirstChild)
	{
		Update2((MAP_ST_BONE*)pCurrent->pFrameFirstChild, &(pCurrent->CombinedTransformationMatrix));
	}
}

void cMapSkinnedMesh::Render()
{


	Render(m_pRoot);
}

void cMapSkinnedMesh::Render(MAP_ST_BONE* pFrame)
{

	if (pFrame)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
		MAP_ST_BONE_MESH* pBoneMesh = (MAP_ST_BONE_MESH*)pFrame->pMeshContainer;
		while (pBoneMesh)
		{
			for (size_t i = 0; i < pBoneMesh->vecMtlTex.size(); ++i)
			{
				g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtlTex[i]->GetMtl());
				g_pD3DDevice->SetTexture(0, pBoneMesh->vecMtlTex[i]->GetTexture());
				pBoneMesh->pOrgMesh->DrawSubset(i);
			}
			pBoneMesh = (MAP_ST_BONE_MESH*)pBoneMesh->pNextMeshContainer;
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		Render((MAP_ST_BONE*)pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		Render((MAP_ST_BONE*)pFrame->pFrameSibling);
	}
}

bool cMapSkinnedMesh::GetHeight(IN float x, OUT float& y, IN float z)
{
	D3DXVECTOR3 vRayPos(x, 20000, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);
	//LPBOOL Hit;
	//MAP_ST_BONE_MESH* pBoneMesh = (MAP_ST_BONE_MESH*)mesh.m_pRoot->pMeshContainer;
	MAP_ST_BONE_MESH* pBoneMesh = (MAP_ST_BONE_MESH*)m_pRoot->pMeshContainer;
	//for (size_t i = 0; i < m_vecSurface.size(); i += 3)
	{
		//float u, v, d;
		float d;
		BOOL Hit;
		//if (D3DXIntersectTri(&m_vecSurface[i + 0],
		//	&m_vecSurface[i + 1],
		//	&m_vecSurface[i + 2],
		//	&vRayPos,
		//	&vRayDir,
		//	&u, &v, &d))
		D3DXIntersect(pBoneMesh->pOrgMesh, &vRayPos, &vRayDir, &Hit, NULL, NULL, NULL, &d, NULL, NULL);

		if(Hit)
		{
			y = 20000 - d;
			return true;
		}
		else return false;
	}
	//return false;
}

void cMapSkinnedMesh::UpdateSkinnedMesh(MAP_ST_BONE* pFrame)
{
	// pCurrentBoneMatrices �� ����Ͻÿ�
	// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 


	// 	BYTE* src = NULL;
	// 	BYTE* dest = NULL;
	// 
	// 	pBoneMesh->pOrgMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
	// 	pBoneMesh->pWrkMesh->LockVertexBuffer( 0, (void**)&dest );
	// 
	// 	//pWrkMesh�� ������Ʈ �����ش�.
	// 	pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
	// 		pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );
	// 
	// 	pBoneMesh->pWrkMesh->UnlockVertexBuffer();
	// 	pBoneMesh->pOrgMesh->UnlockVertexBuffer();


	//��������� ��� �����ӿ� ���ؼ� ����.
}

void cMapSkinnedMesh::SetupBoneMatrixPtrs(MAP_ST_BONE* pFrame)
{
	// �� �������� �޽� �����̳ʿ� �ִ� pSkinInfo�� �̿��Ͽ� ����޴� ��� 
	// �������� ��Ʈ������ ppBoneMatrixPtrs�� �����Ѵ�.
	// pSkinInfo->GetNumBones() ���� ����޴� ���� ������ ã��.
	// pSkinInfo->GetBoneName(i) �� i�� �������� �̸��� ã��
	// D3DXFrameFind(��Ʈ ������, ������ �̸�) �� �������� ã��.
	// ã�Ƽ� �����Ʈ������ �ɾ����.

	//��������� ��� �����ӿ� ���ؼ� ����.
}
