#include<bits/stdc++.h>
using namespace std ;

class Node
{
	public:
	int cnt ;
	char c ;
	Node* left ;
	Node* right ;
	Node(int cnt ,char c)
	{
		this->cnt = cnt ;
		this->c = c ;	
		left = right = NULL ;
	}
	
	Node(int cnt , Node* a ,Node* b )
	{
		c = '0';
		this->cnt = cnt ;	
		this->left = a;
		this->right = b;
	}	
};

class HuffmanTree
{
	public:
	Node* root;	
};

class compare
{
	public:
	bool operator()(Node *a ,Node *b)
	{
		return (a->cnt < b->cnt);
	}
};
class HuffmanEncoding
{
	public:
	string data;
	map<char ,int>charfre;
	priority_queue<Node* ,vector<Node*> ,compare>pq;
	Node* root ;
	map<char ,string>mapcode ;
	
	HuffmanEncoding(string s)
	{
		data = s ;
		for(char c : data){
			charfre[c]++;
		}
		
		for(auto it : charfre)
		{
			Node* newnode;
			newnode = new Node(it.second ,it.first);
			pq.push(newnode);
		}
		
	}
	
	void maketree()
	{
		while(pq.size() > 1)
		{
			Node* a = pq.top() ; pq.pop() ;
			Node* b = pq.top() ; pq.pop() ;
			
			Node* c ;
			int cnt = a->cnt + b->cnt ;
			c = new Node(cnt ,a ,b);
			pq.push(c);
			
		}	
		root = pq.top();
	}
	
	void preorder(Node* root , string s)
	{
		if(root == NULL){
			return ;
		}
		if(root->left == NULL && root->right == NULL){
			mapcode[root->c] = s;
		}
		
		preorder(root->left, s+"0");
		preorder(root->right, s+"1");
	}
	
	void Encode()
	{
		string s;
		preorder(root ,s);
	}
	
	void showcode()
	{
		for(auto it : mapcode)
		{
			cout<<it.first<<"->"<<it.second<<endl;
		}
	}
	
	void performEncoding()
	{
		maketree();
		Encode();
		showcode();
	}
};

int main()
{
	string s = "hello" ;
	HuffmanEncoding obj(s) ;
	obj.performEncoding() ;
}
