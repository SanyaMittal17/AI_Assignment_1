
#ifndef SPORTSLAYOUT_H
#define	SPORTSLAYOUT_H
#define ll long long
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

class SportsLayout{

    private:
    int z,l;
    int** T;
    int **N;
    int time;
    int *mapping;

    public:
    SportsLayout(string inputfilename){   
        readInInputFile(inputfilename);
        mapping= new int[z];
    };

    bool check_output_format(){

        vector<bool> visited(l,false);
        for(int i=0;i<z;i++)
        {
            if((mapping[i]>=1 && mapping[i]<=l))
            {
                if(!visited[mapping[i]-1])
                visited[mapping[i]-1]=true;
                else
                {
                    cout<<"Repeated locations, check format\n";
                    return false;
                }
            }
            else
            {
                cout<<"Invalid location, check format\n";
                return false;
            }
        }

        return true;

    };

    // void readOutputFile(string output_filename);
    
    long long cost_fn(){
        long long cost=0;

        for(int i=0;i<z;i++)
        {
           for(int j=0;j<z;j++) 
           {
                cost+=(long long)N[i][j]*(long long)T[mapping[i]-1][mapping[j]-1];
           }
        }

        return cost;
    };

    void write_to_file(string outputfilename){

         // Open the file for writing
    ofstream outputFile(outputfilename);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        cerr << "Failed to open the file for writing." << std::endl;
        exit(0);
    }

    for(int i=0;i<z;i++)
    outputFile<<mapping[i]<<" ";

    // Close the file
    outputFile.close();

    cout << "Allocation written to the file successfully." << endl;

    };

    void readInInputFile(string inputfilename){
            fstream ipfile;
	        ipfile.open(inputfilename, ios::in);
            if (!ipfile) {
                cout << "No such file\n";
                exit( 0 );
            }
            else {
                

                ipfile>> time;
                ipfile >> z;
                ipfile >> l;

                if(z>l)
                {
                    cout<<"Number of zones more than locations, check format of input file\n";
                    exit(0);
                }


            

            int **tempT;
            int **tempN;

          tempT = new int*[l];
         for (int i = 0; i < l; ++i)
            tempT[i] = new int[l];
        
        tempN = new int*[z];
        for (int i = 0; i < z; ++i)
            tempN[i] = new int[z];

        for(int i=0;i<z;i++)
        {
            for(int j=0;j<z;j++)
            ipfile>>tempN[i][j];
        }

        for(int i=0;i<l;i++)
        {
            for(int j=0;j<l;j++)
            ipfile>>tempT[i][j];
        }

        ipfile.close();

        T= tempT;
        N= tempN;
            }

    };

