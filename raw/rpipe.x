program rpipe{
	version v1{
		int rpipe_open(string name)=1;
		int rpipe_close(int fid)=2;
		string rpipe_recv(int fid, unsigned int max_len)=3;
		int rpipe_send(int fid, string msg)=4;
	}=1;
}=0x20100160;
