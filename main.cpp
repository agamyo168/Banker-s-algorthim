#include <iostream>
#include <string>
#include <vector>


using namespace std;
void input(int n,vector<int> &a)
{   int temp;
    for(int i = 0; i <n ; ++i)
    {
        cin>>temp;
        a.push_back(temp);
    }
}
void sum(vector<int> &a, vector<int> &b)
{
    for(int i = 0; i <a.size(); ++i)
    {
        a[i] = a[i]+b[i];
    }
}
void sub(vector<int> &a, vector<int> &b)
{
    for(int i = 0; i <a.size(); ++i)
    {
        a[i] = a[i] - b[i];
    }
}
bool compare(vector<int> a, vector<int> b)
{
    for(int i = 0; i<b.size();++i)
    {
        if(a[i] > b[i])
            return false;
    }
    return true;

}
bool compareG(vector<int> a, vector<int> b)
{
    for(int i = 0; i<b.size();++i)
    {
        if(a[i] < b[i])
            return false;
    }
    return true;

}
void nestedInput(int n, int m, vector<vector <int> > &a)
{
    for(int i = 0; i <n; ++i)
    {   vector<int> temp;
        int in;
        for(int j = 0;j<m;++j)
        {
            cin>>in;
            temp.push_back(in);

        }
        a.push_back(temp);
    }
}
void display(vector<int> a)
{
    for(int i =0;i<a.size();++i)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
void displayNested(vector<vector<int> > a)
{
    for(int i = 0; i <a.size(); ++i)
    {
        cout<<"P"<<i<<" ";
        for(int j=0;j<a[i].size();++j)
    {
        cout<<a[i][j]<<" ";
    }
    cout<<endl;
    }
}
void needIn(int n, int m, vector<vector<int> > max, vector<vector<int> > allocation,vector<vector<int> > &need)
{
    for(int i = 0; i <n; ++i)
            {   vector<int> temp;
                for(int j = 0; j < m; ++j)
                {
                    temp.push_back(max[i][j]-allocation[i][j]);
                }
                need.push_back(temp);
            }
            cout<<"Need vector is:"<<endl;
            displayNested(need);

}
void safeState(vector<vector<int> > need, vector<vector<int> > allocation, vector<int> available,int n,bool &state,vector<int> &order)
{           vector<int> work;
            vector<bool> finish;
            //Safety algorithm initialization:
            work = available;
            for(int i = 0; i < n; ++i)
            {
                finish.push_back(false);
            }
            //algorithm
            int counter =0;
            while(counter<n)
            {
                for(int i = 0; i < n; ++i)
            {
                if(finish[i]==false&&compare(need[i],work))
                {   finish[i]= true;
                    counter = 0;
                    order.push_back(i);
                    sum(work,allocation[i]);
                }
                counter++;
            }
            }
           //safety test
            state = true;
            for(int i = 0; i<n;++i)
            {
                if(finish[i] == false)
                    {state = false;}
            }

}
//request(){}

int main()
{   bool con = true;
    bool state;
    int n,m;
    int req;
    vector<int> order;
    vector<vector<int> > allocation;
    vector<vector<int> > max;
    vector<int> available;
    vector<vector<int> > need;
    vector<vector<int> > request;
    vector<vector<int> > vectep;
    bool loop = true;
    cout << "Banker's Algorithm Program:" << endl;
    do{     loop = true;
            allocation.clear();
            max.clear();
            available.clear();
            need.clear();
            cout<<"Enter the number of processes and resources respectively: "<<endl;
            cin>>n>>m;
            cout<<"Please Enter the allocation matrix: "<<endl;
            nestedInput(n,m,allocation);
            cout<<"Please Enter the max matrix: "<<endl;
            nestedInput(n,m,max);
            cout<<"Please Enter the available vector: "<<endl;
            input(m,available);
            //Need Vector
            needIn(n,m,max,allocation,need);
            //Menu
            vector<int> bo;
            bo.push_back(0);
            for(int i = 0; i < n; ++i)
            {
                request.push_back(bo);
            }

    while(loop)
    {
            cout<<endl;
            cout<<"1-Safe State\n2-Grant request\n3-Restart\n4-Exit\n"<<endl;
            cout<<"Enter your selection: ";
            int x;
            cin>>x;


        switch(x)
        {
            case 1:
                {
                safeState(need,allocation,available,n,state,order);
                if(state)
                {
                    cout<<"Yes, Safe state <";
                    for(int i = 0; i <order.size(); ++i)
                {
                    cout<<"P"<<order[i];
                    if(i == order.size()-1)
                    {
                        cout<<">";
                    }
                    else
                        cout<<",";
                }
                }
                else
                    cout<<"Not in safe state."<<endl;
                order.clear();
                    break;
                }
            case 2:
            {
            cout<<"Enter the process requesting resources: ";
            cin>>req;
            cout<<"Enter the requested resources vector: ";
            vector<int> temp;
            for(int i =0; i <m; ++i)
            {   int a;
                cin >> a;
                temp.push_back(a);
            }
                request[req] = temp;
           if(!compareG(need[req],request[req]))
            {
                cout<<"Error: process has exceeded it's maximum claim."<<endl;
            }
            else if(!compareG(available,request[req]))
            {
                cout<<"the process must wait;no resources are available."<<endl;
            }
            else if(compareG(need[req],request[req]))
            {
                    vectep.push_back(available);
                    vectep.push_back(allocation[req]);
                    vectep.push_back(need[req]);
                    sub(available,request[req]);
                    sum(allocation[req],request[req]);
                    sub(need[req],request[req]);
                    safeState(need,allocation,available,n,state,order);
                if(state)
                {
                cout<<"Yes, request can be granted with safe state, Safe state <P"<<req<<"req,";
                for(int i = 0; i <order.size(); ++i)
                {
                    cout<<"P"<<order[i];
                    if(i == order.size()-1)
                    {
                        cout<<">";
                    }
                    else
                        cout<<", ";
                }
                order.clear();
                temp.clear();


            }
            else
            {
                cout<<"No, request cannot be granted with safe state.";
            }
                   if(!state)
                    {
                        available = vectep[0];
                        allocation[req] = vectep[1];
                        need[req] = vectep [2];
                    }
            }
            break;
            }
            //grant request
            case 3://restart
               {

                con = true;
                loop = false;
                break;
               }

            case 4:

                con = false;
                loop = false;
                break;
                //exit

        }


    }
   }while(con);
    return 0;
}
