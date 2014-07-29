#pragma once

class ReferenceCounter
{
public:
	ReferenceCounter()
	{
		m_refCount = 1;
	}

	inline void AddReference() { m_refCount++; }
	inline bool RemoveReference() { m_refCount--; return m_refCount == 0; }
	inline int GetReferenceCount() { return m_refCount; }
protected:
private:
	int m_refCount;
};
