#include <span>
#include <future>

template<class T>
void quickSort(std::span<T> cont, int deep = 0) {
	int i = 0, j = cont.size() - 1;
	T mid = cont[j / 2];
	while (i <= j) {
		while (cont[i] < mid)
			i++;
		while (cont[j] > mid)
			j--;
		if (i <= j)
			std::swap(cont[i++], cont[j--]);
	}
	std::future<void> thread;
	if (j > 0) {
		if (deep < 9) { //9
			thread = std::async(quickSort<T>, cont.subspan(0, j + 1), deep + 1);
		}
		else
			quickSort(cont.subspan(0, j + 1), deep + 1);

	}
	if (i < cont.size() - 1)
		quickSort(cont.subspan(i, cont.size() - i), deep + 1);
}

template<class... Args>
inline void quickSort(Args&&... args) {
	quickSort(std::span(args...));
}

template<class T>
void mergeSort(std::span<T> v, int deep = 0) {
    int n = v.size();
    if (n == 1)
        return;
    if (n == 2) {
        if (v[0] > v[1])
            std::swap(v[0], v[1]);
        return;
    }

    int mid = n / 2;

	std::future<void> thread;
    std::vector<T> L(v.begin(), v.begin() + mid);
    const int thCoef = 7;
    if (deep < thCoef)
        thread = async(mergeSort<T>, std::span(L), deep + 1);
    else
        mergeSort(std::span(L), deep + 1);
    std::vector<T> R(v.begin() + mid, v.end());
    mergeSort(std::span(R), deep + 1);
    if (deep < thCoef)
        thread.wait();

    int l_n = L.size();
    int r_n = R.size();
    int i = 0, j = 0, k = 0;
    while (i < l_n && j < r_n)
        if (L[i] < R[j])
            v[k++] = L[i++];
        else
            v[k++] = R[j++];

    while (i < l_n)
        v[k++] = L[i++];

    while (j < r_n)
        v[k++] = R[j++];
}

template<class... Args>
inline void mergeSort(Args&&... args) {
    mergeSort(std::span(args...));
}