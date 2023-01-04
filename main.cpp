#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

string str = "In publishing and graphic design, Lorem ipsum is a placeholder text commonly used to demonstrate the visual form of a document or a typeface without relying on meaningful content. Lorem ipsum may be used as a placeholder before final copy is available.";

template<typename K, typename V>
void print_map(std::unordered_map<K, V> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

typedef struct node{
    char c;
    int freq;
    struct node *l, *r;
    struct node *next;
}NODE;

struct Comp{
    bool operator()(const NODE* a, NODE* b){
        return a->freq > b->freq;
    }
};

NODE *head;

priority_queue<NODE*, vector<NODE*>, Comp> sort(priority_queue<NODE*, vector<NODE*>, Comp> pq){
    NODE *p = head;
    while (p!=NULL)
    {
        NODE *q = new NODE;
        q->c = p->c;
        q->freq = p->freq;
        pq.push(q);
        p = p->next;
    }
    return pq;
}

NODE* build_tree(priority_queue<NODE*, vector<NODE*>, Comp> pq){
    while (pq.size() != 1)
    {
        NODE *left = pq.top();
        pq.pop();
        NODE *right = pq.top();
        pq.pop();
        NODE *node = new NODE;
        node->l = left;
        node->r = right;
        node->freq = left->freq + right->freq;

        pq.push(node);
    }
    return pq.top();
}



void encode(NODE* root, string str, unordered_map<char, string> &code){
    if(root == NULL)
        return;

    if(root->c != ' '){
        code[root->c] = str;
    }
    encode(root->l, str + "0", code);
    encode(root->r, str + "1", code);
}

void decode(NODE *root, string str){
    if(root == NULL)
        return;

    if(root->c != ' '){
        str.push_back(root->c);
    }
    decode(root->l, str);
    decode(root->r, str);
    cout << str;
}



void init_list(){
    head = NULL;
}

void add(char c, int freq){
    NODE *p, *q, *t;
    p = q = head;

    t = new NODE;
    t->c = c;
    t->freq = freq;

    while(p != NULL){
        q = p;
        p = p->next;
    }

    if(head == NULL){
        head = t;
    }else{
        q->next = t;
    }
    t->next = p;
}

NODE* locate(char c){
    NODE *p = head;
    while(p != NULL){
        if(p->c == c)
            return p;
        p = p->next;
    }
    return NULL;
}

void build_hash_table(){
    for (size_t i = 0; i < str.length(); i++)
    {   
        NODE *p = locate(str.at(i));
        if(p == NULL){
            add(str.at(i), 1);
        }else{
            p->freq++;
        }
            
    }
}

void showq(priority_queue<NODE*, vector<NODE*>, Comp> pq){
    priority_queue<NODE*, vector<NODE*>, Comp> g = pq;
    while (!g.empty())
    {
       cout << g.top()->c << " : " << g.top()->freq << endl;
       g.pop();
    }
    
}


void display(NODE *h){
    NODE *p = h;
    while(p != NULL){
        cout << p->c << " : " << p->freq << endl;
        p = p->r;
    }
}

int main(){
   priority_queue<NODE*, vector<NODE*>, Comp> pq;
   init_list();
   build_hash_table();

   pq = sort(pq);
//    showq(pq);
   NODE *f = build_tree(pq);
    
    string str;
    unordered_map<char, string> umap;

    encode(f, str, umap);
    print_map(umap);

    // display(f);
};





