// separate chaining technique (head insertion)
// create a hashtable of integers
import java.util.LinkedList;
import java.util.ArrayList;

public class hashtable
{
    // hashFunction() CHECK
    // void insert() CHECK
    // void delete() CHECK
    // int search() // if value not found then return -1

    // table size
    int capacity;

    // amount of values allowed to be in the hashtable
    int amount;

    private ArrayList<LinkedList<Integer>> myArray;

    // creates an arraylist with "capacity" number of linkedlists
    hashtable(int capacity)
    {
        this.capacity = capacity;
        myArray = new ArrayList<>();
        for (int i = 0;i < capacity;i++)
        {
            LinkedList<Integer> ll = new LinkedList<>();
            myArray.add(ll);
            myArray.set(i, ll);
        }
    }

    // returns the linkedlist at the indexth index
    public LinkedList<Integer> getList(int index)
    {
        return myArray.get(index);
    }

    // gets the correct linked list and performs a head insertion using the
    // passed in value
    public void setList(int hashedIndex, int value)
    {
        myArray.get(hashedIndex).addFirst(value);
    }

    // input: value to be placed in the arraylist
    // output: the index at which the value will be placed at
    public int hashFunction(int value)
    {
        int retVal = (value * 31) % capacity;
        return retVal;
    }

    // creates a linked list on the spot rather than creating
    // 'capacity' number of linked lists from the constructor 
    // to optimize memory usage
    public void insert(int value)
    {
        // stores the index for which 'value' will be placed in
        int hashedIndex = hashFunction(value);
        // LinkedList<Integer> ll = getList(hashedIndex);
        
        // linked list is definitely in the hash table, so
        // we need to find the right one using the hash function generated hash index

        setList(hashedIndex, value);
        // ++capacity;
    }

    // we pass in the value we want to delete rather than
    // what index we want to traverse to because of clarity and user-friendliness
    public void delete(int value)
    {
        if (search(value))
        {
            int hashedIndex = hashFunction(value);
            getList(hashedIndex).removeFirstOccurrence(value);
            // --capacity;
        }
    }

    // return true if value is found, returns false otherwise.
    public boolean search(int value)
    {
        int hashedIndex = hashFunction(value);
        return getList(hashedIndex).contains(value);
    }

    public static void main(String[] args)
    {
        int c = (args.length > 0) ? Integer.parseInt(args[0]) : 11;
        hashtable h = new hashtable(c);

        // for (int i = 0;i < 10;i++)
        // {
        //     // insert n random integers between 1 and 100
        //     h.insert((int)((Math.random() * 101) + 1));
        // }

        h.insert(6);
        // h.insert(3);
        // h.insert(5);
        // h.insert(5);
        // h.insert(7);

        System.out.println(h.myArray);

        // System.out.println(h.search(5));
        // System.out.println(h.search(1));
        // System.out.println(h.search(3));
        // System.out.println(h.search(7));

        // h.delete(5);
        // h.delete(7);

        // System.out.println(h.myArray);
        
        // System.out.println(h.search(5));
        // System.out.println(h.search(1));
        // System.out.println(h.search(3));
        // System.out.println(h.search(7));

    }
}
