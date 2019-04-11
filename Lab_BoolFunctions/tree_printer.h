#include <vector>
using namespace std;
typedef struct TreeOfResults
{
	struct TreeOfResults *l;
	struct TreeOfResults *r;
	bool res;
} tree_t;

void PrintTree(tree_t* tree);

//void PrintTree(vector <pair<bool, bool>> &tree, int i);
