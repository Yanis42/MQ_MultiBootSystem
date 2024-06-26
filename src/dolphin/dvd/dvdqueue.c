#include "dolphin/dvd.h"
#include "dolphin/types.h"

DVDQueue WaitingQueue[4];

void __DVDClearWaitingQueue() {
    int i;

    for (i = 0; i < 4; i++) {
        DVDQueue* ptr = &WaitingQueue[i];

        ptr->mHead = ptr;
        ptr->mTail = ptr;
    }
}

BOOL __DVDPushWaitingQueue(int idx, DVDQueue* newTail) {
    BOOL intrEnabled = OSDisableInterrupts();

    DVDQueue* waitingQueue = &WaitingQueue[idx];

    waitingQueue->mTail->mHead = newTail;
    newTail->mTail = waitingQueue->mTail;
    newTail->mHead = waitingQueue;
    waitingQueue->mTail = newTail;

    OSRestoreInterrupts(intrEnabled);
    return true;
}

DVDQueue* __DVDPopWaitingQueue() {
    BOOL intrEnabled = OSDisableInterrupts();
    int i;

    for (i = 0; i < 4; i++) {
        if (WaitingQueue[i].mHead != &WaitingQueue[i]) {
            DVDQueue* tempQueue;
            DVDQueue* outQueue;

            OSRestoreInterrupts(intrEnabled);

            intrEnabled = OSDisableInterrupts();
            tempQueue = &WaitingQueue[i];
            outQueue = tempQueue->mHead;
            tempQueue->mHead = outQueue->mHead;
            outQueue->mHead->mTail = tempQueue;
            OSRestoreInterrupts(intrEnabled);

            outQueue->mHead = NULL;
            outQueue->mTail = NULL;
            return outQueue;
        }
    }
    OSRestoreInterrupts(intrEnabled);
    return NULL;
}

BOOL __DVDCheckWaitingQueue() {
    BOOL intrEnabled = OSDisableInterrupts();
    int i;

    for (i = 0; i < 4; i++) {
        if (WaitingQueue[i].mHead != &WaitingQueue[i]) {
            OSRestoreInterrupts(intrEnabled);
            return true;
        }
    }
    OSRestoreInterrupts(intrEnabled);
    return false;
}

BOOL __DVDDequeueWaitingQueue(DVDQueue* queue) {
    BOOL intrEnabled = OSDisableInterrupts();
    DVDQueue* tail = queue->mTail;
    DVDQueue* head = queue->mHead;

    if (tail == NULL || head == NULL) {
        OSRestoreInterrupts(intrEnabled);
        return false;
    }
    tail->mHead = head;
    head->mTail = tail;
    OSRestoreInterrupts(intrEnabled);
    return true;
}
