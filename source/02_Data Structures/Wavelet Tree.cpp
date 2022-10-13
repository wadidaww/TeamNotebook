class wavelet_tree {
public:
	int low, high;
	wavelet_tree* l, *r;
	vector<int> freq;
	wavelet_tree(int* from, int* to, int x, int y) {
		low = x, high = y;
		if(from >= to) return;
		if(high == low) {
			freq.reserve(to - from + 1);
			freq.push_back(0);
			for (auto it = from; it != to; it++)
				freq.push_back(freq.back() + 1);
			return;
		}
		int mid = (low + high) / 2;
		auto lessThanMid = [mid](int x) {
			return x <= mid;
		};
		freq.reserve(to - from + 1);
		freq.push_back(0);
		for (auto it = from; it != to; it++)
			freq.push_back(freq.back() + lessThanMid(*it));	
		auto pivot = stable_partition(from, to, lessThanMid);
		l = new wavelet_tree(from, pivot, low, mid);
		r = new wavelet_tree(pivot, to, mid + 1, high);
	}
	int kOrLess(int l, int r, int k) {
		if (l > r or k < low) return 0;
		if (high <= k) return r - l + 1;
		int LtCount = freq[l - 1];
		int RtCount = freq[r];
		return (this->l->kOrLess(LtCount + 1, RtCount, k) +
			this->r->kOrLess(l - LtCount, r - RtCount, k));
	}
};