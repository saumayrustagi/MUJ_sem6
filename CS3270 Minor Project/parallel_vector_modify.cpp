#include <iostream>
#include <vector>
#include <thread>

#define ELEMNUM 1000000

using namespace std;
using u64 = uint_fast64_t;

typedef struct
{
	char c;
	int split;
	vector<char>::iterator it;
	// chrono::microseconds exec_time;
} argstruct;

void *putval(void *arg);
void test_program(vector<char> &v, u64 a, int b);

int main(int argc, char *argv[])
{
	unsigned int num_threads;
	if (argc != 2 || (num_threads = atoi(argv[1])) < 1)
		return 1;

	vector<char> v(ELEMNUM, 'z');

	pthread_t threads[num_threads];
	argstruct thread_args[num_threads];

	const u64 split = ELEMNUM / num_threads;

	for (unsigned int i = 0; i < num_threads; ++i)
	{
		thread_args[i].c = (char)('a' + i);
		thread_args[i].split = split;
		thread_args[i].it = v.begin() + (i * split);

		if (pthread_create(&threads[i], NULL, putval, (void *)&thread_args[i]) != 0)
		{
			cerr << "Failed to create thread: " << i << '\n';
			return 1;
		}
	}

	// chrono::microseconds n;
	for (unsigned int i = 0; i < num_threads; ++i)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			cerr << "Failed to join thread: " << i << '\n';
			return 1;
		}
		// n += thread_args[i].exec_time;
	}

	// cout << "Program took " << n.count() << " microseconds\n";

	// test_program(v, split, num_threads);

	return 0;
}

void *putval(void *arg)
{
	argstruct *args = (argstruct *)arg;

	// auto start = chrono::high_resolution_clock::now();

	while (args->split--)
	{
		*(args->it) = args->c;
		++args->it;
	}

	// auto end = chrono::high_resolution_clock::now();
	// args->exec_time = chrono::duration_cast<chrono::microseconds>(end - start);

	return NULL;
}

void test_program(vector<char> &v, u64 split, int num_threads)
{
	for (int i = 0; i < num_threads; ++i)
	{
		u64 n = 0;
		for (u64 j = split * i; j < split * (i + 1); ++j)
		{
			n += v[j];
		}
		const u64 comp = ('a' + i) * split;
		cout << n << " //" << comp << ' ' << ((comp == n) ? "equal" : "not equal") << endl;
	}
}
