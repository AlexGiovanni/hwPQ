//Alexis Santiago  October 29, 2018 
#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
	// For the mandatory running times below:
	//
	// n is the number of elements in the MinPriorityQueue.
	//
	// Assume that the operations of unordered_map are O(1) time 
	// (they are average case, but not worst-case).

	public:
		// Creates an empty MinPriorityQueue
		MinPriorityQueue()
		{
			
		}

		void test_display()
		{
			cout << "Test_display " << endl;
			for (int i = 0; i < H.size(); i++)
				cout << i << ": " << H[i].first << ", " << H[i].second << endl;
		}

		// Returns the number of elements in the MinPriorityQueue.
		//
		// Must run in O(1) time.
		int size() { return H.size(); }	

		// Pushes a new value x with priority p
		// into the MinPriorityQueue.
		//
		// Must run in O(log(n)) time.		 
		void push(T x, int p)
		{
			//insert in H
			H.push_back(make_pair(x,p));
			//add the index to the map I
			I.insert(make_pair(x,H.size()-1));
			//bubble up
			bubble_up(H.size() - 1);
		}

		// Returns the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		// 
		// Must run in O(1) time.
		T front(){ return H[0].first;}

		// Removes the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		//
		// Must run in O(log(n)) time. 
		void pop()
		{
			if (H.size() == 0)return;
			//set last as root
			H[0] = H[H.size() - 1];
			//remove last
			H.pop_back();
			if (H.size() == 0)return;
			//bubble down
			bubble_down();
		}

		// If x is in the MinPriorityQueue 
		// with current priority at least new_p,  
		// then changes the priority of x to new_p.
		// Undefined behavior otherwise.
		//
		// Must run in O(log(n)) time. 
		void decrease_key(T x, int new_p)
		{
			auto search = I.find(x);
			if (search != I.end()) {
				H[search->second].second = new_p;
				bubble_up(search->second);

			}
		}

	private:
		// You don't need any other instance variables,
		// but you can add some if you want to.
		vector< pair<T, int> > H; // The heap.
		unordered_map<T, int> I;  // Maps values to their indices in H.

		//takes two strings in I and swaps their index
		void swap_index(T x,T y, int index) {
			auto search = I.find(x);
			auto search2 = I.find(y);
			if (search != I.end() && search2 != I.end()) {	 
				swap(search->second, search2->second);
			}
			else { cout << "swap failed" << endl; }
		}
		int parent(int i)	{	return (i - 1) / 2;}

		//is node at index i in violation
		//with parent node.
		bool parent_violation(int i)
		{
			if (H[i].second < H[parent(i)].second)
				return true;
			else
				return false;
		}

		bool children_violation(int i) {
			//it theres two children
			if (l_child(i) <= H.size() - 1 && r_child(i) <= H.size() - 1) {
				//if left or right child are smaller than parent return true
				if (H[l_child(i)].second < H[i].second || H[r_child(i)].second < H[i].second)
					return true;
				else
					return false;
			}
			else if (l_child(i) <= H.size() - 1 && r_child(i) > H.size() - 1) {//if theres one children
				if (H[l_child(i)].second < H[i].second)//if left child is smaller than parent theres violation
					return true;
				else
					return false;
			}
			else if (l_child(i) > H.size() - 1) {//if no left children return (because there cant be any children)
				return false;
			}
		}

		//bubble item at index position
		//up heap until it doesn't violate with
		//it's parent.
		void bubble_up(int index)
		{
			while (parent_violation(index))
			{
				swap(H[index], H[parent(index)]);
				swap_index(H[index].first ,H[parent(index)].first, index);
				index = parent(index);
			}
		}

		

		int l_child(int i) {
			return 2 * i + 1;
		}

		int r_child(int i) {
			return l_child(i) + 1;
		}

		void bubble_down() {
			int i = 0;
			while (children_violation(i)) {
				//if theres no right children
				if (l_child(i) <= H.size() - 1 && r_child(i) > H.size() - 1) {
					swap(H[i], H[l_child(i)]);
					swap_index(H[i].first, H[l_child(i)].first, i);
					i = l_child(i);
				}
				else {
				  //swap with left if left is smaller than right
				  if (H[l_child(i)].second < H[r_child(i)].second) {
					swap(H[i], H[l_child(i)]);
					swap_index(H[i].first, H[l_child(i)].first, i);
					i = l_child(i);
				  }
				  else {//swap with right
					swap(H[i], H[r_child(i)]);
					swap_index(H[i].first, H[r_child(i)].first, i);
					i = r_child(i);
						
				  }	
				}
 
			}
		}
};

#endif 

