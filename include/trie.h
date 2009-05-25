//\textit{trie.h}
//\begin{verbatim}
#ifndef _TRIE_H_
#define _TRIE_H_

#include <map>
#include <string>
#include <iostream>

struct Trie
{
  static const int alphabet_size = 256;
  
  struct node
  {
    bool is_terminal;
    node* childs[alphabet_size];
    node* parent;
    node() :
        is_terminal(false),
        parent(0)
      { 
        memset(childs,0,sizeof(childs));
      }
  };
  
  std::map< node*, node* > p;
  std::map< node*, node* > m;
  
  node* root;
  
  Trie() :
      root( new node() ) 
    { };
    
  static void destroy(const node* root);
  ~Trie();
    
  node* operator[](const std::string& a);
  std::string operator[](const node* what);
    
  Trie& operator+=(const std::string& a);
  Trie& operator-=(const std::string& a); // not actually deleting, just searching and switching is_terminall off
  
  // maybe merge them?
  void calc_p_function();
  void calc_max_terminal_prefixes();
  
  static void output( std::ostream& out, const node* root,int level);
};

#endif // _TRIE_H_
//\end{verbatim}
