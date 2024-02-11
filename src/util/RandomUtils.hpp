#ifndef MYLIB_H_
#define MYLIB_H_

#include <string>
#include <random>
#include <vector>

namespace RandomUtils {
	class RandomUtils {
#pragma region Singleton
	protected:
		RandomUtils();
        ~RandomUtils() {
            free(m_instance);
        }
		inline static RandomUtils* m_instance;
		inline static std::default_random_engine m_engine;
	public:
		RandomUtils(RandomUtils&) = delete;
		void operator=(const RandomUtils&) = delete;

		static RandomUtils* GetInstance();
#pragma endregion
	public:
		int generateInt(int a, int b);
        double generateDouble(double a, double b);
        double generateDouble();
        bool generateBool();

        template<typename T, typename A>
        T getRandomItem(const std::vector<T, A>& v) {
            if(v.empty()) {
                throw "Vector is empty";
            }

        return v[generateInt(0, v.size() - 1)];
        }
	};
}
#endif // MYLIB_H_
