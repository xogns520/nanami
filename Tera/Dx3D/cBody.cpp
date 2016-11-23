#include "StdAfx.h"
#include "cBody.h"
#include "cAllocateHierarchy.h"
#include "cSkinnedMeshManager.h"

cBody::cBody(char* szFolder, char* szFilename)
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
	, m_vPosition(0, 0, 0)
	, m_fPassedAnimBlendTime(0.0f)
	, m_fAnimBlendTime(0.3f)
{
	cBody* pSkinnedMesh = (cBody*)g_pSkinnedMeshManager->GetSkinnedMesh(szFolder, szFilename);

	m_pRootFrame = pSkinnedMesh->m_pRootFrame;
	m_dwWorkingPaletteSize = pSkinnedMesh->m_dwWorkingPaletteSize;
	m_pmWorkingPalette = pSkinnedMesh->m_pmWorkingPalette;
	m_pEffect = pSkinnedMesh->m_pEffect;
	m_stBoundingSphere = pSkinnedMesh->m_stBoundingSphere;
	m_stBoundingBox = pSkinnedMesh->m_stBoundingBox;

	pSkinnedMesh->m_pAnimController->CloneAnimationController(
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationOutputs(),
		pSkinnedMesh->m_pAnimController->GetMaxNumAnimationSets(),
		pSkinnedMesh->m_pAnimController->GetMaxNumTracks(),
		pSkinnedMesh->m_pAnimController->GetMaxNumEvents(),
		&m_pAnimController);
}

void cBody::GetNeckWorld(D3DXFRAME * pFrame, D3DXMATRIX * pParentTM)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	D3DXMATRIXA16 matW;
	D3DXMatrixIdentity(&matW);
	if (pBone->Name != nullptr && std::string(pBone->Name) == std::string("Bip01-Neck"))
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix * (*pParentTM);
		m_matNeckTM = pBone->CombinedTransformationMatrix;
		//D3DXMatrixRotationX(&m_matNeckTM, D3DXToRadian(90));
	}
	else if (pBone->Name != nullptr && std::string(pBone->Name) == std::string("Bip01-Head"))
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix * (*pParentTM);
		m_matHairTM = pBone->CombinedTransformationMatrix;
		//D3DXMatrixRotationX(&m_matNeckTM, D3DXToRadian(90));
	}
	else if (pBone->Name != nullptr && std::string(pBone->Name) == std::string("Bip01-L-Hand"))
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix * (*pParentTM);
		D3DXMATRIXA16 matT, matYR, matXR;
		D3DXMatrixRotationY(&matYR, -1.75f);
		D3DXMatrixRotationX(&matXR, 0.25f);
		D3DXMatrixTranslation(&matT, -0.01f, 0.0f, 0.03f);
		m_matLWeaponTM = matYR * matXR * matT * pBone->CombinedTransformationMatrix;
		//D3DXMatrixRotationX(&m_matNeckTM, D3DXToRadian(90));
	}
	//R_Sword or Bip01-R-Hand or Bip01-R-Finger3Nub
	else if (pBone->Name != nullptr && std::string(pBone->Name) == std::string("Bip01-R-Hand"))
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix * (*pParentTM);
		D3DXMATRIXA16 matT, matYR, matXR;
		D3DXMatrixRotationY(&matYR, -1.75f);
		D3DXMatrixRotationX(&matXR, 0.25f);
		D3DXMatrixTranslation(&matT, -0.01f, 0.0f, 0.03f);
		m_matRWeaponTM = /*matYR * matXR * matT * */pBone->CombinedTransformationMatrix;
		//D3DXMatrixRotationX(&m_matNeckTM, D3DXToRadian(90));
	}
	//Bip01-Pelvis or Bip01-Spine
	else if (pBone->Name != nullptr && std::string(pBone->Name) == std::string("Bip01-Spine"))
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix * (*pParentTM);
		m_matTaliTM = pBone->CombinedTransformationMatrix;
		//D3DXMatrixRotationX(&m_matNeckTM, D3DXToRadian(90));
	}
	else if (pBone->Name != nullptr && std::string(pBone->Name) == std::string("Dummy_root"))
	{
		pBone->CombinedTransformationMatrix = pBone->TransformationMatrix * (*pParentTM);
		m_matRootTM = pBone->CombinedTransformationMatrix;
		//D3DXMatrixRotationX(&m_matNeckTM, D3DXToRadian(90));
	}
	//-180 180 180
	if (pFrame->pFrameSibling)
	{
		GetNeckWorld(pFrame->pFrameSibling, &pBone->CombinedTransformationMatrix);
	}
	if (pFrame->pFrameFirstChild)
	{
		GetNeckWorld(pFrame->pFrameFirstChild, &pBone->CombinedTransformationMatrix);
	}
}

