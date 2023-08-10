#pragma once

#include <iostream>
#include <functional>
#include <unordered_map>

namespace FangFSMLibrary {

    template <typename T>
    class FangFSM {
     public:
        FangFSM(T start, T end) :
            start_state_{start},
            end_state_{end},
            current_state_{start} {}

        void RegisterTransitionFct(T current, std::function<T(void)> func);

        void RegisterStateFct(T state, std::function<void(void)> func);

        void Reset();

        void Run();

        const T& GetCurrentState() const {
            return current_state_;
        }

     private:
        std::unordered_map<T, std::function<void(void)>> state_;

        std::unordered_map<T, std::function<T(void)>> transition_fcts_;

        const T start_state_, end_state_;
        T current_state_;
    };

    template <typename T>
    void FangFSM<T>::RegisterTransitionFct(T current, std::function<T(void)> func) {
        transition_fcts_[current] = func;
    }

    template <typename T>
    void FangFSM<T>::RegisterStateFct(T state, std::function<void(void)> func) {
        state_[state] = func;
    }

    template <typename T>
    void FangFSM<T>::Reset() {
        current_state_ = start_state_;
    }

    template <typename T>
    void FangFSM<T>::Run() {
        state_[current_state_]();
        current_state_ = (transition_fcts_[current_state_]());
    }

}