long long convert(vector<int> v){
        int w[z];
        for(int i=0;i<l;i++){
            if (v[i]!= -1){
                w[v[i]-1]=i+1;
            }
        }
        long long cost=0;
        for(int i=0;i<z;i++)
        {
           for(int j=0;j<z;j++) 
           {
                cost+=(long long)N[i][j]*(long long)T[w[i]-1][w[j]-1];
           }
        }

        return cost;
    };

    // gives best neighbour
    pair<vector<int>,ll> neighborhood(vector<int> v){
        ll parent_cost= convert(v); 
        pair<vector<int>,ll>  ans=pair<vector<int>,ll>(v,parent_cost);
        ll cost=parent_cost;
        ll curr_min=cost;
        vector<int> w=v;
        for(int i=0;i<l;i++){
            if(v[i]!= -1){
                for(int j=i+1;j<l;j++){
                    // int w[l] = v;
                    // int w[l];
                    // copy(v,v+l,w);
                    swap(w[i],w[j]);
                    if (w[j]!=-1 && w[i]!=-1)
{                    for (int k=0;k<z;k++){
                        cost+=((long long)N[w[k]-1][w[i]-1]+(long long)N[w[i]-1][w[k]-1])*((long long)T[k][j]-(long long)T[k][i]);
                        cost+=((long long)N[w[k]-1][w[j]-1]+(long long)N[w[j]-1][w[k]-1])*((long long)T[k][i]-(long long)T[k][j]);
                    }}
                    if (w[j]==-1){
                        for (int k=0;k<z;k++){
                        cost+=((long long)N[w[k]-1][w[i]-1]+(long long)N[w[i]-1][w[k]-1])*((long long)T[k][j]-(long long)T[k][i]);}
                    }
                    if (cost<=curr_min){ans=pair<vector<int>,ll>(w,cost);curr_min=cost;}
                        cost=parent_cost;
                    swap(w[i],w[j]);
                }
            }
        }
        return ans;
    };
    vector<vector<int> > getPermutations(vector<int> nums) {
        vector<vector<int> > result;

        if (nums.size() <= 1) {
            result.push_back(nums);
            return result;
        }

        for (size_t i = 0; i < nums.size(); ++i) {
            vector<int> remaining = nums;
            remaining.erase(remaining.begin() + i);

            vector<vector<int> > permutations = getPermutations(remaining);

            for (const auto& perm : permutations) {
                vector<int> new_perm;
                new_perm.push_back(nums[i]);
                new_perm.insert(new_perm.end(), perm.begin(), perm.end());
                result.push_back(new_perm);
            }
        }
        return result;
    };
    void answer(){
        vector<int> current(l,0);
        for(int i=0;i<l;i++){
            if (i<=z-1){
            current[i]=i+1;
            }else{
                current[i]=-1;
            }
        }
        vector<vector<int> > permute = getPermutations(current);
        ll ans= INT16_MAX;
        vector<int> next;
        for (auto x: permute){
            if(convert(x)<ans){
                ans=convert(x);
                next=x;
            }
        }
        int w[z];
        for(int i=0;i<l;i++){
            if (next[i]!= -1){
                w[next[i]-1]=i+1;
            }
        }
        cout<<"minimum cost: "<< ans<<endl;
        cout<<"minimum cost mapping :";
        for(auto x: w){
            cout<<x<<" ";
        }
        cout<<endl;

    }


    void compute_allocation()
    {
        //you can write your code here 
        //comment out following dummy code
        vector<int> ans;
        ll global_cost = INT_MAX;
        // int current[l];
        vector<int> current(l,0);
        for(int i=0;i<l;i++){
            if (i<=z-1){
            current[i]=i+1;
            }else{
                current[i]=-1;
            }
        }
        // random_device rd;
        mt19937 rng(12345);
        vector<int> sample_state=current;
        ll sample_cost=convert(current);
        // for (int i=0;i<10;i++)
        //     {shuffle(current.begin(),current.end(),rng);
        //     if (convert(current)<sample_cost)
        //         {sample_state=current;
        //         sample_cost=convert(current);}}
        int timeElapsed = 0;
        auto start = chrono::high_resolution_clock::now();
        while(timeElapsed < time*60){
            auto now = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsedDuration = now - start;
            timeElapsed = static_cast<int>(elapsedDuration.count());
            pair<vector<int>,ll> a = neighborhood(current);
            vector<int> neighbor = a.first; 
            ll min_cost = a.second;
            ll parent_cost=convert(current);
            if (min_cost>parent_cost){
                //random restart
                shuffle(current.begin(),current.end(),rng);
                // sample_cost=parent_cost;
                // sample_state=current;
                // for (int i=0;i<9;i++)
                //     {shuffle(current.begin(),current.end(),rng);
                //     int curr_cost=convert(current);
                //     if (curr_cost<sample_cost)
                //         {sample_state=current;
                //         sample_cost=curr_cost;}}
                
            }else{
                // copy(next_state,next_state+l,current);
                current=neighbor;
                if (min_cost<=global_cost){
                    global_cost= min_cost;
                    ans=neighbor;
                }
            }
        }
        for(int i=0;i<l;i++){
            if (ans[i]!= -1){
                mapping[ans[i]-1]=i+1;
            }
        }

    };


};

int main(int argc, char** argv )
{

     // Parse the input.
    if ( argc < 3 )
    {   
        cout<<"Missing arguments\n";
        cout<<"Correct format : \n";
        cout << "./main <input_filename> <output_filename>";
        exit ( 0 );
    }
    string inputfilename ( argv[1] );
    string outputfilename ( argv[2] );
    
    SportsLayout *s  = new SportsLayout( inputfilename );
    s->compute_allocation();
    s->write_to_file(outputfilename);

    long long cost = s->cost_fn ();
    cout<< "cost:"<<cost<<endl;


    return 0;

}


#endif
