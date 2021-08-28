#pragma once

#include <vector>

#include "types.h"

namespace core {

	class IPool {
	public:
		virtual ~IPool() = default;
	};
	
	template <typename T>
	class Pool : public IPool {
	public:
		Pool(int initialSize = 128) {
			resize(initialSize);
		}

		void add(T object) {
			m_data.push_back(object);
		}

		void set(u64 index, T object) {
			m_data[index] = object;
		}

		[[nodiscard]] T& get(u64 index) {
			return m_data[index];
		}

		[[nodiscard]] T& operator [](u64 index) {
			return m_data[index];
		}

		void resize(u64 size) {
			m_data.resize(size);
		}

		void clear() {
			m_data.clear();
		}

		[[nodiscard]] bool isEmpty() const {
			return m_data.empty();
		}
		
		[[nodiscard]] u64 getSize() const {
			return m_data.size();
		}
	
	private:
		std::vector<T> m_data;
	};

}
