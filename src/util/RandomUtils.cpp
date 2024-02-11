#include "RandomUtils.hpp"
#include "iostream"
namespace RandomUtils {
	RandomUtils::RandomUtils()
	{
		std::random_device device;
		m_engine = std::default_random_engine(device());
	}

	RandomUtils* RandomUtils::RandomUtils::GetInstance()
	{
		if (!m_instance) {
			m_instance = new RandomUtils();
		}
		
		return m_instance;
	}

	int RandomUtils::generateInt(int a, int b)
	{
		return std::uniform_int_distribution(a, b)(m_engine);
	}

    double RandomUtils::generateDouble(double a, double b) {
        return std::uniform_real_distribution<double>(a,b)(m_engine);
    }

    double RandomUtils::generateDouble() {
        return std::uniform_real_distribution<double>(0,1)(m_engine);
    }

    bool RandomUtils::generateBool() {
        return std::uniform_int_distribution(0,1)(m_engine);
    }

}
