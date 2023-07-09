#include <iostream>
#include <functional>
#include <unordered_map>

template <typename T>
class FangFSM {
 public:
    FangFSM(T start, T end) : start_state_{start}, end_state_{end} {}

    void RegisterTransitionFct(T current, T next, std::function<bool(void)> func);

    void RegisterStateFct(T state, std::function<void(void)> func);

    void Run();

 private:
    using MyStateType = std::unordered_map<T, std::function>;

    MyStateType state_;

    std::unordered_map<T, MyStateType> transition_fcts_;

    T start_state_, end_state_;
};

template <typename T>
void FangFSM<T>::RegisterTransitionFct(T current, T next, std::function<bool(void)> func) {

}

template <typename T>
void FangFSM<T>::RegisterStateFct(T state, std::function<void(void)> func) {
    state_[state] = func;
}

int main() {
}
