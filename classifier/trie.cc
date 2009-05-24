#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

#include <trie.h>

using namespace std;

#define ALL(c) (c).begin(), (c).end()
#define DBG(x) cout << #x << " = " << x << endl;

void Trie::destroy(const node* root)
{
  if (root) {
    for (int c = 0;c < alphabet_size;++c)
      if (root->childs[c]) {
        destroy(root->childs[c]);
      }
    delete root;
  }
}

Trie::~Trie()
{
  destroy(root);
}

Trie::node* Trie::operator[](const string& a)
{
  node* current = root;
    
  for (int i = 0;i < a.size();++i) {
    if (current->childs[a[i]] == 0)
      return 0;
    current = current->childs[a[i]];
  }
  
  return current;
}

string Trie::operator[](const node* current)
{
  string res;
  while (current->parent != 0) {
    // awful loockup
    for (int c = 0;c < alphabet_size;++c)
      if (current->parent->childs[c] == current) {
        res += c;
        break;
      }
    current = current->parent;
  }
  
  reverse(ALL(res));
  
  return res;
}

Trie& Trie::operator+=(const string& a)
{
  node* current = root;
    
  for (int i = 0;i < a.size();++i) {
    if (current->childs[a[i]] == 0)
      current->childs[a[i]] = new node();
    current->childs[a[i]]->parent = current;
    current = current->childs[a[i]];
  }
  
  current->is_terminal = true;
  
  return *this;
}

Trie& Trie::operator-=(const string& a)
{
  node* what = (*this)[a];
  if (what)
    what->is_terminal = false;
  return *this;
}

void Trie::output(ostream& out,const node* root,int level )
{
  if (root) {
    for (int c = 0;c < alphabet_size;++c)
      if (root->childs[c]) {
        out << string(level,' ') << char(c) << (root->childs[c]->is_terminal ? "#" : "") <<  endl;
        output(out,root->childs[c],level + 1);
      }
  }
}

ostream& operator<<(ostream& out, const Trie& t)
{
  Trie::output(out,t.root,0);
  return out;
}

void Trie::calc_p_function()
{
  p.clear();
  queue< node* > q;
  
  p[root] = root;
  q.push(root);
  
  while (!q.empty()) {
    node* x = q.front();
    q.pop();
    
    if (x != root) {
      //cout << "x = " << (*this)[x] << " p[x] = " << (*this)[p[x]] << endl;
    }
    
    for (int c = 0;c < alphabet_size ;++c)
      if (x->childs[c]) {
        node* y = x->childs[c];
        p[y] = 0;
        while (p[x] != root) {
          node* px = p[x];
          if (px->childs[c]) {
            p[y] = px->childs[c];
            break;
          }
          x = px;
        }
        
        if (p[x] == root) {
          p[y] = ((root->childs[c] && y != root->childs[c]) ? root->childs[c] : root);
        }
        
        q.push(y);
      }
  }
}

void Trie::calc_max_terminal_prefixes()
{
  m.clear();
  queue< node* > q;
  
  m[root] = root;
  q.push(root);
  
  while (!q.empty()) {
    node* x = q.front();
    q.pop();
        
    node* tmp = x;
    
    assert(p[tmp] != 0);
    
    while (p[tmp] != root) {
      if (p[tmp]->is_terminal) {
        m[x] = p[tmp];
        break;
      }
      tmp = p[tmp];
    }
    
    if (p[tmp] == root)
      m[x] = root;
      
    if (x != root) {
      //cout << "x = " << (*this)[x] << " m[x] = " << (*this)[m[x]] << endl;
    }
    
    for (int c = 0;c < alphabet_size;++c)
      if (x->childs[c])
        q.push(x->childs[c]);
  }
}
