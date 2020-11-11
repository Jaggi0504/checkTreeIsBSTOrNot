#include<bits/stdc++.h>
using namespace std;

template<typename T>
class BinaryTreeNode {
	public:
		T data;
		BinaryTreeNode *left;
		BinaryTreeNode *right;
		BinaryTreeNode(T data) {
			this->data = data;
			this->left = NULL;
			this->right = NULL;
		}
};

class checkIsBST {
	public:
	int minimum, maximum;
	bool isBST;
};

BinaryTreeNode<int> *takeInput() {
	int rootData;
	cout<<"Enter the root data:";
	cin>>rootData;
	if(rootData == -1) {
		return NULL;
	}
	BinaryTreeNode<int> *root = new BinaryTreeNode<int>(rootData);
	queue<BinaryTreeNode<int>*> pendingNodes;
	pendingNodes.push(root);
	while(pendingNodes.size() != 0) {
		BinaryTreeNode<int> *front = pendingNodes.front();
		pendingNodes.pop();
		int leftChildData;
		cout<<"Enter the left child of "<<front->data<<":";
		cin>>leftChildData;
		if(leftChildData != -1) {
			BinaryTreeNode<int> *child = new BinaryTreeNode<int>(leftChildData);
			front->left = child;
			pendingNodes.push(child);
		}
		int rightChildData;
		cout<<"Enter the right child of "<<front->data<<":";
		cin>>rightChildData;
		if(rightChildData != -1) {
			BinaryTreeNode<int> *child = new BinaryTreeNode<int>(rightChildData);
			front->right = child;
			pendingNodes.push(child);
		}
	}
	return root;
}

void print(BinaryTreeNode<int> *root) {
	if(root == NULL) {
		return ;
	}
	queue<BinaryTreeNode<int>*> ans;
	ans.push(root);
	while(ans.size() != 0) {
		BinaryTreeNode<int> *front = ans.front();
		ans.pop();
		if(front != NULL) {
			cout<<front->data<<":";
		}
		if(front->left != NULL) {
			cout<<"L:"<<front->left->data<<", ";
			ans.push(front->left);
		} else if(front->left == NULL) {
			cout<<"L:-1, ";
		}
		if(front->right != NULL) {
			cout<<"R:"<<front->right->data;
			ans.push(front->right);
		} else if(front->right == NULL) {
			cout<<"R:-1";
		}
		cout<<endl;
	}
}

BinaryTreeNode<int> *construct(int *input, int si, int ei) {
	if(si > ei) {
		return NULL;
	}
	int mid = (si+ei)/2;
	BinaryTreeNode<int> *root = new BinaryTreeNode<int>(input[mid]);
	BinaryTreeNode<int> *leftAns = construct(input, si, mid-1);
	BinaryTreeNode<int> *rightAns = construct(input, mid+1, ei);
	root->left = leftAns;
	root->right = rightAns;
	return root;
}

BinaryTreeNode<int> *constructTree(int *input, int n) {
	sort(input, input+n);
	BinaryTreeNode<int> *ans = construct(input, 0, n-1);
	return ans;
}

checkIsBST isBSTReturn(BinaryTreeNode<int> *root) {
	if(root == NULL) {
		checkIsBST object;
		object.minimum = INT_MAX;
		object.maximum = INT_MIN;
		object.isBST = true;
		return object;
	}
	checkIsBST leftAns = isBSTReturn(root->left);
	checkIsBST rightAns = isBSTReturn(root->right);
	int minm = min(root->data, min(leftAns.minimum, rightAns.minimum));
	int maxm = max(root->data, max(leftAns.maximum, rightAns.maximum));
	bool isBSTFinal = ((root->data > leftAns.maximum) && (root->data <= rightAns.minimum) && (leftAns.isBST && rightAns.isBST));
	checkIsBST obj;
	obj.maximum = maxm;
	obj.minimum = minm;
	obj.isBST = isBSTFinal;
	return obj;
}

int main() {
	BinaryTreeNode<int> *root = takeInput();
	cout<<endl;
	print(root);
	cout<<endl;
//	int n;
//	cin>>n;
//	int *input = new int[n];
//	for(int i=0;i<n;i++) {
//		cin>>input[i];
//	}
//	BinaryTreeNode<int> *ans = constructTree(input, n);
//	print(ans);
	checkIsBST ans2 = isBSTReturn(root);
	if(ans2.isBST) {
		cout<<"Yes";
	} else {
		cout<<"No";
	}
	return 0;
}
