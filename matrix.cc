#include <vector>
#include <iostream>
#include <stdexcept>
#include <utility>

#define MIN(a,b) ((a) < (b)) ? (a) : (b)
#define SQUARE(m) ((m).nrow() == (m).ncol())

using namespace std;

template <typename Iter>
void show(Iter begin, Iter end)
{
	cout << *begin;
	for (++begin; begin != end; begin++)
		cout << ' ' << *begin;
	cout << '\n';
}

template <typename M>
void show_matrix(M && m)
{
	for (int i = 0; i < m.nrow(); i++) {
		cout << m(i,0);
		for (int j = 1; j < m.ncol(); j++) {
			cout << ' ' << m(i,j);
		}
		cout << '\n';
	}
}

template <template <typename> class M, typename T>
class MatrixAccess {
public:
	T& operator()(int i, int j) { return static_cast<M<T> const&>(*this)(i,j); }

	int nrow() const { return static_cast<M<T> const &>(*this).nrow(); }
	int ncol() const { return static_cast<M<T> const &>(*this).ncol(); }
};

template <typename T>
class Matrix : public MatrixAccess<Matrix, T> {
	vector<vector<T> > m;
public:
	void resize(int i, int j) {
		m.resize(i);
		for (auto & v : m)
			v.resize(j);
	}

	T& operator()(int i, int j) {
		return m[i][j];
	}

	int nrow() const { return m.size(); }
	int ncol() const { return m.empty() ? 0 : m[0].size(); }

};

template <typename T>
class MatrixView : public MatrixAccess<Matrix, T> {
	Matrix<T> & m;
	int row, col;
	int nrows, ncols;
public:
	MatrixView(Matrix<T> &m,  int r, int c, int nr, int nc) : m(m), row(r), col(c), nrows(nr), ncols(nc) {}

	T& operator()(int i, int j) {
		return m(row + i, col + j);
	}

	int nrow() const { return nrows; }
	int ncol() const { return ncols; }

};

template <typename T>
MatrixView<T> make_view(Matrix<T> & m, int r, int c, int nr, int nc)
{
	return MatrixView<T>(m,r,c,nr,nc);
}

template <typename T>
void rotate_2x2(Matrix<T> & frame)
{
	swap(frame(0,1), frame(1,1));
	swap(frame(0,0), frame(0,1));
	swap(frame(0,0), frame(1,0));
}

template <typename M>
void rotate_perimeter(M && m)
{
	Matrix<int> frame;

	frame.resize(2,2);
	int nrow = m.nrow();
	int ncol = m.ncol();
	for (int i = 0; i < ncol - 1; i++) {
		frame(0,0) = m(0, i);
		frame(0,1) = m(i, ncol - 1);
		frame(1,1) = m(nrow - 1, ncol - i - 1);
		frame(1,0) = m(nrow - i - 1, 0);
		rotate_2x2(frame);
		m(0,i) = frame(0,0);
		m(i, ncol - 1) = frame(0,1);
		m(nrow - 1, ncol - i - 1) = frame(1,1);
		m(nrow - i - 1, 0) = frame(1,0);
	}
}

// rotate a matrix 90 degrees clockwise
template <typename T>
void rotate(Matrix<T> & m)
{
	if (!SQUARE(m))
		throw std::runtime_error("rotate: matrix must be square");
	int dim = m.nrow();
	for (int i = 0; i < dim / 2; i++) {
		int new_dim = dim - (i * 2);
		auto view = make_view(m, i, i, new_dim, new_dim);
		rotate_perimeter(view);
	}
}

int main()
{
	Matrix<int> m;
	int dim = 5;

	m.resize(dim,dim);
	for (int i = 0; i < dim * dim; i++) {
		int r = i / dim;
		int c = i % dim;
		m(r,c) = i + 1;
	}

	show_matrix(m);
	cout << '\n';
	rotate(m);
	show_matrix(m);
}
