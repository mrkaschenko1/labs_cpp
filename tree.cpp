#include <iostream>
#include <fstream>
using namespace std;

struct  TreeNode
{
    int data; 
    TreeNode *left; // указатель на левого потомка
    TreeNode *right; // указатель на правого потомка
    TreeNode *parent; // указатель на родителя
    int height = 1;
};

void makeTree(TreeNode** tree);
TreeNode* insertNode(TreeNode** tree, int k);
void deleteTree(TreeNode** tree);
TreeNode* searchNode(TreeNode** tree, int k);
void showTree(TreeNode** tree, int l);
TreeNode* min(TreeNode** tree);
TreeNode* balance(TreeNode* tree);


TreeNode* insertNode(TreeNode** tree, int key){
	if(*tree==NULL){
		*tree = new TreeNode;
		(*tree)->data = key;
		(*tree)->right = NULL;
		(*tree)->left = NULL;
		(*tree)->parent = NULL;
	}
	
	else if(key<(*tree)->data){
		if((*tree)->left != NULL){
		(*tree)->left = insertNode(&((*tree)->left), key);
			//balance(*tree);
			}
		else{
			(*tree)->left = new TreeNode;
			(*tree)->left->left = NULL;
			(*tree)->left->right = NULL;
			(*tree)->left->data = key;
			(*tree)->left->parent = *tree;
			}
		}
	else if(key>(*tree)->data){
		if((*tree)->right != NULL){
			(*tree)->right = insertNode(&((*tree)->right), key);
			//balance(*tree);
			}
		else{
			(*tree)->right = new TreeNode;
			(*tree)->right->left = NULL;
			(*tree)->right->right = NULL;
			(*tree)->right->data = key;
			(*tree)->right->parent = *tree;
			}
		}
	return balance(*tree);	
	}
	
void makeTree(TreeNode** tree){
	ifstream fin("input.txt");
	int a;
	while(!fin.eof()){
		fin >> a;
		insertNode(tree, a);
	}
	}
void showTree(TreeNode **tree,int l)
{
  int i;

  if (*tree!=NULL)
  {
	showTree(&((*tree)->right),l+1); 
    for (i=1; i<=l; i++) cout<<"  "; 
    cout<<(*tree)->data<<endl; 
    showTree(&((*tree)->left),l+1); 
  }
}
TreeNode* searchNode(TreeNode** tree, int k){
   if (*tree == NULL or k == (*tree)->data){
      return *tree;
   }
   if (k < (*tree)->data){
      return searchNode(&((*tree)->left), k);
   }
   else{
      return searchNode(&((*tree)->right), k);
	}
	}
TreeNode* GetMin(TreeNode* p) // поиск узла с минимальным ключом в дереве p 
{
	if(p->left){
		return GetMin(p->left);
		}
	else{
		return p;
		}
}
void deleteTree(TreeNode **tree) {
    if (*tree != NULL)
    {
        deleteTree(&((*tree)->left));
        deleteTree(&((*tree)->right)); 
        //cout << "deleting" << (*tree)->data << "  " << (*tree)->parent->data << endl;
        delete *tree; 
        *tree = NULL;
    }
}


void showSearchResult(TreeNode** tree,int k){
	cout << " show search node " << k << endl;
	if(searchNode(tree, k))
	{
		cout<<"We have found your element"<<endl;
	}
	else{
		cout<<"There is no your element in the tree"<<endl;
		}
	}

	
TreeNode* min(TreeNode** tree){
	if ((*tree)->left == NULL){
		return *tree;
	}
	return min(&((*tree)->left));
}

int height(TreeNode* p){
	return p?p->height:0;
}

int checkDif(TreeNode* p)
{
	return height(p->right)-height(p->left);
}

void fixHeight(TreeNode* p)
{
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

TreeNode* rotLeft(TreeNode* tree){
	if(tree == NULL){
		return tree;
		}
	TreeNode* newRoot = tree->right;
	tree->right = newRoot->left;
	newRoot->left = tree;
	fixHeight(tree);
	fixHeight(newRoot);
	return newRoot;
	}
TreeNode* rotRight(TreeNode* tree){
	if(tree == NULL){
		return tree;
		}
	TreeNode* newRoot = tree->left;
	tree->left = newRoot->right;
	newRoot->right = tree;
	fixHeight(tree);
	fixHeight(newRoot);
	return newRoot;
	}
TreeNode* balance(TreeNode* tree){
	fixHeight(tree);
	if(checkDif(tree)==2 )
	{
		if(checkDif(tree->right) < 0 )
			tree->right = rotRight(tree->right);
		return rotLeft(tree);
	}
	if( checkDif(tree)==-2 )
	{
		if(checkDif(tree->left) > 0)
			tree->left = rotLeft(tree->left);
		return rotRight(tree);
	}
	return tree;
	}
void showMenu(){
	cout << "---------------------------------";
	cout << '\n' << "Choose something" << endl;
	cout << "1.Show tree" << endl;
	cout << "2.Insert node" << endl;
	cout << "3.Delete tree" << endl;
	cout << "4.Find node" << endl;
	cout << "0.Exit" << endl;
	cout << "---------------------------------" << endl;
	}

int main()
{	
	TreeNode *tree = NULL;
	makeTree(&tree);
	makeTree(&tree);
	int choice;
	char binChoice;
	int key;
	while(choice!=0){
	showMenu();
	cout << "Enter number: ";
	cin >> choice;
	cout << '\n';
	switch(choice){
		case 0: 
			return 0;
		case 1:
			showTree(&tree, 15);
			break;
		case 2:
			cout << "Enter key: ";
			cin >> key;
			insertNode(&tree, key);
			break;
		case 3:
			cout << "Are you sure? (type 'y' or 'n')"  << '\n';
			cin >> binChoice;
			if(binChoice == 'y'){
				deleteTree(&tree);
			}
			break;
		case 4:
			cout << "Enter key: ";
			cin >> key;
			showSearchResult(&tree, key);
			break;
		default:
			break;
		}
	}
	return 0;
}

