#pragma once

#include "CoreMinimal.h"
#include "Algo/Reverse.h"
#include "Templates/Tuple.h"
#include "Templates/SharedPointer.h"



// A single Node with an Object Pointer and a reference to an Index
template <typename T>
struct Node {
	TWeakPtr<int> Index;
	T Object;
	int Parent;
	Node(int Idx, TSharedRef<int> InIndex, T InObject)
		: Index(InIndex)
		, Object(InObject)
		, Parent(Idx) // Points to Self
	{
		// Update Index
		*Index.Pin() = Idx;
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
	UnionFindSplit() { Nodes = {}; }

	// Element Adding/Deletion
	void Add(TSharedRef<int> Index, T Object);
	T Remove(TSharedRef<int>&& Index);

	// Query
	inline int Num() const { return Nodes.Num(); }
	bool Contains(TFunction<bool(const T&)> Predicate) const;

	// Set Operations
	T* Find(int Index);
	void Union(int A, int B);
	void Split(int A, int B);
	void Split(int A);
	
private:
	Node<T>* FindNode(int Index);
	int FindLastCommon(int A, int B, int& ADiff, int& BDiff);

	TArray<int> GetPathToRoot(int Index);

	// State
	TArray<Node<T>> Nodes;
};

template<typename T>
inline bool UnionFindSplit<T>::Contains(TFunction<bool(const T&)> Predicate) const {
	for (const Node<T>& Node : Nodes) {
		if (Predicate(Node.Object)) return true;
	}
	return false;
}

// Add an Element to the Set
template<typename T>
inline void UnionFindSplit<T>::Add(TSharedRef<int> Index, T Object) {
	if (Nodes.Num() > 500) {
		UE_LOG(LogTemp, Warning, TEXT("Many Colours: %d"), Nodes.Num());
	}

	// Create and Add the Node
	Node<T> Item = { Nodes.Num(), Index, Object };
	Nodes.Add(Item);
}

// Removes a Node, Replacing it with a random direct Child
template<typename T>
inline T UnionFindSplit<T>::Remove(TSharedRef<int>&& Index) {
	int Idx = *Index;

	if (!Nodes.IsValidIndex(Idx)) return T();

	// Check for a Node to Replace the Node.
	Node<T>* Replacement = Nodes.FindByPredicate([Idx](const Node<T>& Item) {
		return Item.Parent == Idx && Item.Index.IsValid() && *Item.Index.Pin() != Idx;
	});

	// When the Node needs to be replaced Parent-Wise
	if (Replacement) {
		// Replace Parents
		for (Node<T>& Item : Nodes) {
			if (Item.Parent == *Index) Item.Parent = *Replacement->Index.Pin();
		}
	}


	// Shift down Greater Elements, and Stale Elements
	for (Node<T>& Item : Nodes) {
		// Shift Indices
		if (Item.Index.IsValid() && *Item.Index.Pin() > Idx) *Item.Index.Pin() -= 1;
		if (Item.Parent > Idx)  Item.Parent -= 1;
	}

	//int Shift = 0;
	//// Shift down Greater Elements, and Stale Elements
	//for (Node<T>& Item : Nodes) {
	//	if (!Item.Index.IsValid() || *Item.Index.Pin() == Idx) {
	//		Shift++;
	//		continue;
	//	}
	//	// Shift Indices
	//	*Item.Index.Pin() -= Shift;
	//	Item.Parent -= Shift;
	//}

	//// Remove Stale Nodes
	//Nodes = Nodes.FilterByPredicate([](const Node<T>& Node) {
	//	return Node.Index.IsValid();
	//});
	//Idx -= Shift - 1;

	// Remove Indexes Node and Clear Index
	T Object = Nodes[Idx].Object;
	Nodes.RemoveAt(Idx);

	// Reset Index
	*Index = -1;

	return Object;

}

// Finds the Node Associated with an Index
template<typename T>
inline Node<T>* UnionFindSplit<T>::FindNode(int Index) {
	// Invalid Pointer
	if (Index == -1 || !Nodes.IsValidIndex(Index)) return NULL;

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
	Node<T>* ANode = FindNode(A);
	Node<T>* BNode = FindNode(B);
	// Unify Parents
	if (ANode && BNode)	FindNode(A)->Parent = FindNode(B)->Parent;
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

template<typename T>
inline void UnionFindSplit<T>::Split(int A) {
	if (!Nodes.IsValidIndex(A)) return;

	// Get ReplaceParent
	int ReplaceParent = Nodes[A].Parent;
	if (ReplaceParent == A) {
		for (int i = Nodes.Num(); i --> 0;) {
			if (i != A && Nodes[i].Parent == A) {
				ReplaceParent = i;
				break;
			}
		}
	}

	// Apply ReplaceParent
	for (Node<T>& Node : Nodes) {
		if (Node.Parent == A) {
			Node.Parent = ReplaceParent;
		}
	}
	Nodes[A].Parent = A;
}