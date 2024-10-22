/*

    A program that attempts greedy algorithm to minimize the number of chocolate productions.

*/

/*

    time-related functions are adopted from:
    https://www.geeksforgeeks.org/cpp-program-print-current-day-date-time/

*/

#include<iostream>
#include<vector>
#include<ctime>

using namespace std;

int main(){

    // declaring and initializing variables
    vector<int> S, recordS, discardedS; // vectors to store milk-related data
    vector<double> B; // vector to store batch of chocolate data
    vector<time_t> B_date_time; // vector to store production date & time
    int d = 0, milk = 0, maxMilk = 0; // d is the maximum amount of chocolate in each batch
    double milkToChocolate = 0.5;
    time_t tt; // declaring argument for time()
    time_t duration = 3600; // represents an hour in seconds
    struct tm* ti; // variable to store return value of localtime()

    // accept milk shipments until user enter -1
    cout << "Enter the shipments of milk in litre (-1 to stop):\n";
    while(true){
        cin >> milk;
        if (milk > 0)
            S.push_back(milk); // store milk into S
        else if (milk == -1)
            break;
        else
            cout << "Enter valid number only:\n";
    }

    // get input for d
    cout << "Specify the amount of chocolate to be produced" 
    << " in each batch (kg): ";
    cin >> d;

    // the maximum amount of milk (L) can be used in 
    // one batch of chocolate production
    maxMilk = d * 2;

    // initialize variables needed to produce chocolate
    int i = 0, batch = 0, bucket = 0;
    // initialize discarded amount of milk in each milk shipment to 0s
    for (int j=0; j<S.size(); j++)
        discardedS.push_back(0);
    
    // start producing chocolate
    while (i < S.size()){
        bucket = 0; // empty bucket in each batch before production
        // collecting maximum amount of milk before begin producing
        while((bucket < maxMilk) && (i < S.size())){
            bucket = bucket + S[i];
            recordS.push_back(batch); // record which batch of production the milk shipment is used for
            i++;
        }
        // discard overloaded milk
        if (bucket > maxMilk){
            discardedS.erase(discardedS.begin() + (i-1)); // remove 0 at position i-1
            discardedS.emplace((discardedS.begin() + (i-1)), (bucket - maxMilk)); // insert discarded milk in position i-1
            bucket = bucket - discardedS[i-1]; // remove overloaded milk
        }
        // produce chocolate
        B.push_back(bucket * milkToChocolate); // turn milk into chocolate and store inside B
        
        // storing manufacture time
        time(&tt); // get current calendar time in number of seconds elapsed since January 1, 1970
        tt = tt + duration; // to imitate the production takes time
        B_date_time.push_back(tt); // store the production date & time
        duration = duration + 3600; // increment an hour so next production does not finish at the same time
        
        batch++;
    }

    cout << "\n==========================================================";
    cout << "\nEach batch can produce maximum " << d << "kg of chocolate.";
    cout << "\nChocolate to Milk ratio is 1:2";
    cout << "\nMaximum litre of milk in each production: " << d << " * 2 = " << maxMilk;
    cout << "\n==========================================================\n";

    // show the details of the produced batches
    cout << "\nProduction:";
    for (int j=0; j<B.size(); j++){
        ti = localtime(&*(B_date_time.begin()+j)); // convert time to local time
        // asctime returns a string that represents the time in human-readable format
        cout << endl << asctime(ti) << " B[" << j << "] produced " << B[j] << "kg of chocolate. (";
        for (int k=0; k<recordS.size(); k++){ // show which shipment of milk is used in batch j
            if (recordS[k] == j){
                cout << " S[" << k << "] ";
            }
        }
        cout << ")";
    }
    
    // show the amount of discarded milk in each shipment of milk
    cout << "\n\nDiscarded Milk: ";
    for(int j=0; j<discardedS.size(); j++){
        if (discardedS[j]>0){
            cout << "\nS[" << j << "] = " << S[j] << "L discarded " << discardedS[j] << "L.";
        }
        else{
            cout << "\nS[" << j << "] = " << S[j] << "L discarded 0L.";
        }
    }

    cout << endl;

    return 0;
}