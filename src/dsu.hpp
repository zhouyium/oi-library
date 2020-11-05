#ifndef __OI_LIBRARY_DSU_H_38D3D9X74JDI8832DJUW__
#define __OI_LIBRARY_DSU_H_38D3D9X74JDI8832DJUW__

#include <vector>

namespace oi_library {

//Disjoint Set Union
template <class T>
struct DSU {
private:
    /*
    当_dsu[x]<0的时候，说明x的父节点是自己。同时 |_dsu[x]| 表示集合内元素数量
    当_dsu[x]>0的时候，表示父节点
    */
    std::vector<T> _dsu;//并查集
    T _n;//数据容量

public:
    DSU(T n) : _n(n),  _dsu(n, -1) {}
  
    //查找x的父亲
    T find_root(T x) {
        if (x<0 || x>=_n || _dsu[x]<0) {
            return x;
        }
        return _dsu[x] = find_root(_dsu[x]);
    }
 
    //建立关系
    bool union_set(T x, T y) {
        if (x<0 || x>=_n || y<0 || y>=_n) {
            return false;
        }
        x = find_root(x);
        y = find_root(y);
        if (x==y) {
            //两个已经在同一个集合
            return false;
        }
        if (_dsu[x]>_dsu[y]) {
            //保证不会出现单边增长
            swap(x, y);
        }
        _dsu[x] += _dsu[y];
        _dsu[y] = x;
        return true;
    }
 
    //查找x和y是否在同一个父亲
    bool relation(T x, T y) {
        if (x<0 || x>=_n || y<0 || y>=_n) {
            return false;
        }
        return find_root(x) == find_root(y);
    }

    //数据 x 所在集合大小
    T size(T x) {
        if (x<0 || x>=_n) {
            return 0;
        }
        return -_dsu[find_root(x)];
    }

    //获取 DSU 的集合
    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(std::remove_if(result.begin(), result.end(),
                    [&](const std::vector<int>& v) { return v.empty(); }),
                    result.end());
        return result;
    }
}; //end of struct

} //end of namespace

#endif // end of head file