cBody::cBody()
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
{
}

cBody::~cBody(void)
{
	//Destroy();
	SAFE_RELEASE(m_pAnimController);
}

void cBody::Load(char* szDirectory, char* szFilename)
{
	m_pEffect = LoadEffect("MultiAnimation.hpp");

	int nPaletteSize = 0;
	m_pEffect->GetInt("MATRIX_PALETTE_SIZE", &nPaletteSize);

	cAllocateHierarchy ah;
	ah.SetDirectory(szDirectory);
	ah.SetDefaultPaletteSize(nPaletteSize);

	std::string sFullPath(szDirectory);
	sFullPath += std::string(szFilename);

	D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&ah,
		NULL,
		(LPD3DXFRAME*)&m_pRootFrame,
		&m_pAnimController);

	if (m_pmWorkingPalette)
		delete[] m_pmWorkingPalette;

	m_dwWorkingPaletteSize = ah.GetMaxPaletteSize();
	m_pmWorkingPalette = new D3DXMATRIX[m_dwWorkingPaletteSize];
	if (m_pmWorkingPalette == NULL)
	{
		m_dwWorkingPaletteSize = 0;
	}

	if (m_pRootFrame)
		SetupBoneMatrixPtrs(m_pRootFrame);

	m_stBoundingSphere = ah.GetBoundingSphere();
	m_stBoundingBox = ah.GetBoundingBox();

	//m_stBoundingSphere.vCenter = (ah.GetMin() + ah.GetMax()) / 2.0f;
	//m_stBoundingSphere.fRadius = D3DXVec3Length(&(ah.GetMin() - ah.GetMax()));
}

void cBody::UpdateAndRender(D3DXMATRIXA16* pCamaraMat)
{
	if (m_pAnimController)
	{
		m_pAnimController->AdvanceTime(g_pTimeManager->GetDeltaTime(), NULL);
		m_fPassedAnimBlendTime += g_pTimeManager->GetDeltaTime();

		if (m_fPassedAnimBlendTime < m_fAnimBlendTime)
		{
			m_fPassedAnimBlendTime += g_pTimeManager->GetDeltaTime(); //���� ����
																	  //m_pAnimController->ResetTime();
			if (m_fPassedAnimBlendTime > m_fAnimBlendTime) //���� �ð��� ������
			{
				m_pAnimController->SetTrackWeight(0, 1.0f); //0���� ����Ʈ ����
				m_pAnimController->SetTrackEnable(1, false); //1�� Ʈ���� ����
			}
			else
			{
				float f = m_fPassedAnimBlendTime / m_fAnimBlendTime; //������ ���ؼ�
				m_pAnimController->SetTrackWeight(0, f);      //0�� Ʈ���� ����ġ�� 0->1��
				m_pAnimController->SetTrackWeight(1, 1 - f);  //1�� Ʈ���� ����ġ�� 1->0����
			}
		}
	}

	if (m_pRootFrame)
	{
		//D3DXMATRIXA16 mat;
		//D3DXMatrixTranslation(&mat, m_vPosition.x, m_vPosition.y, m_vPosition.z);

		Update(m_pRootFrame, pCamaraMat);
		GetNeckWorld(m_pRootFrame, NULL);
		Render(m_pRootFrame);
	}
}

