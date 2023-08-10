#include "../fsm.hpp"

enum class Status {
    q0,
    q1,
    end
};

int output;
int count = 0;

Status trans_from_q0() {
    if (count > 10) {
        return Status::end;
    } else if (output == 1) {
        return Status::q1;
    }
    return Status::q0;
}

Status trans_from_q1() {
    if (count > 10) {
        return Status::end;
    } else if (output == 2) {
        return Status::q0;
    }

    return Status::q1;
}

Status trans_from_end() {
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
    FangFSMLibrary::FangFSM<Status> fsm(Status::q0, Status::end);

    fsm.RegisterStateFct(Status::q0, q0);
    fsm.RegisterStateFct(Status::q1, q1);
    fsm.RegisterStateFct(Status::end, end);

    fsm.RegisterTransitionFct(Status::q0, trans_from_q0);
    fsm.RegisterTransitionFct(Status::q1, trans_from_q1);
    fsm.RegisterTransitionFct(Status::end, trans_from_end);

    for (int i = 0; i < 20; i++) {
        fsm.Run();
        std::printf("current state: %d\n", static_cast<uint8_t>(fsm.GetCurrentState()));
    }

    return 0;
}
