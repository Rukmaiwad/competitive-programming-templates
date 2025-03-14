import java.util.*;
import java.io.*;

class DisjointSet {
    List<Integer> rank = new ArrayList<>();
    List<Integer> parent = new ArrayList<>();
    List<Integer> size = new ArrayList<>();

    public DisjointSet(int n) {
        for (int i = 0; i <= n; i++) {
            rank.add(0);
            parent.add(i);
            size.add(1);
        }
    }

    // To find parent or Ultimate Parent
    public int findParent(int u) {
        if (u == parent.get(u)) {
            return u;
        }
        int x = findParent(parent.get(u));
        parent.set(u, x);
        return x;
    }

    // Union By Rank
    public void unionByRank(int u, int v) {
        // Find ultimate Parent
        int up_u = findParent(u);
        int up_v = findParent(v);

        if (up_u == up_v) {
            return;
        }

        if (rank.get(up_u) < rank.get(up_v)) {
            parent.set(up_u, up_v);
        } else if (rank.get(up_v) < rank.get(up_u)) {
            parent.set(up_v, up_u);
        } else {
            parent.set(up_v, up_u);
            rank.set(up_u, rank.get(up_u) + 1); // Increment rank only after setting the parent
        }
    }

    // Union By Size
    public void unionBySize(int u, int v) {
        // Find Ultimate Parent
        int up_u = findParent(u);
        int up_v = findParent(v);

        if (up_u == up_v) {
            return;
        }

        if (size.get(up_u) < size.get(up_v)) {
            size.set(up_v, size.get(up_v) + size.get(up_u));
            parent.set(up_u, up_v);
        } else {
            size.set(up_u, size.get(up_u) + size.get(up_v));
            parent.set(up_v, up_u);
        }
    }

    // function to find number of components in graph.
    int numberOfComp(int n){
        Set<Integer> st = new HashSet<>();
        for(int i=1;i<=n;i++){
            st.add(findParent(i));
        }
        return st.size();
        
    }
}

class Main {
    public static void main(String[] args) {
        DisjointSet ds = new DisjointSet(7);

        ds.unionByRank(1, 2);
        ds.unionByRank(2, 3);
        ds.unionByRank(4, 5);
        ds.unionByRank(6, 7);
        ds.unionByRank(5, 6);

        // Checking if 3 and 7 belong to the same component
        if (ds.findParent(3) == ds.findParent(7)) {
            System.out.println("Same component");
        } else {
            System.out.println("Different components");
        }

        ds.unionByRank(3, 7);

        if (ds.findParent(3) == ds.findParent(7)) {
            System.out.println("Same component");
        } else {
            System.out.println("Different components");
        }
    }
}
