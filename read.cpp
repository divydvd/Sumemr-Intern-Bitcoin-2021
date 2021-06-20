#include<bits/stdc++.h>
#include<fstream>
#include<sstream>

using namespace std;

const int max_wt= 4000000;

struct Trans{
	string txid;
	int weight;
	int fee;
	bool done;
	vector<string> parent;
	Trans(string s, int f, int w){
		txid= s;		
		fee= f;
		weight= w;
		done= false;
	}
};

struct myCmp{
	bool operator()(Trans ts1, Trans ts2){
		return ts1.fee>ts2.fee;
	}
};


vector<string> selectBlock(vector<Trans> v){
	priority_queue<Trans, vector<Trans>, myCmp> pq;
	vector<string> res;

	int cost= 0;
	int wt= 0;

	for(int i=0; i<v.size(); i++){
		pq.push(v[i]);
	}

	unordered_set<string> us;

	while(wt<=max_wt && pq.empty()==false){
		Trans t= pq.top();
		pq.pop();
		if(t.parent.size()==0){
			cost+=t.fee;
			wt+=t.weight;
			t.done = true;
			us.insert(t.txid);
			res.push_back(t.txid);
			continue;
		}
		else if(t.parent.size()>0){
			bool flag= true;
			for(int i=0; i<t.parent.size(); i++){
				string s= t.parent[i];
				if(us.find(s)==us.end()){
					flag= false;
					break;
				}
			}
			if(flag==true){
			cost+=t.fee;
			wt+=t.weight;
			t.done = true;
			us.insert(t.txid);
			res.push_back(t.txid);
			}
		}
	}
	return res;
}

int main(){
	ifstream ip("mempool.csv");

	if(!ip.is_open())	{
		cout<<"ERROR: File Open"<<'\n';
	}

	string txid, fee, weight, parent, temp;
	vector<Trans> v;

	while(ip.good()){
		
		getline(ip, txid, ',');
		getline(ip, fee, ',');
		getline(ip, weight, ',');
		getline(ip, parent, '\n');

		stringstream f(fee);
		stringstream w(weight);

		int ff=0;
		int ww=0;

		f>>ff;
		w>>ww;

		struct Trans ts= Trans(txid, ff, ww);

		vector <string> tokens;
		stringstream check1(parent);
		string intermediate;
		while(getline(check1, intermediate, ';')){
			tokens.push_back(intermediate);
		}

		ts.parent= tokens;

		v.push_back(ts);

		

		// cout<<"Txid: "<<ts.txid<<'\n';
		// cout<<"Fee: "<<ts.fee<<'\n';
		// cout<<"Weight: "<<ts.weight<<'\n';
		// cout<<"Parent: ";
		// for(int i=0; i<ts.parent.size(); i++)
		// cout<<ts.parent[i]<<'\n';
		// cout<<'\n';

		// k--;
		
	}

	ip.close();

	ofstream MyFile("Block.txt");

	vector<string> res;
	res= selectBlock(v);

	for(auto x:res){
		MyFile<<x<<endl;

	}
		MyFile.close();

	return 0;
}