void cBody::Render(ST_BONE* pBone /*= NULL*/)
{
	assert(pBone);

	// �� �������� �޽� �����̳ʿ� �ִ� pSkinInfo�� �̿��Ͽ� ����޴� ��� 
	// �������� ��Ʈ������ ppBoneMatrixPtrs�� �����Ѵ�.
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

		// get bone combinations
		LPD3DXBONECOMBINATION pBoneCombos =
			(LPD3DXBONECOMBINATION)(pBoneMesh->pBufBoneCombos->GetBufferPointer());

		D3DXMATRIXA16 matViewProj, matView, matProj;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		matViewProj = matView * matProj;

		D3DXMATRIXA16 mView, mInvView;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &mView);
		D3DXMatrixInverse(&mInvView, 0, &mView);
		D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, 0);
		D3DXVec3TransformCoord(&vEye, &vEye, &mInvView);

		// for each palette
		for (DWORD dwAttrib = 0; dwAttrib < pBoneMesh->dwNumAttrGroups; ++dwAttrib)
		{
			// set each transform into the palette
			for (DWORD dwPalEntry = 0; dwPalEntry < pBoneMesh->dwNumPaletteEntries; ++dwPalEntry)
			{
				DWORD dwMatrixIndex = pBoneCombos[dwAttrib].BoneId[dwPalEntry];
				if (dwMatrixIndex != UINT_MAX)
				{
					m_pmWorkingPalette[dwPalEntry] =
						pBoneMesh->pBoneOffsetMatrices[dwMatrixIndex] *
						(*pBoneMesh->ppBoneMatrixPtrs[dwMatrixIndex]);
				}
			}

			// set the matrix palette into the effect
			m_pEffect->SetMatrixArray("amPalette",
				m_pmWorkingPalette,
				pBoneMesh->dwNumPaletteEntries);

			m_pEffect->SetMatrix("g_mViewProj", &matViewProj);
			m_pEffect->SetVector("vLightDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
			m_pEffect->SetVector("vWorldLightPos", &D3DXVECTOR4(500.0f, 500.0f, 500.0f, 1.0f));
			m_pEffect->SetVector("vWorldCameraPos", &D3DXVECTOR4(vEye, 1.0f));
			m_pEffect->SetVector("vMaterialAmbient", &D3DXVECTOR4(0.53f, 0.53f, 0.53f, 0.53f));
			m_pEffect->SetVector("vMaterialDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

			// we're pretty much ignoring the materials we got from the x-file; just set
			// the texture here
			m_pEffect->SetTexture("g_txScene", pBoneMesh->vecTexture[pBoneCombos[dwAttrib].AttribId]);

			// set the current number of bones; this tells the effect which shader to use
			m_pEffect->SetInt("CurNumBones", pBoneMesh->dwMaxNumFaceInfls - 1);

			// set the technique we use to draw
			m_pEffect->SetTechnique("Skinning20");

			UINT uiPasses, uiPass;

			// run through each pass and draw
			m_pEffect->Begin(&uiPasses, 0);
			for (uiPass = 0; uiPass < uiPasses; ++uiPass)
			{
				m_pEffect->BeginPass(uiPass);
				pBoneMesh->pWorkingMesh->DrawSubset(dwAttrib);
				m_pEffect->EndPass();
			}
			m_pEffect->End();
		}
	}

	//��������� ��� �����ӿ� ���ؼ� ����.
	if (pBone->pFrameSibling)
	{
		Render((ST_BONE*)pBone->pFrameSibling);
	}

	if (pBone->pFrameFirstChild)
	{
		Render((ST_BONE*)pBone->pFrameFirstChild);
	}
}

LPD3DXEFFECT cBody::LoadEffect(char* szFilename)
{
	LPD3DXEFFECT pEffect = NULL;

	D3DXMACRO mac[2] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL,                          NULL }
	};

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	g_pD3DDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion > D3DVS_VERSION(1, 1))
		pmac = mac;

	DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	ID3DXBuffer* pBuffer = NULL;
	if (FAILED(D3DXCreateEffectFromFile(g_pD3DDevice,
		szFilename,
		pmac,
		NULL,
		dwShaderFlags,
		NULL,
		&pEffect,
		&pBuffer)))
	{
		// if creation fails, and debug information has been returned, output debug info
		if (pBuffer)
		{
			OutputDebugStringA((char*)pBuffer->GetBufferPointer());
			SAFE_RELEASE(pBuffer);
		}

		return NULL;
	}

	return pEffect;
}

