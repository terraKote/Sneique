#pragma once

template <typename TClass>
class Singleton
{
protected:
	Singleton() {  }
	~Singleton() { }

public:
	static TClass* GetInstance() {
		static TClass instance;
		return &instance;
	}

	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;
};

