#pragma once

#define g_pObjectPool cObjectPool::GetInstance()

class cObjectPool
{
private:
	std::set<cObject*> m_setObject;

	SINGLETONE(cObjectPool);
public:
	void AddObject(cObject* pObject)
	{
		m_setObject.insert(pObject);
	}
	void RemoveObject(cObject* pObject)
	{
		m_setObject.erase(pObject);
	}
	void Destroy()
	{
		assert(m_setObject.empty() && "cObject�� ��ӹ��� ��ü �� �������� ���� ��ü�� �ֽ��ϴ�.");
	}
};

