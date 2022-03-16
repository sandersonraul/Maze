/**
 * Disjoint set class
 * Ue union by rank and path compression.
 * Elements in the set are numbered starting at 0.
 * 
 * 
 */
class DisjSets{
    public:
       // Generates the disjoint sets, one for each element.
        explicit DisjSets(int numElements);
        //return set's name containing x
        int find(int x);
        //return set's name containing x, with path compression.
        int find(int x);
        // Return the current number of disjoint sets
        int size()const;

        private:
            int* Maze;

} ;