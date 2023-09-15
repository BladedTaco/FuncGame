#pragma once

#include "CoreMinimal.h"
#include "Algo/Reverse.h"
#include "Templates/Tuple.h"



// A single Node with an Object Pointer and a reference to an Index
template <typename T>
struct Node {
	int* Index;
	T Object;
	int Parent;
	Node(int Idx, int& InIndex, T InObject)
		: Index(&InIndex)
		, Object(InObject)
		, Parent(Idx) // Points to Self
	{
		// Update Index
		InIndex = Idx;
	}
	~Node() {
		*Index = -1;
	}
};


/*
A Class for A Disjoint Set that has the operations Union, Find, and Split
Index is Node Position, -1 is Undefined
Parent Index is positive for parent, negative for Object
*/

template <typename T>
class UnionFindSplit {
public:
	// Element Adding/Deletion
	void Add(int& Index, T Object);
	T Remove(int& Index);

	// Query
	inline int Num() const { return Nodes.Num(); }

	// Set Operations
	T* Find(int Index);
	void Union(int A, int B);
	void Split(int A, int B);
	
private:
	Node<T>* FindNode(int Index);
	int FindLastCommon(int A, int B, int& ADiff, int& BDiff);

	TArray<int> GetPathToRoot(int Index);

	// State
	TArray<Node<T>> Nodes;
};

// Add an Element to the Set
template<typename T>
inline void UnionFindSplit<T>::Add(int& Index, T Object) {
	// Create and Add the Node
	Node<T> Item = { Nodes.Num(), Index, Object };
	Nodes.Add(Item);
}

// Removes a Node, Replacing it with a random direct Child
template<typename T>
inline T UnionFindSplit<T>::Remove(int& Index) {
	// Check for a Node to Replace the Node.
	Node<T>* Replacement = Nodes.FindByPredicate([Index](const Node<T>& Item) {
		return Item.Parent == Index && *Item.Index != Index;
	});

	// When the Node needs to be replaced Parent-Wise
	if (Replacement) {
		// Replace Parents
		for (Node<T>& Item : Nodes) {
			if (Item.Parent == Index) Item.Parent = *Replacement->Index;
		}
	}

	// Shift down Greater Elements
	for (Node<T>& Item : Nodes) {
		// Shift Indices
		if (*Item.Index > Index) *Item.Index -= 1;
		if (Item.Parent > Index) Item.Parent -= 1;
	}

	// Remove Indexes Node and Clear Index
	T Object = Nodes[Index].Object;
	Nodes.RemoveAt(Index);

	return Object;

}

// Finds the Node Associated with an Index
template<typename T>
inline Node<T>* UnionFindSplit<T>::FindNode(int Index) {
	// Invalid Pointer
	if (Index == -1) return NULL;

	// Get the Node associated with the Index
	Node<T>* Node = &Nodes[Index];

	// Points to Object
	if (Node->Parent == Index) return Node;

	// Points to Node
	return FindNode(Node->Parent);
}

// Returns the Lowest Common Ancestor, outputs the A and B path direct children.
// Returns -1 on failure, sets no children on same node or failure.
template<typename T>
inline int UnionFindSplit<T>::FindLastCommon(int A, int B, int& ADiff, int& BDiff) {
	// Check for Nothing in Common
	Node<T>* ANode = FindNode(A);
	if (!ANode || ANode != FindNode(B)) return -1;
	// Check for equal
	if (A == B) return A;

	// Nodes have common ancestor
	TArray<int> APath = GetPathToRoot(A);
	TArray<int> BPath = GetPathToRoot(B);
	Algo::Reverse(APath);
	Algo::Reverse(BPath);

	// Find Last Common Node
	int MinLength = FMath::Min(APath.Num(), BPath.Num());
	int Idx = 0;
	while (Idx < MinLength && APath[Idx] == BPath[Idx]) Idx++;

	// Set Child Outputs
	ADiff = APath.IsValidIndex(Idx) ? APath[Idx] : -1;
	BDiff = BPath.IsValidIndex(Idx) ? BPath[Idx] : -1;

	// Return Common Node
	return APath[Idx - 1];
}

// Returns the Path to Root as Indices
template<typename T>
inline TArray<int> UnionFindSplit<T>::GetPathToRoot(int Index) {
	// Start with Root
	TArray<int> Path = { Index };
	Node<T>* Node = &Nodes[Index];

	// Move up Until Root
	while (Node->Parent != Index) {
		Index = Node->Parent;
		Node = &Nodes[Node->Parent];
		// Appending Path
		Path.Add(Index);
	}

	return Path;
}

// Finds the Object Associated with an Index
template<typename T>
inline T* UnionFindSplit<T>::Find(int Index) {
	Node<T>* Node = FindNode(Index);
	return Node ? &Node->Object : NULL;
}

// Unifies two sets
template<typename T>
inline void UnionFindSplit<T>::Union(int A, int B) {
	// Unify Parents
	FindNode(A)->Parent = FindNode(B)->Parent;
}

// Splits below the common ancestor; A prioritized for detach.
template<typename T>
inline void UnionFindSplit<T>::Split(int A, int B) {
	// Get Common and children
	int AChild, BChild;
	int Common = FindLastCommon(A, B, AChild, BChild);

	// Already Split on no common, or same
	if (Common == -1 || A == B) return;

	// Redirect first valid child to itself
	int Child = AChild == -1 ? BChild : AChild;
	Nodes[Child].Parent = Child;
}
