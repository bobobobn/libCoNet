//@author Liu Yukang
#pragma once
#include "scheduler.h"
#include "mstime.h"
#include "parameter.h"

namespace netco 
{
	class NetCo
	{
	public:
		static NetCo* getNetCo(int threadNUm);
		void co_go(std::function<void()>& func, size_t stackSize = parameter::coroutineStackSize, int tid = -1) const;
		void co_go(std::function<void()>&& func, size_t stackSize = parameter::coroutineStackSize, int tid = -1) const;

		void co_sleep(int64_t ms) const;

		void sche_join() const;
	private:
		NetCo(int);
		~NetCo();
		int threadNum_;
		Scheduler* myScheduler_;
	};
}


