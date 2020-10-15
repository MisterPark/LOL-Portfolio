#pragma once
#include <stdlib.h>
#include <time.h>

class Random_Manager
{
public:
	static Random_Manager* Get_Instance() {
		if (nullptr == m_pInstance) {
			m_pInstance = new Random_Manager;
		}
		return m_pInstance;
	}
	static void Destroy_Instance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	Random_Manager();
	~Random_Manager();

public:
	void Ready_Random() { srand(unsigned(time(nullptr))); }
	static int Random4() {
		int iTemp;
		iTemp = rand();
		return iTemp;
	}

private:
	static Random_Manager* m_pInstance;
};

