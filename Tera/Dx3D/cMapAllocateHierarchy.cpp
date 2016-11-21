#include "StdAfx.h"
#include "cMapAllocateHierarchy.h"
#include "cMtlTex.h"

cMapAllocateHierarchy::cMapAllocateHierarchy(void)
{
}
cMapAllocateHierarchy::~cMapAllocateHierarchy(void)
{
}

STDMETHODIMP cMapAllocateHierarchy::CreateFrame(THIS_ LPCSTR Name,
	LPD3DXFRAME *ppNewFrame)
{
	MAP_ST_BONE* pBone = new MAP_ST_BONE;
	D3DXMatrixIdentity(&pBone->TransformationMatrix);
	D3DXMatrixIdentity(&pBone->CombinedTransformationMatrix);

	// TODO : �̸��� �������ּ���.
	pBone->Name = NULL;

	pBone->pFrameFirstChild = NULL;
	pBone->pFrameSibling = NULL;
	pBone->pMeshContainer = NULL;

	*ppNewFrame = pBone;

	return S_OK;
}

STDMETHODIMP cMapAllocateHierarchy::CreateMeshContainer(THIS_ LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	MAP_ST_BONE_MESH* pBoneMesh = new MAP_ST_BONE_MESH;

	pBoneMesh->pOrgMesh = pMeshData->pMesh;
	pBoneMesh->Name = NULL;
	pBoneMesh->pAdjacency = NULL;
	pBoneMesh->pNextMeshContainer = NULL;
	pBoneMesh->pEffects = NULL;
	pBoneMesh->pMaterials = NULL;

	// step 1. pSkinInfo ����
	pBoneMesh->pSkinInfo = NULL;

	pBoneMesh->NumMaterials = 0;

	assert(pMeshData->Type == D3DXMESHTYPE_MESH);

	// step 2. ���� �޽� ����

	SAFE_ADDREF(pMeshData->pMesh);

	pBoneMesh->vecMtlTex.resize(NumMaterials);
	for (DWORD i = 0; i < NumMaterials; ++i)
	{
		pBoneMesh->vecMtlTex[i] = new cMtlTex;

		D3DMATERIAL9& stMtl = pBoneMesh->vecMtlTex[i]->GetMtl();
		stMtl = pMaterials[i].MatD3D;

		std::string sFile(pMaterials[i].pTextureFilename);
		std::string sFullPath = sFile;
		if (m_sFolder.length() > 0)
		{
			sFullPath = m_sFolder + "/" + sFile;
		}
		pBoneMesh->vecMtlTex[i]->SetTexture(g_pTextureManager->GetTexture(sFullPath));
	}

	// step 3. pSkinInfo->GetNumBones()�� ����
	// ������� ��ġ�� ��� ���� ���� ��Ʈ���� ���� ����
	// ppBoneMatrixPtrs, pBoneOffsetMatrices, pCurrentBoneMatrices�� �����Ҵ�

	// step 4. ���� �Ҵ�� pBoneOffsetMatrices ��Ʈ������ �� ����.
	// pSkinInfo->GetBoneOffsetMatrix(i)

	*ppNewMeshContainer = pBoneMesh;
	return S_OK;
}

STDMETHODIMP cMapAllocateHierarchy::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree)
{
	// TODO : ���� �� �սô�.
	SAFE_DELETE(pFrameToFree);
	return S_OK;
}

STDMETHODIMP cMapAllocateHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	// TODO : ���� �� �սô�.
	MAP_ST_BONE_MESH* pBoneMesh = (MAP_ST_BONE_MESH*)pMeshContainerToFree;

	SAFE_RELEASE(pBoneMesh->pOrgMesh);
	for (size_t i = 0; i < pBoneMesh->vecMtlTex.size(); ++i)
	{
		SAFE_RELEASE(pBoneMesh->vecMtlTex[i]);
	}
	SAFE_DELETE(pMeshContainerToFree);
	return S_OK;
}