void cBody::Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent)
{
	pCurrent->CombinedTransformationMatrix = pCurrent->TransformationMatrix;

	

	if (pmatParent)
	{
		pCurrent->CombinedTransformationMatrix =
			pCurrent->CombinedTransformationMatrix * (*pmatParent);
	}

	if (pCurrent->pFrameSibling)
	{
		Update((ST_BONE*)pCurrent->pFrameSibling, pmatParent);
	}

	if (pCurrent->pFrameFirstChild)
	{
		Update((ST_BONE*)pCurrent->pFrameFirstChild, &(pCurrent->CombinedTransformationMatrix));
	}
}

void cBody::SetupBoneMatrixPtrs(ST_BONE* pBone)
{
	assert(pBone);

	// �� �������� �޽� �����̳ʿ� �ִ� pSkinInfo�� �̿��Ͽ� ����޴� ��� 
	// �������� ��Ʈ������ ppBoneMatrixPtrs�� �����Ѵ�.
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			// pSkinInfo->GetNumBones() ���� ����޴� ���� ������ ã��.
			// pSkinInfo->GetBoneName(i) �� i�� �������� �̸��� ã��
			// D3DXFrameFind(��Ʈ ������, ������ �̸�) �� �������� ã��.
			// ã�Ƽ� �����Ʈ������ �ɾ����.
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				LPCSTR szBoneName = pSkinInfo->GetBoneName(i);
				if (szBoneName == NULL || strlen(szBoneName) == 0)
					continue;
				ST_BONE* pInfluence = (ST_BONE*)D3DXFrameFind(m_pRootFrame, szBoneName);
				pBoneMesh->ppBoneMatrixPtrs[i] = &(pInfluence->CombinedTransformationMatrix);
			}
		}
	}

	//��������� ��� �����ӿ� ���ؼ� ����.
	if (pBone->pFrameSibling)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameSibling);
	}

	if (pBone->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameFirstChild);
	}
}

void cBody::SetAnimationIndex(int nIndex)
{
	if (!m_pAnimController)
		return;
	//LPD3DXANIMATIONSET pAnimSet = NULL;
	//m_pAnimController->GetAnimationSet(nIndex, &pAnimSet);
	//m_pAnimController->SetTrackAnimationSet(0, pAnimSet);
	//SAFE_RELEASE(pAnimSet);

	//�ִϸ��̼� ��Ʈ�� �غ� ��
	LPD3DXANIMATIONSET pPrevAnimSet = NULL; //���� �ִϸ��̼�
	LPD3DXANIMATIONSET pNextAnimSet = NULL; //���� �ִϸ��̼�
	
	m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet); //���� 0�� Ʈ���� �ִϸ��̼��� ���� �ִϸ��̼Ǽ�Ʈ��
	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet); //���ڷ� ���� �ִϸ��̼Ǽ�Ʈ�� ���� �ִϸ��̼Ǽ�Ʈ��
	
	D3DXTRACK_DESC stTrackDest;
	m_pAnimController->GetTrackDesc(0, &stTrackDest); //0�� Ʈ���� ������ �޾ƿͼ�
	m_pAnimController->SetTrackDesc(1, &stTrackDest); //1�� Ʈ������ �Ű��� (����)
	
	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet); //0�� Ʈ���� ���� �ִϸ��̼��� ����
	m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet); //1�� Ʈ���� ���� �ִϸ��̼��� ����
															  //(�Լ��� ������ �� 0���� �׻� ���� �ִϸ��̼��̿��� �ϹǷ�)
	
	m_pAnimController->SetTrackWeight(0, 0.0f); //0��Ʈ���� �����ִϸ��̼��̹Ƿ� ����ġ�� 0����
	m_pAnimController->SetTrackWeight(1, 1.0f); //1��Ʈ���� �����ִϸ��̼��̹Ƿ� ����ġ�� 1��
	
	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pNextAnimSet);
	
	m_fPassedAnimBlendTime = 0.0f; //���� �ð� �ʱ�ȭ
}

void cBody::Destroy()
{
	cAllocateHierarchy ah;
	D3DXFrameDestroy((LPD3DXFRAME)m_pRootFrame, &ah);
	SAFE_DELETE_ARRAY(m_pmWorkingPalette);
	SAFE_RELEASE(m_pEffect);
}

void cBody::SetRandomTrackPosition()
{
	m_pAnimController->SetTrackPosition(0, (rand() % 100) / 10.0f);
}
