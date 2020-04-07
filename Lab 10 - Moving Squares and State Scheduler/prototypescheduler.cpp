// Runs a system loop and handles processes with random chance
// CS44001 Assignment 10 - Adapter Moving Square
// Connor DeGeorge
// 4/6/20

#include <queue>
#include <vector>
#include <ctime>
#include "statetransition.hpp"

using std::queue; using std::vector;

int main() {
	queue<Process*> processQueue;
	vector<Process*> waitingList;
	Process prototype;
	srand(time(nullptr));

	// Create 4 processes and admit them into the system
	int index = 0;
	while (index < 4) {
		Process* process = prototype.clone();

		cout << process->report() << endl;
		process->admitted();
		processQueue.push(process);

		++index;
	}

	// Running the system loop
	while (!processQueue.empty() || !waitingList.empty()) {
		// Handle queued processes
		if (!processQueue.empty()) {
			Process* process = processQueue.front();

			process->schedulerDispatch();
			cout << process->report() << endl;

			int r = rand() % 3;
			switch (r) {
			case 0:
				process->exit();
				cout << process->report() << endl;
				processQueue.pop();
				break;
			case 1:
				process->interrupt();
				cout << process->report() << endl;
				processQueue.push(process);
				processQueue.pop();
				break;
			case 2:
				process->eventWait();
				cout << process->report() << endl;
				waitingList.push_back(process);
				processQueue.pop();
				break;
			default:
				break;
			}
		}

		// Handle waiting processes
		int r = rand() % 2;
		if (!waitingList.empty() && r == 0) {
			r = rand() % waitingList.size();
			Process* process = waitingList[r];

			process->eventCompletion();
			cout << process->report() << endl;
			processQueue.push(process);
			waitingList.erase(waitingList.begin() + r);
		}
	}

	return 0;
}