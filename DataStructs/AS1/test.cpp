#include <stdio>

int main(){


for (int i=2; i<n; i++){ // This is O(n)
        for (int j=2; j*j<=i; j++) // This is O(sqrt(n)
        {
            // These are constant time so they don't matter
            if (i % j == 0)
                break;
            else if (j+1 > sqrt(i)) {
                cout << i << " ";

            }
        }
}
