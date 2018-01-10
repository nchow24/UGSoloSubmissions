//nchow24	CS2210A		Nov 18, 2016
//Class OrderedDictionary used to create a binary search tree with nodes

public class OrderedDictionary implements OrderedDictionaryADT {
	private Node<Record> root = new Node<Record>();										//tree's root
	
	//finds the record with key k
	public Record find(Key k){
		//return null if root is empty
		if (root.getElement() == null){
			return null;
		} else {
			Node<Record> x = root;
			while (x.getElement() != null){
				int value = x.getElement().getKey().compareTo(k);
				if (value == 0){
					//key has been found
					return x.getElement();
				} else {
					//go right if k is greater than current key, otherwise go left
					if (value < 0){
						x = x.getRight();
					} else {
						x = x.getLeft();
					}
				}
			}
			//leaf node has been reached, k not in the tree
			return null;
		}
	}
	
	//inserts node into tree if Record's key doesn't already exist
	public void insert(Record r) throws DictionaryException{
		if (find(r.getKey()) != null){
			throw new DictionaryException("insertion", "already exists");
		} else {
			Node<Record> node = new Node<Record>(r);
			Node<Record> leaf1 = new Node<Record>();
			Node<Record> leaf2 = new Node<Record>();
			
			//if root is empty, make node the root
			if (root.getElement() == null){
				root = node;
				root.setLeft(leaf1);
				root.setRight(leaf2);
				leaf1.setParent(root);
				leaf2.setParent(root);
			} else {
				//find appropriate leaf where node should be, make leaf the new node and set new children
				//leaves for the new node
				Node<Record> x = findNode(r.getKey());
				x.setElement(r);
				x.setLeft(leaf1);
				x.setRight(leaf2);
				leaf1.setParent(x);
				leaf2.setParent(x);
			}
		}
	}
	
	//removes node with key k if it exists 
	public void remove(Key k) throws DictionaryException{
		if (find(k) == null){
			throw new DictionaryException("removal", "doesn't exist");
		} else {
			Node<Record> x = findNode(k);
			if ( (x.getLeft().getElement() == null) || (x.getRight().getElement() == null) ){
				//removal of a node at the end of tree
				Node<Record> y;											//the sibling of a leaf that is x's child
				Node<Record> xParent = x.getParent();
				if (x.getLeft().getElement() == null){
					y = x.getRight();
				} else {
					y = x.getLeft();
				}
				if (xParent == null){
					//removal of a root
					root = y;
				} else {
						//removal of an internal node (at least 1 child is leaf)
						if (xParent.getRight() == x){
							xParent.setRight(y);
						} else {
							xParent.setLeft(y);
						}
						y.setParent(xParent);
				}
			} else {
				//removal of an internal node (both children are internal)
				Node<Record> s = smallestNode(x.getRight());
				Node<Record> sParent = s.getParent();
				x.setElement(s.getElement());
				if (sParent.getLeft() == s){
					sParent.setLeft(s.getRight());
				} else {
					sParent.setRight(s.getRight());
				}
				s.getRight().setParent(sParent);
			}
		}
	}
	
	//returns the record whose key is the next largest key compared to k
	public Record successor(Key k){
		if (root.getElement() == null) {
			return null;
		} else {
			Node<Record> x = findNode(k);
			if (x.getRight().getElement() != null){
				//successor is in the subtree rooted by k
				return smallestNode(x.getRight()).getElement();
			} else {
				//successor is an ancestor of k
				Node<Record> xParent = x.getParent();
				if (x.getParent() == null){
					return null;
				}
				while ( (xParent != null) && (xParent.getRight() == x) ){
					x = xParent;
					xParent = x.getParent();
				}
				if (xParent == null){
					//no successor
					return null;
				} else {
					return xParent.getElement();
				}
			}
		}
	}
	
	//returns the record whose key is the next smallest compared to k 
	public Record predecessor(Key k){
		if (root.getElement() == null){
			return null;
		} else {
			Node<Record> x = findNode(k);
			if (x.getLeft().getElement() != null){
				//predecessor is in the subtree rooted by k
				return largestNode(x.getLeft()).getElement();
			} else {
				//predecessor is an ancestor of k
				Node<Record> xParent = x.getParent();
				while ((xParent!= null) && (xParent.getLeft() == x)){
					x = xParent;
					xParent = x.getParent();
				}
				if (xParent == null){
					// no predecessor
					return null;
				} else {
					return xParent.getElement();
				}
			}
		}
	}
	
	//returns the record of the node with the smallest key in tree rooted by root
	public Record smallest(){
		if (root.getElement() == null){
			return null;
		} else {
			//go to the leftmost leaf and return its parent
			Node<Record> x = root;
			while (x.getElement() != null){
				x = x.getLeft();
			}
			return x.getParent().getElement();
		}
		
	}
	
	//returns the record of the node with the largest key in tree rooted by root
	public Record largest(){
		if (root.getElement() == null){
			return null;
		} else {
			//go to the rightmost leaf and get its parent
			Node<Record> x = root;
			while (x.getElement() != null){
				x = x.getRight();
			}
			return x.getParent().getElement();
		}
	}
	
	//returns the node with record whose key is k
	//(same as find() except  it returns the node instead of the record)
	private Node<Record> findNode(Key k){
		if (root.getElement() == null){
			return null;
		} else {
			Node<Record> x = root;
			while ( (x.getElement() != null) && (k.compareTo(x.getElement().getKey()) != 0)){
				if ( k.compareTo(x.getElement().getKey()) == -1){
					x = x.getLeft();
				} else {
						x = x.getRight();
				}
			}
			return x;
		}
	}
	
	//returns the node whose record has the smallest key rooted at n
	//(same as smallest() except it returns a node
	//and can search for the smallest of a subtree)
	private Node<Record> smallestNode(Node<Record> n){
		if (n.getElement() == null){
			return null;
		} else {
			Node<Record> x = n;
			while (x.getElement() != null){
				x = x.getLeft();
			}
			return x.getParent();
		}
	}
	
	//returns the node whose record has the largest key rooted at n
	//(same as largest() except it returns a node
	//and can search for the largest of a subtree)
	private Node<Record> largestNode(Node<Record> n){
		if (n.getElement() == null){
			return null;
		} else {
			Node<Record> x = n;
			while (x.getElement() != null){
				x = x.getRight();
			}
			return x.getParent();
		}
	}
}
