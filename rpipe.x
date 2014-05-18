program rpipe{
	version v1{
		int open(string name)=1;
		int close(int fid)=2;
		string recv(int fid)=3;
		int send(string msg)=4;
	}=1;
}=0x20100160;
