#include <iostream>
#include <functional>
#include <unordered_map>

template <typename T>
class FangFSM {
 public:
    FangFSM(T start, T end) :
        start_state_{static_cast<uint8_t>(start)},
        end_state_{static_cast<uint8_t>(end)},
        current_state_{static_cast<uint8_t>(start)} {}

    void RegisterTransitionFct(T current, std::function<T(void)> func);

    void RegisterStateFct(T state, std::function<void(void)> func);

    void Reset();

    void Run();

    void CurrentStateLog() const {
        std::printf("current state: %d\n", current_state_);
    }

 private:
    std::unordered_map<T, std::function<void(void)>> state_;

    std::unordered_map<T, std::function<T(void)>> transition_fcts_;

    const uint8_t start_state_, end_state_;
    uint8_t current_state_;
};

template <typename T>
void FangFSM<T>::RegisterTransitionFct(T current, std::function<T(void)> func) {
    //transition_fcts_[static_cast<uint8_t>(current)] = func;
    transition_fcts_[current] = func;
}

template <typename T>
void FangFSM<T>::RegisterStateFct(T state, std::function<void(void)> func) {
    state_[static_cast<uint8_t>(state)] = func;
}

template <typename T>
void FangFSM<T>::Reset() {
    current_state_ = start_state_;
}

template <typename T>
void FangFSM<T>::Run() {
    current_state_ = static_cast<uint8_t>(transition_fcts_[current_state_]());
    state_[current_state_]();
}

enum class Status {
    q0,
    q1,
    end
};

int output;
int count = 0;

Status trans_to_q0() {
    if (count > 10) {
        return Status::end;
    } else if (output == 1) {
        return Status::q1;
    }
    return Status::q0;
}

Status trans_to_q1() {
    if (count > 10) {
        return Status::end;
    } else if (output == 2) {
        return Status::q0;
    }

    return Status::q1;
}

Status trans_to_end() {
    return Status::end;
}

void q0() {
    count++;
    output = 1;
}

void q1() {
    count++;
    output = 2;
}

void end() {
}

int main() {
    FangFSM<Status> fsm(Status::q0, Status::end);
    fsm.RegisterStateFct(Status::q0, q0);
    fsm.RegisterStateFct(Status::q1, q1);
    fsm.RegisterStateFct(Status::end, end);

    fsm.RegisterTransitionFct(Status::q0, trans_to_q0);
    fsm.RegisterTransitionFct(Status::q1, trans_to_q1);
    fsm.RegisterTransitionFct(Status::end, trans_to_end);

    for (int i = 0; i < 20; i++) {
        fsm.Run();
        fsm.CurrentStateLog();
    }

    return 0;
}
