#include "segtree.h"

int main() {
    
    vector<int>a={5,3,8,9,1,4}, b{1,1,1,1,1,1}, c{1,2};
    Segment_tree<int>
    myTree(a, INT_MAX, [](const int &a, const int &b) { return a < b ? a : b ; } ),
    myTree1(a, INT_MAX, [](const int &a, const int &b) {return a < b ? a : b ; } ),
    myTree2(b, INT_MAX, [](const int &a, const int &b) {return a < b ? a : b ; } );
    
    for(int i=0; i<myTree.size(); ++i)
        cout << myTree1[i] << " ";
    cout << endl;
    
    for(int i=0; i<myTree1.size(); ++i)
        cout << myTree2[i] << " ";
    cout << endl;
    
    // new segment tree initialised with expression
    Segment_tree<int> neww(myTree1 + myTree2 - myTree2 + myTree2);
    for(int i=0; i<neww.size(); ++i)
        cout << neww[i] << " ";
    
    cout << endl;
    
    //    myTree.print_tree();
    cout << myTree.range_query(0, 5) << endl;
    cout << myTree.range_query(1, 5) << endl;
    cout << myTree.range_query(1, 4) << endl;
    cout << myTree.range_query(3, 3) << endl;
    cout << myTree.range_query(2, 5) << endl;
    cout << myTree.range_query(1, 3) << endl;
    cout << myTree.range_query(5, 5) << endl;
    cout << myTree.range_query(4, 5) << endl;
    cout << myTree.range_query(3, 4) << endl;
    
    myTree.update(5, 15);
    //    myTree.print_tree();
    cout << myTree.range_query(0, 5) << endl;
    cout << myTree.range_query(1, 5) << endl;
    cout << myTree.range_query(1, 4) << endl;
    cout << myTree.range_query(3, 3) << endl;
    cout << myTree.range_query(2, 5) << endl;
    cout << myTree.range_query(1, 3) << endl;
    cout << myTree.range_query(5, 5) << endl;
    cout << myTree.range_query(4, 5) << endl;
    cout << myTree.range_query(3, 4) << endl;
    
    return 0;
}
